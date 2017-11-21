// Revision record ----------------------------------------------------

// Includes -----------------------------------------------------------
#include "drl_common.h"

// Functions ----------------------------------------------------------


// Globals ------------------------------------------------------------

// Locals -------------------------------------------------------------

 
 
// 比较两数组值是否完全相同，true：相同，false：不同
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

// 计算异或值
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
 

// 检测bool类型标志位是否为真：
//		为真，清除标志位并返回true
// 		为假，返回false
bool drCMN_BoolFlgCheck(bool*	BoolFlg)
{
	if(*BoolFlg)
	{
		*BoolFlg = false;
		return true;
	}
	else
	{
		return false;
	}
}
 











