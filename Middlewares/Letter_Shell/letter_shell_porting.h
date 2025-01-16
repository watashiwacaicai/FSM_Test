#ifndef __LETTER_SHELL_PORTING_H
#define __LETTER_SHELL_PORTING_H

#include "./Letter_Shell/shell.h"
#include "./cqueue/Cqueue.h"

#define SHELL_BUFFER_LEN 256 /*shell工作缓冲区的大小*/

extern cQueue_t* que_debug_data; /*用于缓存调试信息的队列*/
extern Shell debug_usart_shell; /*依赖于调试串口的shell*/

void debug_shell_init(void);
void shell_task_handler(void);

#endif
