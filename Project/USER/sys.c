#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 

//********************************************************************************  
// void NVIC_Configuration(void)
// {

   // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

// }


/*
#define DISPLAYCONTENT  				0xe0//��ʾ�����ǻ�ӭ������������  0xf0--0xf1
#define SCREEMNUM 					 		0xe1//��ʾ�����ǻ�ӭ������������  0xf0--0xf1
#define YRAINBASEADDR  					0xf0//��������1�ŵ�10��  0xf0--0xf1
#define WELCOMEBASEADDR  				0x10A//�Զ��延ӭ��Ϣ  0x10A--0x114
#define ADDRepotRdataBASEADDR  	0x110// 0x110-0x119//�洢ʮ��RTU��1�ŵ�10�ŵ������ӱ�����
#define ADDRepotWdataBASEADDR  	0x120// 0x120-0x129//�洢ʮ��RTU��1�ŵ�10�ŵ�ˮλ�ӱ�����
#define SCREENdataBASEADDR  		0x150// 0x150-0x200�洢ʮ��ҳ����Ҫ��ʾ������ ����֧��0x50����ͬ��ʾ��ҳ��
#define RTUparaBASEADDR  				0x200 // 0x200-0x200//�洢RTU�Ĳ���

#define PotrlRTUxDATASAVEBASIC  0x300//�洢RTU�����㱨���ݣ�ÿ��վ�ŷ���1���������洢ÿ��24Сʱ���㱨 ÿ�����24�ΰ��ɲ� 100000�μ���Լ�ɲ�10�ꣻ
*/

void System_Init()
{
	u8 i;
	for(i=0;i<16;i++)//���� ��ʾҳ
	{
		SPI_Flash_Erase_Sector((u32)DISPLAYCONTENT+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//���� ��ʾҳ
	{
		SPI_Flash_Erase_Sector((u32)YRAINBASEADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//���� ��ʾҳ
	{
		SPI_Flash_Erase_Sector((u32)WELCOMEBASEADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//���� ��ʾҳ
	{
		SPI_Flash_Erase_Sector((u32)ADDRepotRdataBASEADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//���� ��ʾҳ
	{
		SPI_Flash_Erase_Sector((u32)ADDRepotWdataBASEADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//���� ��ʾҳ
	{
		SPI_Flash_Erase_Sector((u32)SCREENdataBASEADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//���� ��ʾҳ
	{
		SPI_Flash_Erase_Sector((u32)RTUparaBASEADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//���� ��ʾҳ
	{
		SPI_Flash_Erase_Sector((u32)WaterLevelThresholdADDR+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
	for(i=0;i<16;i++)//���� ��ʾҳ
	{
		SPI_Flash_Erase_Sector((u32)PotrlRTUxDATASAVEBASIC+(u32)i);
		#ifdef WTD
		IWDG_Feed();
		#endif
	}
}
//ϵͳ��λ   
		//SW_RESET();
	//	Sys_Soft_Reset();
void Sys_Soft_Reset(void)
{  
		delay_ms(30);
	SCB->AIRCR =0X05FA0000|(u32)0x04;	  
} 	
