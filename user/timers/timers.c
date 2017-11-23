#include "timers.h"

#define TIMER_DEBUG
#ifdef TIMER_DEBUG
#define TIMER_Debug  printf   
#else  
#define TIMER_Debug(...)                    
#endif 

//定时器宏定义
#define APP_TIMER_PRESCALER     0			// 1tick  = 32.768KHz / (APP_TIMER_PRESCALER+1),设置为32即约1ms一个tick
											// 分频 = 0 ，1tick=30.517us，分频 = 9, 1tick = 305.17us
#define APP_TIMER_OP_QUEUE_SIZE 7

#define NFC_TIMEOUT_INTERVAL     					APP_TIMER_TICKS(500, 	APP_TIMER_PRESCALER)
#define TX_OVERTIME_TIMEOUT_INTERVAL     			APP_TIMER_TICKS(15,		APP_TIMER_PRESCALER)
#define ADC_TIMEOUT_INTERVAL    					APP_TIMER_TICKS(997,APP_TIMER_PRESCALER)		//42 不设置为整数是为了使ADC采集尽量与其他外设避开
#define ADC_FIRST_SAMPLE_TIMEOUT_INTERVAL    		APP_TIMER_TICKS(42,APP_TIMER_PRESCALER)		//42 不设置为整数是为了使ADC采集尽量与其他外设避开


APP_TIMER_DEF(rx_window_timer_id);				/* RX窗正常打开关闭 */
APP_TIMER_DEF(adc_timer_id);					/* ADC采集定时器 */
APP_TIMER_DEF(wait_data_timer_id);				/* 收到前导帧后，打开RX窗等下即将到来的有效数据 */
APP_TIMER_DEF(retransmit_timer_id);				/* 链路层的重发定时器 */
APP_TIMER_DEF(tx_random_delay_timer_id);		/* 随机发送延时 */

TIMER_PARAMETERS_T	TIMER;

uint32_t TIMERS_Init(void)
{
	uint32_t err_code;
	
	TIMER.RetransmitEventFlg = false;
	
	//创建定时器
	APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);
	
	// 循环定时器 ------------------------------------------------------------------------
	err_code = app_timer_create(&rx_window_timer_id,APP_TIMER_MODE_REPEATED,TIMER_RxWindowHandler);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
	
	// 单次定时器 ------------------------------------------------------------------------
	err_code = app_timer_create(&adc_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_ADCHandler);	// ADC采集，单次，每次采集完都需要重新开启定时器
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);

	err_code = app_timer_create(&wait_data_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_WaitDataHandler);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
	
	err_code = app_timer_create(&tx_random_delay_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_TxRandomDelayHandler);
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);
	
	err_code = app_timer_create(&retransmit_timer_id,APP_TIMER_MODE_SINGLE_SHOT,TIMER_RetransmitHandler);	// 重发定时器，每次重新开始一个随机值
	drERROR_CHECK(drERROR_TIMER_BASE_NUM+err_code);	

	return drERROR_SUCCESS;
}

void TIMER_EventHandler(void)
{
	if(TIMER.RetransmitEventFlg)
	{
		TIMER.RetransmitEventFlg = false;
		
		RADIO.IM.ReTxCount++;
		
		if(true == RADIO.IM.TxSucFlg)		//发送成功（收到ACK）
		{
			RADIO.IM.TxSucFlg = false;		//清标志
			RADIO.IM.TxIngFlg = false;
			RADIO.IM.ReTxCount = 0;		
			TIMER_RetransmitStop();
			RADIO_TxSuccess();			//发送成功处理函数	
		}
		else if(RADIO.IM.ReTxCount > NRF_MAX_NUMBER_OF_RETRANSMITS)	//达到最大重发次数
		{
			RADIO.IM.TxSucFlg = false;		//清标志
			RADIO.IM.TxIngFlg = false;
			RADIO.IM.ReTxCount = 0;		
			TIMER_RetransmitStop();
			RADIO_TxFailed();			//发送失败处理函数
		}
		else							//否则重发
		{
			RADIO_StartLinkTx(TX_DATA_TYPE_ANSWER);			//启动硬件发送，发送APP.TX结构体里的数据	
			TIMER_RetransmitStart();
		}			
	}
}

void TIMER_RxWindowStart(void)
{
	uint32_t err_code;

	if(RADIO.IM.RxWindowOnFlg)		//当前RX打开，则关闭
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

// 接收器重置，按约定比例循环开关
void TIMER_RxWindowReset(void)
{
	RADIO.IM.RxWindowAddFlg = false;		// 清除增加接收窗等待有效数据/ACK标志	
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
	
	// 若首次开机，加快采集速度
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

	// RTC 1tick = 30.517us，我做了10分频，也就是1tick = 305.17us
	// 而app_timer_start()要求timeout_ticks大于5，
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
	TIMER_RxWindowAdd(RX_WINDOW_ADD_WAIT_DATA);			//增加RX窗口，等待有效数据
}

void TIMER_RetransmitStart(void)
{
	uint32_t err_code;
	uint32_t random_delay;	
	
	random_delay = 10 + (GetRandomNumber() >> 2);	// 除以4
	
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
	
	random_delay = 6 + (GetRandomNumber() >> 2);	// 除以2	
	
	err_code = app_timer_start(tx_random_delay_timer_id,APP_TIMER_TICKS(random_delay,APP_TIMER_PRESCALER)  ,NULL);
	APP_ERROR_CHECK(err_code);

	
//	uint32_t err_code;
//	uint32_t random_delay = 0;

//	// tick= 30.517us，随机延时：305.17us~62.56ms，
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











