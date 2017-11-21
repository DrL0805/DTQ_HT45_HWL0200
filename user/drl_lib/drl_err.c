// Revision record ----------------------------------------------------

// Includes -----------------------------------------------------------
#include "drl_err.h"

// Functions ----------------------------------------------------------


// Globals ------------------------------------------------------------
drERR_PATAMETERS_T			drERR;

// Locals -------------------------------------------------------------

drErrType drERR_Init(void)
{
	#if USE_ERR_CHECK
	
	drTIM_ERRStart();
	drTIMER_ERRStart(drTIMER_PERIOD_ERR);
	
	#endif
	
	return drERROR_SUCCESS;
}

void drERR_ErrCheck(drErrType err_code)
{
	drErrType i;
	drErrType ErrCode;
	
	switch(err_code)
	{
		case drERROR_1356M_ID_ERR:
			NVIC_SystemReset();				//复位			
			break;
		case drERROR_1356M_CRC_ERR:
		case drERROR_1356M_LEN_ERR:
			break;
		default:		
			break;
	}
	
	// 若错误码已存在，Cnt++
	for(i = 0;i < drERR.ErrNum;i++)
	{
		if(err_code == drERR.Err[i].Code)
		{
			drERR.Err[i].Cnt++;
			return;
		}
	}
	
	// 若为新的错误码，存入
	drERR.Err[drERR.ErrNum].Code = err_code;
	drERR.Err[drERR.ErrNum].Cnt++;
	drERR.ErrNum++;	
}

void drERR_ErrHandler(void)
{
	char * ErrString = " Error:					";
	drErrType i = 0;
	
	if(drERR.HintFlg)
	{
		drERR.HintFlg = false;
		
//		LCD_DRV_DisplayN(16, 16, (uint8_t *)ErrString);
		
		// LCD显示错误码和次数
		for(i = 0;i < drERR.ErrNum;i++)
		{
			LCD_DisDigit_5(16*(i+1)+0, drERR.Err[i].Code);	
			LCD_DisDigit_5(16*(i+1)+8, drERR.Err[i].Cnt);				
		}
	}	
}










 
 

 
 
