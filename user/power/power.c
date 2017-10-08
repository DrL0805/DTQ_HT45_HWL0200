#include "power.h"


POWER_PARAMETERS_T		POWER;

void POWER_Init(void)
{
	//结构体参数初始化
	POWER.SysState = SYS_ON;
	
	POWER_DCDCEnable();
}

//关机函数
void POWER_SysOnToOff(void)
{
	POWER.SysState = SYS_OFF;			//切换系统状态
	
	RADIO_Sleep();						//停止RADIO外设				
	
	LCD_ClearScreen();					
	LCD_Sleep();						//关闭LCD显示
	
	CLOCK_HFCLKStop();					//停止外部时钟
	
	APP_ClearQuestionInfo();			//清空所有题目信息
}

//系统休眠函数
void POWER_SysOnToSleep(void)
{
	POWER.SysState = SYS_SLEEP;
	
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
	
	CLOCK_HFCLKStart();
	
	RADIO_WakeUp();
	
	TIMER_ADCStart();
	
	TIMER_SysStateStart();				//30S休眠定时器开启
	
	LCD_WakeUp();
}

//进入系统测试状态
void POWER_SysOnToTest(void)
{
	POWER.SysState = SYS_TEST;
	
	TIMER_SysStateStop();			//测试模式下，答题器30秒不休眠
	
	TEST.LcdLetterVal = 0;
	TEST.RxRssi = 0;
	TEST.TxRssi = 0;
}


void POWER_SysOnToMatch(void)
{
	POWER.SysState = SYS_MATCH;
	TIMER_SysStateStop();							// 配对模式下，答题器30秒不休眠
	
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
	TIMER_SysStateStart();							// 重新开启30秒休眠定时器	
	
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





