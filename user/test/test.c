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
}

void TEST_RssiTest(void)
{

}

#define LCD_TEST_DELAY 500
void TEST_LcdTest(void)
{
	static bool LcdTestFlg = true;
	
	if(LcdTestFlg)
	{
		LcdTestFlg = false;
		for(uint8_t i = 0;i < 2;i++)
		{
			LCD_DisplayAll();	
			LCD_WriteMultData(0x00,18,LCD_RAM); 
			nrf_delay_ms(LCD_TEST_DELAY);
			
			LCD_ClearScreen();
			LCD_WriteMultData(0x00,18,LCD_RAM); 
			nrf_delay_ms(LCD_TEST_DELAY);		
		}
	}
	ADC_LcdDisValue();
}


void TEST_KeyTest(void)
{
	KEY_Scan();
	
	if(KEY.ScanDownFlg)				
	{
		KEY.ScanDownFlg = false;

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











 
 

 
 
