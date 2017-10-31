// Revision record ----------------------------------------------------

// Includes -----------------------------------------------------------
#include "led.h"

// Functions ----------------------------------------------------------
void LED_ParInit(void);
void LED_PerInit(void);

// Globals ------------------------------------------------------------

// Locals -------------------------------------------------------------



uint32_t LED_Init(void)
{
	nrf_gpio_cfg_output(LED_0);
	
	return drERROR_SUCCESS;
}













 
 

 
 
