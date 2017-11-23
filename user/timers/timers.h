#ifndef __TIMERS_H
#define	__TIMERS_H


#include "main.h"

typedef struct
{
	bool	RetransmitEventFlg;			
}TIMER_PARAMETERS_T;


extern TIMER_PARAMETERS_T	TIMER;

uint32_t TIMERS_Init(void);
void TIMER_EventHandler(void);

void TIMER_RxWindowStart(void);
void TIMER_RxWindowAdd(uint8_t time_ms);
void TIMER_RxWindowReset(void);
void TIMER_RxWindowStop(void);
void TIMER_RxWindowHandler(void * p_context);

void TIMER_ADCStart(void);
void TIMER_ADCStop(void);
void TIMER_ADCHandler(void * p_context);

void TIMER_WaitDataStart(uint8_t time_ms);
void TIMER_WaitDataStop(void);
void TIMER_WaitDataHandler(void * p_context);

void TIMER_RetransmitStart(void);
void TIMER_RetransmitStop(void);
void TIMER_RetransmitHandler(void * p_context);

void TIMER_TxRandomDelayStart(void);
void TIMER_TxRandomDelayStop(void);
void TIMER_TxRandomDelayHandler(void * p_context);

#endif 








