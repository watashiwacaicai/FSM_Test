#ifndef __FLEXBUTTON_PORTING_H
#define __FLEXBUTTON_PORTING_H

/*�û�����ö�ٶ���*/
enum user_button_t
{                    
    USER_BUTTON_UP = 0,
	USER_BUTTON_DOWM,
	USER_BUTTON_CONFIRM,
	USER_BUTTON_RETURN	
};

/*��ť����*/
#define USER_BUTTON_NUM 4

void user_button_init(void);

#endif
