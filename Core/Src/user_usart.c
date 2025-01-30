#include "usart.h"
#include "user_usart.h"
#include "stdio.h" /*引入格式化字符*/
#include "stdarg.h" /*引入不定参数*/
#include "string.h"
#include "./Letter_Shell/letter_shell_porting.h"
#include "./Lw_rb/lw_rb.h"

/*静态变量定义*/
static char rec_data; /*串口接收到的一个字节的数据*/

/*********全局函数定义**********/

/*开启调试串口接收函数*/
void debug_usart_rec_start(void)
{		
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&rec_data, 1);
}

/*调试格式化输出函数*/
int debug_printf(const char *format, ...)
{
    char buffer[128]; /*定义一个缓冲区，用于存储格式化后的字符串*/
    va_list arg;      /*定义一个可变参数列表*/
    int len;          /*定义一个变量，用于存储格式化后字符串的长度*/
   
    va_start(arg, format); /*初始化可变参数列表，指向第一个可变参数*/	
    len = vsnprintf(buffer, sizeof(buffer), format, arg); /*进行字符串格式化*/  
    va_end(arg); /*清理可变参数列表*/
    HAL_UART_Transmit(&DEBUG_USART, (uint8_t *)buffer, (uint16_t)len, 1000); /*串口阻塞式发送，避免中断冲突*/

    return len;
}

/*调试串口单字节接收函数*/
void DEBUG_UART_RxCallback(void)
{			
	if(__HAL_UART_GET_FLAG(&DEBUG_USART, UART_FLAG_RXNE ) != RESET)
	{				
		rec_data = (char)READ_REG(DEBUG_USART.Instance->DR); /*直接从寄存器中读取数据*/	
		lw_rb_write(debug_data_rb, rec_data); /*将接收到的数据载入调试信息队列*/
	}
}
