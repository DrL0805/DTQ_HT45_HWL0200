

/* Includes -----------------------------------------------------*/
#include "lcd_uc1701_drv.h"

static uint32_t* lcd_spi_base_address;

void LCD_UC1701_WriteCmd(uint8_t Cmd)
{
	#if LCD_UC1701_SOFTWARE_SPI
	
	uint8_t i;
	LCD_DRV_CSB_LOW();
	LCD_DRV_A0_LOW();
	
	for(i=0;i<8;i++)
	{
		LCD_DRV_SCL_LOW();
		nrf_gpio_pin_write(LCD_PIN_SDA, Cmd & 0x80);		
		LCD_DRV_SCL_HIGH();
		Cmd = Cmd << 1;
	}
	LCD_DRV_CSB_HIGH();
	LCD_DRV_A0_HIGH();	
	
	#elif LCD_UC1701_HARDWARE_SPI
	
	uint8_t tx_buf[5];
	uint8_t rx_buf[5];

	tx_buf[0] = Cmd;

	spi_master_tx_rx(lcd_spi_base_address,1,tx_buf, rx_buf);
	
	#endif
}

void LCD_UC1701_WriteData(uint8_t Data)
{
	#if LCD_UC1701_SOFTWARE_SPI
	
	uint8_t i;
	LCD_DRV_CSB_LOW();
	LCD_DRV_A0_HIGH();	
	for(i=0;i<8;i++)
	{
		LCD_DRV_SCL_LOW();;
		nrf_gpio_pin_write(LCD_PIN_SDA, Data & 0x80);		
		LCD_DRV_SCL_HIGH();
		Data = Data << 1;
	}
	LCD_DRV_CSB_HIGH();
	LCD_DRV_A0_LOW();	
	
	#elif LCD_UC1701_HARDWARE_SPI
	uint8_t tx_buf[5];
	uint8_t rx_buf[5];

	tx_buf[0] = Data;

	spi_master_tx_rx(lcd_spi_base_address,1,tx_buf, rx_buf);	
	#endif
}

uint8_t LCD_UC1701_Read(uint8_t Cmd)
{
	uint8_t i,ReadData;
	
	// 写入命令
	LCD_DRV_CSB_LOW();		
	
	LCD_DRV_A0_LOW();		// 传输命令
	
	for(i=0;i<8;i++)
	{
		LCD_DRV_SCL_LOW();
		nrf_gpio_pin_write(LCD_PIN_SDA, Cmd & 0x80);		
		LCD_DRV_SCL_HIGH();
		Cmd = Cmd << 1;
	}
	
	LCD_DRV_A0_HIGH();		// 读取数据
	
	nrf_gpio_cfg_input(LCD_DRV_PIN_SDA,NRF_GPIO_PIN_NOPULL);	// 配置SDA脚为输入
	
	LCD_DRV_SCL_LOW();		// 空时钟周期
	__NOP();
	LCD_DRV_SCL_HIGH();
	__NOP();
	
	for(i=0;i<8;i++)
	{
		LCD_DRV_SCL_LOW();
		ReadData |= nrf_gpio_pin_read(LCD_DRV_PIN_SDA) << (7-i);
		LCD_DRV_SCL_HIGH();
		__NOP();
	}
	
	LCD_DRV_CSB_HIGH();	
	
	return ReadData;
}

void LCD_UC1701_DRV_Init(void)
{
	#if LCD_UC1701_SOFTWARE_SPI
	
	nrf_gpio_cfg_output(LCD_DRV_PIN_POWER);
	nrf_gpio_cfg_output(LCD_DRV_PIN_CSB);
	nrf_gpio_cfg_output(LCD_DRV_PIN_RST);
	nrf_gpio_cfg_output(LCD_DRV_PIN_A0);	
	nrf_gpio_cfg_output(LCD_DRV_PIN_SCL);
	nrf_gpio_cfg_output(LCD_DRV_PIN_SDA);
	
	#elif LCD_UC1701_HARDWARE_SPI
	
	lcd_spi_base_address = spi_master_init(SPI1, SPI_MODE3, 0);	
	
	#endif	
	
	LCD_DRV_POWER_ON();
	
	LCD_DRV_RST_HIGH();
	nrf_delay_ms(2);
	LCD_DRV_RST_LOW();
	nrf_delay_ms(1);
	LCD_DRV_RST_HIGH();
	nrf_delay_ms(10);
	
	LCD_UC1701_WriteCmd(LCD_UC1701_SYSTEM_RESET_H);
	LCD_UC1701_WriteData(LCD_UC1701_SYSTEM_RESET_L);
	nrf_delay_ms(5);
	LCD_UC1701_WriteCmd(LCD_UC1701_SET_TEMP_COMP);
	
	LCD_UC1701_WriteCmd(0x2d);//Set Power Control 0x2d
	LCD_UC1701_WriteCmd(0xa2);//Set LC 0xa2
	LCD_UC1701_WriteCmd(0xe9);//Set LCD Bias Ratio 1/4
	
	LCD_UC1701_WriteCmd(0xf1);
	LCD_UC1701_WriteData(63);//Set COM End

	LCD_UC1701_WriteCmd(0x81); //Set VBIAS Potentiometer
	LCD_UC1701_WriteData(95); //4.8V
	
	LCD_UC1701_WriteCmd(0x2f);  //电流
	LCD_UC1701_WriteCmd(0x83);  //Set CKC
	LCD_UC1701_WriteData(0x02); //分频

	LCD_UC1701_WriteCmd(0xab);  //set LC //频率
	LCD_UC1701_WriteCmd(0x82);
	LCD_UC1701_WriteData(0x00);
	LCD_UC1701_WriteData(0x1a);

	LCD_UC1701_WriteCmd(0xc9);  // Set Display Enable
	LCD_UC1701_WriteData(0xaf);	
}


