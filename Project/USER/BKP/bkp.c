#include "sys.h"

void BKP_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��   
	PWR_BackupAccessCmd(ENABLE);	//ʹ�ܺ󱸼Ĵ�������
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)		//��ָ���ĺ󱸼Ĵ����ж�������:��������д���ָ�����ݲ����
	{	 			
		BKP_DeInit();	//��λ�������� 	
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);	//��ָ���ĺ󱸼Ĵ�����д���û���������
		bflagsystemstart=1;//�ϵ縴λ Ԥ��һ��������ʱ��
		task_cnt|=_Start_task; 
		screen_flag=Screen_Power_On;
		DisplayPowerOnEN=1;
		DisplayChangeEN=0;
		#ifdef POWER_DEBUGE
			printf("�ϵ縴λ \r\n");
		#endif
	}
	else 
	{
		bflagsystemstart=0;
		DisplayChangeEN=1;
		#ifdef SCREEN_DEBUGE
		bflagsystemstart=1;//�ϵ縴λ Ԥ��һ��������ʱ��
		task_cnt|=_Start_task; 
		screen_flag=Screen_Power_On;
		DisplayPowerOnEN=1;
		DisplayChangeEN=0;
		#endif
		#ifdef POWER_DEBUGE
			printf("�����λ \r\n");
		#endif
	}		
}

