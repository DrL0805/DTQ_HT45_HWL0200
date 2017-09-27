

/*-------------------------------- Include File -----------------------------------------*/
#include "key.h"

/*-------------------------------- Macro definition -------------------------------------*/

/*-------------------------------- Local Variable ----------------------------------------*/

/*-------------------------------- Gocal Variable ----------------------------------------*///key_struct_t				*KEY = &key_struct;
key_struct_t  KEY;

/*-------------------------------- Function Declaration ----------------------------------*/

/*-------------------------------- Revision record ---------------------------------------*/

void KEY_Init(void)
{
	ret_code_t err_code;
	
	err_code = nrf_drv_gpiote_init();		//ʹ��gpiote����
    APP_ERROR_CHECK(err_code);
	
//	KEY_PowerPinInit();
	KEY_NFCPinInit();
	KEY_MatrixPinInit();
	
	//ȫ�ֱ�������ֵ
	KEY.PressFlg		 = false;		//��ǰ����Ƿ񱻰���
	KEY.ScanDownFlg		 = false;		//����ɨ����ɣ��Ѿ�ɨ�赽��Ч�ļ�ֵ
	KEY.ScanState		 = KEY_ONE;		//��ǰ��������״̬
	KEY.ScanValue		 = 0;			//����ɨ����
	KEY.FnCombFlg 		 = false;
}

void button_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	/* ϵͳ���ڿ���ʱ�����жϲ������� */
	if((I2C_INT == pin) && POWER.SysInitializedFlg) 	
	{		
		LED_TOG(LED_0);
		nrf_delay_ms(600);				//��ʱ�ȴ�13.56M��ͷ�����꣬��ͨ��I2C��ȡ���µ�����
		APP_ParUpdate();				
		APP_ClearQuestionInfo();		//���²���������ϴε���Ŀ��Ϣ
		RADIO.IM.LastRxPackNum = 0;			
		RADIO.IM.LastRxSeqNum = 0;	
	}
	else
	{
		KEY.PressFlg = true;
	}	
}


//���󰴼���ʼ��
void KEY_MatrixPinInit(void)
{
	ret_code_t err_code;
	uint8_t i;
	
//	nrf_gpio_range_cfg_output(KEY_COL1, KEY_COL4);
	nrf_gpio_cfg_output(KEY_COL2);
	nrf_gpio_cfg_output(KEY_COL3);
//	nrf_gpio_range_cfg_input(KEY_ROW1, KEY_ROW4, NRF_GPIO_PIN_NOPULL);
	
	nrf_gpio_cfg_input(KEY_ROW1, NRF_GPIO_PIN_NOPULL);
	nrf_gpio_cfg_input(KEY_ROW2, NRF_GPIO_PIN_NOPULL);
	nrf_gpio_cfg_input(KEY_ROW3, NRF_GPIO_PIN_NOPULL);
	nrf_gpio_cfg_input(KEY_ROW4, NRF_GPIO_PIN_NOPULL);
	
	
	nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(false);
	
	err_code = nrf_drv_gpiote_in_init(KEY_ROW1, &in_config, button_event_handler);
	APP_ERROR_CHECK(err_code);
	nrf_drv_gpiote_in_event_enable(KEY_ROW1,false);
	
	err_code = nrf_drv_gpiote_in_init(KEY_ROW2, &in_config, button_event_handler);
	APP_ERROR_CHECK(err_code);
	nrf_drv_gpiote_in_event_enable(KEY_ROW2,false);

	err_code = nrf_drv_gpiote_in_init(KEY_ROW3, &in_config, button_event_handler);
	APP_ERROR_CHECK(err_code);
	nrf_drv_gpiote_in_event_enable(KEY_ROW3,false);
	
	err_code = nrf_drv_gpiote_in_init(KEY_ROW4, &in_config, button_event_handler);
	APP_ERROR_CHECK(err_code);
	nrf_drv_gpiote_in_event_enable(KEY_ROW4,false);
}



//m24sr�жϽų�ʼ��
void KEY_NFCPinInit(void)
{
	ret_code_t err_code;
	
	nrf_gpio_cfg_input(I2C_INT, NRF_GPIO_PIN_NOPULL);
	
	nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(false);
	
	err_code = nrf_drv_gpiote_in_init(I2C_INT, &in_config, button_event_handler);
	APP_ERROR_CHECK(err_code);
	nrf_drv_gpiote_in_event_enable(I2C_INT, false);
}


