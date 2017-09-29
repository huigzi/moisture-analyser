/**
 * \file   delay.c
 *
 * \brief  Delay routines
 */

/*
* Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/timers/timer64/Timer.h>
#include <ti/sysbios/knl/Semaphore.h>
/*
#include "interrupt.h"
#include "soc_C6748.h"
#include "hw_syscfg0_C6748.h"
#include "hw_types.h"
#include "timer.h"
#include "evmC6748.h"*/

#include "delay.h"

static volatile unsigned int flagIsrCnt = 1;

Timer_Handle USBOTG_Timer;
Semaphore_Handle USBOTGTimeout2Sysdelay;

/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
*******************************************************************************/
#define TMR_PERIOD_LSB32              0x5DC0
#define TMR_PERIOD_MSB32              0x0
#define TIMER_DIV       (12)	//预分频次数
#define TICKS_PER_US    (2)		//预分频后的时钟源=1us/2=500ns(24.5760M晶体)

void USBOTGTimerISR()
{
	flagIsrCnt =0;
	Semaphore_post(USBOTGTimeout2Sysdelay);
}

void SysDelayTimerSetup(void)
{    
   	Timer_Params timerParams;
   	Error_Block eb;

   	Semaphore_Params semParam;

    Error_init(&eb);
	Semaphore_Params_init(&semParam);
	semParam.mode = ti_sysbios_knl_Semaphore_Mode_BINARY;
	USBOTGTimeout2Sysdelay = Semaphore_create(0,&semParam,&eb);

   	Error_init(&eb);
   	Timer_Params_init(&timerParams);
   	timerParams.period = Timer_MAX_PERIOD ;
   	timerParams.periodType = Timer_PeriodType_COUNTS;	//Timer_PeriodType_MICROSECS;
   	timerParams.arg = 0;
   	timerParams.prescalar = TIMER_DIV - 1;
   	timerParams.half = Timer_Half_LOWER;	//UPPER;
   	timerParams.runMode = Timer_RunMode_ONESHOT;
   	timerParams.startMode = Timer_StartMode_USER;
   	//timerParams.Timer_Mode = Timer_Mode_UNCHAINED;
   	USBOTG_Timer = Timer_create(Timer_ANY , USBOTGTimerISR, &timerParams, &eb);
   	if (USBOTG_Timer == NULL) {
   	System_abort("Timer create failed");
   	}
   
}


void Sysdelay(unsigned int milliSec)
{
	//unsigned int hwi_key;

	//hwi_key = Hwi_disable();
	Timer_setPeriod(USBOTG_Timer,milliSec);
	Timer_start(USBOTG_Timer);
	//Hwi_restore(hwi_key);
	Semaphore_pend(USBOTGTimeout2Sysdelay,BIOS_WAIT_FOREVER);
	flagIsrCnt =1;
	Timer_stop(USBOTG_Timer);
}

/**
 * /brief This function starts the timer.
 *
 * /milliSec Maximum value = TIMER_OVERFLOW/TIMER_1MS_COUNT.
 *
 * /NOTE  SysDelay functionality cannot be used till SysStopTimer is called.
 */
void SysStartTimer(unsigned int milliSec)
{
	Timer_setPeriod(USBOTG_Timer,milliSec);
	Timer_start(USBOTG_Timer);
}

/**
 * This function stops the timer.
 */
void SysStopTimer(void)
{
	flagIsrCnt =1;
	Timer_stop(USBOTG_Timer);
}

/**
 * This function checks whether 'count' milli secs are elapsed or not.
 * SysStartTimer has to be called prior to checking status.
 * NOTE: SysDelay functionality cannot be used till SysStopTimer is called.
 */
unsigned int SysIsTimerElapsed(void)
{
    if (flagIsrCnt)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
