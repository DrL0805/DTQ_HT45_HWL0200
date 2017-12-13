#ifndef __APPLICATION_H
#define	__APPLICATION_H

#include "main.h"


#define QUES_TYPE_SINGLECHOICE	0x00
#define QUES_TYPE_MULTICHOICE	0x01
#define QUES_TYPE_JUDGE			0x02
#define QUES_TYPE_FIGURE		0x03
#define QUES_TYPE_FREEDOM		0x04

#define QUES_JUDGE_TRUE			0x01
#define QUES_JUDGE_FALSE		0x02

#define	QUESTION_MAX_NUMBER		(81)


//�������״̬,
typedef enum
{
	PROJECT_RELEASE,		//����״̬ 0
	PROJECT_DEBUG			//����״̬ 1
}PROJECT_DEVELOP_STATE_TYPE;

typedef enum
{
	CMD_QUESTION		= 0x10,					
	CMD_CLEAR_SCREEN    = 0x11,
	CMD_GET_STATE		= 0x24,
	CMD_SYS_OFF			= 0x25,
	CMD_TEST		= 0xF1,
	CMD_PRE				= 0x51,					// ǰ��֡
	CMD_ACK				= 0x52,
	CMD_START_MANUAL_MATCH = 0x40,				
	CMD_AFFIRM_MANUAL_MATCH = 0x41,				
	CMD_STOP_MANUAL_MATCH = 0x42,
	CMD_BROADCAST = 0x43,
	CMD_AUTO_MATCH = 0x44,
	CMD_SET_SCORE = 0X12,			// ����ѧ��
	CMD_LCD_CTRL = 0x13			// ����LCD��ʾ�����ԣ�
}APP_CMD_TYPE;


typedef enum
{
	QUE_SINGLE_CHOICE = 0x01,				// ���ⵥѡ
	QUE_JUDGE = 0x02,				// �����ж�
	QUE_MULTI_CHOICE = 0x03,				// �����ѡ
	QUE_ACTIVITY    = 0x04,				// �����
	QUE_MULTI_SINGLE_CHOICE = 0x05,		// ���ⵥѡ
	QUE_FREE = 0x06,						// ͨ����
	QUE_6_SINGLE_CHOICE = 0X07,				// 6����ѡ�⣬
	QUE_FREE_STOP = 0x80					// ͨ����ֹͣ����
}APP_QUE_TYPE;

typedef struct
{
	APP_CMD_TYPE 	CmdType;
	uint8_t			CmdLen;
	uint8_t			CmdData[240];
}CMD_PARAMETERS_T;

typedef struct
{
	bool				AnsweredFlg;						// �������־�����ݺ�δ��Ҫ���յ���Ŀ��ֻ��������һ��
	bool				ReceiveQueFlg;						// �յ���Ŀ��־
	bool				KeySendLimitFlg;					// �����������Ʊ�־
	
	bool				KeyQueryAllowFlg;					// �������������־
	bool				KeyAttendAllowFlg;					// �������������־
	
	uint8_t 			LastPackNum[4];						// �ϴν��յ���Ŀ���ţ�ռ4bit�����������Ƿ����µ���Ŀ��
	
	APP_QUE_TYPE 		Type;
	uint8_t				Answer;								// ������
	
	// ���ⵥѡ�������
	uint8_t 			MultiAnswer[16];	
	uint8_t 			pMultiAnswerNum;
}QUE_PARAMETERS_T;

typedef struct
{
	CMD_PARAMETERS_T 	CMD;
	QUE_PARAMETERS_T	QUE;
	
	PROJECT_DEVELOP_STATE_TYPE		ProjState;

	bool				NFCIrqFlg;		// 13.56Mˢ���жϱ�־
	bool				NRFUpdataFlg;	// 13.56M���±�־
	bool				KeyCntLimitFlg;	// ����300ms���ƶ�ʱ��
	
	uint32_t			PassCnt;	// ����������					
	uint32_t 			KeyCnt;		// ��Ч����������300ms�����
	uint32_t 			SendCnt;	// �������ʹ���							
	uint32_t			EchoCnt;	// ���Դ���
	
	// ��������������ǰû�յ���Ŀ����ֵ��ʱ�����������ڹ涨ʱ�����յ���Ŀ���Զ��ύ��ֵ
	bool 				RetainKeyExistFlg;	// ��ǰ�����м�ֵ��־
	bool				RetainKeySendFlg;	// ��Ҫ���ͱ�־
	uint8_t				RetainKeyVal;		// ��ǰ����ļ�ֵ
	
	//��û�յ���Ŀʱ�������������Ϊ��ʾ����ʾ���ã���ʵ������
	uint8_t 			LcdDisType;				//��ʾ���ͣ���ĸ���жϡ�����
	uint8_t 			LcdDisData;				//��ʾ����
	
}APP_PARAMETERS_T;


uint32_t APP_Init(void);

uint32_t APP_ParUpdate(void);

void APP_KeyHandler(void);
void APP_CmdHandler(void);

void APP_PwrOnRequest(void);

void APP_KeyPowerHandler(void);
void APP_KeyFnHandler(void);
void APP_KeyClearHandler(void);
void APP_KeySendHandler(void);
void APP_KeyMultiSendHandler(void);
void APP_KeyLastHandler(void);
void APP_KeyNextHandler(void);
void APP_KeyFnAdd1Handler(void);
void APP_KeyFnAdd2Handler(void);
void APP_KeyFnAdd3Handler(void);
void APP_KeyFnAdd4Handler(void);
void APP_KeyFnAdd5Handler(void);
void APP_KeyFnAdd6Handler(void);
void APP_KeyFnAdd7Handler(void);
void APP_KeyFnAdd8Handler(void);
void APP_KeyFnAddOKHandler(void);

void APP_KeySingleChoiceHandler(void);
void APP_Key6SingleChoiceHandler(void);
void APP_KeyMultiChoiceHandler(void);
void APP_KeyMultiSingleChoiceHandler(void);
void APP_KeyFreeHandler(void);
void APP_KeyActivityHandler(void);
void APP_KeyFigureHandler(void);
void APP_KeyJudgeHandler(void);
void APP_KeyEmptyHandler(void);

void APP_CmdTestHandler(void);
void APP_CmdQuestionHandler(void);
void APP_CmdPreHandler(void);
void APP_CmdAckHandler(void);
void APP_CmdSysOffHandler(void);
void APP_CmdGetStateHandler(void);
void APP_CmdClearScreenHandler(void);
void APP_CmdStartManualMatchHandler(void);
void APP_CmdAffirmManualMatchHandler(void);
void APP_CmdStopManualMatchHandler(void);
void APP_CmdSetScoreHandler(void);
void APP_CmdLcdCtrlHandler(void);

void APP_FetchQuesInfo(void);
void APP_PackQuestionInfo(void);



extern APP_PARAMETERS_T		APP;

#endif 




