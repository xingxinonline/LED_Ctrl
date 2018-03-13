#include "sys.h" 
//ҳ�����ݸ�ʽ
// Head_Data + Pack_len + Cmd_Config + Area_len + Area_Config + Data_len + Data
const u8 Head_Data[20]={0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0x01,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x02
};//���������ֽڵİ���
u8 Pack_len[2]={0x24,0x00};//������ʱ���� 
const u8 Cmd_Config[7]={0xA3,0x06,0x01,0x00,0x00,
	0xFF,			/*ɾ�����ж�̬��*/  
	0x01,			/*�������*/   								/*�ɱ༭*/
};	
u8 Area_len[2]={0x1B,0x00};//�������������򳤶� 
const u8 Area_Config[32]={	0x00,			/*��������*/  
							0x00,0x00,		/*x���� ��λ���ֽڣ�8�����ص㣩*/ 								/*�ɱ༭*/
							0x00,0x00,		/*y���� ��λ�����ص�*/											/*�ɱ༭*/
							0x60,0x00,		/*������ ��λ���ֽڣ�8�����ص㣩*/ 							/*�ɱ༭*/
							0x10,0x00,		/*����߶� ��λ�����ص�*/
							0x00,			/*��̬������*/
							0x00,			/*�м��*/
							0x00,			/*��̬������ģʽ0-ѭ����ʾ 1-��ʾ��ɺ�ͣ�������һҳ 
												3-ѭ����ʱδ����ɾ�� 4-ѭ����ʱδ������ʾLogo��Ϣ*/						/*�ɱ༭*/
							0x00,0x00,		/*��̬����ʱʱ��*//*�ɱ༭*/
							0x00,0x00,0x00,	/*�����ֽ�*/
							0x01,			/*�Ƿ�����ʾ 1-������ʾ 2-������ʾ*/										/*�ɱ༭*/
							0x02,			/*�Ƿ��Զ����� 1-���Զ� 2-�Զ�*/											/*�ɱ༭*/
							0x03,			/*��ʾ��ʽ 1-��ֹ��ʾ 2-���ٴ�� 3-�����ƶ� 
														4-�����ƶ� 5-�����ƶ� 6-�����ƶ�*/								/*�ɱ༭*/
							0x00,			/*�˳���ʽ*/
							0x06,			/*��ʾ�ٶ�0-��� ......0x18����*/											/*�ɱ༭*/
							0x00			/*��ʾͣ��ʱ��*/															/*�ɱ༭*/
	};
u8 Data_len[4]={0x00,0x00,0x00,0x00};//������ʱ�������ݳ���  �����Ǳ���������
u8 Power_On[]={"��ӭʹ�ý�ˮ����˾�豸"};
u8 Power_On_Mode[]={"�豸�ѽ����ϵ��Լ�ģʽ"};
u8 Ping_Redboard[]={"���ڼ��쿨ͨ��"};
u8 Ping_Err[]={"�쿨����ʧ��"};
u8 Ping_Success[]={"�쿨���ӳɹ�"};
u8 Init_Screen[]={"���ڳ�ʼ������"};
u8 Init_Err[]={"������ȡ�������������ò���"};
u8 Init_Success[]={"��ʼ�������ɹ�"};
u8 Power_Finish[]={"�ϵ��Լ���ɣ�������λ"};
u8 RTU_Data_Check[]={"����10�����ڷ��ͱ���"};
u8 RTU_Data_Err[]={"�ѳ�ʱ����������"};
u8 RTU_Data_Success[]={"���Ľ��ճɹ������ڽ�������"};
u8 RTU_Data_Parse_Err[]={"���ڽ�������"};
u8 RTU_Data_Parse_Success[]={"���Ľ����ɹ�"};
u8 RTU_Data[100];





const u8 Ping_Cmd[30]={0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0x01,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x02,0x05,
				0x00,0xA2,0x00,0x01,0x00,0x00,0x68,0xF8,0x5A};

