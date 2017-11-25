

/* Includes -----------------------------------------------------*/
#include "lcd_lib.h"

LCD_PARAMETERS_T 		LCD;


const uint8_t Battery_3[64] = {
	0x00,0x00,0xF0,0xF0,0xF8,0x3C,0x0C,0xEC,0xEC,0xEC,0xEC,0xEC,0xEC,0x2C,0x8C,0xEC,
	0xEC,0xEC,0xEC,0x2C,0x8C,0xEC,0xEC,0xEC,0xEC,0xEC,0x0C,0xFC,0xFC,0x00,0x00,0x00,
	0x00,0x00,0x07,0x07,0x0F,0x1C,0x18,0x1B,0x1B,0x1B,0x1B,0x19,0x18,0x1A,0x1B,0x1B,
	0x1B,0x19,0x18,0x1A,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x18,0x1F,0x1F,0x00,0x00,0x00	
};
const uint8_t Battery_2[64] = {
	0x00,0x00,0xF0,0xF0,0xF8,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x8C,0xEC,
	0xEC,0xEC,0xEC,0x2C,0x8C,0xEC,0xEC,0xEC,0xEC,0xEC,0x0C,0xFC,0xFC,0x00,0x00,0x00,
	0x00,0x00,0x07,0x07,0x0F,0x1C,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1A,0x1B,0x1B,
	0x1B,0x19,0x18,0x1A,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x18,0x1F,0x1F,0x00,0x00,0x00
};
const uint8_t Battery_1[64] = {
	0x00,0x00,0xF0,0xF0,0xF8,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,
	0x0C,0x0C,0x0C,0x0C,0x8C,0xEC,0xEC,0xEC,0xEC,0xEC,0x0C,0xFC,0xFC,0x00,0x00,0x00,
	0x00,0x00,0x07,0x07,0x0F,0x1C,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
	0x18,0x18,0x18,0x1A,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x18,0x1F,0x1F,0x00,0x00,0x00
};
const uint8_t Battery_0[64] = {
	0x00,0x00,0xF0,0xF0,0xF8,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,
	0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0xFC,0xFC,0x00,0x00,0x00,
	0x00,0x00,0x07,0x07,0x0F,0x1C,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
	0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0x1F,0x00,0x00,0x00
};

const uint8_t Signal_4[64] = {
	0x00,0x00,0x06,0x0E,0x1A,0x32,0x62,0xFE,0xFE,0x62,0x32,0x1A,0x0E,0x06,0x00,0x00,
	0x80,0x80,0x80,0x00,0x00,0xE0,0xE0,0xE0,0x00,0x00,0xF8,0xF8,0xF8,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x00,0x00,0x1E,0x1E,0x1E,0x00,0x00,
	0x1F,0x1F,0x1F,0x00,0x00,0x1F,0x1F,0x1F,0x00,0x00,0x1F,0x1F,0x1F,0x00,0x00,0x00
};

const uint8_t Signal_3[64] = {
	0x00,0x00,0x06,0x0E,0x1A,0x32,0x62,0xFE,0xFE,0x62,0x32,0x1A,0x0E,0x06,0x00,0x00,
	0x80,0x80,0x80,0x00,0x00,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x00,0x00,0x1E,0x1E,0x1E,0x00,0x00,
	0x1F,0x1F,0x1F,0x00,0x00,0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const uint8_t Signal_2[64] = {
	0x00,0x00,0x06,0x0E,0x1A,0x32,0x62,0xFE,0xFE,0x62,0x32,0x1A,0x0E,0x06,0x00,0x00,
	0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x00,0x00,0x1E,0x1E,0x1E,0x00,0x00,
	0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const uint8_t Signal_1[64] = {
	0x00,0x00,0x06,0x0E,0x1A,0x32,0x62,0xFE,0xFE,0x62,0x32,0x1A,0x0E,0x06,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x00,0x00,0x1E,0x1E,0x1E,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const uint8_t Signal_0[64] = {
	0x00,0x00,0x06,0x0E,0x1A,0x32,0x62,0xFE,0xFE,0x62,0x32,0x1A,0x0E,0x06,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

/* Functions ----------------------------------------------------*/

void LCD_HardWareCheck(void)
{
	LCD_UC1701_DRV_Init();
	
	// 向LCD第一行第一列写入0xbb，再读出，看是否成功，用于检测硬件版本
	LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|0);		//set page address	
	LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 		//column  lsb		
	LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|0); 	//column  msb	
	LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);			// 开始写数据	
	LCD_UC1701_WriteData(0xbb);
	
	LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|0);		//set page address	
	LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 		//column  lsb		
	LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|0); 	//column  msb	

	if(0xbb == LCD_UC1701_Read(0X02))
	{
		LCD.DrvVer = UC1701;
	}
	else
	{
		LCD.DrvVer = IST3308CA3;
	}
}

