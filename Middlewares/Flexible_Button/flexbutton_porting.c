#include "main.h"  
#include "user_usart.h"
#include "string.h"
#include "./Flexible_Button/flexbutton_callback.h"
#include "./Flexible_Button/flexbutton_porting.h"
#include "./Flexible_Button/flexible_button.h"

/*********ȫ�ֱ�������*******/

/*���尴������*/
flex_button_t user_button[USER_BUTTON_NUM];

/*��̬��������*/
static uint8_t user_btn_pin_read(void *arg);

/***********������������********/

/*��ʼ���û�����*/
void user_button_init(void)
{
	memset(&user_button[0], 0x0, sizeof(user_button));
	
	for(uint8_t i = 0; i < USER_BUTTON_NUM; i++)
	{
		user_button[i].id = i; /*���ð���id*/
		user_button[i].cb = user_btn_callback; /*���ð����¼��ص�*/
		user_button[i].usr_button_read = user_btn_pin_read; /*�󶨰������ŵ�ƽ��ȡ����*/
        user_button[i].pressed_logic_level = 0;  /*���ð������µ��߼���ƽ*/
        user_button[i].short_press_start_tick = FLEX_MS_TO_SCAN_CNT(800); /*���ö̰��¼���������ʼ tick*/
        user_button[i].long_press_start_tick = FLEX_MS_TO_SCAN_CNT(1500);  /*���ó����¼���������ʼ tick*/
        user_button[i].long_hold_start_tick = FLEX_MS_TO_SCAN_CNT(2500);   /*���ó��������¼���������ʼ tick*/
		
		flex_button_register(&user_button[i]); /*ע�ᰴ������*/
	}
}

/*******************��̬��������**************/

/*�������ŵ�ƽ��ȡ����*/
/*���������ı�ɨ˳��������ģ���˰����ļ��Ҳ���������*/
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

