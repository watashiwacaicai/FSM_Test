#ifndef __FSM_MENU_H
#define __FSM_MENU_H

#include "stdint.h"
#include "./Lw_Queue/lw_queue.h"

/*�궨��*/

/*�˵���Ϣ���еĳ���*/
#define QUE_MENU_MSG_LEN	10

/*���Ͷ���*/

/*�˵��¼�����*/
enum menu_sinal
{
	UP_SIG,	/*�Ϸ��¼�*/
	DOWN_SIG, /*�·��¼�*/
	CONFIRM_SIG, /*ȷ���¼�*/
	RETURN_SIG /*�����¼�*/
};

/*�˵�״̬����*/
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

/*�˵������¼����Ͷ���*/
typedef struct menu_event
{
	uint8_t menu_event_sinal;
	
}menu_event_t;

/*�˵���׼״̬�����Ͷ���*/
typedef struct _menu_fsm
{
	uint8_t state;	
	
}menu_fsm_t;

/*����*/
extern lw_que_t* que_menu_msg; /*�˵�״̬������Ϣ����*/
extern menu_fsm_t menu_fsm; /*�˵�״̬��*/

void menu_init(menu_fsm_t* me);
void menu_dispatch(menu_fsm_t* me, menu_event_t* event);

#endif
