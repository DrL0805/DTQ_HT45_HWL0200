#include "timers.h"


#define TIMER_DEBUG
#ifdef TIMER_DEBUG
#define TIMER_Debug  printf   
#else  
#define TIMER_Debug(...)                    
#endif 

//��ʱ���궨��
#define APP_TIMER_PRESCALER     0
#define APP_TIMER_OP_QUEUE_SIZE 17

#define TEMP_TIMEOUT_INTERVAL     					APP_TIMER_TICKS(3000, 	APP_TIMER_PRESCALER)
#define LCD_TIMEOUT_INTERVAL     					APP_TIMER_TICKS(2998, 	APP_TIMER_PRESCALER)
#define BUTTON_TIMEOUT_INTERVAL     				APP_TIMER_TICKS(50, 	APP_TIMER_PRESCALER)
#define TX_OVERTIME_TIMEOUT_INTERVAL     			APP_TIMER_TICKS(15,		APP_TIMER_PRESCALER)
#define SYS_STATE_TIMEOUT_INTERVAL     				APP_TIMER_TICKS(5000,	APP_TIMER_PRESCALER)
#define KEY_POWER_TIMEOUT_INTERVAL     				APP_TIMER_TICKS(2700,	APP_TIMER_PRESCALER) 	
#define ADC_TIMEOUT_INTERVAL    					APP_TIMER_TICKS(997,APP_TIMER_PRESCALER)		//42 ������Ϊ������Ϊ��ʹADC�ɼ���������������ܿ�
#define ADC_FIRST_SAMPLE_TIMEOUT_INTERVAL    		APP_TIMER_TICKS(42,APP_TIMER_PRESCALER)		//42 ������Ϊ������Ϊ��ʹADC�ɼ���������������ܿ�
#define TX_ATTEND_TIMEOUT_INTERVAL     				APP_TIMER_TICKS(1100,APP_TIMER_PRESCALER) 
#define SYS_OFF_TIMEOUT_INTERVAL     				APP_TIMER_TICKS(60000,APP_TIMER_PRESCALER)
#define RETRANSMIT_TIMEOUT_INTERVAL     			APP_TIMER_TICKS(70, 	APP_TIMER_PRESCALER)
#define TX_RESULT_DISPLAY_TIMEOUT_INTERVAL     		APP_TIMER_TICKS(1000,APP_TIMER_PRESCALER)
#define DISPLAY_VERSION_TIMEOUT_INTERVAL     		APP_TIMER_TICKS(2000,APP_TIMER_PRESCALER)
#define SEND_ALLOW_TIMEOUT_INTERVAL     			APP_TIMER_TICKS(300,APP_TIMER_PRESCALER)
#define WATCH_DOG_TIMEOUT_INTERVAL     				APP_TIMER_TICKS(500, 	APP_TIMER_PRESCALER)


APP_TIMER_DEF(temp_timer_id);
APP_TIMER_DEF(lcd_timer_id);					/* LCD��ʱˢ�� */
APP_TIMER_DEF(button_timer_id);
APP_TIMER_DEF(rx_window_timer_id);				/* RX�������򿪹ر� */
APP_TIMER_DEF(tx_overtime_timer_id);			/* ���ͳ�ʱ */
APP_TIMER_DEF(sys_state_timer_id);				/* ϵͳ״̬���ƣ�ON/OFF/SLEEP��30���ް���ϵͳ�������ߣ� */
APP_TIMER_DEF(key_power_timer_id);			    /* POWER����ʱ�� */
APP_TIMER_DEF(adc_timer_id);					/* ADC�ɼ���ʱ�� */
APP_TIMER_DEF(tx_attend_timer_id);			    /* ����2.4G���� */
APP_TIMER_DEF(sys_off_timer_id);				/* �ػ���ʱ����ϵͳ���߳���45min���Զ��ػ���*/
APP_TIMER_DEF(wait_data_timer_id);				/* �յ�ǰ��֡�󣬴�RX�����¼�����������Ч���� */
APP_TIMER_DEF(retransmit_timer_id);				/* ��·����ط���ʱ�� */
APP_TIMER_DEF(tx_result_display_timer_id);		/* LCD��ʾ�������ͽ�����ɹ�/ʧ�ܣ� */
APP_TIMER_DEF(display_version_timer_id);		/*  ��ʾ�汾��Ϣ��ʱ�� */
APP_TIMER_DEF(send_allow_timer_id);				/*  �������ƶ�ʱ�� */
APP_TIMER_DEF(tx_random_delay_timer_id);		/*  ���������ʱ */
//APP_TIMER_DEF(watch_dog_timer_id);

