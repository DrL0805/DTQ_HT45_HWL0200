#ifndef __ATTEND_H
#define __ATTEND_H	 

// Includes -----------------------------------------------------------
#include "main.h"

// Defines ------------------------------------------------------------
#define PACKET_S1_FIELD_SIZE             (0UL)  /**< Packet S1 field size in bits. */
#define PACKET_S0_FIELD_SIZE             (0UL)  /**< Packet S0 field size in bits. */
#define PACKET_LENGTH_FIELD_SIZE         (0UL)  /**< Packet length field size in bits. */

#define PACKET_BASE_ADDRESS_LENGTH       (3UL)  				// ��Դ��base��ַ����Ϊ3
#define PACKET_STATIC_LENGTH             (9UL)  				//!< Packet static length in bytes
#define PACKET_PAYLOAD_MAXSIZE           (PACKET_STATIC_LENGTH)  //!< Packet payload maximum size in bytes

// Typedefs -----------------------------------------------------------
typedef struct 
{
	bool		SuportFlg;			//2.4G����֧�ֱ�־
	bool		TxIngFlg;			//���ڷ���2.4G���ڱ�־
	bool		StartTxflg;			//���Ϳ��ڶ�ʱ��������������2.4G���ڱ�־
	
	uint8_t		TxChannal;
	
	uint8_t  	Pid;					
	uint8_t 	TxData[10];
}ATTEND_PARAMETERS_T;

// Functions ----------------------------------------------------------
extern void ATTEND_Init(void);
extern void ATTEND_ParInit(void);
extern void ATTEND_PerInit(void);
extern void ATTEND_TxAttendData(void);

// Globals ------------------------------------------------------------
extern ATTEND_PARAMETERS_T 		ATTEND;

extern	const uint8_t* pFlashTest;   
#endif














