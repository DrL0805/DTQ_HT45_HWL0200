#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_esb.h"
#include "nrf_gpio.h"
#include "app_timer.h"
#include "app_error.h"

#include "simple_uart.h"
#include "uart.h"
#include "timers.h"
#include "clock.h"
#include "led.h"
#include "lcd_lib.h"
#include "key.h"
#include "application.h"
#include "power.h"
#include "radio.h"
#include "adc.h"
#include "attend.h"
#include "flash.h"
#include "test.h"
#include "match.h"
#include "w25qxx.h"
#include "lib_TagType4.h"

// 软件版本 -----------------------------------------------------------
#define 	VERSION_PROTOCOL	(1)			//版本支持的协议,1表示自有协议
#define 	VERSION_LEVEL_1		(2)			//一级版本号
#define     VERSION_LEVEL_2		(0)			//二级版本号



extern uint8_t XOR_Cal(uint8_t * dat,uint16_t length);
extern bool ArrayCmp(uint8_t *str1, uint8_t *str2, uint8_t len);
extern uint8_t GetRandomNumber(void);
extern void GPIO_Default(void);

#endif








