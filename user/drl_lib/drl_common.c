// Revision record ----------------------------------------------------

// Includes -----------------------------------------------------------
#include "drl_common.h"

// Functions ----------------------------------------------------------


// Globals ------------------------------------------------------------

// Locals -------------------------------------------------------------

 
 
// �Ƚ�������ֵ�Ƿ���ȫ��ͬ��true����ͬ��false����ͬ
bool drCMN_ArrayCmp(uint8_t *str1, uint8_t *str2, uint8_t len)
{
	uint8_t i;
	for(i = 0; i < len ; i++)
	{
		if(str1[i] != str2[i])
			return false;
	}
	return true;
}

// �������ֵ
uint8_t drCMN_XorCal(uint8_t * dat,uint16_t length)
{
	uint8_t temp_xor;
	uint16_t i;

	temp_xor = *dat;
	for(i = 1;i < length; i++)
	{
		temp_xor = temp_xor ^ *(dat+i);
	}
	return temp_xor;
}
 
 