//POWER����ʼ��
void KEY_PowerPinInit(void)
{
	ret_code_t err_code;
	
	nrf_gpio_cfg_input(KEY_PWR, NRF_GPIO_PIN_NOPULL);
	
	nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(false);
	err_code = nrf_drv_gpiote_in_init(KEY_PWR, &in_config, button_event_handler);
	APP_ERROR_CHECK(err_code);
	nrf_drv_gpiote_in_event_enable(KEY_PWR, false);
}


void KEY_Scan(void)
{
	uint8_t KeyColBit = 0, KeyRowBit = 0, KeyBit = 0;
	static uint8_t KEY_FirstValue = 0;				// ��һ��ɨ�赽��ֵ
	static uint8_t KEY_NextValue = 0;				// ֮��ɨ�赽��ֵ,�������һ��ɨ��ĵ�ֵ���бȽ�
	
	if(true == KEY.PressFlg)
	{
		KEY.PressFlg = false;
		
		KeyBit |=  nrf_gpio_pin_read(KEY_ROW1) << 0;
		KeyBit |=  nrf_gpio_pin_read(KEY_ROW2) << 1;
		KeyBit |=  nrf_gpio_pin_read(KEY_ROW3) << 2;
		KeyBit |=  nrf_gpio_pin_read(KEY_ROW4) << 3;
		
		nrf_gpio_cfg_input(KEY_COL2, NRF_GPIO_PIN_NOPULL);
		nrf_gpio_cfg_input(KEY_COL3, NRF_GPIO_PIN_NOPULL);
		KeyBit |= nrf_gpio_pin_read(KEY_COL2) << 4;
		KeyBit |= nrf_gpio_pin_read(KEY_COL3) << 5;
		nrf_gpio_cfg_output(KEY_COL2);
		nrf_gpio_cfg_output(KEY_COL3);	
		
		switch(KEY.ScanState)
		{
			case KEY_ONE:
				KEY_FirstValue = KeyBit;
			
				// ��Ч�����ſ���������ʱ��
				if((0x00 != KEY_FirstValue) && (0x0F != KEY_FirstValue) && (0xF0 != KEY_FirstValue))
				{
					KEY.ScanState = KEY_TWO;					
					TIMER_ButtonStart();
				}				
				break;
			case KEY_TWO:
				KEY_NextValue = KeyBit;
			
				if(KEY_NextValue == KEY_FirstValue)				//�������ֵ��ȣ��������,��Ч����
				{
					KEY.ScanState = KEY_THREE;	
				}
				else											//��Ч����
				{
					TIMER_ButtonStop();	
					KEY.ScanState = KEY_ONE;
				}					
				break;
			case KEY_THREE:
				KEY_NextValue = KeyBit;
			
				// �ȴ������ͷ�
				if(KEY_NextValue != KEY_FirstValue)		
				{
					switch (KEY_FirstValue)
					{
						case KEY_SCAN_A_1:
							KEY.ScanValue = KEY_APP_A_1;
							break;
						case KEY_SCAN_B_2:
							KEY.ScanValue = KEY_APP_B_2;
							break;
						case KEY_SCAN_C_3:
							KEY.ScanValue = KEY_APP_C_3;
							break;
						case KEY_SCAN_D_4:
							KEY.ScanValue = KEY_APP_D_4;
							break;
						case KEY_SCAN_RINGHT:
							KEY.ScanValue = KEY_APP_RINGHT;
							break;
						case KEY_SCAN_WRONG:
							KEY.ScanValue = KEY_APP_WRONG;
							break;
						case KEY_SCAN_FN:
							KEY.ScanValue = KEY_APP_FN;
							break;
						default:
							break;
					}
					KEY.ScanDownFlg = true;	
					TIMER_ButtonStop();
					KEY.ScanState = KEY_ONE;
					KEY_FirstValue = 0;
					KEY_NextValue = 0;				
				}
				break;
			default:
				break;
		}
	}
	
	
	
	
	
	
	
	
	
//	static uint8_t KEY_FirstValue = 0;				// ��һ��ɨ�赽��ֵ
//	static uint8_t KEY_NextValue = 0;				// ֮��ɨ�赽��ֵ,�������һ��ɨ��ĵ�ֵ���бȽ�
//	static uint8_t KEY_ReleaseCnt = 0;				// �����ͷŶ�ʱ������������������ʱ��10�룩��δ�ͷţ����Զ��رհ���������ʱ����
//	uint8_t key_col_value = 0;
//	uint8_t key_row_value = 0;
//	
//	if(true == KEY.PressFlg)
//	{
//		KEY.PressFlg = false; //���б�־����
//		
//		switch(KEY.ScanState)
//		{
//			case KEY_ONE:
//				key_row_value = nrf_gpio_port_read(KEY_PORT);
////				nrf_gpio_range_cfg_input(KEY_COL1, KEY_COL4, NRF_GPIO_PIN_NOPULL);
//				key_col_value = nrf_gpio_port_read(KEY_PORT);
////				nrf_gpio_range_cfg_output(KEY_COL1, KEY_COL4);			
//				KEY_FirstValue = (key_row_value & 0x0F) | (key_col_value & 0xF0);
//				if(0x00 == nrf_gpio_pin_read(KEY_PWR))
//				{
//					KEY_FirstValue = KEY_SCAN_POWER;
//				}
//				
//				// ��Ч�����ſ���������ʱ��
//				if((0x00 != KEY_FirstValue) && (0x0F != KEY_FirstValue) && (0xF0 != KEY_FirstValue))
//				{
//					KEY.ScanState = KEY_TWO;					
//					TIMER_ButtonStart();
//				}
//				
//				KEY_ReleaseCnt = 0;
//			break;
//			case KEY_TWO:
//				key_row_value = nrf_gpio_port_read(KEY_PORT);
////				nrf_gpio_range_cfg_input(KEY_COL1, KEY_COL4, NRF_GPIO_PIN_NOPULL);
//				key_col_value = nrf_gpio_port_read(KEY_PORT);
////				nrf_gpio_range_cfg_output(KEY_COL1, KEY_COL4);			
//				KEY_NextValue = (key_row_value & 0x0F) | (key_col_value & 0xF0);			
//			    if(0x00 == nrf_gpio_pin_read(KEY_PWR))
//				{
//					KEY_NextValue = KEY_SCAN_POWER;
//				}
//				
//				if(KEY_NextValue == KEY_FirstValue)				//�������ֵ��ȣ��������,��Ч����
//				{
//					KEY.ScanState = KEY_THREE;	
//				}
//				else											//��Ч����
//				{
//					TIMER_ButtonStop();	
//					KEY.ScanState = KEY_ONE;
//				}								
//			break;
//			case KEY_THREE:
//				key_row_value = nrf_gpio_port_read(KEY_PORT);
////				nrf_gpio_range_cfg_input(KEY_COL1, KEY_COL4, NRF_GPIO_PIN_NOPULL);
//				key_col_value = nrf_gpio_port_read(KEY_PORT);
////				nrf_gpio_range_cfg_output(KEY_COL1, KEY_COL4);		
//				KEY_NextValue = (key_row_value & 0x0F) | (key_col_value & 0xF0);
//			    if(0x00 == nrf_gpio_pin_read(KEY_PWR))
//				{
//					//����������������״̬����POWER��ֱ�ӻ���
//					if(SYS_SLEEP == POWER.SysState)
//						POWER_SysSleepToOn();
//					
//					KEY_NextValue = KEY_SCAN_POWER;
//					TIMER_KeyPowerStart();
//				}
//				
//				// ���簴������10����δ�ͷţ���ֹͣ������ʱ��
//				// ��ֹ��Ч�İ��������°�����ʱ��һֱ����
//				if(++KEY_ReleaseCnt > 200)
//				{
//					TIMER_ButtonStop();
//					KEY.ScanState = KEY_ONE;
//					KEY.ScanValue = 0;
//					KEY_FirstValue = 0;
//					KEY_NextValue = 0;					
//				}
//				
//				// �ȴ������ͷ�
//				if(KEY_NextValue != KEY_FirstValue)		
//				{
//					switch(KEY_FirstValue)
//					{	
//						case KEY_SCAN_A_1:
//							KEY.ScanValue = KEY_APP_A_1;   
//							break;
//						case KEY_SCAN_B_2:
//							KEY.ScanValue = KEY_APP_B_2;   
//							break;
//						case KEY_SCAN_C_3:
//							KEY.ScanValue = KEY_APP_C_3;   
//							break;
//						case KEY_SCAN_D_4:
//							KEY.ScanValue = KEY_APP_D_4;	  
//							break;
//						case KEY_SCAN_E_5:
//							KEY.ScanValue = KEY_APP_E_5;	  
//							break;
//						case KEY_SCAN_F_6:
//							KEY.ScanValue = KEY_APP_F_6;    
//							break;
//						case KEY_SCAN_RINGHT:
//							KEY.ScanValue = KEY_APP_QUERY;    
//							break;
//						case KEY_SCAN_QUERY:
//							KEY.ScanValue = KEY_APP_RINGHT;    
//							break;
//						case KEY_SCAN_WRONG:
//							KEY.ScanValue = KEY_APP_WRONG;    
//							break;
//						case KEY_SCAN_LAST:
//							KEY.ScanValue = KEY_APP_LAST;    
//							break;
//						case KEY_SCAN_NEXT:
//							KEY.ScanValue = KEY_APP_NEXT;    		
//							break;
//						case KEY_SCAN_FN:
//							//��Fn���ϴ���Ϊ��ϼ�ʹ�ã������Ϊ�ͷ�Fn����
//							if(KEY.FnCombFlg)
//							{
//								KEY.FnCombFlg = false;
//								KEY.ScanValue = KEY_APP_INVALID;
//							}
//							else
//							{
//								//KEY_NextValue == 0x0F:������Fn�����ͷţ���ΪFn����
//								//KEY_NextValue != 0x0F:��ϼ���Fn���ͷţ�����Ϊ������Fn����
//								if(0x0F == KEY_NextValue)								
//									KEY.ScanValue = KEY_APP_FN; 
//								else
//									KEY.ScanValue = KEY_APP_INVALID;
//							}
//							break;
//						case KEY_SCAN_POWER:
//							KEY.ScanValue = KEY_APP_POWER;    		
//							break;
//						case KEY_SCAN_SEND:
//							KEY.ScanValue = KEY_APP_SEND;    
//							break;
//						case KEY_SCAN_CLEAR:
//							KEY.ScanValue = KEY_APP_CLEAR;     	
//							break;
//						case KEY_SCAN_FN_ADD_1:								// FN + A ��ϼ�
//							
//							KEY.FnCombFlg = true;
//							KEY.ScanValue = KEY_APP_FN_ADD_1;        	
//							break;
//						case KEY_SCAN_FN_ADD_2:								// FN + B ��ϼ�
//							KEY.FnCombFlg = true;
//							KEY.ScanValue = KEY_APP_FN_ADD_2;        	
//							break;
//						case KEY_SCAN_FN_ADD_3:								// FN + C ��ϼ�
//							KEY.FnCombFlg = true;
//							KEY.ScanValue = KEY_APP_FN_ADD_3;        	
//							break;
//						case KEY_SCAN_FN_ADD_4:								// FN + D ��ϼ�
//							KEY.FnCombFlg = true;
//							KEY.ScanValue = KEY_APP_FN_ADD_4;									
//							break;
//						case KEY_SCAN_FN_ADD_5:	
//							KEY.FnCombFlg = true;							
//							KEY.ScanValue = KEY_APP_FN_ADD_5;
//							break;
//						case KEY_SCAN_FN_ADD_6:
//							KEY.FnCombFlg = true;
//							KEY.ScanValue = KEY_APP_FN_ADD_6;
//							break;
//						case KEY_SCAN_FN_ADD_7:	
//							KEY.FnCombFlg = true;
//							KEY.ScanValue = KEY_APP_FN_ADD_7;
//							break;
//						case KEY_SCAN_FN_ADD_8:	
//							KEY.FnCombFlg = true;
//							KEY.ScanValue = KEY_APP_FN_ADD_8;
//							break;
//						case KEY_SCAN_FN_ADD_9:	
//							KEY.FnCombFlg = true;
//							KEY.ScanValue = KEY_APP_FN_ADD_9;
//							break;
//						case KEY_SCAN_FN_ADD_OK:
//							KEY.FnCombFlg = true;
//							KEY.ScanValue = KEY_APP_FN_ADD_OK;
//							break;
//						case KEY_SCAN_FN_ADD_CE:
//							KEY.FnCombFlg = true;
//							KEY.ScanValue = KEY_APP_FN_ADD_CE;
//							break;
//						case KEY_SCAN_FN_ADD_UP:
//							KEY.FnCombFlg = true;
//							KEY.ScanValue = KEY_APP_FN_ADD_UP;
//							break;
//						case KEY_SCAN_FN_ADD_DOWN:	
//							KEY.FnCombFlg = true;
//							KEY.ScanValue = KEY_APP_FN_ADD_DOWN;
//							break;
//						default:
//							TIMER_ButtonStop();
//							KEY.ScanState = KEY_ONE;
//							KEY.ScanValue = 0;
//							KEY_FirstValue = 0;
//							KEY_NextValue = 0;								
//							break;
//					}
//					KEY.ScanDownFlg = true;	
//					TIMER_ButtonStop();
//					KEY.ScanState = KEY_ONE;
//					KEY_FirstValue = 0;
//					KEY_NextValue = 0;
//				}				
//			break;
//			default: 
//				TIMER_ButtonStop();
//				KEY.ScanState = KEY_ONE;
//				KEY.ScanValue = 0;
//				KEY_FirstValue = 0;
//				KEY_NextValue = 0;	
//		}
//	}
}











