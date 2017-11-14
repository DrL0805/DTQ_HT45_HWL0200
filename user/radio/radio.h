#ifndef __RADIO_H
#define	__RADIO_H

#include "nrf_esb.h"
#include "nrf_error.h"
#include "uart.h"
#include "sdk_common.h"
#include "timers.h"
#include "nrf_delay.h"
#include "main.h"


//底层通信相关宏定义
#define 	NRF_MAX_NUMBER_OF_RETRANSMITS		(4)					//重发次数,不包括第一次
#define 	NRF_ENHANCE_NUMBER					(2)					//每次发送次数，至少为1，多的为加强帧
#define		NRF_RETRANSMIT_DELAY				(280)				//0~255ms随机值
#define 	NRF_PIPE						(0)						
#define     NRF_DEFAULT_TX_CHANNEL			(2)
#define     NRF_DEFAULT_RX_CHANNEL			(4)
#define     NRF_MATCH_TX_CHANNEL			(10)
#define     NRF_MATCH_RX_CHANNEL			(12)

#define     NRF_DEFAULT_TX_POWER					(NRF_ESB_TX_POWER_4DBM)
#define		NRF_DATA_IS_USE   				(0x00)
#define     NRF_DATA_IS_ACK					(0x01)
#define     NRF_DATA_IS_PRE					(0x02)		
#define 	NRF_DATA_HEAD					(0x61)
#define     NRF_DATA_END                   (0x21)
#define     NRF_DATA_RESERVE				(0xFF)  // 保留位默认值
#define		NRF_LINK_DATA_LEN				(17)		// 链路层定义数据长度


#define RX_WINDOW_ADD_WAIT_ACK			(20)	//主动发送数据后，增加RX窗等待"ACK"的时间，20ms增到到25ms，保证成功率
#define RX_WINDOW_ADD_WAIT_DATA			(30)	//接收到前导帧后，增加RX窗等待有效数据的时间
#define RX_WINDOW_ON					(3)		//RX窗打开时间
#define RX_WINDOW_OFF					(100)	//RX窗关闭时间
#define RETURN_ACK_DELAY				(300)	//随机回复ACK的最大时间


#define	TX_DATA_TYPE_ANSWER		0
#define TX_DATA_TYPE_ECHO		1

// 无线参数配置类型
typedef enum
{
	RADIO_CONFIG_NONE,
	RADIO_CONFIG_DTQ,
	RADIO_CONFIG_ATTEND
}RADIO_CONFIG_TYPE;					

// 链路层发送的数据类型
typedef enum
{	
	RADIO_TX_NEED_RETRY,			// 需要重发
	RADIO_TX_NO_RETRY,				// 无需重发，只发送一次
	RADIO_TX_NO_RETRY_RANDOM_DELAY,	// 无需重发，随机延时后在发送
	RADIO_TX_ACK,
	RADIO_TX_STATE	
}RADIO_LINK_TX_TYPE;

// 根据通信协议定义的结构体
typedef struct
{	
	uint8_t Len;					//Head~End的所有有效数据长度
	
	uint8_t Head;					//包头
	uint8_t SrcId[4];				//源UID
	uint8_t DstId[4];				//目标UID
	uint8_t DevId;					//设备UID
	uint8_t ProVer;					//协议版本号
	uint8_t SeqNum;					//帧号
	uint8_t PackNum;				//包号
	uint8_t ExtendLen;				//扩展字节长度
	uint8_t ExtendData[15];			//扩展字节内容
	uint8_t	PackLen;				//包长
	uint8_t PackData[240];			//包内容，存储应用层的命令
	uint8_t Xor;					//不包括包头包尾和自身的异或校验结果
	uint8_t End;					//包尾
}NRF_RX_LINK_LAYER_T;

typedef struct
{	
	uint8_t 		DataLen;					// 保存发送按键的数据
	uint8_t 		Data[252];

	uint8_t			EchoLen;					// 保存回显发送的数据
	uint8_t			EchoData[252];							
	
	uint8_t 		SeqNum;
	uint8_t			PackNum;
}NRF_TX_LINK_LAYER_T;

typedef struct
{
	uint8_t 		Name[10];				// 姓名
	uint16_t		Score;					// 学分
}STUDENT_PARAMETERS_T;

// 配对参数
typedef struct
{
	uint16_t				DtqNum;		
	uint8_t 				DtqUid[4];				
	uint8_t 				JsqUid[4];	
	uint8_t					PublicUid[4];					//公共UID
	STUDENT_PARAMETERS_T	Student;
	uint8_t 				TxChannal;						// 配对的发送频点
	uint8_t					RxChannal;						// 配对的接收频点
	uint8_t					TxPower;
}NRF_MATCH_PARAMETERS_T;

// 实时通信参数
typedef struct
{
	uint8_t 					TxChannal;			// 当前发送频点				
	uint8_t 					RxChannal;			// 当前接收频点
	nrf_esb_tx_power_t 			TxPower;			//发送功率

	bool 						TxIngFlg;					//链路层正在发送标志
	bool 						TxSucFlg;					//发送成功标志
	bool 						RxWindowOnFlg;				//接收窗正常打开
	bool 						RxWindowAddFlg;				//接收窗临时增加用于等待ACK/有效数据
	bool 						RxWindowWaitFlg;			//收到前导帧后，开始等待ACK/有效数据
	
	uint8_t 					LatestRssi;				//保存最新收到2.4G的信号强度值
	uint8_t 					ReTxCount;				//重发计数
	uint8_t 					SequenceReTxCount;		//加强帧重发计数	
	
	uint8_t						LastRxPackNum;
	uint8_t                     LastRxSeqNum;	
}NRF_INSTANT_MESSAGE_T;

typedef struct
{
	RADIO_CONFIG_TYPE			ConfigType;
	
	NRF_RX_LINK_LAYER_T			RX;
	NRF_TX_LINK_LAYER_T			TX;
	NRF_MATCH_PARAMETERS_T		MATCH;
	NRF_INSTANT_MESSAGE_T		IM;
}RADIO_PARAMETERS_T;


//外部变量声明
extern nrf_esb_payload_t        	tx_payload;
extern nrf_esb_payload_t        	rx_payload;
extern RADIO_PARAMETERS_T 			RADIO;


//外部函数声明
uint32_t RADIO_Init(void);
void RADIO_WakeUp(void);
void RADIO_Sleep(void);
void RADIO_RxDataHandler(void);
void RADIO_RxSuccess(void);
void RADIO_TxSuccess(void);
void RADIO_TxFailed(void);
void RADIO_ActivLinkProcess(RADIO_LINK_TX_TYPE LinkTxType);
void RADIO_StartLinkTx(uint8_t TxDataType);
void RADIO_ReturnAck(void);
void RADIO_StartHardTx(uint32_t TxChannal, uint8_t *PayloadBuf, uint8_t PayloadLen);

#endif 

