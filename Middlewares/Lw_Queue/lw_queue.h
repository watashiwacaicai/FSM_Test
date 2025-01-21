#ifndef __LW_QUEUE_H
#define __LW_QUEUE_H

/*定义队列类型*/
typedef struct {
    void** data;        /* 队列的数据存储区 */
    int front;          /* 队列头指针 */
    int rear;           /* 队列尾指针 */
    int capacity;       /* 队列的容量 */
    int size;           /* 队列当前的元素个数 */
}lw_que_t;

/*返回类型定义*/
#define LWQ_SUCCESS     'Y'
#define LWQ_ERR         'N'

lw_que_t* lw_queue_create(int capacity);
void lw_queue_destroy(lw_que_t* queue);
char lw_queue_write(lw_que_t* queue, void* data);
void* lw_queue_read(lw_que_t* queue, char* success);

#endif
