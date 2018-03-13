#ifndef __SCREEN_H
#define __SCREEN_H	
#include "sys.h" 

void PrintftoScreen(u8 *buf,u8 len) ;
void PingtoScreen(void);
void TaskScreenPowerOn(u8 flag);
u8 Character_Transfer(u8 *buf,u8 len);


#endif
