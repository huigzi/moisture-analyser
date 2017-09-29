/*@brief sync address command1 command2 checksum

*每一位均是16进制数，8bit。 第一位符号位FF 第二位地址位 logical address of the receiver device being controlled 目前因为1块板子，暂定地址为0x01 第三位command1，第四位command2均为命令位  第五位是校验位 为二到四位求和值 calculated by performing the 8 bit (modulo 256) sum of the payload bytes (bytes 2 through 4) in the message.

*command1 : 0x00分光\偏振镜片切换 0x01电机转换（天空\黑体测量切换） 0x02温度测量

*command2: 当进行分光\偏振镜片切换时 0x01 0x02 0x03对应3种不同的镜片 0x04为无镜片位置；
	  当进行天空\黑体测量切换时 0x01 黑体测量位置 0x02 天空测量位置；
	  当进行温度测量时 为0x00。

*查询回复格式

*sync opcode data1 data2 checksum

*sync =0xff

*opcode 当command1 = 0x00 时 为0x50；
       当command1 = 0x01 时 为0x51;
       当command1 = 0x02 时 为0x52;

*data1 data2在进行位置转换命令时均为0x00 在进行温度测量时传输温度数据

*checksum为之前接收到的指令的校验码+opcode
*@author SUWEI*/

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/GIO.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/task.h>
#include <scom.h>
#include <Uart.h>
#include <UartLocal.h>
#include <gooao_c6748.h>
#include <cslr/cslr_gpio.h>

GIO_Handle uartMaster1RxHandle;
GIO_Handle uartMaster1TxHandle;
Uart_Params   uartMaster1Params;

void uartMaster_init(void);

uint8_t command_switchfilter[4][5] = {{0xFF, 0x01, 0x00, 0x01, 0x02},
												  {0xFF, 0x01, 0x00, 0x02, 0x03},
												  {0xFF, 0x01, 0x00, 0x03, 0x04},
												  {0xFF, 0x01, 0x00, 0x04, 0x05}};
uint8_t command_switchposition[2][5]= {{0xFF, 0x01, 0x03, 0x03, 0x07},
												   {0xFF, 0x01, 0x01, 0x02, 0x04}};
uint8_t command_quary[2][5] = {{0xFF, 0x01, 0x02, 0x00, 0x03},
										   {0xFF, 0x01, 0x02, 0x01, 0x04}};
uint8_t command_heat[2][5] = {{0xFF, 0x01, 0x05, 0x01, 0x07},
											{0xFF, 0x01, 0x05, 0x00, 0x06}};
uint8_t uart1_recvBuffer[5] = {0};
uint8_t *temp_command;

