#include "fsm_menu.h"
#include "./Lw_Queue/lw_queue.h"
#include "./OLED/OLED.h"

/*ȫ�ֱ�������*/
lw_que_t* que_menu_msg; /*�˵�״̬������Ϣ����*/
menu_fsm_t menu_fsm; /*�˵�״̬��*/
menu_event_t menu_event; /*�˵��¼�*/

/*��̬��������*/
static void page_0_load(void);
static void page_1_load(void);
static void page_2_load(void);
static void page_3_load(void);
static void page_1_1_load(void);
static void page_1_2_load(void);
static void page_2_1_load(void);
static void page_2_2_load(void);
static void page_3_1_load(void);
static void page_3_2_load(void);
static void page_flush(void);

/*ȫ�ֺ�������*/

/*�˵�״̬����ʼ��*/
void menu_init(menu_fsm_t* me)
{
	que_menu_msg = lw_queue_create(QUE_MENU_MSG_LEN); /*��̬�����˵���Ϣ����*/
	me->state = PAGE_0; /*���ó�ʼ״̬*/
	page_0_load(); /*��ʾ��һ��ҳ��*/
}

/*�˵�״̬��������*/
void menu_dispatch(menu_fsm_t* me, menu_event_t* event)
{
	/*����֧��������ж�״̬*/
	/*�ڲ��֧���������Ӧ�¼�*/
	switch(me->state)
	{
		case PAGE_0: 
			switch(event->menu_event_sinal)
			{
				case CONFIRM_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_1; /*״̬�л�*/
					page_1_load(); /*��ʾ��ҳ��*/					
				break;
			}
		break;
			
		case PAGE_1: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_3; /*״̬�л�*/
					page_3_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_2; /*״̬�л�*/
					page_2_load(); 
				break;
				
				case CONFIRM_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_1_1; /*״̬�л�*/
					page_1_1_load(); 
				break;
				
				case RETURN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_0; /*״̬�л�*/
					page_0_load(); 
				break;
			}		
		break;
		
		case PAGE_2: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_1; /*״̬�л�*/
					page_1_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_3; /*״̬�л�*/
					page_3_load(); 
				break;
				
				case CONFIRM_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_2_1; /*״̬�л�*/
					page_2_1_load(); 
				break;
				
				case RETURN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_0; /*״̬�л�*/
					page_0_load(); 
				break;
			}	
			break;
		
		case PAGE_3: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_2; /*״̬�л�*/
					page_2_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_1; /*״̬�л�*/
					page_1_load(); 
				break;
				
				case CONFIRM_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_3_1; /*״̬�л�*/
					page_3_1_load(); 
				break;
				
				case RETURN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_0; /*״̬�л�*/
					page_0_load(); 
				break;
			}	
			break;
		
		case PAGE_1_1: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_1_2; /*״̬�л�*/
					page_1_2_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_1_2; /*״̬�л�*/
					page_1_2_load(); 
				break;
				
				case CONFIRM_SIG: 
					break;
				
				case RETURN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_1; /*״̬�л�*/
					page_1_load(); 
				break;
			}	
			break;
		
		case PAGE_1_2: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_1_1; /*״̬�л�*/
					page_1_1_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_1_1; /*״̬�л�*/
					page_1_1_load(); 
				break;
				
				case CONFIRM_SIG: 
					break;
				
				case RETURN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_1; /*״̬�л�*/
					page_1_load(); 
				break;
			}	
			break;
		
		case PAGE_2_1: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_2_2; /*״̬�л�*/
					page_2_2_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_2_2; /*״̬�л�*/
					page_2_2_load(); 
				break;
				
				case CONFIRM_SIG: 
					break;
				
				case RETURN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_2; /*״̬�л�*/
					page_2_load(); 
				break;
			}	
			break;
		
		case PAGE_2_2: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_2_1; /*״̬�л�*/
					page_2_1_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_2_1; /*״̬�л�*/
					page_2_1_load(); 
				break;
				
				case CONFIRM_SIG: 
					break;
				
				case RETURN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_2; /*״̬�л�*/
					page_2_load(); 
				break;
			}	
			break;
		
		case PAGE_3_1: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_3_2; /*״̬�л�*/
					page_3_2_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_3_2; /*״̬�л�*/
					page_3_2_load(); 
				break;
				
				case CONFIRM_SIG: 
					break;
				
				case RETURN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_3; /*״̬�л�*/
					page_3_load(); 
				break;
			}	
			break;
		
		case PAGE_3_2: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_3_1; /*״̬�л�*/
					page_3_1_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_3_1; /*״̬�л�*/
					page_3_1_load(); 
				break;
				
				case CONFIRM_SIG: 
					break;
				
				case RETURN_SIG: 
					page_flush(); /*����*/
					me->state = PAGE_3; /*״̬�л�*/
					page_3_load(); 
				break;
			}	
			break;
		
	}
}

