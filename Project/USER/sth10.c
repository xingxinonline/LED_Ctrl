/***********************************************************************************
Project:          SHTxx demo program (V2.1)
Filename:         SHTxx_Sample_Code.c    

Prozessor:        80C51 family
Compiler:         Keil Version 6.14

Autor:            MST
Copyrigth:        (c) Sensirion AG      
***********************************************************************************/
//#include <intrins.h> //Keil library (is used for _nop()_ operation)  
#include <math.h>    //Keil library  
#include <stdio.h>   //Keil library
//#include<STC_NEW_8051.H>
#include "sys.h"

//----------------------------------------------------------------------------------
// modul-var
//----------------------------------------------------------------------------------
enum {TEMP,HUMI};
extern Temp_Humi_value Humi_val,Temp_val;





#define noACK 0
#define STH10ACK   1
                            //adr  command  r/w
#define STATUS_REG_W 0x06   //000   0011    0
#define STATUS_REG_R 0x07   //000   0011    1
#define MEASURE_TEMP 0x03   //000   0001    1
#define MEASURE_HUMI 0x05   //000   0010    1
#define RESET        0x1e   //000   1111    0



//初始化IIC
void sth10_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//PA12 是 手动格式化
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1); 	//PA0,PA1 输出高
	delay_ms(1);
}
//----------------------------------------------------------------------------------
char s_write_byte(unsigned char value)
//----------------------------------------------------------------------------------
// writes a byte on the Sensibus and checks the acknowledge 
{ 
  unsigned char i,error=0; 
	SDA_OUT();	
  for (i=0x80;i>0;i/=2)             //shift bit for masking
  { if (i & value) DATA=1;          //masking value with i , write to SENSI-BUS
    else DATA=0;     
		delay_us(1);  
    SCK=1;                          //clk for SENSI-BUS
    delay_us(2);        //pulswith approx. 5 us  	
    SCK=0;
		delay_us(1);        //pulswith approx. 5 us  	
  }
	SDA_IN();delay_us(1);
	SCK=1;delay_us(1);
	error=DATAIN;
	SCK=0;delay_us(1);
	delay_us(50);
	SDA_OUT();	DATA=1;
	delay_us(1);SDA_IN();
	delay_us(5);
//   DATA=1;                           //release DATA-line
//   SCK=1;                            //clk #9 for ack 
  return error; 
  
                         //check ack (DATA will be pulled down by SHT11)

//   SCK=0;        
//   return error;                     //error=1 in case of no acknowledge
}

//----------------------------------------------------------------------------------
char s_read_byte(unsigned char ack)
//----------------------------------------------------------------------------------
// reads a byte form the Sensibus and gives an acknowledge in case of "ack=1" 
{ 
  unsigned char i,val=0;
  DATA=1;                           //release DATA-line
  
  SDA_IN();
	SCK=0;
  delay_us(1);
  for (i=0x80;i>0;i/=2)             //shift bit for masking
  { SCK=1;                          //clk for SENSI-BUS
  delay_us(4);
    if (DATAIN) 
			val=(val | i);        //read bit  
    SCK=0;  
	delay_us(4);
  }
  
  SDA_OUT();
  DATA=!ack;                        //in case of "ack==1" pull down DATA-Line
  SCK=1;                            //clk #9 for ack
  delay_us(3);         //pulswith approx. 5 us 
  SCK=0;
  delay_us(3);
  DATA=1;                           //release DATA-line
  return val;
}

//----------------------------------------------------------------------------------
void s_transstart(void)
//----------------------------------------------------------------------------------
// generates a transmission start 
//       _____         ________
// DATA:      |_______|
//           ___     ___
// SCK : ___|   |___|   |______
{  
   DATA=1; 
     SCK=0;           //Initial state
   delay_us(1);
   SCK=1;
   delay_us(1);
   DATA=0;
   delay_us(1);
   SCK=0;  
   delay_us(1);delay_us(1);
   SCK=1;
   delay_us(1);
   DATA=1;		   
   delay_us(1);
   SCK=0;	   delay_us(1);	DATA=0;		      
}

