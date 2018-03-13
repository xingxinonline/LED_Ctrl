#include "sys.h"

extern RTUparaTest RTUparas_tset[10];
extern Radio_data_type  Radio_data;
extern RTUpara_type RTUparas;//

void Task(void)
{
	RecDataFroBoardUart1();
	MENU_START(); 
	ScreenTask();
	TaskMinute();
	TaskHour();
	TaskDay();
	if(DisplayPowerOnEN)
		TaskScreenPowerOn(screen_flag); 
	if(task_cnt==0)
		TaskLowPower(MENUConfig.workmode);
	TaskAlarm();
	if(bflagwakeup)
		TaskWakeUp(MENUConfig.workmode);
}
void TaskAlarm(void)
{
	if(Alarm_flag)//时钟中断需判断是哪个闹钟产生的中断
	{	
		Alarm_flag=0;	
		ReadAlarmFlag();
	}
	if(Alarm1_flag)
	{
		#ifdef POWER_DEBUGE
			printf("Alarm1 \r\n");
			printf("task_cnt=%X \r\n",task_cnt);
		#endif
		
		Alarm1_flag=0;
		Timer_task();
//		bflagwakeup=1;
//		task_cnt|=_Wakeup_task;
	}
	if(Alarm2_flag)
	{
		bflagwakeup=1;
		Alarm2_flag=0;
		task_cnt|=_Wakeup_task;
		#ifdef POWER_DEBUGE
			printf("Alarm2 \r\n");
			printf("task_cnt=%X \r\n",task_cnt);
		#endif
	}
}
void TaskMinute(void)
{
	if(bflagminute)
	{
		bflagminute=0;
		#ifdef DEBUGE
			TimePrint_dbg();
		#endif
		//每五分钟刷一次屏、显示上个五分钟水位、上个五分钟时段雨量						
	}
}
void TaskHour(void)
{
	u8 i;
	if(bflaghourstart)
	{
		#ifdef DEBUGE
			printf("/************************************************/ \r\n");
			printf("/**********************整点**********************/ \r\n");
			printf("/************************************************/ \r\n");
		#endif
		bflaghourstart=0;
		bflag68byte=0;
		bflag15byte=0; 
		bflag8byte=0; 
		DisplayChangeEN=1;
		for(i=0;i<RTUparas.RTUID_sum;i++)
		{	
			Rain_Lhour[i]=Radio_data.hrain_l[i]=Radio_data.hrain[i];
			Rain_hour[i]=Radio_data.hrain[i]=0x00;	
			WriteDATAtoFlash(LRAIN,Radio_data.hrain_l[i],i);	
			WriteDATAtoFlash(HRAIN,Radio_data.hrain[i],i);
		}
	}
}
void TaskDay(void)
{
	u8 i;
	if(bflagdaystart)//8：00今日雨量清零、第一个五分钟显示昨日雨量 
	{
		#ifdef DEBUGE
			printf("/************************************************/ \r\n");
			printf("/*********************8:00***********************/ \r\n");
			printf("/************************************************/ \r\n");
		#endif
		bflagdaystart=0;
		for(i=0;i<RTUparas.RTUID_sum;i++)
		{
			Rain_Yday[i]=Radio_data.rain_y[i]=Radio_data.rain[i];
			Rain_Yall[i]=Radio_data.rain_sum_y[i]=Radio_data.rain_sum[i];
			Rain_day[i]=Radio_data.rain[i]=0x00;
			WriteDATAtoFlash(YRAIN,Radio_data.rain_y[i],i);
			WriteDATAtoFlash(YARAIN,Radio_data.rain_sum_y[i],i);	
			WriteDATAtoFlash(TRAIN,Radio_data.rain[i],i);	
		}
	}
	if((bflagday==1)&&(DisplayChangeEN==0))
	{
		#ifdef DEBUGE
			printf("/************************************************/ \r\n");
			printf("/*********************00:00复位******************/ \r\n");
			printf("/************************************************/ \r\n");
		#endif
		bflagday=0;
		Sys_Soft_Reset();//系统复位//零点复位；
	}
}
void ScreenTask(void)
{
	if(RTC_check_already)
	{
		RTC_check_already=0;
		Send_BQ_time_dir(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
	}
	if(bflag_configlight)
	{	
		bflag_configlight=0;
		Send_BQ_data_light();
	}	
	if((DisplayChangeEN)&&(Time_power_on==1))
	{
		DisplayChangeEN=0;	
		Send_BQ_data_light();
		Display(DisplayPageno,Displaycontent);
	}	
}

