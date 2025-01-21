#include "./TLSF/tlsf.h"
#include "./TLSF/tlsf_porting.h"

/*����ccm�ڴ�ع�����*/
extern tlsf_t ccm_pool_manager;

void* lwq_malloc(int size)
{
	return tlsf_malloc(ccm_pool_manager, size);
}

void lwq_free(void* block) 
{
	tlsf_free(ccm_pool_manager, block);
}