void LCD_UC1701_Test(void)
{
	
	#if 0		// 显示中文字符测试
	uint8_t CodeBuf[] = {0xCE,0xD2,0xCA,0xC7,0xC1,0xF9,0xD2,0xBB,0xCD,0xAC,0xD1,0xA7};
	uint32_t i = 0;	
		
	LCD_UC1701_DisplayOne(4, LCD_DRV_DOT_HANZI, 0xB7A2);
	
	#endif
	
	
	#if 1		// 显示ascii字符测试
	uint8_t CodeBuf[] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
					0x30,0x41,0x53,0x44,0x46,0x47,0x48,0x6A,0x6B,0x6C,0x3B,0x27};
	uint32_t i;
	
	for(i = 0;i < sizeof(CodeBuf) / sizeof(CodeBuf[0]);i++)
	{
		LCD_UC1701_DisplayOne(0+i,0,*(CodeBuf+i));
	}
	#endif

	
	#if 0		// 全亮全灭测试
	for(uint32_t Page = 0;Page < 8;Page++)
	{
		LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|Page);		//set page address	
		LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 		//column  lsb		
		LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|0); 	//column  msb	
		LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);			// 开始写数据	
		for(uint32_t i = 0; i < 128;i++)
		{
			LCD_UC1701_WriteData(0xff);
		}		
	}
	nrf_delay_ms(1000);
	
	for(uint32_t Page = 0;Page < 8;Page++)
	{
		LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|Page);		//set page address	
		LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 		//column  lsb		
		LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|0); 	//column  msb	
		LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);			// 开始写数据	
		for(uint32_t i = 0; i < 128;i++)
		{
			LCD_UC1701_WriteData(0x00);
		}		
	}
	nrf_delay_ms(1000);	
	#endif
}



/*
* 功能：LCD显示一个字符（汉字或者ASCII码）
* Location：显示位置，从左到后从上到下依次为0~63，一个汉字占2个位置，一个ACSSI码占1个位置
* DotType：点阵类型：字母数字/汉字
* DotBuf：显示点阵内容
*/
void LCD_UC1701_DisplayOne(uint8_t Location, uint8_t DotType, uint16_t DotCode)
{
	uint8_t i, DotBuf[32];
	
	switch(DotType)
	{
		case LCD_DRV_DOT_ASCII:	// ascii码			
			if((uint8_t)DotCode > 0x20)
			{
				memcpy(DotBuf, ascii_thick_songti[(uint8_t)DotCode-0x20], 16);
			}
			else
			{
				memset(DotBuf, 0x00, 16);
			}
			LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|(Location/16)*2);					//set page address	
			LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 								//column  lsb		
			LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|(Location%16)*8); 		//column  msb	
			LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);									// 开始写数据	
			for(i=0;i<8 ;i++)
			{
				LCD_UC1701_WriteData(DotBuf[i]);
			}
			
			LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|(Location/16)*2 + 1);					//set page address	
			LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 								//column  lsb		
			LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|(Location%16)*8); 		//column  msb	
			LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);									// 开始写数据			
			for(i=8;i<16 ;i++)
			{
				LCD_UC1701_WriteData(DotBuf[i]);	
			}
					
			break;
		case LCD_DRV_DOT_HANZI:	// 汉字
			if((DotCode >> 8) >= 0x81)	
			{
				W25_SpiReadHanziDot(DotBuf, DotCode);
				
				// 在LCD屏幕边缘显示中文，字体分开
				if((Location == 15) || (Location == 31) || (Location == 47) || (Location == 63))
				{
//					LCD_DRV_WriteCmd((Location/16)*2+0xb0);							// 设置在第几行显示
//					LCD_DRV_WriteCmd(0x10 + ((Location%16)*8 >> 4));				// 设置在第几列显示
//					LCD_DRV_WriteCmd(0x00 + ((Location%16)*8 &  0x0f));	
					LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|(Location/16)*2);					//set page address	
					LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 								//column  lsb		
					LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|(Location%16)*8); 		//column  msb	
					LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);									// 开始写数据	
					for(i=0;i<8 ;i++)
						LCD_DRV_WriteData(DotBuf[i]);
					
