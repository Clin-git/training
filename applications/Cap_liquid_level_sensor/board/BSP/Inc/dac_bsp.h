#ifndef __dac_H
#define __dac_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

//#define DAC_CHANNEL_1_ENABLE
#define DAC_CHANNEL_2_ENABLE

typedef enum {
    DA_CHANNEL_1,
    DA_CHANNEL_2,
    DA_CHANNEL_TOTAL
}DA_CHANNEL_NUM;

/* ʹ��RT-Thread����ϵͳ,USING_RT_THREAD_OS��main.h�ж��� */
#ifdef USING_RT_THREAD_OS
#include "board.h"

#define DAC_DEVICE_NAME     "dac"

#endif


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
void BSP_DAC_Init(void);

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
uint8_t BSP_DAC_Convert(uint16_t DA_Value, DA_CHANNEL_NUM DA_Channel_Num);

#ifdef __cplusplus
}
#endif
#endif /*__ dac_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
