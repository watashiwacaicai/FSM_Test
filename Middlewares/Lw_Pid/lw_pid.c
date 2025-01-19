#include "stdint.h"
#include "./Lw_Pid/lw_pid.h"

/*宏定义*/
#define PID_OUTPUT_LIMIT_ENABLE		1
#define PID_OUTPUT_LIMIT_DISABLE	0
#define PID_INTEGRAL_LIMIT_ENABLE	2
#define PID_INTEGRAL_LIMIT_DISABLE	0

/*全局函数定义*/

/*设置增量式pid参数*/
void increment_pid_set_argument(Increment_Pid_t* pid_object, float kp, float ki, float kd)
{
	pid_object->kp = kp;
	pid_object->ki = ki;
	pid_object->kd = kd;
}

/*设置位置式pid参数*/
void fullscale_pid_set_argument(Fullscale_Pid_t* pid_object, float kp, float ki, float kd)
{
	pid_object->kp = kp;
	pid_object->ki = ki;
	pid_object->kd = kd;
}

/*设置增量式pid目标值*/
void increment_pid_set_target(Increment_Pid_t* pid_object, float target)
{
	pid_object->target = target;
}

/*设置位置式pid目标值*/
void fullscale_pid_set_target(Fullscale_Pid_t* pid_object, float target)
{
	pid_object->target = target;
}

/*使能增量式pid输出限幅*/
void increment_pid_output_limit_enable(Increment_Pid_t* pid_object)
{
	pid_object->output_limit_state = PID_OUTPUT_LIMIT_ENABLE;
}

/*使能位置式pid输出限幅*/
void fullscale_pid_output_limit_enable(Fullscale_Pid_t* pid_object)
{
	pid_object->output_limit_state = PID_OUTPUT_LIMIT_ENABLE;
}

/*禁用增量式pid输出限幅*/
void increment_pid_output_limit_disable(Increment_Pid_t* pid_object)
{
	pid_object->output_limit_state = PID_OUTPUT_LIMIT_DISABLE;
}

/*禁用位置式pid输出限幅*/
void fullscale_pid_output_limit_disable(Fullscale_Pid_t* pid_object)
{
	pid_object->output_limit_state = PID_OUTPUT_LIMIT_DISABLE;
}

/*设置增量式pid输出限幅上下限*/
void increment_pid_set_output_limit(Increment_Pid_t* pid_object, float upper_limit, float floor_limit)
{
	pid_object->output_upper_limit = upper_limit;
	pid_object->output_floor_limit = floor_limit;
}

/*设置位置式pid输出限幅上下限*/
void fullscale_pid_set_output_limit(Fullscale_Pid_t* pid_object, float upper_limit, float floor_limit)
{
	pid_object->output_upper_limit = upper_limit;
	pid_object->output_floor_limit = floor_limit;
}

/*使能位置式pid的积分限幅*/
void fullscale_pid_intergral_limit_enable(Fullscale_Pid_t* pid_object)
{
	pid_object->intergral_limit_state = PID_INTEGRAL_LIMIT_ENABLE;
}

/*禁用位置式pid的积分限幅*/
void fullscale_pid_intergral_limit_disable(Fullscale_Pid_t* pid_object)
{
	pid_object->intergral_limit_state = PID_INTEGRAL_LIMIT_DISABLE;
}

/*设置位置式pid的积分限幅上下限*/
void fullscale_pid_set_intergral_limit(Fullscale_Pid_t* pid_object, float upper_limit, float floor_limit)
{
	pid_object->intergral_upper_limit = upper_limit;
	pid_object->intergral_floor_limit = floor_limit;
}

/*初始化增量式pid*/
void increment_pid_init(Increment_Pid_t* pid_object)
{
	pid_object->error0 = 0;
	pid_object->error1 = 0;
	pid_object->error2 = 0;
}

/*初始化位置式pid*/
void fullscale_pid_init(Fullscale_Pid_t* pid_object)
{
	pid_object->error0 = 0;
	pid_object->error1 = 0;
	pid_object->error_intergral = 0;
}

/*计算增量式pid*/
float increment_pid_compute(Increment_Pid_t* pid_object, float current_input)
{
	float output;
	
	/*误差传递*/
	pid_object->error2 = pid_object->error1;
	pid_object->error1 = pid_object->error0;
	pid_object->error0 = pid_object->target - current_input;
	
	output = pid_object->kp * (pid_object->error0 - pid_object->error1) + pid_object->ki * pid_object->error0
					+ pid_object->kd * (pid_object->error0 - 2 * pid_object->error1 + pid_object->error2);
	
	/*如果使能了输出限幅*/
	if(pid_object->output_limit_state == PID_OUTPUT_LIMIT_ENABLE)
	{
		if(output > pid_object->output_upper_limit)
		{
			output = pid_object->output_upper_limit;
		}
		if(output < pid_object->output_floor_limit)
		{
			output = pid_object->output_floor_limit;
		}
	}
	
	return output;
}

/*计算位置式pid*/
float fullscale_pid_compute(Fullscale_Pid_t* pid_object, float current_input)
{
	float output;
	
	/*误差传递*/
	pid_object->error1 = pid_object->error0;
	pid_object->error0 = pid_object->target - current_input;
	
	/*计算积分*/
	pid_object->error_intergral += pid_object->error0;
	
	/*如果使能了积分限幅*/
	if(pid_object->intergral_limit_state == PID_INTEGRAL_LIMIT_ENABLE)
	{
		if(pid_object->error_intergral > pid_object->intergral_upper_limit)
		{
			pid_object->error_intergral = pid_object->intergral_upper_limit;
		}
		if(pid_object->error_intergral < pid_object->intergral_floor_limit)
		{
			pid_object->error_intergral = pid_object->intergral_floor_limit;
		}
	}

	output = pid_object->kp * pid_object->error0 + pid_object->ki * pid_object->error_intergral 
				+ pid_object->kd * (pid_object->error0 - pid_object->error1);
	
	/*如果使能了输出限幅*/
	if(pid_object->output_limit_state == PID_OUTPUT_LIMIT_ENABLE)
	{
		if(output > pid_object->output_upper_limit)
		{
			output = pid_object->output_upper_limit;
		}
		if(output < pid_object->output_floor_limit)
		{
			output = pid_object->output_floor_limit;
		}
	}
	
	return output;
	
}
