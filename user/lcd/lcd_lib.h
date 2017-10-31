#ifndef __LCD_LIB_H
#define	__LCD_LIB_H

#include "lcd_drv.h"

//LCD应用层（学号、题号、评分值）关闭显示
#define 	LCD_APP_CLEAR		(9999UL)

#define 	LCD_REFRESH_SIGNAL		(0x01)
#define 	LCD_REFRESH_BATTERY		(0x02)
#define 	LCD_REFRESH_STUDEN_ID	(0x04)
#define 	LCD_REFRESH_SCENE		(0x08)
#define 	LCD_REFRESH_INPUT		(0x10)
#define 	LCD_REFRESH_RESULT		(0x20)

// LCD数码管对应位置，从左到右数，依次是LCD_SEGMENT_1/2/3/4/5/6/7
typedef enum
{
	LCD_SEGMENT_1,		
	LCD_SEGMENT_2,
	LCD_SEGMENT_3,
	LCD_SEGMENT_4,
	LCD_SEGMENT_5,
	LCD_SEGMENT_6,
	LCD_SEGMENT_7
}LCD_SEGMENT_LOCATION;

// 字母显示类型，可按位或显示多个字母
typedef enum 
{
	LCD_CLEAR 	= 0X00,
	LCD_A		= 0x01,
	LCD_B		= 0x02,
	LCD_C		= 0x04,
	LCD_D		= 0x08,
	LCD_E		= 0x10,
	LCD_F		= 0x20,
	LCD_G		= 0x40,
	LCD_H		= 0x80
}LCD_LETTER_TYPE;	

typedef enum 
{
	SEND_RESULT_CLEAR		= 0X00,
	SEND_RESULT_OK			= 0X01,
	SEND_RESULT_FAIL		= 0X02
}LCD_SEND_RESULT_TYPE;		

typedef enum 
{
	JUDGE_CLEAR		= 0X00,
	JUDGE_TRUE		= 0X01,
	JUDGE_FALSE		= 0X02
}LCD_JUDGE_TYPE;		

typedef enum
{
	HONGBAO_DISPLAY,
	HONGBAO_CLEAR
}LCD_HONGBAO_TYPE;

typedef enum 
{
	BATTERY_LEVEL_0 = 0X00,
	BATTERY_LEVEL_1 = 0X01,
	BATTERY_LEVEL_2 = 0X02,
	BATTERY_LEVEL_3 = 0X03,
	BATTERY_LEVEL_OFF
}LCD_BATTERY_LEVEL_TYPE;				

typedef enum 
{
	RSSI_0 = 0X00,
	RSSI_1 = 0X01,
	RSSI_2 = 0X02,
	RSSI_3 = 0X03,
	RSSI_4 = 0X04,
	RSSI_OFF = 0X05
}LCD_SIGNAL_LEVEL_TYPE;	


typedef enum 
{
	DOT_OFF	= 0X00,
	DOT_ON  = 0X01,
}LCD_DOT_TYPE;	

typedef enum 
{
	LCD_DIS_UPDATE,			//正常刷新
	LCD_DIS_VER,			//显示软件版本信息
	LCD_DIS_RSSI,			//显示信号强度	
	LCD_DIS_VOLTAGE,		//显示电压值
	LCD_DIS_CHANNAL,		//显示频点
	LCD_DIS_ATTEND,			//显示考勤信息
	LCD_DIS_DATE			//显示生产日期
}LCD_DISPLAY_TYPE;	

typedef struct
{
	uint8_t		RefreshFlg;		// LCD刷新标志，每Bit对应一个刷新区域
	
//	uint8_t		Signal[64];
//	uint8_t 	Battery[64];
	uint8_t 	StudentId[8];		// 学生姓名/学号
	uint8_t 	Input[16];			// 按键输入内容
	
	uint8_t     ScenePos;			// 回显刷新位置，为了防止LCD刷新一直占用CPU，每次只刷新一个字符
	uint8_t		Scene[49];			// 第一个字节表示需要跟新显示的长度，最大48	
	
	uint8_t 	SendResultState;
}LCD_REFRESH_DATA_T;

typedef struct
{
	bool					UpdateFlg;
	LCD_DISPLAY_TYPE		DisType;
	LCD_REFRESH_DATA_T		DATA;
	
	uint8_t 				GBKCode[2];
	uint8_t					DotMatrix[32];
}LCD_PARAMETERS_T;



extern LCD_PARAMETERS_T LCD;

extern uint32_t LCD_Init(void);
extern void LCD_Sleep(void);
extern void LCD_WakeUp(void);
extern void LCD_Update(void);

extern void LCD_ClearScreen(void);
extern void LCD_DisplayAll(void);
extern void LCD_DisplayLetter(uint8_t Letter);
extern void LCD_DisplayJudge(uint8_t Value);
extern void LCD_DisplayHongbao(uint8_t Value);
extern void LCD_DisplaySendResult(LCD_SEND_RESULT_TYPE SendResult);
extern void LCD_DisplaySignal(LCD_SIGNAL_LEVEL_TYPE Value);
extern void LCD_DisplayBattery(LCD_BATTERY_LEVEL_TYPE Value);

extern void LCD_DisplayDeviceId(void);
extern void LCD_ClearInputArea(void);

extern void LCD_DisplaySceneArea(void);
extern void LCD_ClearSceneArea(void);

extern void LCD_DisDigit(uint8_t Pos, uint32_t Digit);
extern void LCD_DisDigit_5(uint8_t Pos, uint32_t Digit);
extern void LCD_DisVer(void);

#endif 




