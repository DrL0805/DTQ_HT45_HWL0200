#ifndef __DRL_COMMON_H
#define __DRL_COMMON_H	 

// Includes -----------------------------------------------------------
#include "main.h"

// Typedefs -----------------------------------------------------------


// ����Ƿ�Ϊ2��ָ��
#define drIS_POWER_OF_TWO(A) ( ((A) != 0) && ((((A) - 1) & (A)) == 0) )

// ����ֵ��ȡ�ϴ�ֵ
#define drMAX(A,B)		((A) > (B) ? (A) : (B))

// ����ֵ��ȡ��Сֵ
#define drMIN(A,B)		((A) < (B) ? (A) : (B))


extern bool drCMN_ArrayCmp(uint8_t *str1, uint8_t *str2, uint8_t len);
extern uint8_t drCMN_XorCal(uint8_t * dat,uint16_t length);
extern bool drCMN_BoolFlgCheck(bool*	BoolFlg);


#endif














