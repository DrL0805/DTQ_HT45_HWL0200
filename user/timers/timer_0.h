#ifndef __TIMER_0_H
#define __TIMER_0_H	 

// Includes -----------------------------------------------------------
#include "main.h"

// Defines ------------------------------------------------------------
					

// Typedefs -----------------------------------------------------------
typedef struct 
{
	uint32_t	TickCnt;
}TIMER0_PATAMETERS_T;


typedef struct 
{
	bool		InitedFlg;
	bool		TimeOutFlg;
	
	uint32_t 	StartTickCnt;
	uint32_t    TimeOutTickCnt;
}TIMER0_INSTANCE_T;


// Functions ----------------------------------------------------------
extern uint32_t RTC0_Init(void);
extern void drTIM_StartTickSource(void);
extern void drTIM_StopTickSource(void);
extern void drTIM_Start_2(TIMER0_INSTANCE_T * TimerInstance, uint32_t OutTickCnt);
extern void drTIM_Stop_2(TIMER0_INSTANCE_T * TimerInstance);
extern void drTIM_TimeOutCheck(TIMER0_INSTANCE_T * TimerInstance);
extern void drTIM_EventHandler(void);

// 用户自定义定时器
void drTIM_TmpStart(void);
void drTIM_TmpStop(void);
void drTIM_TmpHandler(void);

void drTIM_SysSleepStart(void);
void drTIM_SysSleepStop(void);
void drTIM_SysSleepHandler(void);

void drTIM_LowPwrPromptStart(void);
void drTIM_LowPwrPromptStop(void);
void drTIM_LowPwrPromptHandler(void);

void drTIM_SendResultStart(void);
void drTIM_SendResultStop(void);
void drTIM_SendResultHandler(void);

void drTIM_LCDStart(void);
void drTIM_LCDStop(void);
void drTIM_LCDHandler(void);

void drTIM_ERRStart(void);
void drTIM_ERRStop(void);
void drTIM_ERRHandler(void);

void drTIM_AutoSendStart(void);
void drTIM_AutoSendStop(void);
void drTIM_AutoSendHandler(void);

void drTIM_RSSIStart(void);
void drTIM_RSSIStop(void);
void drTIM_RSSIHandler(void);

void drTIM_KeyFreqCtrlStart(void);
void drTIM_KeyFreqCtrlStop(void);
void drTIM_KeyFreqCtrlHandler(void);

void drTIM_SendLimitStart(void);
void drTIM_SendLimitStop(void);
void drTIM_SendLimitHandler(void);

void drTIM_NFCStart(void);
void drTIM_NFCStop(void);
void drTIM_NFCHandler(void);

// Globals ------------------------------------------------------------

//extern nrf_drv_timer_t TIMER_PUBLIC;				// 公共定时器
//extern nrf_drv_rtc_t rtc; 



extern TIMER0_PATAMETERS_T		TIMER0; 			
extern TIMER0_INSTANCE_T		drTIM_Tmp;
extern TIMER0_INSTANCE_T		drTIM_SysSleep;;

#endif














