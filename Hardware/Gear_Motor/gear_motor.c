#include "./Lw_Pid/lw_pid.h"
#include "./Gear_Motor/gear_motor.h"

/*定义电机的位置式pid对象*/
Pid_object_t motor_pid;

/*定义电机的增量式pid对象*/
Pid_object_t sovor_pid;

/*初始化电机的位置式pid*/
void motor_pid_init(void)
{
	pid_set_argument(&motor_pid, 0.23, 0.67, 1.2); /*设置pid参数*/
	pid_set_target(&motor_pid, 0.0f); /*设置目标数值*/
	pid_output_limit_enable(&motor_pid); /*使能输出限幅*/
	pid_set_output_limit(&motor_pid, 500.0, -500.0); /*设置输出限幅的上下限*/
	pid_intergral_limit_enable(&motor_pid); /*使能积分限幅*/
	pid_set_intergral_limit(&motor_pid, 250.0, -250.0); /*设置积分限幅的上下限*/
	pid_set_mode_fullscale(&motor_pid); /*设置使用位置式pid*/
	pid_init(&motor_pid); /*初始化电机pid对象*/
}

/*初始化电机的增量式pid*/
/*增量式没有积分限幅，因此可以不做相应设置*/
void sovor_pid_init(void)
{
	pid_set_argument(&sovor_pid, 0.14, 0.56, 0.9); /*设置pid参数*/
	pid_set_target(&sovor_pid, 0.0f); /*设置目标数值*/
	pid_output_limit_enable(&sovor_pid); /*使能输出限幅*/
	pid_set_output_limit(&sovor_pid, 500.0, -500.0); /*设置输出限幅的上下限*/
	pid_set_mode_increment(&sovor_pid); /*设置使用增量式pid*/
	pid_init(&sovor_pid); /*初始化电机pid对象*/
}

/*调试功能*/
#ifdef GEAR_MOTOR_DEBUG

#include "user_usart.h"

void shell_sovor_pid_show_argument(void)
{
	debug_printf(">>kp: %7.3f	ki: %7.3f	kd: %7.3f\r\n", sovor_pid.kp, sovor_pid.ki, sovor_pid.kd);
}

void shell_sovor_pid_set_argument(float kp, float ki, float kd)
{
	pid_set_argument(&sovor_pid, kp, ki, kd); /*设置pid参数*/
}

void shell_motor_pid_show_argument(void)
{
	debug_printf(">>kp: %7.3f	ki: %7.3f	kd: %7.3f\r\n", motor_pid.kp, motor_pid.ki, motor_pid.kd);
}

void shell_motor_pid_set_argument(float kp, float ki, float kd)
{
	pid_set_argument(&motor_pid, kp, ki, kd); /*设置pid参数*/
}

#endif
