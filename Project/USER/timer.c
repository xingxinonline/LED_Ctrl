#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//��ʱ�� ��������	   
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)//4999,7199 8Mʱ��Ƶ�ʷ�Ƶ�ֳ� 10K 
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;  //��ռ���ȼ�5�����ڴ��ڽ��������ж�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	TIM_Cmd(TIM3, DISABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־ 
			TIM3_flag=1;
		}
}

void  Timer_task(void)
{
	get_show_time();
	if((MENUConfig.workmode==WORKMODENORMAL)||(MENUConfig.ledstatus==1))
		LEDSTATUS=~LEDSTATUS;
	else LEDSTATUS=1;
	if(bflagsystemstart==1)
	{
		System_Start_time++;
		if(System_Start_time>=300)
		{
			Sys_Soft_Reset();//ϵͳ��λ//��㸴λ��
		}
	}
	if(bflagScreenConfigstart==1)
	{
		bflagScreenConfigcnt++;
		if(bflagScreenConfigcnt>=300)
		{
			bflagScreenConfigstart=0;
			bflagScreenConfigcnt=0;
			Uart1_Recving=0x0;
			bflag_configStart=1;
			bflag_menu=MENU_EXIT;
			Uart_time_Start=0;
			Uart_time_num=0;
			RecvFromUART1_Len=0;
		}
	}
	if(task_cnt&_Serial_task)
	{
		Uart_serailport_num++;
		if(Uart_serailport_num>=5)
		{
			Uart_serailport_num=0;
			task_cnt&=~_Serial_task;
		} 
	}
	if(task_cnt&_Wakeup_task)
	{
		Uart_waketime_num++;
		if(Uart_waketime_num>=MENUConfig.wakestay)
		{
			Uart_waketime_num=0;
			task_cnt&=~_Wakeup_task;
		}
	}
	if(Uart_time_Start==1)
		Uart_time_num++;
	if(Uart_time_num>3)
	{
		Uart_time_num=0;
		Uart_time_Start=0;
		Uart1_Recving=0;
		Uart5_Recving=0;
	}
	if(RebackPC_time!=0)
		RebackPC_time++;
	if(RebackPC_time>2)
	{
		RebackPC(CurrentCMD);
		RebackPC_time=0;
		DisplayChangeEN=1;
	}	
	if((DisplayStayTime!=0xff)&&(DisplayStayTime>0)&&(MENUConfig.workmode!=WORKMODESTOP))
	{
		if(DisplayRunTime<DisplayStayTime)
			DisplayRunTime++;
		else
		{
			DisplayRunTime=0;
			DisplayChangeEN=1;
			if(DisplayPageno<(DisplayPagesub-1))DisplayPageno++;
			else DisplayPageno=0;
		}			
	}
	if((DisplayPowerOnRunTimeStart)&&(DisplayPowerOnEN==0))
	{
		DisplayPowerOnRunTime++;
		if(DisplayPowerOnRunTime>DisplayPowerOnRunTimeCnt)
		{
			DisplayPowerOnRunTimeStart=0;
			DisplayPowerOnRunTime=0;
			DisplayPowerOnEN=1;
			if(bflagRedBoard_Check)
			{
				bflagRedBoard_Check=0;
				screen_flag=Screen_Red_Err;
			}
			if(screen_flag==Screen_Reset_Ready)
			{
				Sys_Soft_Reset();//ϵͳ��λ//��㸴λ��
			}
		}
	}
		
	if(calendar.sec==0)	Minute_Task();
}
void Minute_Task(void)
{
	bflagminute=1;//���ӱ�־
	if(calendar.min%5==0)
		bflagfivemin=1;//����ӱ�־
	if(calendar.min == 0)
		bflaghour=1;//Сʱ��־
	if((calendar.hour ==00 )&&(calendar.min == MENUConfig.hourstart))
		bflagday=1;//�ձ�־
	if(calendar.min == MENUConfig.hourstart)
		bflaghourstart=1;//ʱ����������
	if((calendar.hour == MENUConfig.daystart)&&(calendar.min == MENUConfig.hourstart))
		bflagdaystart=1;//����������
}








