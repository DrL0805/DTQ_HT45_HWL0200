#ifndef __POWER_H
#define __POWER_H

#include "main.h"

#define SYS_OFF_COUNT		(45)		//系统休眠多久后自动关机，单位min

typedef enum 
{			 
	SYS_OFF, 							// 关机
	SYS_ON, 							// 开机
	SYS_SLEEP,							// 休眠
	SYS_TEST,							// 系统测试
	SYS_MATCH							// 无线配对
}POWER_SYSTEM_STATE_TYPE;

typedef struct
{
	bool					SysInitializedFlg;		//系统初始化完成标志
	
	POWER_SYSTEM_STATE_TYPE	SysState;
}POWER_PARAMETERS_T;


extern POWER_PARAMETERS_T		POWER;

void POWER_Init(void);
void POWER_SysPowerOff(void);
void POWER_SysOnToOff(void);
void POWER_SysOnToSleep(void);
void POWER_SysOffToOn(void);
void POWER_SysSleepToOn(void);
void POWER_SysOnToTest(void);
void POWER_SysOnToMatch(void);
void POWER_SysMatchToOn(void);

void POWER_DCDCEnable(void);
void POWER_DCDCDisable(void);

#endif



