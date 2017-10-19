// Revision record ----------------------------------------------------

// Includes -----------------------------------------------------------
#include "match.h"

// Functions ----------------------------------------------------------

// Globals ------------------------------------------------------------
MATCH_PARAMETERS_T 		MATCH;

// Locals -------------------------------------------------------------

void MATCH_Init(void)
{
	
}


void MATCH_AddUidPin(uint8_t *UID, uint8_t *PIN, uint8_t TxChannal, uint8_t RxChannal)
{
	uint8_t i;
	
	// 查看收到的UID是否已存在，若存在直接退出函数
	for(i = 0;i < 5;i++)
	{
		if(ArrayCmp(UID, MATCH.UID[i].UID, 4))
		{
			return ;
		}
	}
	
	// 若为新UID，存入UID结构体开头(UID整体向后移一位)
	for(i = 4;i > 0;i--)
	{
		memcpy(MATCH.UID[i].UID, MATCH.UID[i-1].UID, 4);
		memcpy(MATCH.UID[i].PIN, MATCH.UID[i-1].PIN, 2);
		MATCH.UID[i].TxChannal = MATCH.UID[i-1].TxChannal;
		MATCH.UID[i].RxChannal = MATCH.UID[i-1].RxChannal;
	}
	memcpy(MATCH.UID[0].UID, UID, 4);
	memcpy(MATCH.UID[0].PIN, PIN, 2);
	MATCH.UID[0].TxChannal = TxChannal;
	MATCH.UID[0].RxChannal = RxChannal;
	
	// 收到新的接收器配对指令后，若处于配对模式，自动把索引值改为0，并显示当前收到的PIN码
	if(SYS_MATCH == POWER.SysState)
	{
		MATCH.SelectIndex = 0;
		MATCH_LCDDisplayPIN(MATCH.SelectIndex);
	}
}

void MATCH_DelUidPin(uint8_t *UID, uint8_t *PIN)
{
	uint8_t i;
	uint8_t TmpDelIndex  = 0;
	bool	TmpDelSucFlg = false;
	
	// 查看收到的UID是否存在，若存在则删掉
	for(i = 0;i < 5;i++)
	{
		if(ArrayCmp(UID, MATCH.UID[i].UID, 4))
		{
			memset(MATCH.UID[i].UID, 0x00, 4);
			memset(MATCH.UID[i].PIN, 0x00, 2);
			TmpDelIndex = i;
			TmpDelSucFlg = true;
		}
	}
	
	// 若删除失败，退出函数
	if(false == TmpDelSucFlg)
		return;

	// 若成功删除UID，则UID整体前移，填补被删掉的UID
	for(i = TmpDelIndex+1;i < 5;i++)
	{
		memcpy(MATCH.UID[i-1].UID, MATCH.UID[i].UID, 4);
		memcpy(MATCH.UID[i-1].PIN, MATCH.UID[i].PIN, 2);			
	}

	// 索引重置为0，并显示索引为0的PIN码
	if(SYS_MATCH == POWER.SysState)
	{
		MATCH.SelectIndex = 0;
		MATCH_LCDDisplayPIN(MATCH.SelectIndex);			
	}
}

void MATCH_KeyHandler(void)
{
	switch(KEY.ScanValue)
	{
		case KEY_APP_A_1:					
		case KEY_APP_B_2:
		case KEY_APP_C_3:
		case KEY_APP_D_4: 
		case KEY_APP_E_5:
		case KEY_APP_F_6:	
			break;
		case KEY_APP_RINGHT:				//7
		case KEY_APP_WRONG:					//9		
			break;
		case KEY_APP_QUERY:					//8		
			break;
		case KEY_APP_FN:					//0			
			break;
		case KEY_APP_POWER:	
			break;
		case KEY_APP_CLEAR:	
			break;
		case KEY_APP_SEND:   
			MATCH_KeySendHandler();
			break;
		case KEY_APP_LAST:	
			MATCH_KeyLastHandler();
			break;			
		case KEY_APP_NEXT:	
			MATCH_KeyNextHandler();
			break;
		case KEY_APP_FN_ADD_1:	
			break;
		case KEY_APP_FN_ADD_2:	
			break;
		case KEY_APP_FN_ADD_3:	
			break;
		case KEY_APP_FN_ADD_4:	
			break;
		case KEY_APP_FN_ADD_5:	
			break;
		case KEY_APP_FN_ADD_6:	
			break;
		case KEY_APP_FN_ADD_OK:			
			break;
		case KEY_APP_FN_ADD_8:			
			break;
		case KEY_APP_FN_ADD_UP:					// Fn+上题，退出24G配对模式
			if(SYS_MATCH == POWER.SysState)
			{
				POWER_SysMatchToOn();
				if(MATCH.NewMatchFlg)
				{
						// 若重新绑定接收器，清空题目信息和LCD显示
				}				
			}
			break;
		case KEY_APP_FN_ADD_DOWN:				
			break;		
		default:
			break;
	}
}

void MATCH_KeySendHandler(void)
{

}

void MATCH_KeyLastHandler(void)
{
	if(0 == MATCH.SelectIndex)
		MATCH.SelectIndex = 4;
	else
		MATCH.SelectIndex--;
	
	MATCH_LCDDisplayPIN(MATCH.SelectIndex);
		
}

void MATCH_KeyNextHandler(void)
{
	if(4 == MATCH.SelectIndex)
		MATCH.SelectIndex = 0;
	else
		MATCH.SelectIndex++;
	
	MATCH_LCDDisplayPIN(MATCH.SelectIndex);	
}


void MATCH_LCDDisplayPIN(uint8_t Index)
{

}










 
 

 
 
