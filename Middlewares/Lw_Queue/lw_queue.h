#ifndef __LW_QUEUE_H
#define __LW_QUEUE_H

/*�����������*/
typedef struct {
    void** data;        /* ���е����ݴ洢�� */
    int front;          /* ����ͷָ�� */
    int rear;           /* ����βָ�� */
    int capacity;       /* ���е����� */
    int size;           /* ���е�ǰ��Ԫ�ظ��� */
}lw_que_t;

/*�������Ͷ���*/
#define LWQ_SUCCESS     'Y'
#define LWQ_ERR         'N'

lw_que_t* lw_queue_create(int capacity);
void lw_queue_destroy(lw_que_t* queue);
char lw_queue_write(lw_que_t* queue, void* data);
void* lw_queue_read(lw_que_t* queue, char* success);

#endif
