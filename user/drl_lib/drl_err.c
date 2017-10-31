// Revision record ----------------------------------------------------

// Includes -----------------------------------------------------------
#include "drl_err.h"

// Functions ----------------------------------------------------------


// Globals ------------------------------------------------------------
drERR_PATAMETERS_T			ERR;

// Locals -------------------------------------------------------------

uint32_t drERR_Init(void)
{

	return drERROR_SUCCESS;
}

void drERR_ErrCheck(uint32_t err_code)
{
	uint32_t i;
	
//	switch(err_code)
//	{
//		case 0:
//			break;
//		case 1:
//			break;
//		default:
//			break;
//	}
	
	for(i = 0;i < 32;i++)
	{
		// 检测当前bit是否保存有错误信息，若无，则保存
		if(!(ERR.ErrState & (0x01 << i)))
		{
			ERR.ErrState |= 0x01 << i;
			ERR.ErrData[i] = err_code;
			break;
		}
	}
}

void drERR_ErrHandler(void)
{
	char * ErrString = " Error:					";
	uint32_t i;
	
	if(ERR.HintFlg)
	{
		ERR.HintFlg = false;
		if(ERR.ErrState)
		{
			for(i = 0;i < 32;i++)
			{
				// 检测当前bit是否保存有错误信息，若有，则处理
				if(ERR.ErrState & (0x01 << i))
				{
					LCD_DRV_DisplayN(32, 16, (uint8_t *)ErrString);
					LCD_DisDigit(40, ERR.ErrData[i]);
					break;
				}
			}
		}		
	}
}










 
 

 
 
