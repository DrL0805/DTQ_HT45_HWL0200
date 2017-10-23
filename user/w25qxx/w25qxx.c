// Revision record ----------------------------------------------------

// Includes -----------------------------------------------------------
#include "w25qxx.h"

// Functions ----------------------------------------------------------


// Globals ------------------------------------------------------------


// Locals -------------------------------------------------------------
static uint32_t* spi_base_address;



void W25_Init(void)
{
	uint8_t FlashReadBuffer[255];	
	
    spi_base_address = spi_master_init(SPI0, SPI_MODE3, 0);	
	
	if(0x17 == W25_SpiIdRead())
	{
		// W25128初始化成功
	}
	
	W25_SpiFlashBufferRead(FlashReadBuffer, 0, 32);
}


void W25_SpiWriteByte(uint8_t ByteData)
{
	uint8_t tx_buf[5];
	uint8_t rx_buf[5];

	tx_buf[0] = ByteData;
	
	spi_master_tx_rx(spi_base_address,1,tx_buf, rx_buf);
}


uint8_t W25_SpiIdRead(void)
{
	uint8_t tx_buf[5]={W25X_DeviceID,Dummy_Byte,Dummy_Byte,Dummy_Byte,Dummy_Byte};
	uint8_t rx_buf[5];	

	spi_master_tx_rx(spi_base_address,5,tx_buf, rx_buf);
	
	return rx_buf[4];
}

void W25_SpiFlashBufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	uint8_t tx_buf[255];
	uint8_t rx_buf[255];
	
	tx_buf[0] = W25X_ReadData;					// 命令字
	tx_buf[1] = (ReadAddr & 0xFF0000) >> 16;	// 24bit地址
	tx_buf[2] = (ReadAddr & 0xFF00) >> 8;		
	tx_buf[3] = (ReadAddr & 0xFF);
	memset(tx_buf+4, Dummy_Byte, NumByteToRead);
	
	spi_master_tx_rx(spi_base_address,NumByteToRead+4,tx_buf, rx_buf);
	
	memcpy(pBuffer, rx_buf+4, NumByteToRead);
}

void W25_FlashSectorErase(uint32_t SectorAddr)
{
	uint8_t tx_buf[255], rx_buf[255];
	uint8_t check_tx_buf[2] = {W25X_ReadStatusReg, 0xFF},check_rx_buf[2];	
	
	// FLASH写使能
	W25_SpiWriteByte(W25X_WriteEnable);	
	do
	{
		spi_master_tx_rx(spi_base_address,2,check_tx_buf, check_rx_buf);
	}while((check_rx_buf[1] & WIP_Flag) == 1); 		
	
	//整备需要发送的数据
	tx_buf[0] = W25X_SectorErase;				// 命令字
	tx_buf[1] = (SectorAddr & 0xFF0000) >> 16;	// 24bit地址
	tx_buf[2] = (SectorAddr & 0xFF00) >> 8;		
	tx_buf[3] = (SectorAddr & 0xFF);
	
	// 发送数据
	spi_master_tx_rx(spi_base_address,4,tx_buf, rx_buf);
	
	// 等待FLAHS写完成
	do
	{
		spi_master_tx_rx(spi_base_address,2,check_tx_buf, check_rx_buf);
	}while((check_rx_buf[1] & WIP_Flag) == 1);	
	
	
//  /* Send write enable instruction */
//  SPI_FLASH_WriteEnable();
//  SPI_FLASH_WaitForWriteEnd();
//  /* Sector Erase */
//  /* Select the FLASH: Chip Select low */
//  SPI_FLASH_CS_LOW();
//  /* Send Sector Erase instruction */
//  SPI_FLASH_SendByte(W25X_SectorErase);
//  /* Send SectorAddr high nibble address byte */
//  SPI_FLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
//  /* Send SectorAddr medium nibble address byte */
//  SPI_FLASH_SendByte((SectorAddr & 0xFF00) >> 8);
//  /* Send SectorAddr low nibble address byte */
//  SPI_FLASH_SendByte(SectorAddr & 0xFF);
//  /* Deselect the FLASH: Chip Select high */
//  SPI_FLASH_CS_HIGH();
//  /* Wait the end of Flash writing */
//  SPI_FLASH_WaitForWriteEnd();
}

void W25_FlashPageWrite(uint8_t* pBuffer, uint32_t WtiteAddr, uint16_t NumByteToWrite)
{
	uint8_t tx_buf[255], rx_buf[255];
	uint8_t check_tx_buf[2] = {W25X_ReadStatusReg, 0xFF},check_rx_buf[2];	
	
	// FLASH写使能
	W25_SpiWriteByte(W25X_WriteEnable);	
	do
	{
		spi_master_tx_rx(spi_base_address,2,check_tx_buf, check_rx_buf);
	}while((check_rx_buf[1] & WIP_Flag) == 1); 	
	
	//整备需要发送的数据
	tx_buf[0] = W25X_PageProgram;				// 命令字
	tx_buf[1] = (WtiteAddr & 0xFF0000) >> 16;	// 24bit地址
	tx_buf[2] = (WtiteAddr & 0xFF00) >> 8;		
	tx_buf[3] = (WtiteAddr & 0xFF);
	memcpy(tx_buf+4, pBuffer, NumByteToWrite);
	
	// 发送数据
	spi_master_tx_rx(spi_base_address,NumByteToWrite+4,tx_buf, rx_buf);
	
	// 等待FLAHS写完成
	do
	{
		spi_master_tx_rx(spi_base_address,2,check_tx_buf, check_rx_buf);
	}while((check_rx_buf[1] & WIP_Flag) == 1);
}


void W25_SpiReadHanziDot(uint8_t *DotBuf, uint16_t GBKCode)
{
	uint32_t Addr;
	uint8_t GBKH,GBKL;
	
	GBKH = GBKCode >> 8;
	GBKL = GBKCode &  0xFF;
	
	
	if(GBKH < 0x7F)
	{
		Addr = ((GBKH - 0x81) * 190 + GBKL - 0x40) * 32;
	}
	else
	{
		Addr = ((GBKH - 0x81) * 190 + GBKL - 0x41) * 32;
	}

	W25_SpiFlashBufferRead(DotBuf, Addr, 32);
}







 
 

 
 
