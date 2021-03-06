// Revision record ----------------------------------------------------
/*
	使用外部定时器0，减少内部RTC app_timer的负担
	
	drlTIM_Start
	drlTIM_Stop
	drlTIM_


//void TIMER0_IRQHandler(void)
//{
//	static uint32_t i;
//	
//	i++;
//	NRF_TIMER0->TASKS_CLEAR   		 = 1; 
//	NRF_TIMER0->EVENTS_COMPARE[0]	   = 0;
//	NRF_TIMER0->TASKS_START;
//	
//	nrf_gpio_pin_toggle(17);
//	nrf_gpio_pin_toggle(18);
//}

//void TIMER_0_Init(void)
//{
//    NRF_TIMER0->MODE = 0;		// 计时模式
//	NRF_TIMER0->PRESCALER = 6;	// 不分频
//	NRF_TIMER0->BITMODE = 3;	// 32位宽	
//	NRF_TIMER0->TASKS_CLEAR    = 1; 
//	
//	NRF_TIMER0->CC[0] = (uint32_t)100000;
//	NRF_TIMER0->CC[1] = (uint32_t)100000;
//	NRF_TIMER0->CC[2] = (uint32_t)100000;
//	NRF_TIMER0->CC[3] = (uint32_t)100000;
//	
//    NVIC_SetPriority(TIMER0_IRQn, 1);
//    NVIC_ClearPendingIRQ(TIMER0_IRQn);
//    NVIC_EnableIRQ(TIMER0_IRQn);	
//	
//	NRF_TIMER0->INTENSET = 0x01 << 16;
//	NRF_TIMER0->TASKS_START = 1;
//}	
*/


// Includes -----------------------------------------------------------
#include "timer_0.h"

// Functions ----------------------------------------------------------


// Defines ------------------------------------------------------------
#define TIMER_TICK_MS	10			// 定时器周期


// Globals ------------------------------------------------------------
TIMER0_PATAMETERS_T		TIMER0;

#define 				drTIM_Tmp_TIMING_MS						(1000)
TIMER0_INSTANCE_T		drTIM_Tmp;

// 系统休眠
#define 				drTIM_SysSleep_TIMING_MS				(5000)
TIMER0_INSTANCE_T		drTIM_SysSleep;							

// 低电量报警
#define 				drTIM_LowPwrPrompt_TIMING_MS			(1000)
TIMER0_INSTANCE_T		drTIM_LowPwrPrompt;						

// 显示发送结果（成功/失败）
#define 				drTIM_SendResult_TIMING_MS				(1000)
TIMER0_INSTANCE_T		drTIM_SendResult;						

// LCD显示
#define 				drTIM_LCD_TIMING_MS						(3000)
TIMER0_INSTANCE_T		drTIM_LCD;								

// 程序允许错误提示
#define 				drTIM_ERR_TIMING_MS						(2000)
TIMER0_INSTANCE_T		drTIM_ERR;								

// 自动按键发送压力测试
#define 				drTIM_AutoSend_TIMING_MS				(200)
TIMER0_INSTANCE_T		drTIM_AutoSend;							

// 定时刷新RSSI值
#define 				drTIM_RSSI_TIMING_MS					(1000)
TIMER0_INSTANCE_T		drTIM_RSSI;								

// 按键频率控制
#define 				drTIM_KeyFreqCtrl_TIMING_MS				(300)
TIMER0_INSTANCE_T		drTIM_KeyFreqCtrl;						

// 发送频率限制
#define 				drTIM_SendLimit_TIMING_MS				(300)
TIMER0_INSTANCE_T		drTIM_SendLimit;						

// 读取13.56M中断延时
#define 				drTIM_NFC_TIMING_MS				(500)
TIMER0_INSTANCE_T		drTIM_NFC;	

// 看门狗
#define 				drTIM_WDT_TIMING_MS				(1000)
TIMER0_INSTANCE_T		drTIM_WDT;

// Locals -------------------------------------------------------------
//nrf_drv_rtc_t rtc = NRF_DRV_RTC_INSTANCE(0); 

//static void RTC0_TickHandler(nrf_drv_rtc_int_type_t int_type)
//{
//	nrf_gpio_pin_toggle(17);
//	nrf_gpio_pin_toggle(18);
//	
//	TIMER0.TickCnt++;
//	
//	drTIM_TimeOutCheck(&drTIM_Tmp);
//	drTIM_TimeOutCheck(&drTIM_SysSleep);
//	drTIM_TimeOutCheck(&drTIM_LowPwrPrompt);		
//	drTIM_TimeOutCheck(&drTIM_SendResult);
//	drTIM_TimeOutCheck(&drTIM_LCD);	
//	drTIM_TimeOutCheck(&drTIM_ERR);	
//	drTIM_TimeOutCheck(&drTIM_AutoSend);	
//	drTIM_TimeOutCheck(&drTIM_RSSI);
//	drTIM_TimeOutCheck(&drTIM_KeyFreqCtrl);
//	drTIM_TimeOutCheck(&drTIM_SendLimit);	
//	drTIM_TimeOutCheck(&drTIM_NFC);	
//	drTIM_TimeOutCheck(&drTIM_WDT);	
//}

