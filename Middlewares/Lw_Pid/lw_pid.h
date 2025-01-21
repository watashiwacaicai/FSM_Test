#ifndef __LW_PID_H
#define __LW_PID_H

#include "stdint.h"

/*������*/

typedef struct Pid_object Pid_object_t;

/*pid����*/
struct Pid_object
{
	float kp;
	float ki;
	float kd;
	float target;
	float error0; /*��ǰ���*/
	float error1; /*��һ�����*/
	float error2; /*���ϴ����*/
	float error_intergral; /*������ֵ*/
	float output_upper_limit; /*����޷�����*/
	float output_floor_limit; /*����޷�����*/
	float intergral_upper_limit; /*�����޷�����*/
	float intergral_floor_limit; /*�����޷�����*/
	uint8_t output_limit_state;	/*����޷���ʹ��״̬*/
	uint8_t intergral_limit_state; /*�����޷���ʹ��״̬*/
	uint8_t pid_mode; /*pid�ļ���ģʽ*/
	float (*pid_compute)(Pid_object_t* pid_object, float current_input); /*pid������*/
};

void pid_set_argument(Pid_object_t* pid_object, float kp, float ki, float kd);
void pid_set_target(Pid_object_t* pid_object, float target);
void pid_output_limit_enable(Pid_object_t* pid_object);
void pid_output_limit_disable(Pid_object_t* pid_object);
void pid_set_output_limit(Pid_object_t* pid_object, float upper_limit, float floor_limit);
void pid_intergral_limit_enable(Pid_object_t* pid_object);
void pid_intergral_limit_disable(Pid_object_t* pid_object);
void pid_set_intergral_limit(Pid_object_t* pid_object, float upper_limit, float floor_limit);
void pid_set_mode_increment(Pid_object_t* pid_object);
void pid_set_mode_fullscale(Pid_object_t* pid_object);
void pid_init(Pid_object_t* pid_object);

#endif
