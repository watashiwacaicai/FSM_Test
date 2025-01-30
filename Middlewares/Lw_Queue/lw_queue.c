#include "lw_queue.h"
#include "stdlib.h"
#include "stdbool.h"
#include "lw_queue_porting.h"

/*��̬��������*/

/**
 * @brief �ж϶����Ƿ�Ϊ��
 * @param ���о��
 * @return Ϊ�գ�ture
 * @return �ǿգ�false
 */
static bool is_empty(lw_que_t* queue)
{
    return queue->front == queue->rear && queue->data[queue->front] == NULL;
}

/**
 * @brief �ж϶����Ƿ�����
 * @param ���о��
 * @return ������ture
 * @return δ����false
 */
static bool is_full(lw_que_t* queue)
{
    return queue->front == queue->rear && queue->data[queue->front] != NULL;
}

/*ȫ�ֺ�������*/

/**
 * @brief ��������
 * @param ���г���
 * @return ���о��
 */
lw_que_t* lw_queue_create(uint32_t capacity)
{
    /*��̬������п��ƿ���ڴ�ռ�*/
    lw_que_t* queue = (lw_que_t*)lwq_malloc(sizeof(lw_que_t));

    if (queue == NULL) 
    {
        return NULL;  /*�ڴ����ʧ��*/
    }

    /*��̬��������ڲ����ݵ��ڴ�ռ�*/
    queue->data = (void**)lwq_malloc(sizeof(void*) * capacity);

    if (queue->data == NULL) 
    {
        lwq_free(queue);
        return NULL;  /*�ڴ����ʧ��*/
    }

    queue->front = 0;
    queue->rear = 0;
    queue->capacity = capacity;

    /*��ʼ������Ϊ��*/
    for (uint32_t i = 0; i < capacity; i++) 
    {
        queue->data[i] = NULL;
    }

    return queue;
}

/**
 * @brief ���ٶ���
 * @param ���о��
 */
void lw_queue_destroy(lw_que_t* queue)
{
    if (queue == NULL) 
    {
        return;
    }

    lwq_free(queue->data);
    lwq_free(queue);
}

/**
 * @brief д�����
 * @param ���о��
 * @param ����ָ��
 * @return �ɹ���LWQ_SUCCESS
 * @return ʧ�ܣ�LWQ_ERR
 */
char lw_queue_write(lw_que_t* queue, void* data)
{
    if (queue == NULL || is_full(queue)) 
    {
        return LWQ_ERR;  /*������������Ч����*/
    }

    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % queue->capacity;
   
    return LWQ_SUCCESS;
}

/**
 * @brief ��ȡ����
 * @param ���о��
 * @param �洢��������ַ�
 * @return �ɹ�������ָ��
 * @return ʧ�ܣ�NULL
 */
void* lw_queue_read(lw_que_t* queue, char* success)
{
    if (queue == NULL || is_empty(queue)) 
    {
        if (success != NULL) 
        {
            *success = LWQ_ERR;  /*����Ϊ�ջ���Ч����*/
        }
        return NULL;
    }

    void* data = queue->data[queue->front];
    queue->data[queue->front] = NULL;
    queue->front = (queue->front + 1) % queue->capacity;

    if (success != NULL) 
    {
        *success = LWQ_SUCCESS;  /*��ȡ�ɹ�*/
    }
    return data;
}
