// Revision record ----------------------------------------------------

// Includes -----------------------------------------------------------
#include "drl_timer.h"

// Functions ----------------------------------------------------------
static uint32_t drTIMER_TickScheduler(void);
static uint32_t drTIMER_TickSourceInit(void);
static uint32_t drTIMER_TickParametersInit(void);

// Globals ------------------------------------------------------------

// 定时器链表的头
drTIM_HEAD_PATAMETERS_T			drTIMER_HEAD;					
drTIM_HEAD_PATAMETERS_T*		pdrTIMER_HEAD = &drTIMER_HEAD;

// 用户定义的定时器结构体
drTIM_TIMER_PARAMETERS_T		drTIMER_TEST;
drTIM_TIMER_PARAMETERS_T		drTIMER_PUBLIC;

drTIM_TIMER_PARAMETERS_T		drTIMER_SysSleep;			// 系统休眠						
drTIM_TIMER_PARAMETERS_T		drTIMER_LowPwrPrompt;		// 低电量报警				
drTIM_TIMER_PARAMETERS_T		drTIMER_SendResult;			// 显示发送结果（成功/失败）			
drTIM_TIMER_PARAMETERS_T		drTIMER_LCD;				// LCD显示				
drTIM_TIMER_PARAMETERS_T		drTIMER_ERR;				// 程序允许错误提示				
drTIM_TIMER_PARAMETERS_T		drTIMER_AutoSend;			// 自动按键发送压力测试			
drTIM_TIMER_PARAMETERS_T		drTIMER_RSSI;				// 定时刷新RSSI值				
drTIM_TIMER_PARAMETERS_T		drTIMER_KeyFreqCtrl;		// 按键频率控制				
drTIM_TIMER_PARAMETERS_T		drTIMER_SendLimit;			// 发送频率限制			
drTIM_TIMER_PARAMETERS_T		drTIMER_NFC;				// 读取13.56M中断延时
drTIM_TIMER_PARAMETERS_T		drTIMER_WDT;				// 看门狗喂狗定时器
drTIM_TIMER_PARAMETERS_T		drTIMER_KEY;				// 按键驱动定时器
drTIM_TIMER_PARAMETERS_T		drTIMER_TxOvertime;			// 发送超时定时
drTIM_TIMER_PARAMETERS_T		drTIMER_ADC;				// 电池电量ADC采集定时器
drTIM_TIMER_PARAMETERS_T		drTIMER_RetainKey;			// 记住按键值，当收到题目时自动发送



// Locals -------------------------------------------------------------

uint32_t drTIMER_Init(void)
{	
    uint32_t err_code;
	
	// 创建tick源
	drTIMER_TickSourceInit();
	
	// 初始tick参数
	drTIMER_TickParametersInit();
	
	// 创建用户定时器
	drTIMER_CreateTimer(&drTIMER_TEST, drTIMER_TestHandler);
	drTIMER_CreateTimer(&drTIMER_PUBLIC, drTIMER_PublicHandler);
	
	drTIMER_CreateTimer(&drTIMER_SysSleep, drTIMER_SysSleepHandler);
	drTIMER_CreateTimer(&drTIMER_LowPwrPrompt, drTIMER_LowPwrPromptHandler);
	drTIMER_CreateTimer(&drTIMER_SendResult, drTIMER_SendResultHandler);
	drTIMER_CreateTimer(&drTIMER_LCD, drTIMER_LCDHandler);
	drTIMER_CreateTimer(&drTIMER_ERR, drTIMER_ERRHandler);
	drTIMER_CreateTimer(&drTIMER_AutoSend, drTIMER_AutoSendHandler);
	drTIMER_CreateTimer(&drTIMER_RSSI, drTIMER_RSSIHandler);
	drTIMER_CreateTimer(&drTIMER_KeyFreqCtrl, drTIMER_KeyFreqCtrlHandler);
	drTIMER_CreateTimer(&drTIMER_SendLimit, drTIMER_SendLimitHandler);
	drTIMER_CreateTimer(&drTIMER_NFC, drTIMER_NFCHandler);
	drTIMER_CreateTimer(&drTIMER_WDT, drTIMER_WDTHandler);
	drTIMER_CreateTimer(&drTIMER_KEY, drTIMER_KEYHandler);
	drTIMER_CreateTimer(&drTIMER_TxOvertime, drTIMER_TxOvertimeHandler);
	drTIMER_CreateTimer(&drTIMER_RetainKey, drTIMER_RetainKeyHandler);
	return 0;	
}

