/*********************************************************************/
/*��˾����:  ������ˮ����Ƽ����޹�˾                              */
/*ģ �� ���� DTU                          CPU�ͺţ�W77E58          */
/*�� �� �ˣ�yangm_cui                     ���ڣ�2012-05-01           */
/*�� �� �ˣ�yangm_cui                     ���ڣ�2012-05-22           */ 
/*���������� ȫ�ֱ���ͷ�ļ�                                   	*/
/*����˵����                                                         */
/*��    ����V1.0												*/
/**********************************************************************/

#ifndef __GlobalVar_H__
#define __GlobalVar_H__
#include "sys.h"  

#define _task_idle				0x00	//��������
#define _Sleep_task				0x01	//˯��ģʽ����
#define _PC_task					0x02	//��PCͨ������
#define _Screen_task			0x04	//��Ļ��������
#define _Wakeup_task			0x08	//����ģʽ����
#define _Config_task			0x10	//����ģʽ����
#define _Serial_task			0x20	//����ģʽ����
#define _Start_task				0x40	//����ģʽ����
#define _LedStatus_task		0x80	//����ģʽ����

#define _key_wakeup				0x01	//��������
#define _serial_wakeup		0x02	//˯��ģʽ����
#define _DS3231_wakeup		0x03	//��PCͨ������

#define Screen_Power_On   	0x01
#define Screen_Self_Check   0x02
#define Screen_Data_Init    0x03
#define Screen_Data_Err  	0x04
#define Screen_Data_Right   0x05
#define Screen_Red_Check   	0x06
#define Screen_Red_Err  	0x07
#define Screen_Red_Right   	0x08
#define Screen_Check_Finish 0x09
#define Screen_Reset_Ready	0x0a

#define ALARM1						0x01
#define ALARM2						0x02

#define ALARM2_MINUTE	1
#define ALARM2_HOUR		60

#define USART1_REC_LEN  			512  	//�����������ֽ���512
#define UART5_REC_LEN  				128  	//�����������ֽ���512
#define RTU_NO 						10
#define RTU_DAY_START 		8

#define Open_LED_SCREEN()   GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define Close_LED_SCREEN()	GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define SET_POW_MAX3222()   GPIO_SetBits(GPIOD, GPIO_Pin_0);delay_ms(2)
#define CLR_POW_MAX3222()	delay_ms(2);GPIO_ResetBits(GPIOD, GPIO_Pin_0)

#define SET_POW_USART1_DTR()  	GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define CLR_POW_USART1_DTR()	GPIO_ResetBits(GPIOB, GPIO_Pin_12)

#define GPIOA_NOUSE 		(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_11| GPIO_Pin_15 )
#define GPIOB_NOUSE			(GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10| GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15)
#define GPIOC_NOUSE			(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9  | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)
#define GPIOD_NOUSE			(GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)
#define GPIOE_NOUSE			(GPIO_Pin_All)


#define RCC_APB1_SLEEP_NOUSE		(RCC_APB1Periph_SPI2	|	RCC_APB1Periph_UART4 |	RCC_APB1Periph_UART5)
#define RCC_APB2_SLEEP_NOUSE		(RCC_APB2Periph_GPIOB	| 	RCC_APB2Periph_GPIOE |  RCC_APB2Periph_SPI1)


#define RAIN_MAX 4096