uint32_t LCD_Init(void)
{
	LCD_HardWareCheck();	// 检测当前使用的是哪个LCD驱动硬件
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			LCD_DRV_Init();	
			break;
		case UC1701:
			LCD_UC1701_DRV_Init();
			break;
		default:
			break;
	}

	LCD.DATA.Scene[0] = 48;
	return drERROR_SUCCESS;
}



//关闭LCD显示，进入睡眠（低功耗）状态
void LCD_Sleep(void)
{
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			LCD_DRV_WriteCmd(LCD_DISPLAY_OFF);	
			break;
		case UC1701:
			LCD_UC1701_WriteCmd(0xc9);  // Set Display disable
			LCD_UC1701_WriteData(0xae);	
			
			LCD_UC1701_PinSleep();		
			break;
		default:
			break;
	}
}

//LCD唤醒，重新显示LCD_RAM内容
void LCD_WakeUp(void)
{
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			LCD_DRV_WriteCmd(LCD_DISPLAY_ON);
			break;
		case UC1701:
			LCD_UC1701_WriteCmd(0xc9);  // Set Display disable
			LCD_UC1701_WriteData(0xaf);	
			break;
		default:
			break;
	}	
}

void LCD_Update(void)
{
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			if(LCD.DATA.RefreshFlg)
			{		
				LCD_DRV_WriteCmd(LCD_SET_BOOSTER_H);			// Set Booster
				LCD_DRV_WriteCmd(LCD_SET_BOOSTER_L_X5);   		// Set Booster	
				LCD_DRV_WriteCmd(LCD_SET_EV_H);          		// set reference voltage   LCD_SET_EV_H
				LCD_DRV_WriteCmd(0x1e);							// Set EV L	0x20	 
				LCD_DRV_WriteCmd(LCD_BIAS_SELECT_1_9);
				LCD_DRV_WriteCmd(LCD_REGULATION_RATIO_50);
				LCD_DRV_WriteCmd(0x2F);         				//power control(VB,VR,VF=1,1,1)			
				LCD_DRV_WriteCmd(LCD_DISPLAY_ON);	
				LCD_DRV_WriteCmd(0x40);   						// 从第一行开始显示
				
				if(LCD.DATA.RefreshFlg & LCD_REFRESH_SIGNAL)
				{
					LCD.DATA.RefreshFlg &= ~LCD_REFRESH_SIGNAL;
					LCD_DisplayRSSI(RADIO.IM.LatestRssi);
				}
				
				if(LCD.DATA.RefreshFlg & LCD_REFRESH_BATTERY)
				{
					LCD.DATA.RefreshFlg &= ~LCD_REFRESH_BATTERY;
					ADC_LcdDisValue();
				}

				if(LCD.DATA.RefreshFlg & LCD_REFRESH_STUDEN_ID)
				{
					LCD.DATA.RefreshFlg &= ~LCD_REFRESH_STUDEN_ID;
					LCD_DisplayDeviceId();
				}
				
				if(LCD.DATA.RefreshFlg & LCD_REFRESH_SCENE)
				{
					LCD.DATA.RefreshFlg &= ~LCD_REFRESH_SCENE;
					LCD_DisplaySceneArea();			
				}
				
				if(LCD.DATA.RefreshFlg & LCD_REFRESH_INPUT)
				{
					LCD.DATA.RefreshFlg &= ~LCD_REFRESH_INPUT;
					
				}	
				if(LCD.DATA.RefreshFlg & LCD_REFRESH_RESULT)
				{
					LCD.DATA.RefreshFlg &= ~LCD_REFRESH_RESULT;
		//			LCD_DisplaySendResult(LCD.DATA.SendResultState);
				}		
			}
			break;
		case UC1701:
			if(LCD.DATA.RefreshFlg)
			{		
				LCD_UC1701_WriteCmd(0xab);  //set LC //频率 ,不加这条指令会导致LCD显示颠倒
				
				if(LCD.DATA.RefreshFlg & LCD_REFRESH_SIGNAL)
				{
					LCD.DATA.RefreshFlg &= ~LCD_REFRESH_SIGNAL;
					LCD_DisplayRSSI(RADIO.IM.LatestRssi);
				}
				
				if(LCD.DATA.RefreshFlg & LCD_REFRESH_BATTERY)
				{
					LCD.DATA.RefreshFlg &= ~LCD_REFRESH_BATTERY;
					ADC_LcdDisValue();
				}

				if(LCD.DATA.RefreshFlg & LCD_REFRESH_STUDEN_ID)
				{
					LCD.DATA.RefreshFlg &= ~LCD_REFRESH_STUDEN_ID;
					LCD_DisplayDeviceId();
				}
				
				if(LCD.DATA.RefreshFlg & LCD_REFRESH_SCENE)
				{
					LCD.DATA.RefreshFlg &= ~LCD_REFRESH_SCENE;
					LCD_DisplaySceneArea();			
				}
				
				if(LCD.DATA.RefreshFlg & LCD_REFRESH_INPUT)
				{
					LCD.DATA.RefreshFlg &= ~LCD_REFRESH_INPUT;
					
				}	
				if(LCD.DATA.RefreshFlg & LCD_REFRESH_RESULT)
				{
					LCD.DATA.RefreshFlg &= ~LCD_REFRESH_RESULT;
		//			LCD_DisplaySendResult(LCD.DATA.SendResultState);
				}
				
				LCD_UC1701_PinSleep();		// LCD 配置操作完后，配置引脚减少功耗
			}			
			break;
		default:
			break;
	}	
}

