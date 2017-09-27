/**
  ******************************************************************************
  * @file    lib_TagType4.c
  * @author  MMY Application Team
  * @version V1.0.1
  * @date    06-December-2016
  * @brief   This file help to manage TagType4.
  ******************************************************************************
  * @attention
  * 
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MMY-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  * 
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "lib_TagType4.h"


/**
 * @brief  This structure contains the data of the CC file
 */
sCCFileInfo CCFileStruct;
M24SR_PARAMETERS_T 		NFC;


/* 
 * @ע���˲��ִ�����ݹٷ�������ֲ������
	    ��ֲ�����кܶ����õĺ��������ɵ��ˣ�ֻ������������Ҫ�Ĳ���
	    Դ������ο��ٷ�����
*/

void NFC_Init(void)
{
	uint16_t TmpLen = 0;
	
	TT4_Init();	
	M24SR_GetUID(NFC.UID);
	TT4_ReadNDEF(NFC.DataRead);
	M24SR_ManageGPO(INTERRUPT,RF_GPO);		//GPO����Ϊ�ж�ģʽ
	M24SR_Deselect();						//�ͷ�I2C����Ȩ
	
	TmpLen = NFC.DataRead[0] << 8 | NFC.DataRead[1];		//����M24SR�洢�����ݳ���
	
//	if(TmpLen > 10)											//����̫�̿϶��Ǵ��
//	{
//		if(XOR_Cal(NFC.DataRead+2,TmpLen - 3) == NFC.DataRead[TmpLen - 1])
//		{
			NFC.MatchSucceedFlg = true;
//		}
//		else
//		{
//			NFC.MatchSucceedFlg = false;
//		}	
//	}
//	else
//	{
//		NFC.MatchSucceedFlg = false;
//	}
}



/**
  * @brief  This fonction initialize Tag Type 4
	* @param	None 
  * @retval SUCCESS : Initialization done
  */
uint16_t TT4_Init (void)
{
	uint16_t status = SUCCESS;
	uint8_t CCBuffer[15];
	sCCFileInfo *pCCFile;
	
	pCCFile = &CCFileStruct;
	
	status = M24SR_Initialization( CCBuffer, sizeof(CCBuffer));
	
	pCCFile->NumberCCByte = (uint16_t) ((CCBuffer[0x00]<<8) | CCBuffer[0x01]);
	pCCFile->Version = CCBuffer[0x02];
	pCCFile->MaxReadByte = (uint16_t) ((CCBuffer[0x03]<<8) | CCBuffer[0x04]);
	pCCFile->MaxWriteByte = (uint16_t) ((CCBuffer[0x05]<<8) | CCBuffer[0x06]);
	pCCFile->TField = CCBuffer[0x07];
	pCCFile->LField = CCBuffer[0x08];
	pCCFile->FileID = (uint16_t) ((CCBuffer[0x09]<<8) | CCBuffer[0x0A]);
	pCCFile->NDEFFileMaxSize = (uint16_t) ((CCBuffer[0x0B]<<8) | CCBuffer[0x0C]);
	pCCFile->ReadAccess = CCBuffer[0x0D];
	pCCFile->WriteAccess = CCBuffer[0x0E];	
	
	return status;
}	

/**
  * @brief  This fonction read NDEF file
	* @param	pNDEF : pointer on buffer to fill with NDEF data
  * @retval SUCCESS : NDEF file data have been retrieve
	* @retval ERROR : Not able to get NDEF file data
  */
uint16_t TT4_ReadNDEF(uint8_t *pNDEF)
{
	uint16_t status = ERROR;
	sCCFileInfo *pCCFile;
	
	pCCFile = &CCFileStruct;
	
	if(M24SR_OpenNDEFSession(pCCFile->FileID, TAKE_SESSION) == SUCCESS)
	{
		status = NDEF_ReadNDEF(pNDEF);
		M24SR_CloseNDEFSession(pCCFile->FileID);
	}
	
	return status;
}

/**
  * @brief  This fonction write NDEF file
	* @param	pNDEF : pointer on buffer that contain the NDEF data
  * @retval SUCCESS : NDEF file data have been stored
	* @retval ERROR : Not able to store NDEF file
  */
uint16_t TT4_WriteNDEF(uint8_t *pNDEF)
{
	uint16_t status = ERROR;
	sCCFileInfo *pCCFile;
	
	pCCFile = &CCFileStruct;
	
	if(M24SR_OpenNDEFSession(pCCFile->FileID, ASK_FOR_SESSION) == SUCCESS)
	{
		status = NDEF_WriteNDEF( pNDEF);
		M24SR_CloseNDEFSession(pCCFile->FileID);
	}
	
	return status;
}

//�˴������Ƿ����ܽ������ų��Ŀ���
//false:�����ܵ�ų�����
//true:û�ܵ�ų�����
bool NFC_IsFieldCtrl(void)
{
	return M24SR_ACTION_COMPLETED == M24SR_GetSession();
}











/******************* (C) COPYRIGHT 2013 STMicroelectronics *****END OF FILE****/

