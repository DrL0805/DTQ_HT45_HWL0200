

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
	
	err_code = nrf_drv_gpiote_init();		//使能gpiote外设
    APP_ERROR_CHECK(err_code);
	
//	KEY_PowerPinInit();
	KEY_NFCPinInit();
	KEY_MatrixPinInit();
	
	//全局变量赋初值
	KEY.PressFlg		 = false;		//标记按键是否被按下
	KEY.ScanDownFlg		 = false;		//按键扫描完成，已经扫描到有效的键值
	KEY.ScanState		 = KEY_ONE;		//当前按键检测的状态
	KEY.ScanValue		 = 0;			//按键扫描结果
	KEY.FnCombFlg 		 = false;
	
	return drERROR_SUCCESS;
}

void button_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	/* 系统正在开机时，对中断不做处理 */
	if((I2C_INT == pin) && !APP.NFCIrqFlg) 	
	{		
		APP.NFCIrqFlg = true;
		memset(LCD.DATA.Scene+1, 0x00, 48);		// 清空LCD显示RAM
		LED_TOG(LED_0);			
	}
	else
	{
		KEY.PressFlg = true;
	}	
}


//矩阵按键初始化
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



//m24sr中断脚初始化
void KEY_NFCPinInit(void)
{	
	ret_code_t err_code;
	
	nrf_gpio_cfg_input(I2C_INT, NRF_GPIO_PIN_NOPULL);
	
	nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(false);
	
	err_code = nrf_drv_gpiote_in_init(I2C_INT, &in_config, button_event_handler);
	APP_ERROR_CHECK(err_code);
	nrf_drv_gpiote_in_event_enable(I2C_INT, false);
}


//POWER键初始化
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
	static uint8_t KEY_FirstValue = 0;				// 第一次扫描到的值
	static uint8_t KEY_NextValue = 0;				// 之后扫描到的值,用于与第一次扫描的到值进行比较
	static bool	CombinationKeyFlg = false;			// 组合键被按下标志
	static bool	SpecialKeyFlg = false;				// 特殊按键标志
	
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
			
				// 有效按键才开启按键定时器
				if((0x00 != KEY_FirstValue) && (0x0F != KEY_FirstValue) && (0xF0 != KEY_FirstValue))
				{
					KEY.ScanState = KEY_TWO;	
					drTIMER_KEYStart(drTIMER_PERIOD_KEY);
				}				
				break;
			case KEY_TWO:
				KEY_NextValue = KeyBit;
			
				if(KEY_NextValue == KEY_FirstValue)				//如果两个值相等，消抖完成,有效按键
				{
					KEY.ScanState = KEY_THREE;
				}
				else											//无效按键
				{
					drTIMER_KEYStop();
					KEY.ScanState = KEY_ONE;
				}					
				break;
			case KEY_THREE:
				KEY_NextValue = KeyBit;
				
				if(0x0F != KEY_NextValue)		// 还有按键未被释放		
				{
					drTIMER_SysSleepStart(drTIMER_PERIOD_SysSleep);			
					
					if(KEY_FirstValue != KEY_NextValue)
					{
						SpecialKeyFlg = true;	// 根据好未来要求，交替长按、多个按键一起按不能作为有效键值
					}
					
					// 如果第一个按键是抢红包键，则是组合键
					if(KEY_SCAN_FN == KEY_FirstValue && KEY_NextValue != KEY_FirstValue)
					{
						CombinationKeyFlg  = true;
						switch(KEY_NextValue)
						{
							case 0x29:			// 抢红包+A	
								break;
							case 0x2c:			// 抢红包+B
								break;
							case 0x35:			// 抢红包+C
								break;
							case 0x25:			// 抢红包+D
								LCD_DisVer();
								drTIMER_LCDStart(drTIMER_PERIOD_LCD);				
								break;
							case 0x39:			// 抢红包+对
								break;
							case 0x3d:			// 抢红包+错
								break;
							default: break;
						}
					}
				}
				else							// 所有按键都被释放
				{
					if(CombinationKeyFlg || SpecialKeyFlg)		// 组合键
					{
						CombinationKeyFlg  = false;	
						SpecialKeyFlg = false;
					}
					else
					{
						KEY.ScanDownFlg = true;
						KEY.Type = KEY_TYPE_PHYSICS;						
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
								KEY.ScanValue = KEY_APP_INVALID;
								KEY.ScanDownFlg = false;
								break;
						}	
					}
					drTIMER_KEYStop();
					KEY.ScanState = KEY_ONE;
					KEY_FirstValue = 0;
					KEY_NextValue = 0;						
				}
				break;
			default:
				break;
		}
	}
}











