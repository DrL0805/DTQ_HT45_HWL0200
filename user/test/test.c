// Revision record ----------------------------------------------------

// Includes -----------------------------------------------------------
#include "test.h"

// Functions ----------------------------------------------------------
void TEST_KeyTestSend(void);

// Globals ------------------------------------------------------------
TEST_PARAMETERS_T 		TEST;

// Locals -------------------------------------------------------------



void TEST_Init(void)
{
	TEST.RxRssi = 0;
	TEST.TxRssi = 0;
//	TEST.HuiXianNum = 0;
}

void TEST_RssiTest(void)
{
	
}

#define LCD_TEST_DELAY 500
void TEST_LcdTest(void)
{
	
}


void TEST_KeyHandler(void)
{
	KEY_Scan();
	
	if(KEY.ScanDownFlg)				
	{
		KEY.ScanDownFlg = false;
		
	switch(KEY.ScanValue)
	{
		case KEY_APP_A_1:
			LCD_DRV_DisplayOne(50, LCD_DRV_DOT_ASCII, ASCII_A);
			break;
		case KEY_APP_B_2:
			LCD_DRV_DisplayOne(52, LCD_DRV_DOT_ASCII, ASCII_B);
			break;
		case KEY_APP_C_3:
			LCD_DRV_DisplayOne(54, LCD_DRV_DOT_ASCII, ASCII_C);
			break;
		case KEY_APP_D_4: 
			LCD_DRV_DisplayOne(56, LCD_DRV_DOT_ASCII, ASCII_D);
			break;
		case KEY_APP_RINGHT:
			LCD_DRV_DisplayOne(58, LCD_DRV_DOT_HANZI, 0xA1CC);
			break;
		case KEY_APP_WRONG:
			LCD_DRV_DisplayOne(60, LCD_DRV_DOT_HANZI, 0xA1C1);
			break;
		case KEY_APP_FN:	// ����
			
			RADIO.TX.DataLen = 21;	
			
			RADIO.TX.Data[0] = NRF_DATA_HEAD;					// ͷ
			memcpy(RADIO.TX.Data+1, RADIO.MATCH.DtqUid, 4);		// ԴUID
			memcpy(RADIO.TX.Data+5, TEST.JsqUid, 4);			// Ŀ��UID
			RADIO.TX.Data[9] = 0x11;							// �豸ID
			RADIO.TX.Data[10] = 0x20;					
			RADIO.TX.Data[11] = 0;								// ����ָ���֡��/���Ŷ�Ϊ0
			RADIO.TX.Data[12] = 0;
			RADIO.TX.Data[13] = 0;								// ��չ�ֽڳ���
			RADIO.TX.Data[14] = 4;								// PackLen
			RADIO.TX.Data[15] = CMD_TEST;					// ��������
			RADIO.TX.Data[16] = 2;								// ����ȣ�
			RADIO.TX.Data[17] = TEST.RxRssi;					
			RADIO.TX.Data[18] = TEST.TxRssi;	
			RADIO.TX.Data[19] = XOR_Cal(RADIO.TX.Data+1, RADIO.TX.DataLen - 3);
			RADIO.TX.Data[20] = NRF_DATA_END;
			
			RADIO_ActivLinkProcess(RADIO_TX_NEED_RETRY);		
			break;
		default:
			break;
	}		
		
	}
}




void TEST_KeyTestSend(void)
{
//	APP.TX.Head = NRF_DATA_HEAD;
////	memcpy(APP.TX.DstId,RADIO.MATCH.JsqUid,4);
//	memcpy(APP.TX.DstId,RADIO.MATCH.PublicUid,4);				//����ָ�������UIDΪ�㲥UID����ȫΪ0
//	memcpy(APP.TX.SrcId,RADIO.MATCH.DtqUid,4);
////	memcpy(APP.TX.SrcId,RADIO.MATCH.PublicUid,4);
//	APP.TX.DevId 	= APP.RX.DevId;						//�豸ID�����յ���һ��
//	APP.TX.ProVer 	= APP.RX.ProVer;					//Э��汾�����յ���һ��
////	APP.TX.SeqNum = 0xAA;	
//	APP.TX.PackNum++;
//	APP.TX.PackType = NRF_DATA_IS_USE;
//	APP.TX.TableLen = 0;	
////	APP.RX.AckTable										//��AckTable��
//	APP.TX.CmdType  = 0xF1;	
//	APP.TX.DataLen = 2;									//��������ָ��ռ2�ֽ�
//	
//	APP.TX.Data[0] = TEST.RxRssi;
//	APP.TX.Data[1] = TEST.TxRssi;
//	
//	//��ΪAckTable��Ϊ�գ�����Ҫ�ֶ�У��,Ȼ��ϲ�
//	APP.TX.Xor = XOR_Cal(APP.TX.DstId, 14) ^ XOR_Cal(&APP.TX.CmdType, APP.TX.DataLen + 2);
//	APP.TX.End = NRF_DATA_END;
//	APP.TX.Len = APP.TX.DataLen + 19;					//�������ݵ��ܳ���	
//	
//	RADIO_ActivTxProcess();
}











 
 

 
 
