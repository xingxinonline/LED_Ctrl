#ifndef __MENU_H
#define __MENU_H	
#include "sys.h" 

enum MENU {	MENU_0=0,MENU_1,MENU_11=0x31,MENU_12,MENU_13,MENU_14,MENU_15,MENU_16,MENU_17,MENU_18,MENU_19,
						MENU_111=0x51,MENU_121,MENU_131,MENU_141,MENU_151,MENU_161,MENU_171,MENU_181,MENU_191,
						MENU_SURE,MENU_EXIT,MENU_ERR};

extern u8 bflag_menu;
extern u8 bflag_configStart;
		 
#pragma pack(1)
typedef struct {
  u8   workmode;//工作模式：stop、sleep、normal
	u8   waketime;//stop模式唤醒时间
	u8   daystart;//日雨量更新时间
	u8   hourstart;//时段雨量更新时间
	u8   ledstatus;//控制低功耗模式时工作状态灯开关
	u8  areacode;//8字节区号
  u32  baudrate;//波特率
  u8  wakestay;//唤醒后持续时间
  
} MENUConfig_type;

extern MENUConfig_type MENUConfig;
extern u8 bflag_menu;

#define WORKMODENORMAL	0x01
#define WORKMODESLEEP		0x02
#define WORKMODESTOP		0x04

void MENU_START(void);
void MENU0(void);
void MENU1(void);
void MENU1_1(void);																
void MENU1_2(void);
void MENU1_3(void);				
void MENU1_4(void);
void MENU1_5(void);
void MENU1_6(void);
void MENU1_7(void);
void MENU1_8(void);
void MENU1_9(void);
void MENU1_1_1(void);																
void MENU1_2_1(void);
void MENU1_3_1(void);				
void MENU1_4_1(void);
void MENU1_5_1(void);
void MENU1_6_1(void);
void MENU1_7_1(void);
void MENU1_8_1(void);
void MENU1_9_1(void);
void MENUCONFGSURE(void);
void MENUEXIT(void);
void MENUERR(void);
void ReadMENUConfig(void);

#endif
