#ifndef __MATCH_H
#define __MATCH_H	 
// Includes -----------------------------------------------------------
#include "nrf_gpio.h"
#include "main.h"

// Defines ------------------------------------------------------------
#define 		STORE_MATCH_NUM			(5)			// ���洢PIN������
#define 		MATCH_UID_LEN			(4)			// UID����
#define 		MATCH_PIN_LEN			(2)			// PIN�볤��

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
	bool				NewMatchFlg;										// ���°󶨳ɹ���־
	uint8_t				SelectIndex;										// ѡ����Խ�����UID������
	
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














