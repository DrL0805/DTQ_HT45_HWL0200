#ifndef __UART_H
#define	__UART_H


#include "simple_uart.h"
#include "nrf_gpio.h"
#include "main.h"

	//答题器串口定义
#define RX_PIN_NUMBER  (28)    // UART RX pin number.
#define TX_PIN_NUMBER  (29)    // UART TX pin number.
#define CTS_PIN_NUMBER (27)  // UART Clear To Send pin number. Not used if HWFC is set to false
#define RTS_PIN_NUMBER (26)    // Not used if HWFC is set to false
#define HWFC           false // UART hardware flow control


	//接收器51822RX对应UART口
#define RX_PIN_NUMBER_1  13    // UART RX pin number.
#define TX_PIN_NUMBER_1  14    // UART TX pin number.
#define CTS_PIN_NUMBER_1 11   // UART Clear To Send pin number. Not used if HWFC is set to false
#define RTS_PIN_NUMBER_1 12    // Not used if HWFC is set to false
#define HWFC_1           false // UART hardware flow control
	
	//新版答题器串口定义
#define RX_PIN_NUMBER_2  17    // UART RX pin number.
#define TX_PIN_NUMBER_2  18    // UART TX pin number.
#define CTS_PIN_NUMBER_2 27   // UART Clear To Send pin number. Not used if HWFC is set to false
#define RTS_PIN_NUMBER_2 26    // Not used if HWFC is set to false
#define HWFC_2           false // UART hardware flow control

void DEBUG_Init(void);
void UART_PrintfNByte(uint8_t *buf,uint8_t len);

void UART_Init(void);
int fputc(int ch, FILE *f);
void UART_send_byte(uint8_t byte);
void UART_Send(uint8_t *Buffer, uint32_t Length);
uint8_t UART_Recive(void);

#endif /* __UART_H */








