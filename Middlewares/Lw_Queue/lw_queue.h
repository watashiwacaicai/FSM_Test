#ifndef __LW_QUEUE_H
#define __LW_QUEUE_H

#include "stdint.h"

/*�������Ͷ���*/
#define LWQ_SUCCESS     'Y'
#define LWQ_ERR         'N'

typedef struct 
{
    void** data;        /*���е����ݴ洢��*/
    uint32_t front;          /*����ͷָ��*/
    uint32_t rear;           /*����βָ��*/
    uint32_t capacity;       /*���е�����*/

} lw_que_t;

lw_que_t* lw_queue_create(uint32_t capacity);
void lw_queue_destroy(lw_que_t* queue);
char lw_queue_write(lw_que_t* queue, void* data);
void* lw_queue_read(lw_que_t* queue, char* success);

#endif // !__LW_QUEUE_H
