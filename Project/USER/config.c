/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * �ļ���  ��led.c
 * ����    ��led Ӧ�ú�����         
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�-----------------
 *          |   PC3 - LED1     |
 *          |   PC4 - LED2     |
 *          |   PC5 - LED3     |
 *           ----------------- 
 * ��汾  ��ST3.5.0
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "sys.h" 
extern  Temp_Humi_value Temp_val;
extern  Temp_Humi_value Humi_val;
/*
 * ��������GPIO_Config
 * ����  ������LED�õ���I/O��
 * ����  ����
 * ���  ����
 */
void GPIO_Config(void)
{		
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	//******************************************************
	//LED
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);/*����GPIOC������ʱ��*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;/*ѡ��Ҫ���Ƶ�GPIOC����*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;/*��������ģʽΪͨ���������*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;/*������������Ϊ50MHz */ 
	GPIO_Init(GPIOC, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIOC*/		  
	GPIO_ResetBits(GPIOC, GPIO_Pin_2 | GPIO_Pin_3);/* �ر�����led��	*/	
	
	//MAX3222E PD0_UART_SHDN(���ư�TX) PD1_UART_EN(���ư�RX)
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);/*����GPIOD������ʱ��*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;/*ѡ��Ҫ���Ƶ�GPIOD����*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;/*��������ģʽΪͨ���������*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;/*������������Ϊ50MHz */ 
	GPIO_Init(GPIOD, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIOD*/		  
	GPIO_ResetBits(GPIOD, GPIO_Pin_0 );/* �ر�SHDN����ʹ��*/
	

	//************************************************************
	//RELAY
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);/*����GPIOB������ʱ��*/ 										   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;/*ѡ��Ҫ���Ƶ�GPIOC����*/	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;/*��������ģʽΪͨ���������*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;/*������������Ϊ50MHz */  
	GPIO_Init(GPIOB, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIOC*/		  
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);/* �ر��ⲿ�̵���	*/	

	/* config the extiline(PB0) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
  /* ����P[A|B|C|D|E]12Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* EXTI line gpio config(PA12) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // ��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* EXTI line(PA12) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line12;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	 /* ����P[A|B|C|D|E]12Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
		/* EXTI line gpio config(PD15) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // ��������
  GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* EXTI line(PD15) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource3); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}
void GPIO_NOUSE_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);/*����GPIOC������ʱ��*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIOA_NOUSE;/*ѡ��Ҫ���Ƶ�GPIOC����*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;/*��������ģʽΪͨ���������*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;/*������������Ϊ50MHz */ 
	GPIO_Init(GPIOA, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIOC*/

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);/*����GPIOC������ʱ��*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIOB_NOUSE;/*ѡ��Ҫ���Ƶ�GPIOC����*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;/*��������ģʽΪͨ���������*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;/*������������Ϊ50MHz */ 
	GPIO_Init(GPIOB, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIOC*/
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC| RCC_APB2Periph_AFIO, ENABLE);/*����GPIOC������ʱ��,��PC13-PC15������ͨIO��*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIOC_NOUSE;/*ѡ��Ҫ���Ƶ�GPIOC����*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;/*��������ģʽΪͨ���������*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;/*������������Ϊ50MHz */ 
	GPIO_Init(GPIOC, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIOC*/
	PWR_BackupAccessCmd(ENABLE);//�����޸�RTC�ͺ󱸼Ĵ���
	RCC_LSEConfig(RCC_LSE_OFF);//�ر��ⲿ����ʱ���ź�
	BKP_TamperPinCmd(DISABLE);//?�ر����ּ�⹦��PC13
	BKP_ITConfig(DISABLE);//������д����
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);/*����GPIOC������ʱ��*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIOD_NOUSE;/*ѡ��Ҫ���Ƶ�GPIOC����*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;/*��������ģʽΪͨ���������*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;/*������������Ϊ50MHz */ 
	GPIO_Init(GPIOD, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIOC*/
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);/*����GPIOC������ʱ��*/ 													   
	GPIO_InitStructure.GPIO_Pin = GPIOE_NOUSE;/*ѡ��Ҫ���Ƶ�GPIOC����*/		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;/*��������ģʽΪͨ���������*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;/*������������Ϊ50MHz */ 
	GPIO_Init(GPIOE, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIOC*/
}
void USART1toEXTI(FunctionalState able)
{
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/* config the extiline(PB0) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
  /* ����P[A|B|C|D|E]12Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* EXTI line gpio config(PA12) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // ��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* EXTI line(PA12) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource10); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line10;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
  EXTI_InitStructure.EXTI_LineCmd = able;
  EXTI_Init(&EXTI_InitStructure);
}	
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		EXTI_ClearITPendingBit(EXTI_Line10);     //����жϱ�־λ
		bflagwakeup=1;
		task_cnt|=_Serial_task;
		
	} 
	if(EXTI_GetITStatus(EXTI_Line12) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	  {
		EXTI_ClearITPendingBit(EXTI_Line12);     //����жϱ�־λ
	  } 
	}
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		EXTI_ClearITPendingBit(EXTI_Line3);     //����жϱ�־λ                                                
		Alarm_flag=1;
	}  	
}
//��ʼ���������Ź�
//prer:��Ƶ��:0~7(ֻ�е�3λ��Ч!)
//��Ƶ����=4*2^prer.�����ֵֻ����256!
//rlr:��װ�ؼĴ���ֵ:��11λ��Ч.
//ʱ�����(���):Tout=((4*2^prer)*rlr)/40 (ms).
void IWDG_Init(u8 prer,u16 rlr) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����
	
	IWDG_SetPrescaler(prer);  //����IWDGԤ��Ƶֵ:����IWDGԤ��ƵֵΪ64
	
	IWDG_SetReload(rlr);  //����IWDG��װ��ֵ
	
	IWDG_ReloadCounter();  //����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������
	
	IWDG_Enable();  //ʹ��IWDG
}
//ι�������Ź�
void IWDG_Feed(void)
{   
	#ifdef WTD
		if(MENUConfig.workmode==WORKMODENORMAL)
			IWDG_ReloadCounter();//reload	
	#endif									   
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
