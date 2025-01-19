#include "usart.h"
#include "./Letter_Shell/shell.h"
#include "./OLED/OLED.h"
#include "./Lw_Pid/lw_pid.h"
#include "./Gear_Motor/gear_motor.h"

/*将OLED显示字符串函数导出至shell*/
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), 
					oled_show, OLED_ShowString, show a string on oled);

/*将电机增量式pid显参功能导出至shell*/
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), 
					sovor_pid_show_argu, shell_sovor_pid_show_argument, show the argument of sovor pid object);

/*将电机位置式pid显参功能导出至shell*/
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), 
					motor_pid_show_argu, shell_motor_pid_show_argument, show the argument of motor pid object);

/*将电机增量式pid参数设置功能导出至shell*/
SHELL_EXPORT_CMD_AGENCY(SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),
					sovor_pid_set_argu, shell_sovor_pid_set_argument, set the argument of sovor pid object,
					SHELL_PARAM_FLOAT(p1), SHELL_PARAM_FLOAT(p2), SHELL_PARAM_FLOAT(p3));

/*将电机位置式pid参数设置功能导出至shell*/
SHELL_EXPORT_CMD_AGENCY(SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),
					motor_pid_set_argu, shell_motor_pid_set_argument, set the argument of motor pid object,
					SHELL_PARAM_FLOAT(p1), SHELL_PARAM_FLOAT(p2), SHELL_PARAM_FLOAT(p3));
