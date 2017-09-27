#ifndef __MATCH_H
#define __MATCH_H	 
// Includes -----------------------------------------------------------
#include "nrf_gpio.h"
#include "main.h"

// Defines ------------------------------------------------------------
#define 		STORE_MATCH_NUM			(5)			// 最大存储PIN码数量
#define 		MATCH_UID_LEN			(4)			// UID长度
#define 		MATCH_PIN_LEN			(2)			// PIN码长度

// Typedefs -----------------------------------------------------------

typedef struct 
{
	uint8_t				UID[MATCH_UID_LEN];
	uint8_t				PIN[MATCH_PIN_LEN];
	uint8_t				TxChannal;
	uint8_t				RxChannal;
}UID_PARAMETERS_T;

typedef struct 
{
	bool				NewMatchFlg;										// 重新绑定成功标志
	uint8_t				SelectIndex;										// 选择配对接收器UID的索引
	
	uint8_t				RxChannal;
	uint8_t				TxChannal;
	
	UID_PARAMETERS_T	UID[STORE_MATCH_NUM];
}MATCH_PARAMETERS_T;

// Functions ----------------------------------------------------------
extern void MATCH_Init(void);
extern void MATCH_AddUidPin(uint8_t *UID, uint8_t *PIN, uint8_t TxChannal, uint8_t RxChannal);
extern void MATCH_DelUidPin(uint8_t *UID, uint8_t *PIN);
extern void MATCH_KeyHandler(void);
extern void MATCH_KeySendHandler(void);
extern void MATCH_KeyLastHandler(void);
extern void MATCH_KeyNextHandler(void);
extern void MATCH_LCDDisplayPIN(uint8_t Index);

// Globals ------------------------------------------------------------
extern MATCH_PARAMETERS_T 		MATCH;

	
#endif














