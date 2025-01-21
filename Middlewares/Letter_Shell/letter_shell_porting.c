#include "main.h"
#include "usart.h"
#include "user_usart.h"
#include "./Letter_Shell/shell.h"
#include "./Letter_Shell/letter_shell_porting.h"

/*ȫ�ֱ�������*/
debug_queue_t debug_data_queue; /* ����ָ����� */

/*��̬��������*/
static Shell debug_usart_shell; /*�����ڵ��Դ��ڵ�shell*/
static char shell_buffer[SHELL_BUFFER_LEN]; /*shell����������*/

/*��̬��������*/
static short shellWrite(char *data, unsigned short len);
static void debug_que_init(debug_queue_t *q);

/*********��̬��������**********/

/*shell���ͺ���*/
static short shellWrite(char *data, unsigned short len)
{
	HAL_UART_Transmit(&DEBUG_USART, (uint8_t *)data, (uint16_t)len, 1000); /*��������ʽ���ͣ������жϳ�ͻ*/
	
	return len;
}

/* ��ʼ������ */
static void debug_que_init(debug_queue_t *q) 
{
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

/********ȫ�ֺ�������***********/

/* ����з������� */
int debug_que_send(debug_queue_t *q, char* member) 
{
    if (q->size < DEBUG_QUE_LEN) 
	{
		q->rear = (q->rear + 1) % DEBUG_QUE_LEN;
		q->members[q->rear] = *member;
		q->size++;
		return 1;
    }else{
		return 0;
	}    
}

/* �Ӷ����ж�ȡ���� */
int debug_que_read(debug_queue_t *q, char* member) 
{
    if (q->size > 0) 
	{
        *member = q->members[q->front];
		q->front = (q->front + 1) % DEBUG_QUE_LEN;
		q->size--;
		return 1;
    }else{
		return 0;
	}   
}

/*shell��ʼ������*/
void debug_shell_init(void)
{	
	debug_que_init(&debug_data_queue); /*��ʼ���������ݶ���*/
    debug_usart_shell.write = shellWrite; /*�󶨴��ڷ��ͺ���*/
    shellInit(&debug_usart_shell, shell_buffer, SHELL_BUFFER_LEN); /*��ʼ��shell����*/
}

/*ʱ��Ƭ��ѯ���Ƶ�shell������*/
void shell_task_handler(void)
{
	char* shell_rec_data;
	
	/*�����Ϣ���в�Ϊ��*/
	if(debug_que_read(&debug_data_queue, shell_rec_data))
	{					
		shellHandler(&debug_usart_shell, *shell_rec_data);
	}	
}
