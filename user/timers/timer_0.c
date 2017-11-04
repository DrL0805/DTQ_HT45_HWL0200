// Revision record ----------------------------------------------------
/*
	使用外部定时器0，减少内部RTC app_timer的负担
	
	drlTIM_Start
	drlTIM_Stop
	drlTIM_
	
	
*/


// Includes -----------------------------------------------------------
#include "timer_0.h"

// Functions ----------------------------------------------------------


// Defines ------------------------------------------------------------
#define TIMER_TICK_MS	100			// 定时器周期


// Globals ------------------------------------------------------------
TIMER0_PATAMETERS_T		TIMER0;

TIMER0_INSTANCE_T		drTIM_Tmp;
TIMER0_INSTANCE_T		drTIM_SysSleep;				// 系统休眠
TIMER0_INSTANCE_T		drTIM_LowPwrPrompt;			// 低电量报警
TIMER0_INSTANCE_T		drTIM_SendResult;			// 显示发送结果（成功/失败）
TIMER0_INSTANCE_T		drTIM_LCD;					// LCD显示
TIMER0_INSTANCE_T		drTIM_ERR;					// 程序允许错误提示
TIMER0_INSTANCE_T		drTIM_AutoSend;				// 自动按键发送压力测试
TIMER0_INSTANCE_T		drTIM_RSSI;					// 定时刷新RSSI值
TIMER0_INSTANCE_T		drTIM_KeyFreqCtrl;			// 按键频率控制
TIMER0_INSTANCE_T		drTIM_SendLimit;			// 发送频率限制


// Locals -------------------------------------------------------------
nrf_drv_timer_t TIMER_PUBLIC = NRF_DRV_TIMER_INSTANCE(0);				// 公共定时器



void timer_public_event_handler(nrf_timer_event_t event_type, void* p_context)
{
    switch(event_type)
    {
        case NRF_TIMER_EVENT_COMPARE0:
			TIMER0.TickCnt++;
		
			drTIMER_TimeOutCheck(&drTIM_Tmp);
			drTIMER_TimeOutCheck(&drTIM_SysSleep);
			drTIMER_TimeOutCheck(&drTIM_LowPwrPrompt);		
			drTIMER_TimeOutCheck(&drTIM_SendResult);
			drTIMER_TimeOutCheck(&drTIM_LCD);	
			drTIMER_TimeOutCheck(&drTIM_ERR);	
			drTIMER_TimeOutCheck(&drTIM_AutoSend);	
			drTIMER_TimeOutCheck(&drTIM_RSSI);
			drTIMER_TimeOutCheck(&drTIM_KeyFreqCtrl);
			drTIMER_TimeOutCheck(&drTIM_SendLimit);
		
            break;
        default:
            //Do nothing.
            break;
    }    
}


void drTIMER_Start(TIMER0_INSTANCE_T * TimerInstance, uint32_t OutTickCnt)
{
	TimerInstance->InitedFlg = true;
	TimerInstance->TimeOutFlg = false;
	TimerInstance->TimeOutTickCnt = OutTickCnt;
	TimerInstance->StartTickCnt = TIMER0.TickCnt;
}

void drTIMER_Stop(TIMER0_INSTANCE_T * TimerInstance)
{
	TimerInstance->InitedFlg = false;
}

void drTIMER_TimeOutCheck(TIMER0_INSTANCE_T * TimerInstance)
{
	if(TimerInstance->InitedFlg)
	{
		if((TIMER0.TickCnt - TimerInstance->StartTickCnt) >= TimerInstance->TimeOutTickCnt)
		{
			TimerInstance->TimeOutFlg = true;
			TimerInstance->StartTickCnt = TIMER0.TickCnt;
		}		
	}
}

uint32_t TIMER0_Init(void)
{
	uint32_t err_code, time_ticks;
	
	// TIMER0初始化
    err_code = nrf_drv_timer_init(&TIMER_PUBLIC, NULL, timer_public_event_handler);
    drERROR_CHECK(drERROR_TIMER0_BASE_NUM+err_code);
	
	// 计算tick数
    time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER_PUBLIC, TIMER_TICK_MS);
	
	// 
    nrf_drv_timer_extended_compare(
         &TIMER_PUBLIC, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);
    
	// 使能定时器
	nrf_drv_timer_enable(&TIMER_PUBLIC);	
		
	return drERROR_SUCCESS;
}


void drTIMER_EventHandler(void)
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
}




// 用户定时器 ----------------------------------------------------------------
void drTIM_TmpStart(void)
{
	drTIMER_Start(&drTIM_Tmp, 10);
}

void drTIM_TmpStop(void)
{
	drTIMER_Stop(&drTIM_Tmp);
}

void drTIM_TmpHandler(void)
{
	if(drTIM_Tmp.TimeOutFlg)
	{
		drTIM_Tmp.TimeOutFlg = false;
		LCD_DisDigitN(5, TIMER0.TickCnt/10, 6);
	}
}

void drTIM_SysSleepStart(void)
{
	#if SYS_NO_SLEEP_DEBUG
	drTIMER_Start(&drTIM_SysSleep, 50);
	#endif
}

