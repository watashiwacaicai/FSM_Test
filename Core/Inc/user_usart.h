#ifndef __USER_USART_H
#define __USER_USART_H

/*∫Í∂®“Â*/
#define DEBUG_USART_DMA_RX	hdma_usart1_rx
#define DEBUG_USART_PORT	USART1
#define DEBUG_USART 		huart1

int debug_printf(const char *format, ...);
void debug_usart_rec_start(void);
void DEBUG_UART_RxCallback(void);

#endif
