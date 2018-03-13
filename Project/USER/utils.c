
#include "sys.h"

unsigned int HexToAscII(unsigned char hexData)
{
	unsigned char  High,Low;
	High = (hexData&0xF0)>>4;
	Low  = hexData&0x0F;
	if (High > 0x09)High += 0x37;
	else High += 0x30;
	if(Low > 0x09)Low += 0x37;
	else Low += 0x30;
	return (High<<8)|Low;
}
void AscToHex(unsigned char  *ascData,unsigned char len)
{
	unsigned char  i;
	for (i=0;i<len;i++)
	{
		if (ascData[i]>='0'&&ascData[i]<='9')ascData[i] -= 0x30;
		else if (ascData[i]>='A'&&ascData[i]<='F')ascData[i] -= 0x37;
		else if (ascData[i]>='a'&&ascData[i]<='f')ascData[i] -= 0x57;
	}
}

/* unsigned long str_to_ulong(	const unsigned char xdata * buf,const unsigned char len)
{
	unsigned char i;
	unsigned long res = 0;
	for( i=0; i < len; i++ )
	{
		res = res * 10 + buf[i] - 0x30;
	}
	return res;
}
 */
/* unsigned long hexbuf_to_ulong(	const unsigned char xdata * buf,const unsigned char len)
{
	unsigned char i;
	unsigned char tmp;
	unsigned long res = 0;
	for( i=0; i < len; i++ )
	{
		tmp = buf[i];
		res = res*100UL+ (10UL*(tmp>>4) + (tmp&0x0f));
		
	}
	return res;
} */

//格雷码转二进制
/* unsigned int GraytoHex(unsigned int x)
{
	unsigned int y = x;
         while(x>>=1)
           y ^= x;
          return y;

} */
//二进制转格雷码
/* unsigned int HexToGray(unsigned int xdata HexData)
{
	return HexData^(HexData>>1);
}



 */




/***************************
   hex to bcd 转换程序
***************************/
unsigned long hextobcd(unsigned int hexs)
 {

	unsigned int  va;
	unsigned char   i;
	unsigned char disp_buffer[5];
		va = 10000;								//最大数级万位
		for(i=4;i;i--) 
			{
				disp_buffer[i] = 0;				//目标数组清零
				while ((hexs>=va)&&(va>9)) 
					{
						hexs -= va;				//减除数
						disp_buffer[i]++;		//商位加1
					}
					va /= 10;					//除数除10，指向低一位
			}
		disp_buffer[0]=hexs;						//最后个位数
	return ((unsigned long)disp_buffer[4]<<16)|(disp_buffer[3]<<12)|(disp_buffer[2]<<8)|(disp_buffer[1]<<4)|disp_buffer[0];	
} 
/* unsigned char ulonghextobcd(unsigned long hexs,unsigned char *buf)
{
	unsigned char i,len;
	unsigned char xdata a[12];
	unsigned long val;
	len = 0;
	val  = hexs;
	for (i=0;i<12;i++)
	{
		a[len++] = val%10;
		val /= 10;
		if (val == 0)
		{
			for (i=0;i<len;i++)
			{
				if (i%2==0)
				{
					buf[i/2]=a[i];
				}
				else
				{
					buf[i/2]|=(a[i]<<4);
				}
			}
			if (len%2==0)
					return len/2;
				else 
					return len/2+1;
		}
	}
	return len;
}  */
/* BCD to HEX */
unsigned char BcdtoHex(unsigned char dat)
{
	unsigned char  tmp;
	tmp = dat&0xf0;
	tmp >>= 4;
	tmp *= 10;
	tmp += dat&0x0f;
	return tmp;
}


/* unsigned long ascii_to_ulong(const unsigned char xdata * buf,\
						   const unsigned char len,\
						   const bit ignore_dot )
{
	unsigned char i;
	unsigned long res = 0;
	for( i = 0; buf[i] == 0x30; i++ );
	for( ; i < len; i++ )
	{
		if( ignore_dot && buf[i] == 0x2E)
		{
			continue;
		}
		res = res * 10 + buf[i] - 0x30;
	}
	return res;
} */

/* 例如：val=123456  */
unsigned char ulong_to_ascii(unsigned char  * res,  u32 val,unsigned char dot_pos,u8 sign)	 				  					   
{
	unsigned char len = 0,i;
	unsigned char high, low =0;
	u8 tmp[8];
	
	res[len++] = val % 10 + '0';		    // res[0]='6'
	val /= 10;
	while(val)
	{
		res[len++] = val % 10 + '0';
		val /= 10;
	}
	high = len - 1;
	while(low < high)
	{
		unsigned char tmp = res[low];
		res[low] = res[high];
		res[high] = tmp;
		high--;
		low++;
	}
	if(sign==1){
		tmp[0]='-';
		for(i=0;i<len;i++)
		{
			tmp[i+1]=res[i];
		}
		len++;
		for(i=0;i<len;i++)
		{
			res[i]=tmp[i];
		}
	}
	if( dot_pos > 0 )
	{
		high = len - 1;
		if( len > dot_pos )					// 例如：dot_pos=2
		{
			while( high >= len - dot_pos )
			{
				res[high + 1] = res[high];
				high--;
			}
			res[high + 1] = 0x2E;
			return len + 1;					// 返回 7
		}
		else
		{
            if( high > 0 )					// val=123456时，dot_pos>=6 均会执行该分支，且返回相同结果
            {
			    while( high > 0 )
			    {
				     res[high + 2] = res[high];
				     high--;
			    }
			    res[2] = res[0];
			    res[1] = 0x2E;
			    res[0] = 0x30;
			    return len + 2;
             }								// 返回 8
             else							// 只有val 为1位数且dot_pos>0时，会执行到此,例如val=8 dot_pos=3
             {
                res[dot_pos + 1] = res[high];		  // res[4]='8'
                for( low = 0; low <= dot_pos; low ++ )
                {
                    res[low] = '0';
                }
                res[1] = 0x2E;
				// res[0]='0' res[1]='.' res[2]='0' res[3]='0' res[4]='8'
                return dot_pos + 2;			// 返回 5
            }
		}
	}
	
	return len;								// dot_pos<=0时执行到此， 返回 6
}
