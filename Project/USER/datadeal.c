#include "sys.h"

//68byte
u8 Rebdatastate;
u8 Reback_en;
u8 C_stationaddr1;
u8 Function;
u8 C_rtuaddr2;
u8 Rebdatabuf[14];
extern RTUpara_type RTUparas;//
extern Radio_data_type  Radio_data;
extern Temp_Humi_value Humi_val,Temp_val;
const u8 Send_frame[20]={
	0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0x01,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x02
};
const u8 Send_time[30]={
	0x01,0x00,0x00,0x80 ,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x02,0x0D,0x00,0xA2,0x03,0x01,0x08,0x00}
;
//A5 A5 A5 A5 A5 A5 A5 A5 01 00 00 80 00 00 00 00 00 00 FE 02 0D 00 A2 03 01 08 00 13 20 01 25 11 17 26
//05 B0 3F 5A
const u8 Reback_frame[20]={
	0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x02
};	
const u8 sysparcmd[5]={0xa1 ,0x02, 0x01, 0x00,0x00};
//a5 a5 a5 a5 a5 a5 a5 a5	  01 00 00 80 00 00 00 00 00 00 fe 02 05 00 a2 00 01 00 00 68 f8 5a //ping
//A5 A5 A5 A5 A5 A5 A5 A5 01 00 00 80 00 00 00 00 00 00 FE 02 05 00 A1 02 01 00 00 2D 40 5A

const u8 sysparcmdall[30]={0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0x01,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,
0x00,0xFE,0x02,0x05,0x00,0xA1,0x02,0x01,0x00,0x00,0x2D,0x40,0x5A};
const u8 deleteall[32]={0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0x01,0x00,0x00,0x80,0x00,0x00,0x00,0x00
 ,0x00,0x00,0xfe,0x02,0x07,0x00,0xa3,0x06,0x01,0x02,0x00,0xff,0x00,0x67,0xcc,0x5a
};
const u8 Send_light[24]={
	0x01,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x02,0x07,0x00,0xA3,0x02,0x01,0x02,0x00,0x01,0x0C,0x26,0x2D,0x5A 

};
const u8 Reback2PC[30]={0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xfe,0x02,0x05,0x00,0xa0,0x00,0x00,0x00,0x00,0x64,0xdc,0x5a};
const u8 YYdevice[105]={0x67,0x00,0xa3,0x06,0x01,0x62,0x00,0x00,0x02,0x38,0x00,0x00,0x00,0x00,0x08,0x00
,0x14,0x00,0x48,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x02,0x02,0x01,0x00,0x00,0x0a,0x1d,0x00,0x00
,0x00,0x5c,0x46,0x4f,0x30,0x30,0x31,0x5c,0x43,0x31,0xbb,0xb6,0xd3,0xad,0xca,0xb9,0xd3,0xc3,0xd1,0xe0,0xd3
,0xed,0xd2,0xa3,0xb2,0xe2,0xc9,0xe8,0xb1,0xb8,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x00,0x08,0x00,0x01
,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x02,0x02,0x01,0x00,0x00,0x0a,0x09,0x00,0x00,0x00,0x5c,0x46,0x4f,0x30
,0x30,0x31,0x5c,0x43,0x31
};//ª∂”≠ π”√—‡”Ì“£≤‚…Ë±∏
const u8 Begin_Page[86]={0x54,0x00,0xA3,0x06,0x01,0x00,0x00,0xFF,0x01,0x45,0x00,0x00,0x00,0x00,0x00,0x00,0x60,
0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x00,0x0C,0x05,
0x2A,0x00,0x00,0x00,0x5C,0x46,0x4F,0x30,0x30,0x30,0x20,0xBB,0xB6,0xD3,0xAD,0xCA,0xB9,
0xD3,0xC3,0xD1,0xE0,0xD3,0xED,0xC9,0xE8,0xB1,0xB8,0x2C,0xD5,0xFD,0xD4,0xDA,0xBF,
0xAA,0xBB,0xFA,0x2C,0xC7,0xEB,0xC9,0xD4,0xBA,0xF3,0x2E,0x2E,0x2E

};//ª∂”≠ π”√—‡”Ì“£≤‚…Ë±∏£¨’˝‘⁄ø™ª˙£¨«Î…‘∫Û
const u8 Init_Page[64]={0x3E,0x00,0xA3,0x06,0x01,0x00,0x00,0xFF,0x01,0x2F,0x00,0x00,0x00,0x00,0x00,0x00,0x60,
0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x02,0x00,0x01,0x02,
0x14,0x00,0x00,0x00,0x5C,0x46,0x4F,0x30,0x30,0x30,0xC9,0xE8,0xB1,0xB8,0xB3,0xF5,0xCA,
0xBC,0xBB,0xAF,0xCD,0xEA,0xB3,0xC9

};//…Ë±∏≥ı ºªØÕÍ≥…
const u8 Fail_Page[77]={0x4B,0x00,0xA3,0x06,0x01,0x00,0x00,0xFF,0x01,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x60,
0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x01,0xFF,
0x21,0x00,0x00,0x00,0x5C,0x46,0x4F,0x30,0x30,0x30,0xD2,0xB3,0xC3,0xE6,0xB6,0xC1,0xC8,
0xA1,0xCA,0xA7,0xB0,0xDC,0x2C,0xC7,0xEB,0xD6,0xD8,0xD0,0xC2,0xC5,0xE4,0xD6,0xC3,
0xD2,0xB3,0xC3,0xE6
};//“≥√Ê∂¡»° ß∞‹£¨«Î÷ÿ–¬≈‰÷√“≥√Ê
const u8 Clear_screem[47]={0x2d,0x00,0xa3,0x06,0x01,0x28,0x00,0x00,0x01,0x24,0x00,0x00,0x00,0x00,0x00,0x00
,0x60,0x00,0x40,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x02,0x02,0x01,0x00,0x00,0x0a,0x09,0x00,0x00,
0x00,0x5c,0x46,0x4f,0x30,0x30,0x30,0x5c,0x43,0x31
};//«Â∆¡
const u8 Version[]={"Ver1.3_2015-1-1301"};