//全屏清屏
void LCD_ClearScreen(void)
{
	uint8_t TmpBuf[64];
	
	memset(TmpBuf, ASCII_CLEAR, 64);
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			LCD_DRV_DisplayN(0, 64, TmpBuf);
			break;
		case UC1701:
			LCD_UC1701_DisplayN(0, 64, TmpBuf);
			break;
		default:
			break;
	}	
}

//全屏显示
void LCD_DisplayAll(void)
{
	uint8_t TmpBuf[64];	
	
	memset(TmpBuf, 0xFF, 64);
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			LCD_DRV_DisplayN(0, 64, TmpBuf);
			break;
		case UC1701:
			LCD_UC1701_DisplayN(0, 64, TmpBuf);
			break;
		default:
			break;
	}	
}


void LCD_DisplayLetter(uint8_t Letter)
{
	uint8_t pLcdLetter = 0;	
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			LCD_ClearInputArea();
			if((Letter & LCD_A) == LCD_A)
			{
				LCD_DRV_DisplayOne(35 + pLcdLetter, LCD_DRV_DOT_ASCII, ASCII_A);
				pLcdLetter++;
			}
			
			if((Letter & LCD_B) == LCD_B)
			{
				LCD_DRV_DisplayOne(35 + pLcdLetter, LCD_DRV_DOT_ASCII, ASCII_B);
				pLcdLetter++;
			}

			if((Letter & LCD_C) == LCD_C)
			{
				LCD_DRV_DisplayOne(35 + pLcdLetter, LCD_DRV_DOT_ASCII, ASCII_C);
				pLcdLetter++;
			}

			if((Letter & LCD_D) == LCD_D)
			{
				LCD_DRV_DisplayOne(35 + pLcdLetter, LCD_DRV_DOT_ASCII, ASCII_D);
				pLcdLetter++;
			}
			break;
		case UC1701:
			LCD_ClearInputArea();
			if((Letter & LCD_A) == LCD_A)
			{
				LCD_UC1701_DisplayOne(35 + pLcdLetter, LCD_DRV_DOT_ASCII, ASCII_A);
				pLcdLetter++;
			}
			
			if((Letter & LCD_B) == LCD_B)
			{
				LCD_UC1701_DisplayOne(35 + pLcdLetter, LCD_DRV_DOT_ASCII, ASCII_B);
				pLcdLetter++;
			}

			if((Letter & LCD_C) == LCD_C)
			{
				LCD_UC1701_DisplayOne(35 + pLcdLetter, LCD_DRV_DOT_ASCII, ASCII_C);
				pLcdLetter++;
			}

			if((Letter & LCD_D) == LCD_D)
			{
				LCD_UC1701_DisplayOne(35 + pLcdLetter, LCD_DRV_DOT_ASCII, ASCII_D);
				pLcdLetter++;
			}			
			break;
		default:
			break;
	}	
}

