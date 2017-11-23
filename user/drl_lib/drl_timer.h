#ifndef __DRL_TIMER_H
#define __DRL_TIMER_H	 

// Includes -----------------------------------------------------------
#include "drl_library.h"

// Defines ------------------------------------------------------------
#define 	drTIMER_CLOCK_FREQ			(32768)
#define 	drTIEMR_PRESCALER			(32)		// 定时器分频系数
#define 	drTIMER_TICK_CNT(MS)		(uint32_t)((((MS) * drTIMER_CLOCK_FREQ) / (1000 * (drTIEMR_PRESCALER + 1))))	

#define		drTIMER_MAX_OUT_VALUE		(0xFFFFFF - 1)		//最大超时值

#define 	drTIMER_PERIOD_SysSleep				drTIMER_TICK_CNT(5000)
#define 	drTIMER_PERIOD_LowPwrPrompt			drTIMER_TICK_CNT(1000)
#define 	drTIMER_PERIOD_SendResult			drTIMER_TICK_CNT(1000)
#define 	drTIMER_PERIOD_LCD					drTIMER_TICK_CNT(3000)
#define 	drTIMER_PERIOD_ERR					drTIMER_TICK_CNT(2000)
#define 	drTIMER_PERIOD_AutoSend				drTIMER_TICK_CNT(200)
#define 	drTIMER_PERIOD_RSSI					drTIMER_TICK_CNT(1000)
#define 	drTIMER_PERIOD_KeyFreqCtrl			drTIMER_TICK_CNT(300)
#define 	drTIMER_PERIOD_SendLimit			drTIMER_TICK_CNT(300)
#define 	drTIMER_PERIOD_NFC					drTIMER_TICK_CNT(500)
#define 	drTIMER_PERIOD_WDT					drTIMER_TICK_CNT(1000)
#define 	drTIMER_PERIOD_KEY					drTIMER_TICK_CNT(30)
#define 	drTIMER_PERIOD_TxOvertime			drTIMER_TICK_CNT(20)


// Typedefs -----------------------------------------------------------
typedef enum
{
	drTIM_UNINITIALIZED,				// 未初始化，仅drTIM_CreateTimer创建，但未drTIMER_Start初始化定时器参数
	drTIM_INITIALIZED,					// 已初始化，已drTIM_CreateTimer创建，且drTIM_Start初始化定时器参数
	drTIM_RUNNING,						// 运行
	drTIM_SUSPEND						// 暂停
}drTIM_STATE_T;


typedef struct drTIM_TIMER_NODE
{
	bool							TimeOutFlg;			// 定时器超时标志
	
	drTIM_STATE_T 					State;				// 定时器状态
	
	uint32_t    					TotalTickVal;		// 定时器超时共需要多少tick
	uint32_t						RemainTickVal;		// 还剩多少tick定时器超时
	void 							(*TimerOutHandler)(void);			// 函数指针
	struct drTIM_TIMER_NODE * 		pNext;
}drTIM_TIMER_PARAMETERS_T;

typedef struct
{
	bool									TickRunningFlg;		// tick运行标志
	
	uint32_t								CurVal;				// 当前tick值
	drTIM_TIMER_PARAMETERS_T * 				pNext;
}drTIM_HEAD_PATAMETERS_T;


// Functions ----------------------------------------------------------
extern uint32_t drTIMER_Init(void);
extern uint32_t drTIMER_CreateTimer(drTIM_TIMER_PARAMETERS_T* pTIMER, void (*pTimerOutHandler)(void));
extern uint32_t drTIMER_Start(drTIM_TIMER_PARAMETERS_T* pTIMER, uint32_t OutTickVal);
extern uint32_t drTIMER_Stop(drTIM_TIMER_PARAMETERS_T* pTIMER);

extern void drTIMER_EventHandler(void);

extern void drTIMER_TestStart(uint32_t OutTick);
extern void drTIMER_TestStop(void);
extern void drTIMER_TestHandler(void);

extern void drTIMER_PublicStart(uint32_t OutTick);
extern void drTIMER_PublicStop(void);
extern void drTIMER_PublicHandler(void);

extern void drTIMER_SysSleepStart(uint32_t OutTick);
extern void drTIMER_SysSleepStop(void);
extern void drTIMER_SysSleepHandler(void);
extern void drTIMER_SysSleepEventHandler(void);

extern void drTIMER_LowPwrPromptStart(uint32_t OutTick);
extern void drTIMER_LowPwrPromptStop(void);
extern void drTIMER_LowPwrPromptHandler(void);
extern void drTIMER_LowPwrPromptEventHandler(void);

extern void drTIMER_SendResultStart(uint32_t OutTick);
extern void drTIMER_SendResultStop(void);
extern void drTIMER_SendResultHandler(void);
extern void drTIMER_SendResultEventHandler(void);

extern void drTIMER_LCDStart(uint32_t OutTick);
extern void drTIMER_LCDStop(void);
extern void drTIMER_LCDHandler(void);
extern void drTIMER_LCDHandEventler(void);

extern void drTIMER_ERRStart(uint32_t OutTick);
extern void drTIMER_ERRStop(void);
extern void drTIMER_ERRHandler(void);
extern void drTIMER_ERREventHandler(void);

extern void drTIMER_AutoSendStart(uint32_t OutTick);
extern void drTIMER_AutoSendStop(void);
extern void drTIMER_AutoSendHandler(void);
extern void drTIMER_AutoSendEventHandler(void);

extern void drTIMER_RSSIStart(uint32_t OutTick);
extern void drTIMER_RSSIStop(void);
extern void drTIMER_RSSIHandler(void);
extern void drTIMER_RSSIEventHandler(void);

extern void drTIMER_KeyFreqCtrlStart(uint32_t OutTick);
extern void drTIMER_KeyFreqCtrlStop(void);
extern void drTIMER_KeyFreqCtrlHandler(void);
extern void drTIMER_KeyFreqCtrlEventHandler(void);

extern void drTIMER_SendLimitStart(uint32_t OutTick);
extern void drTIMER_SendLimitStop(void);
extern void drTIMER_SendLimitHandler(void);
extern void drTIMER_SendLimitEventHandler(void);

extern void drTIMER_NFCStart(uint32_t OutTick);
extern void drTIMER_NFCStop(void);
extern void drTIMER_NFCHandler(void);
extern void drTIMER_NFCEventHandler(void);

extern void drTIMER_WDTStart(uint32_t OutTick);
extern void drTIMER_WDTStop(void);
extern void drTIMER_WDTHandler(void);
extern void drTIMER_WDTEventHandler(void);

extern void drTIMER_KEYStart(uint32_t OutTick);
extern void drTIMER_KEYStop(void);
extern void drTIMER_KEYHandler(void);
extern void drTIMER_KEYEventHandler(void);

extern void drTIMER_TxOvertimeStart(uint32_t OutTick);
extern void drTIMER_TxOvertimeStop(void);
extern void drTIMER_TxOvertimeHandler(void);
extern void drTIMER_TxOvertimeEventHandler(void);

// Globals ------------------------------------------------------------
extern drTIM_TIMER_PARAMETERS_T		drTIMER_TEST;

#endif














