#include "power.h"


POWER_PARAMETERS_T		POWER;

uint32_t POWER_Init(void)
{
	//结构体参数初始化
	POWER.SysState = SYS_ON;
	
	POWER_DCDCEnable();
	
	return drERROR_SUCCESS;
}

// 51822深度休眠
void POWER_SysPowerOff(void)
{
	GPIO_Default();							//关机前GPIO配置为高阻态，防止其他按键唤醒系统
	nrf_gpio_cfg_sense_input(KEY_PWR, NRF_GPIO_PIN_NOPULL, NRF_GPIO_PIN_SENSE_LOW);			
	NRF_POWER->SYSTEMOFF = 1;				//进入休眠模式	
}

//关机函数
void POWER_SysOnToOff(void)
{
	POWER.SysState = SYS_OFF;			//切换系统状态
	
	RADIO_Sleep();						//停止RADIO外设				
					
	LCD_Sleep();						//关闭LCD显示
	
	CLOCK_HFCLKStop();					//停止外部时钟
	
}

//系统休眠函数
void POWER_SysOnToSleep(void)
{
	POWER.SysState = SYS_SLEEP;
	
	CLOCK_HFCLKStop();
	
	RADIO_Sleep();
	
	TIMER_ADCStop();
	
	drTIMER_RSSIStop();
	
	LCD_Sleep();
}

//开机
void POWER_SysOffToOn(void)
{
	NVIC_SystemReset();				//复位
}

//唤醒
void POWER_SysSleepToOn(void)
{
	POWER.SysState = SYS_ON;
	
	CLOCK_HFCLKStart();
	
	RADIO_WakeUp();
	
	TIMER_ADCStart();

	drTIMER_SysSleepStart(drTIMER_PERIOD_SysSleep);
	
	drTIMER_RSSIStart(drTIMER_PERIOD_RSSI);
	
	LCD_WakeUp();
}

//进入系统测试状态
void POWER_SysOnToTest(void)
{
	uint8_t LcdTest[] = {0xC9,0xEE,0xDB,0xDA,0xD6,0xD0,0xBF,0xC6,0xD1,0xB6,0xC1,0xAA,0xBF,0xC6,0xBC,0xBC,
						 0xB9,0xC9,0xB7,0xDD,0xD3,0xD0,0xCF,0xDE,0xB9,0xAB,0xCB,0xBE,0x7A,0x6B,0x78,0x6C,
						 0xC6,0xC1,0xC4,0xBB,0xCF,0xD4,0xCA,0xBE,0xB2,0xE2,0xCA,0xD4,0x31,0x32,0x33,0x34,
						 0x61,0x41,0x62,0x42,0x63,0x43,0x64,0x44,0x7E,0x21,0x40,0x23,0x24,0x25,0x5E,0x26};	
	
	POWER.SysState = SYS_TEST;
	
	drTIMER_SysSleepStop();
	
	TEST.RxRssi = 0;
	TEST.TxRssi = 0;
						 
	LCD_DRV_DisplayN(0, 64, LcdTest);
	
	for(uint32_t i = 0;i<5;i++)
	{
		nrf_delay_ms(500);	
		nrf_drv_wdt_feed();			// 延时时间过长，定时喂狗，防止看门狗重启
	}

	LCD_ClearScreen();	
	nrf_delay_ms(300);	
	
	LCD.DATA.RefreshFlg |= LCD_REFRESH_STUDEN_ID;
}


void POWER_SysOnToMatch(void)
{
	POWER.SysState = SYS_MATCH;

	drTIMER_SysSleepStop();			// 配对模式下，答题器30秒不休眠
	
	RADIO.IM.RxChannal = NRF_MATCH_RX_CHANNEL;		// 接收频点设置为配对频点
	
	// 索引重置为0，并显示索引为0的PIN码值
	MATCH.SelectIndex = 0;
	MATCH_LCDDisplayPIN(MATCH.SelectIndex);	
	
	// 清除LCD多余显示信息
	LCD_DisplayJudge(JUDGE_CLEAR);

}

void POWER_SysMatchToOn(void)
{
	POWER.SysState = SYS_ON;
	
	drTIMER_SysSleepStart(drTIMER_PERIOD_SysSleep);
	
	RADIO.IM.RxChannal = RADIO.MATCH.RxChannal;		// 接收频点设置为答题频点

	
}

void POWER_DCDCEnable(void)
{
	NRF_POWER->DCDCEN = 1;
}

void POWER_DCDCDisable(void)
{
	NRF_POWER->DCDCEN = 0;
}





