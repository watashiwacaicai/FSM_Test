#include "./TLSF/tlsf.h"
#include "./TLSF/tlsf_porting.h"

/*����ȫ�ֱ���*/

/*����tlsf�ڴ������*/
tlsf_t ccm_pool_manager;

/*���徲̬����*/

/*����CCM�ڴ��*/
/*CCM�ڴ�����cpuֱ�ӷ��ʣ���֧��DMA*/
static char ccm_pool[CCM_MEM_POOL_SIZE] __attribute__((at(CCM_RAM_ADDR)));

/*ȫ�ֺ�������*/

/*CCM�ڴ�س�ʼ������*/
void ccm_pool_init(void)
{
	ccm_pool_manager = tlsf_create_with_pool(ccm_pool, sizeof(ccm_pool));
}
