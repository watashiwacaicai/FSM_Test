#ifndef __LETTER_SHELL_PORTING_H
#define __LETTER_SHELL_PORTING_H

#define DEBUG_QUE_LEN		128			/*调试数据队列的长度*/
#define SHELL_BUFFER_LEN    256 		/*shell工作缓冲区的大小*/

/* 调试数据队列类型 */
typedef struct {
    char members[DEBUG_QUE_LEN];
    int front;  // 队列头指针
    int rear;   // 队列尾指针
    int size;   // 当前队列中的成员数量
} debug_queue_t;

extern debug_queue_t debug_data_queue; /* 定义指令队列 */

void debug_shell_init(void);
void shell_task_handler(void);

int debug_que_send(debug_queue_t *q, char* member);
int debug_que_read(debug_queue_t *q, char* member); 

#endif
