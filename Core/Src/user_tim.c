#include "tim.h"
#include "user_tim.h"

/*静态变量定义*/
volatile static uint64_t sys_ticking = 0; /*系统时基，1ms自增一次*/

/*********全局函数定义**********/

/*系统时基获取函数*/
uint64_t get_sys_time_base(void)
{
	return sys_ticking;
}

/*定时中断回调函数*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIME_BASE_TIM_PORT)
	{
		sys_ticking++; /*系统时基自增*/
	}
}

