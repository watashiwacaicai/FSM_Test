#include "lw_queue.h"
#include "stdlib.h"
#include "lw_queue_porting.h"

/*ȫ�ֺ�������*/

/*��������*/
lw_que_t* lw_queue_create(int capacity)
{
    lw_que_t* queue = (lw_que_t*)lwq_malloc(sizeof(lw_que_t));
    if (queue == NULL) 
    {
        return NULL;  /*�ڴ����ʧ��*/
    }

    queue->data = (void**)lwq_malloc(sizeof(void*) * capacity);
    if (queue->data == NULL) 
    {
        lwq_free(queue);
        return NULL;  /*�ڴ����ʧ��*/
    }

    queue->front = 0;
    queue->rear = 0;
    queue->capacity = capacity;
    queue->size = 0;

    return queue;
}

/*���ٶ���*/
void lw_queue_destroy(lw_que_t* queue)
{
    if (queue == NULL) 
    {
        return;
    }

    lwq_free(queue->data);
    lwq_free(queue);
}

/*�����д������*/
char lw_queue_write(lw_que_t* queue, void* data)
{
    if (queue == NULL || queue->size >= queue->capacity) 
    {
        return LWQ_ERR;  /*������������Ч����*/
    }

    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;

    return LWQ_SUCCESS;
}

/*�Ӷ��ж�ȡ����*/
void* lw_queue_read(lw_que_t* queue, char* success)
{
    if (queue == NULL || queue->size == 0) 
    {
        if (success != NULL) {
            *success = LWQ_ERR;  // ����Ϊ�ջ���Ч����
        }
        return NULL;
    }

    void* data = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    if (success != NULL) 
    {
        *success = LWQ_SUCCESS;  // ��ȡ�ɹ�
    }

    return data;
}
