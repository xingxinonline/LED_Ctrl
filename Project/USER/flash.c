#include "flash.h" 
#include "spi.h"
#include "delay.h"   
/********************  **************************
 * 文件名  ：flash.c
 * 描述    ：   
 * 库版本  ：ST3.5.0
 *
 * 作者    ：King
 * 日期		 ：2014年10月27日
**********************************************************************************/


u16 SPI_FLASH_TYPE=W25Q64;//默认就是25Q64

//4Kbytes为一个Sector
//16个扇区为1个Block
//W25X16
//容量为2M字节,共有32个Block,512个Sector 

//初始化SPI FLASH的IO口
void SPI_Flash_Init(void)
{	
  
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable SPI1 and GPIO clocks */
  /*!< SPI_FLASH_SPI_CS_GPIO, SPI_FLASH_SPI_MOSI_GPIO, 
       SPI_FLASH_SPI_MISO_GPIO, SPI_FLASH_SPI_DETECT_GPIO 
       and SPI_FLASH_SPI_SCK_GPIO Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);

  /*!< SPI_FLASH_SPI Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
 
  
  /*!< Configure SPI_FLASH_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*!< Configure SPI_FLASH_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*!< Configure SPI_FLASH_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*!< Configure SPI_FLASH_SPI_CS_PIN pin: SPI_FLASH Card CS pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* SPI1 configuration */
  // W25X16: data input on the DIO pin is sampled on the rising edge of the CLK. 
  // Data on the DO and DIO pins are clocked out on the falling edge of CLK.
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);
  /* Enable SPI1  */
  SPI_Cmd(SPI1, ENABLE);
}  

