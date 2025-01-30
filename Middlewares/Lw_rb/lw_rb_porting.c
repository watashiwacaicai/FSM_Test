#include "./TLSF/tlsf.h"

/*����ccm�ڴ�ع�����*/
extern tlsf_t ccm_pool_manager;

void* lw_rb_malloc(int block_size)
{
	return tlsf_malloc(ccm_pool_manager, block_size);
}

void lw_rb_free(void* block)
{
	tlsf_free(ccm_pool_manager, block);
}