//UART
extern u16 Voltage[RTU_NO];
extern u16 Rain_all[RTU_NO];
extern u16 Rain_Yall[RTU_NO];
extern u16 Rain_hour[RTU_NO];
extern u16 Rain_Lhour[RTU_NO];
extern u16 Rain_day[RTU_NO];
extern u16 Rain_Yday[RTU_NO];
extern u32 Water[RTU_NO];
extern u32 Water_flow[RTU_NO];
extern u16 Water_Level_Threshold;
extern u32 PageAlarm;
extern u8 BQSystime[8];
extern u8 Uart5_Recving;
extern u8 Uart5_recvDone;
extern u8 RecvFromUART5_Buf[UART5_REC_LEN];
extern u16 RecvFromUART5_Len;
extern u8 Read_sys_para;
extern u8 Uart5senddataprority;
extern u8 Uart3senddataprority;
extern u8 BQSystimeERR;
extern u8 Uart1_Recving;
extern u16 RecvFromUART1_Len;
extern u8 WhetherDirect;
extern u8 RecvFromUART1_Buf[USART1_REC_LEN];
extern u8  SendToCtrl_Buf[USART1_REC_LEN];
extern u16 SendToCrtl_Len;
extern u16 UART_7E7EFrameLen;
extern u16 UART_68BFrameLen;
extern u16 UART_15BFrameLen;
extern u16 LenfpcforBQ;
extern u8 RTUCurrentHour;
extern u8 DisplayPageNum;
extern u8 Displaycontent;
extern u8 DisplayPageno; 
extern u8 DisplayPagesub; 
extern u8 DisplayStayTime;
extern u8 DisplayRunTime; 
extern u8 DisplayChangeEN;
extern u8 DisplayPowerOnEN;
extern u8 DisplayPowerOnRunTime;
extern u8 DisplayPowerOnRunTimeStart;
extern u8 DisplayPowerOnRunTimeCnt;
extern u8 bflagRedBoard_Check;
extern u8 Uart1_recvDone;
extern u8 RTUnum;

extern u8 bflagminute;
extern u8 bflagfivemin;
extern u8 bflaghour;
extern u8 bflagday;
extern u8 bflaghourstart;
extern u8 bflagdaystart;

extern u8 bflagScreenConfigstart;
extern u32 bflagScreenConfigcnt;
extern u8 bflagsystemstart;
extern u32 System_Start_time;
extern u8 Uart_time_Start;
extern u8 Uart_time_num;
extern u8 Uart_serailport_num;
extern u8 Uart_waketime_num;
extern u8 Timer_IRQ_flag;
extern u16 CurrentCMD;
extern u8 Hardware_check_flag;
extern u8 RebackPC_time;
extern u8 Start_display;
extern u8 BQ_reback_timer;//
extern u8 RTC_check_already;
extern u8 RTC_check_finish;
extern u8 bflag_configlight;
extern u8 Time_power_enable;
extern u8 Time_power_on;
extern u8 Alarm_enable;
extern u8 Alarm_flag;
extern u8 Alarm1_flag;
extern u8 Alarm2_flag;
extern u8 TIM3_flag;
extern u8 screen_flag;
extern u8 Alarm_enable_reflash;
extern u8 test;
extern u8 test01;
extern u8 bflag68byte;
extern u8 bflag15byte;
extern u8 bflag8byte;
//extern u32  GroundWater;
//extern  u16 C_rain;
extern u8 task_cnt;
extern u32 Wakeup_Reason;
extern u8 	bflagwakeup;
// extern u8  idata UART0_B;
// extern u8  idata UART1_B;
// extern u8 Uart0_Recving;
// extern u8 Uart1_Recving;
// extern u8 xdata SendToCrtl_Len;
// extern u16 RecvFromUART_Len;
// extern u16 Lenfpc;

// extern u8 RecvFromBoard_Len;
// extern u8 idata uchRecDataFromRTU[20];
// extern u8 RecvFromUART_Buf[255];
// extern u8  SendToCtrl_Buf[247];
// extern u8 Uart0_FrameLen;
// extern u16 Secondcont;
 extern  u8 RTUIDbuf[100];
// extern  u8 Uart1_recvDone;
// extern  u8 CurrentRTUID;
// extern bit bflag_uart0_recvDone;
// extern bit bflag_uart0_C_recvDone;
// extern bit bflag_uart0_recvStr;

// extern bit bFlag_uart1_to_uart0;
// extern bit Response;

// extern bit bflag_uart1_recvEnable;

//uart2 send data priority
#define NORMALDADT_UART5 0x00
#define SYSPARADADT_UART5 0x01


