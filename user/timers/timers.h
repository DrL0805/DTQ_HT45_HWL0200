#ifndef __TIMERS_H
#define	__TIMERS_H


#include "main.h"

typedef struct
{
	bool	RetransmitEventFlg;			// 
}TIMER_PARAMETERS_T;


extern TIMER_PARAMETERS_T	TIMER;

void TIMERS_Init(void);
void TIMER_EventHandler(void);

void TIMER_TempStart(void);
void TIMER_TempStop(void);
void TIMER_TempHandler(void * p_context);

void TIMER_LCDStart(void);
void TIMER_LCDStop(void);
void TIMER_LCDHandler(void * p_context);

void TIMER_ButtonStart(void);
void TIMER_ButtonStop(void);
void TIMER_ButtonHandler(void * p_context);

void TIMER_RxWindowStart(void);
void TIMER_RxWindowAdd(uint8_t time_ms);
void TIMER_RxWindowReset(void);
void TIMER_RxWindowStop(void);
void TIMER_RxWindowHandler(void * p_context);

void TIMER_TxOvertimeStart(void);
void TIMER_TxOvertimeStop(void);
void TIMER_TxOvertimeHandler(void * p_context);

void TIMER_SysStateStart(void);
void TIMER_SysStateStop(void);
void TIMER_SysStateHandler(void * p_context);

void TIMER_KeyPowerStart(void);
void TIMER_KeyPowerStop(void);
void TIMER_KeyPowerHandler(void * p_context);

void TIMER_ADCStart(void);
void TIMER_ADCStop(void);
void TIMER_ADCHandler(void * p_context);

void TIMER_TxAttendStart(void);
void TIMER_TxAttendStop(void);
void TIMER_TxAttendHandler(void * p_context);

void TIMER_SysOffStart(void);
void TIMER_SysOffStop(void);
void TIMER_SysOffHandler(void * p_context);

void TIMER_WaitDataStart(uint8_t time_ms);
void TIMER_WaitDataStop(void);
void TIMER_WaitDataHandler(void * p_context);

void TIMER_RetransmitStart(void);
void TIMER_RetransmitStop(void);
void TIMER_RetransmitHandler(void * p_context);

void TIMER_TxResultDisplayStart(void);
void TIMER_TxResultDisplayStop(void);
void TIMER_TxResultDisplayHandler(void * p_context);

void TIMER_DisVerStart(void);
void TIMER_DisVerStop(void);
void TIMER_DisVerHandler(void * p_context);

void TIMER_SendAllowStart(void);
void TIMER_SendAllowStop(void);
void TIMER_SendAllowHandler(void * p_context);

void TIMER_TxRandomDelayStart(void);
void TIMER_TxRandomDelayStop(void);
void TIMER_TxRandomDelayHandler(void * p_context);

//void TIMER_WatchDogStart(void);
//void TIMER_WatchDogStop(void);
//void TIMER_WatchDogHandler(void * p_context);

#endif 








