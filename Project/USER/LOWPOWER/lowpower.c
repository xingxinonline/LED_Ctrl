#include "sys.h" 

void TaskLowPower(u8 workmode)
{
	switch(workmode)
	{
//		case WORKMODENORMAL:
		case WORKMODESLEEP:
			#ifdef POWER_DEBUGE
				printf("task_cnt=%d\r\n",task_cnt);
				printf("go to stleep mode\r\n");
			#endif
			TasktoSleepMode();
			Sys_EnterSLEEPmode();
			break; 
		case WORKMODESTOP:
			#ifdef POWER_DEBUGE
				printf("task_cnt=%d\r\n",task_cnt);
				printf("go to stop mode\r\n");
			#endif
			TasktoStopMode();
			Sys_EnterSTOPmode();
			break;
		default:
			break;
	}
}
void TaskWakeUp(u8 workmode)
{
	bflagwakeup=0;
	switch(workmode)
	{
//		case WORKMODENORMAL:
		case WORKMODESLEEP:
				TaskfromSleepMode(); 
				#ifdef POWER_DEBUGE
					printf("%ld年%.2d月%.2d日 ",(unsigned long)calendar.w_year+2000,calendar.w_month,calendar.w_date);
					printf("%.2d时%.2d分%.2d秒  \r\n",calendar.hour,calendar.min,calendar.sec);
					printf("task_cnt=%d\r\n",task_cnt); 
					printf("interrupt from stleep mode\r\n");
				#endif
			break; 
		case WORKMODESTOP:
				TaskfromStopMode();
				#ifdef POWER_DEBUGE
					printf("%ld年%.2d月%.2d日 ",(unsigned long)calendar.w_year+2000,calendar.w_month,calendar.w_date);
					printf("%.2d时%.2d分%.2d秒  \r\n",calendar.hour,calendar.min,calendar.sec);
					printf("task_cnt=%d\r\n",task_cnt);
					printf("interrupt from stop mode\r\n");
				#endif
			break;
		default:
			break;
	}
}
//*****************************************
//睡眠模式
//*****************************************
void Sys_EnterSLEEPmode(void)
{
	__WFI();
}
//*****************************************
//停止模式
//*****************************************
void Sys_EnterSTOPmode(void)
{
	//使能电源管理的时钟
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
 //进入停止模式，设置电压调节器为低功耗模式，等待中断唤醒       
 PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
}
//*****************************************
//睡眠模式准备任务
//*****************************************
void TasktoSleepMode(void)
{
	if(MENUConfig.ledstatus==0)
		CloseAlarm1();
	PER_SLEEP_CONFIG(DISABLE);
}
//*****************************************
//睡眠模式唤醒任务
//*****************************************
void TaskfromSleepMode(void)
{
	PER_SLEEP_CONFIG(ENABLE);
	if(MENUConfig.ledstatus==0)
		OpenAlarm1();
}
//睡眠模式相关外设处理
void PER_SLEEP_CONFIG(FunctionalState able)
{
	CLR_POW_MAX3222();
	FLASHERR=1;
	LEDSTATUS=1;
	RCC_APB1PeriphClockCmd(RCC_APB1_SLEEP_NOUSE, able);
	RCC_APB2PeriphClockCmd(RCC_APB2_SLEEP_NOUSE, able);	
}
//*****************************************
//停止模式准备任务
//*****************************************
void TasktoStopMode(void)
{
	FLASHERR=1;
	LEDSTATUS=1;
	CLR_POW_MAX3222();
	CloseAlarm1();
	ClearAlarm1Flag();
	USART1toEXTI(ENABLE);      
}
//*****************************************
//停止模式唤醒任务
//*****************************************
void TaskfromStopMode(void)
{
	SYSCLKConfig_STOP();
	SET_POW_MAX3222();
	USART1toEXTI(DISABLE); 
	USART_Config(COM1); 
	OpenAlarm1();
}
//恢复系统时钟函数
void SYSCLKConfig_STOP(void)
{ 
  /* After wake-up from STOP reconfigure the system clock */
  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);
   
  /* Wait till HSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
  {}
   
  /* Enable PLL */
  RCC_PLLCmd(ENABLE);
   
  /* Wait till PLL is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
  {}
   
  /* Select PLL as system clock source */
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
   
  /* Wait till PLL is used as system clock source */
  while (RCC_GetSYSCLKSource() != 0x08)
  {}
}

