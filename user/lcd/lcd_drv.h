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
#define LCD_POWER_CONTROL			(DYNAMIC)	// 0x2X
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
#define ASCII_NULL			0x01	// 不做处理
#define ASCII_CLEAR			0x00	// 清空显示
#define ASCII_A				0x41
#define ASCII_B				0x42
#define ASCII_C				0x43
#define ASCII_D				0x44
#define ASCII_E				0x45
#define ASCII_F				0x46
#define ASCII_G				0x47
#define ASCII_H				0x48
#define ASCII_I				0x49
#define ASCII_J				0x4A
#define ASCII_K				0x4B
#define ASCII_L				0x4C
#define ASCII_M				0x4D
#define ASCII_N				0x4E
#define ASCII_O				0x4F
#define ASCII_P				0x50
#define ASCII_Q				0x51
#define ASCII_R				0x52
#define ASCII_S				0x53
#define ASCII_T				0x54
#define ASCII_U				0x55
#define ASCII_V				0x56
#define ASCII_W				0x57
#define ASCII_X				0x58
#define ASCII_Y				0x59
#define ASCII_Z				0x5A


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

extern void LCD_DRV_WriteCmd(uint8_t Cmd);
extern void LCD_DRV_WriteData(uint8_t Data);

extern void LCD_Refresh(uint8_t dot);
extern void LCD_DRV_DisplayOne(uint8_t Location, uint8_t DotType, uint16_t DotCode);
extern void LCD_DRV_DisplayN(uint8_t Location, uint8_t CodeLen, uint8_t* CodeBuf);
extern void LCD_DRV_DisplayDigit(uint8_t Location, uint8_t DigitValue);


#endif 




