/****************************************************************************************************************************************************************
** ��Ȩ:          2020-2030,��������Ϊ�Ƽ���չ���޹�˾
** �ļ���:        dac_bsp.c
** ����:          ���
** �汾:          V1.0.0
** ����:          2020-04-27
** ����:          DAC ͨ�����ô�������
** ����:          DAC ͨ������ DACת��
*****************************************************************************************************************************************************************
** �޸���:        No
** �汾:          No
** �޸�����:      No
** ����:          No
****************************************************************************************************************************************************************/

#include "dac_bsp.h"
#include "VariaType.h"


/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

static DAC_HandleTypeDef hdac;

/**
* ����       : BSP_DAC_Init()
* ��������   : 2020-04-27
* ����       : ���
* ����       : DAC��ʼ��
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : DACͨ��ͨ��DAC_CHANNEL_4_ENABLE��DAC_CHANNEL_5_ENABLE�궨���
* �޸�����   :
*/
void BSP_DAC_Init(void)
{
#if defined(DAC_CHANNEL_1_ENABLE) || defined(DAC_CHANNEL_2_ENABLE)
    
  DAC_ChannelConfTypeDef sConfig = {0};

  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }
  
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
#if defined(DAC_CHANNEL_1_ENABLE) 
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
#endif
  
#if defined(DAC_CHANNEL_2_ENABLE)
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
#endif
  
#endif
}

/**
* ����       : HAL_DAC_MspInit()
* ��������   : 2020-04-27
* ����       : ���
* ����       : DACʱ�ӡ��ײ�ܽų�ʼ������HAL_DAC_Init�ص����ã�
* �������   : dacHandle��DAC�������
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : DACͨ��ͨ��DAC_CHANNEL_4_ENABLE��DAC_CHANNEL_5_ENABLE�궨���
* �޸�����   :
*/
void HAL_DAC_MspInit(DAC_HandleTypeDef* dacHandle)
{
#if defined(DAC_CHANNEL_1_ENABLE) || defined(DAC_CHANNEL_2_ENABLE)
    
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(dacHandle->Instance==DAC)
  {
  /* USER CODE BEGIN DAC_MspInit 0 */

  /* USER CODE END DAC_MspInit 0 */
    /* DAC clock enable */
    __HAL_RCC_DAC1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**DAC GPIO Configuration    
    PA4     ------> DAC_OUT1
    PA5     ------> DAC_OUT2 
    */
    
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
#if defined(DAC_CHANNEL_1_ENABLE)
    GPIO_InitStruct.Pin |= GPIO_PIN_4;
#endif
#if defined(DAC_CHANNEL_2_ENABLE)
    GPIO_InitStruct.Pin |= GPIO_PIN_5;
#endif
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN DAC_MspInit 1 */

  /* USER CODE END DAC_MspInit 1 */
  }
  
#endif
}

/**
* ����       : HAL_DAC_MspDeInit()
* ��������   : 2020-04-27
* ����       : ���
* ����       : DACʱ�ӡ��ײ�ܽŷ���ʼ������HAL_DAC_DeInit�ص����ã�
* �������   : dacHandle��DAC�������
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : DACͨ��ͨ��DAC_CHANNEL_4_ENABLE��DAC_CHANNEL_5_ENABLE�궨���
* �޸�����   :
*/
void HAL_DAC_MspDeInit(DAC_HandleTypeDef* dacHandle)
{
#if defined(DAC_CHANNEL_1_ENABLE) || defined(DAC_CHANNEL_2_ENABLE)
  uint32_t gpio_pin = 0;
    
  if(dacHandle->Instance==DAC)
  {
  /* USER CODE BEGIN DAC_MspDeInit 0 */

  /* USER CODE END DAC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DAC1_CLK_DISABLE();
  
    /**DAC GPIO Configuration    
    PA4     ------> DAC_OUT1
    PA5     ------> DAC_OUT2 
    */
#if defined(DAC_CHANNEL_1_ENABLE)
    gpio_pin |= GPIO_PIN_4;
#endif
#if defined(DAC_CHANNEL_2_ENABLE)
    gpio_pin |= GPIO_PIN_5;
#endif
    HAL_GPIO_DeInit(GPIOA, gpio_pin);

  /* USER CODE BEGIN DAC_MspDeInit 1 */

  /* USER CODE END DAC_MspDeInit 1 */
  }
  
#endif
} 

/**
* ����       : BSP_DAC_Convert()
* ��������   : 2020-04-27
* ����       : ���
* ����       : ָ��DACͨ��д��DAֵ
* �������   : DA_Value(DAֵ),DA_Channel_Num(DAͨ����)
* �������   : ��
* ���ؽ��   : OP_SUCCESS(�ɹ�),OP_FAILED(ʧ��)
* ע���˵�� : ���ֵ���ܳ���4095,ͨ����ֻ������(DA_CHANNEL_1��DA_CHANNEL_2)
* �޸�����   :
*/
uint8_t BSP_DAC_Convert(uint16_t DA_Value, DA_CHANNEL_NUM DA_Channel_Num)
{
  uint32_t channel;
  //DACֵ������Χ
  if(DA_Value > 4095)
  {
    return OP_FAILED;
  }

  if(DA_Channel_Num != DA_CHANNEL_1 && DA_Channel_Num != DA_CHANNEL_2)
  {
    return OP_FAILED;
  }
  
  if(DA_Channel_Num == DA_CHANNEL_1)
      channel = DAC_CHANNEL_1;
  else if(DA_Channel_Num == DA_CHANNEL_2)
      channel = DAC_CHANNEL_2;
  
  HAL_DAC_SetValue(&hdac, channel, DAC_ALIGN_12B_R, DA_Value);
  HAL_DAC_Start(&hdac, channel);
  
  return OP_SUCCESS;
}

