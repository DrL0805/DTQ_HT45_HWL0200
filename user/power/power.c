#include "power.h"


POWER_PARAMETERS_T		POWER;

void POWER_Init(void)
{
	//�ṹ�������ʼ��
	POWER.SysState = SYS_ON;
	
	POWER_DCDCEnable();
}

//�ػ�����
void POWER_SysOnToOff(void)
{
	POWER.SysState = SYS_OFF;			//�л�ϵͳ״̬
	
	RADIO_Sleep();						//ֹͣRADIO����				
	
	LCD_ClearScreen();					
	LCD_Sleep();						//�ر�LCD��ʾ
	
	CLOCK_HFCLKStop();					//ֹͣ�ⲿʱ��
	
	APP_ClearQuestionInfo();			//���������Ŀ��Ϣ
}

//ϵͳ���ߺ���
void POWER_SysOnToSleep(void)
{
	POWER.SysState = SYS_SLEEP;
	
	CLOCK_HFCLKStop();
	
	RADIO_Sleep();
	
	TIMER_ADCStop();	
	
	LCD_Sleep();
}

//����
void POWER_SysOffToOn(void)
{
	NVIC_SystemReset();				//��λ
}

//����
void POWER_SysSleepToOn(void)
{
	POWER.SysState = SYS_ON;
	
	CLOCK_HFCLKStart();
	
	RADIO_WakeUp();
	
	TIMER_ADCStart();
	
	TIMER_SysStateStart();				//30S���߶�ʱ������
	
	LCD_WakeUp();
}

//����ϵͳ����״̬
void POWER_SysOnToTest(void)
{
	POWER.SysState = SYS_TEST;
	
	TIMER_SysStateStop();			//����ģʽ�£�������30�벻����
	
	TEST.LcdLetterVal = 0;
	TEST.RxRssi = 0;
	TEST.TxRssi = 0;
}


void POWER_SysOnToMatch(void)
{
	POWER.SysState = SYS_MATCH;
	TIMER_SysStateStop();							// ���ģʽ�£�������30�벻����
	
	RADIO.IM.RxChannal = NRF_MATCH_RX_CHANNEL;		// ����Ƶ������Ϊ���Ƶ��
	
	// ��������Ϊ0������ʾ����Ϊ0��PIN��ֵ
	MATCH.SelectIndex = 0;
	MATCH_LCDDisplayPIN(MATCH.SelectIndex);	
	
	// ���LCD������ʾ��Ϣ
	LCD_DisplayJudge(JUDGE_CLEAR);

}

void POWER_SysMatchToOn(void)
{
	POWER.SysState = SYS_ON;
	TIMER_SysStateStart();							// ���¿���30�����߶�ʱ��	
	
	RADIO.IM.RxChannal = RADIO.MATCH.RxChannal;		// ����Ƶ������Ϊ����Ƶ��

	
}

void POWER_DCDCEnable(void)
{
	NRF_POWER->DCDCEN = 1;
}

void POWER_DCDCDisable(void)
{
	NRF_POWER->DCDCEN = 0;
}





