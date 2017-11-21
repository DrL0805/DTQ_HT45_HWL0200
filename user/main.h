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
#include "app_fifo.h"
#include "nrf_drv_wdt.h"
#include "nrf_drv_timer.h"

#include "drl_err.h"
#include "drl_debug.h"
#include "drl_common.h"
#include "drl_timer.h"

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
#include "watchdog.h"
#include "timer_0.h"

// 软件版本 -----------------------------------------------------------
#define 	VERSION_PROTOCOL	(0)			//版本支持的协议,1表示自有协议
#define 	VERSION_LEVEL_1		(2)			//一级版本号
#define     VERSION_LEVEL_2		(3)			//二级版本号

#define     VERSION_LEVEL_COMPANY	"HWL-SSLK                "
#define     VERSION_LEVEL_NUMBER	"Ver: 0.6.1              "
#define		VERSION_LEVEL_TIME		"2017-11-2 20:51         "

#define 	SYS_NO_SLEEP_DEBUG		(1)
#define 	USE_WATCH_DOG			(1)
#define 	USE_UART_DEBUG			(0)


extern uint8_t XOR_Cal(uint8_t * dat,uint16_t length);
extern bool ArrayCmp(uint8_t *str1, uint8_t *str2, uint8_t len);
extern uint8_t GetRandomNumber(void);
extern void GPIO_Default(void);

#endif









