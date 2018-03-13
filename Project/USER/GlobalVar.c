/*********************************************************************/
/*公司名称:  北京金水燕禹科技有限公司                              */
/*创 建 人： King              日期：2014-10-31           */
/*修 改 人：               日期：         */ 
/*功能描述：全局变量定义                                      		*/
/*其他说明：                                                         */
/*版    本：V1.0												*/
/**********************************************************************/
#include "sys.h"

u16 Voltage[RTU_NO];
u16 Rain_hour[RTU_NO];
u16 Rain_Lhour[RTU_NO];
u16 Rain_day[RTU_NO];
u16 Rain_Yday[RTU_NO];
u16 Rain_all[RTU_NO];
u16 Rain_Yall[RTU_NO];
u16 Water_Level_Threshold;
u32 Water[RTU_NO]={0};
u32 Water_flow[RTU_NO];


u32 PageAlarm;
u8 Uart5_Recving;
u8 Uart5_recvDone;
u8 RecvFromUART5_Buf[UART5_REC_LEN];
u8 BQSystime[8];
u16 RecvFromUART5_Len;

u8 bflagminute;
u8 bflagfivemin;
u8 bflaghour;
u8 bflagday;
u8 bflaghourstart;
u8 bflagdaystart;

u8 	bflagwakeup;
u32 Wakeup_Reason;
u8 task_cnt;


u8 Uart1_Recving;
u8 Read_sys_para;
u8 BQSystimeERR;
u8 Uart5senddataprority;
u8 Uart3senddataprority;
u8 Uart1_recvDone;
u8 WhetherDirect;
u16 RecvFromUART1_Len;
u8 RecvFromUART1_Buf[USART1_REC_LEN];
u8 SendToCtrl_Buf[USART1_REC_LEN];
u16 SendToCrtl_Len;
u16 UART_7E7EFrameLen;
u16 UART_68BFrameLen;
u16 UART_15BFrameLen;
u16 LenfpcforBQ;
u8 RTUnum;
u8 RTUCurrentHour;
u8 DisplayPageNum;
u8 Displaycontent;
u8 DisplayPagesub; 
u8 DisplayPageno; 
u8 DisplayStayTime; 
u8 DisplayRunTime; 
u8 DisplayChangeEN;
u8 DisplayPowerOnEN;
u8 bflagRedBoard_Check;
u8 DisplayPowerOnRunTime;
u8 DisplayPowerOnRunTimeStart;
u8 DisplayPowerOnRunTimeCnt;
u8 Uart_time_Start;
u8 Uart_time_num;
u8 Uart_serailport_num;
u8 Uart_waketime_num;
u8 bflagsystemstart;
u8 bflagScreenConfigstart;
u32 bflagScreenConfigcnt;
u32 System_Start_time;
u8 Timer_IRQ_flag;
u16 CurrentCMD;
u8 Hardware_check_flag;
u8 Alarm_flag;
u8 Alarm1_flag;
u8 Alarm2_flag;
u8 TIM3_flag;
u8 screen_flag;
u8 RebackPC_time;
u8 Start_display;
u8 BQ_reback_timer;//
u8 RTC_check_already;
u8 RTC_check_finish;
u8 bflag_configlight;
u8 Time_power_enable;
u8 Time_power_on;
u8 Alarm_enable;
u8 Alarm_enable_reflash;
u8 test;
u8 test01;
u8 bflag_firstfivemin;
u8 bflag_eight;
u8 bflag68byte;
u8 bflag15byte;
u8 bflag8byte;

u8 RTUIDbuf[100];



RTUpara_type RTUparas;
RTUparaTest RTUparas_tset[10];
Temp_Humi_value Humi_val,Temp_val;
Radio_data_type Radio_data;
extern u8 YYdevice[105];
extern const u8 Begin_Page[86];//欢迎使用燕禹遥测设备，正在开机，请稍后
extern const u8 Init_Page[64];//设备初始化完成
extern const u8 Fail_Page[77];//页面读取失败，请重新配置页面
extern u8 Clear_screem[47];

#define RTUparalen 10

