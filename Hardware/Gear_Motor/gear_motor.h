#ifndef __GEAR_MOTOR_H
#define __GEAR_MOTOR_H

#include "./Lw_Pid/lw_pid.h"

/*调试宏*/
#define GEAR_MOTOR_DEBUG

extern Pid_object_t motor_pid;
extern Pid_object_t sovor_pid;

void motor_pid_init(void);
void sovor_pid_init(void);

/*调试功能*/	
#ifdef GEAR_MOTOR_DEBUG

void shell_sovor_pid_show_argument(void);
void shell_sovor_pid_set_argument(float kp, float ki, float kd);
void shell_motor_pid_show_argument(void);
void shell_motor_pid_set_argument(float kp, float ki, float kd);

#endif

#endif

