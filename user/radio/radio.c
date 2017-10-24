#include "radio.h"

#define RADIO_DEBUG
#ifdef RADIO_DEBUG
#define RADIO_Debug  		DEBUG_Printf  
#define RADIO_DebugNByte 	DEBUG_PrintfNByte
#else  
#define RADIO_Debug(...)
#define RADIO_DebugNByte(...)  
#endif 

nrf_esb_payload_t        tx_payload;
nrf_esb_payload_t        rx_payload;

RADIO_PARAMETERS_T 			RADIO;

static uint32_t RADIO_Config(void);

void RADIO_Init(void)
{
	ret_code_t err_code;
	

	
	//默认参数
	RADIO.IM.TxChannal = RADIO.MATCH.TxChannal;			
	RADIO.IM.RxChannal = RADIO.MATCH.RxChannal;	
	RADIO.IM.TxPower = RADIO.MATCH.TxPower;
	

	
	err_code = RADIO_Config();
    APP_ERROR_CHECK(err_code);
}

void RADIO_WakeUp(void)
{
	RADIO.IM.RxWindowOnFlg = false;

	TIMER_RxWindowStart();
}

void RADIO_Sleep(void)
{
	TIMER_RxWindowStop();
	my_esb_mode_change(NRF_ESB_MODE_PRX_STOP, 0);
}

void nrf_esb_event_handler(nrf_esb_evt_t const * p_event)
{
    switch (p_event->evt_id)
    {
        case NRF_ESB_EVENT_TX_SUCCESS:
			if(0 == get_tx_fifo_count())
			{
				TIMER_TxOvertimeStop();
				
				if(RADIO.IM.TxIngFlg)
				{
					TIMER_RxWindowAdd(RX_WINDOW_ADD_WAIT_ACK);
				}
				else
				{
					TIMER_RxWindowReset();		
				}
			}
            break;
        case NRF_ESB_EVENT_TX_FAILED:
            break;
        case NRF_ESB_EVENT_RX_RECEIVED:
            break;
    }
}

uint32_t RADIO_Config(void)
{
	uint32_t err_code;
	uint8_t base_addr_0[4] = {0xE7, 0xE7, 0xE7, 0xE7};
	uint8_t addr_prefix[8] = {0xE7, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8 };
	
	nrf_esb_config_t nrf_esb_config         = NRF_ESB_DEFAULT_CONFIG;
	nrf_esb_config.protocol                 = NRF_ESB_PROTOCOL_ESB_DPL;
	nrf_esb_config.retransmit_delay         = 600;
	nrf_esb_config.bitrate                  = NRF_ESB_BITRATE_1MBPS;
	nrf_esb_config.event_handler            = nrf_esb_event_handler;
	nrf_esb_config.mode                     = NRF_ESB_MODE_PRX;
	nrf_esb_config.selective_auto_ack       = true;	
	nrf_esb_config.payload_length           = 252;
	
	err_code = nrf_esb_set_rf_channel(RADIO.IM.RxChannal);
	VERIFY_SUCCESS(err_code);
	
	err_code = nrf_esb_set_tx_power(RADIO.IM.TxPower);
	VERIFY_SUCCESS(err_code);
	
	err_code = nrf_esb_set_base_address_0(base_addr_0);
	VERIFY_SUCCESS(err_code);

	err_code = nrf_esb_set_prefixes(addr_prefix, 8);
	VERIFY_SUCCESS(err_code);

	err_code = nrf_esb_init(&nrf_esb_config);
	VERIFY_SUCCESS(err_code);
	
	return err_code;
}


//对接收到的2.4G原始数据，进行链路层的解析
void RADIO_RxDataHandler(void)
{
	uint8_t pCmdSite = 0;		// 用于解析一个数据包中有几个Cmd命令
	
	if(nrf_esb_read_rx_payload(&rx_payload) == NRF_SUCCESS)
	{		
//		RADIO.IM.LatestRssi = rx_payload.rssi&0x7F;
		/* 包头、包尾、异或校验 */
		if(rx_payload.data[0]					== NRF_DATA_HEAD &&
		   rx_payload.data[rx_payload.length-1] == NRF_DATA_END  &&
		   rx_payload.data[rx_payload.length-2] == XOR_Cal(rx_payload.data+1,(rx_payload.length-3)))
		{
//			//包头、包尾、异或校验完成后，暂时认为是有效数据
//			//根据通信协议，把收到的数据封装到结构体中
			RADIO.RX.Len = rx_payload.length;
			
			RADIO.RX.Head = rx_payload.data[0];	
			memcpy(RADIO.RX.SrcId,rx_payload.data+1,4);						
			memcpy(RADIO.RX.DstId,rx_payload.data+5,4);						
			RADIO.RX.DevId 		= rx_payload.data[9];							
			RADIO.RX.ProVer 	= rx_payload.data[10];						
			RADIO.RX.SeqNum 	= rx_payload.data[11];						
			RADIO.RX.PackNum 	= rx_payload.data[12];						
			RADIO.RX.ExtendLen  = rx_payload.data[13];
			memcpy(RADIO.RX.ExtendData, rx_payload.data+14, RADIO.RX.ExtendLen);
			RADIO.RX.PackLen = rx_payload.data[14 + RADIO.RX.ExtendLen];
			memcpy(RADIO.RX.PackData, rx_payload.data+15+RADIO.RX.ExtendLen, RADIO.RX.PackLen);
			RADIO.RX.Xor 		= rx_payload.data[RADIO.RX.Len-2];		
			RADIO.RX.End 		= rx_payload.data[RADIO.RX.Len-1];					
			
			
			//是否是已匹配的接收器发过来的或广播
			if(ArrayCmp(RADIO.RX.SrcId,RADIO.MATCH.JsqUid,4) || ArrayCmp(RADIO.RX.SrcId,RADIO.MATCH.PublicUid, 4))
			{	
				//发给特定UID或者广播
				if(ArrayCmp(RADIO.RX.DstId,RADIO.MATCH.PublicUid, 4) || ArrayCmp(RADIO.RX.DstId,RADIO.MATCH.DtqUid,4))
				{
					// 只有发给"我"的2.4G数据才更新RSSI值
//					RADIO.IM.LatestRssi = rx_payload.rssi&0x7F;
					
					// 新的包号，或者包号为0，则接收
					if((RADIO.RX.PackNum != RADIO.IM.LastRxPackNum) | (0 == (RADIO.RX.PackNum&0x7F)) | (RADIO.RX.ExtendLen != 0))	
					{
						// 一一解析命令，并处理
						do
						{
							APP.CMD.CmdType = (APP_CMD_TYPE)(RADIO.RX.PackData[pCmdSite]);
							APP.CMD.CmdLen = RADIO.RX.PackData[pCmdSite+1];
							memcpy(APP.CMD.CmdData, RADIO.RX.PackData+pCmdSite+2, APP.CMD.CmdLen);
							pCmdSite += APP.CMD.CmdLen+2;
							APP_CmdHandler();
						}while((pCmdSite+3) <= RADIO.RX.PackLen);  		// 一个命令至少包含CmdType CmdLen CmdData 3个字节
					}
				}
			}
		}
	}
}