void PrintftoScreen(u8 *buf,u8 len) 
{
	u8 crc_buf[512],tmpbuf[512],SendtoScreen_len=0,i;
	u16 CRC16;
	len-=1;//sizeof()�ĳ��Ȱ����������ĳ��ȣ��ʳ��ȶ���1
	for(i=0;i<20;i++)
		tmpbuf[SendtoScreen_len++]=Head_Data[i];
	tmpbuf[SendtoScreen_len++]=Pack_len[0]+len;
	tmpbuf[SendtoScreen_len++]=Pack_len[1];
	for(i=0;i<7;i++)
		tmpbuf[SendtoScreen_len++]=Cmd_Config[i];
	tmpbuf[SendtoScreen_len++]=Area_len[0]+len;
	tmpbuf[SendtoScreen_len++]=Area_len[1];
	for(i=0;i<23;i++)
		tmpbuf[SendtoScreen_len++]=Area_Config[i];
	tmpbuf[SendtoScreen_len++]=Data_len[0]+len;
	tmpbuf[SendtoScreen_len++]=Data_len[1];
	tmpbuf[SendtoScreen_len++]=Data_len[2];
	tmpbuf[SendtoScreen_len++]=Data_len[3];
	for(i=0;i<len;i++)
		tmpbuf[SendtoScreen_len++]=buf[i];
	for(i=8;i<SendtoScreen_len;i++)
		crc_buf[i-8]=tmpbuf[i];
	CRC16=crc16_ctrl(crc_buf,(SendtoScreen_len-8));
	tmpbuf[SendtoScreen_len++]=CRC16;
	tmpbuf[SendtoScreen_len++]=CRC16>>8;
	SendtoScreen_len=Character_Transfer(tmpbuf,SendtoScreen_len); 
	for(i=0;i<SendtoScreen_len;i++)
	{
		USART_SendData(UART5, tmpbuf[i]);
		while (!(UART5->SR & USART_FLAG_TXE));
	}
	#ifdef SCREEN_DEBUGE
		for(i=0;i<SendtoScreen_len;i++)
		{
			USART_SendData(USART1, tmpbuf[i]);
			while (!(USART1->SR & USART_FLAG_TXE));
		}
	#endif
}
void TaskScreenPowerOn(u8 flag)
{
	DisplayPowerOnEN=0;
	switch(flag)
	{
		case Screen_Power_On: 
			DisplayPowerOnRunTimeStart=1;
			DisplayPowerOnRunTimeCnt=10;
			screen_flag = Screen_Self_Check;
			PrintftoScreen(Power_On,sizeof(Power_On));
			break;
		case Screen_Self_Check:
			screen_flag = Screen_Red_Check;
			DisplayPowerOnRunTimeStart=1;
			DisplayPowerOnRunTimeCnt=3;
			PrintftoScreen(Power_On_Mode,sizeof(Power_On_Mode));
			break;
		case Screen_Data_Init:
			ReadFlashpara();
			if(Displaycontent==CONF_SCREEM)
				screen_flag=Screen_Data_Err;
			else
				screen_flag=Screen_Data_Right;
			DisplayChangeEN=0;
			DisplayPowerOnRunTimeStart=1;
			DisplayPowerOnRunTimeCnt=5;
			PrintftoScreen(Init_Screen,sizeof(Init_Screen));
			break;
		case Screen_Data_Err:
			screen_flag=0;
			DisplayPowerOnRunTimeStart=1;
			DisplayPowerOnRunTimeCnt=5;
			PrintftoScreen(Init_Err,sizeof(Init_Err));
			break;
		case Screen_Data_Right:
			screen_flag=Screen_Check_Finish;
			DisplayPowerOnRunTimeStart=1;
			DisplayPowerOnRunTimeCnt=5;
			PrintftoScreen(Init_Success,sizeof(Init_Success));
			break;
		case Screen_Red_Check:
			DisplayPowerOnRunTimeStart=1;
			DisplayPowerOnRunTimeCnt=5;
			bflagRedBoard_Check=1;
			PrintftoScreen(Ping_Redboard,sizeof(Ping_Redboard));
			break;
		case Screen_Red_Err:
			DisplayPowerOnRunTimeStart=1;
			DisplayPowerOnRunTimeCnt=5;
			PrintftoScreen(Ping_Err,sizeof(Ping_Err));
			break;
		case Screen_Red_Right:
			screen_flag=Screen_Data_Init;
			DisplayPowerOnRunTimeStart=1;
			DisplayPowerOnRunTimeCnt=5;
			PrintftoScreen(Ping_Success,sizeof(Ping_Success));
			break;
		case Screen_Check_Finish:
			screen_flag=Screen_Reset_Ready; 
			DisplayPowerOnRunTimeStart=1;
			DisplayPowerOnRunTimeCnt=5;
			PrintftoScreen(Power_Finish,sizeof(Power_Finish));
			break;
		default:
			break;
	}
}
void PingtoScreen(void)
{
	u8 i;
	for(i=0;i<30;i++)
	{
		USART_SendData(UART5, Ping_Cmd[i]);
		while (!(UART5->SR & USART_FLAG_TXE));
	}
	#ifdef SCREEN_DEBUGE
		for(i=0;i<30;i++)
		{
			USART_SendData(USART1, Ping_Cmd[i]);
			while (!(USART1->SR & USART_FLAG_TXE));
		}
	#endif
}
u8 Character_Transfer(u8 *buf,u8 len)
{
	u8 i,j,tmpbuf[512],transfer_len;
	transfer_len=0;
	for(j=0;j<8;j++)
		tmpbuf[transfer_len++]=buf[j];
	for(j=8;j<len;j++)//ת���ַ�
	{
		if(buf[j]==0x5a)
		{
			tmpbuf[transfer_len++]=0x5b;
			tmpbuf[transfer_len++]=0x02;
			continue;
		}
		if(buf[j]==0x5b)
		{//ת���ַ�
			tmpbuf[transfer_len++]=0x5b;
			tmpbuf[transfer_len++]=0x01;
			continue;
		}
		
		if(buf[j]==0xa5)
		{//ת���ַ�
			tmpbuf[transfer_len++]=0xa6;
			tmpbuf[transfer_len++]=0x02;
			continue;
		}
		if(buf[j]==0xa6)
		{//ת���ַ�
			tmpbuf[transfer_len++]=0xa6;
			tmpbuf[transfer_len++]=0x01;
			continue;
		}
		tmpbuf[transfer_len++] =buf[j];//
	}
	tmpbuf[transfer_len++] =0x5A;//
	for(i=0;i<transfer_len;i++)buf[i]=tmpbuf[i];
	return transfer_len;
}
