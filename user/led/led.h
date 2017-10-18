#ifndef __LED_H
#define __LED_H	 

// Includes -----------------------------------------------------------
#include "nrf_gpio.h"
#include "main.h"

// Defines ------------------------------------------------------------
#define LED_SUPORT		(0)
#define LED_0 			(30)

#if LED_SUPORT
#define LED_ON(LED_PIN)		nrf_gpio_pin_clear(LED_PIN)
#define LED_OFF(LED_PIN)	nrf_gpio_pin_set(LED_PIN)
#define LED_TOG(LED_PIN)	nrf_gpio_pin_toggle(LED_PIN)
#else
#define LED_ON(...)		
#define LED_OFF(...)	
#define LED_TOG(...)	
#endif
					

// Typedefs -----------------------------------------------------------


// Functions ----------------------------------------------------------
extern void LED_Init(void);

// Globals ------------------------------------------------------------
 				    
#endif














