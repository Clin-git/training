#ifndef __PICOCAP_APP_H
#define __PICOCAP_APP_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "Picocap.h"
#include "In_Flash_app.h"


/* PCap�ɼ����ڣ���λ ms */
#define PCAP_COLLECT_CYCLE              100

#define DATA_BUF_MAX                    10

#define DATA_2ND_FILTER_BUF_MAX         10

#define DATA_1ST_FILTER_BUF_MAX         96

#define PCAP_DAC_MIN_VALUE              0

#define PCAP_DAC_MAX_VALUE              4095

#define PCAP_ADC_MIN_VALUE              0

#define PCAP_ADC_MAX_VALUE              65535

/* �����˲���Ҫ�Ĳ����ṹ */
typedef struct {    
    uint8_t FilterStart;                //�˲���ʼ��־
    uint8_t InputCountMax;              //�ۼ���������ֵ������ΪDATA_BUF_MAX
    uint8_t FilterFactor;               //�˲�ϵ��
    uint8_t FilterBufMax;               //�˲���󻺴�
    uint16_t FilterCycle;               //�˲�����
    uint32_t InputRangeMax;             //���뷶Χ���ֵ
    uint32_t InputRangeMin;             //���뷶Χ��Сֵ 
}DataFilterParam;
    
/* PCap������ת����Ҫ�Ĳ����ṹ */
typedef struct {
    uint8_t CompenEn;                   //����ʹ��
    uint16_t HeightRange;               //�߶�����
    uint16_t CapADMin;                  //����ADֵ���
    uint16_t CapADLow;                  //����ADֵ�¿̶�
    uint16_t CapADHigh;                 //����ADֵ�Ͽ̶�
    uint16_t CapADMax;                  //����ADֵ������
    uint16_t CapDAMin;                  //����DAֵ���
    uint16_t CapDALow;                  //����DAֵ�¿̶�
    uint16_t CapDAHigh;                 //����DAֵ�Ͽ̶�
    uint16_t CapDAMax;                  //����DAֵ������
    uint32_t CapMin;                    //�������
    uint32_t CapMax;                    //����������
    uint32_t CapMinBak;                 //�������
    uint32_t CapMaxBak;                 //����������
    float Correct_K;                    //��������ϵ��K
    float Correct_B;                    //��������ϵ��B
}PCap_DataConvert_Param;

/* PCapת����������ݵĽṹ */
typedef struct {
    uint16_t LiquidHeightAD;            //Һλ�߶�ADֵ
    float LiquidHeight;                 //Һλ�߶�
    uint16_t PCapDA_ResultValue;        //����DAԭʼ���ֵ
    uint16_t PCapDA_OutValue;           //����DAת�����ֵ
    uint32_t PCap_ResultValue;          //PCapԭʼֵ
}PCap_DataConvert_Out_Param;

/* ʹ��RT-Thread����ϵͳ,USING_RT_THREAD_OS��main.h�ж��� */
#ifdef USING_RT_THREAD_OS
#include <rtthread.h>

#define PCAP_DEVICE_NAME        "pcap"

struct rt_pcap_device_obj {
    struct rt_device            dev;
    DataFilterParam             DataFilter;
    PCap_DataConvert_Param      PCap_DataConvert;
    PCap_DataConvert_Out_Param  PCap_DataConvert_Out;
};
#endif


/**
* ����       : SwitchCurFilter()
* ��������   : 2020-04-30
* ����       : ���
* ����       : �л��˲�ˮƽ����
* �������   : FiltFactor(�˲�ϵ��)
* �������   : FilterParam,ָ���˲������ṹ��;
* ���ؽ��   : ��
* ע���˵�� : �˲�ˮƽ��9�������ִӵ͵��߶�Ӧ�˲���ȴӵ͵���
* �޸�����   :
*/
void SwitchCurFilter(uint8_t FiltFactor, DataFilterParam *FilterParam);

#ifdef __IN_FLASH_APP_H
/**
* ����       : DataFilterParam_Init()
* ��������   : 2020-05-05
* ����       : ���
* ����       : ��ʼ�������˲���Ҫ�Ĳ����ṹ
* �������   : Filterfactor_CountMax, �˲�ϵ�����ۼ���������ֵ,�˲�ϵ���ڸ�8λ,
*              �ۼ���������ֵ�ڵ�8λ;
* �������   : FilterParam,�����˲���Ҫ�Ĳ����ṹָ��;
* ���ؽ��   : ��
* ע���˵�� : Ҫʹ�ñ�����,Ҫ����In_Flash_app.c��In_Flash_app.h��
*              In_Flash.ch��In_Flash.h���ļ�
* �޸�����   :
*/
void DataFilterParam_Init(DataFilterParam *FilterParam, uint16_t Filterfactor_CountMax);
#else
/**
* ����       : DataFilterParam_Init()
* ��������   : 2020-05-05
* ����       : ���
* ����       : ��ʼ�������˲���Ҫ�Ĳ����ṹ
* �������   : Filterfactor_CountMax, �˲�ϵ�����ۼ���������ֵ,�˲�ϵ���ڸ�8λ,
*              �ۼ���������ֵ�ڵ�8λ;
*              InputRangeMax, ���뷶Χ���ֵ;
*              InputRangeMin, ���뷶Χ��Сֵ;
* �������   : FilterParam,�����˲���Ҫ�Ĳ����ṹָ��;
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   : 
*/
void DataFilterParam_Init(DataFilterParam *FilterParam, uint16_t Filterfactor_CountMax,
                            uint32_t InputRangeMax, uint32_t InputRangeMin);