void LCD_DisplayJudge(uint8_t Value)
{
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			LCD_ClearInputArea();
			switch(Value)
			{
				case JUDGE_CLEAR:
					
					break;
				case JUDGE_TRUE:
					LCD_DRV_DisplayOne(35, LCD_DRV_DOT_HANZI, 0xA1CC);
					break;
				case JUDGE_FALSE:
					LCD_DRV_DisplayOne(35, LCD_DRV_DOT_HANZI, 0xA1C1);
					break;
				default:
					break;
			}
			break;
		case UC1701:
			LCD_ClearInputArea();
			switch(Value)
			{
				case JUDGE_CLEAR:
					
					break;
				case JUDGE_TRUE:
					LCD_UC1701_DisplayOne(35, LCD_DRV_DOT_HANZI, 0xA1CC);
					break;
				case JUDGE_FALSE:
					LCD_UC1701_DisplayOne(35, LCD_DRV_DOT_HANZI, 0xA1C1);
					break;
				default:
					break;
			}			
			break;
		default:
			break;
	}	
}

void LCD_DisplayHongbao(uint8_t Value)
{
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			LCD_ClearInputArea();			
			switch(Value)
			{
				case HONGBAO_DISPLAY:
					LCD_DRV_DisplayOne(50, LCD_DRV_DOT_HANZI, 0xA1EF);	
					break;
				case HONGBAO_CLEAR:
					
					break;
				default:
					break;
			}	
			break;
		case UC1701:
			LCD_ClearInputArea();			
			switch(Value)
			{
				case HONGBAO_DISPLAY:
					LCD_UC1701_DisplayOne(50, LCD_DRV_DOT_HANZI, 0xA1EF);	
					break;
				case HONGBAO_CLEAR:
					
					break;
				default:
					break;
			}			
			break;
		default:
			break;
	}	
}

