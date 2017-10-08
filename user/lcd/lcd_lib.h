#ifndef __LCD_LIB_H
#define	__LCD_LIB_H

#include "lcd_drv.h"

//LCD应用层（学号、题号、评分值）关闭显示
#define 	LCD_APP_CLEAR		(9999UL)


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
	BATTERY_LEVEL_0 = 0X00,
	BATTERY_LEVEL_1 = 0X01,
	BATTERY_LEVEL_2 = 0X02,
	BATTERY_LEVEL_3 = 0X03
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
	bool					UpdateFlg;
	LCD_DISPLAY_TYPE		DisType;
	
	uint8_t 				GBKCode[2];
	uint8_t					DotMatrix[32];
}LCD_PARAMETERS_T;



extern LCD_PARAMETERS_T LCD;

void LCD_Init(void);
void LCD_Update(void);

void LCD_Sleep(void);
void LCD_WakeUp(void);

void LCD_ClearScreen(void);
void LCD_DisplayAll(void);
void LCD_ClearLetter(void);
void LCD_DisplayLetter(uint8_t data);
void LCD_DisplayJudge(uint8_t Value);
void LCD_DisplaySendResult(LCD_SEND_RESULT_TYPE SendResult);
void LCD_DisplaySignal(LCD_SIGNAL_LEVEL_TYPE Value);
void LCD_DisplayBattery(LCD_BATTERY_LEVEL_TYPE Value);
void LCD_ClearSegment(void);

void LCD_DisplayStudentName(void);
void LCD_DisplayQuestionNum(uint16_t question_num);
void LCD_DisplayScoreValue(uint16_t grade_value);
void LCD_DisplayDeviceId(void);

extern void LCD_ClearInputArea(void);
extern void LCD_ClearSceneArea(void);
extern void LCD_ClearNameArea(void);
extern void LCD_ClearScoreArea(void);
extern void LCD_ClearSendArea(void);

void LCD_DisplayTest(void);

#endif 




