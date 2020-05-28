#ifndef __ADC_APP_H
#define __ADC_APP_H
#ifdef __cplusplus
 extern "C" {
#endif


#include "adc_bsp.h"
#include "In_Flash_app.h"
#include "VariaType.h"

#define VREF30ADDR          ((uint32_t) 0x1FFFF7B8)             //30���϶�ADC�ο�ֵ��ַ
#define VREF110ADDR         ((uint32_t) 0x1FFFF7C2)             //110���϶�ADC�ο�ֵ��ַ

#define AD_GROUP_MAX        10                                  //ÿ��ͨ���ɼ��������û������Զ���
#define AD_CHANNEL_MAX      AD_CHANNEL_TOTAL                       //ʹ��ADCͨ�������û������Զ���
#define AD_SEQBUFF_MAX      (AD_GROUP_MAX * AD_CHANNEL_MAX)     //ADC���л����С

/* ADC�¶ȴ�����Ҫ�Ĳ����ṹ */
typedef struct {
    float Temper_K1;                                            //�¶�1����ϵ��K1
    float Temper_B1;                                            //�¶�1����ϵ��B1
    float Temper_K2;                                            //�¶�2����ϵ��K2
    float Temper_B2;                                            //�¶�2����ϵ��B2
    uint16_t TempDAMin;                                         //�¶�DAֵ���
    uint16_t TempDAMax;                                         //�¶�DAֵ������
    uint16_t TempDARange;                                       //�¶�DAֵ����
}ADC_TemperParam_TypeDef;

/* ADC�¶ȴ���������ݵĽṹ */
typedef struct {
    uint16_t TemperInAirAD;                                     //�����¶�ADֵ
    uint16_t TemperInLiquidAD;                                  //Һ���¶�ADֵ
    float TemperInAir;                                          //�����¶�
    float TemperInLiquid;                                       //Һ���¶�
}ADC_TemperOut_TypeDef;

/* ʹ��RT-Thread����ϵͳ,USING_RT_THREAD_OS��main.h�ж��� */
#ifdef USING_RT_THREAD_OS
#include <rtthread.h>

#define ADC_DEVICE_NAME         "adc"

struct rt_adc_device_obj {
    struct rt_device        dev;
    ADC_TemperParam_TypeDef ADC_TemperParam;
    ADC_TemperOut_TypeDef   ADC_TemperOut;
};
#endif

#ifdef __IN_FLASH_APP_H
/**
* ����       : Sensor_ADC_TemperParam_Init()
* ��������   : 2020-05-06
* ����       : ���
* ����       : ��ʼ���¶�ת����Ҫ�Ĳ����ṹ
* �������   : ��
* �������   : ADC_TemperParam,�¶�ת����Ҫ�Ĳ����ṹָ��;
* ���ؽ��   : ��
* ע���˵�� : Ҫʹ�ñ�����,Ҫ����In_Flash_app.c��In_Flash_app.h��
*              In_Flash.ch��In_Flash.h���ļ�
* �޸�����   :
*/
void Sensor_ADC_TemperParam_Init(ADC_TemperParam_TypeDef *ADC_TemperParam);
#else
/*
* ����       : Sensor_ADC_TemperParam_Init()
* ��������   : 2020-05-06
* ����       : ���
* ����       : ��ʼ���¶�ת����Ҫ�Ĳ����ṹ
* �������   : Param, Ҫд��ADC_TemperParam�Ĳ�������ָ��;
*              Param_Size, Param�Ĵ�С;
* �������   : ADC_TemperParam,�¶�ת����Ҫ�Ĳ����ṹָ��;
* ���ؽ��   : OP_SUCCESS(�ɹ�)��OP_FAILED(ʧ��)
* ע���˵�� : Param����������(���ֽ�˳������,���ģʽ): 0~1,�¶�1����ϵ��K1; 
*              2~3,�¶�1����ϵ��B1; 4~5,�¶�2����ϵ��K2; 6~7,�¶�2����ϵ��B2;
*              8~9,�¶�DAת�����ֵ; 10~11,�¶�DAת������ֵ;
* �޸�����   :
*/
uint8_t Sensor_ADC_TemperParam_Init(ADC_TemperParam_TypeDef *ADC_TemperParam, uint8_t *Param, 
                            uint16_t Param_Size);
#endif

/**
* ����       : Sensor_ADC_Init()
* ��������   : 2020-04-26
* ����       : ���
* ����       : ��ʼ��ADC�����stm32оƬ�ڲ��¶ȴ��������¶ȱ仯б�ʣ�����ADC��DMA����
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void Sensor_ADC_Init(void);

/**
* ����       : Sensor_ADC_GetChn_Value()
* ��������   : 2020-04-26
* ����       : ���
* ����       : �û���ȡADCͨ����ƽ���˲��������
* �������   : Channel_Num:ͨ����,ָ����ȡ��ͨ��
* �������   : ��
* ���ؽ��   : ƽ���˲���Ľ��
* ע���˵�� : 
* �޸�����   :
*/
uint16_t Sensor_ADC_GetChn_Value(AD_CHANNEL_NUM AD_Channel_Num);

/**
* ����       : Sensor_ADC_Get_TemperData()
* ��������   : 2020-04-26
* ����       : ���
* ����       : ��ȡADC�¶�����
* �������   : ��
* �������   : ��
* ���ؽ��   : �¶�ֵ
* ע���˵�� : �¶ȼ���ɲο�STM32F072�����ֲ�
* �޸�����   :
*/
float Sensor_ADC_Get_TemperData(void);

/**
* ����       : Sensor_ADC_Get_Updata_Flag()
* ��������   : 2020-04-26
* ����       : ���
* ����       : ��ȡADC���ݸ��±�־
* �������   : ��
* �������   : ��
* ���ؽ��   : ADC���±�־
* ע���˵�� : 
* �޸�����   :
*/
uint8_t Sensor_ADC_Get_Updata_Flag(void);
    
/**
* ����       : Sensor_ADC_Clean_Updata_Flag()
* ��������   : 2020-04-26
* ����       : ���
* ����       : ���ADC���±�־
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void Sensor_ADC_Clean_Updata_Flag(void);

#ifdef __cplusplus
}
#endif
#endif