//void Delay(__IO u32 nCount)
//{
//	for(; nCount != 0; nCount--);
//}
void  Verision(void)
{
	u8 i,j;
	u8 tmpbuf[52],buf[60];
	u16 CRC16;

		for(i=0;i<20;i++)
		{
			buf[i] = Reback_frame[i];	
		}
		buf[i++]=22;//Version_len
		buf[i++]=0x00;
		buf[i++]=0xb2;//Version_len
		buf[i++]=0x01;
		buf[i++]=0x00;//
		for(j=0;j<17;j++)
		{
			buf[i++] = Version[j];	
		}
		buf[i++]=0x00;//
		buf[i++]=0x00;//
	for(j=8;j<(i);j++)//»•µÙ∞¸Õ∑µƒ ˝æ›–Ë“™crc–£—Èµƒ≤ø∑÷ ¥”asc_buf01[0] µƒœ¬“ª∏ˆœÚœ¬ ˝ µΩ 8∏ˆA5 Œ™ 58∏ˆ ˝æ›
	{
		tmpbuf[j-8] =buf[j] ;//
	}
	CRC16=crc16_ctrl(tmpbuf,(i-8));
	buf[i++] = CRC16;
	buf[i++] = CRC16>>8;//CRC
	buf[i++] = 0x5A;
	for(j=0;j<i;j++)
	{
		USART_SendData(USART1,buf[j]);
		while (!(USART1->SR & USART_FLAG_TXE));
	}
}

	void RebackPC(u16 curentcmd)
	{
		u8 i,j;
		u8	tmpbuf[30],tmptembuf[30];
		u16 CRC16;
		for(i=0;i<27;i++)
		{
			if(i==22){
				tmpbuf[i]=curentcmd>>8;continue;}
			if(i==23){
				tmpbuf[i]=curentcmd;continue;}
			tmpbuf[i]=Reback2PC[i];
		}
		
		for(j=8;j<27;j++)//»•µÙ∞¸Õ∑µƒ ˝æ›–Ë“™crc–£—Èµƒ≤ø∑÷ ¥”asc_buf01[0] µƒœ¬“ª∏ˆœÚœ¬ ˝ µΩ 8∏ˆA5 Œ™ 58∏ˆ ˝æ›
		{
			tmptembuf[j-8] =tmpbuf[j] ;//
		}
		CRC16=crc16_ctrl(tmptembuf,(27-8));
		tmpbuf[i++] = CRC16;
		tmpbuf[i++] = CRC16>>8;//CRC
		tmpbuf[i++]=0x5a;
		for(i=0;i<30;i++)
		{
			USART_SendData(USART1,tmpbuf[i]);
			while (!(USART1->SR & USART_FLAG_TXE));
		}
	}
	
	void Send_BQ_data_dir()
	{
		u16 i;
		if(RecvFromUART1_Len>512)return;
			for (i=0;i<8;i++)
			{
				USART_SendData(UART5, 0xa5);
				while (!(UART5->SR & USART_FLAG_TXE));
			}
			for (i=0;i<RecvFromUART1_Len+12;i++)
			{
				USART_SendData(UART5, RecvFromUART1_Buf[i]);
				while (!(UART5->SR & USART_FLAG_TXE));
			}
			#ifdef DEBUGE 
			Debug_printf("\r\n DIRECTTOBQ recived \r\n");
			#endif
		
	}
	void Send_BQ_time_dir(u8 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
	{
		unsigned int   CRC_DATA ;
		u16 i;
		u8 tmpbuf[30],weekday;
		weekday=RTC_Get_Week(syear+2000,smon,sday);
		for(i=0;i<19;i++)
		{
			tmpbuf[i]=Send_time[i];
		}
		tmpbuf[19]=hextobcd(syear);
		tmpbuf[20]=0x20;
		tmpbuf[21]=hextobcd(smon);
		tmpbuf[22]=hextobcd(sday);
		tmpbuf[23]=hextobcd(hour);
		tmpbuf[24]=hextobcd(min);
		tmpbuf[25]=hextobcd(sec);
		tmpbuf[26]=hextobcd(weekday);
		CRC_DATA = crc16_ctrl(tmpbuf,27);
		tmpbuf[27]=CRC_DATA;
		tmpbuf[28]=CRC_DATA>>8;
		tmpbuf[29]=0x5A;
		for (i=0;i<8;i++)
		{
			USART_SendData(UART5, 0xa5);
			while (!(UART5->SR & USART_FLAG_TXE));
		}
		for (i=0;i<30;i++)
		{
			USART_SendData(UART5, tmpbuf[i]);
			while (!(UART5->SR & USART_FLAG_TXE));
		}
		#ifdef DEBUGE 
		Debug_printf("\r\n DIRECTTOBQ recived \r\n");
		#endif
	}
void PC_BQ_data_deal(void)
{
	u8   page;
	unsigned int   CRC_DATA   , crc,i,j,k;
	u16 tmp;
	u8	tmpbuf[6];
	u8	buf[USART1_REC_LEN];//for  test
	Time_Power_TypeDef *q;
	CRC_DATA = crc16_ctrl(RecvFromUART1_Buf,RecvFromUART1_Len-3);
	test=17;
	crc = ((RecvFromUART1_Buf[RecvFromUART1_Len-2])<<8)|(RecvFromUART1_Buf[RecvFromUART1_Len-3]);
	if (CRC_DATA == crc)//crc–£—È
	{
		#ifdef WTD
		IWDG_Feed();
		#endif
		CurrentCMD=((RecvFromUART1_Buf[14])<<8)|(RecvFromUART1_Buf[15]);
		RecvFromUART1_Len=RecvFromUART1_Len-12;
	
		for(i=0;i<RecvFromUART1_Len;i++)
		{
			buf[i]=RecvFromUART1_Buf[i+12];
		}
		tmp= (buf[2] << 8) +buf[3];//µ⁄¡„ µ⁄“ªŒª¥Ê¥¢ ˝æ›≥§∂» µ⁄∂˛µ⁄»˝Œª ¥Ê¥¢√¸¡Ó◊÷
		RebackPC_time=1;
		switch (tmp)
		{
		case PING:
			RebackPC_time=0;
			RebackPC(CurrentCMD);
			switch (buf[5])
			{
				
			case 1://wil send commond
				WhetherDirect=1;
				DisplayChangeEN=2;
				break;
			case 2://will send diaplay
				WhetherDirect=4;
				DisplayChangeEN=4;
				break;
			case 3://will send rtu paras
				WhetherDirect=0;
				DisplayChangeEN=8;
				break;
			case 4://welcome
				Displaycontent=WELCOME;	
				DisplayChangeEN=1;
				tmpbuf[0]=WELCOME;
				SPI_Flash_Write(tmpbuf,((u32)DISPLAYCONTENT)<<12,1);
				Sys_Soft_Reset();//œµÕ≥∏¥Œª
				break;
			case 5://normal
				Displaycontent=NORMAL;
				tmpbuf[0]=Displaycontent;
				DisplayChangeEN=1;	;
				SPI_Flash_Write(tmpbuf,((u32)DISPLAYCONTENT)<<12,1);
				Sys_Soft_Reset();//œµÕ≥∏¥Œª
				 break;
			case 0x10:// 

			default:
				break;
			}
			break;		
		case BQ_POWER:
			if(buf[7]==1)
			{
				Open_LED_SCREEN();//BQVCC=1;////POWER ON
				DisplayChangeEN = 1;
			}
			if(buf[7]==2)
			{
				Close_LED_SCREEN();//BQVCC=0;////POWER Off 
				DisplayChangeEN=0;
			}
			Send_BQ_data_dir();
			DisplayChangeEN=0;
			break;
		case RTC_MESSAGE:
			calendar.w_year=BcdtoHex(buf[7]);//year L 
			calendar.w_month=BcdtoHex(buf[9]);//month
			calendar.w_date=BcdtoHex(buf[10]);//date
			calendar.hour=BcdtoHex(buf[11]);//hour
			calendar.min=BcdtoHex(buf[12]);//min
			calendar.sec=BcdtoHex(buf[13]);//sec
			DS3231_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);  //…Ë÷√ ±º
			RTC_check_already=1;
			break;
		case BQ_TIME_POWER:	//∂® ±ø™πÿª˙
			SPI_Flash_Erase_Sector((u32)BQ_TIME_POWER_FlshADDR);
			SPI_Flash_Write_NoCheck(buf,((u32)BQ_TIME_POWER_FlshADDR)<<12,RecvFromUART1_Len-3);//ºı»˝±Ì æ »•µÙ–£—ÈŒª ∫ÕΩ· ¯∑˚
			q=&Timer_Power_Struct;
			memcpy(q,&buf[7],sizeof(Timer_Power_Struct));
			Time_power_enable=1;
			break;
		case QUIT_BQ_TIME_POWER://»°œ˚∂® ±ø™πÿª˙
			SPI_Flash_Erase_Sector((u32)BQ_TIME_POWER_FlshADDR);
			Time_power_enable=0;
			Time_power_on=1;
			break;
		case BQ_LIGHT:	//…Ë÷√¡¡∂» 
			tmpbuf[0] = buf[8];
			SPI_Flash_Write(tmpbuf,((u32)BQ_LIGHT_FlshADDR)<<12,1);
			bflag_configlight=1;
		break;
		case TIME_SET:
			calendar.w_year=BcdtoHex(buf[7]);//year L 
			calendar.w_month=BcdtoHex(buf[9]);//month
			calendar.w_date=BcdtoHex(buf[10]);//date
			calendar.hour=BcdtoHex(buf[11]);//hour
			calendar.min=BcdtoHex(buf[12]);//min
			calendar.sec=BcdtoHex(buf[13]);//sec
			DS3231_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);  //…Ë÷√ ±º‰
			RTC_check_already=1;
			DisplayChangeEN=0;
			break;
		case VERSION:
			RebackPC_time=0;
			Verision();
			DisplayChangeEN=0;
			break;
		case REST_INIT:
			RebackPC_time=0;
			switch (buf[5])
			{
			case 0:
				RebackPC(CurrentCMD);
				#ifdef DEBUGE
					Debug_printf("\r\n SYS_REST !\r\n");
				#endif
				Sys_Soft_Reset();//œµÕ≥∏¥Œª
				break;
			case 1:
				#ifdef DEBUGE
				Debug_printf("\r\n SYSinit please wait....\r\n");
				#endif
				RebackPC(CurrentCMD);
				System_Init();
				Sys_Soft_Reset();//œµÕ≥∏¥Œª
				break;
			}
			break;
		case DATA2BQ://¥Ê¥¢“™œ‘ æµƒ ˝æ›// µ⁄¡„Œª¥Ê¥¢µƒ «Ω” ’µΩµƒ ˝æ›µƒ◊‹≥§∂»
			page=(buf[RecvFromUART1_Len-8]);
			tmpbuf[0]=page;
			if(RecvFromUART1_Len<=512)
			{
				if (buf[RecvFromUART1_Len-6]==0)//¥Ê¥¢“™œ‘ æµƒƒ⁄»›
				{	
					SPI_Flash_Erase_Sector(((u32)SCREENdataBASEADDR+(u32)page));
					SPI_Flash_Write_NoCheck(buf,((u32)SCREENdataBASEADDR+(u32)page)<<12,RecvFromUART1_Len-3);//ºı»˝±Ì æ »•µÙ–£—ÈŒª ∫ÕΩ· ¯∑˚
				}
				else if ((buf[RecvFromUART1_Len-6]&0x0f)==1)//welcome// µ⁄¡„Œª¥Ê¥¢µƒ «Ω” ’µΩµƒ ˝æ›µƒ◊‹≥§∂»
				{
					SPI_Flash_Erase_Sector(((u32) WELCOMEBASEADDR+(u32)page));
					SPI_Flash_Write_NoCheck(buf,((u32) WELCOMEBASEADDR+(u32)page)<<12,RecvFromUART1_Len-3);//ºı»˝±Ì æ »•µÙ–£—ÈŒª ∫ÕΩ· ¯∑˚
				}
				else if ((buf[RecvFromUART1_Len-6]&0x0f)==2)//// ≥ˆ≥ß ±“™œ‘ æµƒƒ⁄»› ¥Ê¥¢‘⁄µ•∆¨ª˙µƒflash…œ
				{
					STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)buf,RecvFromUART1_Len-3);
					//ºı»˝±Ì æ »•µÙ–£—ÈŒª ∫ÕΩ· ¯∑˚
				}
			}
			
			break;
		case RTUPARA:// µ⁄¡„Œª¥Ê¥¢µƒ «Ω” ’µΩµƒ ˝æ›µƒ◊‹≥§∂»
			SPI_Flash_Erase_Sector(((u32)RTUparaBASEADDR));
			SPI_Flash_Write(&buf[7],((u32)RTUparaBASEADDR)<<12,RecvFromUART1_Len-3);
			RTUparas.RTU_sum = buf[7];
			j=8;
			for (i=0;i<RTUparas.RTU_sum;i++)
			{
					j++;//RTU –Ú∫≈  °»•≤ª“™
					for(k = 0; k < 5; k++)
					{
						Hex2Hamming_Code(tmpbuf,buf[j]);
						if(buf[j]==0)
						{
							;
						}
						else
						{
							if(RTUparas.RTUID_sum==0)RTUparas.RTUID_sum=5-k;
						}
						RTUparas.RTUID[i][4-k]= buf[j++];
					}
					RTUparas.Alarm_Hour_r[i] = buf[j++]<<24;
					RTUparas.Alarm_Hour_r[i]|= buf[j++]<<16;
					RTUparas.Alarm_Hour_r[i]|= buf[j++]<<8;
					RTUparas.Alarm_Hour_r[i]|= buf[j++];
					
					RTUparas.Alarm_Day_r[i] = buf[j++]<<24;
					RTUparas.Alarm_Day_r[i]|= buf[j++]<<16;
					RTUparas.Alarm_Day_r[i]|= buf[j++]<<8;
					RTUparas.Alarm_Day_r[i]|= buf[j++];
					
					RTUparas.Alarm_Water[i] = buf[j++]<<24;
					RTUparas.Alarm_Water[i]|= buf[j++]<<16;
					RTUparas.Alarm_Water[i]|= buf[j++]<<8;
					RTUparas.Alarm_Water[i]|= buf[j++];
					
					RTUparas.DateSt[i] = buf[j++];
					RTUparas.MK_value[i] = buf[j++];
					
					RTUparas.Basic_Water[i+1]= buf[j++]<<8;
					RTUparas.Basic_Water[i+1]|= buf[j++];
					RTUparas.Basic_Water[i]= buf[j++]<<8;
					RTUparas.Basic_Water[i]|= buf[j++];
					
					RTUparas.Basic_Water[i+3]= buf[j++]<<8;
					RTUparas.Basic_Water[i+3]|= buf[j++];
					RTUparas.Basic_Water[i+2] = buf[j++]<<8;
					RTUparas.Basic_Water[i+2]|= buf[j++];
			}
			RebackPC(CurrentCMD);
			Sys_Soft_Reset();//œµÕ≥∏¥Œª
			break; 
		case Water_Level_Threshold_set: 
			Water_Level_Threshold = (buf[8]<<8)+buf[7];  
			SPI_Flash_Write((u8 *)&Water_Level_Threshold,(u32)WaterLevelThresholdADDR,sizeof(Water_Level_Threshold));
			RebackPC(CurrentCMD);
		break;
		default:
			Send_BQ_data_dir();
			break;
		}
	}else
	{
		RebackPC(0xa105);//crc err
	}
}

