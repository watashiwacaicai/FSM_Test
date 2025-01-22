#ifndef __FSM_MENU_H
#define __FSM_MENU_H

#include "stdint.h"
#include "./Lw_Queue/lw_queue.h"

/*宏定义*/

/*菜单消息队列的长度*/
#define QUE_MENU_MSG_LEN	10

/*类型定义*/

/*菜单事件定义*/
enum menu_sinal
{
	UP_SIG,	/*上翻事件*/
	DOWN_SIG, /*下翻事件*/
	CONFIRM_SIG, /*确认事件*/
	RETURN_SIG /*返回事件*/
};

/*菜单状态定义*/
enum menu_state
{
	PAGE_0,
	PAGE_1,
	PAGE_2,
	PAGE_3,
	PAGE_1_1,
	PAGE_1_2,
	PAGE_2_1,
	PAGE_2_2,
	PAGE_3_1,
	PAGE_3_2	
};

/*菜单基础事件类型定义*/
typedef struct menu_event
{
	uint8_t menu_event_sinal;
	
}menu_event_t;

/*菜单标准状态机类型定义*/
typedef struct _menu_fsm
{
	uint8_t state;	
	
}menu_fsm_t;

/*声明*/
extern lw_que_t* que_menu_msg; /*菜单状态机的消息队列*/
extern menu_fsm_t menu_fsm; /*菜单状态机*/

void menu_init(menu_fsm_t* me);
void menu_dispatch(menu_fsm_t* me, menu_event_t* event);

#endif