void LCD_DisplaySendResult(LCD_SEND_RESULT_TYPE SendResult)
{
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			switch(SendResult)
			{
				case SEND_RESULT_CLEAR:	
					LCD_DisplayDeviceId();
					break;
				case SEND_RESULT_OK:
					LCD_DRV_DisplayOne(4, LCD_DRV_DOT_HANZI, 0xB7A2);
					LCD_DRV_DisplayOne(6, LCD_DRV_DOT_HANZI, 0xCBCD);
					LCD_DRV_DisplayOne(8, LCD_DRV_DOT_HANZI, 0xB3C9);
					LCD_DRV_DisplayOne(10, LCD_DRV_DOT_HANZI, 0xB9A6);
					break;
				case SEND_RESULT_FAIL:
					LCD_DRV_DisplayOne(4, LCD_DRV_DOT_HANZI, 0xB7A2);
					LCD_DRV_DisplayOne(6, LCD_DRV_DOT_HANZI, 0xCBCD);
					LCD_DRV_DisplayOne(8, LCD_DRV_DOT_HANZI, 0xCAA7);
					LCD_DRV_DisplayOne(10, LCD_DRV_DOT_HANZI, 0xB0DC);
					break;
				default:
					break;
			}	
			break;
		case UC1701:
			switch(SendResult)
			{
				case SEND_RESULT_CLEAR:	
					LCD_DisplayDeviceId();
					break;
				case SEND_RESULT_OK:
					LCD_UC1701_DisplayOne(4, LCD_DRV_DOT_HANZI, 0xB7A2);
					LCD_UC1701_DisplayOne(6, LCD_DRV_DOT_HANZI, 0xCBCD);
					LCD_UC1701_DisplayOne(8, LCD_DRV_DOT_HANZI, 0xB3C9);
					LCD_UC1701_DisplayOne(10, LCD_DRV_DOT_HANZI, 0xB9A6);
					break;
				case SEND_RESULT_FAIL:
					LCD_UC1701_DisplayOne(4, LCD_DRV_DOT_HANZI, 0xB7A2);
					LCD_UC1701_DisplayOne(6, LCD_DRV_DOT_HANZI, 0xCBCD);
					LCD_UC1701_DisplayOne(8, LCD_DRV_DOT_HANZI, 0xCAA7);
					LCD_UC1701_DisplayOne(10, LCD_DRV_DOT_HANZI, 0xB0DC);
					break;
				default:
					break;
			}			
			break;
		default:
			break;
	}	
}

void LCD_DisplaySignal(LCD_SIGNAL_LEVEL_TYPE Value)					//显示信号强度
{	
	uint8_t i,SignalDot[64];	
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			switch(Value)
			{
				case RSSI_0:
					memcpy(SignalDot, Signal_0, 64);
					break;
				case RSSI_1:
					memcpy(SignalDot, Signal_1, 64);
					break;
				case RSSI_2:
					memcpy(SignalDot, Signal_2, 64);
					break;
				case RSSI_3:
					memcpy(SignalDot, Signal_3, 64);
					break;
				case RSSI_4:
					memcpy(SignalDot, Signal_4, 64);
					break;
				case RSSI_OFF:
					memset(SignalDot, 0x00, 64);
					break;		
				default:
					break;
			}
			
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
			break;
		case UC1701:
			switch(Value)
			{
				case RSSI_0:
					memcpy(SignalDot, Signal_0, 64);
					break;
				case RSSI_1:
					memcpy(SignalDot, Signal_1, 64);
					break;
				case RSSI_2:
					memcpy(SignalDot, Signal_2, 64);
					break;
				case RSSI_3:
					memcpy(SignalDot, Signal_3, 64);
					break;
				case RSSI_4:
					memcpy(SignalDot, Signal_4, 64);
					break;
				case RSSI_OFF:
					memset(SignalDot, 0x00, 64);
					break;		
				default:
					break;
			}
			
//			LCD_DRV_WriteCmd(0+0xb0);			// page
//			LCD_DRV_WriteCmd(0x10 + 0);
//			LCD_DRV_WriteCmd(0x00 + 0);
			LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|0);		//set page address	
			LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 		//column  lsb		
			LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|0); 	//column  msb	
			LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);			// 开始写数据	
			for(i=0;i<32 ;i++)
			{
				LCD_UC1701_WriteData(SignalDot[i]);
			}	
			
//			LCD_DRV_WriteCmd(1+0xb0);			// page
//			LCD_DRV_WriteCmd(0x10 + 0);
//			LCD_DRV_WriteCmd(0x00 + 0);
			LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|1);		//set page address	
			LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 		//column  lsb		
			LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|0); 	//column  msb	
			LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);			// 开始写数据				
			for(i=32;i<64 ;i++)
			{
				LCD_UC1701_WriteData(SignalDot[i]);
			}			
			break;
		default:
			break;
	}	
}

