/**@file fr_main.c
*change FPGA(for CMOS) time series.\n
*add CMOS manual total integration time control function.\n
*change the size of TCP/IP package.\n
*change the size of FIFO for network.\n
*@author SuWei
*@date 2017-4-5
*/
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/family/c64p/EventCombiner.h>

#include <interrupt.h>
#include <fr6748_Init.h>
#include <gooao_c6748.h>
#include <scom.h>
#include <fr_uart.h>
#include <cslr/cslr_gpio.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>

#define MAR192			*(unsigned int*) (0x01848300)
#define MAR193			*(unsigned int*) (0x01848304)
#define MAR194			*(unsigned int*) (0x01848308)
#define MAR195			*(unsigned int*) (0x0184830C)
#define MAR196			*(unsigned int*) (0x01848310)
#define MAR197			*(unsigned int*) (0x01848314)
#define MAR198			*(unsigned int*) (0x01848318)
#define MAR199			*(unsigned int*) (0x0184831C)

Hwi_Handle HwiUart1,HwiUart2;

//---------------------------------------------------------------------

//create scom for synning the tasks

void fr_ScomSetup(void)
{
    /* create all SCOM and message objects */
    SCOM_create("P2IN", NULL);
    SCOM_create("IN2P", NULL);
    SCOM_create("P2NET", NULL);
    SCOM_create("NET2P", NULL);
}

void DDR_CACHE_OPEN(void)
{
	MAR192 |= 0x1;
	MAR193 |= 0x1;
	MAR194 |= 0x1;
	MAR195 |= 0x1;
	//MAR196 |= 0x1;
	MAR197 |= 0x1;
	MAR198 |= 0x1;
	MAR199 |= 0x1;
}

int main()

{
    configureGuaoC6748();
    SCOM_init();	//scom
    fr_ScomSetup(); //scom for gooao_c6748 task
    DDR_CACHE_OPEN();
	BIOS_start ();	// Start the BIOS 6 Scheduler
}
