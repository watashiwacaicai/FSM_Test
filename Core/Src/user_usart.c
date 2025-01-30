#include "usart.h"
#include "user_usart.h"
#include "stdio.h" /*�����ʽ���ַ�*/
#include "stdarg.h" /*���벻������*/
#include "string.h"
#include "./Letter_Shell/letter_shell_porting.h"
#include "./Lw_rb/lw_rb.h"

/*��̬��������*/
static char rec_data; /*���ڽ��յ���һ���ֽڵ�����*/

/*********ȫ�ֺ�������**********/

/*�������Դ��ڽ��պ���*/
void debug_usart_rec_start(void)
{		
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&rec_data, 1);
}

/*���Ը�ʽ���������*/
int debug_printf(const char *format, ...)
{
    char buffer[128]; /*����һ�������������ڴ洢��ʽ������ַ���*/
    va_list arg;      /*����һ���ɱ�����б�*/
    int len;          /*����һ�����������ڴ洢��ʽ�����ַ����ĳ���*/
   
    va_start(arg, format); /*��ʼ���ɱ�����б�ָ���һ���ɱ����*/	
    len = vsnprintf(buffer, sizeof(buffer), format, arg); /*�����ַ�����ʽ��*/  
    va_end(arg); /*����ɱ�����б�*/
    HAL_UART_Transmit(&DEBUG_USART, (uint8_t *)buffer, (uint16_t)len, 1000); /*��������ʽ���ͣ������жϳ�ͻ*/

    return len;
}

/*���Դ��ڵ��ֽڽ��պ���*/
void DEBUG_UART_RxCallback(void)
{			
	if(__HAL_UART_GET_FLAG(&DEBUG_USART, UART_FLAG_RXNE ) != RESET)
	{				
		rec_data = (char)READ_REG(DEBUG_USART.Instance->DR); /*ֱ�ӴӼĴ����ж�ȡ����*/	
		lw_rb_write(debug_data_rb, rec_data); /*�����յ����������������Ϣ����*/
	}
}
