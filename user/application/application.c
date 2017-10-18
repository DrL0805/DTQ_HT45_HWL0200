
/* Includes -----------------------------------------------------*/
#include "application.h"

#define APP_DEBUG
#ifdef  APP_DEBUG
#define APP_Debug  		DEBUG_Printf  
#define APP_DebugNByte 	DEBUG_PrintfNByte
#else  
#define APP_Debug(...)
#define APP_DebugNByte(...)  
#endif


APP_PARAMETERS_T		APP;

void APP_Init(void)
{
	APP.ProjState = PROJECT_DEBUG;
	
	if(NFC.MatchSucceedFlg)
	{
		memcpy(RADIO.MATCH.JsqUid,NFC.DataRead+2,4);			//��֮��ԵĽ�����UID
		memcpy(RADIO.MATCH.DtqUid,NFC.UID+3,4);					//������UID
		memcpy(RADIO.MATCH.Student.Name, NFC.DataRead+13, 10);	
		RADIO.MATCH.DtqNum = NFC.DataRead[6] | (NFC.DataRead[7] << 8);
		RADIO.MATCH.Student.Score = 0;
		RADIO.MATCH.TxChannal = NFC.DataRead[8];			
		RADIO.MATCH.RxChannal = NFC.DataRead[9];	
		RADIO.MATCH.TxPower = NFC.DataRead[10];	
	}
	else
	{
		memset(RADIO.MATCH.JsqUid,0xFF,4);			
		memset(RADIO.MATCH.DtqUid,0xFF,4);
		RADIO.MATCH.TxChannal = NRF_DEFAULT_TX_CHANNEL;			
		RADIO.MATCH.RxChannal = NRF_DEFAULT_RX_CHANNEL;		
		RADIO.MATCH.TxPower = NRF_DEFAULT_TX_POWER;
	}
}


//Ӧ�ò�������
void APP_ParUpdate(void)
{	

	TT4_ReadNDEF(NFC.DataRead);					//��ȡ�µ�13.56M����
	M24SR_Deselect();

	NFC.MatchSucceedFlg = true;
	
	if(NFC.MatchSucceedFlg)
	{
		memcpy(RADIO.MATCH.JsqUid,NFC.DataRead+2,4);			//��֮��ԵĽ�����UID
		memcpy(RADIO.MATCH.DtqUid,NFC.UID+3,4);					//������UID
		memcpy(RADIO.MATCH.Student.Name, NFC.DataRead+13, 10);	
		RADIO.MATCH.Student.Score = 0;
		RADIO.MATCH.TxChannal = NFC.DataRead[8];			
		RADIO.MATCH.RxChannal = NFC.DataRead[9];	
		RADIO.MATCH.TxPower = NFC.DataRead[10];	
		
		// ���µ�ǰ�շ�Ƶ��
		RADIO.IM.TxChannal = RADIO.MATCH.TxChannal;			
		RADIO.IM.RxChannal = RADIO.MATCH.RxChannal;	
		RADIO.IM.TxPower = RADIO.MATCH.TxPower;		
	}

	LCD_ClearSceneArea();
	APP.QUE.ReceiveQueFlg = false;
	APP.QUE.Answer = 0;		
	
	RADIO.IM.LastRxPackNum = 0;			
	RADIO.IM.LastRxSeqNum = 0;	
	RADIO.IM.LastRxPackNum = 0;
}

void APP_KeyHandler(void)
{
	KEY_Scan();
	
	if(KEY.ScanDownFlg)				
	{
		KEY.ScanDownFlg = false;
		
		APP.KeyCnt++;
		
		switch(POWER.SysState)
		{
			case SYS_OFF:
				break;				
			case SYS_ON:
				TIMER_SysStateStop();
				TIMER_SysStateStart();
				if(APP.QUE.ReceiveQueFlg)					//�յ���Ŀ
				{
					switch(APP.QUE.Type)
					{
						case QUE_SINGLE_CHOICE:					// ��ѡ
							
							//���������־�����ڿ��ư����ͼ���Ƶ��
							if(false == APP.QUE.KeySendAllowFlg)
								return;
							
							// �������ظ��ύ��
							if(!APP.QUE.AnsweredFlg)
							{								
								APP_KeySingleChoiceHandler();
							}						
							
							break;
						case QUE_JUDGE:						// �ж�
							
							//���������־�����ڿ��ư����ͼ���Ƶ��
							if(false == APP.QUE.KeySendAllowFlg)
								return;
							
							if(!APP.QUE.AnsweredFlg)
							{
								APP_KeyJudgeHandler();
							}							
							break;
						case QUE_MULTI_CHOICE:						// ��ѡ
							//���������־�����ڿ��ư����ͼ���Ƶ��
							if(false == APP.QUE.KeySendAllowFlg)
								return;							
						
							if(!APP.QUE.AnsweredFlg)
							{
								APP_KeyMultiChoiceHandler();
							}
							
							break;
						case QUE_ACTIVITY:					// ��⣨�������
							//���������־�����ڿ��ư����ͼ���Ƶ��
							if(false == APP.QUE.KeySendAllowFlg)
								return;									
						
							if(!APP.QUE.AnsweredFlg)
							{
								APP_KeyActivityHandler();
							}
							
							break;
						case QUE_MULTI_SINGLE_CHOICE:
							if(!APP.QUE.AnsweredFlg)
							{
								APP_KeyMultiSingleChoiceHandler();
							}
							
							break;
						case QUE_FREE:
							APP_KeyFreeHandler();
							break;
						default:
							break;
					}					
				}
				else										//û�յ���Ŀ
				{
//					APP_KeyEmptyHandler();					
				}	
				break;
			case SYS_SLEEP:
				POWER_SysSleepToOn();
				break;
			case SYS_TEST:	
				break;
			case SYS_MATCH:
				MATCH_KeyHandler();
				break;
			default:
				break;
		}
	}
}

