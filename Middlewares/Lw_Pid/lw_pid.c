#include "stdint.h"
#include "./Lw_Pid/lw_pid.h"

/*�궨��*/
#define PID_OUTPUT_LIMIT_ENABLE		1
#define PID_OUTPUT_LIMIT_DISABLE	0
#define PID_INTEGRAL_LIMIT_ENABLE	2
#define PID_INTEGRAL_LIMIT_DISABLE	0

/*ȫ�ֺ�������*/

/*��������ʽpid����*/
void increment_pid_set_argument(Increment_Pid_t* pid_object, float kp, float ki, float kd)
{
	pid_object->kp = kp;
	pid_object->ki = ki;
	pid_object->kd = kd;
}

/*����λ��ʽpid����*/
void fullscale_pid_set_argument(Fullscale_Pid_t* pid_object, float kp, float ki, float kd)
{
	pid_object->kp = kp;
	pid_object->ki = ki;
	pid_object->kd = kd;
}

/*��������ʽpidĿ��ֵ*/
void increment_pid_set_target(Increment_Pid_t* pid_object, float target)
{
	pid_object->target = target;
}

/*����λ��ʽpidĿ��ֵ*/
void fullscale_pid_set_target(Fullscale_Pid_t* pid_object, float target)
{
	pid_object->target = target;
}

/*ʹ������ʽpid����޷�*/
void increment_pid_output_limit_enable(Increment_Pid_t* pid_object)
{
	pid_object->output_limit_state = PID_OUTPUT_LIMIT_ENABLE;
}

/*ʹ��λ��ʽpid����޷�*/
void fullscale_pid_output_limit_enable(Fullscale_Pid_t* pid_object)
{
	pid_object->output_limit_state = PID_OUTPUT_LIMIT_ENABLE;
}

/*��������ʽpid����޷�*/
void increment_pid_output_limit_disable(Increment_Pid_t* pid_object)
{
	pid_object->output_limit_state = PID_OUTPUT_LIMIT_DISABLE;
}

/*����λ��ʽpid����޷�*/
void fullscale_pid_output_limit_disable(Fullscale_Pid_t* pid_object)
{
	pid_object->output_limit_state = PID_OUTPUT_LIMIT_DISABLE;
}

/*��������ʽpid����޷�������*/
void increment_pid_set_output_limit(Increment_Pid_t* pid_object, float upper_limit, float floor_limit)
{
	pid_object->output_upper_limit = upper_limit;
	pid_object->output_floor_limit = floor_limit;
}

/*����λ��ʽpid����޷�������*/
void fullscale_pid_set_output_limit(Fullscale_Pid_t* pid_object, float upper_limit, float floor_limit)
{
	pid_object->output_upper_limit = upper_limit;
	pid_object->output_floor_limit = floor_limit;
}

/*ʹ��λ��ʽpid�Ļ����޷�*/
void fullscale_pid_intergral_limit_enable(Fullscale_Pid_t* pid_object)
{
	pid_object->intergral_limit_state = PID_INTEGRAL_LIMIT_ENABLE;
}

/*����λ��ʽpid�Ļ����޷�*/
void fullscale_pid_intergral_limit_disable(Fullscale_Pid_t* pid_object)
{
	pid_object->intergral_limit_state = PID_INTEGRAL_LIMIT_DISABLE;
}

/*����λ��ʽpid�Ļ����޷�������*/
void fullscale_pid_set_intergral_limit(Fullscale_Pid_t* pid_object, float upper_limit, float floor_limit)
{
	pid_object->intergral_upper_limit = upper_limit;
	pid_object->intergral_floor_limit = floor_limit;
}

/*��ʼ������ʽpid*/
void increment_pid_init(Increment_Pid_t* pid_object)
{
	pid_object->error0 = 0;
	pid_object->error1 = 0;
	pid_object->error2 = 0;
}

/*��ʼ��λ��ʽpid*/
void fullscale_pid_init(Fullscale_Pid_t* pid_object)
{
	pid_object->error0 = 0;
	pid_object->error1 = 0;
	pid_object->error_intergral = 0;
}

/*��������ʽpid*/
float increment_pid_compute(Increment_Pid_t* pid_object, float current_input)
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
float fullscale_pid_compute(Fullscale_Pid_t* pid_object, float current_input)
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
