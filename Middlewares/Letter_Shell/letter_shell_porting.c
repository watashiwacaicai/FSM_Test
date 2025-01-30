#include "main.h"
#include "usart.h"
#include "user_usart.h"
#include "./Lw_rb/lw_rb.h"
#include "./Letter_Shell/shell.h"
#include "./Letter_Shell/letter_shell_porting.h"

/*全局变量定义*/
lw_rb_t* debug_data_rb; /* 定义环形缓冲区 */

/*静态变量定义*/
static Shell debug_usart_shell; /*依赖于调试串口的shell*/
static char shell_buffer[SHELL_BUFFER_LEN]; /*shell工作缓冲区*/

/*静态函数声明*/
static short shellWrite(char *data, unsigned short len);

/*********静态函数定义**********/

/*shell发送函数*/
static short shellWrite(char *data, unsigned short len)
{
	HAL_UART_Transmit(&DEBUG_USART, (uint8_t *)data, (uint16_t)len, 1000); /*串口阻塞式发送，避免中断冲突*/
	
	return len;
}

/********全局函数定义***********/

/*shell初始化函数*/
void debug_shell_init(void)
{	
	debug_data_rb = lw_rb_create(DEBUG_RB_LEN); /*创建调试数据环形缓冲区*/
    debug_usart_shell.write = shellWrite; /*绑定串口发送函数*/
    shellInit(&debug_usart_shell, shell_buffer, SHELL_BUFFER_LEN); /*初始化shell对象*/
}

/*时间片轮询机制的shell任务函数*/
void shell_task_handler(void)
{
	char shell_rec_err;
	char shell_rec_data;
	
	shell_rec_data = lw_rb_read(debug_data_rb, &shell_rec_err);
	
	/*如果消息队列不为空*/
	if(shell_rec_err == LW_RB_SUCCESS)
	{					
		shellHandler(&debug_usart_shell, shell_rec_data);
	}	
}