/*��̬��������*/

/*PAGE_0ҳ����غ���*/
static void page_0_load(void)
{
	OLED_ShowString(32, 16, "This's a", OLED_8X16);
	OLED_ShowString(12, 32, "menu fsm test", OLED_8X16);
}

/*PAGE_1ҳ����غ���*/
static void page_1_load(void)
{
	OLED_ShowString(0, 0, "-> page_1", OLED_8X16);
	OLED_ShowString(0, 16, "   page_2", OLED_8X16);
	OLED_ShowString(0, 32, "   page_3", OLED_8X16);
}

/*PAGE_2ҳ����غ���*/
static void page_2_load(void)
{
	OLED_ShowString(0, 0, "   page_1", OLED_8X16);
	OLED_ShowString(0, 16, "-> page_2", OLED_8X16);
	OLED_ShowString(0, 32, "   page_3", OLED_8X16);
}

/*PAGE_3ҳ����غ���*/
static void page_3_load(void)
{
	OLED_ShowString(0, 0, "   page_1", OLED_8X16);
	OLED_ShowString(0, 16, "   page_2", OLED_8X16);
	OLED_ShowString(0, 32, "-> page_3", OLED_8X16);
}

/*PAGE_1_1ҳ����غ���*/
static void page_1_1_load(void)
{
	OLED_ShowString(0, 0, "-> page_1_1", OLED_8X16);
	OLED_ShowString(0, 16, "   page_1_2", OLED_8X16);
}

/*PAGE_1_2ҳ����غ���*/
static void page_1_2_load(void)
{
	OLED_ShowString(0, 0, "   page_1_1", OLED_8X16);
	OLED_ShowString(0, 16, "-> page_1_2", OLED_8X16);
}

/*PAGE_2_1ҳ����غ���*/
static void page_2_1_load(void)
{
	OLED_ShowString(0, 0, "-> page_2_1", OLED_8X16);
	OLED_ShowString(0, 16, "   page_2_2", OLED_8X16);
}

/*PAGE_2_2ҳ����غ���*/
static void page_2_2_load(void)
{
	OLED_ShowString(0, 0, "   page_2_1", OLED_8X16);
	OLED_ShowString(0, 16, "-> page_2_2", OLED_8X16);
}

/*PAGE_3_1ҳ����غ���*/
static void page_3_1_load(void)
{
	OLED_ShowString(0, 0, "-> page_3_1", OLED_8X16);
	OLED_ShowString(0, 16, "   page_3_2", OLED_8X16);
}

/*PAGE_3_2ҳ����غ���*/
static void page_3_2_load(void)
{
	OLED_ShowString(0, 0, "   page_3_1", OLED_8X16);
	OLED_ShowString(0, 16, "-> page_3_2", OLED_8X16);
}

/*PAGEˢ�º���*/
static void page_flush(void)
{
	OLED_Clear();
} 
