#include "stdint.h"
#include "./Lw_Pid/lw_pid.h"

/*�궨��*/
#define PID_OUTPUT_LIMIT_ENABLE		1
#define PID_OUTPUT_LIMIT_DISABLE	0
#define PID_INTEGRAL_LIMIT_ENABLE	2
#define PID_INTEGRAL_LIMIT_DISABLE	0
#define PID_MODE_INCREMENT			3
#define PID_MODE_FULLSCALE			4

/*��̬��������*/
static float increment_pid_compute(Pid_object_t* pid_object, float current_input);
static float fullscale_pid_compute(Pid_object_t* pid_object, float current_input);

/*ȫ�ֺ�������*/

/*����pid����*/
void pid_set_argument(Pid_object_t* pid_object, float kp, float ki, float kd)
{
	pid_object->kp = kp;
	pid_object->ki = ki;
	pid_object->kd = kd;
}

/*����pidĿ��ֵ*/
void pid_set_target(Pid_object_t* pid_object, float target)
{
	pid_object->target = target;
}

/*ʹ��pid����޷�*/
void pid_output_limit_enable(Pid_object_t* pid_object)
{
	pid_object->output_limit_state = PID_OUTPUT_LIMIT_ENABLE;
}

/*����pid����޷�*/
void pid_output_limit_disable(Pid_object_t* pid_object)
{
	pid_object->output_limit_state = PID_OUTPUT_LIMIT_DISABLE;
}

/*����pid����޷�������*/
void pid_set_output_limit(Pid_object_t* pid_object, float upper_limit, float floor_limit)
{
	pid_object->output_upper_limit = upper_limit;
	pid_object->output_floor_limit = floor_limit;
}

/*ʹ��pid�Ļ����޷�*/
void pid_intergral_limit_enable(Pid_object_t* pid_object)
{
	pid_object->intergral_limit_state = PID_INTEGRAL_LIMIT_ENABLE;
}

/*����pid�Ļ����޷�*/
void pid_intergral_limit_disable(Pid_object_t* pid_object)
{
	pid_object->intergral_limit_state = PID_INTEGRAL_LIMIT_DISABLE;
}

/*����pid�Ļ����޷�������*/
void pid_set_intergral_limit(Pid_object_t* pid_object, float upper_limit, float floor_limit)
{
	pid_object->intergral_upper_limit = upper_limit;
	pid_object->intergral_floor_limit = floor_limit;
}

/*����pidΪ����ʽ*/
void pid_set_mode_increment(Pid_object_t* pid_object)
{
	pid_object->pid_mode = PID_MODE_INCREMENT;
}

/*����pidΪλ��ʽ*/
void pid_set_mode_fullscale(Pid_object_t* pid_object)
{
	pid_object->pid_mode = PID_MODE_FULLSCALE;
}

/*��ʼ��pid*/
void pid_init(Pid_object_t* pid_object)
{
	pid_object->error0 = 0;
	pid_object->error1 = 0;
	pid_object->error2 = 0;
	pid_object->error_intergral = 0;
	
	/*���ѡ��Ϊ����ʽ*/
	if(pid_object->pid_mode == PID_MODE_INCREMENT)
	{
		pid_object->pid_compute = increment_pid_compute;
		
	}else if(pid_object->pid_mode == PID_MODE_FULLSCALE) /*���ѡ��Ϊλ��ʽ*/
	{
		pid_object->pid_compute = fullscale_pid_compute;
	}
}

/*��̬��������*/

/*��������ʽpid*/
static float increment_pid_compute(Pid_object_t* pid_object, float current_input)
{
	float output;
	
	/*����*/
	pid_object->error2 = pid_object->error1;
	pid_object->error1 = pid_object->error0;
	pid_object->error0 = pid_object->target - current_input;
	
	output = pid_object->kp * (pid_object->error0 - pid_object->error1) + pid_object->ki * pid_object->error0
					+ pid_object->kd * (pid_object->error0 - 2 * pid_object->error1 + pid_object->error2);
	
	/*���ʹ��������޷�*/
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

/*����λ��ʽpid*/
static float fullscale_pid_compute(Pid_object_t* pid_object, float current_input)
{
	float output;
	
	/*����*/
	pid_object->error1 = pid_object->error0;
	pid_object->error0 = pid_object->target - current_input;
	
	/*�������*/
	pid_object->error_intergral += pid_object->error0;
	
	/*���ʹ���˻����޷�*/
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
	
	/*���ʹ��������޷�*/
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
