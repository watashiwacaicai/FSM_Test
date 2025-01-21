#include "./Lw_Pid/lw_pid.h"
#include "./Gear_Motor/gear_motor.h"

/*��������λ��ʽpid����*/
Pid_object_t motor_pid;

/*������������ʽpid����*/
Pid_object_t sovor_pid;

/*��ʼ�������λ��ʽpid*/
void motor_pid_init(void)
{
	pid_set_argument(&motor_pid, 0.23, 0.67, 1.2); /*����pid����*/
	pid_set_target(&motor_pid, 0.0f); /*����Ŀ����ֵ*/
	pid_output_limit_enable(&motor_pid); /*ʹ������޷�*/
	pid_set_output_limit(&motor_pid, 500.0, -500.0); /*��������޷���������*/
	pid_intergral_limit_enable(&motor_pid); /*ʹ�ܻ����޷�*/
	pid_set_intergral_limit(&motor_pid, 250.0, -250.0); /*���û����޷���������*/
	pid_set_mode_fullscale(&motor_pid); /*����ʹ��λ��ʽpid*/
	pid_init(&motor_pid); /*��ʼ�����pid����*/
}

/*��ʼ�����������ʽpid*/
/*����ʽû�л����޷�����˿��Բ�����Ӧ����*/
void sovor_pid_init(void)
{
	pid_set_argument(&sovor_pid, 0.14, 0.56, 0.9); /*����pid����*/
	pid_set_target(&sovor_pid, 0.0f); /*����Ŀ����ֵ*/
	pid_output_limit_enable(&sovor_pid); /*ʹ������޷�*/
	pid_set_output_limit(&sovor_pid, 500.0, -500.0); /*��������޷���������*/
	pid_set_mode_increment(&sovor_pid); /*����ʹ������ʽpid*/
	pid_init(&sovor_pid); /*��ʼ�����pid����*/
}

/*���Թ���*/
#ifdef GEAR_MOTOR_DEBUG

#include "user_usart.h"

void shell_sovor_pid_show_argument(void)
{
	debug_printf(">>kp: %7.3f	ki: %7.3f	kd: %7.3f\r\n", sovor_pid.kp, sovor_pid.ki, sovor_pid.kd);
}

void shell_sovor_pid_set_argument(float kp, float ki, float kd)
{
	pid_set_argument(&sovor_pid, kp, ki, kd); /*����pid����*/
}

void shell_motor_pid_show_argument(void)
{
	debug_printf(">>kp: %7.3f	ki: %7.3f	kd: %7.3f\r\n", motor_pid.kp, motor_pid.ki, motor_pid.kd);
}

void shell_motor_pid_set_argument(float kp, float ki, float kd)
{
	pid_set_argument(&motor_pid, kp, ki, kd); /*����pid����*/
}

#endif
