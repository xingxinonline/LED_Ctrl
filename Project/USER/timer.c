#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//定时器 驱动代码	   
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)//4999,7199 8M时钟频率分频分成 10K 
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;  //先占优先级5级低于串口接收数据中断
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	TIM_Cmd(TIM3, DISABLE);  //使能TIMx					 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志 
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
			Sys_Soft_Reset();//系统复位//零点复位；
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
				Sys_Soft_Reset();//系统复位//零点复位；
			}
		}
	}
		
	if(calendar.sec==0)	Minute_Task();
}
void Minute_Task(void)
{
	bflagminute=1;//分钟标志
	if(calendar.min%5==0)
		bflagfivemin=1;//五分钟标志
	if(calendar.min == 0)
		bflaghour=1;//小时标志
	if((calendar.hour ==00 )&&(calendar.min == MENUConfig.hourstart))
		bflagday=1;//日标志
	if(calendar.min == MENUConfig.hourstart)
		bflaghourstart=1;//时段雨量更新
	if((calendar.hour == MENUConfig.daystart)&&(calendar.min == MENUConfig.hourstart))
		bflagdaystart=1;//日雨量更新
}








