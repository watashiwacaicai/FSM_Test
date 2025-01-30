#include "main.h"
#include "usart.h"
#include "user_usart.h"
#include "./Lw_rb/lw_rb.h"
#include "./Letter_Shell/shell.h"
#include "./Letter_Shell/letter_shell_porting.h"

/*ȫ�ֱ�������*/
lw_rb_t* debug_data_rb; /* ���廷�λ����� */

/*��̬��������*/
static Shell debug_usart_shell; /*�����ڵ��Դ��ڵ�shell*/
static char shell_buffer[SHELL_BUFFER_LEN]; /*shell����������*/

/*��̬��������*/
static short shellWrite(char *data, unsigned short len);

/*********��̬��������**********/

/*shell���ͺ���*/
static short shellWrite(char *data, unsigned short len)
{
	HAL_UART_Transmit(&DEBUG_USART, (uint8_t *)data, (uint16_t)len, 1000); /*��������ʽ���ͣ������жϳ�ͻ*/
	
	return len;
}

/********ȫ�ֺ�������***********/

/*shell��ʼ������*/
void debug_shell_init(void)
{	
	debug_data_rb = lw_rb_create(DEBUG_RB_LEN); /*�����������ݻ��λ�����*/
    debug_usart_shell.write = shellWrite; /*�󶨴��ڷ��ͺ���*/
    shellInit(&debug_usart_shell, shell_buffer, SHELL_BUFFER_LEN); /*��ʼ��shell����*/
}

/*ʱ��Ƭ��ѯ���Ƶ�shell������*/
void shell_task_handler(void)
{
	char shell_rec_err;
	char shell_rec_data;
	
	shell_rec_data = lw_rb_read(debug_data_rb, &shell_rec_err);
	
	/*�����Ϣ���в�Ϊ��*/
	if(shell_rec_err == LW_RB_SUCCESS)
	{					
		shellHandler(&debug_usart_shell, shell_rec_data);
	}	
}