void APP_CmdHandler(void)
{
	
	// �����յ�����Ч�������޸���������������رյȴ���Ч���ݵĽ��մ������ٹ���
//	if((CMD_PRE != APP.CMD.CmdType) && RADIO.IM.RxWindowWaitFlg && !(RADIO.RX.PackNum&0x80))
//	{
//		TIMER_RxWindowReset();
//	}
	
	// ����������Ͳ���CMD_PRE������°�����Ϣ
	if((CMD_PRE != APP.CMD.CmdType) && (CMD_LCD_CTRL != APP.CMD.CmdType))
	{
		RADIO.IM.LastRxPackNum = RADIO.RX.PackNum;	
	}	
	else
	{
		LED_TOG(LED_0);
	}
	
	switch(APP.CMD.CmdType)
	{
		case CMD_TEST:						//����ָ��
			APP_CmdTestHandler();
			break;    
		case CMD_QUESTION:	
			APP_CmdQuestionHandler();
			break;
		case CMD_SYS_OFF:
			APP_CmdSysOffHandler();
			break;
		case CMD_TEST_SELF:	
			break;
		case CMD_CLEAR_SCREEN:
			APP_CmdClearScreenHandler();
			break;
		case CMD_GET_STATE:
			APP_CmdGetStateHandler();
			break;
		case CMD_PRE:
			APP_CmdPreHandler();
			break;
		case CMD_ACK:
			APP_CmdAckHandler();
			break;
		case CMD_START_MANUAL_MATCH:
			APP_CmdStartManualMatchHandler();
			break;
		case CMD_AFFIRM_MANUAL_MATCH:
			APP_CmdAffirmManualMatchHandler();
			break;
		case CMD_STOP_MANUAL_MATCH:
			APP_CmdStopManualMatchHandler();
			break;
		case CMD_SET_SCORE:
			APP_CmdSetScoreHandler();
			break;
		case CMD_LCD_CTRL:
			APP_CmdLcdCtrlHandler();
			break;
		default	:		
			break;
	}
}

/* ����������-------------------------------------------------------------------- */

// ���ּ�
void APP_KeyFnAdd8Handler(void)
{
	
}

void APP_KeyPowerHandler(void)
{
	
}

// ���ڼ�
void APP_KeyFnAddOKHandler(void)
{

}

void APP_KeyClearHandler(void)
{
	APP.QUE.Answer = 0;
	APP.QUE.pMultiAnswerNum = 0;
	memset(APP.QUE.MultiAnswer, 0x00, 16);
	LCD_DisplayLetter(APP.QUE.Answer);	
	LCD.DATA.SendResultState = SEND_RESULT_CLEAR;
	LCD.DATA.RefreshFlg |= LCD_REFRESH_RESULT;	
}

void APP_KeyFnHandler(void)
{

}

