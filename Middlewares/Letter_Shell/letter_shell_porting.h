#ifndef __LETTER_SHELL_PORTING_H
#define __LETTER_SHELL_PORTING_H

#include "./Lw_rb/lw_rb.h"

#define DEBUG_RB_LEN		128			/*调试数据环形缓冲区的长度*/
#define SHELL_BUFFER_LEN    256 		/*shell工作缓冲区的大小*/

extern lw_rb_t* debug_data_rb; /* 环形缓冲区 */

void debug_shell_init(void);
void shell_task_handler(void);


#endif
