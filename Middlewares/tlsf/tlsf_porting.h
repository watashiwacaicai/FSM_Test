#ifndef __TLSF_PORTING_H
#define __TLSF_PORTING_H

#include "./TLSF/tlsf.h"

/*CCM 内存区的起始地址*/
#define CCM_RAM_ADDR	0x10000000

/*CCM 内存池的大小*/
#define CCM_MEM_POOL_SIZE	30 * 1024U	/*30kb*/

/*声明ccm内存管理器*/
extern tlsf_t ccm_pool_manager;

void ccm_pool_init(void);

#endif
