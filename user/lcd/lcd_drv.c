

/* Includes -----------------------------------------------------*/
#include "lcd_drv.h"

uint8_t DotMatrix_A[] = {0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20};
uint8_t DotMatrix_B[] = {0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00};
uint8_t DotMatrix_C[] = {0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00};
uint8_t DotMatrix_D[] = {0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00};
uint8_t DotMatrix_1[] = {0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00};
uint8_t DotMatrix_2[] = {0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00};
uint8_t DotMatrix_3[] = {0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00};
uint8_t DotMatrix_4[] = {0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00};
uint8_t DotMatrix_5[] = {0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00};
uint8_t DotMatrix_6[] = {0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00};
uint8_t DotMatrix_7[] = {0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00};
uint8_t DotMatrix_8[] = {0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00};
uint8_t DotMatrix_9[] = {0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00};
uint8_t DotMatrix_0[] = {0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00};	


void LCD_DRV_Init_TEST(uint8_t test)
{
	nrf_gpio_cfg_output(LCD_PIN_POWER);
	nrf_gpio_cfg_output(LCD_PIN_CSB);
	nrf_gpio_cfg_output(LCD_PIN_RST);
	nrf_gpio_cfg_output(LCD_PIN_A0);	
	nrf_gpio_cfg_output(LCD_PIN_SCL);
	nrf_gpio_cfg_output(LCD_PIN_SDA);		
	
	LCD_RST_LOW();
	nrf_delay_ms(50);
	LCD_RST_HIGH();
	nrf_delay_ms(50);
	
	// 数据手册推荐的初始化程序				
	LCD_DRV_WriteCmd(LCD_SET_BOOSTER_H);			// Set Booster
	LCD_DRV_WriteCmd(LCD_SET_BOOSTER_L_X5);   		// Set Booster	
	LCD_DRV_WriteCmd(LCD_SET_EV_H);          		// set reference voltage   LCD_SET_EV_H
	LCD_DRV_WriteCmd(test);							// Set EV L	0x20	 
	LCD_DRV_WriteCmd(LCD_BIAS_SELECT_1_9);
	LCD_DRV_WriteCmd(LCD_REGULATION_RATIO_50);
	LCD_DRV_WriteCmd(0x2F);         				//power control(VB,VR,VF=1,1,1)
	nrf_delay_ms(10);
	
	LCD_DRV_WriteCmd(LCD_SEG_DIRECTION_NORMAL);
	LCD_DRV_WriteCmd(LCD_COM_DIRECTION_REVERSE);	
	LCD_DRV_WriteCmd(LCD_DISPLAY_ON);	
	LCD_DRV_WriteCmd(0x40);         				//Initial Display Line
}


