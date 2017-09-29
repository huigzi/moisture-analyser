/* BIOS6 include */
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/task.h>
#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/family/c64p/EventCombiner.h>

#include <cslr/cslr.h>
#include <cslr/cslr_uart.h>
#include <interrupt.h>
#include <fr_uart.h>
#include <cslr/soc_C6748.h>
#include <hw_soc_C6748.h>

CSL_UartRegsOvly uartRegs1 = (CSL_UartRegsOvly)CSL_UART_1_REGS;
CSL_UartRegsOvly uartRegs2 = (CSL_UartRegsOvly)CSL_UART_2_REGS;
//---------------------------------------------------------------------
#define UART1_CmdSize 2
#define UART1_CmdBufSize 10
int 	c018_flag=0;
int UART1_CmdStartChar_flag=0;
int UART1_CmdReady_Flag=0;
int UART1_CmdCount=0;
unsigned char  UART1_Cmdbuf[UART1_CmdBufSize];
unsigned char	 tuichao1='A',tuichao2='1',zhukong1,zhukong2;

#define UART2_CmdSize 2
#define UART2_CmdBufSize 10
 char send_cSN[20];
int UART2_CmdStartChar_flag=0;
int UART2_CmdReady_Flag=0;
int UART2_CmdCount=0;
unsigned char UART2_Cmdbuf[UART2_CmdBufSize];

//create semaphores for synning the tasks
unsigned char UART1_Cmdbuf_tim[20];
int UART1_CmdReady_Flag_tim=0;
unsigned char Uart_Recv_Data;

//
void UART1_isr(UArg arg)
{
	/*
	unsigned char UART1_RecChar;
	//UART1_RecChar = CSL_FEXT(uartRegs1->RBR,UART_RBR_DATA);
	while(CSL_FEXT(uartRegs1->LSR,UART_LSR_DR)==1)
	{
		UART1_RecChar=CSL_FEXT(uartRegs1->RBR,UART_RBR_DATA);
		Uart_Recv_Data = UART1_RecChar;

		//=======================================================
		if (UART1_CmdStartChar_flag==0)
		{
			if ((UART1_RecChar==0x10)||
					(UART1_RecChar==0x11)||
					(UART1_RecChar==0x12)||
					(UART1_RecChar==0x20)||
					(UART1_RecChar==0x21)||
					(UART1_RecChar==0x2D)||
					(UART1_RecChar==0x2E)||
					(UART1_RecChar==0x30)||
					(UART1_RecChar==0x40)||
					(UART1_RecChar==0x50)||
					(UART1_RecChar==0x53)||
					(UART1_RecChar==0x60)||
					(UART1_RecChar==0x65)||
					(UART1_RecChar==0x61)||
					(UART1_RecChar==0x62)||
					(UART1_RecChar>=0xc0)||
				//(UART1_RecChar==0x55)||  //ceshi
					(UART1_RecChar==0x80)||
					(UART1_RecChar==0xA0)||
//					(UART1_RecChar==0x0E)||
					(UART1_RecChar==0xAA)
				 )
				{
					memset(UART1_Cmdbuf,0,sizeof(UART1_Cmdbuf));
					UART1_CmdStartChar_flag=1;
					UART1_Cmdbuf[0]=UART1_RecChar;
					UART1_CmdCount=0;
					UART1_CmdReady_Flag=0;
					if(UART1_Cmdbuf[0]==0x65)//----------------------
					{
						UART1_CmdReady_Flag_tim=0;//----------------------------
					}
				}
		}
		else if(UART1_CmdStartChar_flag==1)
		{
			if(UART1_CmdReady_Flag!=1)
			{
				UART1_CmdCount++;
				UART1_Cmdbuf[UART1_CmdCount]=UART1_RecChar;

				if (UART1_CmdCount>=(UART1_CmdSize-1))
				{
					UART1_CmdReady_Flag=1;
				}
			}
			else if(UART1_CmdReady_Flag_tim!=1)
			{
			}
		}
	}

	//Hwi_clearInterrupt(5); //ICR = 0x0020;
	*/
}

unsigned char Uart_Recv_Data2;

void UART2_isr(UArg arg)
{

	//int i;
	unsigned char UART2_RecChar;

	UARTIntDisable(UART2, UART_INT_RXDATA_CTI);
	//UART2_RecChar = CSL_FEXT(uartRegs2->RBR,UART_RBR_DATA);
	while(CSL_FEXT(uartRegs2->LSR,UART_LSR_DR)==1)
	{
		UART2_RecChar=CSL_FEXT(uartRegs2->RBR,UART_RBR_DATA);
	}

	UARTIntEnable(UART2, UART_INT_RXDATA_CTI);

//	EventCombiner_enableEvent(SYS_INT_UART2_INT);

/*
		Uart_Recv_Data2 = UART2_RecChar;
		//=======================================================

		if (UART2_CmdStartChar_flag==0)
		{
			if ((UART2_RecChar==0x10)||
					(UART2_RecChar==0x11)||
					(UART2_RecChar==0x12)||
					(UART2_RecChar==0x20)||
					(UART2_RecChar==0x21)||
					(UART2_RecChar==0x2D)||
					(UART2_RecChar==0x2E)||
					(UART2_RecChar==0x30)||
					(UART2_RecChar==0x40)||
					(UART2_RecChar==0x50)||
					(UART2_RecChar==0x53)||
					(UART2_RecChar==0x60)||
					(UART2_RecChar==0x65)||
					(UART2_RecChar==0x61)||
					(UART2_RecChar==0x62)||
					(UART2_RecChar>=0xc0)||
					(UART2_RecChar==0x80)||
					(UART2_RecChar==0x2E)||
					(UART2_RecChar==0x01)||
					(UART2_RecChar==0x02)||
					(UART2_RecChar==0xA0)||
					(UART2_RecChar==0x0E)||
					(UART2_RecChar==0xAA)
				 )
			{
				memset(UART2_Cmdbuf,0,sizeof(UART2_Cmdbuf));
				UART2_CmdStartChar_flag=1;
				UART2_Cmdbuf[0]=UART2_RecChar;
				UART2_CmdCount=0;
			}
		}
		else if(UART2_CmdStartChar_flag==1)
		{
			if(UART2_CmdReady_Flag!=1)
			{
				UART2_CmdCount++;
				UART2_Cmdbuf[UART2_CmdCount]=UART2_RecChar;

				if (UART2_CmdCount>=(UART2_CmdSize-1))
				{
					UART2_CmdReady_Flag=1;
				}
			}
		}
	}
	//Hwi_clearInterrupt(6); //ICR = 0x0040;
*/

}
