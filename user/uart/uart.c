#include "uart.h"


void DEBUG_Init(void)
{
	UART_Init();
}

//��ӡ����N���ֽ�
void UART_PrintfNByte(uint8_t *buf,uint8_t len)
{
	uint8_t i;
	for(i = 0;i < len;i++)
	{
		printf("%02X ",*(buf+i));
	}
	printf(" \r\n");
}


void UART_Init(void)//���ڳ�ʼ������
  {  
//	simple_uart_config(RTS_PIN_NUMBER, TX_PIN_NUMBER, CTS_PIN_NUMBER, RX_PIN_NUMBER, HWFC);
//	simple_uart_config(RTS_PIN_NUMBER_1, TX_PIN_NUMBER_1, CTS_PIN_NUMBER_1, RX_PIN_NUMBER_1, HWFC_1);
	simple_uart_config(RTS_PIN_NUMBER_2, TX_PIN_NUMBER_2, CTS_PIN_NUMBER_2, RX_PIN_NUMBER_2, HWFC_2);

}	



		
/************************************************************** 
* ������  : fputc()
* ����    : �ض���putc��������������ʹ��printf�����Ӵ���1��ӡ���
*************************************************************/
int fputc(int ch, FILE *f)
{
		/* Place your implementation of fputc here */
		/* ����һ���ֽڵ����� */
		simple_uart_put((uint8_t)ch);
		/* �ȴ�������� */
		return ch;
}

/************************************************************** 
* ������  : fgetc()
* ����    : �ض���getc��������������ʹ��scanf�����Ӵ���1��ȡ����
*************************************************************/
int fgetc(FILE *f)
{
		/* �ȴ�����1�������� */
		/* ���ؽ��յ������� */
		return (int)simple_uart_get();
}



