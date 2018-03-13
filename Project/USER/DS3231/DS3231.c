 #include "sys.h"  
     
_calendar_obj calendar;

Time_Power_TypeDef Timer_Power_Struct; 
#define DS3231_WriteAddress 0xD0   
#define DS3231_ReadAddress  0xD1
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表	
u8 BCD2HEX(u8 val)
{
    u8 i;
    i= val&0x0f;
    val >>= 4;
    val &= 0x0f;
    val *= 10;
    i += val;
    
    return i;
}

u16 B_BCD(u8 val)
{
  u8 i,j,k;
  i=val/10;
  j=val%10;
  k=j+(i<<4);
  return k;
}


void I2cByteWrite(u8 addr,u8 bytedata)
{
  IIC_Start();
  delay_us(5);
  IIC_Send_Byte(DS3231_WriteAddress);
  IIC_Wait_Ack();
  delay_us(5);
  IIC_Send_Byte(addr);
  IIC_Wait_Ack();
  delay_us(5);
  IIC_Send_Byte(bytedata);
  IIC_Wait_Ack();
  delay_us(5);
  IIC_Stop();
}	


u8 I2cByteRead(u8 addr)
{
  u8 Dat=0;
  
  IIC_Start();
  IIC_Send_Byte(DS3231_WriteAddress);
  IIC_Wait_Ack();
  delay_us(5);
  IIC_Send_Byte(addr);
  IIC_Wait_Ack();
  delay_us(5);
  IIC_Start();
  IIC_Send_Byte(DS3231_ReadAddress);
  IIC_Wait_Ack();
  delay_us(5);
  Dat=IIC_Read_Byte(1);
  IIC_Stop();
  return Dat;
} 



void DS3231_Init(void)
{
	IIC_Init();
	I2cByteWrite(0x0e,0x1c);
	delay_ms(2); 
  I2cByteWrite(0x0f,0x0);
	delay_ms(2); 
}
void DS3231_Get(void)
{
  calendar.w_year=I2cByteRead(0x06);  
  calendar.w_month=I2cByteRead(0x05);  
  calendar.w_date=I2cByteRead(0x04); 
  calendar.hour=I2cByteRead(0x02);  
  calendar.min=I2cByteRead(0x01);
  calendar.sec=I2cByteRead(0x00);
}

void DS3231_Set(u8 yea,u8 mon,u8 da,u8 hou,u8 min,u8 sec)
{
  u8 temp=0;
  
  temp=B_BCD(yea);
  I2cByteWrite(0x06,temp);
  
  temp=B_BCD(mon);
  I2cByteWrite(0x05,temp);
   
  temp=B_BCD(da);
  I2cByteWrite(0x04,temp);
  
  temp=B_BCD(hou);
  I2cByteWrite(0x02,temp);
  
  temp=B_BCD(min);
  I2cByteWrite(0x01,temp);
  
  temp=B_BCD(sec);
  I2cByteWrite(0x00,temp);
}


