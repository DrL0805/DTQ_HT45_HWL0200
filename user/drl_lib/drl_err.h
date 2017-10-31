#ifndef __DRL_ERR_H
#define __DRL_ERR_H	 

// Includes -----------------------------------------------------------
#include "main.h"

// Typedefs -----------------------------------------------------------
typedef struct
{
	bool		HintFlg;
	uint32_t 	ErrState;	
	uint32_t    ErrData[32];
}drERR_PATAMETERS_T;


// Defines ------------------------------------------------------------
		
#define drERROR_CHECK(ERR_CODE)                             \
    do                                                      \
    {                                                       \
        const uint32_t LOCAL_ERR_CODE = (ERR_CODE);         \
        if (LOCAL_ERR_CODE != drERROR_SUCCESS)                  \
        {                                                   \
            drERR_ErrCheck(LOCAL_ERR_CODE);              \
        }                                                   \
    } while (0)
	

#define drERROR_BASE_NUM					(0x00)
	
// 综合相关ERR_CODE
#define drERROR_SYS_BASE_NUM				(0x00)
#define drERROR_SUCCESS						(drERROR_BASE_NUM + drERROR_SYS_BASE_NUM + 0)

// 	13.56M相关ERR_CODE
#define drERROR_1356M_BASE_NUM				(0x10)
#define drERROR_1356M_SUCCESS				(drERROR_SUCCESS)
#define drERROR_1356M_CRC_ERR				(drERROR_BASE_NUM + drERROR_1356M_BASE_NUM + 1)		// CRC校验错误
#define drERROR_1356M_ID_ERR				(drERROR_BASE_NUM + drERROR_1356M_BASE_NUM + 2)		// UID读取失败
#define drERROR_1356M_LEN_ERR				(drERROR_BASE_NUM + drERROR_1356M_BASE_NUM + 3)		// 读取数据长度异常

	
// Functions ----------------------------------------------------------
extern uint32_t drERR_Init(void);
extern void drERR_ErrCheck(uint32_t err_code);	
extern void drERR_ErrHandler(void);

// Globals ------------------------------------------------------------
 				
extern drERR_PATAMETERS_T			ERR;

#endif














