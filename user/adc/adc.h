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
	bool 	SampleFlg;			//ADC采集标志
	bool	FirstSampleFlg;		//ADC开机时的第一次加快采集速度
	
	uint16_t LatestADCVal;		//最新采集到的ADC值
}adc_struct_t;


extern adc_struct_t				ADC;

void ADC_Init(void);
void ADC_Update(void);
void ADC_StartSample(void);
void ADC_LcdDisValue(void);


#endif 