/* ʹ��RT-Thread����ϵͳ,USING_RT_THREAD_OS��main.h�ж��� */
#ifdef USING_RT_THREAD_OS

static struct rt_device dac_device_obj;     //DAC�豸����

/**
* ����       : stm32_dac_init()
* ��������   : 2020-05-18
* ����       : ���
* ����       : DAC�豸��ʼ��,��������rt_device_registerע���,��
*              rt_device_init��rt_device_open����
* �������   : dev:�豸���
* �������   : ��
* ���ؽ��   : RT_EOK:�豸��ʼ���ɹ�; ����:�豸��ʼ��ʧ��
* ע���˵�� : 
* �޸�����   :
*/
static rt_err_t stm32_dac_init(rt_device_t dev)
{
    BSP_DAC_Init();
    
    return RT_EOK;
}

/**
* ����       : stm32_dac_open()
* ��������   : 2020-05-18
* ����       : ���
* ����       : DAC�豸��,��������rt_device_registerע���,��
*              rt_device_open����
* �������   : dev:�豸���; oflag:�豸����ģʽ��־
* �������   : ��
* ���ؽ��   : RT_EOK:�豸�򿪳ɹ�; 
*              -RT_EBUSY:����豸ע��ʱָ���Ĳ����а��� 
               RT_DEVICE_FLAG_STANDALONE ���������豸���������ظ���;
*              ����:�豸��ʧ��
* ע���˵�� : ���ﲻʹ���豸��,��ֻ����һ��RT_EOK
* �޸�����   :
*/
static rt_err_t  stm32_dac_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

/**
* ����       : stm32_dac_close()
* ��������   : 2020-05-18
* ����       : ���
* ����       : DAC�豸�ر�,��������rt_device_registerע���,��
*              rt_device_close����
* �������   : dev:�豸���;
* �������   : ��
* ���ؽ��   : RT_EOK:�豸�رճɹ�; 
*              -RT_ERROR:�豸�Ѿ���ȫ�رգ������ظ��ر��豸;
*              ����:�豸�ر�ʧ��
* ע���˵�� : ���ﲻʹ���豸�ر�,��ֻ����һ��RT_EOK
* �޸�����   :
*/
static rt_err_t  stm32_dac_close(rt_device_t dev)
{
    return RT_EOK;
}

/**
* ����       : stm32_dac_write()
* ��������   : 2020-05-18
* ����       : ���
* ����       : DAC�豸д����,��������rt_device_registerע���,��
*              rt_device_write����
* �������   : dev:�豸���;
*              pos:д������ƫ����;
*              buffer:�ڴ滺����ָ�룬д������ݽ��ᱻ�����ڻ�������;
*              size:д�����ݵĴ�С
* �������   : ��
* ���ؽ��   : size:д�����ݵ�ʵ�ʴ�С��������ַ��豸�����ش�С���ֽ�Ϊ
               ��λ������ǿ��豸�����صĴ�С�Կ�Ϊ��λ;
*              0:��Ҫ��ȡ��ǰ�̵߳� errno ���жϴ���״̬
* ע���˵�� : 
* �޸�����   :
*/
static rt_size_t stm32_dac_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    uint8_t i;
    
    for(i = pos; i < (size + pos); i++)
    {
        if(i >= DA_CHANNEL_TOTAL)
            return i - pos;
        BSP_DAC_Convert(*(uint16_t *)buffer, (DA_CHANNEL_NUM)i);
    }
    return size;
}

/**
* ����       : stm32_dac_control()
* ��������   : 2020-05-18
* ����       : ���
* ����       : DAC�豸����,��������rt_device_registerע���,��
*              rt_device_control����
* �������   : dev:�豸���;
*              cmd:��������֣��������ͨ�����豸�����������;
*              arg:���ƵĲ���
* �������   : ��
* ���ؽ��   : RT_EOK:����ִ�гɹ�;
*              -RT_ENOSYS:ִ��ʧ�ܣ�dev Ϊ��;
*              ����������:ִ��ʧ��
* ע���˵�� : ���ﲻʹ���豸����,��ֻ����һ��RT_EOK
* �޸�����   :
*/
static rt_err_t  stm32_dac_control(rt_device_t dev, int cmd, void *args)
{    
    return RT_EOK;
}

/**
* ����       : dac_device_init()
* ��������   : 2020-05-18
* ����       : ���
* ����       : DAC�豸������ʼ��,ע��ADC�豸
* �������   : ��
* �������   : ��
* ���ؽ��   : int����ֵ
* ע���˵�� : ������ʹ��RT-Thread���Զ���ʼ�����INIT_DEVICE_EXPORT
               ����ִ��,ϵͳ��λ���Զ���ʼ��
* �޸�����   :
*/
static int dac_device_init(void)
{
    dac_device_obj.type     = RT_Device_Class_Miscellaneous;
    dac_device_obj.init     = stm32_dac_init;
    dac_device_obj.open     = stm32_dac_open;
    dac_device_obj.close    = stm32_dac_close;
    dac_device_obj.read     = RT_NULL;
    dac_device_obj.write    = stm32_dac_write;
    dac_device_obj.control  = stm32_dac_control;
    
    dac_device_obj.user_data = &dac_device_obj;
    
    rt_device_register(&dac_device_obj, DAC_DEVICE_NAME, 
                        RT_DEVICE_FLAG_WRONLY
                        | RT_DEVICE_FLAG_STANDALONE);
    
    return RT_EOK;
}
INIT_DEVICE_EXPORT(dac_device_init);

#endif