void APP_KeySendHandler(void)
{
	//��û�յ���Ŀ�����ͼ���Ч
	if(false == APP.QUE.ReceiveQueFlg)
		return;
	
	//���������־�����ڿ��ư����ͼ���Ƶ��
	if(false == APP.QUE.KeySendAllowFlg)
		return;
	
	// û�����𣬷��ͼ���Ч
	if((0x00 == APP.QUE.Answer) && (QUE_ACTIVITY != APP.QUE.Type))
		return;
	
	
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
		14���������㲥���� = 16
		----------������--------------
			15���������� = 0x10
			16������� = 14
			---------��������---------
				17~20����Ŀ����
				21~24����������
				25~28�����Դ���
				29����Ŀ����
				30��������
		------------------------------
		31��У��
		32����β0x21
	*/	
	RADIO.TX.DataLen = 33;
	
	RADIO.TX.Data[0] = NRF_DATA_HEAD;					// ͷ
	memcpy(RADIO.TX.Data+1, RADIO.MATCH.DtqUid, 4);		// ԴUID
	memcpy(RADIO.TX.Data+5, RADIO.MATCH.JsqUid, 4);		// Ŀ��UID
	RADIO.TX.Data[9] = 0x11;							// �豸ID
	RADIO.TX.Data[10] = 0x20;
	RADIO.TX.Data[11] = ++RADIO.TX.SeqNum;
	RADIO.TX.Data[12] = ++RADIO.TX.PackNum;
	RADIO.TX.Data[13] = 0;						// ��չ�ֽڳ���
	RADIO.TX.Data[14] = 16;					// PackLen
	RADIO.TX.Data[15] = 0x10;				// ��������
	RADIO.TX.Data[16] = 14;					// ����ȣ�
	memcpy(RADIO.TX.Data+17, APP.QUE.LastPackNum, 4);	// ��Ŀ����

	RADIO.TX.Data[21] = APP.KeyCnt >> 0;
	RADIO.TX.Data[22] = APP.KeyCnt >> 8;
	RADIO.TX.Data[23] = APP.KeyCnt >> 16;
	RADIO.TX.Data[24] = APP.KeyCnt >> 24;
	
	RADIO.TX.Data[25] = APP.EchoCnt >> 0;
	RADIO.TX.Data[26] = APP.EchoCnt >> 8;
	RADIO.TX.Data[27] = APP.EchoCnt >> 16;
	RADIO.TX.Data[28] = APP.EchoCnt >> 24;
	
	RADIO.TX.Data[29] = APP.QUE.Type;
	RADIO.TX.Data[30] = APP.QUE.Answer;
	RADIO.TX.Data[31] = XOR_Cal(RADIO.TX.Data+1, RADIO.TX.DataLen - 3);
	RADIO.TX.Data[32] = NRF_DATA_END;
	
	// ��RADIO.TX�ṹ������ݷ��ͳ�ȥ
	RADIO_ActivLinkProcess(RADIO_TX_KEY_ANSWER);
}

void APP_KeyMultiSendHandler(void)
{
	//��û�յ���Ŀ�����ͼ���Ч
	if(false == APP.QUE.ReceiveQueFlg)
		return;
	
	//���������־�����ڿ��ư����ͼ���Ƶ��
	if(false == APP.QUE.KeySendAllowFlg)
		return;
	
	// û�����𣬷��ͼ���Ч
	if(0x00 == APP.QUE.MultiAnswer[0])
		return;
	
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
		14���������㲥���� = 23
		----------������--------------
			15���������� = 0x10
			16������� = 
			---------��������---------
				17~20����Ŀ����
				21����Ŀ����
				22~37��������
		------------------------------
		38��У��
		39����β0x21
	*/	
	RADIO.TX.DataLen = 40;
	
	RADIO.TX.Data[0] = NRF_DATA_HEAD;					// ͷ
	memcpy(RADIO.TX.Data+1, RADIO.MATCH.DtqUid, 4);		// ԴUID
	memcpy(RADIO.TX.Data+5, RADIO.MATCH.JsqUid, 4);		// Ŀ��UID
	RADIO.TX.Data[9] = 0x11;							// �豸ID
	RADIO.TX.Data[10] = 0x20;
	RADIO.TX.Data[11] = ++RADIO.TX.SeqNum;
	RADIO.TX.Data[12] = ++RADIO.TX.PackNum;
	RADIO.TX.Data[13] = 0;						// ��չ�ֽڳ���
	RADIO.TX.Data[14] = 23;					// PackLen
	RADIO.TX.Data[15] = 0x10;				// ��������
	RADIO.TX.Data[16] = 21;					// ����ȣ�
	memcpy(RADIO.TX.Data+17, APP.QUE.LastPackNum, 4);	// ��Ŀ����
	RADIO.TX.Data[21] = APP.QUE.Type;
	memcpy(RADIO.TX.Data+22, APP.QUE.MultiAnswer, 16);	
	RADIO.TX.Data[38] = XOR_Cal(RADIO.TX.Data+1, RADIO.TX.DataLen - 3);
	RADIO.TX.Data[39] = NRF_DATA_END;
	
	// ��RADIO.TX�ṹ������ݷ��ͳ�ȥ
	RADIO_ActivLinkProcess(RADIO_TX_KEY_ANSWER);	
}

void APP_KeyLastHandler(void)
{

}

void APP_KeyNextHandler(void)
{

}

void APP_KeyFnAdd1Handler(void)
{
	if(PROJECT_DEBUG == APP.ProjState)
	{
		LCD.DisType = LCD_DIS_VER;
		TIMER_DisVerStop();
		TIMER_DisVerStart();		
	}
}

