/**
 * \file    fr_uart.c
 *
 * \brief   This file contains the flir tau640 scom
 * \author  zzw
 *
 * \version 0.1   created for the C6748 platforms
 */
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/GIO.h>
#include <xdc/runtime/log.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>

#include <Psc.h>
#include <Uart.h>
#include <UartLocal.h>
#include <guao6748_Init.h>

/* ========================================================================== */
/*                            EXTERNAL REFERENCES                             */
/* ========================================================================== */

Void flir_tau_config(Void);
EDMA3_DRV_Handle edma3init(unsigned int edma3Id, EDMA3_DRV_Result *);

/* ========================================================================== */
/*                             MACRO DEFINITIONS                              */
/* ========================================================================== */

/* ========================================================================== */
/*                           LOCAL FUNCTION PROTOTYPES                        */
/* ========================================================================== */

static Void uartEdmaInit(Void);

/* ========================================================================== */
/*                             GLOBAL VARIABLES                               */
/* ========================================================================== */
/* Handle to the EDMA driver instance                                         */
EDMA3_DRV_Handle hEdma;

/* UART handle for input stream                                               */
GIO_Handle uartRxHandle;

/* UART handle for output stream                                              */
GIO_Handle uartTxHandle;

Uart_Params   uartParams;

/* Global function prototypes */
void user_uart_init(void);

/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */
unsigned short do_crc1021(unsigned char *message, unsigned int len)
{
    int i, j;
    unsigned short crc_reg = 0;
    unsigned short current;

    for (i = 0; i < len; i++)
    {
        current = message[i] << 8;
        for (j = 0; j < 8; j++)
        {
            if ((short)(crc_reg ^ current) < 0)
                crc_reg = (crc_reg << 1) ^ 0x1021;
            else
                crc_reg <<= 1;
            current <<= 1;
        }
    }
    return crc_reg;
}

/**
 * \brief      Entry point for the main task. This creates the required channels
 *             and calls the required functions for demonstrating the UART
 *             driver
 *
 * \param      arg1  [IN]   unused
 * \param      arg2  [IN]   unused
 *
 * \return     None
 */
Void uart2_process(void)
{
    Uart_ChanParams    	chanParams;
	Error_Block 		eb;
 	GIO_Params 			ioParams;

    Error_init(&eb);

    /*
     * Initialize channel attributes.
     */
    GIO_Params_init(&ioParams);
    /* initialise the edma library and get the EDMA handle                    */
    uartEdmaInit();

    /* update the edma Handle                                                 */
    chanParams.hEdma = hEdma;
    ioParams.chanParams = (Ptr)&chanParams;

   	/* create the required streams for the UART demo                           */
    uartTxHandle = GIO_create("/uart2", GIO_OUTPUT, &ioParams, &eb);
    uartRxHandle = GIO_create("/uart2",GIO_INPUT, &ioParams, &eb);

    if ((NULL == uartRxHandle) || (NULL == uartTxHandle))
    {
        System_printf("\nStream creation failed\n");
    }
    else
    {
        /* Run the uart sample application                                    */
        flir_tau_config();
    }
}

/**
 * \brief      Function to initialize the edma driver and get the handle to the
 *             edma driver;
 *
 * \param      arg1  [IN]   unused
 * \param      arg2  [IN]   unused
 *
 * \return     None
 */
static Void uartEdmaInit(Void)
{
    EDMA3_DRV_Result    edmaResult      = 0;

    hEdma = edma3init(0, &edmaResult);

    if (edmaResult != EDMA3_DRV_SOK)
    {
        /* Report EDMA Error */
        System_printf("\nEDMA driver initialization FAIL\n");
    }
    else
    {
        System_printf("\nEDMA driver initialization PASS.\n");
    }
}

/*
 * UART2 init function called when creating the driver.
 */
