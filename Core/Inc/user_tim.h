#ifndef __USER_TIM_H
#define __USER_TIM_H

#include "stdint.h"

/*∫Í∂®“Â*/
#define TIME_BASE_TIM 		htim6
#define TIME_BASE_TIM_PORT  TIM6

uint64_t get_sys_time_base(void);

#endif
