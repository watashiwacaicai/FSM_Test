#include "main.h"
#include "user_led.h"
#include "./OLED/OLED.h"
#include "./Flexible_Button/flexible_button.h"
#include "./Flexible_Button/flexbutton_porting.h"
#include "./Multi_Timer/MultiTimer.h"
#include "./Letter_Shell/shell.h"
#include "./Letter_Shell/letter_shell_porting.h"

/*��̬��������*/
static MultiTimer btn_scan_timer; /*����ɨ�趨ʱ��*/
static MultiTimer led_flicker_timer; /*LED��˸��ʱ��*/
static MultiTimer oled_update_timer; /*OLED���¶�ʱ��*/
static MultiTimer letter_shell_timer; /*letter shell����ʱ��*/

/*��̬��������*/
static void btn_scan_tim_cb(MultiTimer* timer, void* userData);
static void led_flicker_tim_cb(MultiTimer* timer, void* userData);
static void oled_update_tim_cb(MultiTimer* timer, void* userData);
static void letter_shell_tim_cb(MultiTimer* timer, void* userData);

/**********ȫ�ֺ���**********/

/*����ɨ�趨ʱ����������*/
void btn_scan_tim_start(void)
{
	multiTimerStart(&btn_scan_timer, 20, btn_scan_tim_cb, NULL);
}

/*LED��˸��ʱ����������*/
void led_flicker_tim_start(void)
{
	multiTimerStart(&led_flicker_timer, 500, led_flicker_tim_cb, NULL);
}

/*OLED���¶�ʱ����������*/
void oled_update_tim_start(void)
{
	multiTimerStart(&oled_update_timer, 25, oled_update_tim_cb, NULL);
}

/*letter shell����ʱ����������*/
void letter_shell_tim_start(void)
{
	multiTimerStart(&letter_shell_timer, 50, letter_shell_tim_cb, NULL);
}

/**********��̬����**********/

/*����ɨ�������ʱ����ʱ�ص�����*/
static void btn_scan_tim_cb(MultiTimer* timer, void* userData)
{
    flex_button_scan(); /*ɨ�谴��*/
	
	btn_scan_tim_start(); /*��װ�ض�ʱ��*/
}

/*LED��˸��ʱ���Ļص�����*/
static void led_flicker_tim_cb(MultiTimer* timer, void* userData)
{
    user_led_toggle(); /*�û�led��˸*/
	
	led_flicker_tim_start(); /*��װ�ض�ʱ��*/
}

/*OLED���¶�ʱ���Ļص�����*/
static void oled_update_tim_cb(MultiTimer* timer, void* userData)
{
	OLED_Update(); /*����ʾ�����������ݸ��µ�OLED��*/
	
    oled_update_tim_start(); /*��װ�ض�ʱ��*/
}

/*letter shell����ʱ���Ļص�����*/
static void letter_shell_tim_cb(MultiTimer* timer, void* userData)
{
	shell_task_handler(); /*ִ��shell����*/
	
	letter_shell_tim_start(); /*��װ�ض�ʱ��*/
}
