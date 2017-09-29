/* BIOS6 include */
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

extern void UART1_isr(UArg arg);
extern void UART2_isr(UArg arg);

EDMA3_DRV_Handle 	hEdma;
EDMA3_DRV_Handle edma3init(unsigned int edma3Id, EDMA3_DRV_Result *);
//---------------------------------------------------------------------

//create scom for synning the tasks

void fr_ScomSetup(void)
{
    /* create all SCOM and message objects */
    SCOM_create("P2IN", NULL);
    SCOM_create("UM2P", NULL);
    SCOM_create("P2UM", NULL);
    SCOM_create("IN2SPI", NULL);
    SCOM_create("SPI2P", NULL);
    SCOM_create("T2IN", NULL);
}

static Void spiEdmaInit(Void)
{
    EDMA3_DRV_Result edmaResult = 0;

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
    return;
}

int main()
{
    configureGuaoC6748();
    SCOM_init();	//scom
    fr_ScomSetup(); //scom for gooao_c6748 tasks
    spiEdmaInit();
	BIOS_start ();	// Start the BIOS 6 Scheduler
}
