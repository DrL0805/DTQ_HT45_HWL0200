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
	
	// �鿴�յ���UID�Ƿ��Ѵ��ڣ�������ֱ���˳�����
	for(i = 0;i < 5;i++)
	{
		if(ArrayCmp(UID, MATCH.UID[i].UID, 4))
		{
			return ;
		}
	}
	
	// ��Ϊ��UID������UID�ṹ�忪ͷ(UID���������һλ)
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
	
	// �յ��µĽ��������ָ������������ģʽ���Զ�������ֵ��Ϊ0������ʾ��ǰ�յ���PIN��
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
	
	// �鿴�յ���UID�Ƿ���ڣ���������ɾ��
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
	
	// ��ɾ��ʧ�ܣ��˳�����
	if(false == TmpDelSucFlg)
		return;

	// ���ɹ�ɾ��UID����UID����ǰ�ƣ����ɾ����UID
	for(i = TmpDelIndex+1;i < 5;i++)
	{
		memcpy(MATCH.UID[i-1].UID, MATCH.UID[i].UID, 4);
		memcpy(MATCH.UID[i-1].PIN, MATCH.UID[i].PIN, 2);			
	}

	// ��������Ϊ0������ʾ����Ϊ0��PIN��
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
		case KEY_APP_FN_ADD_UP:					// Fn+���⣬�˳�24G���ģʽ
			if(SYS_MATCH == POWER.SysState)
			{
				POWER_SysMatchToOn();
				if(MATCH.NewMatchFlg)
				{
						// �����°󶨽������������Ŀ��Ϣ��LCD��ʾ
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
	/*
		������2.4G��·�����ݸ�ʽ
		0����ͷ0x61
		1��ԴID����Ϊ��û�а󶨳ɹ�������ȫΪ0
		5��Ŀ��ID��������UID
		9���豸���ͣ������� = 0x11
		10��Э��汾 = 0x21
		11��֡��+1
		12������+1
		13����չ�ֽڳ��� = 0
		14���������㲥���� = 12
		----------������--------------
			15���������� = 0x40
			16������� = 10
			---------��������---------
				17��������UID��4Byte
				21��PIN�룬2Byte
				23��������UID��4Byte
		------------------------------
		27��У��
		28����β0x21
	*/	
	
	// ��ǰ�����Ľ�����UIDȫΪ0��ֱ���˳�
	if(ArrayCmp(MATCH.UID[MATCH.SelectIndex].UID, RADIO.MATCH.PublicUid, 4))
	{
		return;
	}
	
	LED_TOG(LED_0);
	
	RADIO.TX.DataLen = 29;
	
	RADIO.TX.Data[0] = NRF_DATA_HEAD;
	memset(RADIO.TX.Data+1, 0x00, 4);
	memcpy(RADIO.TX.Data+5, MATCH.UID[MATCH.SelectIndex].UID, 4);	// ��ǰ�����Ľ�����UID
	RADIO.TX.Data[9] = 0x11;
	RADIO.TX.Data[10] = 0x21;
	RADIO.TX.Data[11] = ++RADIO.TX.SeqNum;
	RADIO.TX.Data[12] = ++RADIO.TX.PackNum;
	RADIO.TX.Data[13] = 0x00;
	RADIO.TX.Data[14] = 12;
	RADIO.TX.Data[15] = 0x40;
	RADIO.TX.Data[16] = 10;
	memcpy(RADIO.TX.Data+17, MATCH.UID[MATCH.SelectIndex].UID, 4);
	memcpy(RADIO.TX.Data+21, MATCH.UID[MATCH.SelectIndex].PIN, 2);
	memcpy(RADIO.TX.Data+23, RADIO.MATCH.DtqUid, 4);
	RADIO.TX.Data[27] = XOR_Cal(RADIO.TX.Data+1, RADIO.TX.DataLen - 3);
	RADIO.TX.Data[28] = NRF_DATA_END;
	
	RADIO_ActivLinkProcess(RADIO_TX_KEY_ANSWER);
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










 
 

 
 