void get_show_time(void)
{
	calendar.w_year=I2cByteRead(0x06);  
	calendar.w_year=BCD2HEX(calendar.w_year);


	calendar.w_month=I2cByteRead(0x05); 
	calendar.w_month=BCD2HEX(calendar.w_month);


	calendar.w_date=I2cByteRead(0x04);  
	calendar.w_date=BCD2HEX(calendar.w_date);
	 

	calendar.hour=I2cByteRead(0x02); 
	calendar.hour&=0x3f;                   
	calendar.hour=BCD2HEX(calendar.hour);


	calendar.min=I2cByteRead(0x01);
	calendar.min=BCD2HEX(calendar.min);
		
		
	calendar.sec=I2cByteRead(0x00);
	calendar.sec=BCD2HEX(calendar.sec);
}
//获得现在是星期几
//功能描述:输入公历日期得到星期(只允许1901-2099年)
//输入参数：公历年月日 
//返回值：星期号																						 
u8 RTC_Get_Week(u16 year,u8 month,u8 day)
{	
	u16 temp2;
	u8 yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 
	// 如果为21世纪,年份数加100  
	if (yearH>19)yearL+=100;
	// 所过闰年数只算1900年之后的  
	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
}
void GetDS3231Temp(u8 *addr)
{
	*addr++=I2cByteRead(0x11);
	*addr=((I2cByteRead(0x12)>>6)&0x03)*25;
}
void OpenDoubleAlarm(void)
{
	unsigned char tmp;
	tmp=I2cByteRead(0x0e);
	tmp|=0x03;
	I2cByteWrite(0x0e,tmp);
}
void OpenAlarm1(void)
{
	unsigned char tmp;
	tmp=I2cByteRead(0x0e);
	tmp|=0x01;
	I2cByteWrite(0x0e,tmp);
}
void OpenAlarm2(void)
{
	unsigned char tmp;
	tmp=I2cByteRead(0x0e);
	tmp|=0x02;
	I2cByteWrite(0x0e,tmp);
}
void CloseDoubleAlarm(void)
{
	unsigned char tmp;
	tmp=I2cByteRead(0x0e);
	tmp&=0xfc;
	I2cByteWrite(0x0e,tmp);
}
void CloseAlarm1(void)
{
	unsigned char tmp;
	tmp=I2cByteRead(0x0e);
	tmp&=0xfe;
	I2cByteWrite(0x0e,tmp);
}
void CloseAlarm2(void)
{
	unsigned char tmp;
	tmp=I2cByteRead(0x0e);
	tmp&=0xfd;
	I2cByteWrite(0x0e,tmp);
}
void DoubleAlarmInit(void)
{
	Alarm1Init();
	Alarm2Init(MENUConfig.waketime); 
}
void Alarm1Init(void)
{
	unsigned char tmp;
	tmp=I2cByteRead(0x0e);
	tmp&=0xfe;
	I2cByteWrite(0x0e,tmp);//关闭闹钟1
	//Alarm1设置为秒中断
	I2cByteWrite(0x07,0x80);
	I2cByteWrite(0x08,0x80);
	I2cByteWrite(0x09,0x80);
	I2cByteWrite(0x0a,0x80);
}
void Alarm2Init(u8 type)
{
	unsigned char tmp;
	tmp=I2cByteRead(0x0e);
	tmp&=0xfd;
	I2cByteWrite(0x0e,tmp);//关闭闹钟2
	//Alarm2设置为分钟数与写入值相同便产生中断，即最小中断间隔一分钟
	switch(type)
	{
		case ALARM2_MINUTE:
			I2cByteWrite(0x0b,0x80);
			I2cByteWrite(0x0c,0x80);
			I2cByteWrite(0x0d,0x80);
			break;
		case ALARM2_HOUR:
			I2cByteWrite(0x0b,MENUConfig.hourstart);
			I2cByteWrite(0x0c,0x80);
			I2cByteWrite(0x0d,0x80);
			break;
		default:
			I2cByteWrite(0x0b,0x00);
			I2cByteWrite(0x0c,0x80);
			I2cByteWrite(0x0d,0x80);
		break;
	}
}
void ReadAlarmFlag(void)
{
	u8 tmp;
	tmp=I2cByteRead(0x0f);
	if(tmp&ALARM1)
	{
		Alarm1_flag=1;
		ClearAlarm1Flag();
	}
	if(tmp&ALARM2)
	{
		SET_POW_MAX3222();
		Alarm2_flag=1;
		ClearAlarm2Flag();
	}
}
void ClearAlarm1Flag(void)
{
	unsigned char tmp;
	tmp=I2cByteRead(0x0f);
	tmp&=0xfe;
	I2cByteWrite(0x0f,tmp);
}
void ClearAlarm2Flag(void)
{
	unsigned char tmp;
	tmp=I2cByteRead(0x0f);
	tmp&=0xfd;
	I2cByteWrite(0x0f,tmp);
}
void SetAlarm1(unsigned char minute)
{
		I2cByteWrite(0x08,minute);
}
void SetAlarm2(void)
{
		u8 minute;
		get_show_time();
		if(calendar.min%5!=MENUConfig.waketime)//不是中断唤醒设置，是复位设置
		{
			minute=calendar.min/5*5+MENUConfig.waketime;
			if(minute<=calendar.min)minute+=5;
		}
		else minute=calendar.min+5;
		I2cByteWrite(0x0B,14);
}