void initGlobleVar(void)
{
	RecvFromUART1_Len=0;
	Uart1_Recving=0;
	Uart5_Recving=0;
	WhetherDirect=0;
	Read_sys_para=0;
	Uart5senddataprority=0;
	Uart_time_num=0;
	Uart_serailport_num=0;
	Uart_waketime_num=0;
	Uart_time_Start=0;
	Hardware_check_flag=0;
	RebackPC_time=0;
	BQ_reback_timer=0;
	RTC_check_already=0;
	RTC_check_finish=0;
	bflag_configlight=0;
	Time_power_enable=0;
	Time_power_on=1;
	Alarm_flag=0;
	Alarm1_flag=0;
	Alarm2_flag=0;
	TIM3_flag=0;
	bflag68byte=0;
	bflag15byte=0;
	bflag8byte=0;
	RTUparas.RTUID_sum=0;
	bflagminute=0;
	bflagfivemin=0;
	bflaghour=0;
	bflagday=0;
	screen_flag=0;
	bflaghourstart=0;
	bflagdaystart=0;
	task_cnt=0;
	Wakeup_Reason=0;
	bflagwakeup=0;
	System_Start_time=0;
	DisplayPowerOnEN=0;
	DisplayPowerOnRunTime=0;
	DisplayPowerOnRunTimeStart=0;
	DisplayPowerOnRunTimeCnt=0;
	bflagRedBoard_Check=0;
	bflagScreenConfigstart=0;
	bflagScreenConfigcnt=0;
	ReadMENUConfig(); 
	USART_Config(COM1);
	USART_Config(COM5);
	BKP_Init();	
	DoubleAlarmInit();
	OpenAlarm1();
	if(MENUConfig.workmode==WORKMODESTOP)
		OpenAlarm2();
	if(bflagsystemstart==0)
		ReadFlashpara();
}
void ReadFlashpara(void)
{
	u16 i,j,k;
  u8 alltmpbuf[USART1_REC_LEN];
	u8 tmpbuf[22];
	u16 len;
	u8 tempbuf[10];	
	SPI_Flash_Read(alltmpbuf,((u32)RTUparaBASEADDR)<<12,sizeof(RTUparas));
	len=alltmpbuf[0]+(alltmpbuf[1]<<8);
	if(len==0xffff)//没有写入参数
	{
		Displaycontent=CONF_SCREEM; return;
	}
	else
	{
		RTUparas.RTU_sum = alltmpbuf[0];
		if(RTUparas.RTU_sum==0xff)RTUparas.RTU_sum=1;
		j=1;
		for (i=0;i<RTUparas.RTU_sum;i++)//接收到的rtu 参数 默认 从第
		{
				j++;//RTU 序号 省去不要
				for(k = 0; k < 5; k++)
				{
					Hex2Hamming_Code(tempbuf,alltmpbuf[j]);
					if(alltmpbuf[j]==0)
					{
						RTUparas.RTUHMID[i*2][4-k]=0xA5;
						RTUparas.RTUHMID[i*2+1][4-k]=0xA5;
					}
					else
					{
						RTUparas.RTUHMID[i*2][4-k]=tempbuf[0];
						RTUparas.RTUHMID[i*2+1][4-k]=tempbuf[1];
						if(RTUparas.RTUID_sum==0)RTUparas.RTUID_sum=5-k;
					}
					RTUparas.RTUID[i][4-k]= alltmpbuf[j++];
				}
				//j=j+12;//名字 省去不要
				RTUparas.Alarm_Hour_r[i] = alltmpbuf[j++]<<24;
				RTUparas.Alarm_Hour_r[i]|= alltmpbuf[j++]<<16;
				RTUparas.Alarm_Hour_r[i]|= alltmpbuf[j++]<<8;
				RTUparas.Alarm_Hour_r[i]|= alltmpbuf[j++];
				
				RTUparas.Alarm_Day_r[i] = alltmpbuf[j++]<<24;
				RTUparas.Alarm_Day_r[i]|= alltmpbuf[j++]<<16;
				RTUparas.Alarm_Day_r[i]|= alltmpbuf[j++]<<8;
				RTUparas.Alarm_Day_r[i]|= alltmpbuf[j++];
				
				RTUparas.Alarm_Water[i] = alltmpbuf[j++]<<24;
				RTUparas.Alarm_Water[i]|= alltmpbuf[j++]<<16;
				RTUparas.Alarm_Water[i]|= alltmpbuf[j++]<<8;
				RTUparas.Alarm_Water[i]|= alltmpbuf[j++];
				
				RTUparas.DateSt[i] = alltmpbuf[j++];
				RTUparas.MK_value[i] = alltmpbuf[j++];
				
				RTUparas.Basic_Water[i+1]= alltmpbuf[j++]<<8;
				RTUparas.Basic_Water[i+1]|= alltmpbuf[j++];
				RTUparas.Basic_Water[i]= alltmpbuf[j++]<<8;
				RTUparas.Basic_Water[i]|= alltmpbuf[j++];
				
				RTUparas.Basic_Water[i+3]= alltmpbuf[j++]<<8;
				RTUparas.Basic_Water[i+3]|= alltmpbuf[j++];
				RTUparas.Basic_Water[i+2] = alltmpbuf[j++]<<8;
				RTUparas.Basic_Water[i+2]|= alltmpbuf[j++];
				
		}
		for(i=0;i<RTUparas.RTUID_sum;i++)
		{
			//获取上小时雨量
			ReadDATAfromFlash(LRAIN ,tempbuf,i); 
			Radio_data.hrain_l[i]=(tempbuf[0]<<8)|tempbuf[1];
			if(Radio_data.hrain_l[i]==0xffff)Radio_data.hrain_l[i]=0;
			Rain_Lhour[i]=Radio_data.hrain_l[i];
			//获取时段雨量
			ReadDATAfromFlash(HRAIN ,tempbuf,i); 
			Radio_data.hrain[i]=(tempbuf[0]<<8)|tempbuf[1];
			if(Radio_data.hrain[i]==0xffff)Radio_data.hrain[i]=0;
			Rain_hour[i]=Radio_data.hrain[i];
			//获取昨日雨量
			ReadDATAfromFlash(YRAIN ,tempbuf,i); 
			Radio_data.rain_y[i]=(tempbuf[0]<<8)|tempbuf[1];
			if(Radio_data.rain_y[i]==0xffff)Radio_data.rain_y[i]=0;
			Rain_Yday[i]=Radio_data.rain_y[i];
			//获取今日雨量
			ReadDATAfromFlash(TRAIN ,tempbuf,i); 
			Radio_data.rain[i]=(tempbuf[0]<<8)|tempbuf[1];
			if(Radio_data.rain[i]==0xffff)Radio_data.rain[i]=0;
			Rain_day[i]=Radio_data.rain[i];
			//获取累计雨量
			ReadDATAfromFlash(ARAIN ,tempbuf,i); 
			Radio_data.rain_sum[i]=(tempbuf[0]<<8)|tempbuf[1];
			if(Radio_data.rain_sum[i]==0xffff)Radio_data.rain_sum[i]=0;
			Rain_all[i]=Radio_data.rain_sum[i];
			//获取昨日累计雨量 
			ReadDATAfromFlash(YARAIN ,tempbuf,i);  
			Radio_data.rain_sum_y[i]=(tempbuf[0]<<8)|tempbuf[1];
			if(Radio_data.rain_sum_y[i]==0xffff)Radio_data.rain_sum_y[i]=0;
			Rain_Yall[i]=Radio_data.rain_sum_y[i];
			// 获取当前水位
			ReadDATAfromFlash(WATERL ,tempbuf,i); 
			Radio_data.water[i]=(tempbuf[0]<<8)|tempbuf[1];
			if(Radio_data.water[i]==0xffff)Radio_data.water[i]=0;
			Water[i]=Radio_data.water[i];
			// 获取当前流量
			ReadDATAfromFlash(WATER_F ,tempbuf,i); 
			Radio_data.flow[i]=(tempbuf[0]<<8)|tempbuf[1];
			if(Radio_data.flow[i]==0xffff)Radio_data.flow[i]=0;
			Water_flow[i]=Radio_data.flow[i];
			// 获取当前温度
			ReadDATAfromFlash(WATERL ,tempbuf,i);  
			Radio_data.temp[i]=(tempbuf[0]<<8)|tempbuf[1];
			if(Radio_data.temp[i]==0xffff)Radio_data.temp[i]=0;
			// 获取当前湿度
			ReadDATAfromFlash(WATERL ,tempbuf,i); 
			Radio_data.humi[i]=(tempbuf[0]<<8)|tempbuf[1];
			if(Radio_data.humi[i]==0xffff)Radio_data.humi[i]=0;  
			
			// 获取当前湿度
		}
		SPI_Flash_Read(tempbuf,((u32)RTUparaBASEADDR)<<12 ,2); 
		Water_Level_Threshold=(tempbuf[0]<<8)|tempbuf[1];
		if(Water_Level_Threshold==0xffff)Water_Level_Threshold=99;
	}	
	SPI_Flash_Read(tmpbuf,((u32)DISPLAYCONTENT)<<12,1);//读取显示内容
	if((tmpbuf[0]==0xff)||(tmpbuf[0]<1 ||tmpbuf[0]>5))
	{
		Displaycontent=CONF_SCREEM;return;
	}
	else
	{
			Displaycontent = tmpbuf[0];
			if(Displaycontent==NORMAL)
			{
				SPI_Flash_Read(tmpbuf,((u32)SCREENdataBASEADDR)<<12,2);//read the screen page //总页数
				len=tmpbuf[0]+(tmpbuf[1]<<8);
				if((len==0xffff)||(len<20)||(len>0x300))
				{
					Displaycontent=YYDEVICE; return;
				}
				SPI_Flash_Read(alltmpbuf,((u32)SCREENdataBASEADDR)<<12,len+2);
			}
			else if(Displaycontent==WELCOME) //包括等待时间
			{
				SPI_Flash_Read(tmpbuf,((u32)WELCOMEBASEADDR)<<12,2);//read the screen page //总页数
				len=tmpbuf[0]+(tmpbuf[1]<<8);
				if((len==0xffff)||(len<20)||(len>0x300))
				{
					Displaycontent=CONF_SCREEM; return;
				}
				SPI_Flash_Read(alltmpbuf,((u32)WELCOMEBASEADDR)<<12,len+2);
			}
			if(screen_flag==0)
			{
				if(alltmpbuf[len-3]!=0xff)
				{
					DisplayPagesub =alltmpbuf[len-4];//总页数
					DisplayStayTime=alltmpbuf[len-2];//第一页停留时页数	
				}
				else
				{	
					DisplayPagesub =1;//总页数
					DisplayStayTime=10;//第一页停留时页数
					DisplayRunTime=0;
				}
			}
			
	}
	DisplayPageno =0;// 当前显示页
	if(MENUConfig.workmode==WORKMODENORMAL)
	{
		DisplayChangeEN=1;	//刷屏
	}
	else if(Water[0]>=Water_Level_Threshold)
	{
		DisplayChangeEN=1;	//刷屏
		Open_LED_SCREEN();
	}
	else
	{
		Close_LED_SCREEN();
		DisplayChangeEN=0;	//刷屏
	}
}


