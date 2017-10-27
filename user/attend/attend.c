// Revision record ----------------------------------------------------
	

// Includes -----------------------------------------------------------
#include "attend.h"

// Functions ----------------------------------------------------------


// Globals ------------------------------------------------------------
ATTEND_PARAMETERS_T 		ATTEND;
/*
 * 生产信息烧录的flash地址,假如烧录时间为2017年6月22号
 * 0xFC00 + 0:0x20
 * 0xFC00 + 1:0x17
 * 0xFC00 + 2:0x06
 * 0xFC00 + 3:0x22
*/
const uint8_t* pFlashTest = (uint8_t *)(0xFC00);		

// Locals -------------------------------------------------------------


/**********************************************************************
	函数：XXX_PerInit
	描述：XXX初始化
	输入：
	输出：
	返回：
**********************************************************************/
void ATTEND_Init(void)
{
	ATTEND_ParInit();
//	ATTEND_PerInit();
}


/**********************************************************************
	函数：XXX_PerInit
	描述：XXX结构体参数初始化
	输入：
	输出：
	返回：
**********************************************************************/
void ATTEND_ParInit(void)
{
	uint32_t TmpUID = 0;
	

	ATTEND.SuportFlg = false;
	ATTEND.TxChannal =  81;
	
//	if(ATTEND.SuportFlg)
//		TIMER_TxAttendStart();				//开启2.4G考勤定时器

	ATTEND.Pid = 0x00;
	ATTEND.TxData[0] = 0x08;		//发送长度为8Byte
	ATTEND.TxData[1] = 0x01 | (ATTEND.Pid << 1);		//参考官方手册,bit0 NoAck位，bit1~bit2 Pid位，0~4循环值
	
//	TmpUID = (uint32_t)(NFC.UID[3] | (NFC.UID[4] << 8) | (NFC.UID[5] << 16) | (NFC.UID[6] << 24));
	TmpUID = (uint32_t)(0x11223344);
	
	ATTEND.TxData[9] =  (((TmpUID / 10) % 10) << 4)         | ((TmpUID / 1) % 10);
	ATTEND.TxData[8] =  (((TmpUID / 1000) % 10) << 4)       | ((TmpUID / 100) % 10);
	ATTEND.TxData[7] =  (((TmpUID / 100000) % 10) << 4)     | ((TmpUID / 10000) % 10);
	ATTEND.TxData[6] =  (((TmpUID / 10000000) % 10) << 4)   | ((TmpUID / 1000000) % 10);
	ATTEND.TxData[5] =  (((TmpUID / 1000000000) % 10) << 4) | ((TmpUID / 100000000) % 10);
	

	/*
	 * ATTEND.TxData[4]:保留值，默认为0x00
	 * ATTEND.TxData[3]:bit4~7生产年份，bit0低电量报警
	 * ATTEND.TxData[2]:生产为一年中的第几旬	
	*/
	ATTEND.TxData[4] = 0x00;		
	if(ADC.LatestADCVal > 2680)
		ATTEND.TxData[3] = (*(pFlashTest+1) << 4) & 0xFE;			
	else
		ATTEND.TxData[3] = (*(pFlashTest+1) << 4) | 0x01;
	switch(*(pFlashTest+2))
	{
		case 0x01:	
			switch(*(pFlashTest+3) >> 4)
			{
				case 0x00:	//月份中的某旬		
					ATTEND.TxData[2] = 0x01;			
					break;
				case 0x01:
					ATTEND.TxData[2] = 0x02;
					break;
				case 0x02:
					ATTEND.TxData[2] = 0x03;
					break;
				default:
					ATTEND.TxData[2] = 0x37;	//37表示出错
					break;
			}
			break;
		case 0x02:
			switch(*(pFlashTest+3) >> 4)
			{
				case 0x00:	//月份中的某旬
					ATTEND.TxData[2] = 0x04;
					break;
				case 0x01:
					ATTEND.TxData[2] = 0x05;
					break;
				case 0x02:
					ATTEND.TxData[2] = 0x06;
					break;
				default:
					ATTEND.TxData[2] = 0x37;	//37表示出错
					break;
			}
			break;
		case 0x03:
			switch(*(pFlashTest+3) >> 4)
			{
				case 0x00:	//月份中的某旬
					ATTEND.TxData[2] = 0x07;
					break;
				case 0x01:
					ATTEND.TxData[2] = 0x08;
					break;
				case 0x02:
					ATTEND.TxData[2] = 0x09;
					break;
				default:
					ATTEND.TxData[2] = 0x37;	//37表示出错
					break;
			}
			break;
		case 0x04:
			switch(*(pFlashTest+3) >> 4)
			{
				case 0x00:	//月份中的某旬
					ATTEND.TxData[2] = 0x10;
					break;
				case 0x01:
					ATTEND.TxData[2] = 0x11;
					break;
				case 0x02:
					ATTEND.TxData[2] = 0x12;
					break;
				default:
					ATTEND.TxData[2] = 0x37;	//37表示出错
					break;
			}
			break;
		case 0x05:
			switch(*(pFlashTest+3) >> 4)
			{
				case 0x00:	//月份中的某旬
					ATTEND.TxData[2] = 0x13;
					break;
				case 0x01:
					ATTEND.TxData[2] = 0x14;
					break;
				case 0x02:
					ATTEND.TxData[2] = 0x15;
					break;
				default:
					ATTEND.TxData[2] = 0x37;	//37表示出错
					break;
			}
			break;
		case 0x06:
			switch(*(pFlashTest+3) >> 4)
			{
				case 0x00:	//月份中的某旬
					ATTEND.TxData[2] = 0x16;
					break;
				case 0x01:
					ATTEND.TxData[2] = 0x17;
					break;
				case 0x02:
					ATTEND.TxData[2] = 0x18;
					break;
				default:
					ATTEND.TxData[2] = 0x37;	//37表示出错
					break;
			}
			break;
		case 0x07:
			switch(*(pFlashTest+3) >> 4)
			{
				case 0x00:	//月份中的某旬
					ATTEND.TxData[2] = 0x19;
					break;
				case 0x01:
					ATTEND.TxData[2] = 0x20;
					break;
				case 0x02:
					ATTEND.TxData[2] = 0x21;
					break;
				default:
					ATTEND.TxData[2] = 0x37;	//37表示出错
					break;
			}
			break;
		case 0x08:
			switch(*(pFlashTest+3) >> 4)
			{
				case 0x00:	//月份中的某旬
					ATTEND.TxData[2] = 0x22;
					break;
				case 0x01:
					ATTEND.TxData[2] = 0x23;
					break;
				case 0x02:
					ATTEND.TxData[2] = 0x24;
					break;
				default:
					ATTEND.TxData[2] = 0x37;	//37表示出错
					break;
			}
			break;
		case 0x09:
			switch(*(pFlashTest+3) >> 4)
			{
				case 0x00:	//月份中的某旬
					ATTEND.TxData[2] = 0x25;
					break;
				case 0x01:
					ATTEND.TxData[2] = 0x26;
					break;
				case 0x02:
					ATTEND.TxData[2] = 0x27;
					break;
				default:
					ATTEND.TxData[2] = 0x37;	//37表示出错
					break;
			}
			break;
		case 0x10:
			switch(*(pFlashTest+3) >> 4)
			{
				case 0x00:	//月份中的某旬
					ATTEND.TxData[2] = 0x28;
					break;
				case 0x01:
					ATTEND.TxData[2] = 0x29;
					break;
				case 0x02:
					ATTEND.TxData[2] = 0x30;
					break;
				default:
					ATTEND.TxData[2] = 0x37;	//37表示出错
					break;
			}
			break;
		case 0x11:
			switch(*(pFlashTest+3) >> 4)
			{
				case 0x00:	//月份中的某旬
					ATTEND.TxData[2] = 0x31;
					break;
				case 0x01:
					ATTEND.TxData[2] = 0x32;
					break;
				case 0x02:
					ATTEND.TxData[2] = 0x33;
					break;
				default:
					ATTEND.TxData[2] = 0x37;	//37表示出错
					break;
			}
			break;
		case 0x12:
			switch(*(pFlashTest+3) >> 4)
			{
				case 0x00:	//月份中的某旬
					ATTEND.TxData[2] = 0x34;
					break;
				case 0x01:
					ATTEND.TxData[2] = 0x35;
					break;
				case 0x02:
					ATTEND.TxData[2] = 0x36;
					break;
				default:
					ATTEND.TxData[2] = 0x37;	//37表示出错
					break;
			}
			break;
		default:
			break;
	}				
	
//	ATTEND.TxData[4] = 0x00;					//默认为0x00
//	ATTEND.TxData[3] = 0x70;					//bit4~7生产年份，bit0低电量报警
//	ATTEND.TxData[2] = 0x10;					//生产为一年中的第几旬
}