//----------------------------------------------------------------------------------
void s_connectionreset(void)
//----------------------------------------------------------------------------------
// communication reset: DATA-line=1 and at least 9 SCK cycles followed by transstart
//       _____________________________________________________         ________
// DATA:                                                      |_______|
//          _    _    _    _    _    _    _    _    _        ___     ___
// SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |______
{  
  unsigned char i; 
	
  DATA=1; SCK=0;                    //Initial state
  for(i=0;i<9;i++)                  //9 SCK cycles
  { SCK=1;
	delay_us(2);
    SCK=0;
	delay_us(2);
  }
  s_transstart();                   //transmission start
}

//----------------------------------------------------------------------------------
char s_softreset(void)
//----------------------------------------------------------------------------------
// resets the sensor by a softreset 
{ 
  unsigned char error=0;  
  s_connectionreset();              //reset communication
  error+=s_write_byte(RESET);       //send RESET-command to sensor
  return error;                     //error=1 in case of no response form the sensor
}

//----------------------------------------------------------------------------------
char s_read_statusreg(unsigned char *p_value, unsigned char *p_checksum)
//----------------------------------------------------------------------------------
// reads the status register with checksum (8-bit)
{ 
  unsigned char error=0;
  s_transstart();                   //transmission start
  error=s_write_byte(STATUS_REG_R); //send command to sensor
  *p_value=s_read_byte(STH10ACK);        //read status register (8-bit)
  *p_checksum=s_read_byte(noACK);   //read checksum (8-bit)  
  return error;                     //error=1 in case of no response form the sensor
}

//----------------------------------------------------------------------------------
char s_write_statusreg(unsigned char *p_value)
//----------------------------------------------------------------------------------
// writes the status register with checksum (8-bit)
{ 
  unsigned char error=0;
  s_transstart();                   //transmission start
  error+=s_write_byte(STATUS_REG_W);//send command to sensor
  error+=s_write_byte(*p_value);    //send value of status register
  return error;                     //error>=1 in case of no response form the sensor
}
 							   
//----------------------------------------------------------------------------------
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode)
//----------------------------------------------------------------------------------
// makes a measurement (humidity/temperature) with checksum
{ 
  unsigned error=0;
  unsigned int i;

  s_transstart();                   //transmission start

  switch(mode){                     //send command to sensor
    case TEMP	: error+=s_write_byte(MEASURE_TEMP); break;
    case HUMI	: error+=s_write_byte(MEASURE_HUMI); break;
    default     : break;	 
  }
  for (i=0;i<65535;i++){
	if(DATAIN==0) 
		break; //wait until sensor has finished the measurement
else
		delay_us(5);
} 

  if(DATAIN) error+=1;                // or timeout (~2 sec.) is reached
  SDA_OUT();
 // LEDSTATU=1;
  *(p_value+1)=s_read_byte(STH10ACK);    //read the first byte (MSB)
  *(p_value)=s_read_byte(STH10ACK);    //read the second byte (LSB)
  *p_checksum =s_read_byte(noACK);  //read checksum
  
//   USART_SendData(UART5,*(p_value));
// 		while (!(UART5->SR & USART_FLAG_TXE));
//     USART_SendData(UART5,*(p_value+1));
// 		while (!(UART5->SR & USART_FLAG_TXE));
  
  return error;
}

//----------------------------------------------------------------------------------
// void init_uart()
// //----------------------------------------------------------------------------------
// //9600 bps @ 11.059 MHz 
// {SCON  = 0x52;    
//  TMOD  = 0x20;    
//  TCON  = 0x69;	  
//  TH1   = 0xfd;    
// }

