/**@file fr_main.c
*change FPGA(for CMOS) time series.\n
*add CMOS manual total integration time control function.\n
*change the size of TCP/IP package.\n
*change the size of FIFO for network.\n
*add UART1 thread.\n
*2016-6-27 change communication channels between UART and NET, this made UART is a part of NET process.\n
*2016-6-28 change TAU's initialization sets. select FFC mode extern model. select Gain mode Low_Level Only.\n
*2016-9-8  change FPGA program, adding XP mode for the same size of picture in different channel.(not used)\n
*The pictures from UPP are in different size now(720*480).\n
*2016-9-28 For single-channel used. Wang May adds algorithm. 485 Thread needed. NET thread may also need changed\n
*2016-12-24 UART model  changed.  POLLED_interrupt MODEL now.\n
*@author SuWei
*/

#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/family/c64p/EventCombiner.h>

#include <interrupt.h>
#include <guao6748_Init.h>
#include <gooao_c6748.h>
#include <scom.h>

/**create all SCOM and message objects
 * scom for gooao_c6748 tasks
 */
void fr_ScomSetup(void)
{
    SCOM_create("IN2P", NULL);
    SCOM_create("P2IN", NULL);
    SCOM_create("P2NET", NULL);
    SCOM_create("NET2P", NULL);
    SCOM_create("UM2NET", NULL);
    SCOM_create("NET2UM", NULL);
}

/**initial configuration. then
 *DSP start the BIOS6 Scheduler
 *@par example
 *@code
 BIOS_start ();
 *@endcode
 */
int main()
{
    configureGuaoC6748();
    SCOM_init();
    fr_ScomSetup();
	BIOS_start ();
}

