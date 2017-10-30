#ifndef __POWER_H
#define __POWER_H

#include "main.h"

#define SYS_OFF_COUNT		(45)		//ϵͳ���߶�ú��Զ��ػ�����λmin

typedef enum 
{			 
	SYS_OFF, 							// �ػ�
	SYS_ON, 							// ����
	SYS_SLEEP,							// ����
	SYS_TEST,							// ϵͳ����
	SYS_MATCH							// �������
}POWER_SYSTEM_STATE_TYPE;

typedef struct
{
	bool					SysInitializedFlg;		//ϵͳ��ʼ����ɱ�־
	
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



