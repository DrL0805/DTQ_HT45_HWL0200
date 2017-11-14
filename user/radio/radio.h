#ifndef __RADIO_H
#define	__RADIO_H

#include "nrf_esb.h"
#include "nrf_error.h"
#include "uart.h"
#include "sdk_common.h"
#include "timers.h"
#include "nrf_delay.h"
#include "main.h"


//�ײ�ͨ����غ궨��
#define 	NRF_MAX_NUMBER_OF_RETRANSMITS		(4)					//�ط�����,��������һ��
#define 	NRF_ENHANCE_NUMBER					(2)					//ÿ�η��ʹ���������Ϊ1�����Ϊ��ǿ֡
#define		NRF_RETRANSMIT_DELAY				(280)				//0~255ms���ֵ
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
#define     NRF_DATA_RESERVE				(0xFF)  // ����λĬ��ֵ
#define		NRF_LINK_DATA_LEN				(17)		// ��·�㶨�����ݳ���


#define RX_WINDOW_ADD_WAIT_ACK			(20)	//�����������ݺ�����RX���ȴ�"ACK"��ʱ�䣬20ms������25ms����֤�ɹ���
#define RX_WINDOW_ADD_WAIT_DATA			(30)	//���յ�ǰ��֡������RX���ȴ���Ч���ݵ�ʱ��
#define RX_WINDOW_ON					(3)		//RX����ʱ��
#define RX_WINDOW_OFF					(100)	//RX���ر�ʱ��
#define RETURN_ACK_DELAY				(300)	//����ظ�ACK�����ʱ��


#define	TX_DATA_TYPE_ANSWER		0
#define TX_DATA_TYPE_ECHO		1

// ���߲�����������
typedef enum
{
	RADIO_CONFIG_NONE,
	RADIO_CONFIG_DTQ,
	RADIO_CONFIG_ATTEND
}RADIO_CONFIG_TYPE;					

// ��·�㷢�͵���������
typedef enum
{	
	RADIO_TX_NEED_RETRY,			// ��Ҫ�ط�
	RADIO_TX_NO_RETRY,				// �����ط���ֻ����һ��
	RADIO_TX_NO_RETRY_RANDOM_DELAY,	// �����ط��������ʱ���ڷ���
	RADIO_TX_ACK,
	RADIO_TX_STATE	
}RADIO_LINK_TX_TYPE;

// ����ͨ��Э�鶨��Ľṹ��
typedef struct
{	
	uint8_t Len;					//Head~End��������Ч���ݳ���
	
	uint8_t Head;					//��ͷ
	uint8_t SrcId[4];				//ԴUID
	uint8_t DstId[4];				//Ŀ��UID
	uint8_t DevId;					//�豸UID
	uint8_t ProVer;					//Э��汾��
	uint8_t SeqNum;					//֡��
	uint8_t PackNum;				//����
	uint8_t ExtendLen;				//��չ�ֽڳ���
	uint8_t ExtendData[15];			//��չ�ֽ�����
	uint8_t	PackLen;				//����
	uint8_t PackData[240];			//�����ݣ��洢Ӧ�ò������
	uint8_t Xor;					//��������ͷ��β����������У����
	uint8_t End;					//��β
}NRF_RX_LINK_LAYER_T;

typedef struct
{	
	uint8_t 		DataLen;					// ���淢�Ͱ���������
	uint8_t 		Data[252];

	uint8_t			EchoLen;					// ������Է��͵�����
	uint8_t			EchoData[252];							
	
	uint8_t 		SeqNum;
	uint8_t			PackNum;
}NRF_TX_LINK_LAYER_T;

typedef struct
{
	uint8_t 		Name[10];				// ����
	uint16_t		Score;					// ѧ��
}STUDENT_PARAMETERS_T;

// ��Բ���
typedef struct
{
	uint16_t				DtqNum;		
	uint8_t 				DtqUid[4];				
	uint8_t 				JsqUid[4];	
	uint8_t					PublicUid[4];					//����UID
	STUDENT_PARAMETERS_T	Student;
	uint8_t 				TxChannal;						// ��Եķ���Ƶ��
	uint8_t					RxChannal;						// ��ԵĽ���Ƶ��
	uint8_t					TxPower;
}NRF_MATCH_PARAMETERS_T;

// ʵʱͨ�Ų���
typedef struct
{
	uint8_t 					TxChannal;			// ��ǰ����Ƶ��				
	uint8_t 					RxChannal;			// ��ǰ����Ƶ��
	nrf_esb_tx_power_t 			TxPower;			//���͹���

	bool 						TxIngFlg;					//��·�����ڷ��ͱ�־
	bool 						TxSucFlg;					//���ͳɹ���־
	bool 						RxWindowOnFlg;				//���մ�������
	bool 						RxWindowAddFlg;				//���մ���ʱ�������ڵȴ�ACK/��Ч����
	bool 						RxWindowWaitFlg;			//�յ�ǰ��֡�󣬿�ʼ�ȴ�ACK/��Ч����
	
	uint8_t 					LatestRssi;				//���������յ�2.4G���ź�ǿ��ֵ
	uint8_t 					ReTxCount;				//�ط�����
	uint8_t 					SequenceReTxCount;		//��ǿ֡�ط�����	
	
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


//�ⲿ��������
extern nrf_esb_payload_t        	tx_payload;
extern nrf_esb_payload_t        	rx_payload;
extern RADIO_PARAMETERS_T 			RADIO;


//�ⲿ��������
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