void B68datadeal(void)
{
	unsigned char   rtu_no,i;
	unsigned int   CRC_DATA,  crc ;
	unsigned char   tempbuf0[20],Minute;
	u8	tmpbuf[6];
	#ifdef WTD
	IWDG_Feed();
	#endif
	
	CRC_DATA = crc16(RecvFromUART1_Buf,RecvFromUART1_Len-2);
	crc = (RecvFromUART1_Buf[RecvFromUART1_Len-1])|((RecvFromUART1_Buf[RecvFromUART1_Len - 2])<<8);
	C_rtuaddr2=RecvFromUART1_Buf[2];
	C_stationaddr1=RecvFromUART1_Buf[1];
	Reback_en=1;

	if (CRC_DATA == crc)//crc–£—È(1)//
	{
		if(RTUparas.RTUID_sum==1)
		{
			rtu_no = 0;
		}
		else
		{
			for (i = 0;i < RTUparas.RTUID_sum;i++)//
			{
				if(C_rtuaddr2 == RTUparas.RTUID[0][i]){
					rtu_no = i;
					break;
				}
				else rtu_no = i;
			}
		}
		if((rtu_no<RTUparas.RTUID_sum)&&((RecvFromUART1_Buf[3]==0x0E)||(RecvFromUART1_Buf[3]==0x0B)||(RecvFromUART1_Buf[3]==0x09)||(RecvFromUART1_Buf[3]==0x0C)))
		{
			#ifdef RTU_DEBUGE
				printf("RTU_NO=%d\r\n",rtu_no);
			#endif
			switch (RecvFromUART1_Buf[RecvFromUART1_Len - 3])
			{
				case ETX: //03 ±ÌΩ· ¯
					Rebdatastate=EOT;//0x04 ’˝≥£Ω· ¯
					break;
				case ETB://0x17 ∫Û–¯”–±®Œƒ
					Rebdatastate=ACK;//0x06 ºÃ–¯ÀÕ ˝
					break;
			default:
				break;
			}	
			tempbuf0[0] = 0xaa;//		
			tempbuf0[1] = RecvFromUART1_Buf[5];//year
			tempbuf0[2] = RecvFromUART1_Buf[6];//month
			tempbuf0[3] = RecvFromUART1_Buf[7];//day
			tempbuf0[4] = RecvFromUART1_Buf[8];//hour
			tempbuf0[5] = RecvFromUART1_Buf[9];//minute
			if((RecvFromUART1_Buf[3]==0x0E)&&(RecvFromUART1_Buf[RecvFromUART1_Len - 3]==0x03)&&(tempbuf0[4]==0x01)&&(RTC_check_finish==0))
			{
				tmpbuf[0]=BcdtoHex(tempbuf0[1]);
				tmpbuf[1]=BcdtoHex(tempbuf0[2]);
				tmpbuf[2]=BcdtoHex(tempbuf0[3]);
				tmpbuf[3]=BcdtoHex(tempbuf0[4]);
				tmpbuf[4]=BcdtoHex(tempbuf0[5]);
				tmpbuf[5]=0;
				DS3231_Set(tmpbuf[0],tmpbuf[1],tmpbuf[2],tmpbuf[3],tmpbuf[4],tmpbuf[5]);
				RTC_check_already=1;
				RTC_check_finish=1;
			}
			
			Minute = (tempbuf0[5]>>4)*10+(tempbuf0[5]&0x0f);
			if(RecvFromUART1_Buf[3]==0x0C)//≤‚ ‘±®
			{
				tempbuf0[8]= RecvFromUART1_Buf[28+2*(Minute/5)];// ÀÆŒª∏ﬂŒª
				tempbuf0[9]= RecvFromUART1_Buf[29+2*(Minute/5)];// ÀÆŒªµÕŒª
			}
			else//≤ª «≤‚ ‘±®
			{
				if(Minute%5>0)//º”±®≤ª «’˚ŒÂ∑÷∑¢µƒ
				{
					tempbuf0[8]= RecvFromUART1_Buf[28+2*(Minute/5)];// ÀÆŒª∏ﬂŒª
					tempbuf0[9]= RecvFromUART1_Buf[29+2*(Minute/5)];// ÀÆŒªµÕŒª
				}
				else if(Minute%5==0)//’˚ŒÂ∑÷∑¢µƒ
				{
					if(Minute==0)
					{
						tempbuf0[8]= RecvFromUART1_Buf[50];// ÀÆŒª∏ﬂŒª
						tempbuf0[9]= RecvFromUART1_Buf[51];// ÀÆŒªµÕŒª
					}
					else
					{
						tempbuf0[8]= RecvFromUART1_Buf[28+2*(Minute/5-1)];// ÀÆŒª∏ﬂŒª
						tempbuf0[9]= RecvFromUART1_Buf[29+2*(Minute/5-1)];// ÀÆŒªµÕŒª
					}
				}
			}				
			if((tempbuf0[8]==0xff)&&(tempbuf0[9]==0xff))
				tempbuf0[8]=tempbuf0[9]=0;
			tempbuf0[10]= RecvFromUART1_Buf[10];// ¿€º∆”Í¡ø∏ﬂŒª
			tempbuf0[11]= RecvFromUART1_Buf[11];// ¿€º∆”Í¡øµÕŒª
			tempbuf0[12]=RecvFromUART1_Buf[12];// ±∂Œ”Í¡ø∏ﬂŒª
			tempbuf0[13]=RecvFromUART1_Buf[13];// ±∂Œ”Í¡øµÕŒª
			tempbuf0[14]=RecvFromUART1_Buf[14];//ΩÒ»’”Í¡ø∏ﬂŒª
			tempbuf0[15]=RecvFromUART1_Buf[15];//ΩÒ»’”Í¡øµÕŒª
			tempbuf0[16]=RecvFromUART1_Buf[52];// µÁ—π∏ﬂŒª
			tempbuf0[17]=RecvFromUART1_Buf[53];// µÁ—πµÕŒª
			//µ±«∞µÁ—π
			tempbuf0[16]=BcdtoHex(tempbuf0[16]);
			tempbuf0[17]=BcdtoHex(tempbuf0[17]);
			Voltage[rtu_no]=Radio_data.vol[rtu_no]=(tempbuf0[16]<<8)|tempbuf0[17];
			WriteDATAtoFlash(VOLTAGE,Radio_data.vol[rtu_no],rtu_no);	
			//¿€º∆”Í¡ø
			Rain_all[rtu_no]=Radio_data.rain_sum[rtu_no]=(tempbuf0[10]<<8)|tempbuf0[11];
			WriteDATAtoFlash(ARAIN,Radio_data.rain_sum[rtu_no],rtu_no);	
			//ΩÒ»’”Í¡ø
			Rain_day[rtu_no]=Radio_data.rain[rtu_no]=(tempbuf0[14]<<8)|tempbuf0[15];
			WriteDATAtoFlash(TRAIN,Radio_data.rain[rtu_no],rtu_no);	
			// ±∂Œ”Í¡ø
			Rain_hour[rtu_no]=Radio_data.hrain[rtu_no]=(tempbuf0[12]<<8)|tempbuf0[13];
			WriteDATAtoFlash(HRAIN,Radio_data.hrain[rtu_no],rtu_no);
			//µ±«∞ÀÆŒª
			Water[rtu_no]=Radio_data.water[rtu_no]=(tempbuf0[8]<<8)|tempbuf0[9];
			WriteDATAtoFlash(WATERL,Radio_data.water[rtu_no],rtu_no);
			#ifdef RTU_DEBUGE
				printf("water=%d\r\n",Water[rtu_no]);
				printf("tempbuf0=%d\r\n",tempbuf0[8]);
				printf("tempbuf1=%d\r\n",tempbuf0[9]);
			#endif
			
			if(MENUConfig.workmode==WORKMODENORMAL)
			{
				DisplayChangeEN=1;	//À¢∆¡
			}
			else if(Water[rtu_no]>=Water_Level_Threshold)
			{
				DisplayChangeEN=1;	//À¢∆¡
				Open_LED_SCREEN();
			}
			else
			{
				Close_LED_SCREEN();
				DisplayChangeEN=0;	//À¢∆¡
			}
		}
	}
	else//crc check eer
	{
		Rebdatastate=NAK;
	}	
}
const u8 Hamming_Code[16]={0x00,0x1B,0x2E,0x35,
							0x47,0x5C,0x69,0x72
							,0x8D,0x96,0xA3,0xB8,
							0xCA,0xD1,0xE4,0xFF
};
enum {
  Vo = 0x5C, JB_water = 0xA3, JB_rain = 0xb8, RAIN_DATA = 0xCA, WATER_DATA=0xff
};
char Hamming_Code2Hex(u8 data)
{	
	u8 i;
	for(i = 0;i < 16; i++){
		if(data == Hamming_Code[i])
			return i;
	}
	return 17;
}
void Hex2Hamming_Code(unsigned char  * res,  u8 val)
{	
	u8 data[2];
	data[0]=(val>>4)&0x0f;
	data[1]=(val)&0x0f;
	res[0] = Hamming_Code[data[0]];	
	res[1] = Hamming_Code[data[1]];	
}

