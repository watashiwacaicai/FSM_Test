#ifndef __LW_QUEUE_PORTING_H
#define __LW_QUEUE_PORTING_H

void* lwq_malloc(int size);
void lwq_free(void* block);

#endif
