#ifndef __LW_RB_PORTING_H 
#define __LW_RB_PORTING_H

#include "stdint.h"

void* lw_rb_malloc(uint32_t block_size);
void lw_rb_free(void* block);

#endif // !__LW_RB_PORTING_H 