void APP_KeyFnAdd2Handler(void)
{
	if(PROJECT_DEBUG == APP.ProjState)
	{
		LCD.DisType = LCD_DIS_RSSI;
		TIMER_DisVerStop();
		TIMER_DisVerStart();		
	}	
}

void APP_KeyFnAdd3Handler(void)
{
	if(PROJECT_DEBUG == APP.ProjState)
	{
		LCD.DisType = LCD_DIS_VOLTAGE;
		TIMER_DisVerStop();
		TIMER_DisVerStart();		
	}
}

void APP_KeyFnAdd4Handler(void)
{
	if(PROJECT_DEBUG == APP.ProjState)
	{
		LCD.DisType = LCD_DIS_CHANNAL;
		TIMER_DisVerStop();
		TIMER_DisVerStart();		
	}
}

void APP_KeyFnAdd5Handler(void)
{
	if(PROJECT_DEBUG == APP.ProjState)
	{
		LCD.DisType = LCD_DIS_ATTEND;
		TIMER_DisVerStop();
		TIMER_DisVerStart();		
	}
}

void APP_KeyFnAdd6Handler(void)
{
	if(PROJECT_DEBUG == APP.ProjState)
	{
		LCD.DisType = LCD_DIS_DATE;
		TIMER_DisVerStop();
		TIMER_DisVerStart();		
	}
}

void APP_KeyFnAdd7Handler(void)
{		
//	if(DEBUG_STATE == APP.SoftWareState)
//	{
//		// Ҫ�յ���Ŀ���Զ�����ſ���
//		if(APP.QUES.AnswerIngFlg)
//		{
//			if(APP.AutoAnswerSwitchFlg)
//			{	
//				// �ر��Զ�������
//				APP.AutoAnswerSwitchFlg = false;
//				TIMER_AutoAnswerStop();		
//			}
//			else
//			{
//				// �����Զ�������
//				APP.AutoAnswerSwitchFlg = true;
//				APP.AutoAnswerTxCnt = 0;
//				APP.AutoAnswerTxSucCnt = 0;
	

//				TIMER_AutoAnswerStart();		
//			}
//		}	
//	}	
}

//��ѡ�ⰴ��������
void APP_KeySingleChoiceHandler(void)
{
	switch(KEY.ScanValue)
	{
		case KEY_APP_A_1:
			APP.QUE.Answer = 0x01;
			LCD_DisplayLetter(APP.QUE.Answer);
			APP_KeySendHandler();
			break;
		case KEY_APP_B_2:
			APP.QUE.Answer = 0x02;
			LCD_DisplayLetter(APP.QUE.Answer);	
			APP_KeySendHandler();
			break;
		case KEY_APP_C_3:
			APP.QUE.Answer = 0x04;
			LCD_DisplayLetter(APP.QUE.Answer);	
			APP_KeySendHandler();
			break;
		case KEY_APP_D_4: 
			APP.QUE.Answer = 0x08;
			LCD_DisplayLetter(APP.QUE.Answer);	
			APP_KeySendHandler();
			break;
		case KEY_APP_E_5:
		case KEY_APP_F_6:
			break;
		case KEY_APP_RINGHT:
			break;
		case KEY_APP_WRONG:	
			break;
		case KEY_APP_QUERY:				
			break;
		case KEY_APP_POWER:	
			break;
		case KEY_APP_FN:				
			break;
		case KEY_APP_CLEAR:	
			APP_KeyClearHandler();
			break;
		case KEY_APP_SEND:   
			APP_KeySendHandler();
			break;
		case KEY_APP_LAST:	
			APP_KeyLastHandler();
			break;			
		case KEY_APP_NEXT:	
			APP_KeyNextHandler();
			break;
		case KEY_APP_FN_ADD_1:	
			APP_KeyFnAdd1Handler();
			break;
		case KEY_APP_FN_ADD_2:	
			APP_KeyFnAdd2Handler();
			break;
		case KEY_APP_FN_ADD_3:	
			APP_KeyFnAdd3Handler();
			break;
		case KEY_APP_FN_ADD_4:	
			APP_KeyFnAdd4Handler();
			break;
		case KEY_APP_FN_ADD_5:	
			APP_KeyFnAdd5Handler();
			break;
		case KEY_APP_FN_ADD_6:	
			APP_KeyFnAdd6Handler();
			break;
		case KEY_APP_FN_ADD_7:	
			APP_KeyFnAdd7Handler();
			break;
		case KEY_APP_FN_ADD_OK:			//Fn+ok ��������
			APP_KeyFnAddOKHandler();
			break;
		case KEY_APP_FN_ADD_8:			//Fn+? ��������
			APP_KeyFnAdd8Handler();
			break;
		case KEY_APP_FN_ADD_UP:			// Fn+���⣬����24G���ģʽ
			POWER_SysOnToMatch();
			break;
		case KEY_APP_FN_ADD_DOWN:		
			break;	
		default:
			break;
	}
}

