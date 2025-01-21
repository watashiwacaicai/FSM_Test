#include "main.h"
#include "usart.h"
#include "user_usart.h"
#include "./Letter_Shell/shell.h"
#include "./Letter_Shell/letter_shell_porting.h"

/*全局变量定义*/
debug_queue_t debug_data_queue; /* 定义指令队列 */

/*静态变量定义*/
static Shell debug_usart_shell; /*依赖于调试串口的shell*/
static char shell_buffer[SHELL_BUFFER_LEN]; /*shell工作缓冲区*/

/*静态函数声明*/
static short shellWrite(char *data, unsigned short len);
static void debug_que_init(debug_queue_t *q);

/*********静态函数定义**********/

/*shell发送函数*/
static short shellWrite(char *data, unsigned short len)
{
	HAL_UART_Transmit(&DEBUG_USART, (uint8_t *)data, (uint16_t)len, 1000); /*串口阻塞式发送，避免中断冲突*/
	
	return len;
}

/* 初始化队列 */
static void debug_que_init(debug_queue_t *q) 
{
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

/********全局函数定义***********/

/* 向队列发送数据 */
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

/* 从队列中读取数据 */
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

/*shell初始化函数*/
void debug_shell_init(void)
{	
	debug_que_init(&debug_data_queue); /*初始化调试数据队列*/
    debug_usart_shell.write = shellWrite; /*绑定串口发送函数*/
    shellInit(&debug_usart_shell, shell_buffer, SHELL_BUFFER_LEN); /*初始化shell对象*/
}

/*时间片轮询机制的shell任务函数*/
void shell_task_handler(void)
{
	char* shell_rec_data;
	
	/*如果消息队列不为空*/
	if(debug_que_read(&debug_data_queue, shell_rec_data))
	{					
		shellHandler(&debug_usart_shell, *shell_rec_data);
	}	
}
