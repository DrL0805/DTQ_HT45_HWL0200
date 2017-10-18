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
//	memcpy(APP.TX.DstId,RADIO.MATCH.PublicUid,4);				//测试指令接收器UID为广播UID，即全为0
//	memcpy(APP.TX.SrcId,RADIO.MATCH.DtqUid,4);
////	memcpy(APP.TX.SrcId,RADIO.MATCH.PublicUid,4);
//	APP.TX.DevId 	= APP.RX.DevId;						//设备ID，与收到的一样
//	APP.TX.ProVer 	= APP.RX.ProVer;					//协议版本，与收到的一样
////	APP.TX.SeqNum = 0xAA;	
//	APP.TX.PackNum++;
//	APP.TX.PackType = NRF_DATA_IS_USE;
//	APP.TX.TableLen = 0;	
////	APP.RX.AckTable										//无AckTable表
//	APP.TX.CmdType  = 0xF1;	
//	APP.TX.DataLen = 2;									//生产测试指令占2字节
//	
//	APP.TX.Data[0] = TEST.RxRssi;
//	APP.TX.Data[1] = TEST.TxRssi;
//	
//	//因为AckTable表为空，所以要分段校验,然后合并
//	APP.TX.Xor = XOR_Cal(APP.TX.DstId, 14) ^ XOR_Cal(&APP.TX.CmdType, APP.TX.DataLen + 2);
//	APP.TX.End = NRF_DATA_END;
//	APP.TX.Len = APP.TX.DataLen + 19;					//发送数据的总长度	
//	
//	RADIO_ActivTxProcess();
}











 
 

 
 
