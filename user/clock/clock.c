

/* Includes -----------------------------------------------------*/
#include "clock.h"

clock_struct_t	CLOCK;

/* Functions ----------------------------------------------------*/
void RTC_calibrate_handler(nrf_drv_clock_evt_type_t event);


void CLOCK_Init(void)
{
	uint32_t err_code;
	
    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);
	
	CLOCK_LFCLKStart();			//开机开启内部时钟
	CLOCK_HFCLKStart();
	CLOCK_RTCCalibrate();		//RTC校准
}

void CLOCK_HFCLKStart(void)
{
	uint16_t i = 0;
	if(!nrf_drv_clock_hfclk_is_running())		//确保时钟不被重复开启
	{
		nrf_drv_clock_hfclk_request(NULL);	
		while(false == nrf_drv_clock_hfclk_is_running())	
		{
			if(++i > 0x0FFF)	//等待开启完成
				return;
		}		
	}
}

void CLOCK_HFCLKStop(void)
{
	if(nrf_drv_clock_hfclk_is_running())		
	{
		nrf_drv_clock_hfclk_release();
	}
}

void CLOCK_LFCLKStart(void)
{
	/* 使用SDK的timer时，要开启内部低频时钟 */
	if(!nrf_drv_clock_lfclk_is_running())
	{
		nrf_drv_clock_lfclk_request(NULL);
	}
}

void CLOCK_LFCLKStop(void)
{
	if(!nrf_drv_clock_lfclk_is_running())
	{
		nrf_drv_clock_lfclk_release();
	}
}


void CLOCK_RTCCalibrate(void)
{
	//注意：内部RC时钟校准时，必须保证外部晶体时钟是开启的
	//0.25 * 40 = 10S 校准一次
	nrf_drv_clock_calibration_start(40,RTC_calibrate_handler);
}

void RTC_calibrate_handler(nrf_drv_clock_evt_type_t event)
{
	switch (event)
    {
    	case NRF_DRV_CLOCK_EVT_HFCLK_STARTED:
    		break;
    	case NRF_DRV_CLOCK_EVT_LFCLK_STARTED:
    		break;
		case NRF_DRV_CLOCK_EVT_CAL_DONE:
			nrf_drv_clock_calibration_start(40,RTC_calibrate_handler);	//循环校准
    		break;
		case NRF_DRV_CLOCK_EVT_CAL_ABORTED:
			nrf_drv_clock_calibration_start(40,RTC_calibrate_handler);
    		break;
    	default:
    		break;
    }
}






