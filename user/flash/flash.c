// Revision record ----------------------------------------------------
/*
	NRF51系列的flash分成CODESIZE页，每页占CODEPAGESIZE字节
	整个flash空间（代码空间）共CODEPAGESIZE * CODESIZE 字节
	
	答题器所用nrf51822共有256KByte，其中
	CODESIZE = 256
	CODEPAGESIZE = 1024
	
	答题器代码flash用不完，所以可以取最后一页的1KByte空间用于存储想要的信息
	
	注意：
		1）flash读写单位为word（4Byte），我尝试每次写入1Byte后，会出现硬件错误	
*/

/*
	Flash存储地址分配，为读写方便，每种信息至少占1字（4Byte）：
	0x3FC00~0x3FC03：接收器UID
	0x3FC04~0x3FC07：答题器UID
	0x3FC08~0x3FC0B：答题器配对序号
	0x3FC0C~0x3FC0F：答题器发送频点
	0x3FC10~0x3FC13：答题器接收频点
	
	
*/

// Includes -----------------------------------------------------------
#include "flash.h"

// Functions ----------------------------------------------------------
void flash_page_erase(uint32_t * page_address);
void flash_word_write(uint32_t * address, uint32_t value);

// Globals ------------------------------------------------------------
FLASH_PARAMETERS_T 		FLASH;

// Locals -------------------------------------------------------------

uint32_t FLASH_Init(void)
{
	// 使用51822最后一页flash来存储用户数据
	FLASH.UserAddr = (uint32_t *)(NRF_FICR->CODEPAGESIZE * (NRF_FICR->CODESIZE - 1));	

	return drERROR_SUCCESS;
}


// 把接收器UID写入flash约定位置
void FLASH_WriteJsqUID(uint8_t *UID)
{
	uint32_t UID4Byte;
	
	UID4Byte = UID[0] | (UID[1] << 8) | (UID[2] << 16) | (UID[3] << 24);

	// FLASH每次写入前必须先擦除
	flash_page_erase(FLASH.UserAddr);	

	flash_word_write(FLASH.UserAddr, (uint32_t)UID4Byte);
}



/** @brief Function for erasing a page in flash.
 *
 * @param page_address Address of the first word in the page to be erased.
 */
void flash_page_erase(uint32_t * page_address)
{
    // Turn on flash erase enable and wait until the NVMC is ready:
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Een << NVMC_CONFIG_WEN_Pos);

    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }

    // Erase page:
    NRF_NVMC->ERASEPAGE = (uint32_t)page_address;

    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }

    // Turn off flash erase enable and wait until the NVMC is ready:
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);

    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }
}


/** @brief Function for filling a page in flash with a value.
 *
 * @param[in] address Address of the first word in the page to be filled.
 * @param[in] value Value to be written to flash.
 */
void flash_word_write(uint32_t * address, uint32_t value)
{
    // Turn on flash write enable and wait until the NVMC is ready:
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos);
	
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }

    *address = value;

    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }

    // Turn off flash write enable and wait until the NVMC is ready:
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);

    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }
}







 
 

 
 
