#include "sys.h"

void BKP_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//使能PWR和BKP外设时钟   
	PWR_BackupAccessCmd(ENABLE);	//使能后备寄存器访问
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)		//从指定的后备寄存器中读出数据:读出了与写入的指定数据不相乎
	{	 			
		BKP_DeInit();	//复位备份区域 	
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);	//向指定的后备寄存器中写入用户程序数据
		bflagsystemstart=1;//上电复位 预留一定的配置时长
		task_cnt|=_Start_task; 
		screen_flag=Screen_Power_On;
		DisplayPowerOnEN=1;
		DisplayChangeEN=0;
		#ifdef POWER_DEBUGE
			printf("上电复位 \r\n");
		#endif
	}
	else 
	{
		bflagsystemstart=0;
		DisplayChangeEN=1;
		#ifdef SCREEN_DEBUGE
		bflagsystemstart=1;//上电复位 预留一定的配置时长
		task_cnt|=_Start_task; 
		screen_flag=Screen_Power_On;
		DisplayPowerOnEN=1;
		DisplayChangeEN=0;
		#endif
		#ifdef POWER_DEBUGE
			printf("软件复位 \r\n");
		#endif
	}		
}

