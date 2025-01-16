#include "main.h"  
#include "usart.h"
#include "string.h"
#include "./Flexible_Button/flexbutton_porting.h"
#include "./Flexible_Button/flexible_button.h"

/******类型定义*********/

/*用户按键枚举定义*/
enum user_button_t
{
    USER_BUTTON_UP = 0, 
    USER_BUTTON_DOWM,    
    USER_BUTTON_CONFIRM,     
    USER_BUTTON_RETURN,    
};

/**********类型定义**********/

/*********全局变量定义*******/

/*定义按键数组*/
flex_button_t user_button[USER_BUTTON_NUM];

/**********全局变量定义******/


/*静态函数声明*/
static void user_btn_callback(void *arg);
static uint8_t user_btn_pin_read(void *arg);

/***********公共函数定义********/

/*初始化用户按键*/
void user_button_init(void)
{
	memset(&user_button[0], 0x0, sizeof(user_button));
	
	for(uint8_t i=0;i<USER_BUTTON_NUM;i++)
	{
		//user_button[i].id = i; /*按键id*/
		user_button[i].cb = user_btn_callback; /*设置按键事件回调*/
		user_button[i].usr_button_read = user_btn_pin_read; /*绑定按键引脚电平读取函数*/
        user_button[i].pressed_logic_level = 0;  /*设置按键按下的逻辑电平*/
        user_button[i].short_press_start_tick = FLEX_MS_TO_SCAN_CNT(800); /*设置短按事件触发的起始 tick*/
        user_button[i].long_press_start_tick = FLEX_MS_TO_SCAN_CNT(1500);  /*设置长按事件触发的起始 tick*/
        user_button[i].long_hold_start_tick = FLEX_MS_TO_SCAN_CNT(2500);   /*设置长按保持事件触发的起始 tick*/

		/*设置按键id*/
		switch(i)
		{
			case 0: user_button[i].id = USER_BUTTON_UP; break;
			
			case 1: user_button[i].id = USER_BUTTON_DOWM; break;
			
			case 2: user_button[i].id = USER_BUTTON_CONFIRM; break;
			
			case 3: user_button[i].id = USER_BUTTON_RETURN; break;
		}
		
		flex_button_register(&user_button[i]); /*注册按键到库*/
	}
}

/*******************静态函数定义**************/

/*用户按键的事件回调函数*/
static void user_btn_callback(void *arg)
{
	flex_button_t *btn = (flex_button_t *)arg;

    switch (btn->id)
    {
        case USER_BUTTON_UP:
            
			switch(btn->event)
			{
				case FLEX_BTN_PRESS_CLICK:			debug_printf(">>key up press\r\n"); break;
				
				case FLEX_BTN_PRESS_DOUBLE_CLICK:	debug_printf(">>key up double click\r\n"); break;
				
				case FLEX_BTN_PRESS_SHORT_START:	debug_printf(">>key up short clicking\r\n"); break;
				
				case FLEX_BTN_PRESS_LONG_HOLD:		debug_printf(">>key up long clicking\r\n"); break;
			}
		
            break;
		
        case USER_BUTTON_DOWM:
            
			switch(btn->event)
			{
				case FLEX_BTN_PRESS_CLICK:			debug_printf(">>key down press\r\n"); break;
				
				case FLEX_BTN_PRESS_DOUBLE_CLICK:	debug_printf(">>key down double click\r\n"); break;
				
				case FLEX_BTN_PRESS_SHORT_START:	debug_printf(">>key down short clicking\r\n"); break;
				
				case FLEX_BTN_PRESS_LONG_HOLD:		debug_printf(">>key down long clicking\r\n"); break;
			}
		
            break;
		
		case USER_BUTTON_CONFIRM:
            
			switch(btn->event)
			{
				case FLEX_BTN_PRESS_CLICK:			debug_printf(">>key confirm press\r\n"); break;
				
				case FLEX_BTN_PRESS_DOUBLE_CLICK:	debug_printf(">>key confirm double click\r\n"); break;
				
				case FLEX_BTN_PRESS_SHORT_START:	debug_printf(">>key confirm short clicking\r\n"); break;
				
				case FLEX_BTN_PRESS_LONG_HOLD:		debug_printf(">>key confirm long clicking\r\n"); break;
			}
		
            break;
		
		case USER_BUTTON_RETURN:
            
			switch(btn->event)
			{
				case FLEX_BTN_PRESS_CLICK:			debug_printf(">>key return press\r\n"); break;
				
				case FLEX_BTN_PRESS_DOUBLE_CLICK:	debug_printf(">>key return double click\r\n"); break;
				
				case FLEX_BTN_PRESS_SHORT_START:	debug_printf(">>key return short clicking\r\n"); break;
				
				case FLEX_BTN_PRESS_LONG_HOLD:		debug_printf(">>key return long clicking\r\n"); break;
			}
		
            break;
    }
}

/*按键引脚电平读取函数*/
static uint8_t user_btn_pin_read(void *arg)
{
	int16_t value = 0;

    flex_button_t *btn = (flex_button_t *)arg;

    switch (btn->id)
    {
        case USER_BUTTON_UP:
            value = HAL_GPIO_ReadPin(MENU_UP_GPIO_Port, MENU_UP_Pin);
            break;
		
        case USER_BUTTON_DOWM:
            value = HAL_GPIO_ReadPin(MENU_DOWN_GPIO_Port, MENU_DOWN_Pin);
            break;
		
		case USER_BUTTON_CONFIRM:
            value = HAL_GPIO_ReadPin(MENU_CONFIRM_GPIO_Port, MENU_CONFIRM_Pin);
            break;
		
		case USER_BUTTON_RETURN:
            value = HAL_GPIO_ReadPin(MENU_RETURN_GPIO_Port, MENU_RETURN_Pin);
            break;
		
        default:
            value = -1;
    }

    return value;
}

