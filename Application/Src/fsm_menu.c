#include "fsm_menu.h"
#include "./Lw_Queue/lw_queue.h"
#include "./OLED/OLED.h"

/*È«¾Ö±äÁ¿¶¨Òå*/
lw_que_t* que_menu_msg; /*²Ëµ¥×´Ì¬»úµÄÏûÏ¢¶ÓÁÐ*/
menu_fsm_t menu_fsm; /*²Ëµ¥×´Ì¬»ú*/
menu_event_t menu_event; /*²Ëµ¥ÊÂ¼þ*/

/*¾²Ì¬º¯ÊýÉùÃ÷*/
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

/*È«¾Öº¯Êý¶¨Òå*/

/*²Ëµ¥×´Ì¬»ú³õÊ¼»¯*/
void menu_init(menu_fsm_t* me)
{
	que_menu_msg = lw_queue_create(QUE_MENU_MSG_LEN); /*¶¯Ì¬´´½¨²Ëµ¥ÏûÏ¢¶ÓÁÐ*/
	me->state = PAGE_0; /*ÉèÖÃ³õÊ¼×´Ì¬*/
	page_0_load(); /*ÏÔÊ¾µÚÒ»¸öÒ³Ãæ*/
}

/*²Ëµ¥×´Ì¬»úµ÷¶ÈÆ÷*/
void menu_dispatch(menu_fsm_t* me, menu_event_t* event)
{
	/*Íâ²ã·ÖÖ§Óï¾äÓÃÓÚÅÐ¶Ï×´Ì¬*/
	/*ÄÚ²ã·ÖÖ§Óï¾äÓÃÓÚÏìÓ¦ÊÂ¼þ*/
	switch(me->state)
	{
		case PAGE_0: 
			switch(event->menu_event_sinal)
			{
				case CONFIRM_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_1; /*×´Ì¬ÇÐ»»*/
					page_1_load(); /*ÏÔÊ¾ÐÂÒ³Ãæ*/					
				break;
			}
		break;
			
		case PAGE_1: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_3; /*×´Ì¬ÇÐ»»*/
					page_3_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_2; /*×´Ì¬ÇÐ»»*/
					page_2_load(); 
				break;
				
				case CONFIRM_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_1_1; /*×´Ì¬ÇÐ»»*/
					page_1_1_load(); 
				break;
				
				case RETURN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_0; /*×´Ì¬ÇÐ»»*/
					page_0_load(); 
				break;
			}		
		break;
		
		case PAGE_2: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_1; /*×´Ì¬ÇÐ»»*/
					page_1_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_3; /*×´Ì¬ÇÐ»»*/
					page_3_load(); 
				break;
				
				case CONFIRM_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_2_1; /*×´Ì¬ÇÐ»»*/
					page_2_1_load(); 
				break;
				
				case RETURN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_0; /*×´Ì¬ÇÐ»»*/
					page_0_load(); 
				break;
			}	
			break;
		
		case PAGE_3: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_2; /*×´Ì¬ÇÐ»»*/
					page_2_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_1; /*×´Ì¬ÇÐ»»*/
					page_1_load(); 
				break;
				
				case CONFIRM_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_3_1; /*×´Ì¬ÇÐ»»*/
					page_3_1_load(); 
				break;
				
				case RETURN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_0; /*×´Ì¬ÇÐ»»*/
					page_0_load(); 
				break;
			}	
			break;
		
		case PAGE_1_1: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_1_2; /*×´Ì¬ÇÐ»»*/
					page_1_2_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_1_2; /*×´Ì¬ÇÐ»»*/
					page_1_2_load(); 
				break;
				
				case CONFIRM_SIG: 
					break;
				
				case RETURN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_1; /*×´Ì¬ÇÐ»»*/
					page_1_load(); 
				break;
			}	
			break;
		
		case PAGE_1_2: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_1_1; /*×´Ì¬ÇÐ»»*/
					page_1_1_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_1_1; /*×´Ì¬ÇÐ»»*/
					page_1_1_load(); 
				break;
				
				case CONFIRM_SIG: 
					break;
				
				case RETURN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_1; /*×´Ì¬ÇÐ»»*/
					page_1_load(); 
				break;
			}	
			break;
		
		case PAGE_2_1: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_2_2; /*×´Ì¬ÇÐ»»*/
					page_2_2_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_2_2; /*×´Ì¬ÇÐ»»*/
					page_2_2_load(); 
				break;
				
				case CONFIRM_SIG: 
					break;
				
				case RETURN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_2; /*×´Ì¬ÇÐ»»*/
					page_2_load(); 
				break;
			}	
			break;
		
		case PAGE_2_2: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_2_1; /*×´Ì¬ÇÐ»»*/
					page_2_1_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_2_1; /*×´Ì¬ÇÐ»»*/
					page_2_1_load(); 
				break;
				
				case CONFIRM_SIG: 
					break;
				
				case RETURN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_2; /*×´Ì¬ÇÐ»»*/
					page_2_load(); 
				break;
			}	
			break;
		
		case PAGE_3_1: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_3_2; /*×´Ì¬ÇÐ»»*/
					page_3_2_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_3_2; /*×´Ì¬ÇÐ»»*/
					page_3_2_load(); 
				break;
				
				case CONFIRM_SIG: 
					break;
				
				case RETURN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_3; /*×´Ì¬ÇÐ»»*/
					page_3_load(); 
				break;
			}	
			break;
		
		case PAGE_3_2: 
			switch(event->menu_event_sinal)
			{
				case UP_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_3_1; /*×´Ì¬ÇÐ»»*/
					page_3_1_load(); 
				break;
				
				case DOWN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_3_1; /*×´Ì¬ÇÐ»»*/
					page_3_1_load(); 
				break;
				
				case CONFIRM_SIG: 
					break;
				
				case RETURN_SIG: 
					page_flush(); /*ÇåÆÁ*/
					me->state = PAGE_3; /*×´Ì¬ÇÐ»»*/
					page_3_load(); 
				break;
			}	
			break;
		
	}
}

