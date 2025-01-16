#include "main.h"
#include "string.h"
#include "usart.h"
#include "./Letter_Shell/shell.h"
#include "./cqueue/Cqueue.h"
#include "./Letter_Shell/letter_shell_porting.h"

/*全局变量定义*/
cQueue_t* que_debug_data; /*用于缓存调试信息的队列*/
Shell debug_usart_shell; /*依赖于调试串口的shell*/

/*静态变量定义*/
static char shell_buffer[SHELL_BUFFER_LEN]; /*shell工作缓冲区*/

/*********静态函数定义**********/

/*shell读取函数*/
//static short shellRead(char *data, unsigned short len)
//{
//	char que_err;
//	char* shell_rec_data;
//	
//	shell_rec_data = (char*)cQRcv(que_debug_data, &que_err);
//	len = strlen(shell_rec_data);
//	
//	/*如果消息队列不为空*/
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

/*shell发送函数*/
static short shellWrite(char *data, unsigned short len)
{
	HAL_UART_Transmit(&DEBUG_USART, (uint8_t *)data, (uint16_t)len, 0xFF); /*串口阻塞式发送*/
	
	return len;
}

/********全局函数定义***********/

/*shell初始化函数*/
void debug_shell_init(void)
{
	que_debug_data = cQcreate(DEBUG_QUE_LEN); /*创建一个长度为5的队列*/
	
//	debug_usart_shell.read = shellRead;
    debug_usart_shell.write = shellWrite;
    shellInit(&debug_usart_shell, shell_buffer, SHELL_BUFFER_LEN);
}

/*适配DMA的shell任务函数*/
void shell_task_handler(void)
{
	char que_err;
	char* shell_rec_data;
	uint16_t len;
	
	shell_rec_data = (char*)cQRcv(que_debug_data, &que_err);
	len = strlen(shell_rec_data);
	
	/*如果消息队列不为空*/
	if(que_err != ERR_Q_EMPTY)
	{
		for(uint8_t i = 0; i < len; i++)
		{
			shellHandler(&debug_usart_shell, shell_rec_data[i]);
		}				
	}
}
