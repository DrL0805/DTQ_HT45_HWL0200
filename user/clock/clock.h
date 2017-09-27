#ifndef __CLOCK_H
#define	__CLOCK_H

#include "nrf_drv_clock.h"
#include "nrf_delay.h"

typedef struct
{
	bool		 Flg;
	
}clock_struct_t;


extern clock_struct_t	CLOCK;

void CLOCK_Init(void);
void CLOCK_HFCLKStart(void);
void CLOCK_HFCLKStop(void);
void CLOCK_LFCLKStart(void);
void CLOCK_LFCLKStop(void);
void CLOCK_RTCCalibrate(void);

#endif 




