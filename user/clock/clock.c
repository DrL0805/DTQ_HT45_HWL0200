

/* Includes -----------------------------------------------------*/
#include "clock.h"

clock_struct_t	CLOCK;

/* Functions ----------------------------------------------------*/
void RTC_calibrate_handler(nrf_drv_clock_evt_type_t event);


uint32_t CLOCK_Init(void)
{
	uint32_t err_code;
	
    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);
	
	drERROR_CHECK(CLOCK_LFCLKStart());			//���������ڲ�ʱ��
	drERROR_CHECK(CLOCK_HFCLKStart());
	drERROR_CHECK(CLOCK_RTCCalibrate());		//RTCУ׼
	
	return drERROR_CLK_SUCCESS;
}

uint32_t CLOCK_HFCLKStart(void)
{
	uint16_t i = 0;
	if(!nrf_drv_clock_hfclk_is_running())		//ȷ��ʱ�Ӳ����ظ�����
	{
		nrf_drv_clock_hfclk_request(NULL);	
		while(false == nrf_drv_clock_hfclk_is_running())	
		{
			if(++i > 0x0FFF)	//�ȴ��������
				return drERROR_CLK_HFCLK_START_TIMEOUT;
		}		
	}
	
	return drERROR_CLK_SUCCESS;
}

uint32_t CLOCK_HFCLKStop(void)
{
	if(nrf_drv_clock_hfclk_is_running())		
	{
		nrf_drv_clock_hfclk_release();
	}
	
	return drERROR_CLK_SUCCESS;
}

uint32_t CLOCK_LFCLKStart(void)
{
	/* ʹ��SDK��timerʱ��Ҫ�����ڲ���Ƶʱ�� */
	if(!nrf_drv_clock_lfclk_is_running())
	{
		nrf_drv_clock_lfclk_request(NULL);
	}
	
	return drERROR_CLK_SUCCESS;
}

uint32_t CLOCK_LFCLKStop(void)
{
	if(!nrf_drv_clock_lfclk_is_running())
	{
		nrf_drv_clock_lfclk_release();
	}
	
	return drERROR_CLK_SUCCESS;
}


uint32_t CLOCK_RTCCalibrate(void)
{
	//ע�⣺�ڲ�RCʱ��У׼ʱ�����뱣֤�ⲿ����ʱ���ǿ�����
	//0.25 * 40 = 10S У׼һ��
	nrf_drv_clock_calibration_start(40,RTC_calibrate_handler);
	
	return drERROR_CLK_SUCCESS;
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
			nrf_drv_clock_calibration_start(40,RTC_calibrate_handler);	//ѭ��У׼
    		break;
		case NRF_DRV_CLOCK_EVT_CAL_ABORTED:
			nrf_drv_clock_calibration_start(40,RTC_calibrate_handler);
    		break;
    	default:
    		break;
    }
}






