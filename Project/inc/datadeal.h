
#ifndef __DATADEAL_H__
#define __DATADEAL_H__
#include "stm32f10x.h"

#define PING 0xA200
#define REST_INIT 0xA201
#define TIME_SET 0xa203 

#define BQ_POWER 0xa300 
#define BQ_TIME_POWER 0xa301
#define BQ_LIGHT 0xa302 
#define DATA2BQ 0xA306
#define QUIT_BQ_TIME_POWER 0xa308
#define Water_Level_Threshold_set 0xB100
  

#define RTUPARA 0xb101
#define VERSION 0xb201
#define RTC_MESSAGE 0xb301

#define YYDEVICE 0x01
#define WELCOME 0x02
#define NORMAL 0x03
#define INIT_SCREEM 0x04
#define CONF_SCREEM 0x05
#define CLEAR_SCREEM 0x06

void PC_BQ_data_deal(void);
void Send_BQ_data_light(void);
void Reback68byte(void);
void Newprotdatadeal(void);
void B68datadeal(void);
void Send_DatatoCrtl(void);
u8 Getshowdata(u8 type ,u8 rtu_no,u8 point,u8 *asciibuf);
void ComposeScreendata(u8* buf, u16 len);
void Display(u8 page ,u8 content);
void RecDataFroBoardUart1(void);
void ReadBQsyspar(void);
void RebackPC(u16 curentcmd);
void Hex2Hamming_Code(unsigned char  * res,  u8 val);
void Send_BQ_time_dir(u8 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);
u8 Byte8datadeal(void);
u32 Water2capacity(u32 water_l);
u32 Water2flow(u32 water_l);// 单位是厘米
u32 Water2capacity_FuDingNX(u32 water_l);// 单位是厘米
//void Delay(__IO u32 nCount);
//{
//	for(; nCount != 0; nCount--);
//}
#endif
