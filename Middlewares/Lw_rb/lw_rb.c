#include "stdlib.h"
#include "lw_rb.h"
#include "lw_rb_porting.h"

/**
 * @brief �������λ�����
 * @param ��������С
 * @return ���������
 */
lw_rb_t* lw_rb_create(uint32_t capacity) 
{
    /*���뻺�������ƿ��ڴ�*/
    lw_rb_t* ring_buffer = (lw_rb_t*)lw_rb_malloc(sizeof(lw_rb_t));
    if (!ring_buffer)
    {
        return NULL;
    }
    ring_buffer->capacity = capacity + 1;

    /*���뻺���������ڴ�*/
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
 * @brief д�뻺����
 * @param ���������
 * @param Ҫд�������
 * @return �ɹ���LW_RB_SUCCESS
 * @return ʧ�ܣ�LW_RB_ERR
 */
char lw_rb_write(lw_rb_t* ring_buffer, char data)
{
    /*������������*/
    if ((ring_buffer->write_pos + 1) % ring_buffer->capacity == ring_buffer->read_pos)
    {
        return LW_RB_ERR;
    }
    ring_buffer->buffer[ring_buffer->write_pos] = data;
    ring_buffer->write_pos = (ring_buffer->write_pos + 1) % ring_buffer->capacity;
 
    return LW_RB_SUCCESS;
}

/**
 * @brief ��ȡ������
 * @param ���������
 * @param �洢��������ַ�
 * @return ��ȡ������
 */
char lw_rb_read(lw_rb_t* ring_buffer, char* success)
{
    if (ring_buffer->read_pos == ring_buffer->write_pos)
    {
        if (success != NULL)
        {
            *success = LW_RB_ERR;  /*������Ϊ�ջ���Ч������*/
        }
        return NULL;
    }

    char data = ring_buffer->buffer[ring_buffer->read_pos];
    ring_buffer->read_pos = (ring_buffer->read_pos + 1) % ring_buffer->capacity;
 
    if (success != NULL)
    {
        *success = LW_RB_SUCCESS;  /*��ȡ�ɹ�*/
    }
    return data;
}

/**
 * @brief ���ٻ�����
 * @param ���������
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
