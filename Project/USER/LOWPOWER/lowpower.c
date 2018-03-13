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
					printf("%ld��%.2d��%.2d�� ",(unsigned long)calendar.w_year+2000,calendar.w_month,calendar.w_date);
					printf("%.2dʱ%.2d��%.2d��  \r\n",calendar.hour,calendar.min,calendar.sec);
					printf("task_cnt=%d\r\n",task_cnt); 
					printf("interrupt from stleep mode\r\n");
				#endif
			break; 
		case WORKMODESTOP:
				TaskfromStopMode();
				#ifdef POWER_DEBUGE
					printf("%ld��%.2d��%.2d�� ",(unsigned long)calendar.w_year+2000,calendar.w_month,calendar.w_date);
					printf("%.2dʱ%.2d��%.2d��  \r\n",calendar.hour,calendar.min,calendar.sec);
					printf("task_cnt=%d\r\n",task_cnt);
					printf("interrupt from stop mode\r\n");
				#endif
			break;
		default:
			break;
	}
}
//*****************************************
//˯��ģʽ
//*****************************************
void Sys_EnterSLEEPmode(void)
{
	__WFI();
}
//*****************************************
//ֹͣģʽ
//*****************************************
void Sys_EnterSTOPmode(void)
{
	//ʹ�ܵ�Դ�����ʱ��
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
 //����ֹͣģʽ�����õ�ѹ������Ϊ�͹���ģʽ���ȴ��жϻ���       
 PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
}
//*****************************************
//˯��ģʽ׼������
//*****************************************
void TasktoSleepMode(void)
{
	if(MENUConfig.ledstatus==0)
		CloseAlarm1();
	PER_SLEEP_CONFIG(DISABLE);
}
//*****************************************
//˯��ģʽ��������
//*****************************************
void TaskfromSleepMode(void)
{
	PER_SLEEP_CONFIG(ENABLE);
	if(MENUConfig.ledstatus==0)
		OpenAlarm1();
}
//˯��ģʽ������账��
void PER_SLEEP_CONFIG(FunctionalState able)
{
	CLR_POW_MAX3222();
	FLASHERR=1;
	LEDSTATUS=1;
	RCC_APB1PeriphClockCmd(RCC_APB1_SLEEP_NOUSE, able);
	RCC_APB2PeriphClockCmd(RCC_APB2_SLEEP_NOUSE, able);	
}
//*****************************************
//ֹͣģʽ׼������
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
//ֹͣģʽ��������
//*****************************************
void TaskfromStopMode(void)
{
	SYSCLKConfig_STOP();
	SET_POW_MAX3222();
	USART1toEXTI(DISABLE); 
	USART_Config(COM1); 
	OpenAlarm1();
}
//�ָ�ϵͳʱ�Ӻ���
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