//----------------------------------------------------------------------------------------
void calc_sth11(float *p_humidity ,float *p_temperature)
//----------------------------------------------------------------------------------------
// calculates temperature [癈] and humidity [%RH] 
// input :  humi [Ticks] (12 bit) 
//          temp [Ticks] (14 bit)
// output:  humi [%RH]
//          temp [癈]
{ const float C1=-4.0;              // for 12 Bit
  const float C2=+0.0405;           // for 12 Bit
  const float C3=-0.0000028;        // for 12 Bit
  const float T1=+0.01;             // for 14 Bit @ 5V
  const float T2=+0.00008;           // for 14 Bit @ 5V	

  float rh=*p_humidity;             // rh:      Humidity [Ticks] 12 Bit 
  float t=*p_temperature;           // t:       Temperature [Ticks] 14 Bit
  float rh_lin;                     // rh_lin:  Humidity linear
  float rh_true;                    // rh_true: Temperature compensated humidity
  float t_C;                        // t_C   :  Temperature [癈]

  t_C=t*0.01 - 40;                  //calc. temperature from ticks to [癈]
  rh_lin=C3*rh*rh + C2*rh + C1;     //calc. humidity from ticks to [%RH]
  rh_true=(t_C-25)*(T1+T2*rh)+rh_lin;   //calc. temperature compensated humidity [%RH]
  if(rh_true>100)rh_true=100;       //cut if the value is outside of
  if(rh_true<0.1)rh_true=0.1;       //the physical possible range

  *p_temperature=t_C;               //return temperature [癈]
  *p_humidity=rh_true;              //return humidity[%RH]
}

//--------------------------------------------------------------------
float calc_dewpoint(float h,float t)
//--------------------------------------------------------------------
// calculates dew point
// input:   humidity [%RH], temperature [癈]
// output:  dew point [癈]
{ float logEx,dew_point;
  logEx=0.66077+7.5*t/(237.3+t)+(log10(h)-2);
  dew_point = (logEx - 0.66077)*237.3/(0.66077+7.5-logEx);
  return dew_point;
}

//----------------------------------------------------------------------------------
void readsht10(void)
//----------------------------------------------------------------------------------
// sample program that shows how to use SHT11 functions
// 1. connection reset 
// 2. measure humidity [ticks](12 bit) and temperature [ticks](14 bit)
// 3. calculate humidity [%RH] and temperature [癈]
// 4. calculate dew point [癈]
// 5. print temperature, humidity, dew point  

{ 
  //float dew_point;
  unsigned char error,checksum;
  unsigned int i;
Temp_val.f=0;
Humi_val.f=0;
sth10_Init();
//LEDSTATU=0;
// s_read_byte(1);
// s_read_byte(1);


	s_connectionreset();

	error=0;
    error+=s_measure((unsigned char*) &Humi_val.i,&checksum,HUMI);  //measure humidity

    error+=s_measure((unsigned char*) &Temp_val.i,&checksum,TEMP);  //measure temperature
    if(error!=0) s_connectionreset();                 //in case of an error: connection reset
    else
    { Humi_val.f=(float)Humi_val.i;                   //converts integer to float
      Temp_val.f=(float)Temp_val.i;                   //converts integer to float
      calc_sth11(&(Humi_val.f),&(Temp_val.f));            //calculate humidity, temperature
      //dew_point=calc_dewpoint(Humi_val.f,Temp_val.f); //calculate dew point
     // printf("temp:%5.1fC humi:%5.1f%% dew point:%5.1fC\n",Temp_val.f,Humi_val.f,dew_point);
    }
    //----------wait approx. 0.8s to avoid heating up SHTxx------------------------------      
    for (i=0;i<4;i++);     //(be sure that the compiler doesn't eliminate this line!)
    //-----------------------------------------------------------------------------------                       
		Temp_val.f=Temp_val.f*10;
		i=(unsigned int)Temp_val.f;
		Humi_val.f=Humi_val.f*10;//11;//
		i=(unsigned int)Humi_val.f;
} 
