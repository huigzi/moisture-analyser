/******************************************************************
 	Timer_drv.h: ��ʱ����������	
 	��������OMAP-L138
******************************************************************/

#ifndef TIMER_DRV_H
#define TIMER_DRV_H

#include <type.h>

void Timer_init(void);

void Timer_delay(INT32U dlyus);

INT32U GetSysTick(void);

#endif