/*¾²Ì¬º¯Êý¶¨Òå*/

/*PAGE_0Ò³Ãæ¼ÓÔØº¯Êý*/
static void page_0_load(void)
{
	OLED_ShowString(32, 16, "This's a", OLED_8X16);
	OLED_ShowString(12, 32, "menu fsm test", OLED_8X16);
}

/*PAGE_1Ò³Ãæ¼ÓÔØº¯Êý*/
static void page_1_load(void)
{
	OLED_ShowString(0, 0, "-> page_1", OLED_8X16);
	OLED_ShowString(0, 16, "   page_2", OLED_8X16);
	OLED_ShowString(0, 32, "   page_3", OLED_8X16);
}

/*PAGE_2Ò³Ãæ¼ÓÔØº¯Êý*/
static void page_2_load(void)
{
	OLED_ShowString(0, 0, "   page_1", OLED_8X16);
	OLED_ShowString(0, 16, "-> page_2", OLED_8X16);
	OLED_ShowString(0, 32, "   page_3", OLED_8X16);
}

/*PAGE_3Ò³Ãæ¼ÓÔØº¯Êý*/
static void page_3_load(void)
{
	OLED_ShowString(0, 0, "   page_1", OLED_8X16);
	OLED_ShowString(0, 16, "   page_2", OLED_8X16);
	OLED_ShowString(0, 32, "-> page_3", OLED_8X16);
}

/*PAGE_1_1Ò³Ãæ¼ÓÔØº¯Êý*/
static void page_1_1_load(void)
{
	OLED_ShowString(0, 0, "-> page_1_1", OLED_8X16);
	OLED_ShowString(0, 16, "   page_1_2", OLED_8X16);
}

/*PAGE_1_2Ò³Ãæ¼ÓÔØº¯Êý*/
static void page_1_2_load(void)
{
	OLED_ShowString(0, 0, "   page_1_1", OLED_8X16);
	OLED_ShowString(0, 16, "-> page_1_2", OLED_8X16);
}

/*PAGE_2_1Ò³Ãæ¼ÓÔØº¯Êý*/
static void page_2_1_load(void)
{
	OLED_ShowString(0, 0, "-> page_2_1", OLED_8X16);
	OLED_ShowString(0, 16, "   page_2_2", OLED_8X16);
}

/*PAGE_2_2Ò³Ãæ¼ÓÔØº¯Êý*/
static void page_2_2_load(void)
{
	OLED_ShowString(0, 0, "   page_2_1", OLED_8X16);
	OLED_ShowString(0, 16, "-> page_2_2", OLED_8X16);
}

/*PAGE_3_1Ò³Ãæ¼ÓÔØº¯Êý*/
static void page_3_1_load(void)
{
	OLED_ShowString(0, 0, "-> page_3_1", OLED_8X16);
	OLED_ShowString(0, 16, "   page_3_2", OLED_8X16);
}

/*PAGE_3_2Ò³Ãæ¼ÓÔØº¯Êý*/
static void page_3_2_load(void)
{
	OLED_ShowString(0, 0, "   page_3_1", OLED_8X16);
	OLED_ShowString(0, 16, "-> page_3_2", OLED_8X16);
}

/*PAGEË¢ÐÂº¯Êý*/
static void page_flush(void)
{
	OLED_Clear();
} 
