#include "usart.h"
#include "./Letter_Shell/shell.h"
#include "./OLED/OLED.h"
#include "./Lw_Pid/lw_pid.h"
#include "./Gear_Motor/gear_motor.h"

/*��OLED��ʾ�ַ�������������shell*/
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), 
					oled_show, OLED_ShowString, show a string on oled);

/*���������ʽpid�Բι��ܵ�����shell*/
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), 
					sovor_pid_show_argu, shell_sovor_pid_show_argument, show the argument of sovor pid object);

/*�����λ��ʽpid�Բι��ܵ�����shell*/
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), 
					motor_pid_show_argu, shell_motor_pid_show_argument, show the argument of motor pid object);

/*���������ʽpid�������ù��ܵ�����shell*/
SHELL_EXPORT_CMD_AGENCY(SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),
					sovor_pid_set_argu, shell_sovor_pid_set_argument, set the argument of sovor pid object,
					SHELL_PARAM_FLOAT(p1), SHELL_PARAM_FLOAT(p2), SHELL_PARAM_FLOAT(p3));

/*�����λ��ʽpid�������ù��ܵ�����shell*/
SHELL_EXPORT_CMD_AGENCY(SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),
					motor_pid_set_argu, shell_motor_pid_set_argument, set the argument of motor pid object,
					SHELL_PARAM_FLOAT(p1), SHELL_PARAM_FLOAT(p2), SHELL_PARAM_FLOAT(p3));
