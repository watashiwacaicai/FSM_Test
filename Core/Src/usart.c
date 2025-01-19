/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

#include "stdio.h" /*�����ʽ���ַ�*/
#include "stdarg.h" /*���벻������*/
#include "string.h"
#include "./Letter_Shell/letter_shell_porting.h"

/*ȫ�ֱ�������*/

/*��̬��������*/
static char rec_data; /*���ڽ��յ���һ���ֽڵ�����*/

/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = DEBUG_UA_TX_Pin|DEBUG_UA_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, DEBUG_UA_TX_Pin|DEBUG_UA_RX_Pin);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/*********ȫ�ֺ�������**********/

/*�������Դ��ڽ��պ���*/
void debug_usart_rec_start(void)
{		
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&rec_data, 1);
}

/*���Ը�ʽ���������*/
int debug_printf(const char *format, ...)
{
    char buffer[256]; /*����һ�������������ڴ洢��ʽ������ַ���*/
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
		debug_que_send(&debug_data_queue, &rec_data); /*�����յ����������������Ϣ����*/
	}
}

/*********ȫ�ֺ�������**********/

/* USER CODE END 1 */
