#include "sys.h"


MENUConfig_type MENUConfig;
u8 bflag_menu=0xff;
u8 bflag_configStart=0;
u8 Config_buf[20];
void MENU_START(void)
{
	if(bflag_configStart)
	{
		bflag_configStart=0;
			switch(bflag_menu) 
		{
			case MENU_0:
				MENU0(); 
			break;
			case MENU_1:
				MENU1();
			break;
			case MENU_11: 
				MENU1_1();
			break;
			case MENU_12:
				MENU1_2();
			break;
			case MENU_13:
				MENU1_3();
			break;
			case MENU_14:
				MENU1_4();
			break;
			case MENU_15:
				MENU1_5();
			break;
			case MENU_16:
				MENU1_6();
			break;
			case MENU_17:
				MENU1_7();
			break;
			case MENU_18:
				MENU1_8();
			break;
			case MENU_19:
				MENU1_9();
			break;
			case MENU_111:
				MENU1_1_1();
			break;
			case MENU_121:
				MENU1_2_1();
			break;
			case MENU_131:
				MENU1_3_1();
			break;
			case MENU_141:
				MENU1_4_1();
			break;
			case MENU_151:
				MENU1_5_1();
			break;
			case MENU_161:
				MENU1_6_1();
			break;
			case MENU_171:
				MENU1_7_1();
			break;
			case MENU_181:
				MENU1_8_1();
			break;
			case MENU_191:
				MENU1_9_1();
			break;
			case MENU_SURE:
				MENUCONFGSURE(); 
			break; 
			case MENU_EXIT:
				MENUEXIT(); 
			break;
			case MENU_ERR:
				MENUERR();
			break;
		}
	}

}

void MENU0(void)
{
	printf("/************�ѽ�������ģʽ***************/ \r\n\r\n");
	if(MENUConfig.workmode==WORKMODESTOP)
		printf("��ǰ����ģʽ:�͹���ģʽ\r\n\r\n"); 
	else
		printf("��ǰ����ģʽ:����ģʽ \r\n\r\n"); 
	printf("�͹���ģʽ����Ƶ��:%d����\r\n\r\n",MENUConfig.waketime); 
	printf("�͹���ģʽ���ѳ���ʱ��:%d��\r\n\r\n",MENUConfig.wakestay); 
	printf("��ǰ������:%ld\r\n\r\n",(unsigned long)MENUConfig.baudrate); 
	printf("��ǰʱ��Ϊ��"); 
	printf("%ld��%.2d��%.2d�� ",(unsigned long)calendar.w_year+2000,calendar.w_month,calendar.w_date);
	printf("%.2dʱ%.2d��%.2d��  \r\n\r\n",calendar.hour,calendar.min,calendar.sec);	
	if(MENUConfig.ledstatus==0)	printf("�͹���ϵͳ״̬��״̬:�ر�\r\n\r\n"); 
	else	printf("�͹���ϵͳ״̬��״̬:����\r\n\r\n"); 
	printf("ʱ����������ʱ��:ÿСʱ%d��\r\n\r\n",MENUConfig.hourstart); 
	printf("����������ʱ��:%d��%d��\r\n\r\n",MENUConfig.daystart,MENUConfig.hourstart); 
	printf("��ǰ����Ϊ:%d\r\n\r\n",(MENUConfig.areacode&0xf0)>>4); 
	printf("1.	�������ò��� \r\n\r\n"); 
	printf("2.	�˳�����ģʽ \r\n\r\n"); 
}	

void MENU1(void)
{
	printf("/************ѡ��Ҫ���õĲ���***************/ \r\n\r\n"); 
	printf("1.	����ģʽ \r\n\r\n"); 
	printf("2.	�͹���ģʽ����Ƶ�� \r\n\r\n"); 
	printf("3.	�͹���ģʽ���ѳ���ʱ�� \r\n\r\n"); 
	printf("4.	������ \r\n\r\n");
	printf("5.	����ʱ�� \r\n\r\n"); 
	printf("6.	״̬�ƿ��� \r\n\r\n"); 
	printf("7.	ʱ����ʼʱ�� \r\n\r\n"); 
	printf("8.	����ʼʱ�� \r\n\r\n"); 
	printf("9.	8�ֽ����� \r\n\r\n"); 
	printf("A.	������һ�� \r\n\r\n"); 
	printf("B.	�˳�����ģʽ \r\n\r\n"); 
}		

