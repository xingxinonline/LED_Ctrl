/*********************************************************************/
/*��˾����:  ������ˮ����Ƽ����޹�˾                              */
/*ģ �� ���� DTU                          CPU�ͺţ�W77E58          */
/*�� �� �ˣ�yangm_cui                     ���ڣ�2012-05-01           */
/*�� �� �ˣ�yangm_cui                     ���ڣ�2012-05-22           */ 
/*���������� ��������ת��ͷ�ļ�                             		*/
/*����˵����                                                         */
/*��    ����V1.0												*/
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