void LCD_DisplayRSSI(uint8_t Rssi)
{
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			if(Rssi >= 80)
			{
				LCD_DisplaySignal(RSSI_1);
			}
			else if(Rssi >= 70 && Rssi < 80)
			{
				LCD_DisplaySignal(RSSI_2);
			}
			else if(Rssi >= 60 && Rssi < 70)
			{
				LCD_DisplaySignal(RSSI_3);
			}
			else if(Rssi >= 20 && Rssi< 60)
			{
				LCD_DisplaySignal(RSSI_4);
			}	
			else
			{
				LCD_DisplaySignal(RSSI_0);
			}	
			break;
		case UC1701:
			if(Rssi >= 80)
			{
				LCD_DisplaySignal(RSSI_1);
			}
			else if(Rssi >= 70 && Rssi < 80)
			{
				LCD_DisplaySignal(RSSI_2);
			}
			else if(Rssi >= 60 && Rssi < 70)
			{
				LCD_DisplaySignal(RSSI_3);
			}
			else if(Rssi >= 20 && Rssi< 60)
			{
				LCD_DisplaySignal(RSSI_4);
			}	
			else
			{
				LCD_DisplaySignal(RSSI_0);
			}			
			break;
		default:
			break;
	}	
}

void LCD_DisplayBattery(LCD_BATTERY_LEVEL_TYPE Value)			//显示电池电量
{
	uint8_t i,BatteryDot[64];
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			switch(Value)
			{
				case BATTERY_LEVEL_0:
					memcpy(BatteryDot, Battery_0, 64);
					break;
				case BATTERY_LEVEL_1:
					memcpy(BatteryDot, Battery_1, 64);
					break;
				case BATTERY_LEVEL_2:
					memcpy(BatteryDot, Battery_2, 64);
					break;
				case BATTERY_LEVEL_3:
					memcpy(BatteryDot, Battery_3, 64);
					break;
				case BATTERY_LEVEL_OFF:
					memset(BatteryDot, 0x00, 64);
					break;
				default:
		//			memset(BatteryDot, 0x00, 64);
					break;
			}	
			
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
			break;
		case UC1701:
			switch(Value)
			{
				case BATTERY_LEVEL_0:
					memcpy(BatteryDot, Battery_0, 64);
					break;
				case BATTERY_LEVEL_1:
					memcpy(BatteryDot, Battery_1, 64);
					break;
				case BATTERY_LEVEL_2:
					memcpy(BatteryDot, Battery_2, 64);
					break;
				case BATTERY_LEVEL_3:
					memcpy(BatteryDot, Battery_3, 64);
					break;
				case BATTERY_LEVEL_OFF:
					memset(BatteryDot, 0x00, 64);
					break;
				default:
		//			memset(BatteryDot, 0x00, 64);
					break;
			}	
			
//			LCD_DRV_WriteCmd(0+0xb0);			// page
//			LCD_DRV_WriteCmd(0x10 + 6);
//			LCD_DRV_WriteCmd(0x00 + 0);
			LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|0);		//set page address	
			LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 		//column  lsb		
			LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|0X60); 	//column  msb	
			LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);			// 开始写数据				
			for(i=0;i<32 ;i++)
			{
				LCD_UC1701_WriteData(BatteryDot[i]);
			}	
			
//			LCD_DRV_WriteCmd(1+0xb0);			// page
//			LCD_DRV_WriteCmd(0x10 + 6);
//			LCD_DRV_WriteCmd(0x00 + 0);
			LCD_UC1701_WriteCmd(LCD_UC1701_SET_PAGE_ADDR|1);		//set page address	
			LCD_UC1701_WriteCmd(LCD_UC1701_SET_COLUMN_ADDR_H); 		//column  lsb		
			LCD_UC1701_WriteData(LCD_UC1701_SET_COLUMN_ADDR_L|0X60); 	//column  msb	
			LCD_UC1701_WriteCmd(LCD_UC1701_WRITE_DATA_H);			// 开始写数据				
			for(i=32;i<64 ;i++)
			{
				LCD_DRV_WriteData(BatteryDot[i]);
			}				
			break;
		default:
			break;
	}	
}

