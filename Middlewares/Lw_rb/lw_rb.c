#include "stdlib.h"
#include "lw_rb.h"
#include "lw_rb_porting.h"

/**
 * @brief 创建环形缓冲区
 * @param 缓冲区大小
 * @return 缓冲区句柄
 */
lw_rb_t* lw_rb_create(uint32_t capacity) 
{
    /*申请缓冲区控制块内存*/
    lw_rb_t* ring_buffer = (lw_rb_t*)lw_rb_malloc(sizeof(lw_rb_t));
    if (!ring_buffer)
    {
        return NULL;
    }
    ring_buffer->capacity = capacity + 1;

    /*申请缓冲区数据内存*/
    ring_buffer->buffer = (char*)lw_rb_malloc(ring_buffer->capacity * sizeof(char));
    if (!ring_buffer->buffer)
    {
        lw_rb_free(ring_buffer);
        return NULL;
    }

    ring_buffer->read_pos = 0;
    ring_buffer->write_pos = 0;
   
    return ring_buffer;
}

/**
 * @brief 写入缓冲区
 * @param 缓冲区句柄
 * @param 要写入的数据
 * @return 成功：LW_RB_SUCCESS
 * @return 失败：LW_RB_ERR
 */
char lw_rb_write(lw_rb_t* ring_buffer, char data)
{
    /*若缓冲区已满*/
    if ((ring_buffer->write_pos + 1) % ring_buffer->capacity == ring_buffer->read_pos)
    {
        return LW_RB_ERR;
    }
    ring_buffer->buffer[ring_buffer->write_pos] = data;
    ring_buffer->write_pos = (ring_buffer->write_pos + 1) % ring_buffer->capacity;
 
    return LW_RB_SUCCESS;
}

/**
 * @brief 读取缓冲区
 * @param 缓冲区句柄
 * @param 存储错误码的字符
 * @return 读取的数据
 */
char lw_rb_read(lw_rb_t* ring_buffer, char* success)
{
    if (ring_buffer->read_pos == ring_buffer->write_pos)
    {
        if (success != NULL)
        {
            *success = LW_RB_ERR;  /*缓冲区为空或无效缓冲区*/
        }
        return NULL;
    }

    char data = ring_buffer->buffer[ring_buffer->read_pos];
    ring_buffer->read_pos = (ring_buffer->read_pos + 1) % ring_buffer->capacity;
 
    if (success != NULL)
    {
        *success = LW_RB_SUCCESS;  /*读取成功*/
    }
    return data;
}

/**
 * @brief 销毁缓冲区
 * @param 缓冲区句柄
 */
char lw_rb_destroy(lw_rb_t* ring_buffer)
{
    if (ring_buffer == NULL)
    {
        return LW_RB_ERR;
    }

    lw_rb_free(ring_buffer->buffer);
    lw_rb_free(ring_buffer);
    return LW_RB_SUCCESS;
}
