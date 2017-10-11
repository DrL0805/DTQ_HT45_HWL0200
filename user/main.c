
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
	LCD_Init();
	TEST_Init();

	TIMER_RxWindowStart();
	TIMER_SysStateStart();	
	
	LCD_ClearScreen();
	LCD_DisplayDeviceId();
	LCD_DisplaySignal(RSSI_4);
	LCD_DisplayBattery(BATTERY_LEVEL_2);
	LCD_DisplayStudentName();
	LCD_DisplayScoreValue(RADIO.MATCH.Student.Score);
	
	POWER.SysInitializedFlg = true;
	
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
//	uint8_t TmpBuf[] = {0xB9, 0xA7, 0xCF, 0xB2, 0xC4, 0xE3, 0xA3, 0xA1, 0xB4, 0xF0, 0xB6, 0xD4, 0xC1, 0xCB};
//	
//	LCD_DRV_DisplayN(40, 14, TmpBuf);
//	LCD_DRV_DisplayOne(43, 0, ASCII_2);
	
//	LED_TOG(LED_0);
//	nrf_delay_ms(100);
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



