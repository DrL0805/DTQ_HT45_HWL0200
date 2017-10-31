#ifndef __WATCHDOG_H
#define __WATCHDOG_H

#include "main.h"

typedef struct
{
	bool 	FeedFlg;
}WATCHDOG_PAR_T;

extern WATCHDOG_PAR_T			 WDT;

uint32_t WDT_Init(void);
void WDT_FeedDog(void);


#endif