u32 Water2flow(u32 water_l)// µ•Œª «¿Â√◊
{
	float flow_w;	
	if(water_l > 13000 ){
		return 164380;
	}
	else
		if(water_l <9300){		
		return 2;
		}
	else
	{
		return (flow_w*10);
	}
}
u8 Byte8datadeal()
{
	u8  rtu_no;
	u16 tmp16,rtuid,i;	
	#ifdef WTD
	IWDG_Feed();
	#endif
	rtuid = Hamming_Code2Hex(RecvFromUART1_Buf[1])<<4;
	rtuid|= Hamming_Code2Hex(RecvFromUART1_Buf[2]);
	
	if(RTUparas.RTUID_sum==1)
	{
		rtu_no = 0;
	}
	else
	{
		for (i = 0;i < RTUparas.RTUID_sum;i++)//
		{
			if(rtuid == RTUparas.RTUID[0][i]){
				rtu_no = i;
				break;
			}
			else rtu_no = i;
		}
	}
	if((rtu_no < RTUparas.RTUID_sum)&&(rtuid==RTUparas.RTUID[0][rtu_no]))
	{
		#ifdef RTU_DEBUGE
			printf("RTU_NO8byte=%d",rtu_no);
		#endif
		tmp16 = Hamming_Code2Hex(RecvFromUART1_Buf[4])<<8;
		tmp16|= Hamming_Code2Hex(RecvFromUART1_Buf[5])<<4;
		tmp16|= Hamming_Code2Hex(RecvFromUART1_Buf[6]);
		switch(RecvFromUART1_Buf[3])
		{
			case Vo:
				//µ±«∞µÁ—π
				Voltage[rtu_no]=Radio_data.vol[rtu_no]= tmp16;
				WriteDATAtoFlash(VOLTAGE,Radio_data.vol[rtu_no],rtu_no);	
				break;
			case JB_rain:
			case RAIN_DATA:
				//¿€º∆”Í¡ø
				Rain_all[rtu_no] =Radio_data.rain_sum[rtu_no] = tmp16;
				WriteDATAtoFlash(ARAIN,Rain_all[rtu_no],rtu_no);	
				//ΩÒ»’”Í¡ø
				if(Radio_data.rain_sum[rtu_no] <Radio_data.rain_sum_y[rtu_no])
				{
					Rain_day[rtu_no]=Radio_data.rain[rtu_no] = Radio_data.rain_sum[rtu_no]+RAIN_MAX-Radio_data.rain_sum_y[rtu_no];
				}
				else
				{
					Rain_day[rtu_no]=Radio_data.rain[rtu_no] = Radio_data.rain_sum[rtu_no]-Radio_data.rain_sum_y[rtu_no];
				}	
				WriteDATAtoFlash(TRAIN,Rain_day[rtu_no],rtu_no);				
				break;
			case JB_water:
			case WATER_DATA:
				//µ±«∞ÀÆŒª
				if(tmp16!=0xfff)
				{
					Water[rtu_no]=Radio_data.water[rtu_no] = tmp16;
					WriteDATAtoFlash(WATERL,Radio_data.water[rtu_no],rtu_no);
				}
				break;				
		}
		if(MENUConfig.workmode==WORKMODENORMAL)
		{
			DisplayChangeEN=1;	//À¢∆¡
		}
		else if(Water[rtu_no]>=Water_Level_Threshold)
		{
			DisplayChangeEN=1;	//À¢∆¡
			Open_LED_SCREEN();
		}
		else
		{
			Close_LED_SCREEN();
			DisplayChangeEN=0;	//À¢∆¡
		}
	}
	return 0;
}
u8 Byte15datadeal()
{
	unsigned char   tempbuf0[8];
	u8  rtu_no,RTUid_Check;
	u8 rtu_id,i;	
	rtu_id=RecvFromUART1_Buf[2];
	RTUid_Check=0;
	if(1)//≤ªΩ¯––crc–£—È
	{	
		if(RTUparas.RTUID_sum==1)
		{
			for (i = 0;i < RTUparas.RTUID_sum;i++)//
			{
				if(rtu_id == RTUparas.RTUID[0][i]){
					
					RTUid_Check=rtu_id;
					break;
				}
			}
			rtu_no = 0;
		}
		else
		{
			for (i = 0;i < RTUparas.RTUID_sum;i++)//
			{
				if(rtu_id == RTUparas.RTUID[0][i]){
					
				RTUid_Check=rtu_id;
					rtu_no = i;
					break;
				}
				else rtu_no = i;
			}
		}
		if((rtu_no<RTUparas.RTUID_sum)&&(RTUid_Check==rtu_id))
		{
			#ifdef RTU_DEBUGE
				printf("RTU_NO=%d",rtu_no);
			#endif
			tempbuf0[0]= RecvFromUART1_Buf[5];// ¿€º∆”Í¡ø∏ﬂŒª
			tempbuf0[1]= RecvFromUART1_Buf[6];// ¿€º∆”Í¡øµÕŒª
			tempbuf0[2]=RecvFromUART1_Buf[7];//ΩÒ»’”Í¡ø∏ﬂŒª
			tempbuf0[3]=RecvFromUART1_Buf[8];//ΩÒ»’”Í¡øµÕŒª
			tempbuf0[4]= RecvFromUART1_Buf[9];// ÀÆŒª∏ﬂŒª
			tempbuf0[5]= RecvFromUART1_Buf[10];// ÀÆŒªµÕŒª
			tempbuf0[6]=RecvFromUART1_Buf[11];// µÁ—π∏ﬂŒª
			tempbuf0[7]=RecvFromUART1_Buf[12];// µÁ—πµÕŒª
			//¿€º∆”Í¡ø
			Rain_all[rtu_no]=Radio_data.rain_sum[rtu_no]=(tempbuf0[0]<<8)|tempbuf0[1];
			WriteDATAtoFlash(ARAIN,Radio_data.rain_sum[rtu_no],rtu_no);	
			//ΩÒ»’”Í¡ø
			Rain_day[rtu_no]=Radio_data.rain[rtu_no]=(tempbuf0[2]<<8)|tempbuf0[3];
			WriteDATAtoFlash(TRAIN,Radio_data.rain[rtu_no],rtu_no);	
			//µ±«∞ÀÆŒª
			Water[rtu_no]=Radio_data.water[rtu_no]=(tempbuf0[4]<<8)|tempbuf0[5];
			WriteDATAtoFlash(WATERL,Radio_data.water[rtu_no],rtu_no);
			//µ±«∞µÁ—π
			Voltage[rtu_no]=Radio_data.vol[rtu_no]=(BcdtoHex)(tempbuf0[6]<<8)|tempbuf0[7];
			WriteDATAtoFlash(VOLTAGE,Radio_data.vol[rtu_no],rtu_no);
				
			if(MENUConfig.workmode==WORKMODENORMAL)
			{
				DisplayChangeEN=1;	//À¢∆¡
			}
			else if(Water[rtu_no]>=Water_Level_Threshold)
			{
				DisplayChangeEN=1;	//À¢∆¡
				Open_LED_SCREEN();
			}
			else
			{
				Close_LED_SCREEN();
				DisplayChangeEN=0;	//À¢∆¡
			}
			
		}
	}
	return 0;
}

