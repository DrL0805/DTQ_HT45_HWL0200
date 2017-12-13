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


//软件运行状态,
typedef enum
{
	PROJECT_RELEASE,		//发布状态 0
	PROJECT_DEBUG			//测试状态 1
}PROJECT_DEVELOP_STATE_TYPE;

typedef enum
{
	CMD_QUESTION		= 0x10,					
	CMD_CLEAR_SCREEN    = 0x11,
	CMD_GET_STATE		= 0x24,
	CMD_SYS_OFF			= 0x25,
	CMD_TEST		= 0xF1,
	CMD_PRE				= 0x51,					// 前导帧
	CMD_ACK				= 0x52,
	CMD_START_MANUAL_MATCH = 0x40,				
	CMD_AFFIRM_MANUAL_MATCH = 0x41,				
	CMD_STOP_MANUAL_MATCH = 0x42,
	CMD_BROADCAST = 0x43,
	CMD_AUTO_MATCH = 0x44,
	CMD_SET_SCORE = 0X12,			// 设置学分
	CMD_LCD_CTRL = 0x13			// 控制LCD显示（回显）
}APP_CMD_TYPE;


typedef enum
{
	QUE_SINGLE_CHOICE = 0x01,				// 单题单选
	QUE_JUDGE = 0x02,				// 单题判断
	QUE_MULTI_CHOICE = 0x03,				// 单题多选
	QUE_ACTIVITY    = 0x04,				// 抢红包
	QUE_MULTI_SINGLE_CHOICE = 0x05,		// 多题单选
	QUE_FREE = 0x06,						// 通用题
	QUE_6_SINGLE_CHOICE = 0X07,				// 6键单选题，
	QUE_FREE_STOP = 0x80					// 通用题停止作答
}APP_QUE_TYPE;

typedef struct
{
	APP_CMD_TYPE 	CmdType;
	uint8_t			CmdLen;
	uint8_t			CmdData[240];
}CMD_PARAMETERS_T;

typedef struct
{
	bool				AnsweredFlg;						// 已作答标志，根据好未来要求，收到题目后只允许作答一次
	bool				ReceiveQueFlg;						// 收到题目标志
	bool				KeySendLimitFlg;					// 按键发送限制标志
	
	bool				KeyQueryAllowFlg;					// 按键举手允许标志
	bool				KeyAttendAllowFlg;					// 按键考勤允许标志
	
	uint8_t 			LastPackNum[4];						// 上次接收的题目包号，占4bit，用于区分是否是新的题目包
	
	APP_QUE_TYPE 		Type;
	uint8_t				Answer;								// 作答结果
	
	// 多题单选作答相关
	uint8_t 			MultiAnswer[16];	
	uint8_t 			pMultiAnswerNum;
}QUE_PARAMETERS_T;

typedef struct
{
	CMD_PARAMETERS_T 	CMD;
	QUE_PARAMETERS_T	QUE;
	
	PROJECT_DEVELOP_STATE_TYPE		ProjState;

	bool				NFCIrqFlg;		// 13.56M刷卡中断标志
	bool				NRFUpdataFlg;	// 13.56M更新标志
	bool				KeyCntLimitFlg;	// 按键300ms限制定时器
	
	uint32_t			PassCnt;	// 物理按键次数					
	uint32_t 			KeyCnt;		// 有效按键次数（300ms间隔）
	uint32_t 			SendCnt;	// 按键发送次数							
	uint32_t			EchoCnt;	// 回显次数
	
	// 按键触发后，若当前没收到题目，键值暂时存起来，若在规定时间内收到题目，自动提交键值
	bool 				RetainKeyExistFlg;	// 当前保存有键值标志
	bool				RetainKeySendFlg;	// 需要发送标志
	uint8_t				RetainKeyVal;		// 当前保存的键值
	
	//当没收到题目时，按键结果仅作为显示（演示）用，无实际意义
	uint8_t 			LcdDisType;				//显示类型，字母、判断、数字
	uint8_t 			LcdDisData;				//显示内容
	
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




