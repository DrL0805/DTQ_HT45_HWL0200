#include "power.h"


POWER_PARAMETERS_T		POWER;

uint32_t POWER_Init(void)
{
	//�ṹ�������ʼ��
	POWER.SysState = SYS_ON;
	
	POWER_DCDCEnable();
	
	return drERROR_SUCCESS;
}

// 51822�������
void POWER_SysPowerOff(void)
{
	GPIO_Default();							//�ػ�ǰGPIO����Ϊ����̬����ֹ������������ϵͳ
	nrf_gpio_cfg_sense_input(KEY_PWR, NRF_GPIO_PIN_NOPULL, NRF_GPIO_PIN_SENSE_LOW);			
	NRF_POWER->SYSTEMOFF = 1;				//��������ģʽ	
}

//�ػ�����
void POWER_SysOnToOff(void)
{
	POWER.SysState = SYS_OFF;			//�л�ϵͳ״̬
	
	RADIO_Sleep();						//ֹͣRADIO����				
					
	LCD_Sleep();						//�ر�LCD��ʾ
	
	CLOCK_HFCLKStop();					//ֹͣ�ⲿʱ��
	
}

//ϵͳ���ߺ���
void POWER_SysOnToSleep(void)
{
	POWER.SysState = SYS_SLEEP;
	
//	nrf_drv_timer_disable(&TIMER_PUBLIC);
	drTIMER_StopTickSource();
	
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
	
	drTIMER_StartTickSource();
	
	CLOCK_HFCLKStart();
	
	RADIO_WakeUp();
	
	TIMER_ADCStart();
	
//	TIMER_SysStateStop();				//30S���߶�ʱ������
//	TIMER_SysStateStart();				//30S���߶�ʱ������
//	drTIMER_Stop(&drTIM_SysSleep);
//	drTIMER_Start(&drTIM_SysSleep, 50);
	drTIM_SysSleepStart();
	
	LCD_WakeUp();
}

//����ϵͳ����״̬
void POWER_SysOnToTest(void)
{
	POWER.SysState = SYS_TEST;
	
//	TIMER_SysStateStop();			//����ģʽ�£�������30�벻����
//	drTIMER_Stop(&drTIM_SysSleep);
	drTIM_SysSleepStop();
	
	TEST.LcdLetterVal = 0;
	TEST.RxRssi = 0;
	TEST.TxRssi = 0;
}


void POWER_SysOnToMatch(void)
{
	POWER.SysState = SYS_MATCH;
//	TIMER_SysStateStop();							// ���ģʽ�£�������30�벻����
//	drTIMER_Stop(&drTIM_SysSleep);
	drTIM_SysSleepStop();
	
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
//	TIMER_SysStateStart();							// ���¿���30�����߶�ʱ��	
//	drTIMER_Start(&drTIM_SysSleep, 50);
	drTIM_SysSleepStart();
	
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





