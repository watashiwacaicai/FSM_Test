#ifndef __LW_RB_H
#define __LW_RB_H

#include "stdint.h"

typedef struct 
{
    uint32_t capacity;
    char* buffer;
    uint32_t read_pos;
    uint32_t write_pos;

} lw_rb_t;

#define LW_RB_SUCCESS   'Y'
#define LW_RB_ERR       'N'

lw_rb_t* lw_rb_create(uint32_t capacity);
char lw_rb_write(lw_rb_t* ring_buffer, char data);
char lw_rb_read(lw_rb_t* ring_buffer, char* success);
char lw_rb_destroy(lw_rb_t* ring_buffer);

#endif // !__LW_RB_H