//接收到的2.4G数据链路层解析通过后，
//提取有效数据到应用层
void RADIO_RxSuccess(void)
{

}

void RADIO_TxSuccess(void)
{
	TEST.TxSucCnt++;
	switch(POWER.SysState)
	{
		case SYS_ON:
			APP.QUE.AnsweredFlg = true;
			LCD.DATA.SendResultState = SEND_RESULT_OK;
			LCD.DATA.RefreshFlg |= LCD_REFRESH_RESULT;			
			TIMER_TxResultDisplayStop();
			TIMER_TxResultDisplayStart();
			break;
		case SYS_SLEEP:
			break;
		case SYS_OFF:
			break;
		case SYS_TEST:			
			break;
		case SYS_MATCH:				
			break;
		default:
			NVIC_SystemReset();
			break;
	}
}

void RADIO_TxFailed(void)
{

	TEST.TxFaiCnt++;
	switch(POWER.SysState)
	{
		case SYS_ON:
			LCD.DATA.SendResultState = SEND_RESULT_FAIL;
			LCD.DATA.RefreshFlg |= LCD_REFRESH_RESULT;		
			TIMER_TxResultDisplayStop();
			TIMER_TxResultDisplayStart();
			break;
		case SYS_SLEEP:
			break;
		case SYS_OFF:
			break;
		case SYS_TEST:			
			break;
		case SYS_MATCH:				
			break;
		default:
			NVIC_SystemReset();
			break;
	}
}

// 激活发送定时器，开始链路层发送流程
// 把RADIO.TX结构体里的数据发送出去
void RADIO_ActivLinkProcess(RADIO_LINK_TX_TYPE LinkTxType)
{
	switch (LinkTxType)
    {
    	case RADIO_TX_KEY_ANSWER:
			RADIO.IM.TxIngFlg = true;
			RADIO.IM.ReTxCount = 0;	
			
			APP.QUE.KeySendLimitFlg = true;			// 处于发送过程时，不允许再次按键发送数据
			TIMER_SendAllowStart();				
		
			// 发送一次数据
			RADIO_StartLinkTx(TX_DATA_TYPE_ANSWER);
			
			// 开启重发定时器，定时器到后检测是否发送成功
			TIMER_RetransmitStart();				
    		break;
		case RADIO_TX_NO_RETRY:
			RADIO_StartLinkTx(TX_DATA_TYPE_ANSWER);
			break;
		case RADIO_TX_NO_RETRY_RANDOM_DELAY:
			TIMER_TxRandomDelayStart();
			break;
    	case RADIO_TX_ACK:
    		break;
		case RADIO_TX_STATE:
			break;
    	default:
    		break;
    }
}

//启动硬件RADIO，发送APP.TX结构体内容
void RADIO_StartLinkTx(uint8_t TxDataType)
{
	switch (TxDataType)
    {
    	case TX_DATA_TYPE_ANSWER:
			RADIO_StartHardTx(RADIO.IM.TxChannal, RADIO.TX.Data, RADIO.TX.DataLen);		
    		break;
    	case TX_DATA_TYPE_ECHO:
			RADIO_StartHardTx(RADIO.IM.TxChannal, RADIO.TX.EchoData, RADIO.TX.EchoLen);		
    		break;
    	default:
    		break;
    }
}


void RADIO_ReturnAck(void)
{

}

// 立即启动硬件发送
void RADIO_StartHardTx(uint32_t TxChannal, uint8_t *PayloadBuf, uint8_t PayloadLen)
{
	TIMER_RxWindowStop();	 					 
	my_esb_mode_change(NRF_ESB_MODE_PTX_START, TxChannal);
	
	tx_payload.length  = PayloadLen;
	tx_payload.pipe    = NRF_PIPE;
	tx_payload.noack = true;
	memcpy(tx_payload.data, PayloadBuf, PayloadLen);
	
	nrf_esb_write_payload(&tx_payload);
	TIMER_TxOvertimeStop();
	TIMER_TxOvertimeStart();
}