void drTIM_EventHandler(void)
{

	drTIM_TmpHandler();
	drTIM_SysSleepHandler();
	drTIM_LowPwrPromptHandler();
	drTIM_SendResultHandler();
	drTIM_LCDHandler();
	drTIM_ERRHandler();
	drTIM_AutoSendHandler();
	drTIM_RSSIHandler();
	drTIM_KeyFreqCtrlHandler();
	drTIM_SendLimitHandler();
	drTIM_NFCHandler();

}

// 初始化TickSource
uint32_t RTC0_Init(void)
{
//    uint32_t err_code;
//	
//    //Initialize RTC instance
//	//注：创建的RTC定时周期必须与 TIMER_TICK_MS 定义的相同
//    err_code = nrf_drv_rtc_init(&rtc, NULL, RTC0_TickHandler);
//    APP_ERROR_CHECK(err_code);
//	
//    //Enable tick event & interrupt
//    nrf_drv_rtc_tick_enable(&rtc,true);
//	
//    //Power on RTC instance
////    nrf_drv_rtc_enable(&rtc);
//	drTIM_StartTickSource();
//	return 0;		
}

void drTIM_StartTickSource(void)
{
//	 nrf_drv_rtc_enable(&rtc);	
}

void drTIM_StopTickSource(void)
{
//	 nrf_drv_rtc_disable(&rtc);	
}

void drTIM_Start_2(TIMER0_INSTANCE_T * TimerInstance, uint32_t OutTickCntMs)
{
//	TimerInstance->InitedFlg = true;
//	TimerInstance->TimeOutFlg = false;
//	TimerInstance->TimeOutTickCnt = OutTickCntMs / TIMER_TICK_MS;
//	TimerInstance->StartTickCnt = TIMER0.TickCnt;
}

void drTIM_Stop_2(TIMER0_INSTANCE_T * TimerInstance)
{
//	TimerInstance->InitedFlg = false;
}

void drTIM_TimeOutCheck(TIMER0_INSTANCE_T * TimerInstance)
{
//	if(TimerInstance->InitedFlg)
//	{
//		if((TIMER0.TickCnt - TimerInstance->StartTickCnt) >= TimerInstance->TimeOutTickCnt)
//		{
//			TimerInstance->TimeOutFlg = true;
//			TimerInstance->StartTickCnt = TIMER0.TickCnt;
//		}		
//	}
}


// 用户定时器 ----------------------------------------------------------------
void drTIM_TmpStart(void)
{
//	drTIM_Start_2(&drTIM_Tmp, drTIM_Tmp_TIMING_MS);
}

void drTIM_TmpStop(void)
{
//	drTIM_Stop_2(&drTIM_Tmp);
}

void drTIM_TmpHandler(void)
{
//	if(drTIM_Tmp.TimeOutFlg)
//	{
//		drTIM_Tmp.TimeOutFlg = false;
//		LCD_DisDigitN(5, TIMER0.TickCnt/10, 6);
//	}
}

void drTIM_SysSleepStart(void)
{
//	#if SYS_NO_SLEEP_DEBUG
//	drTIM_Start_2(&drTIM_SysSleep, drTIM_SysSleep_TIMING_MS);
//	#endif
}

void drTIM_SysSleepStop(void)
{
//	#if SYS_NO_SLEEP_DEBUG
//	drTIM_Stop_2(&drTIM_SysSleep);
//	#endif
}

void drTIM_SysSleepHandler(void)
{
//	#if SYS_NO_SLEEP_DEBUG
//	if(drTIM_SysSleep.TimeOutFlg)
//	{
//		drTIM_SysSleep.TimeOutFlg = false;
//		
//		POWER_SysOnToSleep();
//	}	
//	#endif
}

void drTIM_LowPwrPromptStart(void)
{
//	drTIM_Start_2(&drTIM_LowPwrPrompt, drTIM_LowPwrPrompt_TIMING_MS);
}

void drTIM_LowPwrPromptStop(void)
{
//	drTIM_Stop_2(&drTIM_LowPwrPrompt);
}

void drTIM_LowPwrPromptHandler(void)
{
//	static bool	TmpFlg = false;
//	
//	if(drTIM_LowPwrPrompt.TimeOutFlg)
//	{
//		drTIM_LowPwrPrompt.TimeOutFlg = false;
//		
//		if(TmpFlg)
//		{
//			TmpFlg = false;
//			LCD_DisplayBattery(BATTERY_LEVEL_OFF);
//		}
//		else
//		{
//			TmpFlg = true;
//			LCD_DisplayBattery(BATTERY_LEVEL_0);	
//		}		
//	}	
}


