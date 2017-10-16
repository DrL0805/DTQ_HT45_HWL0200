

/* Includes -----------------------------------------------------*/
#include "lcd_drv.h"

const uint8_t DotMatrix_A[] = {0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20};
const uint8_t DotMatrix_B[] = {0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00};
const uint8_t DotMatrix_C[] = {0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00};
const uint8_t DotMatrix_D[] = {0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00};

const uint8_t DotMatrix_1[] = {0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00};
const uint8_t DotMatrix_2[] = {0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00};
const uint8_t DotMatrix_3[] = {0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00};
const uint8_t DotMatrix_4[] = {0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00};
const uint8_t DotMatrix_5[] = {0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00};
const uint8_t DotMatrix_6[] = {0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00};
const uint8_t DotMatrix_7[] = {0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00};
const uint8_t DotMatrix_8[] = {0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00};
const uint8_t DotMatrix_9[] = {0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00};
const uint8_t DotMatrix_0[] = {0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00};	
//uint8_t DotMatrix_0[] = {0x00,0xE0,0xF0,0x18,0x08,0x18,0xF0,0xE0,0x00,0x0F,0x1F,0x30,0x20,0x30,0x1F,0x0F};	


void LCD_DRV_Init(void)
{
	nrf_gpio_cfg_output(LCD_PIN_POWER);
	nrf_gpio_cfg_output(LCD_PIN_CSB);
	nrf_gpio_cfg_output(LCD_PIN_RST);
	nrf_gpio_cfg_output(LCD_PIN_A0);	
	nrf_gpio_cfg_output(LCD_PIN_SCL);
	nrf_gpio_cfg_output(LCD_PIN_SDA);	

	LCD_POWER_OFF();
	
	LCD_RST_LOW();
	nrf_delay_ms(50);
	LCD_RST_HIGH();
	nrf_delay_ms(50);
	
	// 数据手册推荐的初始化程序				
	LCD_DRV_WriteCmd(LCD_SET_BOOSTER_H);			// Set Booster
	LCD_DRV_WriteCmd(LCD_SET_BOOSTER_L_X5);   		// Set Booster	
	LCD_DRV_WriteCmd(LCD_SET_EV_H);          		// set reference voltage   LCD_SET_EV_H
	LCD_DRV_WriteCmd(0x1e);							// Set EV L	0x20	 
	LCD_DRV_WriteCmd(LCD_BIAS_SELECT_1_9);
	LCD_DRV_WriteCmd(LCD_REGULATION_RATIO_50);
	LCD_DRV_WriteCmd(0x2F);         				//power control(VB,VR,VF=1,1,1)
	nrf_delay_ms(10);
	
	LCD_DRV_WriteCmd(LCD_SEG_DIRECTION_NORMAL);
	LCD_DRV_WriteCmd(LCD_COM_DIRECTION_REVERSE);	
	LCD_DRV_WriteCmd(LCD_DISPLAY_ON);	
	LCD_DRV_WriteCmd(0x40);         				//Initial Display Line
}

void LCD_Refresh(uint8_t dot)
{
	int page,i;

	for(page=0;page<9;page++)			
	{
		LCD_DRV_WriteCmd(0x10);			// Set AX Address H
		LCD_DRV_WriteCmd(0x00);			// Set AX Address L
		LCD_DRV_WriteCmd(page+0xB0);	// 选择页码，共8页
		for(i=0;i<128;i++)				// 	
		{
			LCD_DRV_WriteData(dot);
		}
	}
}

