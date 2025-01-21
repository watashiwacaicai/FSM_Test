#include "main.h"  
#include "user_usart.h"
#include "string.h"
#include "./Flexible_Button/flexbutton_callback.h"
#include "./Flexible_Button/flexbutton_porting.h"
#include "./Flexible_Button/flexible_button.h"

/*********全局变量定义*******/

/*定义按键数组*/
flex_button_t user_button[USER_BUTTON_NUM];

/*静态函数声明*/
static uint8_t user_btn_pin_read(void *arg);

/***********公共函数定义********/

/*初始化用户按键*/
void user_button_init(void)
{
	memset(&user_button[0], 0x0, sizeof(user_button));
	
	for(uint8_t i = 0; i < USER_BUTTON_NUM; i++)
	{
		user_button[i].id = i; /*设置按键id*/
		user_button[i].cb = user_btn_callback; /*设置按键事件回调*/
		user_button[i].usr_button_read = user_btn_pin_read; /*绑定按键引脚电平读取函数*/
        user_button[i].pressed_logic_level = 0;  /*设置按键按下的逻辑电平*/
        user_button[i].short_press_start_tick = FLEX_MS_TO_SCAN_CNT(800); /*设置短按事件触发的起始 tick*/
        user_button[i].long_press_start_tick = FLEX_MS_TO_SCAN_CNT(1500);  /*设置长按事件触发的起始 tick*/
        user_button[i].long_hold_start_tick = FLEX_MS_TO_SCAN_CNT(2500);   /*设置长按保持事件触发的起始 tick*/
		
		flex_button_register(&user_button[i]); /*注册按键到库*/
	}
}

/*******************静态函数定义**************/

/*按键引脚电平读取函数*/
/*这个按键库的遍扫顺序是逆序的，因此按键的检测也得是逆序的*/
static uint8_t user_btn_pin_read(void *arg)
{
	int16_t value = 0;

    flex_button_t *btn = (flex_button_t *)arg;

    switch (btn->id)
    {
        case 3:
            value = HAL_GPIO_ReadPin(MENU_UP_GPIO_Port, MENU_UP_Pin);
            break;
		
        case 2:
            value = HAL_GPIO_ReadPin(MENU_DOWN_GPIO_Port, MENU_DOWN_Pin);
            break;
		
		case 1:
            value = HAL_GPIO_ReadPin(MENU_CONFIRM_GPIO_Port, MENU_CONFIRM_Pin);
            break;
		
		case 0:
            value = HAL_GPIO_ReadPin(MENU_RETURN_GPIO_Port, MENU_RETURN_Pin);
            break;
		
        default:
            value = 1;
    }

    return value;
}

