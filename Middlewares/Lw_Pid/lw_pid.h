#ifndef __LW_PID_H
#define __LW_PID_H

#include "stdint.h"

/*������*/

/*����ʽpid����*/
/*����ʽpid�����ڻ����޷�*/
typedef struct Increment_Pid
{
	float kp;
	float ki;
	float kd;
	float target;
	float error0; /*��ǰ���*/
	float error1; /*��һ�����*/
	float error2; /*���ϴ����*/
	float output_upper_limit; /*����޷�����*/
	float output_floor_limit; /*����޷�����*/
	uint8_t output_limit_state;	/*����޷���ʹ��״̬*/

}Increment_Pid_t;

/*λ��ʽpid����*/
typedef struct Fullscale_Pid
{
	float kp;
	float ki;
	float kd;
	float target;
	float error0; /*��ǰ���*/
	float error1; /*��һ�����*/
	float error_intergral; /*������ֵ*/
	float output_upper_limit; /*����޷�����*/
	float output_floor_limit; /*����޷�����*/
	float intergral_upper_limit; /*�����޷�����*/
	float intergral_floor_limit; /*�����޷�����*/
	uint8_t output_limit_state;	/*����޷���ʹ��״̬*/
	uint8_t intergral_limit_state; /*�����޷���ʹ��״̬*/
	
}Fullscale_Pid_t;

/*����ʽpid��غ���*/
void increment_pid_set_argument(Increment_Pid_t* pid_object, float kp, float ki, float kd);
void increment_pid_set_target(Increment_Pid_t* pid_object, float target);
void increment_pid_output_limit_enable(Increment_Pid_t* pid_object);
void increment_pid_output_limit_disable(Increment_Pid_t* pid_object);
void increment_pid_set_output_limit(Increment_Pid_t* pid_object, float upper_limit, float floor_limit);
void increment_pid_init(Increment_Pid_t* pid_object);
float increment_pid_compute(Increment_Pid_t* pid_object, float current_input);

/*λ��ʽpid��غ���*/
void fullscale_pid_set_argument(Fullscale_Pid_t* pid_object, float kp, float ki, float kd);
void fullscale_pid_set_target(Fullscale_Pid_t* pid_object, float target);
void fullscale_pid_output_limit_enable(Fullscale_Pid_t* pid_object);
void fullscale_pid_output_limit_disable(Fullscale_Pid_t* pid_object);
void fullscale_pid_set_output_limit(Fullscale_Pid_t* pid_object, float upper_limit, float floor_limit);
void fullscale_pid_intergral_limit_enable(Fullscale_Pid_t* pid_object);
void fullscale_pid_intergral_limit_disable(Fullscale_Pid_t* pid_object);
void fullscale_pid_set_intergral_limit(Fullscale_Pid_t* pid_object, float upper_limit, float floor_limit);
void fullscale_pid_init(Fullscale_Pid_t* pid_object);
float fullscale_pid_compute(Fullscale_Pid_t* pid_object, float current_input);

#endif
