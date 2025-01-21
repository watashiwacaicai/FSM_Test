#ifndef __TLSF_PORTING_H
#define __TLSF_PORTING_H

#include "./TLSF/tlsf.h"

/*CCM �ڴ�������ʼ��ַ*/
#define CCM_RAM_ADDR	0x10000000

/*CCM �ڴ�صĴ�С*/
#define CCM_MEM_POOL_SIZE	30 * 1024U	/*30kb*/

/*����ccm�ڴ������*/
extern tlsf_t ccm_pool_manager;

void ccm_pool_init(void);

#endif
