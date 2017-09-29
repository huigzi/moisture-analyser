/******************************************************************
 	Timer_drv.c: 定时器驱动程序	
 	控制器：OMAP-L138
******************************************************************/

#include <timer_drv.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/timers/timer64/Timer.h>
#include <ti/sysbios/knl/Clock.h>

Timer_Handle myTimer;

//-----------------------------------------------------------------------------
#define TIMER_DIV       (12)	//预分频次数
#define TICKS_PER_US    (2)		//预分频后的时钟源=1us/2=500ns(24.5760M晶体)

/******************************************************************
		Timer_init
描述：定时器初始化	
******************************************************************/
void Timer_init(void)
{
	/*
//Timer0初始化
   	TMR0->TGCR = 0x00000000;
   	TMR0->TCR = 0x00000000;
   	TMR0->INTCTLSTAT = 0;
   	SETBIT(TMR0->TGCR, TIMMODE_32BIT_UNCHAINED | PRESCALER(TIMER_DIV - 1) | TIM34RS | TIM12RS);
   	TMR0->TIM34 = 0x00000000;
   	TMR0->PRD34 = 0xFFFFFFFF;
   	TMR0->TIM12 = 0x00000000;
   	TMR0->PRD12 = 2*240000;	
   	SETBIT(TMR0->TCR, ENAMODE34_CONT|ENAMODE12_CONT);

//Timer1初始化
   	TMR1->TGCR = 0x00000000;
   	TMR1->TCR = 0x00000000;
   	TMR1->INTCTLSTAT = 0;
   	SETBIT(TMR1->TGCR, PRESCALER(TIMER_DIV - 1) | TIMMODE_32BIT_UNCHAINED | TIM34RS);
	TMR1->TIM34 = 0x00000000;
   	TMR1->PRD34 = 0xFFFFFFFF;
   	SETBIT(TMR1->TCR, ENAMODE34_CONT);
   	*/
/**/
   	Timer_Params timerParams;
   	Error_Block eb;

   	Error_init(&eb);
   	Timer_Params_init(&timerParams);
   	timerParams.period = Timer_MAX_PERIOD ;
   	timerParams.periodType = Timer_PeriodType_COUNTS;
   	timerParams.arg = 0;
   	timerParams.prescalar = TIMER_DIV - 1;
   	timerParams.half = Timer_Half_LOWER;	//UPPER;
   	timerParams.runMode = Timer_RunMode_CONTINUOUS;
   	timerParams.startMode = Timer_StartMode_AUTO;
   	//timerParams.Timer_Mode = Timer_Mode_UNCHAINED;
   	myTimer = Timer_create(2, NULL, &timerParams, &eb);
   	if (myTimer == NULL) {
   	System_abort("Timer create failed");
   	}

}
/******************************************************************
	Timer_delay
描述：延时程序
输入：dlyus=延时us数(<0x7fffffff)
输出：无
******************************************************************/
void Timer_delay(INT32U dlyus)
{
/*
	INT32U tick0,tick;
	tick0 = Timer_getCount(myTimer);
	if(tick0==0) Timer_start(myTimer);
		//SETBIT(TMR0->TCR, ENAMODE34_CONT);
   	//等待
  	while(1)
   	{
    	tick = Timer_getCount(myTimer);
		if(tick-tick0 >= dlyus*24)
			break;
   	}
*/
	Task_sleep((dlyus+1000)/1000);
/*
	INT32U tick0,tick;
	tick0 = TMR0->TIM34;
	if(tick0==0)
		SETBIT(TMR0->TCR, ENAMODE34_CONT);
   	//等待
  	while(1)
   	{
    	tick = TMR0->TIM34;
		if(tick-tick0 >= dlyus*2)
			break;
   	}
*/
}
/*******************************************************************
	GetSysTick
描述：读系统节拍值
返回：当前值(单位：500us)
*******************************************************************/
INT32U GetSysTick(void)
{
	//return (Timer_getCount(myTimer)/12);	//
	return (Clock_getTicks()*2);
	//return (TMR0->TIM34/1000);
}







