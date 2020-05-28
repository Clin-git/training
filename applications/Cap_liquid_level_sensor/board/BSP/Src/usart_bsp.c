/****************************************************************************************************************************************************************
** ��Ȩ:          2020-2030,��������Ϊ�Ƽ���չ���޹�˾
** �ļ���:        usart_bsp.c
** ����:          ���
** �汾:          V1.0.0
** ����:          2020-04-28
** ����:          ͨ�ô�������
** ����:          ͨ�ô��ڳ�ʼ��, Ϊ���������շ��ṩ�ײ㺯��
*****************************************************************************************************************************************************************
** �޸���:        No
** �汾:          No
** �޸�����:      No
** ����:          No
****************************************************************************************************************************************************************/

#include "usart_bsp.h"

/* ʹ��RT-Thread����ϵͳ,USING_RT_THREAD_OS��main.h�ж��� */
#ifdef USING_RT_THREAD_OS
#include "board.h"
#endif


/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

static UART_HandleTypeDef huart;
static DMA_HandleTypeDef hdma_usart_rx;
static DMA_HandleTypeDef hdma_usart_tx;


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
void BSP_USART_UART_Init(uint32_t baudrate, uint32_t parity)
{
    huart.Instance = USER_USART;
    if(parity == UART_PARITY_NONE)
    {
        huart.Init.WordLength = UART_WORDLENGTH_8B;
    }
    else if(parity == UART_PARITY_ODD 
        || parity == UART_PARITY_EVEN)
    {
        huart.Init.WordLength = UART_WORDLENGTH_9B;
    }
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    huart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;    
    huart.Init.BaudRate = baudrate;
    huart.Init.Parity = parity;

    if (HAL_UART_Init(&huart) != HAL_OK)
    {
        Error_Handler();
    }
    
}

/**
* ����       : HAL_UART_MspInit()
* ��������   : 2020-04-28
* ����       : ���
* ����       : ����ʱ�ӡ��ײ�ܽų�ʼ������HAL_UART_Init�ص����ã�
* �������   : uartHandle�����ڴ������
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : ���ڵ�ʱ�ӡ��ܽš��жϷ��������͵���usart_bsp.h�ļ����涨��
* �޸�����   :
*/
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
  
    USER_USART_TX_PIN_CLK_ENABLE();
    USER_USART_RX_PIN_CLK_ENABLE();

    GPIO_InitStruct.Pin = USER_USART_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = USER_USART_ALTERNATE;
    HAL_GPIO_Init(USER_USART_TX_PIN_GPIOX, &GPIO_InitStruct);
      
    GPIO_InitStruct.Pin = USER_USART_RX_PIN;
    HAL_GPIO_Init(USER_USART_RX_PIN_GPIOX, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart_rx.Instance = DMA1_Channel3;
    hdma_usart_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart_rx.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_usart_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart_rx);

    /* USART1_TX Init */
    hdma_usart_tx.Instance = DMA1_Channel2;
    hdma_usart_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart_tx.Init.Mode = DMA_NORMAL;
    hdma_usart_tx.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_usart_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart_tx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
    
    HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

/**
* ����       : HAL_UART_MspDeInit()
* ��������   : 2020-04-28
* ����       : ���
* ����       : ����ʱ�ӡ��ײ�ܽŷ���ʼ������HAL_UART_DeInit�ص����ã�
* �������   : uartHandle�����ڴ������ָ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : ���ڵ�ʱ�ӡ��ܽš��жϷ��������͵���usart_bsp.h�ļ����涨��
* �޸�����   :
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
    __HAL_RCC_USART1_CLK_DISABLE();
  
    HAL_GPIO_DeInit(USER_USART_TX_PIN_GPIOX, USER_USART_TX_PIN);
    HAL_GPIO_DeInit(USER_USART_RX_PIN_GPIOX, USER_USART_RX_PIN);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
} 

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
uint8_t BSP_UART_Transmit_DMA(uint8_t *pData, uint16_t Size)
{
    if(HAL_UART_Transmit_DMA(&huart, pData, Size) != HAL_OK)
    {
        return OP_FAILED;
    }
    return OP_SUCCESS;
}

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
uint8_t BSP_UART_Receive_DMA(uint8_t *pData, uint16_t Size)
{
    if(HAL_UART_Receive_DMA(&huart, pData, Size) != HAL_OK)
    {
        return OP_FAILED;
    }
    return OP_SUCCESS;
}

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
void BSP_UART_ReceiverTimeout_Config(uint32_t TimeoutValue)
{
    HAL_UART_DisableReceiverTimeout(&huart);
    __HAL_UART_DISABLE_IT(&huart, UART_IT_RTO);
    
    HAL_UART_ReceiverTimeout_Config(&huart, TimeoutValue);
    
    HAL_UART_EnableReceiverTimeout(&huart);
    __HAL_UART_ENABLE_IT(&huart, UART_IT_RTO);
}

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
__weak void HAL_UART_RxTimoCallback(UART_HandleTypeDef *huart)
{
    UNUSED(huart);
}

/**
* ����       : DMA1_Channel2_3_IRQHandler()
* ��������   : 2020-04-28
* ����       : ���
* ����       : DMA1ͨ��2��3���жϷ�����
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void DMA1_Channel2_3_IRQHandler(void)
{

  HAL_DMA_IRQHandler(&hdma_usart_tx);
  HAL_DMA_IRQHandler(&hdma_usart_rx);

}

/**
* ����       : USER_USART_IRQHANDLER()
* ��������   : 2020-04-28
* ����       : ���
* ����       : �����жϷ�����
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : USER_USART_IRQHANDLER��usart_bsp.h�ļ����涨��
* �޸�����   :
*/
void USER_USART_IRQHANDLER(void)
{

    if(__HAL_UART_GET_IT(&huart, UART_IT_RTO))
    {
        __HAL_UART_CLEAR_FLAG(&huart, UART_CLEAR_RTOF);    
        HAL_UART_RxTimoCallback(&huart);
    }
    
    if(__HAL_UART_GET_IT(&huart, UART_IT_TC) && __HAL_UART_GET_IT_SOURCE(&huart, UART_IT_TC))
    {
        CLEAR_BIT(huart.Instance->CR1, USART_CR1_TCIE);
        huart.gState = HAL_UART_STATE_READY;
        HAL_UART_TxCpltCallback(&huart);
    }
    
    if(__HAL_UART_GET_IT(&huart, UART_IT_PE))
    {
        __HAL_UART_CLEAR_FLAG(&huart, UART_CLEAR_PEF);    
    }
    
    if(__HAL_UART_GET_IT(&huart, UART_IT_FE))
    {
        __HAL_UART_CLEAR_FLAG(&huart, UART_CLEAR_FEF);    
    }
    
    if(__HAL_UART_GET_IT(&huart, UART_IT_NE))
    {
        __HAL_UART_CLEAR_FLAG(&huart, UART_CLEAR_NEF);    
    }
    
    if(__HAL_UART_GET_IT(&huart, UART_IT_ORE))
    {
        __HAL_UART_CLEAR_FLAG(&huart, UART_CLEAR_OREF);    
    }
}

