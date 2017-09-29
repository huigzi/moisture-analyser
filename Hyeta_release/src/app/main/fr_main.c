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

int main()

{
    configureGuaoC6748();
    SCOM_init();	//scom
    fr_ScomSetup(); //scom for gooao_c6748 task
	BIOS_start ();	// Start the BIOS 6 Scheduler
}