void LCD_DisplayDeviceId(void)
{
	uint32_t TmpUid, i;
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			TmpUid =  RADIO.MATCH.DtqUid[0] 	   | 
					   RADIO.MATCH.DtqUid[1] << 8  |
					   RADIO.MATCH.DtqUid[2] << 16 |
					   RADIO.MATCH.DtqUid[3] << 24 ;

			for(i = 0;i < 6;i++)
			{
				LCD_DRV_DisplayDigit(10-i,TmpUid%10);
				TmpUid = TmpUid/10;
			}

			LCD_DRV_DisplayOne(4, LCD_DRV_DOT_ASCII, ASCII_CLEAR);
			LCD_DRV_DisplayOne(11, LCD_DRV_DOT_ASCII, ASCII_CLEAR);		
			break;
		case UC1701:
			TmpUid =  RADIO.MATCH.DtqUid[0] 	   | 
					   RADIO.MATCH.DtqUid[1] << 8  |
					   RADIO.MATCH.DtqUid[2] << 16 |
					   RADIO.MATCH.DtqUid[3] << 24 ;

			for(i = 0;i < 6;i++)
			{
				LCD_UC1701_DisplayDigit(10-i,TmpUid%10);
				TmpUid = TmpUid/10;
			}

			LCD_UC1701_DisplayOne(4, LCD_DRV_DOT_ASCII, ASCII_CLEAR);
			LCD_UC1701_DisplayOne(11, LCD_DRV_DOT_ASCII, ASCII_CLEAR);				
			break;
		default:
			break;
	}	
}


void LCD_ClearInputArea(void)
{
	uint8_t TmpBuf[64];
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			memset(TmpBuf, ASCII_CLEAR, 64);
			LCD_DRV_DisplayN(32, 16, TmpBuf);	
			break;
		case UC1701:
			memset(TmpBuf, ASCII_CLEAR, 64);
			LCD_UC1701_DisplayN(32, 16, TmpBuf);
			break;
		default:
			break;
	}	
	
}

void  LCD_DisplaySceneArea(void)
{	
	uint32_t i;
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			// 分三次刷新
			for(i = 0;i < 3;i++)
			{
				// LCD每行，倒数第二个字节是ASCII码，而最后一个字节是汉字的前半个GBK码，则最后一个字节清除掉
				if((LCD.DATA.Scene[16*(i+1) - 1] < 0x81) && (LCD.DATA.Scene[16*(i+1)] >= 0x81))
					LCD.DATA.Scene[16*(i+1)] = 0x00;
				LCD_DRV_DisplayN(16*(i+1), 16, LCD.DATA.Scene+1+16*i);	
			}	
			break;
		case UC1701:
			for(i = 0;i < 3;i++)
			{
				// LCD每行，倒数第二个字节是ASCII码，而最后一个字节是汉字的前半个GBK码，则最后一个字节清除掉
				if((LCD.DATA.Scene[16*(i+1) - 1] < 0x81) && (LCD.DATA.Scene[16*(i+1)] >= 0x81))
					LCD.DATA.Scene[16*(i+1)] = 0x00;
				LCD_UC1701_DisplayN(16*(i+1), 16, LCD.DATA.Scene+1+16*i);	
			}			
			break;
		default:
			break;
	}	
}

void LCD_ClearSceneArea(void)
{
	uint8_t TmpBuf[48];
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			memset(TmpBuf, 0x00, 48);
			LCD_DRV_DisplayN(16, 48, TmpBuf);
			break;
		case UC1701:
			memset(TmpBuf, 0x00, 48);
			LCD_UC1701_DisplayN(16, 48, TmpBuf);			
			break;
		default:
			break;
	}	
}

void LCD_DisDigit(uint8_t Pos, uint32_t Digit)
{
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			LCD_DRV_DisplayDigit(Pos+0,(Digit%1000)/100);
			LCD_DRV_DisplayDigit(Pos+1,(Digit%100)/10);
			LCD_DRV_DisplayDigit(Pos+2,Digit%10);		
			break;
		case UC1701:
			LCD_UC1701_DisplayDigit(Pos+0,(Digit%1000)/100);
			LCD_UC1701_DisplayDigit(Pos+1,(Digit%100)/10);
			LCD_UC1701_DisplayDigit(Pos+2,Digit%10);				
			break;
		default:
			break;
	}	
}

