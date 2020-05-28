#ifndef __SPI_BSP_H
#define __SPI_BSP_H
#ifdef __cplusplus
 extern "C" {
#endif


#include "main.h"
#include "VariaType.h"

#define USER_SPI                        SPI1
#define USER_SPI_ALTERNATE              GPIO_AF0_SPI1

/* USER CODE BEGIN Private defines */
#define USER_SPI_SCK_CLK_ENABLE()       __HAL_RCC_SPI1_CLK_ENABLE()
#define USER_SPI_SCK_CLK_DISABLE()      __HAL_RCC_SPI1_CLK_DISABLE()

#define USER_SPI_SCK_PIN_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()
#define USER_SPI_MISO_PIN_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define USER_SPI_MOSI_PIN_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define USER_SPI_SCK_PIN                GPIO_PIN_3
#define USER_SPI_MISO_PIN               GPIO_PIN_4
#define USER_SPI_MOSI_PIN               GPIO_PIN_5
#define USER_SPI_SCK_PIN_GPIOX          GPIOB
#define USER_SPI_MISO_PIN_GPIOX         GPIOB
#define USER_SPI_MOSI_PIN_GPIOX         GPIOB

#define USER_SPI_TIMEOUT                3000


/**
* ����       : BSP_SPI_Init()
* ��������   : 2020-05-20
* ����       : ���
* ����       : SPI��ʼ��
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void BSP_SPI_Init(void);

/**
* ����       : BSP_SPI_Transmit()
* ��������   : 2020-05-20
* ����       : ���
* ����       : SPI��������
* �������   : pData�����ͻ���ָ��;
*              Size�������С
* �������   : ��
* ���ؽ��   : OP_SUCCESS(�ɹ�),OP_FAILED(ʧ��)
* ע���˵�� : 
* �޸�����   :
*/
uint8_t BSP_SPI_Transmit(uint8_t *pData, uint16_t Size);

/**
* ����       : BSP_SPI_Receive()
* ��������   : 2020-05-20
* ����       : ���
* ����       : SPI��������
* �������   : pData�����ջ���ָ��;
*              Size�������С
* �������   : ��
* ���ؽ��   : OP_SUCCESS(�ɹ�),OP_FAILED(ʧ��)
* ע���˵�� : 
* �޸�����   :
*/
uint8_t BSP_SPI_Receive(uint8_t *pData, uint16_t Size);

/**
* ����       : BSP_SPI_Receive()
* ��������   : 2020-05-20
* ����       : ���
* ����       : SPI���Ͳ���������
* �������   : TxData�����ͻ���ָ��; RxData: ���ջ���ָ��
*              Size�������С
* �������   : ��
* ���ؽ��   : OP_SUCCESS(�ɹ�),OP_FAILED(ʧ��)
* ע���˵�� : 
* �޸�����   :
*/
uint8_t BSP_SPI_TransmitReceive(uint8_t *TxData, uint8_t *RxData, uint16_t Size);


#ifdef __cplusplus
}
#endif
#endif /*__ spi_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