//��ѡ�ⰴ��������
void APP_KeyMultiChoiceHandler(void)
{
	switch(KEY.ScanValue)
	{
		case KEY_APP_A_1:
			APP.QUE.Answer |= 0x01;
			LCD_DisplayLetter(APP.QUE.Answer);		
			break;
		case KEY_APP_B_2:
			APP.QUE.Answer |= 0x02;
			LCD_DisplayLetter(APP.QUE.Answer);		
			break;
		case KEY_APP_C_3:
			APP.QUE.Answer |= 0x04;
			LCD_DisplayLetter(APP.QUE.Answer);		
			break;
		case KEY_APP_D_4: 
			APP.QUE.Answer |= 0x08;
			LCD_DisplayLetter(APP.QUE.Answer);		
			break;
		case KEY_APP_RINGHT:
			APP_KeySendHandler();			
			break;
		case KEY_APP_WRONG:					
			APP_KeyClearHandler();
			break;
		case KEY_APP_FN:				
			break;

		default:
			break;
	}
}	

// ���ⵥѡ
void APP_KeyMultiSingleChoiceHandler(void)
{

	switch(KEY.ScanValue)
	{
		case KEY_APP_A_1:
			APP.QUE.MultiAnswer[APP.QUE.pMultiAnswerNum++] = 0x01;
			LCD_DRV_DisplayOne(31+APP.QUE.pMultiAnswerNum,LCD_DRV_DOT_ASCII,ASCII_A);
			break;
		case KEY_APP_B_2:
			APP.QUE.MultiAnswer[APP.QUE.pMultiAnswerNum++] = 0x02;
			LCD_DRV_DisplayOne(31+APP.QUE.pMultiAnswerNum,LCD_DRV_DOT_ASCII,ASCII_B);	
			break;
		case KEY_APP_C_3:
			APP.QUE.MultiAnswer[APP.QUE.pMultiAnswerNum++] = 0x04;
			LCD_DRV_DisplayOne(31+APP.QUE.pMultiAnswerNum,LCD_DRV_DOT_ASCII,ASCII_C);	
			break;
		case KEY_APP_D_4: 
			APP.QUE.MultiAnswer[APP.QUE.pMultiAnswerNum++] = 0x08;
			LCD_DRV_DisplayOne(31+APP.QUE.pMultiAnswerNum,LCD_DRV_DOT_ASCII,ASCII_D);	
			break;
		case KEY_APP_RINGHT:
			APP_KeyMultiSendHandler();			
			break;
		case KEY_APP_WRONG:					
			APP_KeyClearHandler();
			break;
		case KEY_APP_FN:					// �����				
			break;
		default:
			break;
	}	
}

void APP_KeyFreeHandler(void)
{
	switch(KEY.ScanValue)
	{
		case KEY_APP_A_1:
			APP.QUE.Answer = 0x01;
//			LCD_DisplayLetter(APP.QUE.Answer);
			APP_KeySendHandler();
			break;
		case KEY_APP_B_2:
			APP.QUE.Answer = 0x02;
//			LCD_DisplayLetter(APP.QUE.Answer);	
			APP_KeySendHandler();
			break;
		case KEY_APP_C_3:
			APP.QUE.Answer = 0x04;
//			LCD_DisplayLetter(APP.QUE.Answer);	
			APP_KeySendHandler();
			break;
		case KEY_APP_D_4: 
			APP.QUE.Answer = 0x08;
//			LCD_DisplayLetter(APP.QUE.Answer);	
			APP_KeySendHandler();
			break;
		case KEY_APP_RINGHT:
			APP.QUE.Answer = 0x10;
//			LCD_DisplayJudge(JUDGE_TRUE);
			APP_KeySendHandler();
			break;
		case KEY_APP_WRONG:	
			APP.QUE.Answer = 0x20;
//			LCD_DisplayJudge(JUDGE_FALSE);
			APP_KeySendHandler();
			break;
		case KEY_APP_FN:
			APP.QUE.Answer = 0x40;
//			LCD_DisplayHongbao(HONGBAO_DISPLAY);
			APP_KeySendHandler();
			break;
		default:
			break;
	}
}


void APP_KeyActivityHandler(void)
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
		case KEY_APP_RINGHT:
		case KEY_APP_WRONG:	
			break;
		case KEY_APP_QUERY:				
			break;
		case KEY_APP_POWER:	
			break;
		case KEY_APP_FN:
			APP.QUE.Answer = 0x01;

