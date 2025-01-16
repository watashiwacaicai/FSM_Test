#include "main.h"
#include "string.h"
#include "usart.h"
#include "./Letter_Shell/shell.h"
#include "./cqueue/Cqueue.h"
#include "./Letter_Shell/letter_shell_porting.h"

/*ȫ�ֱ�������*/
cQueue_t* que_debug_data; /*���ڻ��������Ϣ�Ķ���*/
Shell debug_usart_shell; /*�����ڵ��Դ��ڵ�shell*/

/*��̬��������*/
static char shell_buffer[SHELL_BUFFER_LEN]; /*shell����������*/

/*********��̬��������**********/

/*shell��ȡ����*/
//static short shellRead(char *data, unsigned short len)
//{
//	char que_err;
//	char* shell_rec_data;
//	
//	shell_rec_data = (char*)cQRcv(que_debug_data, &que_err);
//	len = strlen(shell_rec_data);
//	
//	/*�����Ϣ���в�Ϊ��*/
//	if(que_err != ERR_Q_EMPTY)
//	{
//		for(uint8_t i = 0; i < len; i++)
//		{
//			shellHandler(&debug_usart_shell, shell_rec_data[i]);
//		}
//				
//		return len;
//		
//	}else{
//	
//		return 0;
//	}

//}

/*shell���ͺ���*/
static short shellWrite(char *data, unsigned short len)
{
	HAL_UART_Transmit(&DEBUG_USART, (uint8_t *)data, (uint16_t)len, 0xFF); /*��������ʽ����*/
	
	return len;
}

/********ȫ�ֺ�������***********/

/*shell��ʼ������*/
void debug_shell_init(void)
{
	que_debug_data = cQcreate(DEBUG_QUE_LEN); /*����һ������Ϊ5�Ķ���*/
	
//	debug_usart_shell.read = shellRead;
    debug_usart_shell.write = shellWrite;
    shellInit(&debug_usart_shell, shell_buffer, SHELL_BUFFER_LEN);
}

/*����DMA��shell������*/
void shell_task_handler(void)
{
	char que_err;
	char* shell_rec_data;
	uint16_t len;
	
	shell_rec_data = (char*)cQRcv(que_debug_data, &que_err);
	len = strlen(shell_rec_data);
	
	/*�����Ϣ���в�Ϊ��*/
	if(que_err != ERR_Q_EMPTY)
	{
		for(uint8_t i = 0; i < len; i++)
		{
			shellHandler(&debug_usart_shell, shell_rec_data[i]);
		}				
	}
}