Void UartMasterProcess(Void)
{
    size_t    len     =  0;
    Int		  status  =  IOM_COMPLETED;
    uint8_t command;

    ScomMessage *uartMsg;
    SCOM_Handle hs_Net2UM,hs_UM2Net;

    hs_Net2UM = SCOM_open("NET2UM");
    hs_UM2Net = SCOM_open("UM2NET");

    if(!hs_Net2UM || !hs_UM2Net )
    {
    	for(;;);
    }

    len = (unsigned int) 5;

    while(1)
    {
    	uartMsg = SCOM_getMsg(hs_Net2UM, BIOS_WAIT_FOREVER);

    	command = uartMsg->command;

    	switch(command)
    	{
    		case 0x00:
    			temp_command = command_switchfilter[0];
    			status = GIO_write(uartMaster1TxHandle,temp_command,&len);

    			if (IOM_COMPLETED != status)
    			{
    				System_printf("\r\nGIO_write faile = d. returned : %d", status);
    			}

    			status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			if(uart1_recvBuffer[1] != 0x50 || uart1_recvBuffer[4] != 0x52)
    			{
    				status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			}
    			break;
    		case 0x01:
    			temp_command = command_switchfilter[1];
    			status = GIO_write(uartMaster1TxHandle,temp_command,&len);

    			if (IOM_COMPLETED != status)
    			{
    			    System_printf("\r\nGIO_write faile = d. returned : %d", status);
    			}

    			status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			if(uart1_recvBuffer[1] != 0x50 || uart1_recvBuffer[4] != 0x53)
    			{
    				status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			}
    			break;
    		case 0x02:
    			temp_command = command_switchfilter[2];
    			status = GIO_write(uartMaster1TxHandle,temp_command,&len);

    			if (IOM_COMPLETED != status)
    			{
    			    System_printf("\r\nGIO_write faile = d. returned : %d", status);
    			}

    			status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			if(uart1_recvBuffer[1] != 0x50 || uart1_recvBuffer[4] != 0x54)
    			{
    				status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			}
    			break;
    		case 0x03:
    			temp_command = command_switchfilter[3];
    			status = GIO_write(uartMaster1TxHandle,temp_command,&len);

    			if (IOM_COMPLETED != status)
    			{
    				System_printf("\r\nGIO_write faile = d. returned : %d", status);
    			}

    			status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			if(uart1_recvBuffer[1] != 0x50 || uart1_recvBuffer[4] != 0x55)
    			{
    				status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			}
    			break;
    		case 0x04:
    			temp_command = command_switchposition[0];
    			status = GIO_write(uartMaster1TxHandle,temp_command,&len);

    			if (IOM_COMPLETED != status)
    			{
    			    System_printf("\r\nGIO_write faile = d. returned : %d", status);
    			}

    			status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			while(uart1_recvBuffer[1] != 0x51)
    				status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			break;
    		case 0x05:
    			temp_command =  command_heat[0];
    			status = GIO_write(uartMaster1TxHandle,temp_command,&len);

    			if (IOM_COMPLETED != status)
    			{
    			    System_printf("\r\nGIO_write faile = d. returned : %d", status);
    			}

    			status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    		    while(uart1_recvBuffer[1] != 0x55 || uart1_recvBuffer[3] != 0x01)
    		    	status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			break;
    		case 0x06:
    			temp_command = command_quary[0];
    			status = GIO_write(uartMaster1TxHandle,temp_command,&len);

    			if (IOM_COMPLETED != status)
    			{
    			    System_printf("\r\nGIO_write faile = d. returned : %d", status);
    			}

    			status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			while(uart1_recvBuffer[1] != 0x52)
    				status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			break;
    		case 0x07:
    			temp_command =  command_heat[1];
    			status = GIO_write(uartMaster1TxHandle,temp_command,&len);

    			if (IOM_COMPLETED != status)
    			{
    			    System_printf("\r\nGIO_write faile = d. returned : %d", status);
    			}

    			status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			while(uart1_recvBuffer[1] != 0x55 || uart1_recvBuffer[3] != 0x00)
    				status = GIO_read(uartMaster1RxHandle,&uart1_recvBuffer,&len);
    			break;
    		default:
    			break;
    	}
        uartMsg->extra_flag = 1;
		SCOM_putMsg(hs_UM2Net, uartMsg);
    }
}

Void tskUartMaster(UArg arg1, UArg arg2)
{
    Uart_ChanParams    	chanParams;
	Error_Block 		eb;
 	GIO_Params 			ioParams;

    Error_init(&eb);

    GIO_Params_init(&ioParams);//Initialize channel attributes.
    ioParams.chanParams = (Ptr)&chanParams;

   	/* create the required streams for the UART demo                           */
    uartMaster1TxHandle = GIO_create("/uart1", GIO_OUTPUT, &ioParams, &eb);
    uartMaster1RxHandle = GIO_create("/uart1",GIO_INPUT, &ioParams, &eb);

    if ((NULL == uartMaster1RxHandle) || (NULL == uartMaster1TxHandle))
    {
        System_printf("\nStream creation failed\n");
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
void uartMaster_init()
{
    Uart_init();

    uartMaster1Params = Uart_PARAMS;
    //uartMaster1Params.opMode = Uart_OpMode_POLLED;
    uartMaster1Params.opMode =  Uart_OpMode_INTERRUPT;
    uartMaster1Params.baudRate = Uart_BaudRate_9_6K;
    uartMaster1Params.hwiNumber = 8;
    uartMaster1Params.rxThreshold = Uart_RxTrigLvl_1;
    uartMaster1Params.softTxFifoThreshold = 1;
    uartMaster1Params.stopBits = Uart_NumStopBits_2;
	uartMaster1Params.polledModeTimeout = 1000000; //for timeout wait input data
    if(Uart_OpMode_POLLED == uartMaster1Params.opMode)
    {
    	System_printf("\r\nUart is configured in polled mode");
    }
    else if (Uart_OpMode_INTERRUPT == uartMaster1Params.opMode)
    {
    	System_printf("\r\nUart is configured in interrupt mode");
    }
    else if (Uart_OpMode_DMAINTERRUPT == uartMaster1Params.opMode)
    {
    	System_printf("\r\nUart is configured in dma mode");
    }
    else
    {
    	System_printf("\r\nError: Unknown mode of operation!!!!!!!!!!");
   	}

}
