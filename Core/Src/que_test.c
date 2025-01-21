#include "./Lw_Queue/lw_queue.h"
#include "./TLSF/tlsf_porting.h"
#include "./TLSF/tlsf.h"
#include "./OLED/OLED.h"

lw_que_t* test_que;
char jk = 'A';
char* wri_jk;
char* rec_jk;
char rec_jk_str[10];
char que_err;

void que_te(void)
{		
	test_que = lw_queue_create(5);

	for(int i = 0; i < 10; i++)
	{
		wri_jk = (char*)tlsf_malloc(ccm_pool_manager, sizeof(char));
		*wri_jk = jk;
		que_err = lw_queue_write(test_que, (void*)wri_jk);
		if(que_err == LWQ_ERR)
		{
			tlsf_free(ccm_pool_manager, (void*)wri_jk);
			break;
		}
		jk++;
	}

	for(int i = 0; i < 10; i++)
	{
		rec_jk = (char*)lw_queue_read(test_que, &que_err);

		if(que_err == LWQ_ERR)
		{
			break;
		}
		rec_jk_str[i] = *rec_jk;
		tlsf_free(ccm_pool_manager, (void*)rec_jk);
	}

	OLED_ShowString(0, 16, rec_jk_str, OLED_8X16);

}