// 定时器超时检测并处理函数
void drTIMER_EventHandler(void)
{
	drTIMER_SysSleepEventHandler();
	drTIMER_LowPwrPromptEventHandler();
	drTIMER_SendResultEventHandler();
	drTIMER_LCDHandEventler();
	drTIMER_ERREventHandler();
	drTIMER_AutoSendEventHandler();
	drTIMER_RSSIEventHandler();
	drTIMER_KeyFreqCtrlEventHandler();
	drTIMER_SendLimitEventHandler();
	drTIMER_NFCEventHandler();
	drTIMER_WDTEventHandler();
	drTIMER_KEYEventHandler();	
	drTIMER_TxOvertimeEventHandler();	
	drTIMER_RetainKeyEventHandler();	
	
}


uint32_t drTIMER_CreateTimer(drTIM_TIMER_PARAMETERS_T* pTIMER, void (*pTimerOutHandler)(void))
{
	// 设定新定时器pTIMER参数
	pTIMER->TimeOutFlg = false;
	pTIMER->State = drTIM_UNINITIALIZED;
	pTIMER->RemainTickVal = drTIMER_MAX_OUT_VALUE;
	pTIMER->TotalTickVal = drTIMER_MAX_OUT_VALUE;
	pTIMER->TimerOutHandler = pTimerOutHandler;
	
	// 在头结点之后插入新节点
	pTIMER->pNext = pdrTIMER_HEAD->pNext;
	pdrTIMER_HEAD->pNext = pTIMER;
	
	return 0;
}

uint32_t drTIMER_Start(drTIM_TIMER_PARAMETERS_T* pTIMER, uint32_t OutTickVal)
{
	// 初始化定时器参数
	pTIMER->State = drTIM_INITIALIZED;
	pTIMER->TotalTickVal = OutTickVal;
	pTIMER->RemainTickVal = OutTickVal;
	
	// 开始一次定时器调度
	drTIMER_TickScheduler();
	
	return 0;
}

uint32_t drTIMER_Stop(drTIM_TIMER_PARAMETERS_T* pTIMER)
{
	pTIMER->State = drTIM_UNINITIALIZED;
	
	return 0;
}

uint32_t drTIM_Suspend(drTIM_TIMER_PARAMETERS_T* pTIMER)
{
	pTIMER->State = drTIM_SUSPEND;
	
	return 0;	
}

void RTC0_IRQHandler(void)
{
	drTIMER_TickScheduler();
}

static uint32_t drTIMER_TickScheduler(void)
{
	uint32_t NextTickVal = drTIMER_MAX_OUT_VALUE;			// 下一个定时器超时所需tick		
	uint32_t CurCount;				
	drTIM_TIMER_PARAMETERS_T* pNextTimer = pdrTIMER_HEAD->pNext;
	
	CurCount = NRF_RTC0->COUNTER;			// 获取当前tick值
	
	NRF_RTC0->TASKS_CLEAR = 1;				// 清COUNTER值，从零开始计数	
	NRF_RTC0->EVENTS_TICK = 0;				// EVENT触发后一定要清空，否则会一直触发EVENT事件
	NRF_RTC0->EVENTS_COMPARE[0] = 0;		// EVENT触发后一定要清空，否则会一直触发EVENT事件		
	
	while(NULL != pNextTimer)	// 遍历整个定时链表
	{
		switch(pNextTimer->State)
		{
			case drTIM_UNINITIALIZED:
				break;
			case drTIM_INITIALIZED:
				pNextTimer->State = drTIM_RUNNING;
				pNextTimer->RemainTickVal = pNextTimer->TotalTickVal;
				NextTickVal = drMIN(NextTickVal, pNextTimer->RemainTickVal);
				break;
			case drTIM_RUNNING:
				if(CurCount >= pNextTimer->RemainTickVal)
				{
					// 触发定时器超时函数
					pNextTimer->TimerOutHandler();	
					
					// 重置定时器超时值
					pNextTimer->RemainTickVal = pNextTimer->TotalTickVal;
				}
				else
				{
					// 重新计算下次超时所需tick数
					pNextTimer->RemainTickVal = pNextTimer->RemainTickVal - CurCount;
				}
				NextTickVal = drMIN(NextTickVal, pNextTimer->RemainTickVal);
				break;
			case drTIM_SUSPEND:
				break;
			default:
				break;
		}
		
		pNextTimer = pNextTimer->pNext;
	}

	NRF_RTC0->CC[0] = NextTickVal;		
	
	return 0;
}

