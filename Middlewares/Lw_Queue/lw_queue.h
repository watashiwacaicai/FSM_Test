#ifndef __LW_QUEUE_H
#define __LW_QUEUE_H

#include "stdint.h"

/*返回类型定义*/
#define LWQ_SUCCESS     'Y'
#define LWQ_ERR         'N'

typedef struct 
{
    void** data;        /*队列的数据存储区*/
    uint32_t front;          /*队列头指针*/
    uint32_t rear;           /*队列尾指针*/
    uint32_t capacity;       /*队列的容量*/

} lw_que_t;

lw_que_t* lw_queue_create(uint32_t capacity);
void lw_queue_destroy(lw_que_t* queue);
char lw_queue_write(lw_que_t* queue, void* data);
void* lw_queue_read(lw_que_t* queue, char* success);

#endif // !__LW_QUEUE_H
