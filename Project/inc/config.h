#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
// 
//#define DEBUGE
//#define SCREEN_DEBUGE
//#define RTU_DEBUGE
//#define POWER_DEBUGE
#define WTD
#define ON  1
#define OFF 0

//带参宏，可以像内联函数一样使用
#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_2);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_2)

#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_3);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_3)



//IO操作函数	
					

					
#define LEDSTATUS PCout(0x02)// PC4	
		
#define FLASHERR PCout(0x03)// PC5	


void GPIO_Config(void);
void USART1toEXTI(FunctionalState able);
void GPIO_NOUSE_Config(void);
void IWDG_Init(u8 prer,u16 rlr);
void IWDG_Feed(void);
void Debug_printf_buf(const char *str,u8* buf ,u32 len,char string);
void Debug_printf(const char* format, ...);
void TimePrint_dbg(void);					
#endif /* __LED_H */
