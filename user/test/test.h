#ifndef __TEST_H
#define __TEST_H	 

// Includes -----------------------------------------------------------
#include "main.h"

// Defines ------------------------------------------------------------


// Typedefs -----------------------------------------------------------
typedef struct 
{
	uint8_t		RxRssi;				//�������յ�������������RSSI
	uint8_t 	TxRssi;				//�����������������յ���RSSI
	uint8_t     JsqUid[4];			//����ģʽʱ�յ��Ľ�����UID
	
	uint8_t 	LcdLetterVal;		//�洢LCD��ĸ��ֵ	
	
	
	uint16_t	HuiXianNum;
	
	uint16_t 	TxSucCnt;
	uint16_t	TxFaiCnt;
	
	uint32_t    TxIrqCnt;
	uint32_t	SendLimitCnt;
	uint32_t    ReturnCnt;
	
	uint32_t    StartCnt;
	uint32_t    StopCnt;
	
}TEST_PARAMETERS_T;

// Functions ----------------------------------------------------------
extern void TEST_Init(void);
extern void TEST_RssiTest(void);
extern void TEST_LcdTest(void);
extern void TEST_KeyHandler(void);
// Globals ------------------------------------------------------------
extern TEST_PARAMETERS_T 		TEST;

		 				    
#endif














