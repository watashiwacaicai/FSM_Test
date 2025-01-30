#include "./TLSF/tlsf.h"
#include "./cJSON/cJSON.h"

/*����ccm�ڴ�ع�����*/
extern tlsf_t ccm_pool_manager;

static void* cJSON_malloc_hook(size_t block_size)
{
	return tlsf_malloc(ccm_pool_manager, block_size);
}

static void cJSON_free_hook(void* block)
{
	tlsf_free(ccm_pool_manager, block);
}

/**
 * @brief �ض���cJSON���ڴ������
 * @param NULL
 * @return NULL
 */
void cJSON_set_hook(void)
{
	cJSON_Hooks new_hooks;
	new_hooks.malloc_fn = cJSON_malloc_hook;
	new_hooks.free_fn   = cJSON_free_hook;
	cJSON_InitHooks(&new_hooks);
}
