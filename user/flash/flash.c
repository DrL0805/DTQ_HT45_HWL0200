// Revision record ----------------------------------------------------
/*
	NRF51ϵ�е�flash�ֳ�CODESIZEҳ��ÿҳռCODEPAGESIZE�ֽ�
	����flash�ռ䣨����ռ䣩��CODEPAGESIZE * CODESIZE �ֽ�
	
	����������nrf51822����256KByte������
	CODESIZE = 256
	CODEPAGESIZE = 1024
	
	����������flash�ò��꣬���Կ���ȡ���һҳ��1KByte�ռ����ڴ洢��Ҫ����Ϣ
	
	ע�⣺
		1��flash��д��λΪword��4Byte�����ҳ���ÿ��д��1Byte�󣬻����Ӳ������	
*/

/*
	Flash�洢��ַ���䣬Ϊ��д���㣬ÿ����Ϣ����ռ1�֣�4Byte����
	0x3FC00~0x3FC03��������UID
	0x3FC04~0x3FC07��������UID
	0x3FC08~0x3FC0B��������������
	0x3FC0C~0x3FC0F������������Ƶ��
	0x3FC10~0x3FC13������������Ƶ��
	
	
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
	// ʹ��51822���һҳflash���洢�û�����
	FLASH.UserAddr = (uint32_t *)(NRF_FICR->CODEPAGESIZE * (NRF_FICR->CODESIZE - 1));	

	return drERROR_SUCCESS;
}


// �ѽ�����UIDд��flashԼ��λ��
void FLASH_WriteJsqUID(uint8_t *UID)
{
	uint32_t UID4Byte;
	
	UID4Byte = UID[0] | (UID[1] << 8) | (UID[2] << 16) | (UID[3] << 24);

	// FLASHÿ��д��ǰ�����Ȳ���
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







 
 

 
 
