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
	
	CLOCK_HFCLKStop();
	
	RADIO_Sleep();
	
	TIMER_ADCStop();
	
	drTIMER_RSSIStop();
	
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

	drTIMER_SysSleepStart(drTIMER_PERIOD_SysSleep);
	
	drTIMER_RSSIStart(drTIMER_PERIOD_RSSI);
	
	LCD_WakeUp();
}

//����ϵͳ����״̬
void POWER_SysOnToTest(void)
{
	POWER.SysState = SYS_TEST;
	

	drTIMER_SysSleepStop();
	
	TEST.RxRssi = 0;
	TEST.TxRssi = 0;
	
//	for(uint8_t i = 0;i < 2;i++)
//	{
//		LCD_DisplayAll();
//		nrf_delay_ms(1000);
//		LCD_ClearScreen();
//		nrf_delay_ms(1000);		
//	}	
	for(uint8_t i = 0;i < 64;i += 2)
	{
		LCD_DRV_DisplayOne(i,LCD_DRV_DOT_HANZI,0xBBD8);
	}
	nrf_delay_ms(2000);	
	LCD_ClearScreen();	
	nrf_delay_ms(300);	
	
	LCD.DATA.RefreshFlg |= LCD_REFRESH_STUDEN_ID;
}


void POWER_SysOnToMatch(void)
{
	POWER.SysState = SYS_MATCH;

	drTIMER_SysSleepStop();			// ���ģʽ�£�������30�벻����
	
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
	
	drTIMER_SysSleepStart(drTIMER_PERIOD_SysSleep);
	
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