//			LCD_DisplayHongbao(HONGBAO_DISPLAY);
			
			APP_KeySendHandler();
			break;
		case KEY_APP_CLEAR:	
			APP_KeyClearHandler();
			break;
		case KEY_APP_SEND:   
			APP_KeySendHandler();
			break;
		case KEY_APP_LAST:	
			APP_KeyLastHandler();
			break;			
		case KEY_APP_NEXT:	
			APP_KeyNextHandler();
			break;
		case KEY_APP_FN_ADD_1:	
			APP_KeyFnAdd1Handler();
			break;
		case KEY_APP_FN_ADD_2:	
			APP_KeyFnAdd2Handler();
			break;
		case KEY_APP_FN_ADD_3:	
			APP_KeyFnAdd3Handler();
			break;
		case KEY_APP_FN_ADD_4:	
			APP_KeyFnAdd4Handler();
			break;
		case KEY_APP_FN_ADD_5:	
			APP_KeyFnAdd5Handler();
			break;
		case KEY_APP_FN_ADD_6:	
			APP_KeyFnAdd6Handler();
			break;
		case KEY_APP_FN_ADD_7:	
			APP_KeyFnAdd7Handler();
			break;
		case KEY_APP_FN_ADD_OK:			//Fn+ok ��������
			APP_KeyFnAddOKHandler();
			break;
		case KEY_APP_FN_ADD_8:			//Fn+? ��������
			APP_KeyFnAdd8Handler();
			break;
		case KEY_APP_FN_ADD_UP:			// Fn+���⣬����24G���ģʽ
			POWER_SysOnToMatch();
			break;
		case KEY_APP_FN_ADD_DOWN:		
			break;	
		default:
			break;
	}
}

//�����ⰴ��������
void APP_KeyFigureHandler(void)
{
	switch(KEY.ScanValue)
	{
		case KEY_APP_A_1:					
		case KEY_APP_B_2:
		case KEY_APP_C_3:
		case KEY_APP_D_4: 
		case KEY_APP_E_5:
		case KEY_APP_F_6:			
		case KEY_APP_RINGHT:											//7
		case KEY_APP_WRONG:												//9
		case KEY_APP_QUERY:												//8
		
			break;
		case KEY_APP_FN:												//0	

			break;
		case KEY_APP_POWER:	
			break;
		case KEY_APP_CLEAR:	
			APP_KeyClearHandler();
			break;
		case KEY_APP_SEND:   
			APP_KeySendHandler();
			break;
		case KEY_APP_LAST:	
			APP_KeyLastHandler();
			break;			
		case KEY_APP_NEXT:	
			APP_KeyNextHandler();
			break;
		case KEY_APP_FN_ADD_1:	
			APP_KeyFnAdd1Handler();
			break;
		case KEY_APP_FN_ADD_2:	
			APP_KeyFnAdd2Handler();
			break;
		case KEY_APP_FN_ADD_3:	
			APP_KeyFnAdd3Handler();
			break;
		case KEY_APP_FN_ADD_4:	
			APP_KeyFnAdd4Handler();
			break;
		case KEY_APP_FN_ADD_5:	
			APP_KeyFnAdd5Handler();
			break;
		case KEY_APP_FN_ADD_6:	
			APP_KeyFnAdd6Handler();
			break;
		case KEY_APP_FN_ADD_7:	
			APP_KeyFnAdd7Handler();
			break;
		case KEY_APP_FN_ADD_OK:			//Fn+ok ��������
			APP_KeyFnAddOKHandler();
			break;
		case KEY_APP_FN_ADD_8:			//Fn+? ��������
			APP_KeyFnAdd8Handler();
			break;
		case KEY_APP_FN_ADD_UP:			// Fn+���⣬����24G���ģʽ
			POWER_SysOnToMatch();
			break;
		case KEY_APP_FN_ADD_DOWN:		
			break;	
		default:
			break;
	}
}

//�����ⰴ��������
void APP_KeyJudgeHandler(void)
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
		case KEY_APP_RINGHT:
			APP.QUE.Answer = JUDGE_TRUE;
			LCD_DisplayJudge(APP.QUE.Answer);
			APP_KeySendHandler();
			break;
		case KEY_APP_WRONG:	
			APP.QUE.Answer = JUDGE_FALSE;
			LCD_DisplayJudge(APP.QUE.Answer);
			APP_KeySendHandler();
			break;
		case KEY_APP_FN:													//0		
			break;
		case KEY_APP_POWER:	
			break;
		case KEY_APP_CLEAR:	
			APP_KeyClearHandler();
			break;
		case KEY_APP_SEND:   
			APP_KeySendHandler();
			break;
		case KEY_APP_LAST:	
			APP_KeyLastHandler();
			break;			
		case KEY_APP_NEXT:	
			APP_KeyNextHandler();
			break;
		case KEY_APP_FN_ADD_1:			//��ĸ		
		case KEY_APP_FN_ADD_2:	
		case KEY_APP_FN_ADD_3:	
		case KEY_APP_FN_ADD_4:	
		case KEY_APP_FN_ADD_5:	
		case KEY_APP_FN_ADD_6:	
	
			break;
		case KEY_APP_FN_ADD_7:						//��
		
			break;
		case KEY_APP_FN_ADD_9:						//��
		
			break;
		case KEY_APP_FN_ADD_OK:			//Fn+ok ��������
			APP_KeyFnAddOKHandler();
			break;
		case KEY_APP_FN_ADD_8:			//Fn+? ��������
			APP_KeyFnAdd8Handler();
			break;
		default:
			break;
	}
}

