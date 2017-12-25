// Revision record ----------------------------------------------------

// Includes -----------------------------------------------------------
#include "drl_timer.h"

// Functions ----------------------------------------------------------
static uint32_t drTIMER_TickScheduler(void);
static uint32_t drTIMER_TickSourceInit(void);
static uint32_t drTIMER_TickParametersInit(void);

// Globals ------------------------------------------------------------

// ��ʱ�������ͷ
drTIM_HEAD_PATAMETERS_T			drTIMER_HEAD;					
drTIM_HEAD_PATAMETERS_T*		pdrTIMER_HEAD = &drTIMER_HEAD;

// �û�����Ķ�ʱ���ṹ��
drTIM_TIMER_PARAMETERS_T		drTIMER_TEST;
drTIM_TIMER_PARAMETERS_T		drTIMER_PUBLIC;

drTIM_TIMER_PARAMETERS_T		drTIMER_SysSleep;			// ϵͳ����						
drTIM_TIMER_PARAMETERS_T		drTIMER_LowPwrPrompt;		// �͵�������				
drTIM_TIMER_PARAMETERS_T		drTIMER_SendResult;			// ��ʾ���ͽ�����ɹ�/ʧ�ܣ�			
drTIM_TIMER_PARAMETERS_T		drTIMER_LCD;				// LCD��ʾ				
drTIM_TIMER_PARAMETERS_T		drTIMER_ERR;				// �������������ʾ				
drTIM_TIMER_PARAMETERS_T		drTIMER_AutoSend;			// �Զ���������ѹ������			
drTIM_TIMER_PARAMETERS_T		drTIMER_RSSI;				// ��ʱˢ��RSSIֵ				
drTIM_TIMER_PARAMETERS_T		drTIMER_KeyFreqCtrl;		// ����Ƶ�ʿ���				
drTIM_TIMER_PARAMETERS_T		drTIMER_SendLimit;			// ����Ƶ������			
drTIM_TIMER_PARAMETERS_T		drTIMER_NFC;				// ��ȡ13.56M�ж���ʱ
drTIM_TIMER_PARAMETERS_T		drTIMER_WDT;				// ���Ź�ι����ʱ��
drTIM_TIMER_PARAMETERS_T		drTIMER_KEY;				// ����������ʱ��
drTIM_TIMER_PARAMETERS_T		drTIMER_TxOvertime;			// ���ͳ�ʱ��ʱ
drTIM_TIMER_PARAMETERS_T		drTIMER_ADC;				// ��ص���ADC�ɼ���ʱ��
drTIM_TIMER_PARAMETERS_T		drTIMER_RetainKey;			// ��ס����ֵ�����յ���Ŀʱ�Զ�����



// Locals -------------------------------------------------------------

uint32_t drTIMER_Init(void)
{	
    uint32_t err_code;
	
	// ����tickԴ
	drTIMER_TickSourceInit();
	
	// ��ʼtick����
	drTIMER_TickParametersInit();
	
	// �����û���ʱ��
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

// ��ʱ����ʱ��Ⲣ������
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
	// �趨�¶�ʱ��pTIMER����
	pTIMER->TimeOutFlg = false;
	pTIMER->State = drTIM_UNINITIALIZED;
	pTIMER->RemainTickVal = drTIMER_MAX_OUT_VALUE;
	pTIMER->TotalTickVal = drTIMER_MAX_OUT_VALUE;
	pTIMER->TimerOutHandler = pTimerOutHandler;
	
	// ��ͷ���֮������½ڵ�
	pTIMER->pNext = pdrTIMER_HEAD->pNext;
	pdrTIMER_HEAD->pNext = pTIMER;
	
	return 0;
}

