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
	
	memcpy(LCD.DotMatrix, FlashReadBuffer, 32);
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

	tx_buf[0] = W25X_ReadData;
	tx_buf[1] = (ReadAddr & 0xFF0000) >> 16;
	tx_buf[2] = (ReadAddr & 0xFF00) >> 8;
	tx_buf[3] = (ReadAddr & 0xFF);
	memset(tx_buf+4, Dummy_Byte, NumByteToRead);
	
	spi_master_tx_rx(spi_base_address,NumByteToRead+4,tx_buf, rx_buf);
	
	memcpy(pBuffer, rx_buf+4, NumByteToRead);
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







 
 

 
 
