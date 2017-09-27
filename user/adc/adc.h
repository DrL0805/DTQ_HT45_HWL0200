#ifndef __ADC_H
#define	__ADC_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "adc.h"
#include "nrf_drv_adc.h"
#include "nrf.h"
#include "nordic_common.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "app_util_platform.h"
#include "main.h"


typedef struct 
{
	bool 	SampleFlg;			//ADC�ɼ���־
	bool	FirstSampleFlg;		//ADC����ʱ�ĵ�һ�μӿ�ɼ��ٶ�
	
	uint16_t LatestADCVal;		//���²ɼ�����ADCֵ
}adc_struct_t;


extern adc_struct_t				ADC;

void ADC_Init(void);
void ADC_Update(void);
void ADC_StartSample(void);
void ADC_LcdDisValue(void);


#endif 

