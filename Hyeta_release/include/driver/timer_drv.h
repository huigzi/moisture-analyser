/******************************************************************
 	Timer_drv.h: 定时器驱动程序	
 	控制器：OMAP-L138
******************************************************************/

#ifndef TIMER_DRV_H
#define TIMER_DRV_H

#include <type.h>

void Timer_init(void);

void Timer_delay(INT32U dlyus);

INT32U GetSysTick(void);

#endif