void TIMERS_Init(void)
{
	uint32_t err_code;
	
	//������ʱ��
	APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);
	
	//-------------------------- ѭ����ʱ�� ------------------------------
	err_code = app_timer_create(&temp_timer_id,APP_TIMER_MODE_REPEATED,TIMER_TempHandler);
	APP_ERROR_CHECK(err_code);
	
	err_code = app_timer_create(&lcd_timer_id,APP_TIMER_MODE_REPEATED,TIMER_LCDHandler);
	APP_ERROR_CHECK(err_code);	
	
	err_code = app_timer_create(&button_timer_id,APP_TIMER_MODE_REPEATED,TIMER_ButtonHandler);
	APP_ERROR_CHECK(err_code);	
	
	err_code = app_timer_create(&key_power_timer_id,APP_TIMER_MODE_REPEATED,TIMER_KeyPowerHandler);	
	APP_ERROR_CHECK(err_code);
	
	err_code = app_timer_create(&rx_window_timer_id,APP_TIMER_MODE_REPEATED,TIMER_RxWindowHandler);
	APP_ERROR_CHECK(err_code);	
	
	err_code = app_timer_create(&tx_attend_timer_id,APP_TIMER_MODE_REPEATED,TIMER_TxAttendHandler);
	APP_ERROR_CHECK(err_code);	

	err_code = app_timer_create(&sys_off_timer_id,APP_TIMER_MODE_REPEATED,TIMER_SysOffHandler);
	APP_ERROR_CHECK(err_code);
	
	err_code = app_timer_create(&retransmit_timer_id,APP_TIMER_MODE_REPEATED,TIMER_RetransmitHandler);
	APP_ERROR_CHECK(err_code);	
	
//	err_code = app_timer_create(&retransmit_timer_id,APP_TIMER_MODE_REPEATED,TIMER_WatchDogHandler);
//	APP_ERROR_CHECK(err_code);		

	//-------------------------- ���ζ�ʱ�� ------------------------------
	err_code = app_timer_create(&sys_state_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_SysStateHandler);
	APP_ERROR_CHECK(err_code);
	
	// ADC�ɼ������Σ�ÿ�βɼ��궼��Ҫ���¿�����ʱ��
	err_code = app_timer_create(&adc_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_ADCHandler);
	APP_ERROR_CHECK(err_code);

	err_code = app_timer_create(&wait_data_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_WaitDataHandler);
	APP_ERROR_CHECK(err_code);

	err_code = app_timer_create(&tx_result_display_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_TxResultDisplayHandler);
	APP_ERROR_CHECK(err_code);

	err_code = app_timer_create(&display_version_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_DisVerHandler);
	APP_ERROR_CHECK(err_code);	
	
	err_code = app_timer_create(&send_allow_timer_id,APP_TIMER_MODE_REPEATED,TIMER_SendAllowHandler);
	APP_ERROR_CHECK(err_code);		

	err_code = app_timer_create(&tx_random_delay_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_TxRandomDelayHandler);
	APP_ERROR_CHECK(err_code);	
}

void TIMER_EventHandler(void)
{
	
}

void TIMER_TempStart(void)
{
	uint32_t err_code;
	err_code = app_timer_start(temp_timer_id,TEMP_TIMEOUT_INTERVAL,NULL);
	APP_ERROR_CHECK(err_code);
}

void TIMER_TempStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(temp_timer_id);
	APP_ERROR_CHECK(err_code);
}