void Reback68byte(void)
{
	u16 CRC_DATA,i;
	Rebdatabuf[0]=0x7e;
	Rebdatabuf[1]=C_rtuaddr2;
	Rebdatabuf[2]=C_stationaddr1;
	Rebdatabuf[3]=Function;
	Rebdatabuf[4]=0x09;
	Rebdatabuf[5]=RecvFromUART1_Buf[5];//year
	Rebdatabuf[6]=RecvFromUART1_Buf[6];//month
	Rebdatabuf[7]=RecvFromUART1_Buf[7];//day
	Rebdatabuf[8]=RecvFromUART1_Buf[8];//hour
	Rebdatabuf[9]=RecvFromUART1_Buf[9];//minute
	Rebdatabuf[10]=0;//second
	
	Rebdatabuf[11]=Rebdatastate;
	CRC_DATA = crc16(Rebdatabuf,12);
	Rebdatabuf[12]=CRC_DATA;
	Rebdatabuf[13]=CRC_DATA>>8;
	for(i=0;i<14;i++)
	{
		USART_SendData(USART1,Rebdatabuf[i]);
		while (!(USART1->SR & USART_FLAG_TXE));
	}
}

void Newprotdatadeal(void)
{
	;
}

void Send_DeleteCMD(void)
{
	u16 i;
	for(i=0;i<32;i++)//«¯”Úƒ⁄ ‰»Îµƒ◊÷∑˚
	{
		USART_SendData(UART5, deleteall[i]);
		while (!(UART5->SR & USART_FLAG_TXE));
	}
}
void Send_BQ_data_light(void)
{
	unsigned char   tempbuf[10];
	u8 i;
	u16 CRC16;
	u8 BQLight_Buf[30];
	SPI_Flash_Read(tempbuf,((u32)BQ_LIGHT_FlshADDR)<<12,1);// 
	for(i=0;i<20;i++)
	{
		BQLight_Buf[i]=Send_light[i];
	}
	BQLight_Buf[20]=tempbuf[0];
	CRC16=crc16_ctrl(BQLight_Buf,21);
	BQLight_Buf[21]= CRC16;;
	BQLight_Buf[22]= CRC16>>8;
	BQLight_Buf[23]= 0x5a;
	for (i=0;i<8;i++)
	{
		USART_SendData(UART5, 0xa5);
		while (!(UART5->SR & USART_FLAG_TXE));
	}
}
void Send_DatatoCrtl(void)
{
	u16 i;
	if(SendToCrtl_Len>USART1_REC_LEN)return;
	if(Time_power_on==1)
	{//BQ on power
		if(BQ_reback_timer==0)
		BQ_reback_timer=1;//start check 
		for(i=0;i<SendToCrtl_Len;i++)//«¯”Úƒ⁄ ‰»Îµƒ◊÷∑˚
		{
			USART_SendData(UART5, SendToCtrl_Buf[i]);
			while (!(UART5->SR & USART_FLAG_TXE));
		}

	}
}	
u8 Getshowdata(u8 type ,u8 rtu_no,u8 point,u8 *asciibuf )
{
	u8 i,res;
	u16 c_rain,l_rain,h_rain,capacity,y_rain,a_rain,vol;
	u32 c_water,water_f;
	
	point=point-0x30;
	rtu_no=rtu_no-0x31;//1∫≈’æ∂‘”¶∏˜ ˝◊Èµ⁄“ª∏ˆ ˝æ›
	if(RTUparas.RTUID_sum==1)
	{
		rtu_no = 0;
	}
	#ifdef RTU_DEBUGE
		printf("RTU_NO1=%d\r\n",rtu_no);
	printf("water1=%d\r\n",Water[rtu_no]);
	#endif
	//µ±«∞µÁ—π
	vol=Voltage[rtu_no];
	//ΩÒ»’”Í¡ø
	c_rain=Rain_day[rtu_no]*RTUparas.MK_value[0];//√ø∂∑±Ì æµƒ”Í¡øŒ™0.5mm
	//◊Ú»’”Í¡ø
	y_rain=Rain_Yday[rtu_no]*RTUparas.MK_value[0];//√ø∂∑±Ì æµƒ”Í¡øŒ™0.5mm 
	//¿€º∆”Í¡ø
	a_rain=Rain_all[rtu_no]*RTUparas.MK_value[0];//√ø∂∑±Ì æµƒ”Í¡øŒ™0.5mm 
	// ±∂Œ”Í¡ø
	h_rain=Rain_hour[rtu_no]*RTUparas.MK_value[0];//√ø∂∑±Ì æµƒ”Í¡øŒ™0.5mm
	//…œ ±∂Œ”Í¡ø
	l_rain=Rain_Lhour[rtu_no]*RTUparas.MK_value[0];
	if(l_rain==0xffff)l_rain=0;
	l_rain=l_rain*RTUparas.MK_value[0];//√ø∂∑±Ì æµƒ”Í¡øŒ™0.5mm
	//µ±«∞ÀÆŒª
	c_water=Water[rtu_no];
	if(c_water==0xffff)c_water=0;
	if(RTUparas.Basic_Water[rtu_no]!=0xffffffff)
	c_water+=RTUparas.Basic_Water[rtu_no];/// √ø∏ˆµ•Œª±Ì æ 1cm œ‘ æµ•Œªƒ¨»œ «m
	//µ±«∞ø‚»›
	capacity= Water2capacity_FuDingNX(c_water);	
	//¡˜¡ø
	water_f = Water_flow[rtu_no];	
	//–° ±”Í¡ø°¢»’”Í¡ø±®æØ
	if(((h_rain+ 5)/10) > RTUparas.Alarm_Hour_r[rtu_no] || ((c_rain+ 5)/10) > RTUparas.Alarm_Day_r[rtu_no] || c_water > RTUparas.Alarm_Water[rtu_no])
	{
		Alarm_enable = 1;
	}
	else
	{	
		Alarm_enable_reflash =1;
		Alarm_enable = 0;
	}
	switch(type)
	{
		case CAPAC://ø‚»›
			res = ulong_to_ascii(asciibuf,  (u32)capacity, point,0);
			break;
		case WATERL://ÀÆŒª
			switch (point)
			{
			case 0:
				c_water/=100;
				break;
			case 1:
				c_water/=10;
				break;
			case 2:
				break;
			default:
				point=2;
				break;
			}	
			res = ulong_to_ascii(asciibuf,  (u32)c_water, point,0);
	
			break;
			
		case WATER_F://¡˜¡ø
			if((water_f/100)<10)//0-10 »°»˝Œª”––ß ˝ pint = 2;
			{
				point = 2;
			}else
				if((water_f/100)<100)//0-10 »°»˝Œª”––ß ˝ pint = 2;
			{
				point = 1;
			}else
				point = 0;
			switch (point)
			{
			case 0:
				water_f/=100;
				
				break;
			case 1:
				water_f/=10;
				break;
			case 2:
				break;
			default:
				point=2;
				break;
			}	
			res = ulong_to_ascii(asciibuf,  (u32)water_f, point,0);
			break;
		case HRAIN:// ±∂Œ”Í¡ø
			switch (point)
			{
				case 0:
					h_rain/=10;
					break;
				case 1:
					break;
				default:
					point=1;
					break;
			}	
			res = ulong_to_ascii(asciibuf,(u32)h_rain, point,0);
			break;
			case LRAIN://…œ ±∂Œ”Í¡ø
			switch (point)
			{
				case 0:
					l_rain/=10;
					break;
				case 1:
					break;
				default:
					point=1;
					break;
			}	
			res = ulong_to_ascii(asciibuf,(u32)l_rain, point,0);
			break;
		case TRAIN://ΩÒ»’”Í¡ø
			switch (point)
			{
				case 0:
					c_rain/=10;
					break;
				case 1:
					break;
				default:
					point=1;
					break;
			}	
			res = ulong_to_ascii(asciibuf,(u32)c_rain, point,0);
			break;
		case YRAIN://◊Ú»’”Í¡ø
			switch (point)
			{
				case 0:
					y_rain/=10;
					break;
				case 1:
					break;
				default:
					point=1;
					break;
			}	
			res = ulong_to_ascii(asciibuf,(u32)y_rain, point,0);
			break;
		case ARAIN://¿€º∆”Í¡ø
			switch (point)
			{
				case 0:
					a_rain/=10;
					break;
				case 1:
					break;
				default:
					point=1;
					break;
			}	
			res = ulong_to_ascii(asciibuf,(u32)a_rain, point,0);
			break;
		case TEMPERATURE://Œ¬∂»
			if(Temp_val.f<0)//Œ¬∂»xiao”⁄0∂»µƒ
			{
				Temp_val.f=Temp_val.f*(-1);
				res = ulong_to_ascii(asciibuf,(u32)Temp_val.f, point,1);
			}
			else res = ulong_to_ascii(asciibuf,(u32)Temp_val.f, point,0);
			break;
		case HUMIDITY:// ™∂»
			res = ulong_to_ascii(asciibuf,(u32)Humi_val.f,point,0);
			break;
		case STATIONNAME://’æ√˚
			for(i=0;i<12;i++){
			
				break;
			}
			res=i;
			break;
		case VOLTAGE://µÁ—π
			res = ulong_to_ascii(asciibuf,(u32)vol, point,0);
			break;
		default :
			break;					
	}
	return res;
}

