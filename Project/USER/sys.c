#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 

//********************************************************************************  
// void NVIC_Configuration(void)
// {

   // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级

// }


/*
#define DISPLAYCONTENT  				0xe0//显示内容是欢迎还是正常内容  0xf0--0xf1
#define SCREEMNUM 					 		0xe1//显示内容是欢迎还是正常内容  0xf0--0xf1
#define YRAINBASEADDR  					0xf0//昨日雨量1号到10号  0xf0--0xf1
#define WELCOMEBASEADDR  				0x10A//自定义欢迎信息  0x10A--0x114
#define ADDRepotRdataBASEADDR  	0x110// 0x110-0x119//存储十个RTU从1号到10号的雨量加报数据
#define ADDRepotWdataBASEADDR  	0x120// 0x120-0x129//存储十个RTU从1号到10号的水位加报数据
#define SCREENdataBASEADDR  		0x150// 0x150-0x200存储十个页面屏要显示的数据 本屏支持0x50个不同显示的页面
#define RTUparaBASEADDR  				0x200 // 0x200-0x200//存储RTU的参数

#define PotrlRTUxDATASAVEBASIC  0x300//存储RTU的整点报数据，每个站号分配1个扇区，存储每天24小时整点报 每天擦除24次按可擦 100000次计算约可擦10年；
*/

void System_Init()
{
	u8 i;
	for(i=0;i<16;i++)//擦除 显示页
	{
		SPI_Flash_Erase_Sector((u32)DISPLAYCONTENT+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//擦除 显示页
	{
		SPI_Flash_Erase_Sector((u32)YRAINBASEADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//擦除 显示页
	{
		SPI_Flash_Erase_Sector((u32)WELCOMEBASEADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//擦除 显示页
	{
		SPI_Flash_Erase_Sector((u32)ADDRepotRdataBASEADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//擦除 显示页
	{
		SPI_Flash_Erase_Sector((u32)ADDRepotWdataBASEADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//擦除 显示页
	{
		SPI_Flash_Erase_Sector((u32)SCREENdataBASEADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//擦除 显示页
	{
		SPI_Flash_Erase_Sector((u32)RTUparaBASEADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//擦除 显示页
	{
		SPI_Flash_Erase_Sector((u32)WaterLevelThresholdADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//擦除 显示页
	{
		SPI_Flash_Erase_Sector((u32)PotrlRTUxDATASAVEBASIC+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
}
//系统软复位   
		//SW_RESET();
	//	Sys_Soft_Reset();
void Sys_Soft_Reset(void)
{  
		delay_ms(30);
	SCB->AIRCR =0X05FA0000|(u32)0x04;	  
} 	
