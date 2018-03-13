#ifndef __FLASH_H
#define __FLASH_H			    
#include "sys.h" 

//W25Xϵ��/Qϵ��оƬ�б�	   
//W25Q80 ID  0XEF13
//W25Q16 ID  0XEF14
//W25Q32 ID  0XEF15
//W25Q32 ID  0XEF16	
#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16

extern u16 SPI_FLASH_TYPE;//��������ʹ�õ�flashоƬ�ͺ�

#define	SPI_FLASH_CS PBout(12)  //ѡ��FLASH	
#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_4)				 
////////////////////////////////////////////////////////////////////////////
 
//ָ���
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


/* //��������w25q64 
	*w25q64 �ܹ���64M����0x800��������ÿ������4K���ֽڼ�0x1000���ֽ�
	*����������Ϊ��Ԫ��ʼд����ַ��0x100X0x100��ʼ�洢����
	*��0x1000X0x1000 ��ַ��ʼ�洢�洢RTUЭ������ ����ÿ��31��ÿ��24������ÿ������4K�ռ�洢����ѭ����ȡ
	*1��վ�� 31x24=744=0x2e8��4K�ռ� 
	*����ʮ���ռ�ռ��10���豸ÿ���豸24��4K�ռ��ܹ�240������
	*
	*
****************** */
#define DISPLAYCONTENT  				0xe0//��ʾ�����ǻ�ӭ������������  0xf0--0xf1
#define SCREEMNUM 					 	0xe1//��ʾ�����ǻ�ӭ������������  0xf0--0xf1
#define BQ_TIME_POWER_FlshADDR			0xe2
#define BQ_LIGHT_FlshADDR			    0xe3//���õ���Ļ����


#define LEDCTRL_WORKMODE			    0xe4//����ģʽ
#define LEDCTRL_WAKETIME			    0xe5//����ʱ��
#define LEDCTRL_WAKESTAY			    0xe6//���ѳ���ʱ��
#define LEDCTRL_BAUDRATE			    0xe7//������
#define LEDCTRL_DAYSTART			    0xe8//����������������������ʱ��
#define LEDCTRL_HOURSTART			    0xe9//ʱ����������ʱ����������ʱ��
#define LEDCTRL_LEDSTATUS			    0xea//״̬��
#define LEDCTRL_AreaCode			    0xeb//8�ֽ�����

#define YRAINBASEADDR  				0xf0//��������
#define TRAINBASEADDR  				0xf1//��������
#define ALLRAINBASEADDR  			0xf2//�ۼ�����
#define HRAINBASEADDR  				0xf3//ʱ������
#define LASTHRAINBASEADDR  			0xf4//��ʱ������
#define WATERBASEADDR  				0xf5//��ǰˮλ
#define FLOWBASEADDR  				0xf6//��ǰ����
#define CAPABASEADDR  				0xf7//��ǰ����
#define TEMPBASEADDR  				0xf8//��ǰ�¶�
#define HUMIBASEADDR  				0xf9//��ǰʪ��
#define VOLBASEADDR  				0xfa//��ǰʪ��

#define WELCOMEBASEADDR  				0x100//�Զ��延ӭ��Ϣ  0x10A--0x114
#define ADDRepotRdataBASEADDR  	0x110// 0x110-0x119//�洢ʮ��RTU��1�ŵ�10�ŵ������ӱ�����
#define ADDRepotWdataBASEADDR  	0x120// 0x120-0x129//�洢ʮ��RTU��1�ŵ�10�ŵ�ˮλ�ӱ�����
#define SCREENdataBASEADDR  		0x150// 0x150-0x200�洢ʮ��ҳ����Ҫ��ʾ������ ����֧��0x50����ͬ��ʾ��ҳ��
#define RTUparaBASEADDR  				0x200 // 0x200-0x200//�洢RTU�Ĳ���
#define WaterLevelThresholdADDR 0x280 //ˮλ��ֵ�洢��
#define PotrlRTUxDATASAVEBASIC  0x300//�洢RTU�����㱨���ݣ�ÿ��վ�ŷ���1���������洢ÿ��24Сʱ���㱨 ÿ�����24�ΰ��ɲ� 100000�μ���Լ�ɲ�10�ꣻ

#define DATA_MARKT      0x400*0x1000

void SPI_Flash_Init(void);
u16  SPI_Flash_ReadID(void);  	    //��ȡFLASH ID
u8	 SPI_Flash_ReadSR(void);        //��ȡ״̬�Ĵ��� 
void SPI_FLASH_Write_SR(u8 sr);  	//д״̬�Ĵ���
void SPI_FLASH_Write_Enable(void);  //дʹ�� 
void SPI_FLASH_Write_Disable(void);	//д����
void SPI_Flash_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //��ȡflash
void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//д��flash
void SPI_Flash_Erase_Chip(void);    	  //��Ƭ����
void SPI_Flash_Erase_Sector(u32 Dst_Addr);//��������
void SPI_Flash_Wait_Busy(void);           //�ȴ�����
void SPI_Flash_PowerDown(void);           //�������ģʽ
void SPI_Flash_WAKEUP(void);			  //����
void WriteDATAtoFlash(u8 addr,u16 dat,u8 offset);
void ReadDATAfromFlash(u8 type,u8 *DatAdrr,u8 offset);
#endif
