void LCD_DRV_Init(void)
{
	nrf_gpio_cfg_output(LCD_PIN_POWER);
	nrf_gpio_cfg_output(LCD_PIN_CSB);
	nrf_gpio_cfg_output(LCD_PIN_RST);
	nrf_gpio_cfg_output(LCD_PIN_A0);	
	nrf_gpio_cfg_output(LCD_PIN_SCL);
	nrf_gpio_cfg_output(LCD_PIN_SDA);		
	
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

void LCD_DRV_DisplayTest(uint8_t ph, uint8_t pl)
{
	int page,i;

	for(page=0;page<9;page++)			
	{
		LCD_DRV_WriteCmd(0x10);			// Set AX Address H
		LCD_DRV_WriteCmd(0x00);			// Set AX Address L
		LCD_DRV_WriteCmd(page+0xB0);	// 选择页码，共8页
		for(i=0;i<128;i++)				// 	
		{
			LCD_DRV_WriteData(ph);
		}
	}	
}

//图片写入
void LCD_DRV_DisplayPicture(uint8_t pic[])
{
	uint8_t i,page;

	for(page=0;page<9;page++)
	{
		LCD_DRV_WriteCmd(0x10);
		LCD_DRV_WriteCmd(0x00);
		LCD_DRV_WriteCmd(page+0xb0);
		for(i=0;i<128 ;i++)
		{
			LCD_DRV_WriteData(*pic);
			pic++;
		}
	}
}


void LCD_DRV_DisplayJie(void)
{
	uint8_t i,j;
	uint8_t Bmp[]=
	{
//		0x82,0x42,0x31,0x00,0x00,0x10,0x60,0x07,0x10,0x60,0x00,0x00,0x11,0xE2,0x02,0x00,
//		0x00,0x08,0x08,0x88,0x48,0x28,0x18,0xFF,0x18,0x28,0x48,0x88,0x08,0x08,0x00,0x00,
	
//		/*--  文字:  杰，图像上下翻转  --*/
//		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
//		0x41,0x42,0x8C,0x00,0x00,0x08,0x06,0xE0,0x08,0x06,0x00,0x00,0x88,0x47,0x40,0x00,
//		0x00,0x10,0x10,0x11,0x12,0x14,0x18,0xFF,0x18,0x14,0x12,0x11,0x10,0x10,0x00,0x00
		
		/*--  文字:  杰，图像上下不翻转  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0x08,0x08,0x88,0x48,0x28,0x18,0xFF,0x18,0x28,0x48,0x88,0x08,0x08,0x00,0x00,
		0x82,0x42,0x31,0x00,0x00,0x10,0x60,0x07,0x10,0x60,0x00,0x00,0x11,0xE2,0x02,0x00
	};
	
	LCD_DRV_WriteCmd(0x10);
	LCD_DRV_WriteCmd(0x00);			
	LCD_DRV_WriteCmd(0+0xb0);		// page
	for(i=0;i<16 ;i++)
	{
		LCD_DRV_WriteData(Bmp[i]);
	}
	
	LCD_DRV_WriteCmd(0x10);
	LCD_DRV_WriteCmd(0x00);
	LCD_DRV_WriteCmd(1+0xb0);
	for(i=0;i<16 ;i++)
	{
		LCD_DRV_WriteData(Bmp[i+16]);
	}
}

/*
* Hang:从上到下0~3
* Lie：从左到右0~7
* DotMatrix：汉字点阵，16*16
*/
void LCD_DRV_DisplayHanzi(uint8_t Hang, uint8_t Lie, uint16_t GBKCode)
{
	uint8_t i;
	uint8_t DotBuf[32];
	
	W25_SpiReadHanziDot(DotBuf, GBKCode);
	
	
	LCD_DRV_WriteCmd(Hang*2+0+0xb0);			// page
	LCD_DRV_WriteCmd(0x10+Lie);
	LCD_DRV_WriteCmd(0x00);	
	for(i=0;i<16 ;i++)
	{
		LCD_DRV_WriteData(DotBuf[i]);
	}
	
	LCD_DRV_WriteCmd(Hang*2+1+0xb0);		// page
	LCD_DRV_WriteCmd(0x10+Lie);
	LCD_DRV_WriteCmd(0x00);		
	for(i=16;i<32 ;i++)
	{
		LCD_DRV_WriteData(DotBuf[i]);
	}	
}

/*
* Hang:从上到下0~3
* Lie：从左到右0~15
* DotMatrix：字符点阵，8*16
*/
void LCD_DRV_DisplayAscii(uint8_t Hang, uint8_t Lie, uint8_t* ASCIIDotMatrix)
{
	uint8_t i;
	uint8_t lie_p;
	
	lie_p = Lie*8;
	
	LCD_DRV_WriteCmd(Hang*2+0+0xb0);			// page
	LCD_DRV_WriteCmd(0x10 + (lie_p >> 4));
	LCD_DRV_WriteCmd(0x00 + (lie_p &  0x0f));	
	for(i=0;i<8 ;i++)
	{
		LCD_DRV_WriteData(ASCIIDotMatrix[i]);
	}
	
	LCD_DRV_WriteCmd(Hang*2+1+0xb0);			// page
	LCD_DRV_WriteCmd(0x10 + (lie_p >> 4));
	LCD_DRV_WriteCmd(0x00 + (lie_p &  0x0f));		
	for(i=8;i<16 ;i++)
	{
		LCD_DRV_WriteData(ASCIIDotMatrix[i]);
	}	
}

void LCD_DRV_DisplayDigit(uint8_t Hang, uint8_t Lie, uint8_t Digit)
{
	uint8_t DigitDotMatrix[16];
	
	
	switch (Digit)
    {
    	case 1:
			LCD_DRV_DisplayAscii(Hang, Lie, DotMatrix_1);
    		break;
    	case 2:
			LCD_DRV_DisplayAscii(Hang, Lie, DotMatrix_2);
    		break;
		case 3:
			LCD_DRV_DisplayAscii(Hang, Lie, DotMatrix_3);
    		break;
		case 4:
			LCD_DRV_DisplayAscii(Hang, Lie, DotMatrix_4);
    		break;
		case 5:
			LCD_DRV_DisplayAscii(Hang, Lie, DotMatrix_5);
    		break;
		case 6:
			LCD_DRV_DisplayAscii(Hang, Lie, DotMatrix_6);
    		break;
		case 7:
			LCD_DRV_DisplayAscii(Hang, Lie, DotMatrix_7);
    		break;
		case 8:
			LCD_DRV_DisplayAscii(Hang, Lie, DotMatrix_8);
    		break;
		case 9:
			LCD_DRV_DisplayAscii(Hang, Lie, DotMatrix_9);
    		break;
		case 0:
			LCD_DRV_DisplayAscii(Hang, Lie, DotMatrix_0);
    		break;
    	default:
    		break;
    }
}


void LCD_DRV_DisplayLetter(uint8_t Letter)
{
	uint8_t i, TmpDisplaySite = 0;		// 显示位置
	
	LCD_DRV_ClearInputArea();
	
	if((Letter & LCD_A) == LCD_A)
	{
		LCD_DRV_DisplayAscii(3, 2+TmpDisplaySite, DotMatrix_A);
		TmpDisplaySite++;
	}
	
	if((Letter & LCD_B) == LCD_B)
	{
		LCD_DRV_DisplayAscii(3, 2+TmpDisplaySite, DotMatrix_B);
		TmpDisplaySite++;
	}

	if((Letter & LCD_C) == LCD_C)
	{
		LCD_DRV_DisplayAscii(3, 2+TmpDisplaySite, DotMatrix_C);
		TmpDisplaySite++;
	}

	if((Letter & LCD_D) == LCD_D)
	{
		LCD_DRV_DisplayAscii(3, 2+TmpDisplaySite, DotMatrix_D);
		TmpDisplaySite++;
	}	
	
	
//	switch(Letter)
//	{
//		case 1:
//			LCD_DRV_DisplayAscii(3, 2, DotMatrix_A);
//			break;
//		case 2:
//			LCD_DRV_DisplayAscii(3, 2, DotMatrix_B);
//			break;
//		case 3:
//			LCD_DRV_DisplayAscii(3, 2, DotMatrix_C);
//			break;
//		case 4:
//			LCD_DRV_DisplayAscii(3, 2, DotMatrix_D);
//			break;
//		default:
//			break;
//	}
}

void LCD_DRV_ClearInputArea(void)
{
	int page,i;

	for(page=6;page<8;page++)			
	{
		LCD_DRV_WriteCmd(0x10);			// Set AX Address H
		LCD_DRV_WriteCmd(0x00);			// Set AX Address L
		LCD_DRV_WriteCmd(page+0xB0);	// 选择页码，共8页
		for(i=0;i<64;i++)				// 	
		{
			LCD_DRV_WriteData(0x00);
		}
	}	
}

void LCD_DRV_ClearSceneArea(void)
{
	int page,i;

	for(page=4;page<6;page++)			
	{
		LCD_DRV_WriteCmd(0x10);			// Set AX Address H
		LCD_DRV_WriteCmd(0x00);			// Set AX Address L
		LCD_DRV_WriteCmd(page+0xB0);	// 选择页码，共8页
		for(i=0;i<128;i++)				// 	
		{
			LCD_DRV_WriteData(0x00);
		}
	}	
}
void LCD_DRV_ClearNameArea(void)
{
	int page,i;

	for(page=2;page<4;page++)			
	{
		LCD_DRV_WriteCmd(0x10);			// Set AX Address H
		LCD_DRV_WriteCmd(0x00);			// Set AX Address L
		LCD_DRV_WriteCmd(page+0xB0);	// 选择页码，共8页
		for(i=0;i<96;i++)					
		{
			LCD_DRV_WriteData(0x00);
		}
	}
}

void LCD_DRV_ClearScoreArea(void)
{
	int page,i;
	
	for(page=2;page<4;page++)			
	{
		// 从96列开始清除显示
		LCD_DRV_WriteCmd(0x16);			// Set AX Address H
		LCD_DRV_WriteCmd(0x00);			// Set AX Address L
		
		LCD_DRV_WriteCmd(page+0xB0);	// 选择页码，共8页
		for(i=0;i<32;i++)					
		{
			LCD_DRV_WriteData(0x00);
		}
	}
}

void LCD_DRV_ClearSendArea(void)
{
	int page,i;

	for(page=6;page<8;page++)			
	{
		// 从96列开始清除显示
		LCD_DRV_WriteCmd(0x14);			// Set AX Address H
		LCD_DRV_WriteCmd(0x00);			// Set AX Address L

		LCD_DRV_WriteCmd(page+0xB0);	// 选择页码，共8页
		for(i=0;i<64;i++)					
		{
			LCD_DRV_WriteData(0x00);
		}
	}
}


void LCD_DRV_DisplayBattery(void)
{
	uint8_t i;
	
	uint8_t BatteryDot[] = {
				0x00,0xF0,0xF0,0x30,0x3E,0x06,0x06,0xF6,0xF6,0xF6,0xF6,0xF6,0xF6,0x16,0xC6,0xF6,
				0xF6,0xF6,0xF6,0xF6,0x36,0x86,0xF6,0xF6,0xF6,0xF6,0xF6,0x06,0x06,0xFE,0xFE,0x00,
				0x00,0x0F,0x0F,0x0C,0x7C,0x60,0x60,0x6F,0x6F,0x6F,0x6F,0x67,0x60,0x6C,0x6F,0x6F,
				0x6F,0x6F,0x6F,0x61,0x68,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x60,0x60,0x7F,0x7F,0x00
//				0xF8,0xF8,0x18,0x1F,0x0B,0x03,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0x1B,0x83,0xFB,
//				0xFB,0xFB,0xFB,0xFB,0xFB,0x1B,0x83,0xF3,0xFB,0xFB,0xFB,0xFB,0xFB,0x03,0xFF,0xFF,
//				0x0F,0x1F,0x18,0xF8,0xC8,0xC0,0xDF,0xDF,0xDF,0xDF,0xDF,0xCF,0xC0,0xD8,0xDF,0xDF,
//				0xDF,0xDF,0xDF,0xCF,0xC0,0xD8,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xC0,0xFF,0xFF
		};	
	
	LCD_DRV_WriteCmd(0+0xb0);			// page
	LCD_DRV_WriteCmd(0x10 + 6);
	LCD_DRV_WriteCmd(0x00 + 0);
	for(i=0;i<32 ;i++)
	{
		LCD_DRV_WriteData(BatteryDot[i]);
	}	
	
	LCD_DRV_WriteCmd(1+0xb0);			// page
	LCD_DRV_WriteCmd(0x10 + 6);
	LCD_DRV_WriteCmd(0x00 + 0);
	for(i=32;i<64 ;i++)
	{
		LCD_DRV_WriteData(BatteryDot[i]);
	}				
				
}




void LCD_DRV_DisplaySignal(void)
{
	uint8_t i;
	
	uint8_t SignalDot[] = {
		0x00,0x0E,0x1E,0x36,0x66,0x46,0xFE,0xFE,0x46,0x66,0x36,0x1E,0x0E,0x00,0x00,0x00,
		0x80,0x80,0x80,0x00,0x00,0x00,0xE0,0xE0,0xE0,0x00,0x00,0x00,0xFE,0xFE,0xFE,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x7F,0x00,0x00,0x7C,0x7C,0x7C,0x00,0x00,0x00,
		0x7F,0x7F,0x7F,0x00,0x00,0x00,0x7F,0x7F,0x7F,0x00,0x00,0x00,0x7F,0x7F,0x7F,0x00
//			0x07,0x0F,0x1B,0x33,0x63,0x43,0xFF,0xFF,0x43,0x63,0x33,0x1B,0x0F,0x07,0x03,0x00,
//			0x00,0x80,0x80,0x80,0x00,0x00,0x00,0xE0,0xE0,0xE0,0x00,0x00,0x00,0xFE,0xFE,0xFE,
//			0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFC,0xFC,0x00,0x00,
//			0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF
	};	
	
	LCD_DRV_WriteCmd(0+0xb0);			// page
	LCD_DRV_WriteCmd(0x10 + 0);
	LCD_DRV_WriteCmd(0x00 + 0);
	for(i=0;i<32 ;i++)
	{
		LCD_DRV_WriteData(SignalDot[i]);
	}	
	
	LCD_DRV_WriteCmd(1+0xb0);			// page
	LCD_DRV_WriteCmd(0x10 + 0);
	LCD_DRV_WriteCmd(0x00 + 0);
	for(i=32;i<64 ;i++)
	{
		LCD_DRV_WriteData(SignalDot[i]);
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












uint8_t 					LCD_RAM[18] = {0x00,0x00,0x00,0x00,0x00,0x00,
                                           0x00,0x00,0x00,0x00,0x00,0x00,
                                           0x00,0x00,0x00,0x00,0x00,0x00};							//LCD中内存数据	

/* Functions ----------------------------------------------------*/

void LCD_WriteData(uint8_t data, uint8_t count, uint8_t flag)
{
	uint8_t i;
	
	if(flag == 0)													//处理向左移位的操作
	{
		for (i=0; i<count; i++)
		{
			nrf_gpio_pin_clear(LCD_WRB);
			LCD_DRIVE_DELAY();
			nrf_gpio_pin_write(LCD_DATA, data & 0x80);
			LCD_DRIVE_DELAY();
			nrf_gpio_pin_set(LCD_WRB);
			LCD_DRIVE_DELAY();
			data <<= 1;
		}
	}
	else															//处理向右移位的操作
	{
		for (i=0; i<count; i++)
		{
			nrf_gpio_pin_clear(LCD_WRB);
			LCD_DRIVE_DELAY();
			nrf_gpio_pin_write(LCD_DATA, data & 0x01);
			LCD_DRIVE_DELAY();
			nrf_gpio_pin_set(LCD_WRB);
			LCD_DRIVE_DELAY();
			data >>= 1;
		}
	}
}

void LCD_WriteCommand(uint8_t cmd)
{
	nrf_gpio_pin_clear(LCD_CSB);
	LCD_DRIVE_DELAY();
	LCD_WriteData(0x80, 3, 0);
	LCD_WriteData(cmd, 8, 0);
	//写命令的第九个时钟数据
	nrf_gpio_pin_clear(LCD_WRB);
	LCD_DRIVE_DELAY();
	nrf_gpio_pin_clear(LCD_DATA);
	LCD_DRIVE_DELAY();
	nrf_gpio_pin_set(LCD_WRB);
	LCD_DRIVE_DELAY();
	nrf_gpio_pin_set(LCD_CSB);
	LCD_DRIVE_DELAY();
}

void LCD_WriteSignleData(uint8_t addr, uint8_t data)
{
	nrf_gpio_pin_clear(LCD_CSB);
	LCD_DRIVE_DELAY();
	LCD_WriteData(0xa0, 3, 0);
	LCD_WriteData(addr << 2, 6, 0);
	LCD_WriteData(data, 4, 1);
	nrf_gpio_pin_set(LCD_CSB);
	LCD_DRIVE_DELAY();
}

void LCD_WriteMultData(uint8_t addr, uint8_t len, uint8_t * data)
{
	uint8_t i;
	
	nrf_gpio_pin_clear(LCD_CSB);
	LCD_DRIVE_DELAY();
	LCD_WriteData(0xa0, 3, 0);
	LCD_WriteData(addr << 2, 6, 0);
	for(i=0;i<len;i++)
	{
	    LCD_WriteData(data[i], 4, 1);
	}
	nrf_gpio_pin_set(LCD_CSB);
	LCD_DRIVE_DELAY();
}

//清除LCD的RAM数据
void LCD_ClearRam(uint8_t ram1, uint8_t ram2)
{
	LCD_RAM[ram1] &= 0x08;
	LCD_RAM[ram2] &= 0x00;
}

//修改LCD的RAM数据
void LCD_ModifyRam(uint8_t ram1, uint8_t ram2, uint8_t data1, uint8_t data2)
{
	LCD_RAM[ram1] |= data1;
	LCD_RAM[ram2] |= data2;
}

void LCD_ModifySegment(uint8_t ram1, uint8_t ram2, uint8_t data)
{
	switch(data)
	{
		case 0:
			LCD_ClearRam(ram1, ram2);
			LCD_ModifyRam(ram1, ram2, 0x5, 0xF);
			break;
		case 1:
			LCD_ClearRam(ram1, ram2);
			LCD_ModifyRam(ram1, ram2, 0x5, 0x0);		
			break;
		case 2:
			LCD_ClearRam(ram1, ram2);
			LCD_ModifyRam(ram1, ram2, 0x3, 0xD);		
		break;
		case 3:
			LCD_ClearRam(ram1, ram2);
			LCD_ModifyRam(ram1, ram2, 0x7, 0x9);
		break;
		case 4:
			LCD_ClearRam(ram1, ram2);	
			LCD_ModifyRam(ram1, ram2, 0x7, 0x2);	
		break;
		case 5:
			LCD_ClearRam(ram1, ram2);	
			LCD_ModifyRam(ram1, ram2, 0x6, 0xB);		
		break;
		case 6:
			LCD_ClearRam(ram1, ram2);
			LCD_ModifyRam(ram1, ram2, 0x6, 0xF);		
		break;
		case 7:
			LCD_ClearRam(ram1, ram2);
			LCD_ModifyRam(ram1, ram2, 0x5, 0x1);		
		break;
		case 8:
			LCD_ClearRam(ram1, ram2);		
			LCD_ModifyRam(ram1, ram2, 0x7, 0xF);		
		break;
		case 9:
			LCD_ClearRam(ram1, ram2);
			LCD_ModifyRam(ram1, ram2, 0x7, 0xB);		
		break;
		case 10:
			LCD_ClearRam(ram1, ram2);	
		break;
		default:
			break;
	}
}