// TICK源初始化
static uint32_t drTIMER_TickSourceInit(void)
{
	
	NRF_RTC0->PRESCALER = drTIEMR_PRESCALER;	// fRTC [kHz] = 32.768 / (PRESCALER + 1 )
												// PRESCALER = 32：约1ms的TICK，COUNTER++，实际上是1.007ms
												// PRESCALER = 0：约30.517us
	
	NRF_RTC0->TASKS_CLEAR = 1;
	NRF_RTC0->CC[0] = drTIMER_MAX_OUT_VALUE;
	
//	NRF_RTC0->EVTENSET |= 0x01 << 0;				// 使能TICK中断
//	NRF_RTC0->INTENSET |= 0x01 << 0;
	NRF_RTC0->EVTENSET |= 0x01 << 16;				// 使能COMPARE0中断
	NRF_RTC0->INTENSET |= 0x01 << 16;
	
	NVIC_ClearPendingIRQ(RTC0_IRQn);
    NVIC_SetPriority(RTC0_IRQn, 1);
    NVIC_EnableIRQ(RTC0_IRQn);		
	
	NRF_RTC0->TASKS_START = 1;			// 开始运行RTC0定时器		
	
	return 0;
}

// TICK参数初始化
static uint32_t drTIMER_TickParametersInit(void)
{
	drTIMER_HEAD.TickRunningFlg = true;
	drTIMER_HEAD.CurVal = 0;
	
	drTIMER_HEAD.pNext = NULL;
	
	return 0;
}

// 测试定时器 -----------------------------------------------------------
void drTIMER_TestStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_TEST, OutTick);
}

void drTIMER_TestStop(void)
{
	drTIMER_Stop(&drTIMER_TEST);
}

void drTIMER_TestHandler(void)
{
	__NOP();
}

// 公共定时器 -----------------------------------------------------------
void drTIMER_PublicStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_PUBLIC, OutTick);
}

void drTIMER_PublicStop(void)
{
	drTIMER_Stop(&drTIMER_PUBLIC);
}

void drTIMER_PublicHandler(void)
{
//	drTIMER_TestStop();
	__NOP();
}

// 系统休眠定时器 --------------------------------------------------
void drTIMER_SysSleepStart(uint32_t OutTick)
{
	#if !SYS_NO_SLEEP_DEBUG
	drTIMER_Start(&drTIMER_SysSleep, OutTick);
	#endif
}

void drTIMER_SysSleepStop(void)
{
	#if !SYS_NO_SLEEP_DEBUG
	drTIMER_Stop(&drTIMER_SysSleep);
	#endif
}

void drTIMER_SysSleepHandler(void)
{
	#if !SYS_NO_SLEEP_DEBUG
	drTIMER_SysSleep.TimeOutFlg = true;
	#endif
}

void drTIMER_SysSleepEventHandler(void)
{
	if(drCMN_BoolFlgCheck(&drTIMER_SysSleep.TimeOutFlg))
	{
		drTIMER_SysSleepStop();
		
		POWER_SysOnToSleep();
	}
}

// 低电量报警定时器 --------------------------------------------------
void drTIMER_LowPwrPromptStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_LowPwrPrompt, OutTick);
}

void drTIMER_LowPwrPromptStop(void)
{
	drTIMER_Stop(&drTIMER_LowPwrPrompt);
}

void drTIMER_LowPwrPromptHandler(void)
{
	drTIMER_LowPwrPrompt.TimeOutFlg = true;
}

