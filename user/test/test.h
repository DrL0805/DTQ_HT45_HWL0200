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
	
	uint8_t 	LcdLetterVal;		//�洢LCD��ĸ��ֵ	
	
	
	uint16_t	HuiXianNum;
}TEST_PARAMETERS_T;

// Functions ----------------------------------------------------------
extern void TEST_Init(void);
extern void TEST_RssiTest(void);
extern void TEST_LcdTest(void);
extern void TEST_KeyTest(void);
// Globals ------------------------------------------------------------
extern TEST_PARAMETERS_T 		TEST;

		 				    
#endif














