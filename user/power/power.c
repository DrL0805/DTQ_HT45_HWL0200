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
	
	drTIM_StopTickSource();
	
	CLOCK_HFCLKStop();
	
	RADIO_Sleep();
	
	TIMER_ADCStop();	
	
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
	
	drTIM_StartTickSource();
	
	CLOCK_HFCLKStart();
	
	RADIO_WakeUp();
	
	TIMER_ADCStart();
	
//	TIMER_SysStateStop();				//30S休眠定时器开启
//	TIMER_SysStateStart();				//30S休眠定时器开启
//	drTIM_Stop_2(&drTIM_SysSleep);
//	drTIM_Start_2(&drTIM_SysSleep, 50);
	drTIM_SysSleepStart();
	drTIMER_SysSleepStart(drTIMER_PERIOD_SysSleep);
	
	LCD_WakeUp();
}

//进入系统测试状态
void POWER_SysOnToTest(void)
{
	POWER.SysState = SYS_TEST;
	
	drTIM_SysSleepStop();			//测试模式下，答题器30秒不休眠
	drTIMER_SysSleepStop();
	
	TEST.RxRssi = 0;
	TEST.TxRssi = 0;
	
//	for(uint8_t i = 0;i < 2;i++)
//	{
//		LCD_DisplayAll();
//		nrf_delay_ms(1000);
//		LCD_ClearScreen();
//		nrf_delay_ms(1000);		
//	}	
	for(uint8_t i = 0;i < 64;i += 2)
	{
		LCD_DRV_DisplayOne(i,LCD_DRV_DOT_HANZI,0xBBD8);
	}
	nrf_delay_ms(2000);	
	LCD_ClearScreen();	
	nrf_delay_ms(300);	
	
	LCD.DATA.RefreshFlg |= LCD_REFRESH_STUDEN_ID;
}


void POWER_SysOnToMatch(void)
{
	POWER.SysState = SYS_MATCH;
//	TIMER_SysStateStop();							// 配对模式下，答题器30秒不休眠
//	drTIM_Stop_2(&drTIM_SysSleep);
	drTIM_SysSleepStop();
	drTIMER_SysSleepStop();
	
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
//	TIMER_SysStateStart();							// 重新开启30秒休眠定时器	
//	drTIM_Start_2(&drTIM_SysSleep, 50);
	drTIM_SysSleepStart();
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