#endif

#ifdef __IN_FLASH_APP_H
/**
* ����       : DataConvertParam_Init()
* ��������   : 2020-05-05
* ����       : ���
* ����       : ��ʼ������ת����Ҫ�Ĳ����ṹ
* �������   : ��
* �������   : DataConvert_Param,����ת����Ҫ�Ĳ����ṹָ��;
* ���ؽ��   : ��
* ע���˵�� : Ҫʹ�ñ�����,Ҫ����In_Flash_app.c��In_Flash_app.h��
*              In_Flash.ch��In_Flash.h���ļ�
* �޸�����   :
*/
void DataConvertParam_Init(PCap_DataConvert_Param *DataConvert_Param);
#else
/**
* ����       : DataConvertParam_Init()
* ��������   : 2020-05-05
* ����       : ���
* ����       : ��ʼ������ת����Ҫ�Ĳ����ṹ
* �������   : CompenEn, ����ʹ��;
*              Param, Ҫд��DataConvert_Param�Ĳ�������ָ��;
*              Param_Size, Param�Ĵ�С;
* �������   : DataConvert_Param,����ת����Ҫ�Ĳ����ṹָ��;
* ���ؽ��   : OP_SUCCESS(�ɹ�)��OP_FAILED(ʧ��)
* ע���˵�� : Param�����ݷֲ�(���ֽڷֲ�): 0~1,λ�Ƹ߶�; 2~5,�����������;
*              6~9,������������; 10~13,�����������; 14~17,������������; 
*              18~19,����ADֵ���; 20~21,����ADֵ�¿̶�; 22~23,����ADֵ�Ͽ̶�; 
*              24~25,����ADֵ������; 26~27,����DAֵ���; 28~29,����DAֵ�¿̶�; 
*              30~31,����DAֵ�Ͽ̶�; 32~33,����DAֵ������; 34~35,��������ϵ��K; 
*              36~37,��������ϵ��B;
* �޸�����   :
*/
uint8_t DataConvertParam_Init(PCap_DataConvert_Param *DataConvert_Param, uint8_t CompenEn,
                            uint8_t *Param, uint16_t Param_Size);
#endif

/**
* ����       : Sensor_PCap_GetResult()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ��ȡPCapԭʼ�ɼ�ֵ
* �������   : reg_addr,����Ĵ����ĵ�ַ;
* �������   : PCap_Result,����PCap��������
* ���ؽ��   : �����ɹ�/ʧ��
* ע���˵�� : 
* �޸�����   : 
*/
uint8_t Sensor_PCap_GetResult(uint8_t reg_addr, uint32_t *PCap_Result);

/**
* ����       : Sensor_DataFilter()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���ݰ�ָ���˲����������˲�
* �������   : FilterParam,ָ���˲������ṹ��;InputValue,���������
* �������   : OutputValue,�˲����ֵ
* ���ؽ��   : �����ɹ�/ʧ��
* ע���˵�� : ʹ�ñ�����ǰ,�Ƚ�FilterParam��ʼ��(��������ÿһ����Ա�����ʵ�ֵ),����������ʹ��
* �޸�����   : 
*/
uint8_t Sensor_DataFilter(DataFilterParam *FilterParam, uint32_t InputValue, uint32_t *OutputValue);

/**
* ����       : Sensor_PCap_DataConvert()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���ݰ�ָ�����Ʋ�����������ת��
* �������   : DataConvert_Param,ָ�����Ʋ����ṹ��;InputValue,���������
* �������   : DataConvert_Out,������ݵĲ����ṹ��
* ���ؽ��   : ��
* ע���˵�� : ʹ�ñ�����ǰ,�Ƚ�DataConvert_Param��ʼ��(��������ÿһ����Ա�����ʵ�ֵ),����������ʹ��
* �޸�����   : 
*/
void Sensor_PCap_DataConvert(PCap_DataConvert_Param *DataConvert_Param, 
                                uint32_t InputValue, 
                                PCap_DataConvert_Out_Param *DataConvert_Out);

#ifdef __cplusplus
}
#endif
#endif
