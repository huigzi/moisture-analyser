#include <stdio.h>
#include <stdlib.h>
#include <gooao_c6748.h>
#include <scom.h>
#include <cslr/cslr_gpio.h>

ScomMessage timerMsg;
SCOM_Handle hs_Timer2In;
extern CSL_GpioRegsOvly     gpioRegs;
extern double ntc_for_control;
intmax_t count = 0;

void tskTimer(void)
{
	hs_Timer2In = SCOM_open("T2IN");
	if(!hs_Timer2In)
	{
		for(;;);
	}
	if(count == 0)
	{
		 CSL_FINS(gpioRegs->BANK[3].OUT_DATA,GPIO_OUT_DATA_OUT2,1);
		 CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT31,1);
	}
	if(count > 0 && ntc_for_control < -10)
	{
		 CSL_FINS(gpioRegs->BANK[3].OUT_DATA,GPIO_OUT_DATA_OUT2,1);
		 CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT31,0);
	}
	if(count > 0 && ntc_for_control >= -10)
	{
		 CSL_FINS(gpioRegs->BANK[3].OUT_DATA,GPIO_OUT_DATA_OUT2,0);
		 CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT31,0);
	}
	count++;
	if(count > 2)
		count = 0;

	SCOM_putMsg(hs_Timer2In, &timerMsg);

}

