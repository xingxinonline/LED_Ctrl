/*********************************************************************/
/*公司名称:  北京金水燕禹科技有限公司                              */
/*模 块 名： DTU                          CPU型号：W77E58          */
/*创 建 人：yangm_cui                     日期：2012-05-01           */
/*修 改 人：yangm_cui                     日期：2012-05-22           */ 
/*功能描述： 数据类型转换头文件                             		*/
/*其他说明：                                                         */
/*版    本：V1.0												*/
/**********************************************************************/
#ifndef _utils_h_
#define _utils_h_
//#include <INTRINS.H>
#include "sys.h"
unsigned int HexToAscII(unsigned char hexData);
void AscToHex(unsigned char /* xdata */ *ascData,unsigned char len);
unsigned long hextobcd(unsigned int hexs);
unsigned char BcdtoHex(unsigned char dat);
//unsigned int GraytoHex(unsigned int GrayCode);
//unsigned int HexToGray(unsigned int HexData);
// void HexBufToAscIIBuf(unsigned char *AscIIBuf,unsigned char *hexBuf,unsigned char len);
//unsigned long str_to_ulong(	const unsigned char xdata * buf,const unsigned char len);
//unsigned char ulonghextobcd(unsigned long hexs,unsigned char *buf);
//unsigned long hexbuf_to_ulong(	const unsigned char xdata * buf,const unsigned char len);
//unsigned long ascii_to_ulong(const unsigned char xdata * buf,
//						   const unsigned char len,
//						   const bit ignore_dot );
unsigned char ulong_to_ascii(unsigned char  * res,u32 val,unsigned char dot_pos,u8 sign);

#endif
