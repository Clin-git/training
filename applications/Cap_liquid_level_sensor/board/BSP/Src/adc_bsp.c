/****************************************************************************************************************************************************************
** ��Ȩ:          2020-2030,��������Ϊ�Ƽ���չ���޹�˾
** �ļ���:        adc_bsp.c
** ����:          ���
** �汾:          V1.0.0
** ����:          2020-04-27
** ����:          ADC��ͨ������ DMA�������� �ڲ��¶ȴ���������
** ����:          ADCģ���ͨ��DMA���� �ڲ��¶�ADCת��
*****************************************************************************************************************************************************************
** �޸���:        No
** �汾:          No
** �޸�����:      No
** ����:          No
****************************************************************************************************************************************************************/

#include "adc_bsp.h"
#include "VariaType.h"

/* ʹ��RT-Thread����ϵͳ,USING_RT_THREAD_OS��main.h�ж��� */
#ifdef USING_RT_THREAD_OS
#include "board.h"
#endif

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

static ADC_HandleTypeDef hadc;
static DMA_HandleTypeDef hdma_adc;

/**
* ����       : BSP_ADC_Init()
* ��������   : 2020-04-27
* ����       : ���
* ����       : DAC��ʼ��
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : ADCͨ��ͨ��ADC_CHANNEL_0_ENABLE��ADC_CHANNEL_1_ENABLE,...,ADC_CHANNEL_9_ENABLE,
*                      ADC_CHANNEL_TEMPSENSOR_ENABLE�궨���
* �޸�����   :
*/
void BSP_ADC_Init(void)
{
#if defined(ADC_CHANNEL_0_ENABLE) || defined(ADC_CHANNEL_1_ENABLE) \
    || defined(ADC_CHANNEL_2_ENABLE) || defined(ADC_CHANNEL_3_ENABLE) \
    || defined(ADC_CHANNEL_6_ENABLE) || defined(ADC_CHANNEL_7_ENABLE) \
    || defined(ADC_CHANNEL_8_ENABLE) || defined(ADC_CHANNEL_9_ENABLE)
    
  ADC_ChannelConfTypeDef sConfig = {0};

  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = ENABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  
  if (HAL_ADCEx_Calibration_Start(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;

#ifdef ADC_CHANNEL_0_ENABLE
  sConfig.Channel = ADC_CHANNEL_0;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
#endif
  
#ifdef ADC_CHANNEL_1_ENABLE
  sConfig.Channel = ADC_CHANNEL_1;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
#endif
  
#ifdef ADC_CHANNEL_2_ENABLE
  sConfig.Channel = ADC_CHANNEL_2;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
#endif
  
#ifdef ADC_CHANNEL_3_ENABLE
  sConfig.Channel = ADC_CHANNEL_3;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
#endif
  
#ifdef ADC_CHANNEL_6_ENABLE
  sConfig.Channel = ADC_CHANNEL_6;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
#endif
  
#ifdef ADC_CHANNEL_7_ENABLE
  sConfig.Channel = ADC_CHANNEL_7;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
#endif

#ifdef ADC_CHANNEL_8_ENABLE
  sConfig.Channel = ADC_CHANNEL_8;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
#endif
  
#ifdef ADC_CHANNEL_9_ENABLE
  sConfig.Channel = ADC_CHANNEL_9;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
#endif
  
#ifdef ADC_CHANNEL_TEMPSENSOR_ENABLE
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
#endif

#endif
}

/**
* ����       : HAL_ADC_MspInit()
* ��������   : 2020-04-27
* ����       : ���
* ����       : ADCʱ�ӡ��ײ�ܽų�ʼ������HAL_ADC_Init�ص����ã�
* �������   : adcHandle��ADC�������
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : ADCͨ��ͨ��ADC_CHANNEL_0_ENABLE��ADC_CHANNEL_1_ENABLE,...,ADC_CHANNEL_9_ENABLE,
*                      ADC_CHANNEL_TEMPSENSOR_ENABLE�궨���
* �޸�����   :
*/
void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{
#if defined(ADC_CHANNEL_0_ENABLE) || defined(ADC_CHANNEL_1_ENABLE) \
    || defined(ADC_CHANNEL_2_ENABLE) || defined(ADC_CHANNEL_3_ENABLE) \
    || defined(ADC_CHANNEL_6_ENABLE) || defined(ADC_CHANNEL_7_ENABLE) \
    || defined(ADC_CHANNEL_8_ENABLE) || defined(ADC_CHANNEL_9_ENABLE)
    
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
    /* DMA controller clock enable */
    __HAL_RCC_DMA1_CLK_ENABLE();
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();
      
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**ADC GPIO Configuration    
    PA0     ------> ADC_IN0
    PA1     ------> ADC_IN1
    PA2     ------> ADC_IN2
    PA3     ------> ADC_IN3
    PA6     ------> ADC_IN6
    PA7     ------> ADC_IN7
    PB0     ------> ADC_IN8
    PB1     ------> ADC_IN9 
    */
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
#if defined(ADC_CHANNEL_0_ENABLE) || defined(ADC_CHANNEL_1_ENABLE) \
    || defined(ADC_CHANNEL_2_ENABLE) || defined(ADC_CHANNEL_3_ENABLE) \
    || defined(ADC_CHANNEL_6_ENABLE) || defined(ADC_CHANNEL_7_ENABLE)
      
    __HAL_RCC_GPIOA_CLK_ENABLE();    
#if defined(ADC_CHANNEL_0_ENABLE)
    GPIO_InitStruct.Pin |= GPIO_PIN_0;
#endif
#if defined(ADC_CHANNEL_1_ENABLE)
    GPIO_InitStruct.Pin |= GPIO_PIN_1;
#endif
#if defined(ADC_CHANNEL_2_ENABLE)
    GPIO_InitStruct.Pin |= GPIO_PIN_2;
#endif
#if defined(ADC_CHANNEL_3_ENABLE)
    GPIO_InitStruct.Pin |= GPIO_PIN_3;
#endif
#if defined(ADC_CHANNEL_6_ENABLE)
    GPIO_InitStruct.Pin |= GPIO_PIN_6;
#endif
#if defined(ADC_CHANNEL_7_ENABLE)
    GPIO_InitStruct.Pin |= GPIO_PIN_7;
#endif
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif        
    
#if defined(ADC_CHANNEL_8_ENABLE) || defined(ADC_CHANNEL_9_ENABLE)

    __HAL_RCC_GPIOB_CLK_ENABLE(); 
    GPIO_InitStruct.Pin = 0;
#if defined(ADC_CHANNEL_8_ENABLE)
    GPIO_InitStruct.Pin |= GPIO_PIN_0;
#endif
#if defined(ADC_CHANNEL_9_ENABLE)
    GPIO_InitStruct.Pin |= GPIO_PIN_1;
#endif
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif
    

    /* ADC1 DMA Init */
    /* ADC Init */
    hdma_adc.Instance = DMA1_Channel1;
    hdma_adc.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc.Init.Mode = DMA_CIRCULAR;
    hdma_adc.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_adc) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc);

    /* DMA interrupt init */
    /* DMA1_Channel1_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
    /* ADC1 interrupt Init */
    HAL_NVIC_SetPriority(ADC1_COMP_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(ADC1_COMP_IRQn);
  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
  
#endif
}

/**
* ����       : HAL_ADC_MspDeInit()
* ��������   : 2020-04-27
* ����       : ���
* ����       : ADCʱ�ӡ��ײ�ܽŷ���ʼ������HAL_ADC_DeInit�ص����ã�
* �������   : adcHandle��ADC�������
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : ADCͨ��ͨ��ADC_CHANNEL_0_ENABLE��ADC_CHANNEL_1_ENABLE,...,ADC_CHANNEL_9_ENABLE,
*                      ADC_CHANNEL_TEMPSENSOR_ENABLE�궨���
* �޸�����   :
*/
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{
#if defined(ADC_CHANNEL_0_ENABLE) || defined(ADC_CHANNEL_1_ENABLE) \
    || defined(ADC_CHANNEL_2_ENABLE) || defined(ADC_CHANNEL_3_ENABLE) \
    || defined(ADC_CHANNEL_6_ENABLE) || defined(ADC_CHANNEL_7_ENABLE) \
    || defined(ADC_CHANNEL_8_ENABLE) || defined(ADC_CHANNEL_9_ENABLE)
    
    uint32_t gpio_pin = 0;
    
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();
  
    /**ADC GPIO Configuration    
    PA0     ------> ADC_IN0
    PA1     ------> ADC_IN1
    PA2     ------> ADC_IN2
    PA3     ------> ADC_IN3
    PA6     ------> ADC_IN6
    PA7     ------> ADC_IN7
    PB0     ------> ADC_IN8
    PB1     ------> ADC_IN9 
    */
#if defined(ADC_CHANNEL_0_ENABLE) || defined(ADC_CHANNEL_1_ENABLE) \
    || defined(ADC_CHANNEL_2_ENABLE) || defined(ADC_CHANNEL_3_ENABLE) \
    || defined(ADC_CHANNEL_6_ENABLE) || defined(ADC_CHANNEL_7_ENABLE)
      
#if defined(ADC_CHANNEL_0_ENABLE)
      gpio_pin |= GPIO_PIN_0;
#endif
#if defined(ADC_CHANNEL_1_ENABLE)
      gpio_pin |= GPIO_PIN_1;
#endif
#if defined(ADC_CHANNEL_2_ENABLE)
      gpio_pin |= GPIO_PIN_2;
#endif
#if defined(ADC_CHANNEL_3_ENABLE)
      gpio_pin |= GPIO_PIN_3;
#endif
#if defined(ADC_CHANNEL_6_ENABLE)
      gpio_pin |= GPIO_PIN_6;
#endif
#if defined(ADC_CHANNEL_7_ENABLE)
      gpio_pin |= GPIO_PIN_7;
#endif

    HAL_GPIO_DeInit(GPIOA, gpio_pin);
                          
#endif

#if defined(ADC_CHANNEL_8_ENABLE) || defined(ADC_CHANNEL_9_ENABLE) \
      
#if defined(ADC_CHANNEL_8_ENABLE)
      gpio_pin |= GPIO_PIN_0;
#endif
#if defined(ADC_CHANNEL_9_ENABLE)
      gpio_pin |= GPIO_PIN_1;
#endif

    HAL_GPIO_DeInit(GPIOB, gpio_pin);
                          
#endif

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);

    /* ADC1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(ADC1_COMP_IRQn);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
#endif
} 

/**
* ����       : BSP_ADC_Start_DMA()
* ��������   : 2020-04-27
* ����       : ���
* ����       : ADC��ʼDMA����
* �������   : pData��DMA���ջ���ָ��;
*              Length�������С
* �������   : ��
* ���ؽ��   : OP_SUCCESS(�ɹ�),OP_FAILED(ʧ��)
* ע���˵�� : 
* �޸�����   :
*/
uint8_t BSP_ADC_Start_DMA(uint32_t *pData, uint32_t Length)
{
    if(HAL_ADC_Start_DMA(&hadc, pData,  Length) != HAL_OK)
    {
        return OP_FAILED;
    }
    return OP_SUCCESS;
}

/**
* ����       : BSP_ADC_Conver_Start()
* ��������   : 2020-05-14
* ����       : ���
* ����       : ADCת����ʼ
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void BSP_ADC_Conver_Start(void)
{
    SET_BIT(hadc.Instance->CR, ADC_CR_ADSTART);
}

/**
* ����       : BSP_ADC_Conver_Start()
* ��������   : 2020-05-14
* ����       : ���
* ����       : ADCת��ֹͣ
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void BSP_ADC_Conver_Stop(void)
{
    SET_BIT(hadc.Instance->CR, ADC_CR_ADSTP);
}

/**
* ����       : DMA1_Channel1_IRQHandler()
* ��������   : 2020-04-27
* ����       : ���
* ����       : DMA1ͨ��1�жϷ�����
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void DMA1_Channel1_IRQHandler(void)
{

  HAL_DMA_IRQHandler(&hdma_adc);

}

/**
* ����       : ADC1_COMP_IRQHandler()
* ��������   : 2020-04-27
* ����       : ���
* ����       : ADC1�жϷ�����
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ADC1_COMP_IRQHandler(void)
{

  HAL_ADC_IRQHandler(&hadc);

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
