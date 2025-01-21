#ifndef __FLEXBUTTON_PORTING_H
#define __FLEXBUTTON_PORTING_H

/*用户按键枚举定义*/
enum user_button_t
{                    
    USER_BUTTON_UP = 0,
	USER_BUTTON_DOWM,
	USER_BUTTON_CONFIRM,
	USER_BUTTON_RETURN	
};

/*按钮数量*/
#define USER_BUTTON_NUM 4

void user_button_init(void);

#endif
