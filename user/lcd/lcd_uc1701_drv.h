#ifndef __LCD_UC1701_DRV_H
#define	__LCD_UC1701_DRV_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "nrf_gpio.h"
#include "nrf_delay.h"

#include "main.h"

#define LCD_UC1701_SOFTWARE_SPI		(1)			// 软件模拟SPI
#define LCD_UC1701_HARDWARE_SPI		(0)			// 硬件SPI

// lcd uc1701x 命令类型
#define LCD_UC1701_WRITE_DATA_H	(0X01)	// 写数据
#define LCD_UC1701_WRITE_DATA_L	(0X00)
#define LCD_UC1701_READ_DATA_H	(0X02)	// 读数据
#define LCD_UC1701_READ_DATA_L	(0X00)
#define LCD_UC1701_GET_STATUS_H	(0X03)	// 获取状态
#define LCD_UC1701_GET_STATUS_L	(0X00)	// 0bxxxx0000
#define LCD_UC1701_SET_COLUMN_ADDR_H	(0X04) //设置列地址 
#define LCD_UC1701_SET_COLUMN_ADDR_L	(0X00) // 0b0xxxxxx,0~17
#define LCD_UC1701_SET_TEMP_COMP	(0X24) // 0b001001xx，温度补偿
#define LCD_UC1701_SET_PWR_CTRL		(0X28) // 0b00101xxx
#define LCD_UC1701_SET_ADVANCED_PROGRAM_CTRL_H (0X30) // 高级编程控制
#define LCD_UC1701_SET_ADVANCED_PROGRAM_CTRL_L (0X00) // 0bxxxxxxxx
#define LCD_UC1701_SET_PAGE_ADDR	 (0XB0) // 0b10110xxx
#define LCD_UC1701_SET_Vbias_POTENTIOMETER_H (0X81)
#define LCD_UC1701_SET_Vbias_POTENTIOMETER_L (0X00) // 0b0xxxxxxx
#define LCD_UC1701_SET_LC	(0XA0)	// 0b1010xxxx，LCD控制
#define LCD_UC1701_SET_DISPLAY_ENABLE_H (0XC9)	// LCD显示开关控制
#define LCD_UC1701_SET_DISPLAY_ENABLE_L (0XAE)  // 0b1010111x
#define LCD_UC1701_SYSTEM_RESET_H	(0XE1)
#define LCD_UC1701_SYSTEM_RESET_L	(0XE2)
#define LCD_UC1701_NOP	(0XE3)
#define LCD_UC1701_SET_TEST_CTRL_H	(0XE4)
#define LCD_UC1701_SET_TEST_CTRL_L	(0X00) // 0bxxxxxxxx
#define LCD_UC1701_SET_LCD_BIAS_RATIO	(0XE8) // 0b111010xx
#define LCD_UC1701_SET_COM_END_H	(0XF1) // ,SET_CEN
#define LCD_UC1701_SET_COM_END_L	(0X00) // 0b00xxxxxx
#define LCD_UC1701_SET_LW_H		(0X82) 
#define LCD_UC1701_SET_LW_L		(0X00) 
#define LCD_UC1701_SET_LW_L2	(0X00) // 0b0xxxxxxx
#define LCD_UC1701_SET_ISOF_H	(0X82) 
#define LCD_UC1701_SET_ISOF_L	(0X01) 
#define LCD_UC1701_SET_ISOF_L2	(0X00) // 0b00000xxx
#define LCD_UC1701_SET_IS0E_H	(0X82) 
#define LCD_UC1701_SET_ISOE_L	(0X02) 
#define LCD_UC1701_SET_ISOE_L2	(0X00) // 0b00000xxx
#define LCD_UC1701_SET_CKC_H	(0X83) 
#define LCD_UC1701_SET_CKC_L	(0X00) // 0b000xxxxx


// LCD PIN 
#define LCD_DRV_PIN_POWER				(21)
#define LCD_DRV_PIN_CSB					(22)
#define LCD_DRV_PIN_RST					(23)
#define LCD_DRV_PIN_A0					(24)
#define LCD_DRV_PIN_SCL					(25)
#define LCD_DRV_PIN_SDA					(26)

// LCD PIN STATE
#define LCD_DRV_POWER_OFF()				nrf_gpio_pin_set(LCD_DRV_PIN_POWER)
#define LCD_DRV_POWER_ON()				nrf_gpio_pin_clear(LCD_DRV_PIN_POWER)

#define LCD_DRV_CSB_HIGH()				nrf_gpio_pin_set(LCD_DRV_PIN_CSB)
#define LCD_DRV_CSB_LOW()				nrf_gpio_pin_clear(LCD_DRV_PIN_CSB)

#define LCD_DRV_RST_HIGH()				nrf_gpio_pin_set(LCD_DRV_PIN_RST)
#define LCD_DRV_RST_LOW()				nrf_gpio_pin_clear(LCD_DRV_PIN_RST)

#define LCD_DRV_A0_HIGH()				nrf_gpio_pin_set(LCD_DRV_PIN_A0)					// 传输显示的数据
#define LCD_DRV_A0_LOW()				nrf_gpio_pin_clear(LCD_DRV_PIN_A0)					// 传输控制命令

#define LCD_DRV_SCL_HIGH()				nrf_gpio_pin_set(LCD_DRV_PIN_SCL)
#define LCD_DRV_SCL_LOW()				nrf_gpio_pin_clear(LCD_DRV_PIN_SCL)

#define LCD_DRV_SDA_HIGH()				nrf_gpio_pin_set(LCD_DRV_PIN_SDA)
#define LCD_DRV_SDA_LOW()				nrf_gpio_pin_clear(LCD_DRV_PIN_SDA)


void LCD_UC1701_DRV_Init(void);
void LCD_UC1701_Test(void);
void LCD_UC1701_WriteCmd(uint8_t Cmd);
void LCD_UC1701_WriteData(uint8_t Data);
uint8_t LCD_UC1701_Read(uint8_t Cmd);


void LCD_UC1701_DisplayOne(uint8_t Location, uint8_t DotType, uint16_t DotCode);
void LCD_UC1701_DisplayN(uint8_t Location, uint8_t CodeLen, uint8_t* CodeBuf);
void LCD_UC1701_DisplayDigit(uint8_t Location, uint8_t DigitValue);

#endif 




