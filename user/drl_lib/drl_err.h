#ifndef __DRL_ERR_H
#define __DRL_ERR_H	 

// Includes -----------------------------------------------------------
#include "main.h"

// Typedefs -----------------------------------------------------------

typedef		uint32_t 	drErrType;			

typedef struct
{
	bool				HintFlg;
	drErrType 			ErrState;	
	drErrType    		ErrData[32];
}drERR_PATAMETERS_T;


// Defines ------------------------------------------------------------
		
#define drERROR_CHECK(ERR_CODE)                             \
    do                                                      \
    {                                                       \
        const drErrType LOCAL_ERR_CODE = (ERR_CODE);         \
        if (LOCAL_ERR_CODE != drERROR_SUCCESS)                  \
        {                                                   \
            drERR_ErrCheck(LOCAL_ERR_CODE);              \
        }                                                   \
    } while (0)
	
	
// ERR_CODE基地址	
#define drERROR_BASE_NUM					(0x0000)
	
// 公共ERR_CODE
#define drERROR_SYS_BASE_NUM				(0x0000)
#define drERROR_SUCCESS						(drERROR_BASE_NUM + drERROR_SYS_BASE_NUM + 0)

// 时钟ERR_CODE
#define drERROR_CLK_BASE_NUM				(0x0100)		
#define drERROR_CLK_SUCCESS					(drERROR_SUCCESS)
#define drERROR_CLK_LFCLK_START_TIMEOUT		(drERROR_BASE_NUM + drERROR_CLK_BASE_NUM + 1)			
#define drERROR_CLK_HFCLK_START_TIMEOUT		(drERROR_BASE_NUM + drERROR_CLK_BASE_NUM + 2)	

	
// 	13.56M相关ERR_CODE
#define drERROR_1356M_BASE_NUM				(0x0200)
#define drERROR_1356M_SUCCESS				(drERROR_SUCCESS)
#define drERROR_1356M_CRC_ERR				(drERROR_BASE_NUM + drERROR_1356M_BASE_NUM + 1)		// CRC校验错误
#define drERROR_1356M_ID_ERR				(drERROR_BASE_NUM + drERROR_1356M_BASE_NUM + 2)		// UID读取失败
#define drERROR_1356M_LEN_ERR				(drERROR_BASE_NUM + drERROR_1356M_BASE_NUM + 3)		// 读取数据长度异常

// RADIO
#define drERROR_RADIO_BASE_NUM				(0x0300)		
#define drERROR_RADIO_SUCCESS					(drERROR_SUCCESS)
#define drERROR_RADIO_1							(drERROR_BASE_NUM + drERROR_RADIO_BASE_NUM + 1)			
#define drERROR_RADIO_2							(drERROR_BASE_NUM + drERROR_RADIO_BASE_NUM + 2)	
	
	
// TIMER
#define drERROR_TIMER_BASE_NUM				(0x0400)		
#define drERROR_TIMER_SUCCESS					(drERROR_SUCCESS)
#define drERROR_TIMER_1							(drERROR_BASE_NUM + drERROR_TIMER_BASE_NUM + 1)			
#define drERROR_TIMER_2							(drERROR_BASE_NUM + drERROR_TIMER_BASE_NUM + 2)	



// Functions ----------------------------------------------------------
extern drErrType drERR_Init(void);
extern void drERR_ErrCheck(uint32_t err_code);	
extern void drERR_ErrHandler(void);

// Globals ------------------------------------------------------------
 				
extern drERR_PATAMETERS_T			ERR;

#endif














