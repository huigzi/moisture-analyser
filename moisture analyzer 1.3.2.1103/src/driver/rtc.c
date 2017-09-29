//-----------------------------------------------------------------------------
// \file    evmc6748_rtc.c
// \brief   implementation of a rtc driver for C6748.
//
//-----------------------------------------------------------------------------

#include <xdc/std.h>
#include <cslr/cslr_rtc.h>
#include <cslr/evmc6748_rtc.h>
#include <cslr/soc_C6748.h>

//-----------------------------------------------------------------------------
// Static Variable Declarations
//-----------------------------------------------------------------------------
// set RTC time flage
unsigned char TimeSetFlage = 0x00;
CSL_RtcRegsOvly sysRtcRegs = (CSL_RtcRegsOvly)CSL_RTC_0_REGS;

//-----------------------------------------------------------------------------
void RTC_init(void)
{
	uint32_t wait_reset;

   // unlock the rtc regs.
	sysRtcRegs->KICK0 = RTCKICK0_UNLOCK;
	sysRtcRegs->KICK1 = RTCKICK1_UNLOCK;
   
	// Set software reset on RTC module
	sysRtcRegs->OSC |= 0x20;
	for(wait_reset=0;wait_reset<10000;wait_reset++); // Random loop value -- adjust as necessary 

   // init time...12:00:00 Sunday January 1.
	sysRtcRegs->SECOND = 0x00;
	sysRtcRegs->MINUTE = 0x00;
	sysRtcRegs->HOUR = 0x12;
	sysRtcRegs->DAY = 0x01;
	sysRtcRegs->MONTH = 0x01;
	sysRtcRegs->YEAR = 0x01;
	sysRtcRegs->DOTW = 0x00;
   
   // set the rtc to run.
   CSL_FINST(sysRtcRegs->CTRL,RTC_CTRL_RUN,RUN);
   // lock the rtc regs.
//    sysRtcRegs->KICK0 = RTCKICK0_LOCK;
//    sysRtcRegs->KICK1 = RTCKICK1_LOCK;

}

/*********************************************************************
	BCDFormat
*********************************************************************/
Uint8 BCDFormat(Uint8 var,Uint8 lmax,Uint8 lmin)
{
	if(((var>>4)>9)||((var&0x0f)>9))
		return lmin;
	if((var>lmax)||(var<lmin))
		return lmin;
	return var;
}

//-----------------------------------------------------------------------------
void RTC_getTimeBCD(rtc_time_t *time)
{
	// wait for rtc to not be busy.
	while (CSL_FEXT (sysRtcRegs->STATUS,RTC_STATUS_BUSY)){}
	// get the time.
	time->sec = (uint8_t)sysRtcRegs->SECOND;
	time->min = (uint8_t)sysRtcRegs->MINUTE;
	time->hour = (uint8_t)sysRtcRegs->HOUR;
	time->day = (uint8_t)sysRtcRegs->DAY;
	time->month = (uint8_t)sysRtcRegs->MONTH;
	time->year = (uint8_t)sysRtcRegs->YEAR;
	time->dayofweek = (uint8_t)sysRtcRegs->DOTW;

	time->sec = BCDFormat(time->sec,0x59,0x00);
	time->min = BCDFormat(time->min,0x59,0x00);
	time->hour= BCDFormat(time->hour,0x23,0x00);
	time->day = BCDFormat(time->day,0x31,0x01);
	time->month=BCDFormat(time->month,0x12,0x01);
	time->year =BCDFormat(time->year,0x30,0x12);

}
//-----------------------------------------------------------------------------
void RTC_getTime(rtc_time_t *time)
{
	// wait for rtc to not be busy.
	while (CSL_FEXT (sysRtcRegs->STATUS,RTC_STATUS_BUSY)){}
	// get the time.
	time->sec = (uint8_t)sysRtcRegs->SECOND;
	time->min = (uint8_t)sysRtcRegs->MINUTE;
	time->hour = (uint8_t)sysRtcRegs->HOUR;
	time->day = (uint8_t)sysRtcRegs->DAY;
	time->month = (uint8_t)sysRtcRegs->MONTH;
	time->year = (uint8_t)sysRtcRegs->YEAR;
	time->dayofweek = (uint8_t)sysRtcRegs->DOTW;
}

//-----------------------------------------------------------------------------
void RTC_setTime(rtc_time_t *in_time)
{
   // wait for rtc to not be busy.
	while (CSL_FEXT (sysRtcRegs->STATUS,RTC_STATUS_BUSY)){}

   // set time to input.
   sysRtcRegs->SECOND = in_time->sec;
   sysRtcRegs->MINUTE = in_time->min;
   sysRtcRegs->HOUR = in_time->hour;
   sysRtcRegs->DAY = in_time->day;
   sysRtcRegs->MONTH = in_time->month;
   sysRtcRegs->YEAR = in_time->year;
   sysRtcRegs->DOTW = in_time->dayofweek;
   
   TimeSetFlage = 0xFF;

}

