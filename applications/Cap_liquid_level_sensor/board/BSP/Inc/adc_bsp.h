#ifndef __ADC_BSP_H
#define __ADC_BSP_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */



/* USER CODE BEGIN Private defines */

//#define ADC_CHANNEL_0_ENABLE
//#define ADC_CHANNEL_1_ENABLE
#define ADC_CHANNEL_2_ENABLE
//#define ADC_CHANNEL_3_ENABLE
//#define ADC_CHANNEL_6_ENABLE
//#define ADC_CHANNEL_7_ENABLE
//#define ADC_CHANNEL_8_ENABLE
//#define ADC_CHANNEL_9_ENABLE
#define ADC_CHANNEL_TEMPSENSOR_ENABLE

typedef enum {
#ifdef ADC_CHANNEL_0_ENABLE
    AD_CHANNEL_0,
#endif
#ifdef ADC_CHANNEL_1_ENABLE
    AD_CHANNEL_1,
#endif
#ifdef ADC_CHANNEL_2_ENABLE
    AD_CHANNEL_2,
#endif
#ifdef ADC_CHANNEL_3_ENABLE
    AD_CHANNEL_3,
#endif
#ifdef ADC_CHANNEL_6_ENABLE
    AD_CHANNEL_6,
#endif
#ifdef ADC_CHANNEL_7_ENABLE
    AD_CHANNEL_7,
#endif
#ifdef ADC_CHANNEL_8_ENABLE
    AD_CHANNEL_8,
#endif
#ifdef ADC_CHANNEL_9_ENABLE
    AD_CHANNEL_9,
#endif
#ifdef ADC_CHANNEL_TEMPSENSOR_ENABLE
    AD_CHANNEL_TEMPSENSOR,
#endif
    AD_CHANNEL_TOTAL
}AD_CHANNEL_NUM;


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
void BSP_ADC_Init(void);


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
uint8_t BSP_ADC_Start_DMA(uint32_t *pData, uint32_t Length);

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
void BSP_ADC_Conver_Start(void);

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
void BSP_ADC_Conver_Stop(void);


#ifdef __cplusplus
}
#endif
#endif /*__ adc_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
