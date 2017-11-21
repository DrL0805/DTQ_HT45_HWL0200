#ifndef __DRL_COMMON_H
#define __DRL_COMMON_H	 

// Includes -----------------------------------------------------------
#include "main.h"

// Typedefs -----------------------------------------------------------


// 检测是否为2的指数
#define drIS_POWER_OF_TWO(A) ( ((A) != 0) && ((((A) - 1) & (A)) == 0) )

// 两个值中取较大值
#define drMAX(A,B)		((A) > (B) ? (A) : (B))

// 两个值中取较小值
#define drMIN(A,B)		((A) < (B) ? (A) : (B))


extern bool drCMN_ArrayCmp(uint8_t *str1, uint8_t *str2, uint8_t len);
extern uint8_t drCMN_XorCal(uint8_t * dat,uint16_t length);
extern bool drCMN_BoolFlgCheck(bool*	BoolFlg);


#endif














