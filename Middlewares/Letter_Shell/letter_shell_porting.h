#ifndef __LETTER_SHELL_PORTING_H
#define __LETTER_SHELL_PORTING_H

#define DEBUG_QUE_LEN		128			/*�������ݶ��еĳ���*/
#define SHELL_BUFFER_LEN    256 		/*shell�����������Ĵ�С*/

/* �������ݶ������� */
typedef struct {
    char members[DEBUG_QUE_LEN];
    int front;  // ����ͷָ��
    int rear;   // ����βָ��
    int size;   // ��ǰ�����еĳ�Ա����
} debug_queue_t;

extern debug_queue_t debug_data_queue; /* ����ָ����� */

void debug_shell_init(void);
void shell_task_handler(void);

int debug_que_send(debug_queue_t *q, char* member);
int debug_que_read(debug_queue_t *q, char* member); 

#endif
