#include "lw_queue.h"
#include "stdlib.h"
#include "lw_queue_porting.h"

/*全局函数定义*/

/*创建队列*/
lw_que_t* lw_queue_create(int capacity)
{
    lw_que_t* queue = (lw_que_t*)lwq_malloc(sizeof(lw_que_t));
    if (queue == NULL) 
    {
        return NULL;  /*内存分配失败*/
    }

    queue->data = (void**)lwq_malloc(sizeof(void*) * capacity);
    if (queue->data == NULL) 
    {
        lwq_free(queue);
        return NULL;  /*内存分配失败*/
    }

    queue->front = 0;
    queue->rear = 0;
    queue->capacity = capacity;
    queue->size = 0;

    return queue;
}

/*销毁队列*/
void lw_queue_destroy(lw_que_t* queue)
{
    if (queue == NULL) 
    {
        return;
    }

    lwq_free(queue->data);
    lwq_free(queue);
}

/*向队列写入数据*/
char lw_queue_write(lw_que_t* queue, void* data)
{
    if (queue == NULL || queue->size >= queue->capacity) 
    {
        return LWQ_ERR;  /*队列已满或无效队列*/
    }

    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;

    return LWQ_SUCCESS;
}

/*从队列读取数据*/
void* lw_queue_read(lw_que_t* queue, char* success)
{
    if (queue == NULL || queue->size == 0) 
    {
        if (success != NULL) {
            *success = LWQ_ERR;  // 队列为空或无效队列
        }
        return NULL;
    }

    void* data = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    if (success != NULL) 
    {
        *success = LWQ_SUCCESS;  // 读取成功
    }

    return data;
}
