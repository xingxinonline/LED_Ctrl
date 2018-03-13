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
	printf("/************已进入配置模式***************/ \r\n\r\n");
	if(MENUConfig.workmode==WORKMODESTOP)
		printf("当前工作模式:低功耗模式\r\n\r\n"); 
	else
		printf("当前工作模式:正常模式 \r\n\r\n"); 
	printf("低功耗模式唤醒频率:%d分钟\r\n\r\n",MENUConfig.waketime); 
	printf("低功耗模式唤醒持续时间:%d秒\r\n\r\n",MENUConfig.wakestay); 
	printf("当前波特率:%ld\r\n\r\n",(unsigned long)MENUConfig.baudrate); 
	printf("当前时间为："); 
	printf("%ld年%.2d月%.2d日 ",(unsigned long)calendar.w_year+2000,calendar.w_month,calendar.w_date);
	printf("%.2d时%.2d分%.2d秒  \r\n\r\n",calendar.hour,calendar.min,calendar.sec);	
	if(MENUConfig.ledstatus==0)	printf("低功耗系统状态灯状态:关闭\r\n\r\n"); 
	else	printf("低功耗系统状态灯状态:开启\r\n\r\n"); 
	printf("时段雨量更新时间:每小时%d分\r\n\r\n",MENUConfig.hourstart); 
	printf("日雨量更新时间:%d点%d分\r\n\r\n",MENUConfig.daystart,MENUConfig.hourstart); 
	printf("当前区号为:%d\r\n\r\n",(MENUConfig.areacode&0xf0)>>4); 
	printf("1.	重新配置参数 \r\n\r\n"); 
	printf("2.	退出配置模式 \r\n\r\n"); 
}	

void MENU1(void)
{
	printf("/************选择要配置的参数***************/ \r\n\r\n"); 
	printf("1.	工作模式 \r\n\r\n"); 
	printf("2.	低功耗模式唤醒频率 \r\n\r\n"); 
	printf("3.	低功耗模式唤醒持续时间 \r\n\r\n"); 
	printf("4.	波特率 \r\n\r\n");
	printf("5.	配置时间 \r\n\r\n"); 
	printf("6.	状态灯开关 \r\n\r\n"); 
	printf("7.	时段起始时间 \r\n\r\n"); 
	printf("8.	日起始时间 \r\n\r\n"); 
	printf("9.	8字节区号 \r\n\r\n"); 
	printf("A.	返回上一层 \r\n\r\n"); 
	printf("B.	退出配置模式 \r\n\r\n"); 
}		

void MENU1_1(void)
{
	printf("/************工作模式配置***************/ \r\n\r\n"); 
	printf("1.	正常模式 \r\n\r\n"); 
	printf("2.	低功耗模式 \r\n\r\n"); 
	printf("A.	返回上一层 \r\n\r\n"); 
	printf("B.	退出配置模式 \r\n\r\n"); 
}																	
void MENU1_2(void)
{
	printf("/************低功耗模式唤醒频率配置***************/ \r\n\r\n"); 
	printf("1.	1分钟 \r\n\r\n"); 
	printf("2.	60分钟 \r\n\r\n"); 
	printf("A.	返回上一层 \r\n\r\n"); 
	printf("B.	退出配置模式 \r\n\r\n");
}		 

void MENU1_3(void)
{
	printf("/************低功耗模式唤醒持续时间配置***************/ \r\n\r\n"); 
	printf("1.	2秒 \r\n\r\n"); 
	printf("2.	3秒 \r\n\r\n"); 
	printf("3.	5秒 \r\n\r\n"); 
	printf("4.	10秒 \r\n\r\n"); 
	printf("A.	返回上一层 \r\n\r\n"); 
	printf("B.	退出配置模式 \r\n\r\n"); 	
}		
									
