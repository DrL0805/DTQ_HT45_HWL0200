#include "timers.h"

#define TIMER_DEBUG
#ifdef TIMER_DEBUG
#define TIMER_Debug  printf   
#else  
#define TIMER_Debug(...)                    
#endif 

//��ʱ���궨��
#define APP_TIMER_PRESCALER     0			// 1tick  = 32.768KHz / (APP_TIMER_PRESCALER+1),����Ϊ32��Լ1msһ��tick
											// ��Ƶ = 0 ��1tick=30.517us����Ƶ = 9, 1tick = 305.17us
#define APP_TIMER_OP_QUEUE_SIZE 7

#define NFC_TIMEOUT_INTERVAL     					APP_TIMER_TICKS(500, 	APP_TIMER_PRESCALER)
#define TX_OVERTIME_TIMEOUT_INTERVAL     			APP_TIMER_TICKS(15,		APP_TIMER_PRESCALER)
#define ADC_TIMEOUT_INTERVAL    					APP_TIMER_TICKS(997,APP_TIMER_PRESCALER)		//42 ������Ϊ������Ϊ��ʹADC�ɼ���������������ܿ�
#define ADC_FIRST_SAMPLE_TIMEOUT_INTERVAL    		APP_TIMER_TICKS(42,APP_TIMER_PRESCALER)		//42 ������Ϊ������Ϊ��ʹADC�ɼ���������������ܿ�


APP_TIMER_DEF(rx_window_timer_id);				/* RX�������򿪹ر� */
APP_TIMER_DEF(adc_timer_id);					/* ADC�ɼ���ʱ�� */
APP_TIMER_DEF(wait_data_timer_id);				/* �յ�ǰ��֡�󣬴�RX�����¼�����������Ч���� */
APP_TIMER_DEF(retransmit_timer_id);				/* ��·����ط���ʱ�� */
APP_TIMER_DEF(tx_random_delay_timer_id);		/* ���������ʱ */

TIMER_PARAMETERS_T	TIMER;

uint32_t TIMERS_Init(void)
{
	uint32_t err_code;
	
	TIMER.RetransmitEventFlg = false;
	
	//������ʱ��
	APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);
	
	// ѭ����ʱ�� ------------------------------------------------------------------------
	err_code = app_timer_create(&rx_window_timer_id,APP_TIMER_MODE_REPEATED,TIMER_RxWindowHandler);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
	
	// ���ζ�ʱ�� ------------------------------------------------------------------------
	err_code = app_timer_create(&adc_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_ADCHandler);	// ADC�ɼ������Σ�ÿ�βɼ��궼��Ҫ���¿�����ʱ��
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);

	err_code = app_timer_create(&wait_data_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_WaitDataHandler);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
	
	err_code = app_timer_create(&tx_random_delay_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_TxRandomDelayHandler);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
	
	err_code = app_timer_create(&retransmit_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_RetransmitHandler);	// �ط���ʱ����ÿ�����¿�ʼһ�����ֵ
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);	

	return drERROR_SUCCESS;
}

void TIMER_EventHandler(void)
{
	if(TIMER.RetransmitEventFlg)
	{
		TIMER.RetransmitEventFlg = false;
		
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
			RADIO_StartLinkTx(TX_DATA_TYPE_ANSWER);			//����Ӳ�����ͣ�����APP.TX�ṹ���������	
			TIMER_RetransmitStart();
		}			
	}
}

void TIMER_RxWindowStart(void)
{
	uint32_t err_code;

	if(RADIO.IM.RxWindowOnFlg)		//��ǰRX�򿪣���ر�
	{	
		my_esb_mode_change(NRF_ESB_MODE_PRX_STOP, RADIO.IM.RxChannal);
		err_code = app_timer_start(rx_window_timer_id,APP_TIMER_TICKS(RX_WINDOW_OFF,APP_TIMER_PRESCALER),NULL);
		drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
		RADIO.IM.RxWindowOnFlg = false;	
		RADIO.IM.RxWindowAddFlg = false;			
	}
	else
	{
		my_esb_mode_change(NRF_ESB_MODE_PRX_START, RADIO.IM.RxChannal);	
		err_code = app_timer_start(rx_window_timer_id,APP_TIMER_TICKS(RX_WINDOW_ON,APP_TIMER_PRESCALER),NULL);
		drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
		RADIO.IM.RxWindowOnFlg = true;
		RADIO.IM.RxWindowAddFlg = false;
	}
}

