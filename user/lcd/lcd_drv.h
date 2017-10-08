#ifndef __LCD_DRV_H
#define	__LCD_DRV_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "main.h"

// IST3308CA3 LCD Driver Command
#define LCD_DISPLAY_ON				(0xAF)	
#define LCD_DISPLAY_OFF				(0xAE)
#define LCD_DISPLAY_STARTING_LINE	(DYNAMIC)
#define LCD_SET_PAGE_ADDRESS		(DYNAMIC)
#define LCD_SET_AX_ADDRESS			(DYNAMIC)
#define LCD_WRITE_DISPLAY_DATA		(DYNAMIC)
#define LCD_READ_DISPLAY_DATA		(DYNAMIC)
#define LCD_SEG_DIRECTION_NORMAL	(0xA0)
#define LCD_SEG_DIRECTION_REVERSE	(0xA1)
#define LCD_INVERSE_DISPLAY_NORMAL	(0xA6)
#define LCD_INVERSE_DISPLAY_INVERSE	(0xA7)
#define LCD_ALL_PIXEL_ON_NORMAL		(0xA4)
#define LCD_ALL_PIXEL_ON_ON			(0xA5)
#define LCD_BIAS_SELECT_1_9			(0xA2)
#define LCD_BIAS_SELECT_1_7			(0xA3)
#define LCD_SW_RESET				(0xE2)
#define LCD_COM_DIRECTION_NORMAL	(0xC0)
#define LCD_COM_DIRECTION_REVERSE	(0xC8)
#define LCD_POWER_CONTROL			(DYNAMIC)
#define LCD_REGULATION_RATIO_30		(0x20)
#define LCD_REGULATION_RATIO_35		(0x21)
#define LCD_REGULATION_RATIO_40		(0x22)
#define LCD_REGULATION_RATIO_45		(0x23)
#define LCD_REGULATION_RATIO_50		(0x24)
#define LCD_REGULATION_RATIO_55		(0x25)
#define LCD_REGULATION_RATIO_60		(0x26)
#define LCD_REGULATION_RATIO_65		(0x27)
#define LCD_SET_EV_H				(0x81)		
#define LCD_SET_EV_L				(DYNAMIC)	// 0~63
#define LCD_SET_BOOSTER_H			(0xF8)
#define LCD_SET_BOOSTER_L_X5		(0x00)
#define LCD_SET_BOOSTER_L_X4		(0x01)
#define LCD_NOP						(0xE3)
#define LCD_SPI4_READ_RAM_DATA		(0x37)


// LCD PIN 
#define LCD_PIN_POWER				(21)
#define LCD_PIN_CSB					(22)
#define LCD_PIN_RST					(23)
#define LCD_PIN_A0					(24)
#define LCD_PIN_SCL					(25)
#define LCD_PIN_SDA					(26)

// LCD PIN STATE
#define LCD_POWER_OFF()				nrf_gpio_pin_set(LCD_PIN_POWER)
#define LCD_POWER_ON()				nrf_gpio_pin_clear(LCD_PIN_POWER)

#define LCD_CSB_HIGH()				nrf_gpio_pin_set(LCD_PIN_CSB)
#define LCD_CSB_LOW()				nrf_gpio_pin_clear(LCD_PIN_CSB)

#define LCD_RST_HIGH()				nrf_gpio_pin_set(LCD_PIN_RST)
#define LCD_RST_LOW()				nrf_gpio_pin_clear(LCD_PIN_RST)

#define LCD_A0_HIGH()				nrf_gpio_pin_set(LCD_PIN_A0)					// 传输显示的数据
#define LCD_A0_LOW()				nrf_gpio_pin_clear(LCD_PIN_A0)					// 传输控制命令

#define LCD_SCL_HIGH()				nrf_gpio_pin_set(LCD_PIN_SCL)
#define LCD_SCL_LOW()				nrf_gpio_pin_clear(LCD_PIN_SCL)

#define LCD_SDA_HIGH()				nrf_gpio_pin_set(LCD_PIN_SDA)
#define LCD_SDA_LOW()				nrf_gpio_pin_clear(LCD_PIN_SDA)


// ASCII编码
#define ASCII_A				0x41
#define ASCII_B				0x42
#define ASCII_C				0x43
#define ASCII_D				0x44
#define ASCII_0				0x30
#define ASCII_1				0x31
#define ASCII_2				0x32
#define ASCII_3				0x33
#define ASCII_4				0x34
#define ASCII_5				0x35
#define ASCII_6				0x36
#define ASCII_7				0x37
#define ASCII_8				0x38
#define ASCII_9				0x39

// LCD点阵显示类型
#define LCD_DRV_DOT_ASCII	0
#define LCD_DRV_DOT_HANZI	1



extern void LCD_DRV_Init(void);
extern void LCD_DRV_Init_TEST(uint8_t test);
extern void LCD_DRV_DisplayTest(uint8_t ph, uint8_t pl);
extern void LCD_DRV_DisplayOne(uint8_t Location, uint8_t DotType, uint16_t DotCode);
extern void LCD_DRV_DisplayHanzi(uint8_t Hang, uint8_t Lie, uint16_t GBKCode);
extern void LCD_DRV_DisplayAscii(uint8_t Hang, uint8_t Lie, uint8_t* ASCIIDotMatrix);
extern void LCD_DRV_DisplayDigit(uint8_t Hang, uint8_t Lie, uint8_t Digit);
extern void LCD_DRV_DisplayLetter(uint8_t Letter);
extern void LCD_DRV_ClearInputArea(void);
extern void LCD_DRV_ClearSceneArea(void);
extern void LCD_DRV_ClearNameArea(void);
extern void LCD_DRV_ClearScoreArea(void);
extern void LCD_DRV_ClearSendArea(void);

extern void LCD_DRV_DisplayBattery(void);
extern void LCD_DRV_DisplaySignal(void);
extern void LCD_DRV_WriteCmd(uint8_t Cmd);
extern void LCD_DRV_WriteData(uint8_t Data);














#define LCD_DATA          		(8u)
#define LCD_WRB          		(9u)
#define LCD_CSB          		(10u)
#define LCD_POWER				(18u)

#define LCD_PowerCtrlOff()			nrf_gpio_pin_set(LCD_POWER)
#define LCD_PowerCtrlOn()			nrf_gpio_pin_clear(LCD_POWER)

//---------------------LCD控制命令---------------------------------
#define SYSDIS 				0x00 //关闭系统振荡器
#define SYSEN 				0x01 //打开系统振荡器
#define LCDOFF 				0x02 //关闭LCF偏压
#define LCDON 				0x03 //打开LCF偏压
#define RC256 				0x18 //使用内部时钟
#define BIAS_1_3			0x29 //LCD1/3偏压设置
#define LCD_DRIVE_DELAY()	do{ __nop();__nop(); }while(0)
//#define LCD_DRIVE_DELAY()	nrf_delay_us(10)


extern uint8_t 					LCD_RAM[18];




void LCD_WriteData(uint8_t data, uint8_t count, uint8_t flag);
void LCD_WriteCommand(uint8_t cmd);
void LCD_WriteSignleData(uint8_t addr, uint8_t data);
void LCD_WriteMultData(uint8_t addr, uint8_t len, uint8_t * data);
void LCD_ClearRam(uint8_t ram1, uint8_t ram2);
void LCD_ModifyRam(uint8_t ram1, uint8_t ram2, uint8_t data1, uint8_t data2);
void LCD_ModifySegment(uint8_t ram1, uint8_t ram2, uint8_t data);


#endif 




