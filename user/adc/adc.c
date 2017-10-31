
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
		
		//���ɼ�20�����ݣ�ͷβ��ȥ��5����ȡ�м�10�ε�ƽ��ֵ��Ϊ�ɼ����
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
		//ADC�ɼ�ʱ��������󹦺���������д���ʹ�ɼ��������׼ȷ
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

//ð������
void bubbleSort(int16_t *buf, uint16_t len)
{  
    uint16_t    i, j;  
    bool    	flag = 1;   
	
	//ֻҪflag����һ����ѭ����������ʱ��ֵΪfalse����˵���Ѿ��ź��򣬲��ü���ѭ��
    for (i = 0; i < len && flag; i++)  
    {  
        flag = false;     		   
        for (j = len - 1; j > i; j--)  
        {  
            if (buf[j] < buf[j-1])  
            {  
                swap(&buf[j], &buf[j-1]);  
                flag = true;  							 //����н������ͽ���Ǳ�����1  
            }  
        }  
    } 
} 

/*
	����2900����ʾ3��
	2900~2800����ʾ2��
	2800~2700����ʾ1��
	2700~2650����ʾ0������
	С��2650���Զ��ػ�
*/
void ADC_LcdDisValue(void)
{
	//"ʩ����"ԭ��
	//ע�⣺��һ����ʾ��ʱ������"ʩ����"����Ϊ�п��ܲɼ��ĵ�ѹ�պò��ڷ�Χ�ڣ����²���ʾ	
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