//					LCD_DRV_WriteCmd(((Location+1)/16)*2+0xb0);							// 设置在第几行显示
//					LCD_DRV_WriteCmd(0x10 + (((Location+1)%16)*8 >> 4));				// 设置在第几列显示
//					LCD_DRV_WriteCmd(0x00 + (((Location+1)%16)*8 &  0x0f));
					LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|((Location+1)/16));					//set page address	
					LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 								//column  lsb		
					LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|((Location+1)%16)*8); 		//column  msb	
					LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);									// 开始写数据						
					for(i=8;i<16 ;i++)
						LCD_DRV_WriteData(DotBuf[i]);					
									
//					LCD_DRV_WriteCmd((Location/16)*2 + 1 + 0xb0);					// 设置在第几行显示
//					LCD_DRV_WriteCmd(0x10 + ((Location%16)*8 >> 4));				// 设置在第几列显示
//					LCD_DRV_WriteCmd(0x00 + ((Location%16)*8 &  0x0f));		
					LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|(Location/16)*2 + 1);					//set page address	
					LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 								//column  lsb		
					LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|(Location%16)*8); 		//column  msb	
					LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);									// 开始写数据	
					for(i=16;i<24 ;i++)
						LCD_DRV_WriteData(DotBuf[i]);	
						
//					LCD_DRV_WriteCmd(((Location+1)/16)*2 + 1 + 0xb0);					// 设置在第几行显示
//					LCD_DRV_WriteCmd(0x10 + (((Location+1)%16)*8 >> 4));				// 设置在第几列显示
//					LCD_DRV_WriteCmd(0x00 + (((Location+1)%16)*8 &  0x0f));		
					LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|(Location/16)*2 + 1);					//set page address	
					LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 								//column  lsb		
					LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|((Location+1)%16)*8); 		//column  msb	
					LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);									// 开始写数据	
					for(i=24;i<32 ;i++)
						LCD_DRV_WriteData(DotBuf[i]);					
				}
				else					
				{
//					LCD_DRV_WriteCmd((Location/16)*2+0xb0);							// 设置在第几行显示
//					LCD_DRV_WriteCmd(0x10 + ((Location%16)*8 >> 4));				// 设置在第几列显示
//					LCD_DRV_WriteCmd(0x00 + ((Location%16)*8 &  0x0f));	
					LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|(Location/16)*2);					//set page address	
					LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 								//column  lsb		
					LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|(Location%16)*8); 		//column  msb	
					LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);									// 开始写数据	
					for(i=0;i<16 ;i++)
						LCD_DRV_WriteData(DotBuf[i]);
					
//					LCD_DRV_WriteCmd((Location/16)*2 + 1 + 0xb0);					// 设置在第几行显示
//					LCD_DRV_WriteCmd(0x10 + ((Location%16)*8 >> 4));				// 设置在第几列显示
//					LCD_DRV_WriteCmd(0x00 + ((Location%16)*8 &  0x0f));		
					LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|(Location/16)*2 + 1);					//set page address	
					LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 								//column  lsb		
					LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|(Location%16)*8); 		//column  msb	
					LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);									// 开始写数据						
					for(i=16;i<32 ;i++)
						LCD_DRV_WriteData(DotBuf[i]);				
				}		
			}
			break;
		default:
			break;
	}
}

void LCD_UC1701_DisplayN(uint8_t Location, uint8_t CodeLen, uint8_t* CodeBuf)
{
	uint8_t pLocation = 0;
	
	if(0 == CodeLen)
		return;
	do
	{
		if(CodeBuf[pLocation] >= 0x81)	// 汉字显示
		{
			LCD_UC1701_DisplayOne(Location+pLocation, 1, (uint16_t)(CodeBuf[pLocation]<<8 |  CodeBuf[pLocation+1]));
			pLocation += 2;
		}
		else							// ASCII显示
		{
			LCD_UC1701_DisplayOne(Location+pLocation, 0, (CodeBuf[pLocation]));
			pLocation++;
		}	
	}while(pLocation < CodeLen);
}


void LCD_UC1701_DisplayDigit(uint8_t Location, uint8_t DigitValue)
{
	switch(DigitValue)
	{
		case 0:
			LCD_UC1701_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_0);
			break;
		case 1:
			LCD_UC1701_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_1);
			break;
		case 2:
			LCD_UC1701_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_2);
			break;
		case 3:
			LCD_UC1701_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_3);
			break;
		case 4:
			LCD_UC1701_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_4);
			break;
		case 5:
			LCD_UC1701_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_5);
			break;
		case 6:
			LCD_UC1701_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_6);
			break;
		case 7:
			LCD_UC1701_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_7);
			break;
		case 8:
			LCD_UC1701_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_8);
			break;
		case 9:
			LCD_UC1701_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_9);
			break;
		default:
			break;
	}
}

