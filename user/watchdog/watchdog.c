#include "watchdog.h"


nrf_drv_wdt_channel_id	 m_channel_id;
WATCHDOG_PAR_T			 WDT;

void wdt_event_handler(void)
{
//	DEBUG_UART_1("wdt_handler \r\n");
    
    //NOTE: The max amount of time we can spend in WDT interrupt is two cycles of 32768[Hz] clock - after that, reset occurs
} 


uint32_t WDT_Init(void)
{	
	#if USE_WATCH_DOG
	
	uint32_t err_code = NRF_SUCCESS;
	
	//�������ã����Ź�2�볬ʱ��ÿ1��ιһ�ι�
    nrf_drv_wdt_config_t config = NRF_DRV_WDT_DEAFULT_CONFIG;
    err_code = nrf_drv_wdt_init(&config, wdt_event_handler);
    APP_ERROR_CHECK(err_code);
    err_code = nrf_drv_wdt_channel_alloc(&m_channel_id);
    APP_ERROR_CHECK(err_code);
    nrf_drv_wdt_enable();	
	
	//����ι����ʱ��
	TIMER_WatchDogStart();
//	drTIM_WDTStart();
	WDT.FeedFlg = false;
	
	#endif
	
	return drERROR_SUCCESS;
}


void WDT_FeedDog(void)
{
	if(WDT.FeedFlg)
	{
		WDT.FeedFlg = false;
		nrf_drv_wdt_feed();
	}
}

















