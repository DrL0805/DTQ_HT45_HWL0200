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
extern uint32_t TIMER0_Init(void);
//extern void drTIMER_TimerOutCheck(void);
extern void drTIMER_Start(TIMER0_INSTANCE_T * TimerInstance, uint32_t OutTickCnt);
extern void drTIMER_Stop(TIMER0_INSTANCE_T * TimerInstance);
extern void drTIMER_TimeOutCheck(TIMER0_INSTANCE_T * TimerInstance);
extern void drTIMER_EventHandler(void);

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
// Globals ------------------------------------------------------------
extern TIMER0_PATAMETERS_T		TIMER0; 			
extern TIMER0_INSTANCE_T		drTIM_Tmp;
extern TIMER0_INSTANCE_T		drTIM_SysSleep;;

#endif














