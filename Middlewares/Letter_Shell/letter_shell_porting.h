#ifndef __LETTER_SHELL_PORTING_H
#define __LETTER_SHELL_PORTING_H

#include "./Letter_Shell/shell.h"
#include "./cqueue/Cqueue.h"

#define SHELL_BUFFER_LEN 256 /*shell�����������Ĵ�С*/

extern cQueue_t* que_debug_data; /*���ڻ��������Ϣ�Ķ���*/
extern Shell debug_usart_shell; /*�����ڵ��Դ��ڵ�shell*/

void debug_shell_init(void);
void shell_task_handler(void);

#endif
