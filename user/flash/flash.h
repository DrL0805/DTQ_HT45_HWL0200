#ifndef __FLASH_H
#define __FLASH_H	 

// Includes -----------------------------------------------------------
//#include "nrf_gpio.h"
#include "main.h"

// Defines ------------------------------------------------------------


// Typedefs -----------------------------------------------------------
typedef struct 
{
	uint32_t 		PageSize;			// == 2014
	uint32_t		PageNum;			// == 256
	uint32_t*		UserAddr;			// 存储用户信息的地址，为51822最后一页flash，地址为0x3FC00，共1K
}FLASH_PARAMETERS_T;

// Functions ----------------------------------------------------------
extern void FLASH_Init(void);
extern void FLASH_WriteJsqUID(uint8_t *UID);
extern void flash_page_erase(uint32_t * page_address);
extern void flash_word_write(uint32_t * address, uint32_t value);
// Globals ------------------------------------------------------------
extern FLASH_PARAMETERS_T 		FLASH;

		 				    
#endif