void drTIM_SysSleepStop(void)
{
	#if SYS_NO_SLEEP_DEBUG
	drTIMER_Stop(&drTIM_SysSleep);
	#endif
}

void drTIM_SysSleepHandler(void)
{
	#if SYS_NO_SLEEP_DEBUG
	if(drTIM_SysSleep.TimeOutFlg)
	{
		drTIM_SysSleep.TimeOutFlg = false;
		
		POWER_SysOnToSleep();
	}	
	#endif
}

void drTIM_LowPwrPromptStart(void)
{
	drTIMER_Start(&drTIM_LowPwrPrompt, 10);
}

void drTIM_LowPwrPromptStop(void)
{
	drTIMER_Stop(&drTIM_LowPwrPrompt);
}

void drTIM_LowPwrPromptHandler(void)
{
	static bool	TmpFlg = false;
	
	if(drTIM_LowPwrPrompt.TimeOutFlg)
	{
		drTIM_LowPwrPrompt.TimeOutFlg = false;
		
		if(TmpFlg)
		{
			TmpFlg = false;
			LCD_DisplayBattery(BATTERY_LEVEL_OFF);
		}
		else
		{
			TmpFlg = true;
			LCD_DisplayBattery(BATTERY_LEVEL_0);	
		}		
	}	
}


void drTIM_SendResultStart(void)
{
	drTIMER_Start(&drTIM_SendResult, 10);
}

void drTIM_SendResultStop(void)
{
	drTIMER_Stop(&drTIM_SendResult);
}

void drTIM_SendResultHandler(void)
{
//	static bool	TmpFlg = false;
	
	if(drTIM_SendResult.TimeOutFlg)
	{
		drTIM_SendResult.TimeOutFlg = false;
		
		LCD.DATA.SendResultState = SEND_RESULT_CLEAR;
		LCD.DATA.RefreshFlg |= LCD_REFRESH_RESULT;
	}	
}

void drTIM_LCDStart(void)
{
	drTIMER_Start(&drTIM_LCD, 30);
}

void drTIM_LCDStop(void)
{
	drTIMER_Stop(&drTIM_LCD);
}


void drTIM_LCDHandler(void)
{
//	static bool	TmpFlg = false;
	
	if(drTIM_LCD.TimeOutFlg)
	{
		drTIM_LCD.TimeOutFlg = false;
		
		drTIM_LCDStop();
		LCD.DATA.RefreshFlg |= LCD_REFRESH_SCENE;
	}	
}

void drTIM_ERRStart(void)
{
	drTIMER_Start(&drTIM_ERR, 20);
}

void drTIM_ERRStop(void)
{
	drTIMER_Stop(&drTIM_ERR);
}


void drTIM_ERRHandler(void)
{
//	static bool	TmpFlg = false;
	
	if(drTIM_ERR.TimeOutFlg)
	{
		drTIM_ERR.TimeOutFlg = false;
		
		ERR.HintFlg = true;
	}	
}

void drTIM_AutoSendStart(void)
{
	drTIMER_Start(&drTIM_AutoSend, 2);
}

void drTIM_AutoSendStop(void)
{
	drTIMER_Stop(&drTIM_AutoSend);
}

void drTIM_AutoSendHandler(void)
{
//	static bool	TmpFlg = false;
	
	if(drTIM_AutoSend.TimeOutFlg)
	{
		drTIM_AutoSend.TimeOutFlg = false;
		
		KEY.ScanDownFlg = true;
		KEY.ScanValue = KEY_APP_A_1;
	}	
}

void drTIM_RSSIStart(void)
{
	drTIMER_Start(&drTIM_RSSI, 3);
}

void drTIM_RSSIStop(void)
{
	drTIMER_Stop(&drTIM_RSSI);
}

void drTIM_RSSIHandler(void)
{
//	static bool	TmpFlg = false;
	
	if(drTIM_RSSI.TimeOutFlg)
	{
		drTIM_RSSI.TimeOutFlg = false;
		
		LCD.DATA.RefreshFlg |= LCD_REFRESH_SIGNAL;
	}	
}



void drTIM_KeyFreqCtrlStart(void)
{
	drTIMER_Start(&drTIM_KeyFreqCtrl, 3);
}

void drTIM_KeyFreqCtrlStop(void)
{
	drTIMER_Stop(&drTIM_KeyFreqCtrl);
}

void drTIM_KeyFreqCtrlHandler(void)
{
//	static bool	TmpFlg = false;
	
	if(drTIM_KeyFreqCtrl.TimeOutFlg)
	{
		drTIM_KeyFreqCtrl.TimeOutFlg = false;
		
		drTIM_KeyFreqCtrlStop();
		APP.KeyCntLimitFlg = false;
	}	
}

void drTIM_SendLimitStart(void)
{
	drTIMER_Start(&drTIM_SendLimit, 3);
}

void drTIM_SendLimitStop(void)
{
	drTIMER_Stop(&drTIM_SendLimit);
}

void drTIM_SendLimitHandler(void)
{
//	static bool	TmpFlg = false;
	
	if(drTIM_SendLimit.TimeOutFlg)
	{
		drTIM_SendLimit.TimeOutFlg = false;
		
		drTIM_SendLimitStop();
		APP.QUE.KeySendLimitFlg = false;
	}	
}











 
 

 
 