typedef enum {
  PC_BQ_DATA =2, PCPROTOCOL7E7EDATA, PCPROTOCOL68DATA,PTL15DATA,PTL8DATA, DIRECTTOBQ,BQREBACK,
} DATA_TypeDef;
typedef enum {
  COM1 =1, COM4, COM5,
} COM_TypeDef;
typedef enum {
	ETX=0x03,//��ʾ����
	ETB=0x17,//��ʾ����δ����
	ACK=0x06, //��ʾ�ɹ����գ�Ҫ���������
	NAK=0x15,//��ʾУ���Ҫ���ط���
	EOT=0x04,//��ʾ��������������������
	ENQ=0x05,//��ʾ�������������������񣨹�̬��ȡ��Զ�̲����޸ĵȣ���
} DATA_Reback_TypeDef;

typedef enum {
  WATERL=1/*ˮλ*/, CAPAC/*����*/,WATER_F/*����*/,TRAIN/*��������*/,HRAIN/*ʱ������*/,LRAIN/*��ʱ������*/,  \
	YRAIN /*��������*/,ARAIN/*�ۼ�����*/,YARAIN/*�ۼ�����*/,TEMPERATURE/*�¶�*/, HUMIDITY/*ʪ��*/, STATIONNAME/*վ��*/,VOLTAGE/*��ѹ*/,
} SCREENDATA_TypeDef;

typedef enum {
  RTU1=0,RTU2,RTU3,RTU4,RTU5,RTU6,RTU7,RTU8,RTU_NUM,
} RTUID_TypeDef;

typedef enum {
  DS=11,
  L_RAIN=12,
  B_WATER=14,
  MK=18,
  CR_MONTH=19,
} RTUID_ParaDef;
typedef enum {
  DIS_ALL = 0, DIS_RAIN, DIS_WAT, DIS_TEMP, DIS_HUMI,
} DISPLAY;
typedef enum {
   STAY= 1, FAST, MOVE2LEFT,MOVE2RIGHT, MOVE2UP, MOVE2DOWN,
} DISPLAMODLE;


typedef enum {
  NO_MOVE = 0, MOVE15S=15, 
} sMOVETIME;
typedef struct {
  
  u8 RTUnum;
  u8  pos; // RTUID and name save postion
  u8  len;//RTUID and name save postion

} RtuIDPara;


typedef union 
{ 
	u32 i;
  float f;
} Temp_Humi_value;



#pragma pack(1)
typedef struct {
  u8  RTU_sum;//
	u8  RTUID_sum;
  u8  RTUID[10][5];
  u8  RTUHMID[20][5];
  u8  DateSt[10];
  u8  MK_value[10];
  u32 Basic_Water[10];//RTUID and name save postion
  u32 Alarm_Water[10];//RTUID and name save postion
  u32 Alarm_Hour_r[10];//RTUID and name save postion
  u32 Alarm_Day_r[10];//RTUID and name save postion
} RTUpara_type;
#pragma pack(1)
typedef struct {
	u16 vol[10];//��ѹ
  u16 rain[10];//��������
	u16 hrain[10];//ʱ������
  u16 rain_y[10];//��������
	u16 rain_sum[10];//�ۼ�����
	u16 rain_sum_y[10];//�����ۼ�����  ����8�ֽڼ����������
	u16 hrain_l[10];//��ʱ������
	u16 temp[10];//��ʱ������
	u16 humi[10];//��ʱ������
  u32 capacity[10];//����
  u32 water[10];//ˮλ
	u32 flow[10];//����
	
} Radio_data_type;


typedef struct {
//  u8 RTUnoT;//
//  u8 RTUIDT;
 // u8  TRTUname[10];
  u8   TDateSt;
  u8   TMK_value;
  //u16  Last_rain; // RTUID and name save postion
  u32  TBasic_Water;//RTUID and name save postion
  u32  Treverse;
} RTUparaTest;




typedef struct {
  u8  dismodle; // screem display  stay  fast moveto left
  u8 areaX;
  u8 areaY;
  u8 areaLen;
  u8 areaWide;
  u8 dispeed;// display speed
  u8 len;
  u8  disbuf[128];//the character to send to the screen
}ScreenPara;


void initGlobleVar(void);
void ReadFlashpara(void);
void display_start(void);
int Refresh_Flashpara(void);

#endif
