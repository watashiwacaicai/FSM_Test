#include "tim.h"
#include "user_tim.h"

/*��̬��������*/
volatile static uint64_t sys_ticking = 0; /*ϵͳʱ����1ms����һ��*/

/*********ȫ�ֺ�������**********/

/*ϵͳʱ����ȡ����*/
uint64_t get_sys_time_base(void)
{
	return sys_ticking;
}

/*��ʱ�жϻص�����*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIME_BASE_TIM_PORT)
	{
		sys_ticking++; /*ϵͳʱ������*/
	}
}

