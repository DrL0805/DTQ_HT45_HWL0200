#ifndef __W25QXX_H
#define __W25QXX_H	 

// Includes -----------------------------------------------------------
#include "main.h"
#include "spi_master_config.h" // This file must be in the application folder
#include "spi_master.h"

// Defines ------------------------------------------------------------
#define SPI_FLASH_PageSize     			256
#define SPI_FLASH_PerWritePageSize      256
#define W25X_WriteEnable		      0x06 
#define W25X_WriteDisable		      0x04 
#define W25X_ReadStatusReg		    0x05 
#define W25X_WriteStatusReg		    0x01 
#define W25X_ReadData			      0x03 
#define W25X_FastReadData		      0x0B 
#define W25X_FastReadDual		      0x3B 
#define W25X_PageProgram		      0x02 
#define W25X_BlockErase			      0xD8 
#define W25X_SectorErase		      0x20 
#define W25X_ChipErase			      0xC7 
#define W25X_PowerDown			      0xB9 
#define W25X_ReleasePowerDown	    0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   	0x90 
#define W25X_JedecDeviceID		    0x9F 

#define WIP_Flag                  0x01  /* Write In Progress (WIP) flag */

#define Dummy_Byte                0xFF

// Typedefs -----------------------------------------------------------

typedef struct
{
	uint32_t* 			SpiBaseAdd;
}W25_PARAMETERS_T;

// Functions ----------------------------------------------------------
extern void W25_Init(void);
extern void W25_SpiWriteByte(uint8_t ByteData);
extern uint8_t W25_SpiIdRead(void);
extern void W25_SpiFlashBufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
extern void W25_FlashSectorErase(uint32_t SectorAddr);
extern void W25_FlashPageWrite(uint8_t* pBuffer, uint32_t WtiteAddr, uint16_t NumByteToWrite);
extern void W25_SpiReadHanziDot(uint8_t *DotBuf, uint16_t GBKCode);

// Globals ------------------------------------------------------------
 				    
#endif














