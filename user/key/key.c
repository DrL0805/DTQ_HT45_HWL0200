

/*-------------------------------- Include File -----------------------------------------*/
#include "key.h"

/*-------------------------------- Macro definition -------------------------------------*/

/*-------------------------------- Local Variable ----------------------------------------*/

/*-------------------------------- Gocal Variable ----------------------------------------*///key_struct_t				*KEY = &key_struct;
key_struct_t  KEY;

/*-------------------------------- Function Declaration ----------------------------------*/

/*-------------------------------- Revision record ---------------------------------------*/

uint32_t KEY_Init(void)
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
	
	return drERROR_SUCCESS;
}

void button_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	/* ϵͳ���ڿ���ʱ�����жϲ������� */
	if((I2C_INT == pin) && POWER.SysInitializedFlg && !APP.NFCIrqFlg) 	
	{		
		APP.NFCIrqFlg = true;			
		LED_TOG(LED_0);			
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
	uint8_t KeyBit = 0;
	static uint8_t KEY_FirstValue = 0;				// ��һ��ɨ�赽��ֵ
	static uint8_t KEY_NextValue = 0;				// ֮��ɨ�赽��ֵ,�������һ��ɨ��ĵ�ֵ���бȽ�
	static bool	CombinationKeyFlg = false;			// ��ϼ������±�־
	
	static uint8_t KEY_CombinationValue;			// ������ϼ���ֵ
	
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
				
				if(0x0F != KEY_NextValue)		// ���а���δ���ͷ�		
				{
					if(KEY_NextValue != KEY_FirstValue)
					{
						CombinationKeyFlg = true;
						KEY_CombinationValue = KEY_NextValue;					
					}
				}
				else							// ���а��������ͷ�
				{
					if(CombinationKeyFlg)		// ��ϼ�
					{
						CombinationKeyFlg  = false;	
						if(KEY_CombinationValue == 0x25)	// �����+D
						{
							LCD_DisVer();
//							TIMER_DisVerStart();
							drTIM_LCDStart();
						}
					}
					else
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
					}
					TIMER_ButtonStop();
					KEY.ScanState = KEY_ONE;
					KEY_FirstValue = 0;
					KEY_NextValue = 0;						
				}
			
				// �ȴ������ͷ�
//				if(KEY_NextValue != KEY_FirstValue)		
//				if(0x0F == KEY_NextValue)				// ���а��������ͷ���
//				{
//					switch (KEY_FirstValue)
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
//						case KEY_SCAN_RINGHT:
//							KEY.ScanValue = KEY_APP_RINGHT;
//							break;
//						case KEY_SCAN_WRONG:
//							KEY.ScanValue = KEY_APP_WRONG;
//							break;
//						case KEY_SCAN_FN:
//							KEY.ScanValue = KEY_APP_FN;
//							break;
//						default:
//							break;
//					}
//					KEY.ScanDownFlg = true;	
//					TIMER_ButtonStop();
//					KEY.ScanState = KEY_ONE;
//					KEY_FirstValue = 0;
//					KEY_NextValue = 0;				
//				}
				break;
			default:
				break;
		}
	}
}