u8 ChangeScreemdata(u8* buf,u16 i)
{
	u8 tmp,res,j;
	u8 tmpbuf[16];
	#ifdef WTD
	IWDG_Feed();
	#endif
	if(buf[i]!='\\')
	{
		SendToCtrl_Buf[SendToCrtl_Len++]=buf[i];
		return 0;
	}
	else
	{
		if(buf[i+1]=='U')
		{
			switch(buf[i+2])
			{ 
				case 'V'://ø‚»›µ•Œª «ÕÚ¡¢∑Ω√◊
					res=Getshowdata(VOLTAGE,buf[i+3],buf[i+4],tmpbuf);
					if(res>200)return 0;
					for(j=0;j<res;j++)
					SendToCtrl_Buf[SendToCrtl_Len++]=tmpbuf[j];
					break;	
				case 'K'://ø‚»›µ•Œª «ÕÚ¡¢∑Ω√◊
					res=Getshowdata(CAPAC,buf[i+3],buf[i+4],tmpbuf);
					if(res>200)return 0;
					for(j=0;j<res;j++)
					SendToCtrl_Buf[SendToCrtl_Len++]=tmpbuf[j];
					break;	
				case 'W'://ÀÆŒªµ•Œª «m
					res=Getshowdata(WATERL,buf[i+3],buf[i+4],tmpbuf);
					if(res>200)return 0;
					for(j=0;j<res;j++)
					SendToCtrl_Buf[SendToCrtl_Len++]=tmpbuf[j];
					break;
					
				case 'F'://¡˜¡øµ•Œª «m
					res=Getshowdata(WATER_F,buf[i+3],buf[i+4],tmpbuf);
					if(res>200)return 0;
					for(j=0;j<res;j++)
					SendToCtrl_Buf[SendToCrtl_Len++]=tmpbuf[j];
					break;	
				case 'L'://…œ–° ±”Í¡øµ•Œª «mm//case 'R':
					res=Getshowdata(HRAIN,buf[i+3],buf[i+4],tmpbuf);
					if(res>200)return 0;
					for(j=0;j<res;j++)
					SendToCtrl_Buf[SendToCrtl_Len++]=tmpbuf[j];
					break;
				case 'R'://–° ±”Í¡øµ•Œª «mm//case 'R':
					res=Getshowdata(HRAIN,buf[i+3],buf[i+4],tmpbuf);
					if(res>200)return 0;
					for(j=0;j<res;j++)
					SendToCtrl_Buf[SendToCrtl_Len++]=tmpbuf[j];
					break;
				case 'Y'://◊Ú»’”Í¡øµ•Œª «mm
					res=Getshowdata(YRAIN,buf[i+3],buf[i+4],tmpbuf);
					if(res>200)return 0;
					for(j=0;j<res;j++)
					SendToCtrl_Buf[SendToCrtl_Len++]=tmpbuf[j];
					break;
				case 'C'://ΩÒ»’”Í¡øµ•Œª «mm
					res=Getshowdata(TRAIN,buf[i+3],buf[i+4],tmpbuf);
					if(res>200)return 0;
					for(j=0;j<res;j++)
					SendToCtrl_Buf[SendToCrtl_Len++]=tmpbuf[j];
					break;
				case 'A'://leiji”Í¡øµ•Œª «mm
					res=Getshowdata(ARAIN,buf[i+3],buf[i+4],tmpbuf);
					if(res>200)return 0;
					for(j=0;j<res;j++)
					SendToCtrl_Buf[SendToCrtl_Len++]=tmpbuf[j];
					break;
				case 'T'://Œ¬∂»µ•Œª «case 'T':
					res=Getshowdata(TEMPERATURE,buf[i+3],buf[i+4],tmpbuf);
					if(res>200)return 0;
					for(j=0;j<res;j++)
					SendToCtrl_Buf[SendToCrtl_Len++]=tmpbuf[j];
					break;	
				case 'H'://case 'H':
					res=Getshowdata(HUMIDITY,buf[i+3],buf[i+4],tmpbuf);
					if(res>200)return 0;
					for(j=0;j<res;j++)
					SendToCtrl_Buf[SendToCrtl_Len++]=tmpbuf[j];
					break;
				case 'M'://01  's'√ª”– ±º‰øÁ∂»
						
						SPI_Flash_Read(tmpbuf,((u32)PotrlRTUxDATASAVEBASIC+((u32)(buf[i+3]-0x31)))<<12,16);
						SendToCtrl_Buf[SendToCrtl_Len++]=(tmpbuf[2]>>4)+0x30;
						SendToCtrl_Buf[SendToCrtl_Len++]=(tmpbuf[2]&0x0f)+0x30;
						break;								
				case 'D'://01  's'√ª”– ±º‰øÁ∂»
						SPI_Flash_Read(tmpbuf,((u32)PotrlRTUxDATASAVEBASIC+((u32)(buf[i+3]-0x31)))<<12,16);
						SendToCtrl_Buf[SendToCrtl_Len++]=(tmpbuf[3]>>4)+0x30;
						SendToCtrl_Buf[SendToCrtl_Len++]=(tmpbuf[3]&0x0f)+0x30;
						break;			

				case 'S'://00-01  's'–° ± ”– ±º‰øÁ∂»
					
					SPI_Flash_Read(tmpbuf,((u32)PotrlRTUxDATASAVEBASIC+((u32)(buf[i+3]-0x31)))<<12,16);
				
					if(tmpbuf[4]==0xff)tmpbuf[4]=8;
					else if(tmpbuf[5]>5)
					{
						if((tmpbuf[4]&0x0f)==0x09)
							tmpbuf[4]=tmpbuf[4]+7;
						else
							tmpbuf[4]++;
					}
						
					if((tmpbuf[4]==0)||(tmpbuf[4]==0x10)||(tmpbuf[4]==0x20))
					{
						if(tmpbuf[4]==0)
						{
							SendToCtrl_Buf[SendToCrtl_Len++]=0x32;//23µ„
							SendToCtrl_Buf[SendToCrtl_Len++]=0x33;
						}
						if(tmpbuf[4]==0x10)
						{
							SendToCtrl_Buf[SendToCrtl_Len++]=0x30;//23µ„
							SendToCtrl_Buf[SendToCrtl_Len++]=0x39;	
						}
						if(tmpbuf[4]==0x20)
						{
							SendToCtrl_Buf[SendToCrtl_Len++]=0x31;//23µ„
							SendToCtrl_Buf[SendToCrtl_Len++]=0x39;	
						}
					}
					else
					{
						tmp=tmpbuf[4]>>4;
						SendToCtrl_Buf[SendToCrtl_Len++]=0x30+tmp;
						tmp=(tmpbuf[4]&0x0f)-1;
						SendToCtrl_Buf[SendToCrtl_Len++]=tmp+0x30;//–° ±
					}
					SendToCtrl_Buf[SendToCrtl_Len++]='-';
					
					if(tmpbuf[4]==0x24)
					{
						SendToCtrl_Buf[SendToCrtl_Len++]=0x30;//23µ„
						SendToCtrl_Buf[SendToCrtl_Len++]=0x30;	
					}
					else
					{
						SendToCtrl_Buf[SendToCrtl_Len++]=(tmpbuf[4]>>4)+0x30;
						SendToCtrl_Buf[SendToCrtl_Len++]=(tmpbuf[4]&0x0f)+0x30;
					}
					break;	
					case 's'://01  's'√ª”– ±º‰øÁ∂»
					
					SPI_Flash_Read(tmpbuf,((u32)PotrlRTUxDATASAVEBASIC+((u32)(buf[i+3]-0x31)))<<12,16);
				
					if(tmpbuf[4]==0xff)tmpbuf[4]=8;
					else if(tmpbuf[5]>5)
					{
						if((tmpbuf[4]&0x0f)==0x09) tmpbuf[4]=tmpbuf[4]+7;
						else tmpbuf[4]++;
					}				
					if(tmpbuf[4]==0x24)
					{
						SendToCtrl_Buf[SendToCrtl_Len++]=0x30;//23µ„
						SendToCtrl_Buf[SendToCrtl_Len++]=0x30;	
					}
					else
					{
						SendToCtrl_Buf[SendToCrtl_Len++]=(tmpbuf[4]>>4)+0x30;
						SendToCtrl_Buf[SendToCrtl_Len++]=(tmpbuf[4]&0x0f)+0x30;
					}
					break;	
					case 'N':
					res=Getshowdata(STATIONNAME,buf[i+3],buf[i+4],tmpbuf);
					if(res>200)return 0;
					for(j=0;j<res;j++)
					SendToCtrl_Buf[SendToCrtl_Len++]=tmpbuf[j];
					break;
					default:
						break;
				}
			return 4;			
			}
		else
		{
			if((buf[i+1]=='C')&&(Alarm_enable == 1))
			{
				buf[i+2]='2';
				if(Alarm_enable_reflash == 1)
				{
					Alarm_enable_reflash =0;
					DisplayChangeEN=1;	
				}
			}
			SendToCtrl_Buf[SendToCrtl_Len++]=buf[i];
			return 0;
		}
	}
}


