

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


void LCD_Init(void)
{
		
	LCD_DRV_Init();	
}


//关闭LCD显示，进入睡眠（低功耗）状态
void LCD_Sleep(void)
{
//	LCD_DRV_WriteCmd(0x40);  			// 从第一行开始显示
	LCD_DRV_WriteCmd(LCD_DISPLAY_OFF);	
	
	TIMER_LCDStop();
}

//LCD唤醒，重新显示LCD_RAM内容
void LCD_WakeUp(void)
{
//	LCD_DRV_WriteCmd(0x40);  			// 从第一行开始显示
	LCD_DRV_WriteCmd(LCD_DISPLAY_ON);

	TIMER_LCDStart();
}

void LCD_Update(void)
{
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
			LCD_DisplaySignal(RSSI_4);
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
}

//全屏清屏
void LCD_ClearScreen(void)
{
	uint8_t TmpBuf[64];
	
	memset(TmpBuf, ASCII_CLEAR, 64);
	LCD_DRV_DisplayN(0, 64, TmpBuf);		
}

//全屏显示
void LCD_DisplayAll(void)
{
	uint8_t TmpBuf[64];
	
	memset(TmpBuf, 0xFF, 64);
	LCD_DRV_DisplayN(0, 64, TmpBuf);
}


void LCD_DisplayLetter(uint8_t Letter)
{
	LCD_ClearInputArea();
	uint8_t pLcdLetter = 0;
	
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
}

void LCD_DisplayJudge(uint8_t Value)
{
	
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
}

void LCD_DisplayHongbao(uint8_t Value)
{
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
}

void LCD_DisplaySendResult(LCD_SEND_RESULT_TYPE SendResult)
{
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
}

void LCD_DisplaySignal(LCD_SIGNAL_LEVEL_TYPE Value)					//显示信号强度
{	
	uint8_t i,SignalDot[64];	
	
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
//			memset(SignalDot, 0x00, 64);
			break;
	}
	
//	LCD_DRV_WriteCmd(0x40);  			// 从第一行开始显示	
	
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

void LCD_DisplayBattery(LCD_BATTERY_LEVEL_TYPE Value)			//显示电池电量
{
	uint8_t i,BatteryDot[64];
	
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
		default:
//			memset(BatteryDot, 0x00, 64);
			break;
	}	

//	LCD_DRV_WriteCmd(0x40);  			// 从第一行开始显示		
	
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

void LCD_DisplayDeviceId(void)
{
	uint32_t TmpUid, i;
	
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
	
//----------------------------------------------------------	
	
	// 显示测试内容
//	LCD_DRV_DisplayDigit(13,(APP.KeyCnt%1000)/100);
//	LCD_DRV_DisplayDigit(14,(APP.KeyCnt%100)/10);
//	LCD_DRV_DisplayDigit(15,APP.KeyCnt%10);	

//	LCD_DRV_DisplayDigit(0,(TEST.TxFaiCnt%1000)/100);
//	LCD_DRV_DisplayDigit(1,(TEST.TxFaiCnt%100)/10);
//	LCD_DRV_DisplayDigit(2,TEST.TxFaiCnt%10);	
	
//	LCD_DRV_DisplayDigit(12,(TEST.TxSucCnt%10000)/1000);
//	LCD_DRV_DisplayDigit(13,(TEST.TxSucCnt%1000)/100);
//	LCD_DRV_DisplayDigit(14,(TEST.TxSucCnt%100)/10);
//	LCD_DRV_DisplayDigit(15,TEST.TxSucCnt%10);	
//	
//	LCD_DRV_DisplayDigit(0,(RADIO.MATCH.DtqNum%1000)/100);
//	LCD_DRV_DisplayDigit(1,(RADIO.MATCH.DtqNum%100)/10);
//	LCD_DRV_DisplayDigit(2,RADIO.MATCH.DtqNum%10);		
//	
//	LCD_DRV_DisplayDigit(5,(APP.EchoCnt%10000)/1000);
//	LCD_DRV_DisplayDigit(6,(APP.EchoCnt%1000)/100);
//	LCD_DRV_DisplayDigit(7,(APP.EchoCnt%100)/10);
//	LCD_DRV_DisplayDigit(8,APP.EchoCnt%10);	
}


void LCD_ClearInputArea(void)
{
	uint8_t TmpBuf[64];
	
	memset(TmpBuf, ASCII_CLEAR, 64);
	LCD_DRV_DisplayN(32, 16, TmpBuf);	
}

void  LCD_DisplaySceneArea(void)
{	
	// 一次整屏刷新
	LCD_DRV_DisplayN(16, LCD.DATA.Scene[0], LCD.DATA.Scene+1);	
	
//	// 分3次刷新
////	if(LCD.DATA.ScenePos%16 == 0)
////	{
//		LCD_DRV_DisplayN(16+LCD.DATA.ScenePos, 16, LCD.DATA.Scene + 1 + LCD.DATA.ScenePos);	
////	}	
////	else
////	{
////		LCD_DRV_DisplayN(16+LCD.DATA.ScenePos, 16, LCD.DATA.Scene + 1 + LCD.DATA.ScenePos);	
////	}
//	
//	if(*(LCD.DATA.Scene + 1 + LCD.DATA.ScenePos + 15) >= 0x81)	// 汉字显示
//	{
//		LCD.DATA.ScenePos += 17;
//	}
//	else													// ASCII显示
//	{
//		LCD.DATA.ScenePos += 16;
//	}	
//	
//	if(LCD.DATA.ScenePos < 48)
//	{
//		LCD.DATA.RefreshFlg |= LCD_REFRESH_SCENE;
//	}
}

void LCD_ClearSceneArea(void)
{
	LCD.DATA.Scene[0] = 48;
	memset(LCD.DATA.Scene+1, 0x00, 48);
	
	LCD.DATA.RefreshFlg |= LCD_REFRESH_SCENE;
	LCD.DATA.ScenePos = 0;
}



