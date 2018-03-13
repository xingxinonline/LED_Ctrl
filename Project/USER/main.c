/******************** **********************
 * 文件名  ：main.c
 * 描述    ：   
 * 库版本  ：ST3.5.0
 *
 * 作者    ：King
 * 日期		 ：2014年10月27日
**********************************************************************************/
#include "sys.h"
extern RTUparaTest RTUparas_tset[10];
extern Radio_data_type  Radio_data;
extern RTUpara_type RTUparas;//
void Delay(__IO u32 nCount);
void GetChipUniqueID(void);
void GetFlashSize(void);
const u8 test001[]={"欢迎使用燕禹设备,正在开机,请稍后..."};
/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{	
 	delay_init();	    	 //延时函数初始化	
	/* LED 端口初始化 */
	GPIO_NOUSE_Config(); 
	GPIO_Config();
	SPI_Flash_Init();  
	DS3231_Init();
	initGlobleVar();
	while(SPI_Flash_ReadID()!=W25Q64)
	{
		for(;;)
		{
			#ifdef DEBUGE 
				Debug_printf("\r\n Flash ERR\r\n");
			#endif
			delay_ms(1000);
			FLASHERR=~FLASHERR;
		}
	}	
	FLASHERR=0;
	LEDSTATUS=0;
	delay_ms(2000);
	FLASHERR=1;
	delay_ms(100);
	#ifdef WTD
	if(MENUConfig.workmode==WORKMODENORMAL)
		IWDG_Init(4,625);  
	#endif
	get_show_time();
	#ifdef DEBUGE 
	TimePrint_dbg();
	#endif
//	GetChipUniqueID();
//	GetFlashSize();
	while (1)
	{	
		IWDG_Feed();
		Task();
	}
}
void GetChipUniqueID(void)
{
	
	u32 chipUniqueID32[3];

	chipUniqueID32[0] = *(__IO u32*)(0X1FFFF7F0);//ID????32??????
	chipUniqueID32[1] = *(__IO u32*)(0X1FFFF7EC);//ID????32??????
	chipUniqueID32[2] = *(__IO u32*)(0X1FFFF7E8);//ID????32??????
	
	Debug_printf("此芯片唯一ID为 %X-%X-%X\r\n\r\n",chipUniqueID32[0],chipUniqueID32[1],chipUniqueID32[2]);

}
void GetFlashSize(void)
{
	u16 Stm32_Flash_Size;
	
	Stm32_Flash_Size = *(u16*)(0x1FFFF7E0);//???????
	
	Debug_printf("芯片闪存容量大小为 %dK\r\n\r\n",Stm32_Flash_Size);

}
void Delay(__IO u32 nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
} 
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