void TIMER_TempHandler(void * p_context)
{
	

}


void TIMER_LCDStart(void)
{
	uint32_t err_code;
	err_code = app_timer_start(lcd_timer_id,LCD_TIMEOUT_INTERVAL,NULL);
	APP_ERROR_CHECK(err_code);
}

void TIMER_LCDStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(lcd_timer_id);
	APP_ERROR_CHECK(err_code);
}

void TIMER_LCDHandler(void * p_context)
{	
	LCD.UpdateFlg = true;
}

void TIMER_ButtonStart(void)
{
	uint32_t err_code;
	err_code = app_timer_start(button_timer_id,BUTTON_TIMEOUT_INTERVAL,NULL);
	APP_ERROR_CHECK(err_code);
}

void TIMER_ButtonStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(button_timer_id);
	APP_ERROR_CHECK(err_code);
}

void TIMER_ButtonHandler(void * p_context)
{
//	TIMER_Debug("[TIMER] TIMER_ButtonHandler  \r\n");
	KEY.PressFlg = true;
}


void TIMER_RxWindowStart(void)
{
	uint32_t err_code;

	if(RADIO.IM.RxWindowOnFlg)		//��ǰRX�򿪣���ر�
	{
		nrf_esb_stop_rx();	
		err_code = app_timer_start(rx_window_timer_id,APP_TIMER_TICKS(RX_WINDOW_OFF,APP_TIMER_PRESCALER),NULL);
		RADIO.IM.RxWindowOnFlg = false;	
		RADIO.IM.RxWindowAddFlg = false;			
	}
	else
	{
		my_esb_mode_change(NRF_ESB_MODE_PRX, RADIO.IM.RxChannal);
		nrf_esb_start_rx();	
		err_code = app_timer_start(rx_window_timer_id,APP_TIMER_TICKS(RX_WINDOW_ON,APP_TIMER_PRESCALER),NULL);
		RADIO.IM.RxWindowOnFlg = true;
		RADIO.IM.RxWindowAddFlg = false;
	}
	APP_ERROR_CHECK(err_code);
}

// ���������ã���Լ������ѭ������
void TIMER_RxWindowReset(void)
{
	RADIO.IM.RxWindowWaitFlg = false;
	RADIO.IM.RxWindowOnFlg = false;
	
	TIMER_RxWindowStop();
	TIMER_RxWindowStart();
}

void TIMER_RxWindowAdd(uint8_t time_ms)
{
	my_esb_mode_change(NRF_ESB_MODE_PRX, RADIO.IM.RxChannal);
	nrf_esb_start_rx();	
	
	TIMER_RxWindowStop();
	app_timer_start(rx_window_timer_id,APP_TIMER_TICKS(time_ms,APP_TIMER_PRESCALER),NULL);
	
	RADIO.IM.RxWindowOnFlg = true;
	RADIO.IM.RxWindowAddFlg = true;
}

void TIMER_RxWindowStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(rx_window_timer_id);
	APP_ERROR_CHECK(err_code);
}

void TIMER_RxWindowHandler(void * p_context)
{
	RADIO.IM.RxWindowWaitFlg = false;
	RADIO.IM.RxWindowAddFlg = false;
	TIMER_RxWindowStop();
	TIMER_RxWindowStart();
}

void TIMER_TxOvertimeStart(void)
{
	uint32_t err_code;
	err_code = app_timer_start(tx_overtime_timer_id,TX_OVERTIME_TIMEOUT_INTERVAL,NULL);
	APP_ERROR_CHECK(err_code);
}

void TIMER_TxOvertimeStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(tx_overtime_timer_id);
	APP_ERROR_CHECK(err_code);
}

void TIMER_TxOvertimeHandler(void * p_context)
{
	
}

void TIMER_SysStateStart(void)
{
//	uint32_t err_code;
//	err_code = app_timer_start(sys_state_timer_id,SYS_STATE_TIMEOUT_INTERVAL,NULL);
//	APP_ERROR_CHECK(err_code);
}