static uint32_t swap_bits(uint32_t inp)
{
    uint32_t i;
    uint32_t retval = 0;
    
    inp = (inp & 0x000000FFUL);
    
    for(i = 0; i < 8; i++)
    {
        retval |= ((inp >> i) & 0x01) << (7 - i);     
    }
    
    return retval;    
}


static uint32_t bytewise_bitswap(uint32_t inp)
{
      return (swap_bits(inp >> 24) << 24)
           | (swap_bits(inp >> 16) << 16)
           | (swap_bits(inp >> 8) << 8)
           | (swap_bits(inp));
}

/**********************************************************************
	函数：XXX_PerInit
	描述：XXX外设初始化
	输入：
	输出：
	返回：
**********************************************************************/
void ATTEND_PerInit(void)
{
	NRF_RADIO->TXPOWER   = (RADIO_TXPOWER_TXPOWER_Pos4dBm << RADIO_TXPOWER_TXPOWER_Pos);	//功率
	NRF_RADIO->FREQUENCY = 81;//ATTEND.TxChannal;           										//频点	
	NRF_RADIO->MODE      = (RADIO_MODE_MODE_Nrf_1Mbit << RADIO_MODE_MODE_Pos);				//速率
	
	NRF_RADIO->PREFIX0 = 
		((uint32_t)swap_bits(0x01) << 24) // Prefix byte of address 3 converted to nRF24L series format
	  | ((uint32_t)swap_bits(0x01) << 16) // Prefix byte of address 2 converted to nRF24L series format
	  | ((uint32_t)swap_bits(0x01) << 8)  // Prefix byte of address 1 converted to nRF24L series format
	  | ((uint32_t)swap_bits(0x01) << 0); // Prefix byte of address 0 converted to nRF24L series format
  
	NRF_RADIO->PREFIX1 = 
		((uint32_t)swap_bits(0x01) << 24) // Prefix byte of address 7 converted to nRF24L series format
	  | ((uint32_t)swap_bits(0x01) << 16) // Prefix byte of address 6 converted to nRF24L series format
	  | ((uint32_t)swap_bits(0x01) << 8) // Prefix byte of address 6 converted to nRF24L series format
	  | ((uint32_t)swap_bits(0x01) << 0); // Prefix byte of address 4 converted to nRF24L series format

	NRF_RADIO->BASE0       = bytewise_bitswap(0x02030405UL);  // Base address for prefix 0 converted to nRF24L series format
	NRF_RADIO->BASE1       = bytewise_bitswap(0x02030405UL);  // Base address for prefix 1-7 converted to nRF24L series format
  
	NRF_RADIO->TXADDRESS   = 0x00UL;      // Set device address 0 to use when transmitting
	NRF_RADIO->RXADDRESSES = 0x01UL;    // Enable device address 0 to use to select which addresses to receive

	// Packet configuration
	NRF_RADIO->PCNF0 = (0 << RADIO_PCNF0_S0LEN_Pos) | (6 << RADIO_PCNF0_LFLEN_Pos) | (3 << RADIO_PCNF0_S1LEN_Pos);	

	// Packet configuration
	NRF_RADIO->PCNF1 = (RADIO_PCNF1_WHITEEN_Disabled        << RADIO_PCNF1_WHITEEN_Pos) |
					   (RADIO_PCNF1_ENDIAN_Big              << RADIO_PCNF1_ENDIAN_Pos)  |
					   (4									<< RADIO_PCNF1_BALEN_Pos)   |
					   (0                                   << RADIO_PCNF1_STATLEN_Pos) |
					   (32							        << RADIO_PCNF1_MAXLEN_Pos);
	// CRC Config
	NRF_RADIO->CRCCNF = (RADIO_CRCCNF_LEN_Two << RADIO_CRCCNF_LEN_Pos); // Number of checksum bits
	if ((NRF_RADIO->CRCCNF & RADIO_CRCCNF_LEN_Msk) == (RADIO_CRCCNF_LEN_Two << RADIO_CRCCNF_LEN_Pos))
	{
		NRF_RADIO->CRCINIT = 0xFFFFUL;      // Initial value      
		NRF_RADIO->CRCPOLY = 0x11021UL;     // CRC poly: x^16+x^12^x^5+1
	}
	else if ((NRF_RADIO->CRCCNF & RADIO_CRCCNF_LEN_Msk) == (RADIO_CRCCNF_LEN_One << RADIO_CRCCNF_LEN_Pos))
	{
		NRF_RADIO->CRCINIT = 0xFFUL;        // Initial value
		NRF_RADIO->CRCPOLY = 0x107UL;       // CRC poly: x^8+x^2^x^1+1
	}
	
	//不使用SHORT和中断
	NRF_RADIO->SHORTS = 0;
	NRF_RADIO->INTENSET = 0;						
}


