/******************** (C) COPYRIGHT 2014 JSYY***************************
 * �ļ���  ��usart.c
 * ����    ��������ش���      
 * Ӳ�����ӣ�------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * ��汾  ��ST3.5.0
 * ����    ��King
**********************************************************************************/	
#include "sys.h"
/*
 * ��������USART1_Config
 * ����  ��USART1 GPIO ����,����ģʽ����
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void USART_Config(u8 comn)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//4 λ��ռ���ȼ��� 0 λ��Ӧ���ȼ�
	switch(comn)
	{
		case COM1:
			/* config USART1 clock */
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
			/* USART1 GPIO config */
			/* Configure USART1 Tx (PA.09)(PB10) as alternate function push-pull */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);    
			/* Configure USART1 Rx (PA.10)(PB11) as input floating */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			/* Configure USART1 DTR (PB.12)(PB13) as alternate function push-pull */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);    
			/* Configure USART1 DCD (PB.12)(PB13) as input floating */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
		
			/* USART1 mode config */
			USART_InitStructure.USART_BaudRate = MENUConfig.baudrate;
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;
			USART_InitStructure.USART_StopBits = USART_StopBits_1;
			USART_InitStructure.USART_Parity = USART_Parity_No ;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART1, &USART_InitStructure);
			/* Enable the USARTy Interrupt */
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			USART_Cmd(USART1, ENABLE);
			
			SET_POW_MAX3222();
			SET_POW_USART1_DTR();
			break;
		case COM4:
				/* config UART4 clock */
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
					 // Configure UART4 Rx (PC11) as input floating                             
			GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOC, &GPIO_InitStructure);
			// Configure UART4 Tx (PC10) as alternate function push-pull                
			GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
			GPIO_Init(GPIOC, &GPIO_InitStructure);
				
		//	 UART4 mode config 
			USART_InitStructure.USART_BaudRate = 57600;
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;
			USART_InitStructure.USART_StopBits = USART_StopBits_1;
			USART_InitStructure.USART_Parity = USART_Parity_No ;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(UART4, &USART_InitStructure);
					// Enable the UART4 Interrupt 
			NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
			USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
			USART_Cmd(UART4, ENABLE);	
			break;
		case COM5:
			/* configUART5 clock */
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);


			/* UART5 GPIO config */
			/* Configure UART5 Tx PC12(PA.09)(PB10)  as alternate function push-pull */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOC, &GPIO_InitStructure);    
			/* Configure UART5 Rx PD2   (PA.10)(PB11) as input floating */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
			/* UART5 mode config */
			USART_InitStructure.USART_BaudRate = 57600;
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;
			USART_InitStructure.USART_StopBits = USART_StopBits_1;
			USART_InitStructure.USART_Parity = USART_Parity_No ;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(UART5, &USART_InitStructure);
				
			NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;	 
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
			USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
			USART_Cmd(UART5, ENABLE);	
			break;
		default:
			break;
	}
	
	
}



/*
 * ��������fputc
 * ����  ���ض���c�⺯��printf��USART1
 * ����  ����
 * ���  ����
 * ����  ����printf����
 */
//int fputc(int ch, FILE *f)
//{
//	/* ��Printf���ݷ������� */
//	USART_SendData(UART4, (unsigned char) ch);
//	while (!(UART4->SR & USART_FLAG_TXE));
//	return (ch);
//}
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 
	#ifdef WTD
	IWDG_Feed();
	#endif	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������    
	USART1->DR = (u8) ch;
	return ch;
	
}

