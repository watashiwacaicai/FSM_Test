#include "stdint.h"
#include "user_usart.h"
#include "fsm_menu.h"
#include "./Flexible_Button/flexible_button.h"
#include "./Flexible_Button/flexbutton_porting.h"
#include "./TLSF/tlsf.h"
#include "./TLSF/tlsf_porting.h"
#include "./Lw_Queue/lw_queue.h"

/*用户按键的事件回调函数*/
void user_btn_callback(void *arg)
{
	flex_button_t *btn = (flex_button_t *)arg;

    switch (btn->id)
    {
        case USER_BUTTON_UP:
            
			switch(btn->event)
			{
				case FLEX_BTN_PRESS_CLICK:	
				{		
					menu_event_t* send_msg = (menu_event_t*)tlsf_malloc(ccm_pool_manager, sizeof(menu_event_t)); /*为事件申请内存空间*/
					send_msg->menu_event_sinal = UP_SIG; /*事件赋值*/
					lw_queue_write(que_menu_msg, (void*)send_msg); /*将事件送入菜单消息队列*/
					debug_printf(">>key up press\r\n"); 
				break;
				}
				case FLEX_BTN_PRESS_DOUBLE_CLICK:	
					debug_printf(">>key up double click\r\n"); 
				break;
				
				case FLEX_BTN_PRESS_SHORT_START:	
					debug_printf(">>key up short clicking\r\n"); 
				break;
				
				case FLEX_BTN_PRESS_LONG_HOLD:		
					debug_printf(">>key up long clicking\r\n"); 
				break;
			}
		
        break;
		
        case USER_BUTTON_DOWM:
            
			switch(btn->event)
			{
				case FLEX_BTN_PRESS_CLICK:	
				{
					menu_event_t* send_msg = (menu_event_t*)tlsf_malloc(ccm_pool_manager, sizeof(menu_event_t)); /*为事件申请内存空间*/
					send_msg->menu_event_sinal = DOWN_SIG; /*事件赋值*/
					lw_queue_write(que_menu_msg, (void*)send_msg); /*将事件送入菜单消息队列*/
					debug_printf(">>key down press\r\n"); 
				break;
				}
				case FLEX_BTN_PRESS_DOUBLE_CLICK:	
					debug_printf(">>key down double click\r\n"); 
				break;
				
				case FLEX_BTN_PRESS_SHORT_START:	
					debug_printf(">>key down short clicking\r\n"); 
				break;
				
				case FLEX_BTN_PRESS_LONG_HOLD:		
					debug_printf(">>key down long clicking\r\n"); 
				break;
			}
		
        break;
		
		case USER_BUTTON_CONFIRM:
            
			switch(btn->event)
			{
				case FLEX_BTN_PRESS_CLICK:	
				{
					menu_event_t* send_msg = (menu_event_t*)tlsf_malloc(ccm_pool_manager, sizeof(menu_event_t)); /*为事件申请内存空间*/
					send_msg->menu_event_sinal = CONFIRM_SIG; /*事件赋值*/
					lw_queue_write(que_menu_msg, (void*)send_msg); /*将事件送入菜单消息队列*/
					debug_printf(">>key confirm press\r\n"); 
				break;
				}
				case FLEX_BTN_PRESS_DOUBLE_CLICK:	
					debug_printf(">>key confirm double click\r\n"); 
				break;
				
				case FLEX_BTN_PRESS_SHORT_START:	
					debug_printf(">>key confirm short clicking\r\n"); 
				break;
				
				case FLEX_BTN_PRESS_LONG_HOLD:		
					debug_printf(">>key confirm long clicking\r\n"); 
				break;
			}
		
        break;
		
		case USER_BUTTON_RETURN:
            
			switch(btn->event)
			{
				case FLEX_BTN_PRESS_CLICK:	
				{
					menu_event_t* send_msg = (menu_event_t*)tlsf_malloc(ccm_pool_manager, sizeof(menu_event_t)); /*为事件申请内存空间*/
					send_msg->menu_event_sinal = RETURN_SIG; /*事件赋值*/
					lw_queue_write(que_menu_msg, (void*)send_msg); /*将事件送入菜单消息队列*/
					debug_printf(">>key return press\r\n"); 
				break;
				}
				case FLEX_BTN_PRESS_DOUBLE_CLICK:	
					debug_printf(">>key return double click\r\n"); 
				break;
				
				case FLEX_BTN_PRESS_SHORT_START:	
					debug_printf(">>key return short clicking\r\n"); 
				break;
				
				case FLEX_BTN_PRESS_LONG_HOLD:		
					debug_printf(">>key return long clicking\r\n"); 
				break;
			}
		
        break;
    }
}

