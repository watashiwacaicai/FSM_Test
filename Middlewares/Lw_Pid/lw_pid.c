#include "./Lw_Pid/lw_pid.h"

/********************静态函数声明********************/
static float increment_pid_compute(Pid_object_t* pid_object, float current_input);
static float fullscale_pid_compute(Pid_object_t* pid_object, float current_input);

/********************全局函数定义********************/

/**
 * @brief	设置pid参数
 * @param	pid_object pid对象
 * @param	kp 比例参数
 * @param	ki 积分参数
 * @param	kd 微分参数
 * @return	无
 */
void pid_set_argument(Pid_object_t* pid_object, float kp, float ki, float kd)
{
	pid_object->kp = kp;
	pid_object->ki = ki;
	pid_object->kd = kd;
}

/**
 * @brief	设置pid目标值
 * @param	pid_object pid对象
 * @param	target 目标值	
 * @return	无
 */
void pid_set_target(Pid_object_t* pid_object, float target)
{
	pid_object->target = target;
}

/**
 * @brief	使能pid输出限幅
 * @param	pid_object pid对象
 * @return	无
 */
void pid_output_limit_enable(Pid_object_t* pid_object)
{
	pid_object->output_limit_state = PID_OUTPUT_LIMIT_ENABLE;
}

/**
 * @brief	禁用pid输出限幅
 * @param	pid_object pid对象
 * @return	无
 */
void pid_output_limit_disable(Pid_object_t* pid_object)
{
	pid_object->output_limit_state = PID_OUTPUT_LIMIT_DISABLE;
}

/**
 * @brief	设置pid输出限幅上下限
 * @param	pid_object pid对象
 * @param	upper_limit 输出上限
 * @param	floor_limit 输出下限
 * @return	无
 */
void pid_set_output_limit(Pid_object_t* pid_object, float upper_limit, float floor_limit)
{
	pid_object->output_upper_limit = upper_limit;
	pid_object->output_floor_limit = floor_limit;
}

/**
 * @brief	使能pid的积分限幅
 * @param	pid_object pid对象
 * @return	无
 */
void pid_intergral_limit_enable(Pid_object_t* pid_object)
{
	pid_object->intergral_limit_state = PID_INTEGRAL_LIMIT_ENABLE;
}

/**
 * @brief	禁用pid的积分限幅
 * @param	pid_object pid对象
 * @return	无
 */
void pid_intergral_limit_disable(Pid_object_t* pid_object)
{
	pid_object->intergral_limit_state = PID_INTEGRAL_LIMIT_DISABLE;
}

/**
 * @brief	设置pid的积分限幅上下限
 * @param	pid_object pid对象
 * @param	upper_limit 输出上限
 * @param	floor_limit 输出下限
 * @return	无
 */
void pid_set_intergral_limit(Pid_object_t* pid_object, float upper_limit, float floor_limit)
{
	pid_object->intergral_upper_limit = upper_limit;
	pid_object->intergral_floor_limit = floor_limit;
}

/**
 * @brief	设置pid为增量式
 * @param	pid_object pid对象
 * @return	无
 */
void pid_set_mode_increment(Pid_object_t* pid_object)
{
	pid_object->pid_mode = PID_MODE_INCREMENT;
}

/**
 * @brief	设置pid为位置式
 * @param	pid_object pid对象
 * @return	无
 */
void pid_set_mode_fullscale(Pid_object_t* pid_object)
{
	pid_object->pid_mode = PID_MODE_FULLSCALE;
}

/**
 * @brief	初始化pid对象
 * @param	pid_object pid对象
 * @return	无
 */
void pid_init(Pid_object_t* pid_object)
{
	pid_object->error0 = 0.0;
	pid_object->error1 = 0.0;
	pid_object->error2 = 0.0;
	pid_object->error_intergral = 0.0;
	
	/*如果选择为增量式*/
	if(pid_object->pid_mode == PID_MODE_INCREMENT)
	{
		pid_object->pid_compute = increment_pid_compute;		
	}
	else if(pid_object->pid_mode == PID_MODE_FULLSCALE) /*如果选择为位置式*/
	{
		pid_object->pid_compute = fullscale_pid_compute;
	}
}

/********************静态函数定义********************/

/*计算增量式pid*/
static float increment_pid_compute(Pid_object_t* pid_object, float current_input)
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
static float fullscale_pid_compute(Pid_object_t* pid_object, float current_input)
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
