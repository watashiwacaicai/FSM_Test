#ifndef __LW_PID_H
#define __LW_PID_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

/********************宏定义********************/
#define PID_OUTPUT_LIMIT_ENABLE		1
#define PID_OUTPUT_LIMIT_DISABLE	0
#define PID_INTEGRAL_LIMIT_ENABLE	2
#define PID_INTEGRAL_LIMIT_DISABLE	0
#define PID_MODE_INCREMENT			3
#define PID_MODE_FULLSCALE			4


/********************数据类型定义********************/

typedef struct Pid_object Pid_object_t;

/*pid对象*/
struct Pid_object
{
	float kp;
	float ki;
	float kd;
	float target;
	float error0; /*当前误差*/
	float error1; /*上一次误差*/
	float error2; /*上上次误差*/
	float error_intergral; /*积分数值*/
	float output_upper_limit; /*输出限幅上限*/
	float output_floor_limit; /*输出限幅下限*/
	float intergral_upper_limit; /*积分限幅上限*/
	float intergral_floor_limit; /*积分限幅下限*/
	uint8_t output_limit_state;	/*输出限幅的使用状态*/
	uint8_t intergral_limit_state; /*积分限幅的使用状态*/
	uint8_t pid_mode; /*pid的计算模式*/
	float (*pid_compute)(Pid_object_t* pid_object, float current_input); /*pid计算句柄*/
};

/********************函数声明********************/

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

#ifdef __cplusplus
}
#endif

#endif
