
#include <stdio.h>
#include <stdarg.h>
#include <sys.h>
#define DEBUG_Pf
void Debug_printf(const char* format, ...)
{
	#ifdef DEBUG_Pf
	va_list args;

	va_start(args,format);
	vprintf(format,args); //������vprintf
	va_end(args);
	#else
	  (void)format;
	#endif
	
}

void Debug_printf_buf(const char *str,u8* buf ,u32 len,char string){
	#ifdef DEBUG_Pf
	u32 i;

	
	printf("%s\n",str);
	printf("\n");
	for(i = 0;i < len;i++){
		if('d'== string )	
	printf("%d ",buf[i]);
		else 
	printf("%02X ",buf[i]);
	}
	printf("\r\n");
	#else
	  (void)buf;
		(void)len;
	#endif
}
extern Radio_data_type  Radio_data;
void TimePrint_dbg(void)
{
	u8 t,tmp[2];
	GetDS3231Temp(tmp);
	t=calendar.min/5+1;
	printf("\n  \\ | /    \r\n");
	if(tmp[0]&0x80)
	{
		tmp[0]&=0x7F;
		
		printf(" -  %.2d -   ��ǰ�¶�Ϊ-%.2d.%.2d�� ",t,tmp[0],tmp[1]);
	}
	else
	{
		printf(" -  %.2d -   ��ǰ�¶�Ϊ%.2d.%.2d�� ",t,tmp[0],tmp[1]);
	}
	printf("%ld��%.2d��%.2d�� ",(unsigned long)calendar.w_year+2000,calendar.w_month,calendar.w_date);
	printf("%.2dʱ%.2d��%.2d��  \r\n",calendar.hour,calendar.min,calendar.sec);
	printf("  / | \\    \r\n\r\n");
}