//û���յ���Ŀ�������������LCD��ʾ����ʵ������
void APP_KeyEmptyHandler(void)
{
	switch(KEY.ScanValue)
	{
		case KEY_APP_A_1:
			LCD_DisplayLetter(LCD_A);
			break;
		case KEY_APP_B_2:
			LCD_DisplayLetter(LCD_B);
			break;
		case KEY_APP_C_3:
			LCD_DisplayLetter(LCD_C);
			break;
		case KEY_APP_D_4: 	
			LCD_DisplayLetter(LCD_D);
			break;
		case KEY_APP_RINGHT:	
			LCD_DisplayJudge(JUDGE_TRUE);
			break;
		case KEY_APP_WRONG:		
			LCD_DisplayJudge(JUDGE_FALSE);
			break;
		case KEY_APP_FN:
			LCD_DisplayHongbao(HONGBAO_DISPLAY);
			break;
		default:
			break;
	}
}

/* 2.4G�������-------------------------------------------------------------------- */
void APP_CmdTestHandler(void)
{
	
}

void APP_CmdQuestionHandler(void)
{
	uint8_t i;
	uint8_t TmpHanziNum;
	/* 
	 * 1��������δ�յ���Ŀ����ȡ��ǰ��Ŀ
	 * 2�����������յ���Ŀ�����ݰ����ж��Ƿ�������Ŀ�������µ���Ŀ�����ղ������ϴ��յ�����Ŀ
	*/
	if(false == APP.QUE.ReceiveQueFlg)
	{
		APP.QUE.KeySendAllowFlg = true;
		APP.QUE.AnsweredFlg = false;
		memcpy(APP.QUE.LastPackNum, APP.CMD.CmdData, 4);
	}
	else
	{
		if(ArrayCmp(APP.CMD.CmdData, APP.QUE.LastPackNum, 4))
		{
			return;	//��ͬ��Ŀ��ֱ���˳�����
		}
		else	
		{	
			APP.QUE.KeySendAllowFlg = true;
			APP.QUE.AnsweredFlg = false;			
			memcpy(APP.QUE.LastPackNum, APP.CMD.CmdData, 4);
		}
	}

	// ������Ŀ��Ϣ
	APP.QUE.Type = APP.CMD.CmdData[4];
	
	if(APP.QUE.Type == QUE_FREE_STOP)	
	{
		APP.QUE.ReceiveQueFlg = false;		
	}	
	else
	{
		APP.QUE.ReceiveQueFlg = true;	
	}
	
	APP.QUE.Answer = 0;
	APP.QUE.pMultiAnswerNum = 0;
	memset(APP.QUE.MultiAnswer, 0x00, 16);	

	LCD_DRV_DisplayN(16, APP.CMD.CmdLen - 5, APP.CMD.CmdData+5);			
}

void APP_CmdSysOffHandler(void)
{
	POWER_SysOnToOff();
}

void APP_CmdPreHandler(void)
{
	uint8_t point_bit;
	
	if(RADIO.RX.ExtendLen)
	{
		point_bit = (RADIO.RX.ExtendData[RADIO.MATCH.DtqNum / 8] >> (RADIO.MATCH.DtqNum % 8)) & 0x01;
		if(point_bit)
		{
			if(false ==RADIO.IM.RxWindowWaitFlg)
			{
				RADIO.IM.RxWindowWaitFlg = true;
				if(110 > (APP.CMD.CmdData[0] + 5))
				{
					TIMER_WaitDataStart(110 - APP.CMD.CmdData[0] - 5);	//��5��ǰ��֡������
				}
				else
				{
					TIMER_RxWindowAdd(RX_WINDOW_ADD_WAIT_DATA);	
				}
			}			
		}
	}
	else
	{
		if(false ==RADIO.IM.RxWindowWaitFlg)
		{
			RADIO.IM.RxWindowWaitFlg = true;
			if(110 > (APP.CMD.CmdData[0] + 5))
			{
				TIMER_WaitDataStart(110 - APP.CMD.CmdData[0] - 5);	//��5��ǰ��֡������
			}
			else
			{
				TIMER_RxWindowAdd(RX_WINDOW_ADD_WAIT_DATA);	
			}
		}	
	}
}

