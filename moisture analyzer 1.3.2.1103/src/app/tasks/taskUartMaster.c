/* BIOS6 include */
/*driver/Uart_edma.c line 87 has been modified*/
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/GIO.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/task.h>
#include <scom.h>
#include <Uart.h>
#include <UartLocal.h>
#include <gooao_c6748.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

GIO_Handle uartMasterRxHandle;
GIO_Handle uartMasterTxHandle;
Uart_Params   uartMasterParams;

union{
	float mirror_float;
	uint8_t mirror_uint8_t[4];
}mirror_temperature;

union{
	float radiator_float;
	uint8_t radiator_uint8_t[4];
}radiator_temperature;

union{
	float control_float;
	uint8_t control_uint8_t[4];
}control_tempo;

void uartMaster_init(void);

uint8_t uart_Buffer[20] = {0};
int32_t uart_count = 0;

Void UartMasterProcess(Void)
{
    size_t    len     =  16;
    int32_t		  status  =  IOM_COMPLETED;
    double   pt100_temperature_tempo = 0, ntc_temperature_tempo = 0, control_quality_tempo = 0;
    uint16_t  PWM_value_tempo = 0;

    ScomMessage *uartMsg;
    SCOM_Handle hs_Proc2UM,hs_UM2Proc;

    hs_Proc2UM = SCOM_open("P2UM");
    hs_UM2Proc = SCOM_open("UM2P");

    typedef enum{
    	READY_TO_SEND,
    	HOLD_ON
    }uart_status;

    if(!hs_Proc2UM || !hs_UM2Proc )
    {
    	for(;;);
    }

    while(1)
    {
    	uartMsg = SCOM_getMsg(hs_Proc2UM, BIOS_WAIT_FOREVER);
    	mirror_temperature.mirror_float = (float)(uartMsg->NTC_Temparation);
    	control_tempo.control_float = (float)(uartMsg->control_quantity);
    	//pt100_temperature_tempo = uartMsg->PT100_Temparation;
    	//control_quality_tempo = uartMsg->control_quantity;
    	radiator_temperature.radiator_float = (float)(uartMsg->PT100_Temparation);
    	//ntc_temperature_tempo = uartMsg->NTC_Temparation;
    	PWM_value_tempo = uartMsg->PWM_value;

    	mirror_temperature.mirror_float -= 2.6;

    	if(mirror_temperature.mirror_float > 99)
    		mirror_temperature.mirror_float = 99;

    	if(mirror_temperature.mirror_float <- 70)
    		mirror_temperature.mirror_float = -70;

    	if(radiator_temperature.radiator_float >99)
    		radiator_temperature.radiator_float = 99;

    	if(radiator_temperature.radiator_float <-70)
    		radiator_temperature.radiator_float = -70;

//    	if(pt100_temperature_tempo > 99)
//    	{
//    		pt100_temperature_tempo = 99;
//    	}
//    	else if(pt100_temperature_tempo < -70)
//    	{
//    		pt100_temperature_tempo = - 70;
//    	}
//
//    	if(ntc_temperature_tempo > 99)
//    	{
//    		ntc_temperature_tempo = 99;
//    	}
//    	else if(ntc_temperature_tempo < -70)
//    	{
//    		ntc_temperature_tempo = - 70;
//    	}

//    	pt100_temperature_tempo = (pt100_temperature_tempo + 100) * 100;
//    	ntc_temperature_tempo = (ntc_temperature_tempo + 100) * 100;
//    	control_quality_tempo = control_quality_tempo * 100;

//    	uart_Buffer[1] = (intmax_t)ntc_temperature_tempo / 256;
//    	uart_Buffer[2] = (intmax_t)ntc_temperature_tempo % 256;
//    	uart_Buffer[5] = (intmax_t)pt100_temperature_tempo / 256;
//     uart_Buffer[6] = (intmax_t)pt100_temperature_tempo % 256;
//     uart_Buffer[8] = (intmax_t)control_quality_tempo / 256;
//     uart_Buffer[9] = (intmax_t)control_quality_tempo % 256;
//     uart_Buffer[10] = PWM_value_tempo / 256;
//     uart_Buffer[11] = PWM_value_tempo %256;

    	uart_Buffer[0] = 0xab;
    	uart_Buffer[1] = 0xab;
    	uart_Buffer[2] = 0xab;
    	uart_Buffer[3] = 0xab;

    	uart_Buffer[4] = mirror_temperature.mirror_uint8_t[0];
    	uart_Buffer[5] = mirror_temperature.mirror_uint8_t[1];
    	uart_Buffer[6] = mirror_temperature.mirror_uint8_t[2];
    	uart_Buffer[7] = mirror_temperature.mirror_uint8_t[3];

    	uart_Buffer[8] = radiator_temperature.radiator_uint8_t[0];
    	uart_Buffer[9] = radiator_temperature.radiator_uint8_t[1];
    	uart_Buffer[10] = radiator_temperature.radiator_uint8_t[2];
    	uart_Buffer[11] = radiator_temperature.radiator_uint8_t[3];

    	uart_Buffer[12] = control_tempo.control_uint8_t[0];
    	uart_Buffer[13] = control_tempo.control_uint8_t[1];
    	uart_Buffer[14] = control_tempo.control_uint8_t[2];
    	uart_Buffer[15] = control_tempo.control_uint8_t[3];

        if (uart_count == 0)
        {
        	status = GIO_write(uartMasterTxHandle, &uart_Buffer, &len);

			if (IOM_COMPLETED != status)
			{
				System_printf("\r\nGIO_write failed. returned : %d", status);
			}
        }

        uart_count++;

        if (uart_count > 1)
        	uart_count = 0;

		SCOM_putMsg(hs_UM2Proc, uartMsg);
    }
}

/**
 * @brief      Entry point for the main task. This creates the required channels
 *             and calls the required functions for demonstrating the UART
 *             driver
 *
 * @param      arg1  [IN]   unused
 * @param      arg2  [IN]   unused
 *
 * @return     None
 */
Void tskUartMaster(UArg arg1, UArg arg2)
{
    Uart_ChanParams    	chanParams;
	Error_Block 		eb;
 	GIO_Params 			ioParams;

    Error_init(&eb);

    GIO_Params_init(&ioParams);//Initialize channel attributes.
    ioParams.chanParams = (Ptr)&chanParams;

   	/* create the required streams for the UART demo                           */
    uartMasterTxHandle = GIO_create("/uart2", GIO_OUTPUT, &ioParams, &eb);
    uartMasterRxHandle = GIO_create("/uart2",GIO_INPUT, &ioParams, &eb);

    if ((NULL == uartMasterRxHandle) || (NULL == uartMasterTxHandle))
    {
        System_abort("\nStream creation failed\n");
    }
    else
    {
        /* Run the uart main application                                    */
    	UartMasterProcess();

    }
}

/*
 * UART1 init function called when creating the driver.
 */
void uartMaster_init(void)
{
    Uart_init();

    uartMasterParams = Uart_PARAMS;
    uartMasterParams.opMode = Uart_OpMode_POLLED;
    uartMasterParams.baudRate = Uart_BaudRate_9_6K;
    uartMasterParams.hwiNumber = 8;
    uartMasterParams.rxThreshold = Uart_RxTrigLvl_1;
    uartMasterParams.softTxFifoThreshold = 1;
    uartMasterParams.stopBits = Uart_NumStopBits_2;
    uartMasterParams.parity = Uart_Parity_NONE;
	//uartMasterParams.polledModeTimeout = 1000000; //for timeout wait input data

}
