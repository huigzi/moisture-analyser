/**@file taskImageProcess.c
 *This file is a special relay for different task process.
 *@author SuWei
 */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/GIO.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <scom.h>
#include <gooao_c6748.h>
#include <cslr/cslr_gpio.h>
#include <fr_uart.h>

//#include other image process algorithms head files

extern Semaphore_Handle semIn2P;	//input->Process
extern Semaphore_Handle semP2In;

extern CSL_GpioRegsOvly     gpioRegs;

#pragma DATA_ALIGN(wbuf, 128);
#pragma DATA_ALIGN(rbuf, 128);
uint8_t wbuf[1024];
uint8_t rbuf[1024];

/** initial the scom flag*/

void tskImageProcess(void)
{
    ScomMessage *pMsgBuf;
    SCOM_Handle hs_In2Proc,hs_Proc2In;
    SCOM_Handle hs_Proc2Net,hs_Net2Proc;

    hs_In2Proc  = SCOM_open("IN2P");
    hs_Proc2In  = SCOM_open("P2IN");
    hs_Proc2Net = SCOM_open("P2NET");
    hs_Net2Proc = SCOM_open("NET2P");

    if( !hs_In2Proc || !hs_Proc2In || !hs_Proc2Net || !hs_Net2Proc)
    {
        for(;;);
    }
    while(1)
    {
        // Get Input Buffer and image buffer size
        pMsgBuf = SCOM_getMsg( hs_In2Proc, BIOS_WAIT_FOREVER );

        pMsgBuf->command = 0x020;
        pMsgBuf->integration_time_status = NO_NEED;
        pMsgBuf->extra_flag = 0;
        printf("working now...\n");

        //other process...
        SCOM_putMsg(hs_Proc2Net, pMsgBuf);
        pMsgBuf = SCOM_getMsg( hs_Net2Proc, BIOS_WAIT_FOREVER );
        // Tell the capture routine we're done
        SCOM_putMsg( hs_Proc2In, pMsgBuf );

    }

}