void LCD_DisDigit_5(uint8_t Pos, uint32_t Digit)
{
		
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			LCD_DRV_DisplayDigit(Pos+0,(Digit%100000)/10000);
			LCD_DRV_DisplayDigit(Pos+1,(Digit%10000)/1000);
			LCD_DRV_DisplayDigit(Pos+2,(Digit%1000)/100);
			LCD_DRV_DisplayDigit(Pos+3,(Digit%100)/10);
			LCD_DRV_DisplayDigit(Pos+4,Digit%10);		
			break;
		case UC1701:
			LCD_UC1701_DisplayDigit(Pos+0,(Digit%100000)/10000);
			LCD_UC1701_DisplayDigit(Pos+1,(Digit%10000)/1000);
			LCD_UC1701_DisplayDigit(Pos+2,(Digit%1000)/100);
			LCD_UC1701_DisplayDigit(Pos+3,(Digit%100)/10);
			LCD_UC1701_DisplayDigit(Pos+4,Digit%10);				
			break;
		default:
			break;
	}
}

void LCD_DisDigit_10(uint8_t Pos, uint32_t Digit)
{
	uint32_t i;
	uint32_t Tmp = Digit;
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			for(i = 0;i < 10;i++)
			{
				LCD_DRV_DisplayDigit(Pos+9-i,Tmp%10);
				Tmp = Tmp / 10;
			}			
			break;
		case UC1701:
			for(i = 0;i < 10;i++)
			{
				LCD_UC1701_DisplayDigit(Pos+9-i,Tmp%10);
				Tmp = Tmp / 10;
			}			
			break;
		default:
			break;
	}	
}

void LCD_DisDigitN(uint8_t Pos, uint32_t Digit, uint8_t Len)
{
	uint32_t i;
	uint32_t Tmp = Digit;
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			for(i = 0;i < Len;i++)
			{
				LCD_DRV_DisplayDigit(Pos+Len-1-i,Tmp%10);
				Tmp = Tmp / 10;
			}		
			break;
		case UC1701:
			for(i = 0;i < Len;i++)
			{
				LCD_UC1701_DisplayDigit(Pos+Len-1-i,Tmp%10);
				Tmp = Tmp / 10;
			}				
			break;
		default:
			break;
	}	
}

void LCD_DisVer(void)
{
	char* uID = "uID:";
	char* Vol = "Vol:      mV";
	uint32_t TmpUid;
	
	switch(LCD.DrvVer)
	{
		case IST3308CA3:
			// 先临时清除显示
			LCD_ClearSceneArea();
			
			// 完整ID
			TmpUid =  RADIO.MATCH.DtqUid[0] 	   | 
					   RADIO.MATCH.DtqUid[1] << 8  |
					   RADIO.MATCH.DtqUid[2] << 16 |
					   RADIO.MATCH.DtqUid[3] << 24 ;
			LCD_DRV_DisplayN(17, 4, (uint8_t *)uID);
			LCD_DisDigitN(21, TmpUid, 10);
			
			// 版本号
			LCD_DRV_DisplayN(34, 16, (uint8_t *)VERSION_LEVEL_NUMBER);
			
			// 电池电量
			LCD_DRV_DisplayN(50, 12, (uint8_t *)Vol);
			LCD_DisDigitN(55, ADC.LatestADCVal, 4);		
			break;
		case UC1701:
			// 先临时清除显示
			LCD_ClearSceneArea();
			
			// 完整ID
			TmpUid =  RADIO.MATCH.DtqUid[0] 	   | 
					   RADIO.MATCH.DtqUid[1] << 8  |
					   RADIO.MATCH.DtqUid[2] << 16 |
					   RADIO.MATCH.DtqUid[3] << 24 ;
			LCD_UC1701_DisplayN(17, 4, (uint8_t *)uID);
			LCD_DisDigitN(21, TmpUid, 10);
			
			// 版本号
			LCD_UC1701_DisplayN(34, 16, (uint8_t *)VERSION_LEVEL_NUMBER);
			
			// 电池电量
			LCD_UC1701_DisplayN(50, 12, (uint8_t *)Vol);
			LCD_DisDigitN(55, ADC.LatestADCVal, 4);				
			break;
		default:
			break;
	}		
}