void ComposeScreendata(u8* buf, u16 len)
{
	u16 i,j,CRC16;
	u16 lentmp;
	u16 lenbuf[5],uplen[5],newlenbuf[5],newuplen[5];
	u8 tmpbuf[USART1_REC_LEN];
	u8 tmp,areanum;
	
	SendToCrtl_Len = 0;
	for(i=0;i<20;i++)
	{
		SendToCtrl_Buf[SendToCrtl_Len++] = Send_frame[i];	
	}
	for(i=0;i<9;i++)
	{
		SendToCtrl_Buf[SendToCrtl_Len++] = buf[i];	
	}
	areanum=buf[8];
	if(areanum>6)return;
	for(j=0;j<areanum;j++)
	{	
		if(j==0)uplen[j]=9;
		else 
		uplen[j]=uplen[j-1]+lenbuf[j-1]+2;
		
		lenbuf[j]=buf[uplen[j]]+(buf[(uplen[j]+1)]<<8);
		lentmp=SendToCrtl_Len;
		if((uplen[j]>USART1_REC_LEN)||(lenbuf[j]>USART1_REC_LEN))return;
		for(i=uplen[j];i<lenbuf[j]+uplen[j]+2;i++)
		{
			tmp=ChangeScreemdata(buf,i);
			i=i+tmp;
		}
		lentmp=SendToCrtl_Len-lentmp-2;//‘ˆº”ªÚºı…Ÿ¡À «¯”Ú ˝æ›∫Û≥§∂»∑¢…˙±‰ªØ «¯”Ú1 µƒ ≥§∂»Œª÷√ ‘⁄ 29 30¥¶
		newlenbuf[j]=lentmp;
		
		if(j==0)newuplen[j]=9;//∏¸∏ƒ ˝æ›∫Û≥§∂»∑¢…˙±‰ªØ
		else 
		newuplen[j]=newuplen[j-1]+newlenbuf[j-1]+2;
		
		SendToCtrl_Buf[20+newuplen[j]]=lentmp;//low
		SendToCtrl_Buf[20+newuplen[j]+1]=lentmp>>8;//hight
		
		SendToCtrl_Buf[45+newuplen[j]]=lentmp-27;//low
		SendToCtrl_Buf[45+newuplen[j]+1]=(lentmp-27)>>8;//hight
		
	}
	SendToCtrl_Buf[20] = SendToCrtl_Len-22;//÷ÿ–¬º∆À„◊‹≥§∂»
	SendToCtrl_Buf[21] = (SendToCrtl_Len-22)>>8;
	if(SendToCrtl_Len>USART1_REC_LEN)return;
	for(j=8;j<(SendToCrtl_Len);j++)//»•µÙ∞¸Õ∑µƒ ˝æ›–Ë“™crc–£—Èµƒ≤ø∑÷ ¥”asc_buf01[0] µƒœ¬“ª∏ˆœÚœ¬ ˝ µΩ 8∏ˆA5 Œ™ 58∏ˆ ˝æ›
	{
		tmpbuf[j-8] =SendToCtrl_Buf[j];//
	}
	CRC16=crc16_ctrl(tmpbuf,(SendToCrtl_Len-8));
	
	SendToCtrl_Buf[SendToCrtl_Len++] = CRC16;
	SendToCtrl_Buf[SendToCrtl_Len++] = CRC16>>8;//CRC
	i=0;
	for(j=8;j<(SendToCrtl_Len);j++)//◊™“Â◊÷∑˚
	{
		if(SendToCtrl_Buf[j]==0x5a)
		{
			tmpbuf[i++]=0x5b;
			tmpbuf[i++]=0x02;
			continue;
		}
		if(SendToCtrl_Buf[j]==0x5b)
		{//◊™“Â◊÷∑˚
			tmpbuf[i++]=0x5b;
			tmpbuf[i++]=0x01;
			continue;
		}
		
		if(SendToCtrl_Buf[j]==0xa5)
		{//◊™“Â◊÷∑˚
			tmpbuf[i++]=0xa6;
			tmpbuf[i++]=0x02;
			continue;
		}
		if(SendToCtrl_Buf[j]==0xa6)
		{//◊™“Â◊÷∑˚
			tmpbuf[i++]=0xa6;
			tmpbuf[i++]=0x01;
			continue;
		}
		tmpbuf[i++] =SendToCtrl_Buf[j];//
	}
	SendToCrtl_Len=8;
	for(j=0;j<i;j++)
	{
		SendToCtrl_Buf[SendToCrtl_Len++]=tmpbuf[j];//
	}
	SendToCtrl_Buf[SendToCrtl_Len++] = 0x5A;	
}
const char* msg[] = {"WELCOME","NORMAL","YYDEVICE","CLEAR_SCREEM"};