uint32_t drTIMER_Start(drTIM_TIMER_PARAMETERS_T* pTIMER, uint32_t OutTickVal)
{
	// ��ʼ����ʱ������
	pTIMER->State = drTIM_INITIALIZED;
	pTIMER->TotalTickVal = OutTickVal;
	pTIMER->RemainTickVal = OutTickVal;
	
	// ��ʼһ�ζ�ʱ������
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
	uint32_t NextTickVal = drTIMER_MAX_OUT_VALUE;			// ��һ����ʱ����ʱ����tick		
	uint32_t CurCount;				
	drTIM_TIMER_PARAMETERS_T* pNextTimer = pdrTIMER_HEAD->pNext;
	
	CurCount = NRF_RTC0->COUNTER;			// ��ȡ��ǰtickֵ
	
	NRF_RTC0->TASKS_CLEAR = 1;				// ��COUNTERֵ�����㿪ʼ����	
	NRF_RTC0->EVENTS_TICK = 0;				// EVENT������һ��Ҫ��գ������һֱ����EVENT�¼�
	NRF_RTC0->EVENTS_COMPARE[0] = 0;		// EVENT������һ��Ҫ��գ������һֱ����EVENT�¼�		
	
	while(NULL != pNextTimer)	// ����������ʱ����
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
					// ������ʱ����ʱ����
					pNextTimer->TimerOutHandler();	
					
					// ���ö�ʱ����ʱֵ
					pNextTimer->RemainTickVal = pNextTimer->TotalTickVal;
				}
				else
				{
					// ���¼����´γ�ʱ����tick��
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

// TICKԴ��ʼ��
static uint32_t drTIMER_TickSourceInit(void)
{
	
	NRF_RTC0->PRESCALER = drTIEMR_PRESCALER;	// fRTC [kHz] = 32.768 / (PRESCALER + 1 )
												// PRESCALER = 32��Լ1ms��TICK��COUNTER++��ʵ������1.007ms
												// PRESCALER = 0��Լ30.517us
	
	NRF_RTC0->TASKS_CLEAR = 1;
	NRF_RTC0->CC[0] = drTIMER_MAX_OUT_VALUE;
	
//	NRF_RTC0->EVTENSET |= 0x01 << 0;				// ʹ��TICK�ж�
//	NRF_RTC0->INTENSET |= 0x01 << 0;
	NRF_RTC0->EVTENSET |= 0x01 << 16;				// ʹ��COMPARE0�ж�
	NRF_RTC0->INTENSET |= 0x01 << 16;
	
	NVIC_ClearPendingIRQ(RTC0_IRQn);
    NVIC_SetPriority(RTC0_IRQn, 1);
    NVIC_EnableIRQ(RTC0_IRQn);		
	
	NRF_RTC0->TASKS_START = 1;			// ��ʼ����RTC0��ʱ��		
	
	return 0;
}

// TICK������ʼ��
static uint32_t drTIMER_TickParametersInit(void)
{
	drTIMER_HEAD.TickRunningFlg = true;
	drTIMER_HEAD.CurVal = 0;
	
	drTIMER_HEAD.pNext = NULL;
	
	return 0;
}

// ���Զ�ʱ�� -----------------------------------------------------------
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

// ������ʱ�� -----------------------------------------------------------
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

// ϵͳ���߶�ʱ�� --------------------------------------------------
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

// �͵���������ʱ�� --------------------------------------------------
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

// ���ͽ����ʾ��ʱ�� --------------------------------------------
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

// LCD��ʱ��ʾ��ʱ�� ----------------------------------------------------
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

// �����ⶨʱ�� -----------------------------------------------
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

// �Զ����Ͳ��Զ�ʱ�� ----------------------------------------------
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

// �ź�ǿ����ʾ ---------------------------------------------------
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

// ����Ƶ�ʿ��ƶ�ʱ�� ------------------------------------------
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

// ����Ƶ�����ƶ�ʱ�� --------------------------------------------------
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

// 13.56MHz�յ��жϺ���ʱ��д���ݶ�ʱ�� -------------------------------------
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

// ���Ź�ι����ʱ�� -----------------------------------------------------
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

// ����������ʱ�� -------------------------------------------------
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

// ���ͳ�ʱ��ʱ�� ---------------------------------------------------
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

// ��ס������ֵ�����յ���Ŀ���Զ�����ֵ ---------------------------------------------------
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
		
		if(drCMN_BoolFlgCheck(&APP.RetainKeySendFlg))	// ����Ҫ���ͼ�ֵ���ڰ�������ʱ�����յ���Ŀ�����ͼ�ֵ
		{
			KEY.ScanDownFlg = true;
			KEY.Type = KEY_TYPE_SIMULATION;
			KEY.ScanValue = APP.RetainKeyVal;
		}			
	}
}




