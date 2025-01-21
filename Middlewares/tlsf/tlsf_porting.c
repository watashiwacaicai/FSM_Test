#include "./TLSF/tlsf.h"
#include "./TLSF/tlsf_porting.h"

/*定义全局变量*/

/*定义tlsf内存控制器*/
tlsf_t ccm_pool_manager;

/*定义静态变量*/

/*定义CCM内存池*/
/*CCM内存区由cpu直接访问，不支持DMA*/
static char ccm_pool[CCM_MEM_POOL_SIZE] __attribute__((at(CCM_RAM_ADDR)));

/*全局函数定义*/

/*CCM内存池初始化函数*/
void ccm_pool_init(void)
{
	ccm_pool_manager = tlsf_create_with_pool(ccm_pool, sizeof(ccm_pool));
}