//读取SPI_FLASH的状态寄存器
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
u8 SPI_Flash_ReadSR(void)   
{  
	u8 byte=0;   
	SPI_FLASH_CS_LOW() ;                            //使能器件   
	SPI1_ReadWriteByte(W25X_ReadStatusReg);    //发送读取状态寄存器命令    
	byte=SPI1_ReadWriteByte(0Xff);             //读取一个字节  
	SPI_FLASH_CS_HIGH() ;                            //取消片选     
	return byte;   
} 
//写SPI_FLASH状态寄存器
//只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
void SPI_FLASH_Write_SR(u8 sr)   
{   
	SPI_FLASH_CS_LOW() ;                            //使能器件   
	SPI1_ReadWriteByte(W25X_WriteStatusReg);   //发送写取状态寄存器命令    
	SPI1_ReadWriteByte(sr);               //写入一个字节  
	SPI_FLASH_CS_HIGH() ;                            //取消片选     	      
}   
//SPI_FLASH写使能	
//将WEL置位   
void SPI_FLASH_Write_Enable(void)   
{
	SPI_FLASH_CS_LOW();                            //使能器件   
    SPI1_ReadWriteByte(W25X_WriteEnable);      //发送写使能  
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
} 
//SPI_FLASH写禁止	
//将WEL清零  
void SPI_FLASH_Write_Disable(void)   
{  
	SPI_FLASH_CS_LOW() ;                            //使能器件   
    SPI1_ReadWriteByte(W25X_WriteDisable);     //发送写禁止指令    
	SPI_FLASH_CS_HIGH() ;                            //取消片选     	      
} 			    
//读取芯片ID W25X16的ID:0XEF14
u16 SPI_Flash_ReadID(void)
{
	u16 Temp = 0;	  
	SPI_FLASH_CS_LOW();				    
	SPI1_ReadWriteByte(0x90);//发送读取ID命令	    
	SPI1_ReadWriteByte(0x00); 	    
	SPI1_ReadWriteByte(0x00); 	    
	SPI1_ReadWriteByte(0x00); 	 			   
	Temp|=SPI1_ReadWriteByte(0xFF)<<8;  
	Temp|=SPI1_ReadWriteByte(0xFF);	 
	SPI_FLASH_CS_HIGH();				    
	return Temp;
}   		    
//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(24bit)
//NumByteToRead:要读取的字节数(最大65535)
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
 	u16 i;    												    
	SPI_FLASH_CS_LOW() ;                            //使能器件   
    SPI1_ReadWriteByte(W25X_ReadData);         //发送读取命令   
    SPI1_ReadWriteByte((u8)((ReadAddr)>>16));  //发送24bit地址    
    SPI1_ReadWriteByte((u8)((ReadAddr)>>8));   
    SPI1_ReadWriteByte((u8)ReadAddr); 
	
    for(i=0;i<NumByteToRead;i++)
	{ 
        pBuffer[i]=SPI1_ReadWriteByte(0XFF);   //循环读数  
    }
	SPI_FLASH_CS_HIGH() ;                            //取消片选     	      
}  
//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	 
void SPI_Flash_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
 	u16 i;  
    SPI_FLASH_Write_Enable();                  //SET WEL 
	SPI_FLASH_CS_LOW() ;                            //使能器件   
    SPI1_ReadWriteByte(W25X_PageProgram);      //发送写页命令   
    SPI1_ReadWriteByte((u8)((WriteAddr)>>16)); //发送24bit地址    
    SPI1_ReadWriteByte((u8)((WriteAddr)>>8));   
    SPI1_ReadWriteByte((u8)WriteAddr);
	
    for(i=0;i<NumByteToWrite;i++)SPI1_ReadWriteByte(pBuffer[i]);//循环写数  
	SPI_FLASH_CS_HIGH() ;                            //取消片选 
	SPI_Flash_Wait_Busy();					   //等待写入结束
} 
//无检验写SPI FLASH 
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
void SPI_Flash_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 			 		 
	u16 pageremain;	   
	pageremain=256-WriteAddr%256; //单页剩余的字节数		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//不大于256个字节
	while(1)
	{	   
		SPI_Flash_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//写入结束了
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //减去已经写入了的字节数
			if(NumByteToWrite>256)pageremain=256; //一次可以写入256个字节
			else pageremain=NumByteToWrite; 	  //不够256个字节了
		}
	};	    
} 
//写SPI FLASH  
//在指定地址开始写入指定长度的数据
//该函数带擦除操作!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)  		   
u8 SPI_FLASH_BUF[4096];
void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
	u32 secpos;
	u16 secoff;
	u16 secremain;	   
 	u16 i;    

	#ifdef WTD
	IWDG_Feed();
	#endif
	secpos=WriteAddr/4096;//扇区地址 0~511 for w25x16
	secoff=WriteAddr%4096;//在扇区内的偏移
	secremain=4096-secoff;//扇区剩余空间大小   

	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//不大于4096个字节
	while(1) 
	{	
		SPI_Flash_Read(SPI_FLASH_BUF,secpos*4096,4096);//读出整个扇区的内容
		
		for(i=0;i<secremain;i++)//校验数据
		{
			if(SPI_FLASH_BUF[secoff+i]!=0XFF)break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
			SPI_Flash_Erase_Sector(secpos);//擦除这个扇区
			for(i=0;i<secremain;i++)	   //复制
			{
				SPI_FLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			SPI_Flash_Write_NoCheck(SPI_FLASH_BUF,secpos*4096,4096);//写入整个扇区  

		}else SPI_Flash_Write_NoCheck(pBuffer,WriteAddr,secremain);//写已经擦除了的,直接写入扇区剩余区间. 				   
		if(NumByteToWrite==secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++;//扇区地址增1
			secoff=0;//偏移位置为0 	 

		   	pBuffer+=secremain;  //指针偏移
			WriteAddr+=secremain;//写地址偏移	   
		   	NumByteToWrite-=secremain;				//字节数递减
			if(NumByteToWrite>4096)secremain=4096;	//下一个扇区还是写不完
			else secremain=NumByteToWrite;			//下一个扇区可以写完了
		}	 
	};	 	 
}
//擦除整个芯片
//整片擦除时间:
//W25X16:25s 
//W25X32:40s 
//W25X64:40s 
//等待时间超长...
void SPI_Flash_Erase_Chip(void)   
{                                             
    SPI_FLASH_Write_Enable();                  //SET WEL 
    SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS_LOW() ;                            //使能器件   
    SPI1_ReadWriteByte(W25X_ChipErase);        //发送片擦除命令  
	SPI_FLASH_CS_HIGH() ;                            //取消片选     	      
	SPI_Flash_Wait_Busy();   				   //等待芯片擦除结束
}   
//擦除一个扇区
//Dst_Addr:扇区地址 0~511 for w25x16
//擦除一个山区的最少时间:150ms
void SPI_Flash_Erase_Sector(u32 Dst_Addr)   
{   
	Dst_Addr*=4096;
    SPI_FLASH_Write_Enable();                  //SET WEL 	 
    SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS_LOW() ;                            //使能器件   
    SPI1_ReadWriteByte(W25X_SectorErase);      //发送扇区擦除指令 
    SPI1_ReadWriteByte((u8)((Dst_Addr)>>16));  //发送24bit地址    
    SPI1_ReadWriteByte((u8)((Dst_Addr)>>8));   
    SPI1_ReadWriteByte((u8)Dst_Addr);  
	SPI_FLASH_CS_HIGH() ;                            //取消片选     	      
    SPI_Flash_Wait_Busy();   				   //等待擦除完成
}  
//等待空闲
void SPI_Flash_Wait_Busy(void)   
{   
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   // 等待BUSY位清空
}  
//进入掉电模式
void SPI_Flash_PowerDown(void)   
{ 
  	SPI_FLASH_CS_LOW() ;                            //使能器件   
    SPI1_ReadWriteByte(W25X_PowerDown);        //发送掉电命令  
	SPI_FLASH_CS_HIGH() ;                            //取消片选     	      
    delay_us(3);                               //等待TPD  
}   
//唤醒
void SPI_Flash_WAKEUP(void)   
{  
  	SPI_FLASH_CS_LOW() ;                            //使能器件   
    SPI1_ReadWriteByte(W25X_ReleasePowerDown);   //  send W25X_PowerDown command 0xAB    
	SPI_FLASH_CS_HIGH() ;                            //取消片选     	      
    delay_us(3);                               //等待TRES1
}   
//将RTU数据写入flash
void WriteDATAtoFlash(u8 type,u16 dat,u8 offset)
{
	u8 tmpbuf[2];
	get_show_time();
	switch(type)
	{
		case WATERL:
			tmpbuf[0] = dat>>8;
			tmpbuf[1] = dat;
			SPI_Flash_Write(tmpbuf,(((u32)WATERBASEADDR)<<12)+(2*offset),2);
		break;
		case CAPAC:
			tmpbuf[0] = dat>>8;
			tmpbuf[1] = dat;
			SPI_Flash_Write(tmpbuf,(((u32)CAPABASEADDR)<<12)+(2*offset),2);
		break;
		case WATER_F:
			tmpbuf[0] = dat>>8;
			tmpbuf[1] = dat;
			SPI_Flash_Write(tmpbuf,(((u32)FLOWBASEADDR)<<12)+(2*offset),2);
		break;
		case TRAIN:
			tmpbuf[0] = dat>>8;
			tmpbuf[1] = dat;
			SPI_Flash_Write(tmpbuf,(((u32)TRAINBASEADDR)<<12)+(2*offset),2);
		break;
		case HRAIN:
			tmpbuf[0] = dat>>8;
			tmpbuf[1] = dat;
			SPI_Flash_Write(tmpbuf,(((u32)HRAINBASEADDR)<<12)+(2*offset),2);
		break;
		case LRAIN:
			tmpbuf[0] = dat>>8;
			tmpbuf[1] = dat;
			SPI_Flash_Write(tmpbuf,(((u32)LASTHRAINBASEADDR)<<12)+(2*offset),2);
		break;
		case YRAIN:
			tmpbuf[0] = dat>>8;
			tmpbuf[1] = dat;
			SPI_Flash_Write(tmpbuf,(((u32)YRAINBASEADDR)<<12)+(2*offset),2);
		break;
		case ARAIN:
			tmpbuf[0] = dat>>8;
			tmpbuf[1] = dat;
			SPI_Flash_Write(tmpbuf,(((u32)ALLRAINBASEADDR)<<12)+(2*offset),2);
		break;
		case TEMPERATURE:
			tmpbuf[0] = dat>>8;
			tmpbuf[1] = dat;
			SPI_Flash_Write(tmpbuf,(((u32)TEMPBASEADDR)<<12)+(2*offset),2);
		break; 
		case HUMIDITY:
			tmpbuf[0] = dat>>8;
			tmpbuf[1] = dat;
			SPI_Flash_Write(tmpbuf,(((u32)HUMIBASEADDR)<<12)+(2*offset),2);
		break;
		case VOLTAGE:
			tmpbuf[0] = dat>>8;
			tmpbuf[1] = dat;
			SPI_Flash_Write(tmpbuf,(((u32)VOLBASEADDR)<<12)+(2*offset),2); 
		break;
	}
	
	
}
//将RTU数据写入flash
void ReadDATAfromFlash(u8 type,u8 *DatAdrr,u8 offset)
{
	u8 tmpbuf[2];
	switch(type)
	{
		case WATERL:
			SPI_Flash_Read(tmpbuf,(((u32)WATERBASEADDR)<<12)+(2*offset),2);
			*DatAdrr++ = tmpbuf[0];
			*DatAdrr   = tmpbuf[1];
		break;
		case CAPAC:
			SPI_Flash_Read(tmpbuf,(((u32)CAPABASEADDR)<<12)+(2*offset),2);
			*DatAdrr++ = tmpbuf[0];
			*DatAdrr   = tmpbuf[1];
		break;
		case WATER_F:
			SPI_Flash_Read(tmpbuf,(((u32)FLOWBASEADDR)<<12)+(2*offset),2);
			*DatAdrr++ = tmpbuf[0];
			*DatAdrr   = tmpbuf[1];
		break;
		case TRAIN:
			SPI_Flash_Read(tmpbuf,(((u32)TRAINBASEADDR)<<12)+(2*offset),2);
			*DatAdrr++ = tmpbuf[0];
			*DatAdrr   = tmpbuf[1];
		break;
		case HRAIN:
			SPI_Flash_Read(tmpbuf,(((u32)HRAINBASEADDR)<<12)+(2*offset),2);
			*DatAdrr++ = tmpbuf[0];
			*DatAdrr   = tmpbuf[1];
		break;
		case LRAIN:
			SPI_Flash_Read(tmpbuf,(((u32)LASTHRAINBASEADDR)<<12)+(2*offset),2);
			*DatAdrr++ = tmpbuf[0];
			*DatAdrr   = tmpbuf[1];
		break;
		case YRAIN:
			SPI_Flash_Read(tmpbuf,(((u32)YRAINBASEADDR)<<12)+(2*offset),2);
			*DatAdrr++ = tmpbuf[0];
			*DatAdrr   = tmpbuf[1];
		break;
		case ARAIN:
			SPI_Flash_Read(tmpbuf,(((u32)ALLRAINBASEADDR)<<12)+(2*offset),2);
			*DatAdrr++ = tmpbuf[0];
			*DatAdrr   = tmpbuf[1];
		break;
		case TEMPERATURE:
			SPI_Flash_Read(tmpbuf,(((u32)TEMPBASEADDR)<<12)+(2*offset),2);
			*DatAdrr++ = tmpbuf[0];
			*DatAdrr   = tmpbuf[1];
		break;
		case HUMIDITY:
			SPI_Flash_Read(tmpbuf,(((u32)HUMIBASEADDR)<<12)+(2*offset),2);
			*DatAdrr++ = tmpbuf[0];
			*DatAdrr   = tmpbuf[1];
		break;
		case VOLTAGE:
			SPI_Flash_Read(tmpbuf,(((u32)VOLBASEADDR)<<12)+(2*offset),2);
			*DatAdrr++ = tmpbuf[0];
			*DatAdrr   = tmpbuf[1];
		break;
	}
}
