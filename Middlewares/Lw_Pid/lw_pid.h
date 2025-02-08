#ifndef __LW_PID_H
#define __LW_PID_H

#include "stdint.h"

/*对象定义*/

typedef struct Pid_object Pid_object_t;

/*pid对象*/
struct Pid_object
{
	double kp;
	double ki;
	double kd;
	double target;
	double error0; /*当前误差*/
	double error1; /*上一次误差*/
	double error2; /*上上次误差*/
	double error_intergral; /*积分数值*/
	double output_upper_limit; /*输出限幅上限*/
	double output_floor_limit; /*输出限幅下限*/
	double intergral_upper_limit; /*积分限幅上限*/
	double intergral_floor_limit; /*积分限幅下限*/
	uint8_t output_limit_state;	/*输出限幅的使用状态*/
	uint8_t intergral_limit_state; /*积分限幅的使用状态*/
	uint8_t pid_mode; /*pid的计算模式*/
	double (*pid_compute)(Pid_object_t* pid_object, double current_input); /*pid计算句柄*/
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
