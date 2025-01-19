#ifndef __LW_PID_H
#define __LW_PID_H

#include "stdint.h"

/*对象定义*/

/*增量式pid对象*/
/*增量式pid不存在积分限幅*/
typedef struct Increment_Pid
{
	float kp;
	float ki;
	float kd;
	float target;
	float error0; /*当前误差*/
	float error1; /*上一次误差*/
	float error2; /*上上次误差*/
	float output_upper_limit; /*输出限幅上限*/
	float output_floor_limit; /*输出限幅下限*/
	uint8_t output_limit_state;	/*输出限幅的使用状态*/

}Increment_Pid_t;

/*位置式pid对象*/
typedef struct Fullscale_Pid
{
	float kp;
	float ki;
	float kd;
	float target;
	float error0; /*当前误差*/
	float error1; /*上一次误差*/
	float error_intergral; /*积分数值*/
	float output_upper_limit; /*输出限幅上限*/
	float output_floor_limit; /*输出限幅下限*/
	float intergral_upper_limit; /*积分限幅上限*/
	float intergral_floor_limit; /*积分限幅下限*/
	uint8_t output_limit_state;	/*输出限幅的使用状态*/
	uint8_t intergral_limit_state; /*积分限幅的使用状态*/
	
}Fullscale_Pid_t;

/*增量式pid相关函数*/
void increment_pid_set_argument(Increment_Pid_t* pid_object, float kp, float ki, float kd);
void increment_pid_set_target(Increment_Pid_t* pid_object, float target);
void increment_pid_output_limit_enable(Increment_Pid_t* pid_object);
void increment_pid_output_limit_disable(Increment_Pid_t* pid_object);
void increment_pid_set_output_limit(Increment_Pid_t* pid_object, float upper_limit, float floor_limit);
void increment_pid_init(Increment_Pid_t* pid_object);
float increment_pid_compute(Increment_Pid_t* pid_object, float current_input);

/*位置式pid相关函数*/
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