void display_start(void)
{
	u8 times=0;
	Start_display=3;
	Send_BQ_data_light();
	while(Start_display==3)
	{
		#ifdef WTD
			IWDG_Feed();
		#endif
		times++;
		Display(0,CLEAR_SCREEM);
		delay_ms(500);
		RecDataFroBoardUart1();
		if(times>3)break;
	}
	times=0;
	while(Start_display==2)
	{
		#ifdef WTD
		IWDG_Feed();
		#endif
		times++;
		Display(0,YYDEVICE);
		delay_ms(100);
		RecDataFroBoardUart1();
		if(times>3)break;
	}
}



int Refresh_Flashpara(void)
{
	
	u8 tmp[20],i;
	SPI_Flash_Read(tmp,(u32)DATA_MARKT,sizeof(Radio_data));
	
	{
		for(i=0;i<sizeof(Radio_data);i++)
		{
			if(tmp[i]!=((u8 *)(&Radio_data))[i])
			{
//				 SPI_Flash_Write((u8 *)&Radio_data,(u32)DATA_MARKT,sizeof(Radio_data));
//				 Debug_printf_buf(" Old flash buf is \r\n",tmp,sizeof(Radio_data),'x');
//				 SPI_Flash_Read(tmp,(u32)DATA_MARKT,sizeof(Radio_data));
//				 Debug_printf_buf(" NEW flash buf is \r\n",tmp,sizeof(Radio_data),'x');
				 return 2;
			}
		}
		return 1 ;
	}	
}

