

/* Includes -----------------------------------------------------*/
#include "lcd_lib.h"

LCD_PARAMETERS_T 		LCD;

/* Functions ----------------------------------------------------*/


void LCD_Init(void)
{
	
	nrf_gpio_cfg_output(LCD_PIN_POWER);
	nrf_gpio_cfg_output(LCD_PIN_CSB);
	nrf_gpio_cfg_output(LCD_PIN_RST);
	nrf_gpio_cfg_output(LCD_PIN_A0);	
	nrf_gpio_cfg_output(LCD_PIN_SCL);
	nrf_gpio_cfg_output(LCD_PIN_SDA);		
	
}

//刷新LCD_RAM，更新LCD显示
void LCD_Update(void)
{
	uint8_t TmpLcdRam[18];		//临时保存LCDRAM信息
	
	if(LCD.UpdateFlg)
	{
		LCD.UpdateFlg = false;	
		
		switch(LCD.DisType)
		{
			case LCD_DIS_UPDATE:
				
				break;
			case LCD_DIS_VER:
				
				break;
			case LCD_DIS_RSSI:
				
				break;
			case LCD_DIS_VOLTAGE:
			
				break;
			case LCD_DIS_CHANNAL:
			
				break;
			case LCD_DIS_ATTEND:
				
				break;
			case LCD_DIS_DATE:
				
				break;
			default:
				LCD.DisType = LCD_DIS_UPDATE;
				break;
		}
	}
}

//关闭LCD显示，进入睡眠（低功耗）状态
void LCD_Sleep(void)
{
	LCD_DRV_WriteCmd(LCD_DISPLAY_OFF);	

}

//LCD唤醒，重新显示LCD_RAM内容
void LCD_WakeUp(void)
{
	LCD_DRV_WriteCmd(LCD_DISPLAY_ON);	
	

}


//全屏清屏
void LCD_ClearScreen(void)
{
	LCD_DRV_DisplayTest(0x00,0x00);
}

//全屏显示
void LCD_DisplayAll(void)
{
	LCD_DRV_DisplayTest(0xff,0xff);
}


void LCD_ClearLetter(void)
{

}

void LCD_DisplayLetter(uint8_t data)
{
	switch(data)
	{
		case LCD_A:
			
			break;
		case LCD_B:
			break;
		case LCD_C:
			break;
		case LCD_D:
			break;
		
	}
}

void LCD_DisplayJudge(uint8_t Value)
{
	
	LCD_DRV_ClearInputArea();
	
	switch(Value)
	{
		case JUDGE_CLEAR:
			
			break;
		case JUDGE_TRUE:
			LCD_DRV_DisplayHanzi(3,1,0xA1CC);
			break;
		case JUDGE_FALSE:
			LCD_DRV_DisplayHanzi(3,1,0xA1C1);
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
			LCD_DRV_ClearSendArea();
			break;
		case SEND_RESULT_OK:
			LCD_DRV_DisplayHanzi(3,4,0xB7A2);
			LCD_DRV_DisplayHanzi(3,5,0xCBCD);			
			LCD_DRV_DisplayHanzi(3,6,0xB3C9);
			LCD_DRV_DisplayHanzi(3,7,0xB9A6);
			break;
		case SEND_RESULT_FAIL:
			LCD_DRV_DisplayHanzi(3,4,0xB7A2);
			LCD_DRV_DisplayHanzi(3,5,0xCBCD);
			LCD_DRV_DisplayHanzi(3,6,0xCAA7);
			LCD_DRV_DisplayHanzi(3,7,0xB0DC);
			break;
		default:
			break;
	}	
}

void LCD_DisplaySignal(LCD_SIGNAL_LEVEL_TYPE Value)					//显示信号强度
{	
	switch(Value)
	{
		case RSSI_0:
			LCD_DRV_DisplaySignal();
			break;
		case RSSI_1:
			
			break;
		case RSSI_2:
			
			break;
		case RSSI_3:
			
			break;
		case RSSI_4:
			
			break;
		case RSSI_OFF:
		
			break;		
		default:
			
			break;
	}		
}

void LCD_DisplayBattery(LCD_BATTERY_LEVEL_TYPE Value)			//显示电池电量
{
	switch(Value)
	{
		case BATTERY_LEVEL_0:
			LCD_DRV_DisplayBattery();
			break;
		case BATTERY_LEVEL_1:
		
			break;
		case BATTERY_LEVEL_2:
			
			break;
		case BATTERY_LEVEL_3:

			break;
		default:

			break;
	}	
}

void LCD_ClearSegment(void)
{

}


void LCD_DisplayStudentName(void)
{
	uint8_t i, TmpNameLen = 0;

	LCD_DRV_ClearNameArea();
	
	// 计算名字长度
	for(i = 0;i < 12;i++)
	{
		// 中文GBK码不可能有0x00
		if(0x00 == RADIO.MATCH.Student.Name[i])	
		{
			TmpNameLen = i / 2;
			break;
		}
	}
	
	if(TmpNameLen)
	{
		for(i = 0;i < TmpNameLen;i++)
		{
			LCD_DRV_DisplayHanzi(1,1+i,(RADIO.MATCH.Student.Name[2*i] << 8) | RADIO.MATCH.Student.Name[2*i+1]);	// 无
		}	
	}
	else
	{
		LCD_DRV_DisplayHanzi(1,1,0xCEDE);	// 无
		LCD_DRV_DisplayHanzi(1,2,0xD0D5);	// 姓
		LCD_DRV_DisplayHanzi(1,3,0xC3FB);	// 名
	}
}

void LCD_DisplayQuestionNum(uint16_t question_num)
{

}

void LCD_DisplayScoreValue(uint16_t grade_value)
{
	uint8_t Tmp;
	
	LCD_DRV_ClearScoreArea();	
	
	Tmp = grade_value % 10;
	LCD_DRV_DisplayDigit(1, 14, Tmp);		// 个位
	Tmp = (grade_value % 100) / 10;			
	LCD_DRV_DisplayDigit(1, 13, Tmp);		// 十位
	Tmp = (grade_value % 1000) / 100;				
	LCD_DRV_DisplayDigit(1, 12, Tmp);		// 百位
	
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
		LCD_DRV_DisplayDigit(0, 10-i, TmpUid%10);
		TmpUid = TmpUid/10;
	}
}


void LCD_DisplayScene(uint8_t Scene)
{
	
	LCD_DRV_DisplayHanzi(2,1,0xB5A5);	
	LCD_DRV_DisplayHanzi(2,2,0xD1A1);	
	LCD_DRV_DisplayHanzi(2,3,0xCCE2);	
	LCD_DRV_DisplayHanzi(2,4,0xD7F7);	
	LCD_DRV_DisplayHanzi(2,5,0xB4F0);	
	
}



#define DISPLAY_TIME 		(200)						//显示的时间
void LCD_DisplayTest(void)
{
}








