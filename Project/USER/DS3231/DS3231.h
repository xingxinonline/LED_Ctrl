#include "sys.h"
#ifndef __DS3231_H__
#define __DS3231_H__


typedef struct 
{
	u8 hour;
	u8 min;
	u8 sec;			
	u8 w_year;
	u8  w_month;
	u8  w_date;
	u8  week;		 
}_calendar_obj;	
typedef struct 
{
	u8 no;
	u8 time_power_buf[12];
}Time_Power_TypeDef;	

extern Time_Power_TypeDef Timer_Power_Struct;	//日历结构体	
extern _calendar_obj calendar;	//日历结构体

extern u8 const mon_table[12];	//月份日期数据表
u8 I2cByteRead(u8 addr);
void DS3231_Init(void);
void get_show_time(void);      
u8 RTC_Get_Week(u16 year,u8 month,u8 day);
void DS3231_Set(u8 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//设置时间	
void ReadAlarmFlag(void);
void OpenDoubleAlarm(void);
void OpenAlarm1(void);
void OpenAlarm2(void);
void CloseDoubleAlarm(void);
void CloseAlarm1(void);
void CloseAlarm2(void);
void DoubleAlarmInit(void);
void Alarm1Init(void);
void Alarm2Init(u8 type);
void ClearAlarm1Flag(void);
void ClearAlarm2Flag(void);
void SetAlarm1(unsigned char minute);
void SetAlarm2(void);
void GetDS3231Temp(u8 *addr);
#endif