void drTIMER_LowPwrPromptEventHandler(void)
{
	static bool	TmpFlg = false;	
	
	if(drCMN_BoolFlgCheck(&drTIMER_LowPwrPrompt.TimeOutFlg))
	{
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

// 发送结果显示定时器 --------------------------------------------
void drTIMER_SendResultStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_SendResult, OutTick);
}

void drTIMER_SendResultStop(void)
{
	drTIMER_Stop(&drTIMER_SendResult);
}

void drTIMER_SendResultHandler(void)
{
	drTIMER_SendResult.TimeOutFlg = true;
}

void drTIMER_SendResultEventHandler(void)
{
	if(drCMN_BoolFlgCheck(&drTIMER_LowPwrPrompt.TimeOutFlg))
	{
		drTIMER_SendResultStop();
		
		LCD.DATA.SendResultState = SEND_RESULT_CLEAR;
		LCD.DATA.RefreshFlg |= LCD_REFRESH_RESULT;		
	}
}

// LCD临时显示定时器 ----------------------------------------------------
void drTIMER_LCDStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_LCD, OutTick);
}

void drTIMER_LCDStop(void)
{
	drTIMER_Stop(&drTIMER_LCD);
}

void drTIMER_LCDHandler(void)
{
	drTIMER_LCD.TimeOutFlg = true;
}

void drTIMER_LCDHandEventler(void)
{
	if(drCMN_BoolFlgCheck(&drTIMER_LCD.TimeOutFlg))
	{
		drTIMER_LCDStop();
		
		LCD.DATA.RefreshFlg |= LCD_REFRESH_SCENE;		
	}
}

// 错误检测定时器 -----------------------------------------------
void drTIMER_ERRStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_ERR, OutTick);
}

void drTIMER_ERRStop(void)
{
	drTIMER_Stop(&drTIMER_ERR);
}

void drTIMER_ERRHandler(void)
{
	drTIMER_ERR.TimeOutFlg = true;
}

void drTIMER_ERREventHandler(void)
{
	if(drCMN_BoolFlgCheck(&drTIMER_ERR.TimeOutFlg))
	{
		drERR.HintFlg = true;
	}
}

// 自动发送测试定时器 ----------------------------------------------
void drTIMER_AutoSendStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_AutoSend, OutTick);
}

void drTIMER_AutoSendStop(void)
{
	drTIMER_Stop(&drTIMER_AutoSend);
}

void drTIMER_AutoSendHandler(void)
{
	drTIMER_AutoSend.TimeOutFlg = true;
}

void drTIMER_AutoSendEventHandler(void)
{
	if(drCMN_BoolFlgCheck(&drTIMER_AutoSend.TimeOutFlg))
	{
		KEY.ScanDownFlg = true;
		KEY.Type = KEY_TYPE_SIMULATION;
		KEY.ScanValue = KEY_APP_A_1;		
	}
}

// 信号强度显示 ---------------------------------------------------
void drTIMER_RSSIStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_RSSI, OutTick);
}

void drTIMER_RSSIStop(void)
{
	drTIMER_Stop(&drTIMER_RSSI);
}

void drTIMER_RSSIHandler(void)
{
	drTIMER_RSSI.TimeOutFlg = true;
}

void drTIMER_RSSIEventHandler(void)
{
	if(drCMN_BoolFlgCheck(&drTIMER_RSSI.TimeOutFlg))
	{
		LCD.DATA.RefreshFlg |= LCD_REFRESH_SIGNAL;
	}
}

// 按键频率控制定时器 ------------------------------------------
void drTIMER_KeyFreqCtrlStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_KeyFreqCtrl, OutTick);
}

void drTIMER_KeyFreqCtrlStop(void)
{
	drTIMER_Stop(&drTIMER_KeyFreqCtrl);
}

void drTIMER_KeyFreqCtrlHandler(void)
{
	drTIMER_KeyFreqCtrl.TimeOutFlg = true;
}

void drTIMER_KeyFreqCtrlEventHandler(void)
{
	if(drCMN_BoolFlgCheck(&drTIMER_KeyFreqCtrl.TimeOutFlg))
	{
		drTIMER_KeyFreqCtrlStop();
		
		APP.KeyCntLimitFlg = false;		
	}
}