void user_uart_init()
{
    //Uart_init();

    uartParams = Uart_PARAMS;
	uartParams.opMode = Uart_OpMode_POLLED;
	uartParams.baudRate = Uart_BaudRate_57_6K;	//Uart_BaudRate_115_2K;
	uartParams.hwiNumber = 9;
	uartParams.rxThreshold = Uart_RxTrigLvl_1;
	uartParams.softTxFifoThreshold = 1;

	if(Uart_OpMode_POLLED == uartParams.opMode)
	{
		System_printf("\r\nUart is configured in polled mode");
	}
	else if (Uart_OpMode_INTERRUPT == uartParams.opMode)
	{
		System_printf("\r\nUart is configured in interrupt mode");
	}
	else if (Uart_OpMode_DMAINTERRUPT == uartParams.opMode)
	{
		System_printf("\r\nUart is configured in dma mode");
	}
	else
	{
		System_printf("\r\nError: Unknown mode of operation!!!!!!!!!!");
	}
}
//------------------------------------------------------------------------
Void flir_tau_config(Void)
{
    size_t    len     =  0;
    char     sendBuf[64];
    char     RecvBuf[64];
    Int		  status  =  IOM_COMPLETED;
    unsigned short crc_init,crc_val;
    int i;

    //set the dynamic-range-control mode
    sendBuf[0]= 0x6E;
    sendBuf[1]= 0x00;	//status
    sendBuf[2]= 0x00;	//reserve
    sendBuf[3]= 0x0A;	//function ID GAIN_MODE
    sendBuf[4]= 0x00;	//byte count MSB
    sendBuf[5]= 0x02;	//byte count LSB
    len = 6;
    crc_val = do_crc1021(sendBuf, len);
    sendBuf[6]= (crc_val>>8) & 0xFF;	//CRC1 MSB
    sendBuf[7]= crc_val & 0xFF;	//CRC1 LSB
    sendBuf[8]= 0x00;	//parameter MSB
    sendBuf[9]= 0x01;	//parameter LSB Low Gain Only
    len = 10;
    crc_val = do_crc1021(sendBuf, len);
    sendBuf[10]= (crc_val>>8) & 0xFF;	//CRC2 MSB
    sendBuf[11]= crc_val & 0xFF;	//CRC2 LSB

    len = 12;
    status = GIO_write(uartTxHandle,sendBuf,&len);
    if (IOM_COMPLETED != status)
    {
    	System_printf("\r\nGIO_write failed. returned : %d", status);
    }

    len = 10;
    status = GIO_read(uartRxHandle,&RecvBuf,&len);
    if (IOM_COMPLETED != status)
    {
    	System_printf("\r\nGIO_read failed. returned : %d", status);
    }

    //set Flat Field Correction (FFC)
    sendBuf[0]= 0x6E;
    sendBuf[1]= 0x00;	//status
    sendBuf[2]= 0x00;	//reserve
    sendBuf[3]= 0x0B;	//function ID FFC_MODE
    sendBuf[4]= 0x00;	//byte count MSB
    sendBuf[5]= 0x02;	//byte count LSB
    len = 6;
    crc_val = do_crc1021(sendBuf, len);
    sendBuf[6]= (crc_val>>8) & 0xFF;	//CRC1 MSB
    sendBuf[7]= crc_val & 0xFF;	//CRC1 LSB
    sendBuf[8]= 0x00;	//parameter MSB
    sendBuf[9]= 0x02;	//parameter LSB External mode
    len = 10;
    crc_val = do_crc1021(sendBuf, len);
    sendBuf[10]= (crc_val>>8) & 0xFF;	//CRC2 MSB
    sendBuf[11]= crc_val & 0xFF;	//CRC2 LSB

    len = 12;
    status = GIO_write(uartTxHandle,sendBuf,&len);
    if (IOM_COMPLETED != status)
    {
        System_printf("\r\nGIO_write failed. returned : %d", status);
    }

    len = 10;
    status = GIO_read(uartRxHandle,&RecvBuf,&len);
    if (IOM_COMPLETED != status)
    {
        System_printf("\r\nGIO_read failed. returned : %d", status);
    }

	//set lvds data out mode-------------------------------------------------
    sendBuf[0]= 0x6E;
	sendBuf[1]= 0x00;	//status
	sendBuf[2]= 0x00;	//reserve
	sendBuf[3]= 0x12;	//function ID DIGITAL_OUTPUT_MODE
	sendBuf[4]= 0x00;	//byte count MSB
	sendBuf[5]= 0x02;	//byte count LSB
	len = 6;
	crc_val = do_crc1021(sendBuf, len);
	sendBuf[6]= (crc_val>>8) & 0xFF;	//CRC1 MSB
	sendBuf[7]= crc_val & 0xFF;	//CRC1 LSB
	sendBuf[8]= 0x07;	//parameter MSB
	sendBuf[9]= 0x00;	//parameter LSB SET LVDS BIT DEPTH 14bits
	len = 10;
	crc_val = do_crc1021(sendBuf, len);
	sendBuf[10]= (crc_val>>8) & 0xFF;	//CRC2 MSB
	sendBuf[11]= crc_val & 0xFF;	//CRC2 LSB

	len = 12;
	status = GIO_write(uartTxHandle,sendBuf,&len);
	if (IOM_COMPLETED != status)
	{
		System_printf("\r\nGIO_write failed. returned : %d", status);
	}

	len = 10;
	status = GIO_read(uartRxHandle,&RecvBuf,&len);
	if (IOM_COMPLETED != status)
	{
		System_printf("\r\nGIO_read failed. returned : %d", status);
	}


    //ext sync ---------------------------------------------------------------
//    	sendBuf[0]= 0x6E;
//    	sendBuf[1]= 0x00;	//status
//    	sendBuf[2]= 0x00;	//reserve
//    	sendBuf[3]= 0x21;	//function ID	EXTERNAL_SYNC
//    	sendBuf[4]= 0x00;	//byte count MSB
//    	sendBuf[5]= 0x02;	//byte count LSB
//    	len = 6;
//    	crc_val = do_crc1021(sendBuf, len);
//    	sendBuf[6]= (crc_val>>8) & 0xFF;	//CRC1 MSB
//    	sendBuf[7]= crc_val & 0xFF;	//CRC1 LSB
//    	sendBuf[8]= 0x00;	//parameter MSB
//    	sendBuf[9]= 0x02;	//parameter LSB	set as master
//    	len = 10;
//    	crc_val = do_crc1021(sendBuf, len);
//    	sendBuf[10]= (crc_val>>8) & 0xFF;	//CRC2 MSB
//    	sendBuf[11]= crc_val & 0xFF;	//CRC2 LSB
//
//    	len = 12;
//    	status = GIO_write(uartTxHandle,sendBuf,&len);
//    	if (IOM_COMPLETED != status)
//    	{
//    		System_printf("\r\nGIO_write failed. returned : %d", status);
//    	}
//
//    	len = 12;
//    	status = GIO_read(uartRxHandle,&RecvBuf,&len);
//    	if (IOM_COMPLETED != status)
//    	{
//    		 System_printf("\r\nGIO_read failed. returned : %d", status);
//    	}
}

/* ========================================================================== */
/*                              END OF FILE                                   */
/* ========================================================================== */
