#ifndef __LOWPOWER_H
#define __LOWPOWER_H	
#include "sys.h" 

void TaskLowPower(u8 workmode);
//*****************************************
//˯��ģʽ
//*****************************************
void Sys_EnterSLEEPmode(void);
//*****************************************
//ֹͣģʽ
//*****************************************
void Sys_EnterSTOPmode(void);
//*****************************************
//˯��ģʽ׼������
//*****************************************
void TasktoSleepMode(void);
//*****************************************
//ֹͣģʽ׼������
//*****************************************
void TasktoStopMode(void);
//*****************************************
//˯��ģʽ��������
//*****************************************
void TaskfromSleepMode(void);
//*****************************************
//ֹͣģʽ��������
//*****************************************
void TaskfromStopMode(void);
//�ָ�ϵͳʱ�Ӻ���
void SYSCLKConfig_STOP(void);
void TaskWakeUp(u8 workmode);
void PER_SLEEP_CONFIG(FunctionalState able);
void PER_STOP_CONFIG(FunctionalState able);









#endif


