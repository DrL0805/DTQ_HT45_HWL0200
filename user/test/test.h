#ifndef __TEST_H
#define __TEST_H	 

// Includes -----------------------------------------------------------
#include "main.h"

// Defines ------------------------------------------------------------


// Typedefs -----------------------------------------------------------
typedef struct 
{
	uint8_t		RxRssi;				//答题器收到接收器发出的RSSI
	uint8_t 	TxRssi;				//答题器发出接收器收到的RSSI
	uint8_t     JsqUid[4];			//测试模式时收到的接收器UID
	
	uint8_t 	LcdLetterVal;		//存储LCD字母键值	
	
	
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














