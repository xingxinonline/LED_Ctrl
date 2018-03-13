#ifndef __FLASH_H
#define __FLASH_H			    
#include "sys.h" 

//W25X系列/Q系列芯片列表	   
//W25Q80 ID  0XEF13
//W25Q16 ID  0XEF14
//W25Q32 ID  0XEF15
//W25Q32 ID  0XEF16	
#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16

extern u16 SPI_FLASH_TYPE;//定义我们使用的flash芯片型号

#define	SPI_FLASH_CS PBout(12)  //选中FLASH	
#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_4)				 
////////////////////////////////////////////////////////////////////////////
 
//指令表
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 


/* //容量分配w25q64 
	*w25q64 总共有64M容量0x800个扇区，每个扇区4K个字节即0x1000个字节
	*现在以扇区为单元开始写基地址从0x100X0x100开始存储数据
	*从0x1000X0x1000 地址开始存储存储RTU协议数据 按照每月31天每天24包数据每包数据4K空间存储数据循环存取
	*1个站需 31x24=744=0x2e8个4K空间 
	*开辟十个空间空间给10个设备每个设备24个4K空间总共240个扇区
	*
	*
****************** */
#define DISPLAYCONTENT  				0xe0//显示内容是欢迎还是正常内容  0xf0--0xf1
#define SCREEMNUM 					 	0xe1//显示内容是欢迎还是正常内容  0xf0--0xf1
#define BQ_TIME_POWER_FlshADDR			0xe2
#define BQ_LIGHT_FlshADDR			    0xe3//配置的屏幕亮度


#define LEDCTRL_WORKMODE			    0xe4//工作模式
#define LEDCTRL_WAKETIME			    0xe5//唤醒时间
#define LEDCTRL_WAKESTAY			    0xe6//唤醒持续时间
#define LEDCTRL_BAUDRATE			    0xe7//波特率
#define LEDCTRL_DAYSTART			    0xe8//昨日雨量、今日雨量更新时间
#define LEDCTRL_HOURSTART			    0xe9//时段雨量、上时段雨量更新时间
#define LEDCTRL_LEDSTATUS			    0xea//状态灯
#define LEDCTRL_AreaCode			    0xeb//8字节区号

#define YRAINBASEADDR  				0xf0//昨日雨量
#define TRAINBASEADDR  				0xf1//今日雨量
#define ALLRAINBASEADDR  			0xf2//累计雨量
#define HRAINBASEADDR  				0xf3//时段雨量
#define LASTHRAINBASEADDR  			0xf4//上时段雨量
#define WATERBASEADDR  				0xf5//当前水位
#define FLOWBASEADDR  				0xf6//当前流量
#define CAPABASEADDR  				0xf7//当前库容
#define TEMPBASEADDR  				0xf8//当前温度
#define HUMIBASEADDR  				0xf9//当前湿度
#define VOLBASEADDR  				0xfa//当前湿度

#define WELCOMEBASEADDR  				0x100//自定义欢迎信息  0x10A--0x114
#define ADDRepotRdataBASEADDR  	0x110// 0x110-0x119//存储十个RTU从1号到10号的雨量加报数据
#define ADDRepotWdataBASEADDR  	0x120// 0x120-0x129//存储十个RTU从1号到10号的水位加报数据
#define SCREENdataBASEADDR  		0x150// 0x150-0x200存储十个页面屏要显示的数据 本屏支持0x50个不同显示的页面
#define RTUparaBASEADDR  				0x200 // 0x200-0x200//存储RTU的参数
#define WaterLevelThresholdADDR 0x280 //水位阈值存储区
#define PotrlRTUxDATASAVEBASIC  0x300//存储RTU的整点报数据，每个站号分配1个扇区，存储每天24小时整点报 每天擦除24次按可擦 100000次计算约可擦10年；

#define DATA_MARKT      0x400*0x1000

void SPI_Flash_Init(void);
u16  SPI_Flash_ReadID(void);  	    //读取FLASH ID
u8	 SPI_Flash_ReadSR(void);        //读取状态寄存器 
void SPI_FLASH_Write_SR(u8 sr);  	//写状态寄存器
void SPI_FLASH_Write_Enable(void);  //写使能 
void SPI_FLASH_Write_Disable(void);	//写保护
void SPI_Flash_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //读取flash
void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//写入flash
void SPI_Flash_Erase_Chip(void);    	  //整片擦除
void SPI_Flash_Erase_Sector(u32 Dst_Addr);//扇区擦除
void SPI_Flash_Wait_Busy(void);           //等待空闲
void SPI_Flash_PowerDown(void);           //进入掉电模式
void SPI_Flash_WAKEUP(void);			  //唤醒
void WriteDATAtoFlash(u8 addr,u16 dat,u8 offset);
void ReadDATAfromFlash(u8 type,u8 *DatAdrr,u8 offset);
#endif
















