// Revision record ----------------------------------------------------

// Includes -----------------------------------------------------------
#include "drl_err.h"

// Functions ----------------------------------------------------------


// Globals ------------------------------------------------------------
drERR_PATAMETERS_T			ERR;

// Locals -------------------------------------------------------------

drErrType drERR_Init(void)
{
	drTIM_ERRStart();
	return drERROR_SUCCESS;
}

void drERR_ErrCheck(drErrType err_code)
{
	drErrType i;
	
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
	drErrType i;
	
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
					LCD_DisDigit_5(40, ERR.ErrData[i]);
					break;
				}
			}
		}		
	}
}










 
 

 
 