void TIMER_SysStateStop(void)
{
//	uint32_t err_code;
//	err_code = app_timer_stop(sys_state_timer_id);
//	APP_ERROR_CHECK(err_code);
}

void TIMER_SysStateHandler(void * p_context)
{
//	POWER_SysOnToSleep();
}

void TIMER_KeyPowerStart(void)
{
	uint32_t err_code;
	
	err_code = app_timer_start(key_power_timer_id,KEY_POWER_TIMEOUT_INTERVAL,NULL);
	APP_ERROR_CHECK(err_code);
}


void TIMER_KeyPowerStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(key_power_timer_id);
	APP_ERROR_CHECK(err_code);
}


void TIMER_KeyPowerHandler(void * p_context)
{
	if(0x00 == nrf_gpio_pin_read(KEY_PWR))
	{	
		switch(POWER.SysState)
		{
			case SYS_ON:
			case SYS_TEST:
				POWER_SysOnToOff();
				break;
			case SYS_OFF:
				POWER_SysOffToOn();
				break;
			default:
				break;
		}
	}
}

void TIMER_ADCStart(void)
{
	uint32_t err_code;
	
	// ���״ο������ӿ�ɼ��ٶ�
	if(ADC.FirstSampleFlg)
	{
		err_code = app_timer_start(adc_timer_id,ADC_FIRST_SAMPLE_TIMEOUT_INTERVAL,NULL);
	}
	else	
	{
		err_code = app_timer_start(adc_timer_id,ADC_TIMEOUT_INTERVAL,NULL);
	}
	APP_ERROR_CHECK(err_code);
}

void TIMER_ADCStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(adc_timer_id);
	APP_ERROR_CHECK(err_code);
}

void TIMER_ADCHandler(void * p_context)
{
	ADC.SampleFlg = true;
	TIMER_ADCStart();
}

void TIMER_TxAttendStart(void)
{
	uint32_t err_code;
	uint32_t random_delay = 0;
	random_delay = (uint32_t)(GetRandomNumber() / 5);		// �����ʱ0~51ms
	
//	err_code = app_timer_start(tx_attend_timer_id,TX_ATTEND_TIMEOUT_INTERVAL ,NULL);
	err_code = app_timer_start(tx_attend_timer_id,APP_TIMER_TICKS(1075 + random_delay,APP_TIMER_PRESCALER)  ,NULL);
	APP_ERROR_CHECK(err_code);
}


void TIMER_TxAttendStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(tx_attend_timer_id);
	APP_ERROR_CHECK(err_code);
}


void TIMER_TxAttendHandler(void * p_context)
{
	ATTEND.StartTxflg = true;
}

void TIMER_SysOffStart(void)
{
	uint32_t err_code;
	err_code = app_timer_start(sys_off_timer_id,SYS_OFF_TIMEOUT_INTERVAL,NULL);
	APP_ERROR_CHECK(err_code);
}

void TIMER_SysOffStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(sys_off_timer_id);
	APP_ERROR_CHECK(err_code);
}

void TIMER_SysOffHandler(void * p_context)
{

}

void TIMER_WaitDataStart(uint8_t time_ms)
{
	uint32_t err_code;
	err_code = app_timer_start(wait_data_timer_id,APP_TIMER_TICKS(time_ms,APP_TIMER_PRESCALER),NULL);
	APP_ERROR_CHECK(err_code);
}

void TIMER_WaitDataStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(wait_data_timer_id);
	APP_ERROR_CHECK(err_code);
}

void TIMER_WaitDataHandler(void * p_context)
{
	TIMER_RxWindowAdd(RX_WINDOW_ADD_WAIT_DATA);			//����RX���ڣ��ȴ���Ч����
}

void TIMER_RetransmitStart(void)
{
	uint32_t err_code;
	err_code = app_timer_start(retransmit_timer_id,RETRANSMIT_TIMEOUT_INTERVAL,NULL);
	APP_ERROR_CHECK(err_code);
}

void TIMER_RetransmitStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(retransmit_timer_id);
	APP_ERROR_CHECK(err_code);
}

