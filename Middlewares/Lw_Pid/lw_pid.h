#ifndef __LW_PID_H
#define __LW_PID_H

#include "stdint.h"

/*������*/

typedef struct Pid_object Pid_object_t;

/*pid����*/
struct Pid_object
{
	double kp;
	double ki;
	double kd;
	double target;
	double error0; /*��ǰ���*/
	double error1; /*��һ�����*/
	double error2; /*���ϴ����*/
	double error_intergral; /*������ֵ*/
	double output_upper_limit; /*����޷�����*/
	double output_floor_limit; /*����޷�����*/
	double intergral_upper_limit; /*�����޷�����*/
	double intergral_floor_limit; /*�����޷�����*/
	uint8_t output_limit_state;	/*����޷���ʹ��״̬*/
	uint8_t intergral_limit_state; /*�����޷���ʹ��״̬*/
	uint8_t pid_mode; /*pid�ļ���ģʽ*/
	double (*pid_compute)(Pid_object_t* pid_object, double current_input); /*pid������*/
};

void pid_set_argument(Pid_object_t* pid_object, double kp, double ki, double kd);
void pid_set_target(Pid_object_t* pid_object, double target);
void pid_output_limit_enable(Pid_object_t* pid_object);
void pid_output_limit_disable(Pid_object_t* pid_object);
void pid_set_output_limit(Pid_object_t* pid_object, double upper_limit, double floor_limit);
void pid_intergral_limit_enable(Pid_object_t* pid_object);
void pid_intergral_limit_disable(Pid_object_t* pid_object);
void pid_set_intergral_limit(Pid_object_t* pid_object, double upper_limit, double floor_limit);
void pid_set_mode_increment(Pid_object_t* pid_object);
void pid_set_mode_fullscale(Pid_object_t* pid_object);
void pid_init(Pid_object_t* pid_object);

#endif
