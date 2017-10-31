#ifndef __KEY_H
#define	__KEY_H

#include <stdbool.h>
#include "app_timer.h"
#include "uart.h"
#include "nrf_delay.h"
#include "nrf_drv_gpiote.h"
#include "timers.h"
#include "main.h"

#define BUTTON_0       KEY_ROW1
#define BUTTON_1       KEY_ROW2
#define BUTTON_2       KEY_ROW3
#define BUTTON_3       KEY_ROW4
#define BUTTON_4       KEY_PWR
#define BUTTONS_NUMBER 5

#define BUTTON_DETECTION_DELAY           APP_TIMER_TICKS(10, 0)

//键盘行IO口
#define KEY_ROW1		    	(12u)
#define KEY_ROW2		    	(2u)
#define KEY_ROW3		    	(13u)
#define KEY_ROW4		    	(4u)

//#define	KEY_COL1				(4u)
#define	KEY_COL2				(14u)
#define	KEY_COL3				(6u)
//#define	KEY_COL4				(7u)

#define	KEY_PWR					(30u)


#define KEY_PORT 				(NRF_GPIO_PORT_SELECT_PORT0)
#define KEY_VALUE_MASK			(0x0F)

//按键扫描值定义
#define KEY_SCAN_INVALID			(0)			//无效扫描结果
#define KEY_SCAN_A_1				0x2B		
#define KEY_SCAN_B_2				0x2E
#define KEY_SCAN_C_3				0x17
#define KEY_SCAN_D_4				0x27
#define KEY_SCAN_E_5				0x2B
#define KEY_SCAN_F_6				0x1B
#define KEY_SCAN_RINGHT				(0x1B)
#define KEY_SCAN_QUERY				(0x87)
#define KEY_SCAN_WRONG				(0x1D)
#define KEY_SCAN_LAST				(0x8D)
#define KEY_SCAN_NEXT		        (0x17)
#define KEY_SCAN_FN					(0x2D)
#define KEY_SCAN_POWER				(0xDD)			//随便定的个值	
#define KEY_SCAN_SEND				(0x8E)
#define KEY_SCAN_CLEAR				(0x4E)
#define KEY_SCAN_FN_ADD_1			(0xC9)			//组合键Fn+A
#define KEY_SCAN_FN_ADD_2			(0xA9)			//组合键Fn+B
#define KEY_SCAN_FN_ADD_3			(0x99)			//组合键Fn+C
#define KEY_SCAN_FN_ADD_4			(0xCB)			//组合键Fn+D
#define KEY_SCAN_FN_ADD_5			(0xAB)			//组合键Fn+E
#define KEY_SCAN_FN_ADD_6			(0x9B)			//组合键Fn+F
#define KEY_SCAN_FN_ADD_7			(0x83)			//组合键Fn+7
#define KEY_SCAN_FN_ADD_8			(0xC3)			//组合键Fn+8
#define KEY_SCAN_FN_ADD_9			(0xA3)			//组合键Fn+9
//#define KEY_SCAN_FN_ADD_POWER		()				//组合键Fn+电源
#define KEY_SCAN_FN_ADD_OK			(0x8A)			//组合键Fn+OK
#define KEY_SCAN_FN_ADD_CE			(0xCA)			//组合键Fn+删除
#define KEY_SCAN_FN_ADD_UP			(0x89)			//组合键Fn+上题
#define KEY_SCAN_FN_ADD_DOWN		(0x93)			//组合键Fn+下题










// 好未来
#define KEY_APP_INVALID				(0)			//无效按键
#define KEY_APP_A_1					(1)		
#define KEY_APP_B_2					(2)
#define KEY_APP_C_3					(3)
#define KEY_APP_D_4					(4)
#define KEY_APP_E_5					(5)
#define KEY_APP_F_6					(6)
#define KEY_APP_RINGHT				(7)
#define KEY_APP_QUERY				(8)
#define KEY_APP_WRONG				(9)
#define KEY_APP_LAST				(13)
#define KEY_APP_NEXT		        (14)
#define KEY_APP_FN					(15)
#define KEY_APP_POWER				(16)	
#define KEY_APP_SEND				(17)
#define KEY_APP_CLEAR				(18)
#define KEY_APP_FN_ADD_1			(21)
#define KEY_APP_FN_ADD_2			(22)
#define KEY_APP_FN_ADD_3			(23)
#define KEY_APP_FN_ADD_4			(24)
#define KEY_APP_FN_ADD_5			(25)
#define KEY_APP_FN_ADD_6			(26)
#define KEY_APP_FN_ADD_7			(27)			
#define KEY_APP_FN_ADD_8			(28)			
#define KEY_APP_FN_ADD_9			(29)			
#define KEY_APP_FN_ADD_POWER		(30)			
#define KEY_APP_FN_ADD_OK			(31)			
#define KEY_APP_FN_ADD_CE			(32)			
#define KEY_APP_FN_ADD_UP			(33)			
#define KEY_APP_FN_ADD_DOWN			(34)			

//按键扫描步骤
typedef enum {
	KEY_ONE, 
    KEY_TWO,
	KEY_THREE
} __KEY_STATE;	


typedef struct 
{
	bool 		PressFlg;			//标记按键是否被按下
	bool		ScanDownFlg;		//按键扫描完成，已经扫描到有效的键值
	uint8_t 	ScanState;			//当前按键检测的状态			
	
	uint8_t     ScanValue;			//按键扫描结果
	bool	 	FnCombFlg;			//Fn组合键标志。防止Fn作为组合键后，释放Fn键时被认作一次单独的Fn按键
}key_struct_t;


extern key_struct_t  KEY;
	

extern uint32_t KEY_Init(void);
extern void KEY_Scan(void);
void KEY_PowerPinInit(void);
void KEY_NFCPinInit(void);
void KEY_MatrixPinInit(void);


#endif 

