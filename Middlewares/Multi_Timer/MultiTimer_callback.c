#include "main.h"
#include "user_led.h"
#include "./OLED/OLED.h"
#include "./Flexible_Button/flexible_button.h"
#include "./Flexible_Button/flexbutton_porting.h"
#include "./Multi_Timer/MultiTimer.h"
#include "./Letter_Shell/shell.h"
#include "./Letter_Shell/letter_shell_porting.h"

/*静态变量定义*/
static MultiTimer btn_scan_timer; /*按键扫描定时器*/
static MultiTimer led_flicker_timer; /*LED闪烁定时器*/
static MultiTimer oled_update_timer; /*OLED更新定时器*/
static MultiTimer letter_shell_timer; /*letter shell任务定时器*/

/*静态函数声明*/
static void btn_scan_tim_cb(MultiTimer* timer, void* userData);
static void led_flicker_tim_cb(MultiTimer* timer, void* userData);
static void oled_update_tim_cb(MultiTimer* timer, void* userData);
static void letter_shell_tim_cb(MultiTimer* timer, void* userData);

/**********全局函数**********/

/*按键扫描定时器启动函数*/
void btn_scan_tim_start(void)
{
	multiTimerStart(&btn_scan_timer, 20, btn_scan_tim_cb, NULL);
}

/*LED闪烁定时器启动函数*/
void led_flicker_tim_start(void)
{
	multiTimerStart(&led_flicker_timer, 500, led_flicker_tim_cb, NULL);
}

/*OLED更新定时器启动函数*/
void oled_update_tim_start(void)
{
	multiTimerStart(&oled_update_timer, 25, oled_update_tim_cb, NULL);
}

/*letter shell任务定时器启动函数*/
void letter_shell_tim_start(void)
{
	multiTimerStart(&letter_shell_timer, 50, letter_shell_tim_cb, NULL);
}

/**********静态函数**********/

/*按键扫描软件定时器超时回调函数*/
static void btn_scan_tim_cb(MultiTimer* timer, void* userData)
{
    flex_button_scan(); /*扫描按键*/
	
	btn_scan_tim_start(); /*重装载定时器*/
}

/*LED闪烁定时器的回调函数*/
static void led_flicker_tim_cb(MultiTimer* timer, void* userData)
{
    user_led_toggle(); /*用户led闪烁*/
	
	led_flicker_tim_start(); /*重装载定时器*/
}

/*OLED更新定时器的回调函数*/
static void oled_update_tim_cb(MultiTimer* timer, void* userData)
{
	OLED_Update(); /*将显示缓冲区的内容更新到OLED上*/
	
    oled_update_tim_start(); /*重装载定时器*/
}

/*letter shell任务定时器的回调函数*/
static void letter_shell_tim_cb(MultiTimer* timer, void* userData)
{
	shell_task_handler(); /*执行shell任务*/
	
	letter_shell_tim_start(); /*重装载定时器*/
}