// u8 Uart5_Recving;
// u8 Uart5_recvDone;
// u8 RecvFromUART5_Buf[UART5_REC_LEN];
// u16 RecvFromUART5_Len;
void UART5_IRQHandler(void)                	//����5�жϷ������
{
	u8 tmp;
	
	if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) //�����ж�
	{
	Uart_time_Start=1;
	Uart_time_num=0;
		
		tmp =USART_ReceiveData(UART5);//(USART1->DR);	//��ȡ���յ�������
		USART_SendData(UART5,tmp);
		while(USART_GetFlagStatus(UART5,USART_FLAG_TXE) == RESET);
		if((Hardware_check_flag&0x40)&&(tmp==0xaa))
			Hardware_check_flag|=0x10;
		switch (Uart5_Recving)
		{
			case 0:
				if(tmp == 0xA5)
				{
					Uart5_Recving=1;
					RecvFromUART5_Len=0;
					RecvFromUART5_Buf[RecvFromUART5_Len++]=tmp;
				}
				break;
			case 1:
				if(tmp == 0xA5)
				{
					Uart5_Recving=2;
					RecvFromUART5_Buf[RecvFromUART5_Len++]=tmp;
				}
				break;	
			case 2:	
				RecvFromUART5_Buf[RecvFromUART5_Len++]=tmp;
				if(tmp == 0x5A)
				{
					Uart5_Recving=0;
					Uart5_recvDone=BQREBACK;
					BQ_reback_timer=0;
					Uart_time_Start=0;
					Uart_time_num=0;
				}
				break;
			default:
				break;
			
		}	
	}	
}
extern RTUpara_type RTUparas;//
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 tmp;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�����ж�
	{
		if(task_cnt==0)
		{
			bflagwakeup=1;
			task_cnt|=_Serial_task;
		}
		Uart_time_Start=1;
		Uart_time_num=0;
		tmp =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		if((Hardware_check_flag&0x40)&&(tmp==0xaa))
			Hardware_check_flag|=0x01;
		switch (Uart1_Recving)
			{
				case 0:
					if (tmp == 0x7E)
					{
						RecvFromUART1_Len = 0;//
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
						Uart1_Recving = 0x01;		
					}
					else if (tmp == 0xA5)//&&(WhetherDirect==0))
					{
						Uart1_Recving = 0x11;
					}
					else if (tmp ==MENUConfig.areacode)	//8�ֽ�
					{
						RecvFromUART1_Len = 0;//
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
						Uart1_Recving = 0x21;
					}
					else if (tmp == 0x20)//��������
					{
						RecvFromUART1_Len = 0;//
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
						Uart1_Recving = 0x30;					
					}
					break;
				case 1:
					
					RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
					if((tmp==0x7E)&&(RecvFromUART1_Len==2))//�¹�Լ
					{
						Uart1_Recving=0x70;
					}
					else if(RecvFromUART1_Len == 5)
					{ 
						if(RecvFromUART1_Buf[4] == 0x0A)//15�ֽڳ��̲�
						{
								Uart1_Recving = 3;
								UART_15BFrameLen = tmp;
								UART_15BFrameLen += 5;
						}
						else														//68�ֽڼ���չ����
						{
							Uart1_Recving = 0x02;
							UART_68BFrameLen = tmp;
							UART_68BFrameLen += 5;
						}
					}
					break;
				case 2:
					RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
					if (RecvFromUART1_Len == UART_68BFrameLen)
					{
						bflag68byte=1;
						Uart1_Recving = 0;
						Uart1_recvDone = PCPROTOCOL68DATA;//һ֡�������
						Uart_time_Start=0;
						Uart_time_num=0;
					}
					break;
				case 3:
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
						if (RecvFromUART1_Len == UART_15BFrameLen)
						{
							bflag15byte=1;
							Uart1_Recving = 0;
							Uart1_recvDone = PTL15DATA;//һ֡�������  
							Uart_time_Start=0;
							Uart_time_num=0;
						}
					break;
				
				case 0x11:case 0x12:case 0x13:case 0x14:case 0x15:case 0x16:case 0x17:
					if (tmp == 0xA5)
						{
							Uart1_Recving++;
						
							RecvFromUART1_Len = 0;test=7;
						}
					else if (Uart1_Recving >= 0x16)
					{
						Uart1_Recving=18;
						RecvFromUART1_Len = 1;test=7;
					}
					break;	
			case 0x18:
					RecvFromUART1_Buf[RecvFromUART1_Len++]=tmp;
					if(RecvFromUART1_Len==14)//14 datas head package
						{
							Uart1_Recving=0x1a;	
							LenfpcforBQ=RecvFromUART1_Buf[13];//big first
							LenfpcforBQ=LenfpcforBQ<<8;
							LenfpcforBQ|=RecvFromUART1_Buf[12];		
						}
					break;	
				case 0x1a:
					if(RecvFromUART1_Len!=(LenfpcforBQ+15))//û�н������ ���� ��ʾͷ �� ���ݳ��������ֽ� ĩβ У��ͱ�ʾ��
						RecvFromUART1_Buf[RecvFromUART1_Len++]=tmp;
					else{
					Uart1_Recving=0x1b;
					RecvFromUART1_Buf[RecvFromUART1_Len++]=tmp;
					}
						
					break;	
				case 0x1b:
						RecvFromUART1_Buf[RecvFromUART1_Len++]=tmp;
						Uart1_Recving=0;
						Uart1_recvDone = PC_BQ_DATA;//һ֡�������
						test01++;
						Uart_time_Start=0;
						Uart_time_num=0;
					break;	
				case 0x21: //���յ�̨ 8�ֽ�������

					if(RecvFromUART1_Len <7)
					{
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
					}
					else
					{
						bflag8byte=1;
						Uart_time_Start	=0;
						Uart_time_num=0;
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
						Uart1_recvDone = PTL8DATA;
						Uart1_Recving = 0;
					}
					break;
				case 0x30:
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
						if(RecvFromUART1_Len>=40)//�յ�40�����Ͽո񣬽��봮������
						{
							u8 i;
							for(i=0;i<RecvFromUART1_Len;i++)
							{
								if(RecvFromUART1_Buf[i]!=0x20)
								{
									Uart1_Recving=0;
									Uart_time_Start=0;
									Uart_time_num=0;
									break;
								}
								else if(i>=20)
								{
									task_cnt|=_Config_task;
									Uart1_Recving=0x31;
									bflag_menu=MENU_0;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
									bflag_configStart=1;
									Alarm_flag=1;
									bflagScreenConfigstart=0;
									bflagScreenConfigcnt=0;		 							
								}
							}
						}
					break;
				case 0x31:
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
						if(RecvFromUART1_Len==1)
						{
							if(RecvFromUART1_Buf[0]==0x20)//������������û����
							{
									RecvFromUART1_Len=0;
									Uart_time_Start=0;
									Uart_time_num=0;
									
							}
							else if(RecvFromUART1_Buf[0]==0x31)//�������ò���
							{
									Uart1_Recving=0x32;
									bflag_menu=MENU_1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
									bflag_configStart=1;
							}
							else if(RecvFromUART1_Buf[0]==0x32)//�˳�����ģʽ
							{
									Uart1_Recving=0x0;
									bflag_configStart=1;
									bflag_menu=MENU_EXIT;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
							else 
							{
									bflag_menu=MENU_ERR;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
						}
					break;						
				case 0x32:
					
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
						if(RecvFromUART1_Len==1)
						{
							if((RecvFromUART1_Buf[0]>=0x31)&&((RecvFromUART1_Buf[0]<=0x39)))//���빤��ģʽ����
							{
									Uart1_Recving=RecvFromUART1_Buf[0]+0x10;
									bflag_menu=RecvFromUART1_Buf[0];
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
									bflag_configStart=1;
							}
							else if((RecvFromUART1_Buf[0]=='A')||(RecvFromUART1_Buf[0]=='a'))//������һ��
							{
									Uart1_Recving=0x31;
									bflag_menu=MENU_0;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
							else if((RecvFromUART1_Buf[0]=='B')||(RecvFromUART1_Buf[0]=='b'))//�˳�����
							{
									Uart1_Recving=0x0;
									bflag_menu=MENU_EXIT;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
							else
							{
									bflag_menu=MENU_ERR;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
						}
					break;	
				
				case 0x44:
				case 0x48:
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
						if(RecvFromUART1_Len==1)
						{
							if((RecvFromUART1_Buf[0]==0x31)||(RecvFromUART1_Buf[0]==0x32)||(RecvFromUART1_Buf[0]==0x33))//����ģʽ
							{
									Uart1_Recving+=0x10;
									bflag_menu=MENU_SURE;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
							else if((RecvFromUART1_Buf[0]=='A')||(RecvFromUART1_Buf[0]=='a'))//������һ��
							{
									Uart1_Recving=0x32;
									bflag_menu=MENU_1;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
							else if((RecvFromUART1_Buf[0]=='B')||(RecvFromUART1_Buf[0]=='b'))//�˳�����
							{
									Uart1_Recving=0x0;
									bflag_configStart=1;
									bflag_menu=MENU_EXIT;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
							else
							{
									bflag_menu=MENU_ERR;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
						}
					break;		
				case 0x43:
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
						if(RecvFromUART1_Len==1)
						{
							if((RecvFromUART1_Buf[0]==0x31)||(RecvFromUART1_Buf[0]==0x32)||(RecvFromUART1_Buf[0]==0x33)||(RecvFromUART1_Buf[0]==0x34))//����ʱ��
							{
									Uart1_Recving+=0x10;
									bflag_menu=MENU_SURE;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
							else if((RecvFromUART1_Buf[0]=='A')||(RecvFromUART1_Buf[0]=='a'))//������һ��
							{
									Uart1_Recving=0x32;
									bflag_menu=MENU_1;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
							else if((RecvFromUART1_Buf[0]=='B')||(RecvFromUART1_Buf[0]=='b'))//�˳�����
							{
									Uart1_Recving=0x0;
									bflag_configStart=1;
									bflag_menu=MENU_EXIT;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
							else
							{
									bflag_menu=MENU_ERR;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
						}
					break;					
				case 0x45:
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
						if((RecvFromUART1_Buf[0]=='A')||(RecvFromUART1_Buf[0]=='a'))//������һ��
						{
								Uart1_Recving=0x32;
								bflag_menu=MENU_1;
								bflag_configStart=1;
								Uart_time_Start=0;
								Uart_time_num=0;
								RecvFromUART1_Len=0;
						}
						else if((RecvFromUART1_Buf[0]=='B')||(RecvFromUART1_Buf[0]=='b'))//�˳�����
						{
								Uart1_Recving=0x0;
								bflag_menu=MENU_EXIT;
								Uart_time_Start=0;
								Uart_time_num=0;
								RecvFromUART1_Len=0;
						}
						else if(RecvFromUART1_Len>=19)
						{
							if((RecvFromUART1_Buf[4]==0x2D)&&(RecvFromUART1_Buf[10]==0x20)&&(RecvFromUART1_Buf[13]==0x3A))//����ʱ�� 2018-1-22 10:56:48 32 30 31 38 2D 31 2D 32 32 20 31 30 3A 35 36 3A 34 38 
							{
									Uart1_Recving=0x55;
									bflag_menu=MENU_SURE;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
							else
							{
									bflag_menu=MENU_ERR;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
						 }
					break;
					case 0x41:
					case 0x42:							
					case 0x46:
					case 0x47:
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
						if(RecvFromUART1_Len==1)
						{
							if((RecvFromUART1_Buf[0]==0x31)||(RecvFromUART1_Buf[0]==0x32))//״̬��
							{
									Uart1_Recving+=0x10;
									bflag_menu=MENU_SURE;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
							else if((RecvFromUART1_Buf[0]=='A')||(RecvFromUART1_Buf[0]=='a'))//������һ��
							{
									Uart1_Recving=0x32;
									bflag_menu=MENU_1;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
							else if((RecvFromUART1_Buf[0]=='B')||(RecvFromUART1_Buf[0]=='b'))//�˳�����
							{
									Uart1_Recving=0x0;
									bflag_configStart=1;
									bflag_menu=MENU_EXIT;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}
							else
							{
									bflag_menu=MENU_ERR;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
							}          
						}
					break;				
				case 0x49:
						RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
						if(((RecvFromUART1_Buf[0]>='0')&&(RecvFromUART1_Buf[0]<='9'))||((RecvFromUART1_Buf[0]>='A')&&(RecvFromUART1_Buf[0]<='F'))||((RecvFromUART1_Buf[0]>='a')&&(RecvFromUART1_Buf[0]<='f')))//������һ��
						{
								Uart1_Recving+=0x10;
								bflag_menu=MENU_SURE;
								bflag_configStart=1;
								Uart_time_Start=0;
								Uart_time_num=0;
								RecvFromUART1_Len=0;
						}
						else if((RecvFromUART1_Buf[0]=='Z')||(RecvFromUART1_Buf[0]=='z'))//������һ��
						{
								Uart1_Recving=0x32;
								bflag_menu=MENU_1;
								bflag_configStart=1;
								Uart_time_Start=0;
								Uart_time_num=0;
								RecvFromUART1_Len=0;
						}
						else if((RecvFromUART1_Buf[0]=='X')||(RecvFromUART1_Buf[0]=='x'))//�˳�����
						{
								Uart1_Recving=0x0;
								bflag_configStart=1;
								bflag_menu=MENU_EXIT;
								Uart_time_Start=0;
								Uart_time_num=0;
								RecvFromUART1_Len=0;
						}
						else
						{
								bflag_menu=MENU_ERR;
								bflag_configStart=1;
								Uart_time_Start=0;
								Uart_time_num=0;
								RecvFromUART1_Len=0;
						}
					break;				
				case 0x51:
				case 0x52:	
				case 0x53:
				case 0x54:	
				case 0x55:
				case 0x56:
				case 0x57:
				case 0x58:
				case 0x59:	
							RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
							if(RecvFromUART1_Len==1)
							{
								if((RecvFromUART1_Buf[0]=='Y')||(RecvFromUART1_Buf[0]=='y'))//��ʼ���ù���ģʽ
								{
										bflag_menu=Uart1_Recving;
										bflag_configStart=1;
										Uart_time_Start=0;
										Uart_time_num=0;
										RecvFromUART1_Len=0;
								}
								else if((RecvFromUART1_Buf[0]=='N')||(RecvFromUART1_Buf[0]=='n'))//��ʼ���ù���ģʽ
								{
									bflag_menu=Uart1_Recving-0x20;
									Uart1_Recving-=0x10;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
								}
								else
								{
									bflag_menu=MENU_ERR;
									bflag_configStart=1;
									Uart_time_Start=0;
									Uart_time_num=0;
									RecvFromUART1_Len=0;
								}
							 }
					break;	
				case 0x70:////7e7e protocol
					RecvFromUART1_Buf[RecvFromUART1_Len++] = tmp;
					if((RecvFromUART1_Len>12)&&(RecvFromUART1_Len==((((RecvFromUART1_Buf[11]&0x0F)<<8)|RecvFromUART1_Buf[12])+17))){//len�ĵ�12λ��ʾ���ĳ��ȣ���+17Ϊ���ĳ���
						Uart1_recvDone = PCPROTOCOL7E7EDATA;	
						Uart1_Recving=0;
						Uart_time_Start=0;
						Uart_time_num=0;
					}
					break;					
			default:break;
			}
	}
}
//void UART4_IRQHandler(void)                	//����1�жϷ������
//{
//	u8 tmp;
//	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) //�����ж�
//	{
//		tmp =USART_ReceiveData(UART4);//(USART1->DR);	//��ȡ���յ�������
//	}
//}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