void drTIM_SendResultStart(void)
{
//	drTIM_Start_2(&drTIM_SendResult, drTIM_SendResult_TIMING_MS);
}

void drTIM_SendResultStop(void)
{
//	drTIM_Stop_2(&drTIM_SendResult);
}

void drTIM_SendResultHandler(void)
{
//	if(drTIM_SendResult.TimeOutFlg)
//	{
//		drTIM_SendResult.TimeOutFlg = false;
//		
//		LCD.DATA.SendResultState = SEND_RESULT_CLEAR;
//		LCD.DATA.RefreshFlg |= LCD_REFRESH_RESULT;
//	}	
}

void drTIM_LCDStart(void)
{
//	drTIM_Start_2(&drTIM_LCD, drTIM_LCD_TIMING_MS);
}

void drTIM_LCDStop(void)
{
//	drTIM_Stop_2(&drTIM_LCD);
}


void drTIM_LCDHandler(void)
{
//	if(drTIM_LCD.TimeOutFlg)
//	{
//		drTIM_LCD.TimeOutFlg = false;
//		
//		drTIM_LCDStop();
//		LCD.DATA.RefreshFlg |= LCD_REFRESH_SCENE;
//	}	
}

void drTIM_ERRStart(void)
{
//	drTIM_Start_2(&drTIM_ERR, drTIM_ERR_TIMING_MS);
}

void drTIM_ERRStop(void)
{
//	drTIM_Stop_2(&drTIM_ERR);
}


void drTIM_ERRHandler(void)
{
//	if(drTIM_ERR.TimeOutFlg)
//	{
//		drTIM_ERR.TimeOutFlg = false;
//		
//		drERR.HintFlg = true;
//	}	
}

void drTIM_AutoSendStart(void)
{
//	drTIM_Start_2(&drTIM_AutoSend, drTIM_AutoSend_TIMING_MS);
}

void drTIM_AutoSendStop(void)
{
//	drTIM_Stop_2(&drTIM_AutoSend);
}

void drTIM_AutoSendHandler(void)
{
//	if(drTIM_AutoSend.TimeOutFlg)
//	{
//		drTIM_AutoSend.TimeOutFlg = false;
//		
//		KEY.ScanDownFlg = true;
//		KEY.ScanValue = KEY_APP_A_1;
//	}	
}

void drTIM_RSSIStart(void)
{
//	drTIM_Start_2(&drTIM_RSSI, drTIM_RSSI_TIMING_MS);
}

void drTIM_RSSIStop(void)
{
//	drTIM_Stop_2(&drTIM_RSSI);
}

void drTIM_RSSIHandler(void)
{
//	if(drTIM_RSSI.TimeOutFlg)
//	{
//		drTIM_RSSI.TimeOutFlg = false;
//		
//		LCD.DATA.RefreshFlg |= LCD_REFRESH_SIGNAL;
//	}	
}



void drTIM_KeyFreqCtrlStart(void)
{
//	drTIM_Start_2(&drTIM_KeyFreqCtrl, drTIM_KeyFreqCtrl_TIMING_MS);
}

void drTIM_KeyFreqCtrlStop(void)
{
//	drTIM_Stop_2(&drTIM_KeyFreqCtrl);
}

void drTIM_KeyFreqCtrlHandler(void)
{
//	if(drTIM_KeyFreqCtrl.TimeOutFlg)
//	{
//		drTIM_KeyFreqCtrl.TimeOutFlg = false;
//		
//		drTIM_KeyFreqCtrlStop();
//		APP.KeyCntLimitFlg = false;
//	}	
}

void drTIM_SendLimitStart(void)
{
//	drTIM_Start_2(&drTIM_SendLimit, drTIM_SendLimit_TIMING_MS);
}

void drTIM_SendLimitStop(void)
{
//	drTIM_Stop_2(&drTIM_SendLimit);
}

void drTIM_SendLimitHandler(void)
{
//	if(drTIM_SendLimit.TimeOutFlg)
//	{
//		drTIM_SendLimit.TimeOutFlg = false;
//		
//		drTIM_SendLimitStop();
//		APP.QUE.KeySendLimitFlg = false;
//	}	
}

void drTIM_NFCStart(void)
{
//	drTIM_Start_2(&drTIM_NFC, drTIM_NFC_TIMING_MS);
}

void drTIM_NFCStop(void)
{
//	drTIM_Stop_2(&drTIM_NFC);
}

void drTIM_NFCHandler(void)
{
//	if(drTIM_NFC.TimeOutFlg)
//	{
//		drTIM_NFC.TimeOutFlg = false;
//		drTIM_NFCStop();
//		
//		APP.NRFUpdataFlg = true;		
//	}	
}









 
 

 
 
