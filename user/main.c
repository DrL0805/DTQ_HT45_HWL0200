
#include "main.h"

static void MAIN_DebugFun(void);

app_fifo_t my_fifo;

uint16_t buffer_size = 2048;
uint8_t	buffer[2048];	

int main (void)
{
	POWER.SysInitializedFlg = false;
	
	GPIO_Default();
	CLOCK_Init();
//	DEBUG_Init();
	nrf_gpio_cfg_output(TX_PIN_NUMBER_2);
	nrf_gpio_cfg_output(RX_PIN_NUMBER_2);
	
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
	ADC_Init();
	TEST_Init();
	
	TIMER_RxWindowStart();
	TIMER_SysStateStart();	
	TIMER_LCDStart();
	
	LCD_ClearScreen();
	LCD_DisplayDeviceId();
	LCD_DisplaySignal(RSSI_4);
	LCD_DisplayBattery(BATTERY_LEVEL_3);
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
				LCD_Update();
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
//		__WFE();							
//		__WFI();		
	}
}



static void MAIN_DebugFun(void)
{
//	LCD_POWER_ON();
//	LCD_DRV_WriteCmd(LCD_DISPLAY_ON);	
//	LCD_DRV_WriteCmd(0x40); 
	
//	uint32_t err_code;
//	uint32_t i,j=38,k;
//	uint8_t m=4,n=98,p;
//	uint32_t data_len = 1024;
//	uint8_t write_data[1024] = {1, 2, 3, 4, 5};
//	uint8_t  read_data[1024];  	
//	uint8_t TmpBuf[] = {0xB9, 0xA7, 0xCF, 0xB2, 0xC4, 0xE3, 0xA3, 0xA1, 0xB4, 0xF0, 0xB6, 0xD4, 0xC1, 0xCB};
//	
//	LCD_DRV_DisplayN(40, 14, TmpBuf);
//	LCD_DRV_DisplayOne(43, 0, ASCII_2);
	
//	LED_TOG(LED_0);
//	nrf_delay_ms(100);
	
//	while(1)
//	{
//		nrf_gpio_pin_set(TX_PIN_NUMBER_2);
//		nrf_gpio_pin_set(RX_PIN_NUMBER_2);
//		LCD_Refresh(0xFF);
////		nrf_delay_ms(500);
//		nrf_gpio_pin_clear(TX_PIN_NUMBER_2);
//		nrf_gpio_pin_clear(RX_PIN_NUMBER_2);
//		LCD_Refresh(0x00);
////		nrf_delay_ms(500);
//	}
	

//	err_code = app_fifo_init(&my_fifo, buffer, (uint16_t)sizeof(buffer));
//	
//	data_len = 1024;
//	err_code = app_fifo_write(&my_fifo, write_data, &data_len);
//	if (err_code == NRF_SUCCESS)
//	{
//		if (data_len < 5)
//		{
//			// Attempt another write operation using data_len value as offset
//		}
//	}
//	else if (err_code == NRF_ERROR_NO_MEM)
//	{
//		// FIFO is full
//	}
//	else
//	{
//		// API parameters incorrect, should not happen
//	}	

//		nrf_gpio_pin_set(TX_PIN_NUMBER_2);
//		nrf_gpio_pin_set(RX_PIN_NUMBER_2);	
//	// Read 5 elements to the FIFO
//	data_len = 1024;
//	err_code = app_fifo_read(&my_fifo, read_data, &data_len);
//	// Check if write was successful
//	if (err_code == NRF_SUCCESS)
//	{
//		// Check if read was partial
//		if (data_len < 5)
//		{
//			// Not as many elements in array as requested
//		}
//	}
//	else if (err_code == NRF_ERROR_NOT_FOUND)
//	{
//		// FIFO is empty
//	}
//	else
//	{
//		// API parameters incorrect, should not happen
//	}
//		nrf_gpio_pin_clear(TX_PIN_NUMBER_2);
//		nrf_gpio_pin_clear(RX_PIN_NUMBER_2);	
//	nrf_delay_ms(100);

//	nrf_gpio_pin_set(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_set(RX_PIN_NUMBER_2);		
//	memset(read_data, 0x00, 256);
//	nrf_gpio_pin_clear(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_clear(RX_PIN_NUMBER_2);	
//	nrf_delay_ms(50);

//	nrf_gpio_pin_set(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_set(RX_PIN_NUMBER_2);		
//	memcpy(read_data, write_data, 1024);
//	nrf_gpio_pin_clear(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_clear(RX_PIN_NUMBER_2);	
//	nrf_delay_ms(50);
	
//	nrf_gpio_pin_set(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_set(RX_PIN_NUMBER_2);	
//	i=0;
//	do
//	{
//		i++;
//	}while(i<1024);
//	nrf_gpio_pin_clear(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_clear(RX_PIN_NUMBER_2);	
//	nrf_delay_ms(50);	

//	nrf_gpio_pin_set(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_set(RX_PIN_NUMBER_2);	
//	for(i = 1024;i > 0;i--)
//	{
//	}
//	nrf_gpio_pin_clear(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_clear(RX_PIN_NUMBER_2);	
//	nrf_delay_ms(50);	

//	nrf_gpio_pin_set(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_set(RX_PIN_NUMBER_2);	
//	i=0;
//	do
//	{
//		i++;
//		k=i/j;
//	}while(i<1024);
//	nrf_gpio_pin_clear(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_clear(RX_PIN_NUMBER_2);	
//	nrf_delay_ms(50);

//	nrf_gpio_pin_set(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_set(RX_PIN_NUMBER_2);	
//	i=0;
//	do
//	{
//		i++;
//		p=m/n;
//	}while(i<1024);
//	nrf_gpio_pin_clear(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_clear(RX_PIN_NUMBER_2);	
//	nrf_delay_ms(50);

//	nrf_gpio_pin_set(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_set(RX_PIN_NUMBER_2);	
//	i=0;
//	do
//	{
//		i++;
//		j=j<<6;
//	}while(i<1024);
//	nrf_gpio_pin_clear(TX_PIN_NUMBER_2);
//	nrf_gpio_pin_clear(RX_PIN_NUMBER_2);	
//	nrf_delay_ms(50);
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



