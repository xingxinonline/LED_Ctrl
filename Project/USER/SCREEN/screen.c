#include "sys.h" 
//页面内容格式
// Head_Data + Pack_len + Cmd_Config + Area_len + Area_Config + Data_len + Data
const u8 Head_Data[20]={0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0x01,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x02
};//后面两个字节的包长
u8 Pack_len[2]={0x24,0x00};//无数据时包长 
const u8 Cmd_Config[7]={0xA3,0x06,0x01,0x00,0x00,
	0xFF,			/*删除所有动态区*/  
	0x01,			/*区域个数*/   								/*可编辑*/
};	
u8 Area_len[2]={0x1B,0x00};//无数据整个区域长度 
const u8 Area_Config[32]={	0x00,			/*区域类型*/  
							0x00,0x00,		/*x坐标 单位：字节（8个像素点）*/ 								/*可编辑*/
							0x00,0x00,		/*y坐标 单位：像素点*/											/*可编辑*/
							0x60,0x00,		/*区域宽度 单位：字节（8个像素点）*/ 							/*可编辑*/
							0x10,0x00,		/*区域高度 单位：像素点*/
							0x00,			/*动态区域编号*/
							0x00,			/*行间距*/
							0x00,			/*动态区运行模式0-循环显示 1-显示完成后停留在最后一页 
												3-循环超时未更新删除 4-循环超时未更新显示Logo信息*/						/*可编辑*/
							0x00,0x00,		/*动态区超时时间*//*可编辑*/
							0x00,0x00,0x00,	/*保留字节*/
							0x01,			/*是否单行显示 1-单行显示 2-多行显示*/										/*可编辑*/
							0x02,			/*是否自动换行 1-不自动 2-自动*/											/*可编辑*/
							0x03,			/*显示方式 1-静止显示 2-快速打出 3-向左移动 
														4-向右移动 5-向上移动 6-向下移动*/								/*可编辑*/
							0x00,			/*退出方式*/
							0x06,			/*显示速度0-最快 ......0x18最慢*/											/*可编辑*/
							0x00			/*显示停留时间*/															/*可编辑*/
	};
u8 Data_len[4]={0x00,0x00,0x00,0x00};//无数据时区域数据长度  后面是本区域数据
u8 Power_On[]={"欢迎使用金水燕禹公司设备"};
u8 Power_On_Mode[]={"设备已进入上电自检模式"};
u8 Ping_Redboard[]={"正在检测红卡通信"};
u8 Ping_Err[]={"红卡连接失败"};
u8 Ping_Success[]={"红卡连接成功"};
u8 Init_Screen[]={"正在初始化参数"};
u8 Init_Err[]={"参数读取错误，请重新配置参数"};
u8 Init_Success[]={"初始化参数成功"};
u8 Power_Finish[]={"上电自检完成，即将复位"};
u8 RTU_Data_Check[]={"请在10分钟内发送报文"};
u8 RTU_Data_Err[]={"已超时，请检测数据"};
u8 RTU_Data_Success[]={"报文接收成功，正在解析报文"};
u8 RTU_Data_Parse_Err[]={"正在解析报文"};
u8 RTU_Data_Parse_Success[]={"报文解析成功"};
u8 RTU_Data[100];





const u8 Ping_Cmd[30]={0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0x01,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x02,0x05,
				0x00,0xA2,0x00,0x01,0x00,0x00,0x68,0xF8,0x5A};

void PrintftoScreen(u8 *buf,u8 len) 
{
	u8 crc_buf[512],tmpbuf[512],SendtoScreen_len=0,i;
	u16 CRC16;
	len-=1;//sizeof()的长度包括结束符的长度，故长度多了1
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
	for(j=8;j<len;j++)//转义字符
	{
		if(buf[j]==0x5a)
		{
			tmpbuf[transfer_len++]=0x5b;
			tmpbuf[transfer_len++]=0x02;
			continue;
		}
		if(buf[j]==0x5b)
		{//转义字符
			tmpbuf[transfer_len++]=0x5b;
			tmpbuf[transfer_len++]=0x01;
			continue;
		}
		
		if(buf[j]==0xa5)
		{//转义字符
			tmpbuf[transfer_len++]=0xa6;
			tmpbuf[transfer_len++]=0x02;
			continue;
		}
		if(buf[j]==0xa6)
		{//转义字符
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