void ATTEND_TxAttendData(void)
{
	uint16_t i;
	
	if(ATTEND.StartTxflg  && ATTEND.SuportFlg && nrf_esb_is_idle())
	{
		
//		nrf_gpio_pin_set(RX_PIN_NUMBER_2);
//		nrf_gpio_pin_set(TX_PIN_NUMBER_2);	
		
		ATTEND.StartTxflg = false;
		
		CLOCK_HFCLKStart();						//RADIO外设必须打开外部时钟
		
		// 若当前RADIO配置类型不是发送考勤，配置为发送考勤：不重复配置，减少功耗
		if(RADIO_CONFIG_ATTEND != RADIO.ConfigType)
		{
			RADIO.ConfigType = RADIO_CONFIG_ATTEND;
			TIMER_RxWindowStop();		
			nrf_esb_disable();							//关掉库函数相关的RADIO配置
			ATTEND_PerInit();
		}		

		if(ADC.LatestADCVal > 2680)
			ATTEND.TxData[3] = (*(pFlashTest+1) << 4) & 0xFE;			
		else
			ATTEND.TxData[3] = (*(pFlashTest+1) << 4) | 0x01;		
		
		if(++ATTEND.Pid < 4)
		{
			ATTEND.TxData[1] = 0x01 | (ATTEND.Pid << 1);
		}
		else
		{
			ATTEND.Pid = 0;
			ATTEND.TxData[1] = 0x01 | (ATTEND.Pid << 1);
		}		
		NRF_RADIO->PACKETPTR = (uint32_t)ATTEND.TxData;
			
		//启动硬件发送	
        NRF_RADIO->EVENTS_READY = 0U;
        NRF_RADIO->TASKS_TXEN   = 1; // Enable radio and wait for ready.
		i = 0x0FFF;
        while (NRF_RADIO->EVENTS_READY == 0U)
        {
            if(--i == 0)
			{
				ATTEND.StartTxflg = true;	//这次发送失败，在发送一次
				return;
			}
        }

        // Start transmission.
        NRF_RADIO->TASKS_START = 1U;
        NRF_RADIO->EVENTS_END  = 0U; 
		i = 0x0FFF;
        while(NRF_RADIO->EVENTS_END == 0U) // Wait for end of the transmission packet.
        {
            if(--i == 0)
			{
				ATTEND.StartTxflg = true;	//这次发送失败，在发送一次
				return;
			}
        }

        NRF_RADIO->EVENTS_DISABLED = 0U;
        NRF_RADIO->TASKS_DISABLE   = 1U; // Disable the radio.
		i = 0x0FFF;
        while(NRF_RADIO->EVENTS_DISABLED == 0U)
        {
            if(--i == 0)
			{
				ATTEND.StartTxflg = true;	//这次发送失败，在发送一次
				return;
			}
        }	
		
		if(SYS_ON == POWER.SysState)
		{
			TIMER_RxWindowStart();			
		}
		else	
		{
			CLOCK_HFCLKStop();
		}
		
//		LED_TOG(LED_0);
//		nrf_gpio_pin_clear(RX_PIN_NUMBER_2);
//		nrf_gpio_pin_clear(TX_PIN_NUMBER_2);		
	
	}	
}




