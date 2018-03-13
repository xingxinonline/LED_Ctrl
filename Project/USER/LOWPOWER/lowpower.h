#ifndef __LOWPOWER_H
#define __LOWPOWER_H	
#include "sys.h" 

void TaskLowPower(u8 workmode);
//*****************************************
//睡眠模式
//*****************************************
void Sys_EnterSLEEPmode(void);
//*****************************************
//停止模式
//*****************************************
void Sys_EnterSTOPmode(void);
//*****************************************
//睡眠模式准备任务
//*****************************************
void TasktoSleepMode(void);
//*****************************************
//停止模式准备任务
//*****************************************
void TasktoStopMode(void);
//*****************************************
//睡眠模式唤醒任务
//*****************************************
void TaskfromSleepMode(void);
//*****************************************
//停止模式唤醒任务
//*****************************************
void TaskfromStopMode(void);
//恢复系统时钟函数
void SYSCLKConfig_STOP(void);
void TaskWakeUp(u8 workmode);
void PER_SLEEP_CONFIG(FunctionalState able);
void PER_STOP_CONFIG(FunctionalState able);









#endif


