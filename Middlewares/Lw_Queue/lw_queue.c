#include "lw_queue.h"
#include "stdlib.h"
#include "stdbool.h"
#include "lw_queue_porting.h"

/*静态函数定义*/

/**
 * @brief 判断队列是否为空
 * @param 队列句柄
 * @return 为空：ture
 * @return 非空：false
 */
static bool is_empty(lw_que_t* queue)
{
    return queue->front == queue->rear && queue->data[queue->front] == NULL;
}

/**
 * @brief 判断队列是否已满
 * @param 队列句柄
 * @return 已满：ture
 * @return 未满：false
 */
static bool is_full(lw_que_t* queue)
{
    return queue->front == queue->rear && queue->data[queue->front] != NULL;
}

/*全局函数定义*/

/**
 * @brief 创建队列
 * @param 队列长度
 * @return 队列句柄
 */
lw_que_t* lw_queue_create(uint32_t capacity)
{
    /*动态申请队列控制块的内存空间*/
    lw_que_t* queue = (lw_que_t*)lwq_malloc(sizeof(lw_que_t));

    if (queue == NULL) 
    {
        return NULL;  /*内存分配失败*/
    }

    /*动态申请队列内部数据的内存空间*/
    queue->data = (void**)lwq_malloc(sizeof(void*) * capacity);

    if (queue->data == NULL) 
    {
        lwq_free(queue);
        return NULL;  /*内存分配失败*/
    }

    queue->front = 0;
    queue->rear = 0;
    queue->capacity = capacity;

    /*初始化队列为空*/
    for (uint32_t i = 0; i < capacity; i++) 
    {
        queue->data[i] = NULL;
    }

    return queue;
}

/**
 * @brief 销毁队列
 * @param 队列句柄
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
 * @brief 写入队列
 * @param 队列句柄
 * @param 数据指针
 * @return 成功：LWQ_SUCCESS
 * @return 失败：LWQ_ERR
 */
char lw_queue_write(lw_que_t* queue, void* data)
{
    if (queue == NULL || is_full(queue)) 
    {
        return LWQ_ERR;  /*队列已满或无效队列*/
    }

    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % queue->capacity;
   
    return LWQ_SUCCESS;
}

/**
 * @brief 读取队列
 * @param 队列句柄
 * @param 存储错误码的字符
 * @return 成功：数据指针
 * @return 失败：NULL
 */
void* lw_queue_read(lw_que_t* queue, char* success)
{
    if (queue == NULL || is_empty(queue)) 
    {
        if (success != NULL) 
        {
            *success = LWQ_ERR;  /*队列为空或无效队列*/
        }
        return NULL;
    }

    void* data = queue->data[queue->front];
    queue->data[queue->front] = NULL;
    queue->front = (queue->front + 1) % queue->capacity;

    if (success != NULL) 
    {
        *success = LWQ_SUCCESS;  /*读取成功*/
    }
    return data;
}
