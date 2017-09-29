#ifndef EVMC6748_RTC_H
#define EVMC6748_RTC_H

// bitmask defines for KICK.
#define RTCKICK0_UNLOCK       (0x83E70B13)
#define RTCKICK1_UNLOCK       (0x95A4F1E0)
#define RTCKICK0_LOCK         (0xFFFFFFFF)
#define RTCKICK1_LOCK         (0xFFFFFFFF)

//-----------------------------------------------------------------------------
// Public Typedefs
//-----------------------------------------------------------------------------
typedef struct
{
   Uint8 sec;
   Uint8 min;
   Uint8 hour;
   Uint8 day;
   Uint8 month;
   Uint8 year;
   Uint8 dayofweek;
} rtc_time_t;

//-----------------------------------------------------------------------------
// Public Function Prototypes
//-----------------------------------------------------------------------------

void RTC_init(void);
void RTC_getTime(rtc_time_t *time);
void RTC_setTime(rtc_time_t *in_time);
void RTC_getTimeBCD(rtc_time_t *time);

#endif

