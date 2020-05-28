#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "VariaType.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

#define USER_USART              USART1
#define USER_USART_ALTERNATE    GPIO_AF1_USART1

/* USER CODE BEGIN Private defines */
#define USER_USART_TX_PIN_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define USER_USART_RX_PIN_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define USER_USART_TX_PIN               GPIO_PIN_9
#define USER_USART_RX_PIN               GPIO_PIN_10
#define USER_USART_TX_PIN_GPIOX         GPIOA
#define USER_USART_RX_PIN_GPIOX         GPIOA

#define USER_USART_IRQHANDLER           USART1_IRQHandler


#ifndef OP_SUCCESS
#define OP_SUCCESS
#endif

#ifndef OP_FAILED
#define OP_FAILED
#endif



/**
* ����       : BSP_USART_UART_Init()
* ��������   : 2020-04-28
* ����       : ���
* ����       : ���ڳ�ʼ��
* �������   : baudrate,�����ʣ�parity,��żУ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void BSP_USART_UART_Init(uint32_t baudrate, uint32_t parity);

/**
* ����       : BSP_UART_Transmit_DMA()
* ��������   : 2020-04-28
* ����       : ���
* ����       : ���ڿ�ʼDMA����
* �������   : pData��DMA���ͻ���ָ��;
*              Size�������С
* �������   : ��
* ���ؽ��   : OP_SUCCESS(�ɹ�),OP_FAILED(ʧ��)
* ע���˵�� : 
* �޸�����   :
*/
uint8_t BSP_UART_Transmit_DMA(uint8_t *pData, uint16_t Size);

/**
* ����       : BSP_UART_Receive_DMA()
* ��������   : 2020-04-28
* ����       : ���
* ����       : ���ڿ�ʼDMA����
* �������   : pData��DMA���ջ���ָ��;
*              Size�������С
* �������   : ��
* ���ؽ��   : OP_SUCCESS(�ɹ�),OP_FAILED(ʧ��)
* ע���˵�� : 
* �޸�����   :
*/
uint8_t BSP_UART_Receive_DMA(uint8_t *pData, uint16_t Size);

/**
* ����       : BSP_UART_ReceiverTimeout_Config()
* ��������   : 2020-04-28
* ����       : ���
* ����       : �������ý��ճ�ʱ�ж�
* �������   : TimeoutValue����ʱʱ�䣬��λ������λ��;
*              ���磺1����ʼλ��8λ���ݣ�1��ֹͣλ�Ĵ������ã�
*              ��10λΪ1�������ֽڣ�������4�������ֽڵĳ�ʱʱ�䣬
*              TimeoutValue = 40
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void BSP_UART_ReceiverTimeout_Config(uint32_t TimeoutValue);

/**
* ����       : HAL_UART_RxTimoCallback()
* ��������   : 2020-04-28
* ����       : ���
* ����       : ���ڽ��ճ�ʱ�жϻص�����
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : �ú����Ǹ������庯�������������ļ����ض��壬�����Զ����һ����������HAL���в����ڵ�
* �޸�����   :
*/
void HAL_UART_RxTimoCallback(UART_HandleTypeDef *huart);
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