// ���������ã���Լ������ѭ������
void TIMER_RxWindowReset(void)
{
	RADIO.IM.RxWindowAddFlg = false;		// ������ӽ��մ��ȴ���Ч����/ACK��־	
	RADIO.IM.RxWindowWaitFlg = false;
	RADIO.IM.RxWindowOnFlg = false;
	
	TIMER_RxWindowStop();
	TIMER_RxWindowStart();
}

void TIMER_RxWindowAdd(uint8_t time_ms)
{
	uint32_t err_code;
	
	my_esb_mode_change(NRF_ESB_MODE_PRX_START, RADIO.IM.RxChannal);
	
	TIMER_RxWindowStop();
	err_code = app_timer_start(rx_window_timer_id,APP_TIMER_TICKS(time_ms,APP_TIMER_PRESCALER),NULL);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
	
	RADIO.IM.RxWindowOnFlg = true;
	RADIO.IM.RxWindowAddFlg = true;
}

void TIMER_RxWindowStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(rx_window_timer_id);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
}

void TIMER_RxWindowHandler(void * p_context)
{
	RADIO.IM.RxWindowWaitFlg = false;
	RADIO.IM.RxWindowAddFlg = false;
	TIMER_RxWindowStop();
	TIMER_RxWindowStart();
}

void TIMER_ADCStart(void)
{
	uint32_t err_code;
	
	// ���״ο������ӿ�ɼ��ٶ�
	if(ADC.FirstSampleFlg)
	{
		err_code = app_timer_start(adc_timer_id,ADC_FIRST_SAMPLE_TIMEOUT_INTERVAL,NULL);
		drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
	}
	else	
	{
		err_code = app_timer_start(adc_timer_id,ADC_TIMEOUT_INTERVAL,NULL);
		drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
	}
}

void TIMER_ADCStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(adc_timer_id);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
}

void TIMER_ADCHandler(void * p_context)
{
	ADC.SampleFlg = true;
	TIMER_ADCStart();
}

void TIMER_WaitDataStart(uint8_t time_ms)
{
	uint32_t err_code;

	// RTC 1tick = 30.517us��������10��Ƶ��Ҳ����1tick = 305.17us
	// ��app_timer_start()Ҫ��timeout_ticks����5��
	if(time_ms < 2)
		time_ms = 2;

	err_code = app_timer_start(wait_data_timer_id,APP_TIMER_TICKS(time_ms,APP_TIMER_PRESCALER),NULL);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
}

void TIMER_WaitDataStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(wait_data_timer_id);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
}

void TIMER_WaitDataHandler(void * p_context)
{
	TIMER_RxWindowAdd(RX_WINDOW_ADD_WAIT_DATA);			//����RX���ڣ��ȴ���Ч����
}

void TIMER_RetransmitStart(void)
{
	uint32_t err_code;
	uint32_t random_delay;	
	
	random_delay = 10 + (GetRandomNumber() >> 2);	// ����4
	
	err_code = app_timer_start(retransmit_timer_id,APP_TIMER_TICKS(random_delay,APP_TIMER_PRESCALER)  ,NULL);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
}

void TIMER_RetransmitStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(retransmit_timer_id);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
}

void TIMER_RetransmitHandler(void * p_context)
{
	TIMER.RetransmitEventFlg = true;
}

void TIMER_TxRandomDelayStart(void)
{
	uint32_t err_code;								
	uint32_t random_delay;							
	
	random_delay = 6 + (GetRandomNumber() >> 2);	// ����2	
	
	err_code = app_timer_start(tx_random_delay_timer_id,APP_TIMER_TICKS(random_delay,APP_TIMER_PRESCALER)  ,NULL);
	APP_ERROR_CHECK(err_code);

	
//	uint32_t err_code;
//	uint32_t random_delay = 0;

//	// tick= 30.517us�������ʱ��305.17us~62.56ms��
//	random_delay = 10 +  GetRandomNumber() * 8;	
//	err_code = app_timer_start(tx_random_delay_timer_id,random_delay,NULL);
//	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
}


void TIMER_TxRandomDelayStop(void)
{
	uint32_t err_code;
	err_code = app_timer_stop(tx_random_delay_timer_id);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
}

void TIMER_TxRandomDelayHandler(void * p_context)
{
	RADIO_StartLinkTx(TX_DATA_TYPE_ECHO);
}