// 发送频率限制定时器 --------------------------------------------------
void drTIMER_SendLimitStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_SendLimit, OutTick);
}

void drTIMER_SendLimitStop(void)
{
	drTIMER_Stop(&drTIMER_SendLimit);
}

void drTIMER_SendLimitHandler(void)
{
	drTIMER_SendLimit.TimeOutFlg = true;
}

void drTIMER_SendLimitEventHandler(void)
{
	if(drCMN_BoolFlgCheck(&drTIMER_SendLimit.TimeOutFlg))
	{
		drTIMER_SendLimitStop();
		
		APP.QUE.KeySendLimitFlg = false;
	}
}

// 13.56MHz收到中断后延时读写数据定时器 -------------------------------------
void drTIMER_NFCStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_NFC, OutTick);
}

void drTIMER_NFCStop(void)
{
	drTIMER_Stop(&drTIMER_NFC);
}

void drTIMER_NFCHandler(void)
{
	drTIMER_NFC.TimeOutFlg = true;
}

void drTIMER_NFCEventHandler(void)
{
	if(drCMN_BoolFlgCheck(&drTIMER_NFC.TimeOutFlg))
	{
		drTIMER_NFCStop();
		
		APP.NRFUpdataFlg = true;
	}
}

// 看门狗喂狗定时器 -----------------------------------------------------
void drTIMER_WDTStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_WDT, OutTick);
}

void drTIMER_WDTStop(void)
{
	drTIMER_Stop(&drTIMER_WDT);
}

void drTIMER_WDTHandler(void)
{
	drTIMER_WDT.TimeOutFlg = true;
}

void drTIMER_WDTEventHandler(void)
{
	if(drCMN_BoolFlgCheck(&drTIMER_WDT.TimeOutFlg))
	{
		WDT.FeedFlg = true;
	}
}

// 按键驱动定时器 -------------------------------------------------
void drTIMER_KEYStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_KEY, OutTick);
}

void drTIMER_KEYStop(void)
{
	drTIMER_Stop(&drTIMER_KEY);
}

void drTIMER_KEYHandler(void)
{
	drTIMER_KEY.TimeOutFlg = true;
}

void drTIMER_KEYEventHandler(void)
{
	if(drCMN_BoolFlgCheck(&drTIMER_KEY.TimeOutFlg))
	{
		KEY.PressFlg = true;
	}
}

// 发送超时定时器 ---------------------------------------------------
void drTIMER_TxOvertimeStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_TxOvertime, OutTick);
}

void drTIMER_TxOvertimeStop(void)
{
	drTIMER_Stop(&drTIMER_TxOvertime);
}

void drTIMER_TxOvertimeHandler(void)
{
	drTIMER_TxOvertime.TimeOutFlg = true;
}

void drTIMER_TxOvertimeEventHandler(void)
{
	if(drCMN_BoolFlgCheck(&drTIMER_TxOvertime.TimeOutFlg))
	{
		drTIMER_TxOvertimeStop();
		
		nrf_esb_flush_tx();
		TIMER_RxWindowReset();
	}
}

// 记住按键键值，当收到题目是自动发键值 ---------------------------------------------------
void drTIMER_RetainKeyStart(uint32_t OutTick)
{
	drTIMER_Start(&drTIMER_RetainKey, OutTick);
}

void drTIMER_RetainKeyStop(void)
{
	drTIMER_Stop(&drTIMER_RetainKey);
}

void drTIMER_RetainKeyHandler(void)
{
	drTIMER_RetainKey.TimeOutFlg = true;
}

void drTIMER_RetainKeyEventHandler(void)
{
	if(drCMN_BoolFlgCheck(&drTIMER_RetainKey.TimeOutFlg))
	{
		drTIMER_RetainKeyStop();
		
		APP.RetainKeyExistFlg = false;					
		
		if(drCMN_BoolFlgCheck(&APP.RetainKeySendFlg))	// 若需要发送键值（在按键保留时间内收到题目）则发送键值
		{
			KEY.ScanDownFlg = true;
			KEY.Type = KEY_TYPE_SIMULATION;
			KEY.ScanValue = APP.RetainKeyVal;
		}			
	}
}




