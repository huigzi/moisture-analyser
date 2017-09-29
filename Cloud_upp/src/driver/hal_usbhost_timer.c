/******************************************************************
 	Timer_drv.c: ��ʱ����������	
 	��������OMAP-L138
******************************************************************/

#include <timer_drv.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/timers/timer64/Timer.h>
#include <ti/sysbios/knl/Clock.h>

Timer_Handle myTimer;

//-----------------------------------------------------------------------------
#define TIMER_DIV       (12)	//Ԥ��Ƶ����
#define TICKS_PER_US    (2)		//Ԥ��Ƶ���ʱ��Դ=1us/2=500ns(24.5760M����)

/******************************************************************
		Timer_init
��������ʱ����ʼ��	
******************************************************************/
void Timer_init(void)
{
	/*
//Timer0��ʼ��
   	TMR0->TGCR = 0x00000000;
   	TMR0->TCR = 0x00000000;
   	TMR0->INTCTLSTAT = 0;
   	SETBIT(TMR0->TGCR, TIMMODE_32BIT_UNCHAINED | PRESCALER(TIMER_DIV - 1) | TIM34RS | TIM12RS);
   	TMR0->TIM34 = 0x00000000;
   	TMR0->PRD34 = 0xFFFFFFFF;
   	TMR0->TIM12 = 0x00000000;
   	TMR0->PRD12 = 2*240000;	
   	SETBIT(TMR0->TCR, ENAMODE34_CONT|ENAMODE12_CONT);

//Timer1��ʼ��
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
��������ʱ����
���룺dlyus=��ʱus��(<0x7fffffff)
�������
******************************************************************/
void Timer_delay(INT32U dlyus)
{
/*
	INT32U tick0,tick;
	tick0 = Timer_getCount(myTimer);
	if(tick0==0) Timer_start(myTimer);
		//SETBIT(TMR0->TCR, ENAMODE34_CONT);
   	//�ȴ�
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
   	//�ȴ�
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
��������ϵͳ����ֵ
���أ���ǰֵ(��λ��500us)
*******************************************************************/
INT32U GetSysTick(void)
{
	//return (Timer_getCount(myTimer)/12);	//
	return (Clock_getTicks()*2);
	//return (TMR0->TIM34/1000);
}