void TIMER_RetransmitHandler(void * p_context)
{
	RADIO.IM.ReTxCount++;
	
	if(true == RADIO.IM.TxSucFlg)		//���ͳɹ����յ�ACK��
	{
		RADIO.IM.TxSucFlg = false;		//���־
		RADIO.IM.TxIngFlg = false;
		RADIO.IM.ReTxCount = 0;		
		TIMER_RetransmitStop();
		RADIO_TxSuccess();			//���ͳɹ�������
	}
	else if(RADIO.IM.ReTxCount > NRF_MAX_NUMBER_OF_RETRANSMITS)	//�ﵽ����ط�����
	{
		RADIO.IM.TxSucFlg = false;		//���־
		RADIO.IM.TxIngFlg = false;
		RADIO.IM.ReTxCount = 0;		
		TIMER_RetransmitStop();
		RADIO_TxFailed();			//����ʧ�ܴ�����
	}
	else							//�����ط�
	{
		RADIO_StartLinkTx();			//����Ӳ�����ͣ�����APP.TX�ṹ���������	
	}
}

void TIMER_TxResultDisplayStart(void)
{
	uint32_t err_code;
	err_code = app_timer_start(tx_result_display_timer_id,TX_RESULT_DISPLAY_TIMEOUT_INTERVAL,NULL);
	APP_ERROR_CHECK(err_code);
}

void TIMER_TxResultDisplayStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(tx_result_display_timer_id);
	APP_ERROR_CHECK(err_code);
}

void TIMER_TxResultDisplayHandler(void * p_context)
{
	LCD.DATA.SendResultState = SEND_RESULT_CLEAR;
	LCD.DATA.RefreshFlg |= LCD_REFRESH_RESULT;
	APP.QUE.KeySendAllowFlg = true;					// ����������
}

void TIMER_DisVerStart(void)
{
	uint32_t err_code;
	err_code = app_timer_start(display_version_timer_id,DISPLAY_VERSION_TIMEOUT_INTERVAL,NULL);
	APP_ERROR_CHECK(err_code);
}

void TIMER_DisVerStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(display_version_timer_id);
	APP_ERROR_CHECK(err_code);
}

void TIMER_DisVerHandler(void * p_context)
{
	LCD.DisType = LCD_DIS_UPDATE;
}


void TIMER_SendAllowStart(void)
{
	uint32_t err_code;
	
	err_code = app_timer_start(send_allow_timer_id,SEND_ALLOW_TIMEOUT_INTERVAL,NULL);
	APP_ERROR_CHECK(err_code);
}

void TIMER_SendAllowStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(send_allow_timer_id);
	APP_ERROR_CHECK(err_code);
}

void TIMER_SendAllowHandler(void * p_context)
{
	APP.QUE.KeySendAllowFlg = true;
}

void TIMER_TxRandomDelayStart(void)
{
	uint32_t err_code;
	uint32_t random_delay;
	
	random_delay = 5 + GetRandomNumber() / 5;		
	
	err_code = app_timer_start(tx_random_delay_timer_id,APP_TIMER_TICKS(random_delay,APP_TIMER_PRESCALER)  ,NULL);
	APP_ERROR_CHECK(err_code);
}


void TIMER_TxRandomDelayStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(tx_random_delay_timer_id);
	APP_ERROR_CHECK(err_code);
}


void TIMER_TxRandomDelayHandler(void * p_context)
{
	RADIO_StartLinkTx();
}

//void TIMER_WatchDogStart(void)
//{
//	uint32_t err_code;
//	err_code = app_timer_start(watch_dog_timer_id,WATCH_DOG_TIMEOUT_INTERVAL,NULL);
//	APP_ERROR_CHECK(err_code);
//}

//void TIMER_WatchDogStop(void)
//{
//	uint32_t err_code;
//	err_code = app_timer_stop(watch_dog_timer_id);
//	APP_ERROR_CHECK(err_code);
//}

//void TIMER_WatchDogHandler(void * p_context)
//{
//	WDT.FeedFlg = true;
//}
