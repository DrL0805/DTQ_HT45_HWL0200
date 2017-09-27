
#include "main.h"

static void MAIN_DebugFun(void);
	
int main (void)
{
	POWER.SysInitializedFlg = false;

	GPIO_Default();
	CLOCK_Init();
	TIMERS_Init();
	KEY_Init();
	NFC_Init();
	FLASH_Init();
	POWER_Init();	
	APP_Init();
	RADIO_Init();
	LED_Init();
//	TIMER_TempStart();
	W25_Init();
	LCD_DRV_Init();	

	TIMER_RxWindowStart();
//	TIMER_SysStateStart();	
	
	LCD_ClearScreen();
	LCD_DisplayDeviceId();
	LCD_DisplaySignal(RSSI_0);
	LCD_DisplayBattery(BATTERY_LEVEL_0);
	LCD_DisplayStudentName();
	LCD_DisplayScoreValue(RADIO.MATCH.Student.Score);
	
	POWER.SysInitializedFlg = true;
	
//	while(1)
//	{
//		for(uint8_t i=18; i<0x28;i++)
//		{
//			LCD_DRV_Init_TEST(i);
//			
//			LCD_ClearScreen();
//			LCD_DisplayDeviceId();
//			LCD_DisplaySignal(RSSI_0);
//			LCD_DisplayBattery(BATTERY_LEVEL_0);
//			LCD_DisplayStudentName();
//			LCD_DisplayScoreValue(RADIO.MATCH.Student.Score);			
//			
//			nrf_delay_ms(2000);
//		}
//	}
	
	
	
	while(true)
	{
		switch(POWER.SysState)
		{
			case SYS_ON:
				RADIO_RxDataHandler();
				APP_KeyHandler();
				break;
			case SYS_SLEEP:
				RADIO_RxDataHandler();
				APP_KeyHandler();
				break;
			case SYS_OFF:
				APP_KeyHandler();
				break;
			case SYS_TEST:			
				break;
			case SYS_MATCH:					
				break;
			default:
				NVIC_SystemReset();
				break;
		}			
		MAIN_DebugFun();
		__WFE();							
		__WFI();		
	}
}



static void MAIN_DebugFun(void)
{
//	KEY_Scan();
//	LCD_DisplayStudentName(KEY.ScanValue);
//	LCD_DisplayQuestionNum(45);
//	LCD_DisplayScoreValue(87);


//	LED_ON(LED_0);
//	nrf_delay_ms(200);
//	LED_OFF(LED_0);
//	nrf_delay_ms(200);
	
//		LCD_DRV_DisplayTest(0x00,0x00);
//		nrf_delay_ms(500);			
//		LCD_DRV_DisplayPicture(BMP);
//		nrf_delay_ms(500);
//		LCD_DRV_DisplayTest(0xAA,0xFF);
//		nrf_delay_ms(500);	
}


// 计算异或值
uint8_t XOR_Cal(uint8_t * dat,uint16_t length)
{
	uint8_t temp_xor;
	uint16_t i;

	temp_xor = *dat;
	for(i = 1;i < length; i++)
	{
		temp_xor = temp_xor ^ *(dat+i);
	}
	return temp_xor;
}

// 比较两数组值是否完全相同，true：相同，false：不同
bool ArrayCmp(uint8_t *str1, uint8_t *str2, uint8_t len)
{
	uint8_t i;
	for(i = 0; i < len ; i++)
	{
		if(str1[i] != str2[i])
			return false;
	}
	return true;
}

// 获取随机数值：0~255
uint8_t GetRandomNumber(void)
{
    NRF_RNG->TASKS_START = 1; // start the RNG peripheral.

	// Wait until the value ready event is generated.
	while (NRF_RNG->EVENTS_VALRDY == 0)
	{
		// Do nothing.
	}
	NRF_RNG->EVENTS_VALRDY = 0;		 // Clear the VALRDY EVENT.
	
	NRF_RNG->TASKS_STOP = 1;		//随机数产生后要STOP，否则一直运行，产生功耗
	
	return (uint8_t)NRF_RNG->VALUE;
}

/* 51822的gpio配置为默认状态 */
void GPIO_Default(void)
{
    uint32_t i = 0;
    for(i = 0; i< 32 ; i++ ) 
	{
        NRF_GPIO->PIN_CNF[i] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                               | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                               | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                               | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
                               | (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);
    }
}



