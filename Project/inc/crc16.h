#ifndef __CRC16_H__
#define __CRC16_H__
unsigned int crc16(unsigned char *puchMsg, unsigned int usDataLen);
unsigned int crc16modbus(unsigned char *puchMsg, unsigned int usDataLen);
unsigned int CRC16RTU( unsigned char * pszBuf, unsigned int unLength);
//unsigned char CRC7(unsigned char *in_data,unsigned char len);
unsigned int crc16_ctrl(unsigned char *databuf, unsigned int size);

#endif