void APP_CmdAckHandler(void)
{
	uint8_t i, pUid = 1;
	
	for(i = 0;i < APP.CMD.CmdData[0];i++)
	{
		// ���˴������Ƿ��յ�ACK
		if(ArrayCmp(APP.CMD.CmdData+pUid, RADIO.MATCH.DtqUid, 4))
		{
			RADIO.IM.TxSucFlg = true;
			break;
		}
		pUid += 4;
	}
}

void APP_CmdGetStateHandler(void)
{

}

void APP_CmdClearScreenHandler(void)
{
	
}

void APP_CmdStartManualMatchHandler(void)
{
	MATCH_AddUidPin(APP.CMD.CmdData, APP.CMD.CmdData+4, APP.CMD.CmdData[6], APP.CMD.CmdData[7]);
}

void APP_CmdAffirmManualMatchHandler(void)
{
	
}

void APP_CmdStopManualMatchHandler(void)
{
	MATCH_DelUidPin(APP.CMD.CmdData,APP.CMD.CmdData+4);
}

void APP_CmdSetScoreHandler(void)
{
	uint8_t i;
	
	for(i = 0;i < (APP.CMD.CmdLen / 4);i++)
	{
		if(ArrayCmp(RADIO.MATCH.DtqUid, APP.CMD.CmdData+5*i, 4))
		{
			RADIO.MATCH.Student.Score = APP.CMD.CmdData[5*i + 4];
		}
	}

}

void APP_CmdLcdCtrlHandler(void)
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
		14���������㲥���� = 10
		----------������--------------
			15���������� = 0x13
			16������� = 6
			---------��������---------
				17~20�����к�
				21~24��������UID
		------------------------------
		25��У��
		26����β0x21
	*/
	uint8_t i;
	static uint8_t  EchoSeq[4];				// �������
	
	for(i = 0;i < (RADIO.RX.PackLen / 56);i++) 
	{
		// �鿴�������Ƿ��д˴�����
		if(ArrayCmp(RADIO.MATCH.DtqUid, RADIO.RX.PackData+6 + i*56, 4))
		{			
			// �鿴�Ƿ����µĻ�����Ϣ
			if(!ArrayCmp(EchoSeq, RADIO.RX.PackData+2 + i*56, 4))
			{
				memcpy(EchoSeq, RADIO.RX.PackData+2 + i*56, 4);
				
				APP.EchoCnt++;
				
				// ����ָ�����LCD��ʾ
				LCD.DATA.Scene[0] = 48;		
				memcpy(LCD.DATA.Scene+1, RADIO.RX.PackData+10 + i*56, LCD.DATA.Scene[0]);
				LCD.DATA.RefreshFlg |= LCD_REFRESH_SCENE;
							
				// ���ػ���ȷ����Ϣ
				RADIO.TX.DataLen = 27;	
				
				RADIO.TX.Data[0] = NRF_DATA_HEAD;					// ͷ
				memcpy(RADIO.TX.Data+1, RADIO.MATCH.DtqUid, 4);		// ԴUID
				memcpy(RADIO.TX.Data+5, RADIO.MATCH.JsqUid, 4);		// Ŀ��UID
				RADIO.TX.Data[9] = 0x11;							// �豸ID
				RADIO.TX.Data[10] = 0x20;
				RADIO.TX.Data[11] = ++RADIO.TX.SeqNum;
				RADIO.TX.Data[12] = ++RADIO.TX.PackNum;
				RADIO.TX.Data[13] = 0;						// ��չ�ֽڳ���
				RADIO.TX.Data[14] = 10;					// PackLen
				RADIO.TX.Data[15] = CMD_LCD_CTRL;		// ��������
				RADIO.TX.Data[16] = 8;					// ����ȣ�
				memcpy(RADIO.TX.Data+17, RADIO.RX.PackData+2+i*56, 4);	// ���к�ԭ������
				memcpy(RADIO.TX.Data+21, RADIO.MATCH.DtqUid, 4);
				RADIO.TX.Data[25] = XOR_Cal(RADIO.TX.Data+1, RADIO.TX.DataLen - 3);
				RADIO.TX.Data[26] = NRF_DATA_END;	
				
				RADIO_ActivLinkProcess(RADIO_TX_NO_RETRY_RANDOM_DELAY);					
				break;				
			}
		}
	}
}


//������Ŀ��Ϣ
void APP_FetchQuesInfo(void)
{

}
	
	
//��װ��Ŀ��Ϣ
void APP_PackQuestionInfo(void)
{

}