/*
* 功能：LCD显示一个字符（汉字或者ASCII码）
* Location：显示位置，从左到后从上到下依次为0~63，一个汉字占2个位置，一个ACSSI码占1个位置
* DotType：点阵类型：字母数字/汉字
* DotBuf：显示点阵内容
*/
void LCD_DRV_DisplayOne(uint8_t Location, uint8_t DotType, uint16_t DotCode)
{
	uint8_t i, DotBuf[32];
	
	if(Location > 63)
		return;
	
	switch(DotType)
	{
		case LCD_DRV_DOT_ASCII:	// ascii码		
			switch((uint8_t)DotCode)
			{
				case ASCII_NULL:
					return;			// 不做处理
					break;
				case ASCII_CLEAR:
					memset(DotBuf, 0x00, 16);
					break;
				case ASCII_A:
					memcpy(DotBuf, DotMatrix_A, 16);
					break;
				case ASCII_B:
					memcpy(DotBuf, DotMatrix_B, 16);
					break;
				case ASCII_C:
					memcpy(DotBuf, DotMatrix_C, 16);
					break;
				case ASCII_D:
					memcpy(DotBuf, DotMatrix_D, 16);
					break;
				case ASCII_1:
					memcpy(DotBuf, DotMatrix_1, 16);
					break;
				case ASCII_2:
					memcpy(DotBuf, DotMatrix_2, 16);
					break;
				case ASCII_3:
					memcpy(DotBuf, DotMatrix_3, 16);
					break;
				case ASCII_4:
					memcpy(DotBuf, DotMatrix_4, 16);
					break;
				case ASCII_5:
					memcpy(DotBuf, DotMatrix_5, 16);
					break;
				case ASCII_6:
					memcpy(DotBuf, DotMatrix_6, 16);
					break;
				case ASCII_7:
					memcpy(DotBuf, DotMatrix_7, 16);
					break;
				case ASCII_8:
					memcpy(DotBuf, DotMatrix_8, 16);
					break;
				case ASCII_9:
					memcpy(DotBuf, DotMatrix_9, 16);
					break;
				case ASCII_0:
					memcpy(DotBuf, DotMatrix_0, 16);
					break;
				default:				
					break;
			}
		
			LCD_DRV_WriteCmd(0x40); 
			
			LCD_DRV_WriteCmd((Location/16)*2 + 0xb0);						// 设置在第几行显示
			LCD_DRV_WriteCmd(0x10 + ((Location%16)*8 >> 4));				// 设置在第几列显示
			LCD_DRV_WriteCmd(0x00 + ((Location%16)*8 &  0x0f));			
			for(i=0;i<8 ;i++)
				LCD_DRV_WriteData(DotBuf[i]);
			
			LCD_DRV_WriteCmd((Location/16)*2 + 1 + 0xb0);			
			LCD_DRV_WriteCmd(0x10 + ((Location%16)*8 >> 4));
			LCD_DRV_WriteCmd(0x00 + ((Location%16)*8 &  0x0f));		
			for(i=8;i<16 ;i++)
				LCD_DRV_WriteData(DotBuf[i]);		
			break;
		case LCD_DRV_DOT_HANZI:	// 汉字
			if((DotCode >> 8) >= 0x81)	
			{
				W25_SpiReadHanziDot(DotBuf, DotCode);
				
				LCD_DRV_WriteCmd(0x40); 
				
				LCD_DRV_WriteCmd((Location/16)*2+0xb0);			
				LCD_DRV_WriteCmd(0x10 + ((Location%16)*8 >> 4));				// 设置在第几列显示
				LCD_DRV_WriteCmd(0x00 + ((Location%16)*8 &  0x0f));	
				for(i=0;i<16 ;i++)
					LCD_DRV_WriteData(DotBuf[i]);
				
				LCD_DRV_WriteCmd((Location/16)*2 + 1 + 0xb0);		
				LCD_DRV_WriteCmd(0x10 + ((Location%16)*8 >> 4));				// 设置在第几列显示
				LCD_DRV_WriteCmd(0x00 + ((Location%16)*8 &  0x0f));		
				for(i=16;i<32 ;i++)
					LCD_DRV_WriteData(DotBuf[i]);					
			}
			break;
		default:
			break;
	}
}

void LCD_DRV_DisplayN(uint8_t Location, uint8_t CodeLen, uint8_t* CodeBuf)
{
	uint8_t pLocation = 0;
	
	if(0 == CodeLen)
		return;
	
	do
	{
		if(CodeBuf[pLocation] >= 0x81)	// 汉字显示
		{
			LCD_DRV_DisplayOne(Location+pLocation, 1, (uint16_t)(CodeBuf[pLocation]<<8 |  CodeBuf[pLocation+1]));
			pLocation += 2;
		}
		else							// ASCII显示
		{
			LCD_DRV_DisplayOne(Location+pLocation, 0, (CodeBuf[pLocation]));
			pLocation++;
		}	
	}while(pLocation < CodeLen);
}

void LCD_DRV_DisplayDigit(uint8_t Location, uint8_t DigitValue)
{
	switch(DigitValue)
	{
		case 0:
			LCD_DRV_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_0);
			break;
		case 1:
			LCD_DRV_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_1);
			break;
		case 2:
			LCD_DRV_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_2);
			break;
		case 3:
			LCD_DRV_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_3);
			break;
		case 4:
			LCD_DRV_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_4);
			break;
		case 5:
			LCD_DRV_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_5);
			break;
		case 6:
			LCD_DRV_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_6);
			break;
		case 7:
			LCD_DRV_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_7);
			break;
		case 8:
			LCD_DRV_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_8);
			break;
		case 9:
			LCD_DRV_DisplayOne(Location, LCD_DRV_DOT_ASCII, ASCII_9);
			break;
		default:
			break;
	}
}

void LCD_DRV_WriteCmd(uint8_t Cmd)
{
	uint8_t i;
	
	LCD_CSB_LOW();
	LCD_A0_LOW();			// 控制命令
	
	for(i = 0;i < 8;i++)
	{
		LCD_SCL_LOW();
//		LCD_DRIVE_DELAY();

		nrf_gpio_pin_write(LCD_PIN_SDA, Cmd & 0x80);		
//		if(Cmd & 0x80)
//			LCD_SDA_HIGH();
//		else
//			LCD_SDA_LOW();
//		LCD_DRIVE_DELAY();
		
		LCD_SCL_HIGH();
//		LCD_DRIVE_DELAY();
		
		Cmd = Cmd << 1;
	}
	
	LCD_CSB_HIGH();
}

void LCD_DRV_WriteData(uint8_t Data)
{
	uint8_t i;
	
	LCD_CSB_LOW();
	LCD_A0_HIGH();			// 显示点阵
	
	for(i = 0;i < 8;i++)
	{
		LCD_SCL_LOW();
//		LCD_DRIVE_DELAY();
		
		nrf_gpio_pin_write(LCD_PIN_SDA, Data & 0x80);	
//		if(Cmd & 0x80)
//			LCD_SDA_HIGH();
//		else
//			LCD_SDA_LOW();
//		LCD_DRIVE_DELAY();
		
		LCD_SCL_HIGH();
//		LCD_DRIVE_DELAY();
		
		Data = Data << 1;
	}
	
	LCD_CSB_HIGH();
}