void MENU1_1(void)
{
	printf("/************����ģʽ����***************/ \r\n\r\n"); 
	printf("1.	����ģʽ \r\n\r\n"); 
	printf("2.	�͹���ģʽ \r\n\r\n"); 
	printf("A.	������һ�� \r\n\r\n"); 
	printf("B.	�˳�����ģʽ \r\n\r\n"); 
}																	
void MENU1_2(void)
{
	printf("/************�͹���ģʽ����Ƶ������***************/ \r\n\r\n"); 
	printf("1.	1���� \r\n\r\n"); 
	printf("2.	60���� \r\n\r\n"); 
	printf("A.	������һ�� \r\n\r\n"); 
	printf("B.	�˳�����ģʽ \r\n\r\n");
}		 

void MENU1_3(void)
{
	printf("/************�͹���ģʽ���ѳ���ʱ������***************/ \r\n\r\n"); 
	printf("1.	2�� \r\n\r\n"); 
	printf("2.	3�� \r\n\r\n"); 
	printf("3.	5�� \r\n\r\n"); 
	printf("4.	10�� \r\n\r\n"); 
	printf("A.	������һ�� \r\n\r\n"); 
	printf("B.	�˳�����ģʽ \r\n\r\n"); 	
}		
									
void MENU1_4(void)
{
	printf("/************����������***************/ \r\n\r\n"); 
	printf("1.	300 \r\n\r\n"); 
	printf("2.	9600 \r\n\r\n"); 
	printf("3.	19200 \r\n\r\n"); 
	printf("A.	������һ�� \r\n\r\n"); 
	printf("B.	�˳�����ģʽ \r\n\r\n"); 
}	
void MENU1_5(void)
{
	printf("/************ʱ������***************/ \r\n\r\n"); 
	printf("ʱ�������ʽ (ASCII):yyyy-MM-dd HH:mm:ss\r\n\r\n"); 
	printf("ʱ�������ʽ (HEX):32 30 31 38 2D 31 31 2D 32 32 20 31 30 3A 35 36 3A 34 38\r\n\r\n"); 
	printf("A.	������һ�� \r\n\r\n"); 
	printf("B.	�˳�����ģʽ \r\n\r\n"); 
	printf("�����ַ�������������µ�ʱ�䲢����\r\n\r\n"); 
}
void MENU1_6(void)
{
	printf("/************״̬�ƿ���***************/ \r\n\r\n"); 
	printf("1.	�����͹���״̬����ʾ \r\n\r\n"); 
	printf("2.	�رյ͹���״̬����ʾ \r\n\r\n"); 
	printf("A.	������һ�� \r\n\r\n"); 
	printf("B.	�˳�����ģʽ \r\n\r\n"); 
}	
void MENU1_7(void)
{
	printf("/************ʱ����������ʱ��***************/ \r\n\r\n"); 
	printf("1.	ÿСʱ0��ʱ����ʱ������ \r\n\r\n"); 
	printf("2.	ÿСʱ5��ʱ����ʱ������ \r\n\r\n"); 
	printf("A.	������һ�� \r\n\r\n"); 
	printf("B.	�˳�����ģʽ \r\n\r\n"); 
}	
void MENU1_8(void)
{
	printf("/************����������ʱ��***************/ \r\n\r\n"); 
	printf("1.	08:00 \r\n\r\n"); 
	printf("2.	09:00 \r\n\r\n"); 
	printf("3.	00:00 \r\n\r\n"); 
	printf("A.	������һ�� \r\n\r\n"); 
	printf("B.	�˳�����ģʽ \r\n\r\n");  
}	
void MENU1_9(void)
{
	printf("/************8�ֽ���������***************/ \r\n\r\n");
	printf("Z.	������һ�� \r\n\r\n"); 
	printf("X.	�˳�����ģʽ \r\n\r\n"); 	
	printf("���ڼ�������0~9��A~F����վ��(0x00~0x0F)\r\n\r\n");  
}	
void MENU1_1_1(void)
{
	SPI_Flash_Write(Config_buf,((u32)LEDCTRL_WORKMODE)<<12,1);
	//����ģʽ
	if(Config_buf[0]==0x32)MENUConfig.workmode=WORKMODESTOP;
	else MENUConfig.workmode=WORKMODENORMAL;
	printf("/************����ģʽ�������***************/ \r\n\r\n"); 
	if(MENUConfig.workmode==WORKMODENORMAL)
		printf("��ǰ����ģʽ:����ģʽ\r\n\r\n"); 
	if(MENUConfig.workmode==WORKMODESTOP)
		printf("��ǰ����ģʽ:�͹���ģʽ\r\n\r\n"); 
	printf("/*****���ư帴λ�������½�������*****/ \r\n\r\n\r\n\r\n"); 
	Sys_Soft_Reset();//ϵͳ��λ
}		
void MENU1_2_1(void)
{
	SPI_Flash_Write(Config_buf,((u32)LEDCTRL_WAKETIME)<<12,1);
	if(Config_buf[0]==0x31)MENUConfig.waketime=1;
	else MENUConfig.waketime=60;
	printf("/************�͹��Ļ���Ƶ���������***************/ \r\n\r\n"); 
	printf("�͹���ģʽ����Ƶ��:%d����\r\n\r\n",MENUConfig.waketime); 
	Uart1_Recving=0x31;
	bflag_menu=MENU_0;
	Uart_time_Start=0;
	Uart_time_num=0;
	RecvFromUART1_Len=0;
	bflag_configStart=1;
}		
void MENU1_3_1(void)
{
	SPI_Flash_Write(Config_buf,((u32)LEDCTRL_WAKESTAY)<<12,1);
	if(Config_buf[0]==0x31)MENUConfig.wakestay=2;
	else if(Config_buf[0]==0x32)MENUConfig.wakestay=3;
	else if(Config_buf[0]==0x34)MENUConfig.wakestay=10;
	else MENUConfig.wakestay=5;	
	printf("/************�͹���ģʽ���ѳ���ʱ���������***************/ \r\n\r\n"); 
	printf("�͹���ģʽ���ѳ���ʱ��:%d��\r\n\r\n",MENUConfig.wakestay); 
	Uart1_Recving=0x31;
	bflag_menu=MENU_0;
	Uart_time_Start=0;
	Uart_time_num=0;
	RecvFromUART1_Len=0;
	bflag_configStart=1;
}		
void MENU1_4_1(void)
{
	SPI_Flash_Write(Config_buf,((u32)LEDCTRL_BAUDRATE)<<12,1);
	if(Config_buf[0]==0x31)MENUConfig.baudrate=300;
	else if(Config_buf[0]==0x32)MENUConfig.baudrate=9600;
	else MENUConfig.baudrate=19200;
	printf("/************�������������***************/ \r\n\r\n"); 
	printf("��ǰ������:%ld\r\n\r\n",(unsigned long)MENUConfig.baudrate);
	printf("/*****���ư帴λ�������������Ϊ%ld���½�������*****/ \r\n\r\n\r\n\r\n",(unsigned long)MENUConfig.baudrate); 
	Sys_Soft_Reset();//ϵͳ��λ
}		
void MENU1_5_1(void)
{
		u8 i;
	for(i=0;i<19;i++)
	{
		if((Config_buf[i]>=0x30)&&(Config_buf[i]<=0x39))
			Config_buf[i]-=0x30;
	}
	calendar.w_year=Config_buf[2]*10+Config_buf[3];//year L 
	calendar.w_month=Config_buf[5]*10+Config_buf[6];//month
	calendar.w_date=Config_buf[8]*10+Config_buf[9];//date
	calendar.hour=Config_buf[11]*10+Config_buf[12];//hour
	calendar.min=Config_buf[14]*10+Config_buf[15];//min
	calendar.sec=Config_buf[17]*10+Config_buf[18];//sec
	DS3231_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);  //����ʱ��
	RTC_check_already=1;
	get_show_time();
	printf("/************ʱ���������***************/ \r\n\r\n"); 
	printf("��ǰʱ��Ϊ��"); 
	printf("%ld��%.2d��%.2d�� ",(unsigned long)calendar.w_year+2000,calendar.w_month,calendar.w_date);
	printf("%.2dʱ%.2d��%.2d��  \r\n\r\n",calendar.hour,calendar.min,calendar.sec);	
	Uart1_Recving=0x31;
	bflag_menu=MENU_0;
	Uart_time_Start=0;
	Uart_time_num=0;
	RecvFromUART1_Len=0;
	bflag_configStart=1;
}
void MENU1_6_1(void)
{
	SPI_Flash_Write(Config_buf,((u32)LEDCTRL_LEDSTATUS)<<12,1);
	if(Config_buf[0]==0x32)
		MENUConfig.ledstatus=0;
	else
		MENUConfig.ledstatus=1;
	printf("/************�͹���ϵͳ״̬��״̬***************/ \r\n\r\n"); 
	if(MENUConfig.ledstatus==0)
		printf("�͹���ϵͳ״̬��״̬:�ر�\r\n\r\n"); 
	else
		printf("�͹���ϵͳ״̬��״̬:����\r\n\r\n"); 
	Uart1_Recving=0x31;
	bflag_menu=MENU_0;
	Uart_time_Start=0;
	Uart_time_num=0;
	RecvFromUART1_Len=0;
	bflag_configStart=1;
}		
void MENU1_7_1(void)
{
	SPI_Flash_Write(Config_buf,((u32)LEDCTRL_HOURSTART)<<12,1);
	if(Config_buf[0]==0x32)
		MENUConfig.hourstart=5;
	else
		MENUConfig.hourstart=0;
	Alarm2Init(MENUConfig.waketime); 
	printf("/************ʱ����������ʱ���������***************/ \r\n\r\n"); 
	printf("ʱ����������ʱ��:ÿСʱ%d��\r\n\r\n",MENUConfig.hourstart);
	printf("�͹���Сʱ����ʱ��:ÿСʱ%d��\r\n\r\n",MENUConfig.hourstart); 
	Uart1_Recving=0x31;
	bflag_menu=MENU_0;
	Uart_time_Start=0;
	Uart_time_num=0;
	RecvFromUART1_Len=0;
	bflag_configStart=1;
	
}		
void MENU1_8_1(void)
{
	SPI_Flash_Write(Config_buf,((u32)LEDCTRL_DAYSTART)<<12,1);
	if(Config_buf[0]==0x32)MENUConfig.daystart=9;
	else if(Config_buf[0]==0x33)MENUConfig.daystart=0;
	else MENUConfig.daystart=8;
	printf("/************����������ʱ���������***************/ \r\n\r\n"); 
	printf("����������ʱ��:%d��%d��\r\n\r\n",MENUConfig.daystart,MENUConfig.hourstart); 
	Uart1_Recving=0x31;
	bflag_menu=MENU_0;
	Uart_time_Start=0;
	Uart_time_num=0;
	RecvFromUART1_Len=0;
	bflag_configStart=1;
}		
void MENU1_9_1(void)
{
	u8 tmpbuf[2];
	if((Config_buf[0]>='0')&&(Config_buf[0]<='9'))
		Config_buf[0]-=0x30;
		
	else if((Config_buf[0]>='A')&&(Config_buf[0]<='F'))
		Config_buf[0]-=0x37;
		 
	else if((Config_buf[0]>='a')&&(Config_buf[0]<='f'))
		Config_buf[0]-=0x57;//������һ��
	else Config_buf[0]=0;
	if((Config_buf[0]<=0x0f)||(Config_buf[0]>0x00))
	{
		tmpbuf[0]=Config_buf[0];
	}
	else tmpbuf[0]=0;
	SPI_Flash_Write(tmpbuf,((u32)LEDCTRL_AreaCode)<<12,1);
	Hex2Hamming_Code(tmpbuf,Config_buf[0]);
	MENUConfig.areacode=tmpbuf[1];
	printf("/************8�ֽ������������***************/ \r\n\r\n"); 
	printf("��ǰ����Ϊ:%d\r\n\r\n",(MENUConfig.areacode&0xf0)>>4); 
	Uart1_Recving=0x31;
	bflag_menu=MENU_0;
	Uart_time_Start=0;
	Uart_time_num=0;
	RecvFromUART1_Len=0;
	bflag_configStart=1;
}		
void MENUCONFGSURE(void) 
{
	u8 i;
	for(i=0;i<20;i++)
	{
			Config_buf[i]=RecvFromUART1_Buf[i];
	}
	printf("�Ƿ�ȷ���޸Ĳ�����Y/N  \r\n\r\n"); 
}		
void MENUEXIT(void)
{
	printf("/************���˳�����ģʽ***************/ \r\n\r\n"); 
	if(MENUConfig.workmode==WORKMODESTOP)
		printf("��ǰ����ģʽ:�͹���ģʽ\r\n\r\n"); 
	else
		printf("��ǰ����ģʽ:����ģʽ\r\n\r\n"); 
	printf("�͹���ģʽ����Ƶ��:%d����\r\n\r\n",MENUConfig.waketime); 
	printf("�͹���ģʽ���ѳ���ʱ��:%ld��\r\n\r\n",(unsigned long)MENUConfig.wakestay); 
	printf("��ǰ������:%ld\r\n\r\n",(unsigned long)MENUConfig.baudrate); 
	printf("%ld��%.2d��%.2d�� ",(unsigned long)calendar.w_year+2000,calendar.w_month,calendar.w_date);
	printf("%.2dʱ%.2d��%.2d��  \r\n\r\n",calendar.hour,calendar.min,calendar.sec);	
	if(MENUConfig.ledstatus==0)	printf("�͹���ϵͳ״̬��״̬:�ر�\r\n\r\n"); 
	else	printf("�͹���ϵͳ״̬��״̬:����\r\n\r\n"); 
	printf("ʱ����������ʱ��:ÿСʱ%d��\r\n\r\n",MENUConfig.hourstart); 
	printf("����������ʱ��:%d��%d��\r\n\r\n",MENUConfig.daystart,MENUConfig.hourstart); 
	printf("��ǰ����Ϊ:%d\r\n\r\n",(MENUConfig.areacode&0xf0)>>4); 
	task_cnt&=~_Config_task;
}		
void MENUERR(void)
{
	printf("/************���������������������***************/ \r\n\r\n"); 
}		
void ReadMENUConfig(void)
{
	u8 tmpbuf[2];
	
	//����ģʽ
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_WORKMODE)<<12,1);
	if(tmpbuf[0]==0x32)
		MENUConfig.workmode=WORKMODESTOP;
	else 
		MENUConfig.workmode=WORKMODENORMAL;
	//�͹���ģʽ����Ƶ��
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_WAKETIME)<<12,1);
	if(tmpbuf[0]==0x31)
		MENUConfig.waketime=1;
	else 
		MENUConfig.waketime=60;
	//�͹���ģʽ���ѳ���ʱ��
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_WAKESTAY)<<12,1);
	if(tmpbuf[0]==0x31)
		MENUConfig.wakestay=2;
	else if(tmpbuf[0]==0x32)
		MENUConfig.wakestay=3;
	else if(tmpbuf[0]==0x34)
		MENUConfig.wakestay=10;
	else 
		MENUConfig.wakestay=5;
	//������
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_BAUDRATE)<<12,1);
	if(tmpbuf[0]==0x31)
		MENUConfig.baudrate=300;
	else if(tmpbuf[0]==0x32)
		MENUConfig.baudrate=9600;
	else 
		MENUConfig.baudrate=19200;
	//����ʼʱ��
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_DAYSTART)<<12,1);
	if(tmpbuf[0]==0x32)
		MENUConfig.daystart=9;
	else if(tmpbuf[0]==0x33)
		MENUConfig.daystart=0;
	else 
		MENUConfig.daystart=8;
	//ʱ����ʼʱ��
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_HOURSTART)<<12,1);
	if(tmpbuf[0]==0x32)
		MENUConfig.hourstart=5;
	else 
		MENUConfig.hourstart=0;
	//led״̬�ƿ���
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_LEDSTATUS)<<12,1);
	if(tmpbuf[0]==0x32)
		MENUConfig.ledstatus=0;
	else 
		MENUConfig.ledstatus=1;
	//8�ֽ�����
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_AreaCode)<<12,1);
	if(tmpbuf[0]==0xff)
		MENUConfig.areacode=0;
	else
	{
		MENUConfig.areacode=tmpbuf[0];
	}
	Hex2Hamming_Code(tmpbuf,MENUConfig.areacode);
	MENUConfig.areacode=tmpbuf[1];
}
