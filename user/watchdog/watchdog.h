#ifndef __WATCHDOG_H
#define __WATCHDOG_H

#include "main.h"

#define 	USE_WATCH_DOG

typedef struct
{
	bool 	FeedFlg;
}WATCHDOG_PAR_T;

extern WATCHDOG_PAR_T			 WDT;

void WDT_Init(void);
void WDT_FeedDog(void);


#endif









