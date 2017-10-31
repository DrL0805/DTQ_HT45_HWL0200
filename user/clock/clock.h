#ifndef __CLOCK_H
#define	__CLOCK_H

#include "drl_err.h"
#include "nrf_drv_clock.h"
#include "nrf_delay.h"

typedef struct
{
	bool		 Flg;
	
}clock_struct_t;


extern clock_struct_t	CLOCK;

uint32_t CLOCK_Init(void);
uint32_t CLOCK_HFCLKStart(void);
uint32_t CLOCK_HFCLKStop(void);
uint32_t CLOCK_LFCLKStart(void);
uint32_t CLOCK_LFCLKStop(void);
uint32_t CLOCK_RTCCalibrate(void);

#endif 




