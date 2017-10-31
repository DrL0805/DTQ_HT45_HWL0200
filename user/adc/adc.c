
/*-------------------------------- Include File -----------------------------------------*/
#include "adc.h"
/*-------------------------------- Macro definition -------------------------------------*/
#define ADC_BUFFER_SIZE 20  
/*-------------------------------- Local Variable ----------------------------------------*/
static nrf_adc_value_t       adc_buffer[ADC_BUFFER_SIZE]; /**< ADC buffer. */
static nrf_drv_adc_channel_t m_channel_config =  
{
	 {
		 {                                                       
			.resolution = NRF_ADC_CONFIG_RES_10BIT,                
			.input      = NRF_ADC_CONFIG_SCALING_SUPPLY_ONE_THIRD, 
			.reference  = NRF_ADC_CONFIG_REF_VBG,                  
			.ain        = NRF_ADC_CONFIG_INPUT_DISABLED                           
		 }
    }, 
	NULL
};

/*-------------------------------- Gocal Variable ----------------------------------------*/
adc_struct_t				ADC;

/*-------------------------------- Function Declaration ----------------------------------*/
static void adc_event_handler(nrf_drv_adc_evt_t const * p_event);
static void bubbleSort(int16_t *buf, uint16_t len);
static void swap(int16_t *a, int16_t *b);
/*----------------------------------------------------------------------------------------*/

uint32_t ADC_Init(void)
{
    ret_code_t ret_code;
    nrf_drv_adc_config_t config = NRF_DRV_ADC_DEFAULT_CONFIG;
	
    ret_code = nrf_drv_adc_init(&config, adc_event_handler);
    APP_ERROR_CHECK(ret_code);

    nrf_drv_adc_channel_enable(&m_channel_config);	
	
	ADC.FirstSampleFlg = true;
	
	return drERROR_SUCCESS;
}

void ADC_StartSample(void)
{
	nrf_drv_adc_buffer_convert(adc_buffer,ADC_BUFFER_SIZE);
	nrf_drv_adc_sample();
}
                            

/**
 * @brief ADC interrupt handler.
 */
static void adc_event_handler(nrf_drv_adc_evt_t const * p_event)
{
	uint8_t i;
	uint32_t adc_value = 0;

    if (p_event->type == NRF_DRV_ADC_EVT_DONE)
    {	
		bubbleSort(adc_buffer,ADC_BUFFER_SIZE);
		
		//共采集20个数据，头尾各去掉5个，取中间10次的平均值作为采集结果
		for(i = 5;i < ADC_BUFFER_SIZE -5;i++)
        {
			adc_value = adc_value + adc_buffer[i];
        }
		ADC.LatestADCVal = 3600 *  adc_value / (ADC_BUFFER_SIZE -10) / 1024;

		LCD.DATA.RefreshFlg |= LCD_REFRESH_BATTERY;
		
    }
}

void ADC_Update(void)
{	
	if(ADC.SampleFlg)
	{
		//ADC采集时，尽量与大功耗外设的运行错开，使采集结果更加准确
//		if(nrf_esb_is_idle() && (false == LCD.UpdateFlg))
		{		
			ADC.SampleFlg = false;
			ADC_StartSample();			
		}		
	}
}


void swap(int16_t *a, int16_t *b)  
{  
    uint16_t    temp;  
    temp = *a;  
      *a = *b;  
      *b = temp;  
}

//冒泡排序
void bubbleSort(int16_t *buf, uint16_t len)
{  
    uint16_t    i, j;  
    bool    	flag = 1;   
	
	//只要flag在下一次外循环条件检测的时候值为false，就说明已经排好序，不用继续循环
    for (i = 0; i < len && flag; i++)  
    {  
        flag = false;     		   
        for (j = len - 1; j > i; j--)  
        {  
            if (buf[j] < buf[j-1])  
            {  
                swap(&buf[j], &buf[j-1]);  
                flag = true;  							 //如果有交换，就将标记变量赋1  
            }  
        }  
    } 
} 

/*
	大于2900：显示3格
	2900~2800：显示2格
	2800~2700：显示1个
	2700~2650：显示0格并闪动
	小于2650：自动关机
*/
void ADC_LcdDisValue(void)
{
	//"施密特"原理，
	//注意：第一次显示的时候不能用"施密特"，因为有可能采集的电压刚好不在范围内，导致不显示	
	if(ADC.FirstSampleFlg)
	{
		if(ADC.LatestADCVal >= 2900)
		{
			LCD_DisplayBattery(BATTERY_LEVEL_3);
		}
		else if(ADC.LatestADCVal >= 2800 && ADC.LatestADCVal < 2900)
		{
			LCD_DisplayBattery(BATTERY_LEVEL_2);
		}
		else if(ADC.LatestADCVal >= 2700 && ADC.LatestADCVal < 2800)
		{
			LCD_DisplayBattery(BATTERY_LEVEL_1);
		}
		else if(ADC.LatestADCVal >= 2650 && ADC.LatestADCVal < 2700)
		{
			TIMER_LowPowerPromptStart();
			LCD_DisplayBattery(BATTERY_LEVEL_0);
		}	
		else if( ADC.LatestADCVal < 2630)
		{
			POWER_SysOnToOff();
		}
	}
	else	
	{
		if(ADC.LatestADCVal > 2920)
		{
			LCD_DisplayBattery(BATTERY_LEVEL_3);
		}
		else if(ADC.LatestADCVal > 2820 && ADC.LatestADCVal < 2880)
		{
			LCD_DisplayBattery(BATTERY_LEVEL_2);
		}		
		else if(ADC.LatestADCVal > 2720 && ADC.LatestADCVal < 2780)
		{
			LCD_DisplayBattery(BATTERY_LEVEL_1);
		}		
		else if(ADC.LatestADCVal > 2630 && ADC.LatestADCVal < 2680)
		{
			TIMER_LowPowerPromptStart();
			LCD_DisplayBattery(BATTERY_LEVEL_0);		
		}
		else if(ADC.LatestADCVal < 2630)
		{
			POWER_SysOnToOff();
		}
				
	}	
	
	ADC.FirstSampleFlg = false;
}






