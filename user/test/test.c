// Revision record ----------------------------------------------------

// Includes -----------------------------------------------------------
#include "test.h"

// Functions ----------------------------------------------------------
void TEST_KeyTestSend(void);

// Globals ------------------------------------------------------------
TEST_PARAMETERS_T 		TEST;

// Locals -------------------------------------------------------------



uint32_t TEST_Init(void)
{
	TEST.RxRssi = 0;
	TEST.TxRssi = 0;

	return 0;
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
		case KEY_APP_FN:	// 发送
			
			RADIO.TX.DataLen = 21;	
			
			RADIO.TX.Data[0] = NRF_DATA_HEAD;					// 头
			memcpy(RADIO.TX.Data+1, RADIO.MATCH.DtqUid, 4);		// 源UID
			memcpy(RADIO.TX.Data+5, TEST.JsqUid, 4);			// 目标UID
			RADIO.TX.Data[9] = 0x11;							// 设备ID
			RADIO.TX.Data[10] = 0x20;					
			RADIO.TX.Data[11] = 0;								// 回显指令的帧号/包号都为0
			RADIO.TX.Data[12] = 0;
			RADIO.TX.Data[13] = 0;								// 扩展字节长度
			RADIO.TX.Data[14] = 4;								// PackLen
			RADIO.TX.Data[15] = CMD_TEST;					// 命令类型
			RADIO.TX.Data[16] = 2;								// 命令长度，
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
}











 
 

 
 