void Display(u8 page ,u8 content)
{
	u8 tmpbuf[USART1_REC_LEN];
	u16	len;
	switch(content)
	{
		case WELCOME:
			SPI_Flash_Read(tmpbuf,((u32)WELCOMEBASEADDR+(u32)page)<<12,2);
			len=tmpbuf[0]+(tmpbuf[1]<<8);
			if((len==0xffff)||(len<20)||(len>0x300))
			{
				Displaycontent=CONF_SCREEM;//µ»¥˝ ‰»Î ˝æ›
				DisplayStayTime=0xff;
				return ;
			}
			SPI_Flash_Read(tmpbuf,((u32)WELCOMEBASEADDR+(u32)page)<<12,len+2);
			DisplayStayTime=tmpbuf[len-2];//±æ“≥Õ£¡Ù ±
				DisplayRunTime=0;
			ComposeScreendata(tmpbuf,len);
			break;
		case NORMAL:
			SPI_Flash_Read(tmpbuf,((u32)SCREENdataBASEADDR+(u32)page)<<12,2);
			len=tmpbuf[0]+(tmpbuf[1]<<8);
			if((len<20)||(len>USART1_REC_LEN))
			{
				Displaycontent=CONF_SCREEM;//µ»¥˝ ‰»Î ˝æ›
				DisplayStayTime=0xff;
				return ;
			}
			SPI_Flash_Read(tmpbuf,((u32)SCREENdataBASEADDR+(u32)page)<<12,len+2);
			DisplayStayTime=tmpbuf[len-2];//±æ“≥Õ£¡Ù ±
			DisplayRunTime=0;
			len=len-6;
			ComposeScreendata(tmpbuf,len+2);//∫Û»˝∏ˆ◊÷Ω⁄ ◊‹“≥ ˝ “≥¬Î Õ£¡Ù ±º‰ π§◊˜ƒ£ Ω ¡Ω∏ˆ±£¡Ù◊÷Ω⁄ “™»•µÙ	
			break;
		case YYDEVICE:
			STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)tmpbuf,2);//small type
			len=tmpbuf[0]+(tmpbuf[1]<<8);
			if((len==0xffff)||(len<20)||(len>0x300))
			{
				ComposeScreendata((u8 *)Begin_Page,86);//ª∂”≠ π”√—‡”Ì“£≤‚…Ë±∏
				DisplayStayTime=0xff;
			}
			else
			{
				STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)tmpbuf,len);
				ComposeScreendata(tmpbuf,len);//∫Û»˝∏ˆ◊÷Ω⁄ ◊‹“≥ ˝ “≥¬Îµ» “™»•µÙ
				DisplayStayTime=0xff;
			}
			break;
		case INIT_SCREEM:
			ComposeScreendata((u8 *)Init_Page,64);//ª∂”≠ π”√—‡”Ì“£≤‚…Ë±∏
			DisplayStayTime=0xff;
			break;	
		case CONF_SCREEM:
			ComposeScreendata((u8 *)Fail_Page,77);//ª∂”≠ π”√—‡”Ì“£≤‚…Ë±∏
			DisplayStayTime=0xff;
			break;	
		case CLEAR_SCREEM:
			ComposeScreendata((u8 *)Clear_screem,47);//ª∂”≠ π”√—‡”Ì“£≤‚…Ë±∏
			DisplayStayTime=1;
			DisplayRunTime=0;
			break;	
		default:
			break;		
	}
//	if(Uart5senddataprority==NORMALDADT_UART5)
	Send_DatatoCrtl();
}
void RecDataFroBoardUart1(void)//receive data from RTU use as 485
{
	u8 i;
if(Uart1_recvDone!=0)
{
	switch (Uart1_recvDone)
	{
	case PC_BQ_DATA:
		PC_BQ_data_deal();
		break;
	case PCPROTOCOL68DATA:
		if(Displaycontent!=CONF_SCREEM)
			B68datadeal();
		else 
			Display(DisplayPageno,CONF_SCREEM);
		break;
	case PTL15DATA:	
		if(Displaycontent!=CONF_SCREEM)
			Byte15datadeal();
		else 
			Display(DisplayPageno,CONF_SCREEM);
		break;
	case PTL8DATA:	
		if(Displaycontent!=CONF_SCREEM)
			Byte8datadeal();
		else 
			Display(DisplayPageno,CONF_SCREEM);
		break;
	case PCPROTOCOL7E7EDATA:
		if(Displaycontent!=CONF_SCREEM)
			Newprotdatadeal();
		else 
			Display(DisplayPageno,CONF_SCREEM);
		break;
		
	default:
		break;
	}
	Uart1_recvDone=0;
}
if(Uart5_recvDone==BQREBACK)//Ω´BQøÿ÷∆∞Â∑µªÿµƒ ˝æ›∑¢ÀÕ∏¯…œŒªª˙
 {
	 switch (RecvFromUART5_Buf[22])
	 {
		case 0xa1:
			Read_sys_para=0;
			for(i=0;i<8;i++)
			BQSystime[i]=RecvFromUART5_Buf[29+i];
			Uart5senddataprority&=0xfe;
		break;
		case 0xa0:
			if(bflagRedBoard_Check)
			{  
				bflagRedBoard_Check=0;
				screen_flag=Screen_Red_Right;
			}
		break;
		default:
		 break;
	 }	 

	Uart5_recvDone=0;
} 
}

