/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * 文件名  ：led.c
 * 描述    ：led 应用函数库         
 * 实验平台：野火STM32开发板
 * 硬件连接：-----------------
 *          |   PC3 - LED1     |
 *          |   PC4 - LED2     |
 *          |   PC5 - LED3     |
 *           ----------------- 
 * 库版本  ：ST3.5.0
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "sys.h" 
extern  Temp_Humi_value Temp_val;
extern  Temp_Humi_value Humi_val;
/*
 * 函数名：GPIO_Config
 * 描述  ：配置LED用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
void GPIO_Config(void)
{		
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	//******************************************************
	//LED
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);/*开启GPIOC的外设时钟*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;/*选择要控制的GPIOC引脚*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;/*设置引脚模式为通用推挽输出*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;/*设置引脚速率为50MHz */ 
	GPIO_Init(GPIOC, &GPIO_InitStructure);/*调用库函数，初始化GPIOC*/		  
	GPIO_ResetBits(GPIOC, GPIO_Pin_2 | GPIO_Pin_3);/* 关闭所有led灯	*/	
	
	//MAX3222E PD0_UART_SHDN(控制板TX) PD1_UART_EN(控制板RX)
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);/*开启GPIOD的外设时钟*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;/*选择要控制的GPIOD引脚*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;/*设置引脚模式为通用推挽输出*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;/*设置引脚速率为50MHz */ 
	GPIO_Init(GPIOD, &GPIO_InitStructure);/*调用库函数，初始化GPIOD*/		  
	GPIO_ResetBits(GPIOD, GPIO_Pin_0 );/* 关闭SHDN发送使能*/
	

	//************************************************************
	//RELAY
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);/*开启GPIOB的外设时钟*/ 										   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;/*选择要控制的GPIOC引脚*/	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;/*设置引脚模式为通用推挽输出*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;/*设置引脚速率为50MHz */  
	GPIO_Init(GPIOB, &GPIO_InitStructure);/*调用库函数，初始化GPIOC*/		  
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);/* 关闭外部继电器	*/	

	/* config the extiline(PB0) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
  /* 配置P[A|B|C|D|E]12为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* EXTI line gpio config(PA12) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // 上拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* EXTI line(PA12) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line12;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	 /* 配置P[A|B|C|D|E]12为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
		/* EXTI line gpio config(PD15) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // 上拉输入
  GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* EXTI line(PD15) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource3); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}
void GPIO_NOUSE_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);/*开启GPIOC的外设时钟*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIOA_NOUSE;/*选择要控制的GPIOC引脚*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;/*设置引脚模式为通用推挽输出*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;/*设置引脚速率为50MHz */ 
	GPIO_Init(GPIOA, &GPIO_InitStructure);/*调用库函数，初始化GPIOC*/

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);/*开启GPIOC的外设时钟*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIOB_NOUSE;/*选择要控制的GPIOC引脚*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;/*设置引脚模式为通用推挽输出*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;/*设置引脚速率为50MHz */ 
	GPIO_Init(GPIOB, &GPIO_InitStructure);/*调用库函数，初始化GPIOC*/
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC| RCC_APB2Periph_AFIO, ENABLE);/*开启GPIOC的外设时钟,将PC13-PC15用作普通IO口*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIOC_NOUSE;/*选择要控制的GPIOC引脚*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;/*设置引脚模式为通用推挽输出*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;/*设置引脚速率为50MHz */ 
	GPIO_Init(GPIOC, &GPIO_InitStructure);/*调用库函数，初始化GPIOC*/
	PWR_BackupAccessCmd(ENABLE);//允许修改RTC和后备寄存器
	RCC_LSEConfig(RCC_LSE_OFF);//关闭外部低速时钟信号
	BKP_TamperPinCmd(DISABLE);//?关闭入侵检测功能PC13
	BKP_ITConfig(DISABLE);//备份区写保护
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);/*开启GPIOC的外设时钟*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIOD_NOUSE;/*选择要控制的GPIOC引脚*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;/*设置引脚模式为通用推挽输出*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;/*设置引脚速率为50MHz */ 
	GPIO_Init(GPIOD, &GPIO_InitStructure);/*调用库函数，初始化GPIOC*/
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);/*开启GPIOC的外设时钟*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIOE_NOUSE;/*选择要控制的GPIOC引脚*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;/*设置引脚模式为通用推挽输出*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;/*设置引脚速率为50MHz */ 
	GPIO_Init(GPIOE, &GPIO_InitStructure);/*调用库函数，初始化GPIOC*/
}
void USART1toEXTI(FunctionalState able)
{
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/* config the extiline(PB0) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
  /* 配置P[A|B|C|D|E]12为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* EXTI line gpio config(PA12) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // 上拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* EXTI line(PA12) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource10); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line10;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = able;
  EXTI_Init(&EXTI_InitStructure);
}	
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET) //确保是否产生了EXTI Line中断
	{
		EXTI_ClearITPendingBit(EXTI_Line10);     //清除中断标志位
		bflagwakeup=1;
		task_cnt|=_Serial_task;
		
	} 
	if(EXTI_GetITStatus(EXTI_Line12) != RESET) //确保是否产生了EXTI Line中断
	  {
		EXTI_ClearITPendingBit(EXTI_Line12);     //清除中断标志位
	  } 
	}
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET) //确保是否产生了EXTI Line中断
	{
		EXTI_ClearITPendingBit(EXTI_Line3);     //清除中断标志位                                                
		Alarm_flag=1;
	}  	
}
//初始化独立看门狗
//prer:分频数:0~7(只有低3位有效!)
//分频因子=4*2^prer.但最大值只能是256!
//rlr:重装载寄存器值:低11位有效.
//时间计算(大概):Tout=((4*2^prer)*rlr)/40 (ms).
void IWDG_Init(u8 prer,u16 rlr) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能对寄存器IWDG_PR和IWDG_RLR的写操作
	
	IWDG_SetPrescaler(prer);  //设置IWDG预分频值:设置IWDG预分频值为64
	
	IWDG_SetReload(rlr);  //设置IWDG重装载值
	
	IWDG_ReloadCounter();  //按照IWDG重装载寄存器的值重装载IWDG计数器
	
	IWDG_Enable();  //使能IWDG
}
//喂独立看门狗
void IWDG_Feed(void)
{   
	#ifdef WTD
		if(MENUConfig.workmode==WORKMODENORMAL)
			IWDG_ReloadCounter();//reload	
	#endif									   
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
