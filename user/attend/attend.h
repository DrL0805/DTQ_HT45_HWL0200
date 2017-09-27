#ifndef __ATTEND_H
#define __ATTEND_H	 

// Includes -----------------------------------------------------------
#include "main.h"

// Defines ------------------------------------------------------------
#define PACKET_S1_FIELD_SIZE             (0UL)  /**< Packet S1 field size in bits. */
#define PACKET_S0_FIELD_SIZE             (0UL)  /**< Packet S0 field size in bits. */
#define PACKET_LENGTH_FIELD_SIZE         (0UL)  /**< Packet length field size in bits. */

#define PACKET_BASE_ADDRESS_LENGTH       (3UL)  				// 有源卡base地址长度为3
#define PACKET_STATIC_LENGTH             (9UL)  				//!< Packet static length in bytes
#define PACKET_PAYLOAD_MAXSIZE           (PACKET_STATIC_LENGTH)  //!< Packet payload maximum size in bytes

// Typedefs -----------------------------------------------------------
typedef struct 
{
	bool		SuportFlg;			//2.4G考勤支持标志
	bool		TxIngFlg;			//正在发送2.4G考勤标志
	bool		StartTxflg;			//发送考勤定时器到后，启动发送2.4G考勤标志
	
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