void MENU1_4(void)
{
	printf("/************波特率配置***************/ \r\n\r\n"); 
	printf("1.	300 \r\n\r\n"); 
	printf("2.	9600 \r\n\r\n"); 
	printf("3.	19200 \r\n\r\n"); 
	printf("A.	返回上一层 \r\n\r\n"); 
	printf("B.	退出配置模式 \r\n\r\n"); 
}	
void MENU1_5(void)
{
	printf("/************时间配置***************/ \r\n\r\n"); 
	printf("时间输入格式 (ASCII):yyyy-MM-dd HH:mm:ss\r\n\r\n"); 
	printf("时间输入格式 (HEX):32 30 31 38 2D 31 31 2D 32 32 20 31 30 3A 35 36 3A 34 38\r\n\r\n"); 
	printf("A.	返回上一层 \r\n\r\n"); 
	printf("B.	退出配置模式 \r\n\r\n"); 
	printf("请在字符串输入框输入新的时间并发送\r\n\r\n"); 
}
void MENU1_6(void)
{
	printf("/************状态灯开关***************/ \r\n\r\n"); 
	printf("1.	开启低功耗状态灯显示 \r\n\r\n"); 
	printf("2.	关闭低功耗状态灯显示 \r\n\r\n"); 
	printf("A.	返回上一层 \r\n\r\n"); 
	printf("B.	退出配置模式 \r\n\r\n"); 
}	
void MENU1_7(void)
{
	printf("/************时段雨量更新时间***************/ \r\n\r\n"); 
	printf("1.	每小时0分时更新时段雨量 \r\n\r\n"); 
	printf("2.	每小时5分时更新时段雨量 \r\n\r\n"); 
	printf("A.	返回上一层 \r\n\r\n"); 
	printf("B.	退出配置模式 \r\n\r\n"); 
}	
void MENU1_8(void)
{
	printf("/************日雨量更新时间***************/ \r\n\r\n"); 
	printf("1.	08:00 \r\n\r\n"); 
	printf("2.	09:00 \r\n\r\n"); 
	printf("3.	00:00 \r\n\r\n"); 
	printf("A.	返回上一层 \r\n\r\n"); 
	printf("B.	退出配置模式 \r\n\r\n");  
}	
void MENU1_9(void)
{
	printf("/************8字节区号配置***************/ \r\n\r\n");
	printf("Z.	返回上一层 \r\n\r\n"); 
	printf("X.	退出配置模式 \r\n\r\n"); 	
	printf("请在键盘输入0~9或A~F配置站号(0x00~0x0F)\r\n\r\n");  
}	
void MENU1_1_1(void)
{
	SPI_Flash_Write(Config_buf,((u32)LEDCTRL_WORKMODE)<<12,1);
	//工作模式
	if(Config_buf[0]==0x32)MENUConfig.workmode=WORKMODESTOP;
	else MENUConfig.workmode=WORKMODENORMAL;
	printf("/************工作模式配置完成***************/ \r\n\r\n"); 
	if(MENUConfig.workmode==WORKMODENORMAL)
		printf("当前工作模式:正常模式\r\n\r\n"); 
	if(MENUConfig.workmode==WORKMODESTOP)
		printf("当前工作模式:低功耗模式\r\n\r\n"); 
	printf("/*****控制板复位，请重新进入配置*****/ \r\n\r\n\r\n\r\n"); 
	Sys_Soft_Reset();//系统复位
}		
void MENU1_2_1(void)
{
	SPI_Flash_Write(Config_buf,((u32)LEDCTRL_WAKETIME)<<12,1);
	if(Config_buf[0]==0x31)MENUConfig.waketime=1;
	else MENUConfig.waketime=60;
	printf("/************低功耗唤醒频率配置完成***************/ \r\n\r\n"); 
	printf("低功耗模式唤醒频率:%d分钟\r\n\r\n",MENUConfig.waketime); 
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
	printf("/************低功耗模式唤醒持续时间配置完成***************/ \r\n\r\n"); 
	printf("低功耗模式唤醒持续时间:%d秒\r\n\r\n",MENUConfig.wakestay); 
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
	printf("/************波特率配置完成***************/ \r\n\r\n"); 
	printf("当前波特率:%ld\r\n\r\n",(unsigned long)MENUConfig.baudrate);
	printf("/*****控制板复位，请更换波特率为%ld重新进入配置*****/ \r\n\r\n\r\n\r\n",(unsigned long)MENUConfig.baudrate); 
	Sys_Soft_Reset();//系统复位
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
	DS3231_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);  //设置时间
	RTC_check_already=1;
	get_show_time();
	printf("/************时间配置完成***************/ \r\n\r\n"); 
	printf("当前时间为："); 
	printf("%ld年%.2d月%.2d日 ",(unsigned long)calendar.w_year+2000,calendar.w_month,calendar.w_date);
	printf("%.2d时%.2d分%.2d秒  \r\n\r\n",calendar.hour,calendar.min,calendar.sec);	
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
	printf("/************低功耗系统状态灯状态***************/ \r\n\r\n"); 
	if(MENUConfig.ledstatus==0)
		printf("低功耗系统状态灯状态:关闭\r\n\r\n"); 
	else
		printf("低功耗系统状态灯状态:开启\r\n\r\n"); 
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
	printf("/************时段雨量更新时间配置完成***************/ \r\n\r\n"); 
	printf("时段雨量更新时间:每小时%d分\r\n\r\n",MENUConfig.hourstart);
	printf("低功耗小时唤醒时间:每小时%d分\r\n\r\n",MENUConfig.hourstart); 
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
	printf("/************日雨量更新时间配置完成***************/ \r\n\r\n"); 
	printf("日雨量更新时间:%d点%d分\r\n\r\n",MENUConfig.daystart,MENUConfig.hourstart); 
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
		Config_buf[0]-=0x57;//返回上一层
	else Config_buf[0]=0;
	if((Config_buf[0]<=0x0f)||(Config_buf[0]>0x00))
	{
		tmpbuf[0]=Config_buf[0];
	}
	else tmpbuf[0]=0;
	SPI_Flash_Write(tmpbuf,((u32)LEDCTRL_AreaCode)<<12,1);
	Hex2Hamming_Code(tmpbuf,Config_buf[0]);
	MENUConfig.areacode=tmpbuf[1];
	printf("/************8字节区号配置完成***************/ \r\n\r\n"); 
	printf("当前区号为:%d\r\n\r\n",(MENUConfig.areacode&0xf0)>>4); 
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
	printf("是否确认修改参数？Y/N  \r\n\r\n"); 
}		
void MENUEXIT(void)
{
	printf("/************已退出配置模式***************/ \r\n\r\n"); 
	if(MENUConfig.workmode==WORKMODESTOP)
		printf("当前工作模式:低功耗模式\r\n\r\n"); 
	else
		printf("当前工作模式:正常模式\r\n\r\n"); 
	printf("低功耗模式唤醒频率:%d分钟\r\n\r\n",MENUConfig.waketime); 
	printf("低功耗模式唤醒持续时间:%ld秒\r\n\r\n",(unsigned long)MENUConfig.wakestay); 
	printf("当前波特率:%ld\r\n\r\n",(unsigned long)MENUConfig.baudrate); 
	printf("%ld年%.2d月%.2d日 ",(unsigned long)calendar.w_year+2000,calendar.w_month,calendar.w_date);
	printf("%.2d时%.2d分%.2d秒  \r\n\r\n",calendar.hour,calendar.min,calendar.sec);	
	if(MENUConfig.ledstatus==0)	printf("低功耗系统状态灯状态:关闭\r\n\r\n"); 
	else	printf("低功耗系统状态灯状态:开启\r\n\r\n"); 
	printf("时段雨量更新时间:每小时%d分\r\n\r\n",MENUConfig.hourstart); 
	printf("日雨量更新时间:%d点%d分\r\n\r\n",MENUConfig.daystart,MENUConfig.hourstart); 
	printf("当前区号为:%d\r\n\r\n",(MENUConfig.areacode&0xf0)>>4); 
	task_cnt&=~_Config_task;
}		
void MENUERR(void)
{
	printf("/************输入命令错误，请重新输入***************/ \r\n\r\n"); 
}		
void ReadMENUConfig(void)
{
	u8 tmpbuf[2];
	
	//工作模式
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_WORKMODE)<<12,1);
	if(tmpbuf[0]==0x32)
		MENUConfig.workmode=WORKMODESTOP;
	else 
		MENUConfig.workmode=WORKMODENORMAL;
	//低功耗模式唤醒频率
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_WAKETIME)<<12,1);
	if(tmpbuf[0]==0x31)
		MENUConfig.waketime=1;
	else 
		MENUConfig.waketime=60;
	//低功耗模式唤醒持续时间
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_WAKESTAY)<<12,1);
	if(tmpbuf[0]==0x31)
		MENUConfig.wakestay=2;
	else if(tmpbuf[0]==0x32)
		MENUConfig.wakestay=3;
	else if(tmpbuf[0]==0x34)
		MENUConfig.wakestay=10;
	else 
		MENUConfig.wakestay=5;
	//波特率
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_BAUDRATE)<<12,1);
	if(tmpbuf[0]==0x31)
		MENUConfig.baudrate=300;
	else if(tmpbuf[0]==0x32)
		MENUConfig.baudrate=9600;
	else 
		MENUConfig.baudrate=19200;
	//日起始时间
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_DAYSTART)<<12,1);
	if(tmpbuf[0]==0x32)
		MENUConfig.daystart=9;
	else if(tmpbuf[0]==0x33)
		MENUConfig.daystart=0;
	else 
		MENUConfig.daystart=8;
	//时段起始时间
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_HOURSTART)<<12,1);
	if(tmpbuf[0]==0x32)
		MENUConfig.hourstart=5;
	else 
		MENUConfig.hourstart=0;
	//led状态灯开关
	SPI_Flash_Read(tmpbuf,((u32)LEDCTRL_LEDSTATUS)<<12,1);
	if(tmpbuf[0]==0x32)
		MENUConfig.ledstatus=0;
	else 
		MENUConfig.ledstatus=1;
	//8字节区号
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
