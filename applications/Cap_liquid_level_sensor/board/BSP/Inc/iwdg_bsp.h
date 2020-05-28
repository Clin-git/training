#ifndef __iwdg_H
#define __iwdg_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define IWDG_TIMEOUT        1000        //��ʱʱ��,��λ����

/**
* ����       : BSP_IWDG_Init()
* ��������   : 2020-04-27
* ����       : ���
* ����       : �������Ź���ʼ��
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : ���Ź�ʱ�����ڲ�40KHz������Ƶ��õ������ʱ�� = ��Ƶϵ��*����ֵ/40 ms��
*              ����8��Ƶ������ֵ4000�������ʱ��Ϊ 800 ms
* �޸�����   :
*/
void BSP_IWDG_Init(void);

/**
* ����       : BSP_IWDG_Refresh()
* ��������   : 2020-04-27
* ����       : ���
* ����       : �������Ź�ι��
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void BSP_IWDG_Refresh(void);

#ifdef __cplusplus
}
#endif
#endif /*__ iwdg_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
