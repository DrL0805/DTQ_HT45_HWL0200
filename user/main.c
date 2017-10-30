
#include "main.h"

static void MAIN_DebugFun(void);



int main (void)
{
	POWER.SysInitializedFlg = false;
	
	GPIO_Default();
	CLOCK_Init();
//	DEBUG_Init();
	
	TIMERS_Init();
	KEY_Init();
	NFC_Init();
	FLASH_Init();
	POWER_Init();	
	APP_Init();
	
	RADIO_Init();
	LED_Init();
	W25_Init();
	LCD_Init();
	ADC_Init();
	WDT_Init();	
	
//	W25_ReadTestData();
	
	TIMER_RxWindowStart();	
	TIMER_SysStateStart();	
//	TIMER_LCDStart();
	TIMER_ADCStart();
	LCD_DRV_WriteCmd(LCD_DISPLAY_ON);
	LCD_ClearScreen();
	
	LCD.DATA.RefreshFlg |= LCD_REFRESH_SIGNAL;
	LCD.DATA.RefreshFlg |= LCD_REFRESH_STUDEN_ID;
	POWER.SysInitializedFlg = true;	
	
//	LCD_DisDigit(0, RADIO.MATCH.DtqNum);
//	LCD_DisDigit(4, RADIO.MATCH.TxChannal);
//	LCD_DisDigit(8, RADIO.MATCH.RxChannal);
//	LCD_DisDigit(12, ++TmpCnt);
	
//	TIMER_TempStart();
	
	
	while(true)
	{
		switch(POWER.SysState)
		{
			case SYS_ON:	
				TIMER_EventHandler();	
				RADIO_RxDataHandler();	
				APP_KeyHandler();	
				LCD_Update();	
				ADC_Update();	
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
		APP_ParUpdate();
//		MAIN_DebugFun();
		WDT_FeedDog();			
		// 若接收缓存数据全部处理完成，休眠
		if(!get_rx_fifo_count() || !LCD.DATA.RefreshFlg || !APP.NFCIrqFlg)
		{
			__WFE();							
			__WFI();			
		}		
	}
}


static void MAIN_DebugFun(void)
{
//	uint32_t addr = 0x100000;
//	uint8_t WriteBuf[5] = {0x11,0x22,0x33,0x44,0x55};
//	uint8_t ReadBuf[5];

//	W25_FlashSectorErase(addr);
//	W25_FlashPageWrite(WriteBuf, addr, 5);
//	
//	W25_SpiFlashBufferRead(ReadBuf, addr, 5);
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



