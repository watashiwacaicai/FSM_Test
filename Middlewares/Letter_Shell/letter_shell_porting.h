#ifndef __LETTER_SHELL_PORTING_H
#define __LETTER_SHELL_PORTING_H

#include "./Lw_rb/lw_rb.h"

#define DEBUG_RB_LEN		128			/*�������ݻ��λ������ĳ���*/
#define SHELL_BUFFER_LEN    256 		/*shell�����������Ĵ�С*/

extern lw_rb_t* debug_data_rb; /* ���λ����� */

void debug_shell_init(void);
void shell_task_handler(void);


#endif
