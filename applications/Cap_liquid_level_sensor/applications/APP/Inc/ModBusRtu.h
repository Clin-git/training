#ifndef __MODBUSRTU_H
#define __MODBUSRTU_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "usart_app.h"
#include "ModBus_Conf.h"

//���ͻ����С
#define SEND_SIZE                       32

#ifndef RECEIVE_SIZE
//���ջ���Ĵ�С
#define RECEIVE_SIZE                    32
#endif

//�Զ��ϴ�����,��λ ms
#define AUTOUPLOAD_CYCLE                1000

#define BROADCASTADDR                     0x00                                  //�㲥��ַ

#define HOLDING_REG_REGION1_BGEIN         0x0030                                //���ּĴ�����ʼ��ַ1
#define HOLDING_REG_REGION1_END           0x0041                                //���ּĴ���������ַ1

#define INPUT_REG_REGION1_BEGIN           0x0000                                //����Ĵ�����ʼ��ַ1
#define INPUT_REG_REGION1_END             0x0006                                //����Ĵ���������ַ1
#define INPUT_REG_REGION2_BEGIN           0x0080                                //����Ĵ�����ʼ��ַ2
#define INPUT_REG_REGION2_END             0x0080                                //����Ĵ���������ַ2

#define SINGLE_COIL_REGION1_BEGIN         0x0050                                //������Ȧ�Ĵ�����ʼ��ַ1
#define SINGLE_COIL_REGION1_END           0x0053                                //������Ȧ�Ĵ���������ַ1

#define SPECIAL_COIL_REGION1_BEGIN        0x0000                                //����Ĵ�����ʼ��ַ1
#define SPECIAL_COIL_REGION1_END          0x0005                                //����Ĵ���������ַ1

#define MUL_REG_REGION1_BEGIN             0x0030                                //����Ĵ�����ʼ��ַ1
#define MUL_REG_REGION1_END               0x0041                                //����Ĵ���������ַ1

#define DEF_MUL_REG_REGION1_BEGIN         0x0080                                //�Զ���26/27������Ĵ�����ʼ��ַ1
#define DEF_MUL_REG_REGION1_END           0x00A2                                //�Զ���26/27������Ĵ���������ַ1
//#define DEF_MUL_REG_REGION2_BEGIN         0x0090                                //�Զ���26/27������Ĵ�����ʼ��ַ2
//#define DEF_MUL_REG_REGION2_END           0x0096                                //�Զ���26/27������Ĵ���������ַ2
//#define DEF_MUL_REG_REGION3_BEGIN         0x00B0                                //�Զ���26/27������Ĵ�����ʼ��ַ3
//#define DEF_MUL_REG_REGION3_END           0x00C0                                //�Զ���26/27������Ĵ���������ַ3

#define MUL_VERSION_INF_BEGIN             0x00E0                                //�汾��Ϣ��ʼ��ַ
#define MUL_VERSION_INF_END               0x00E5                                //�汾��Ϣ������ַ

#define MB_NONE_EXCEPTION                 0x00                                  //Modbus���쳣
#define MB_FUNC_EXCEPTION                 0x01                                  //Modbus��������Ч
#define MB_ADDR_EXCEPTION                 0x02                                  //Modbus���ʵ�ַʧ��
#define MB_VALU_EXCEPTION                 0x03                                  //Modbus������ֵ��Ч
#define MB_DEVC_EXCEPTION                 0x04                                  //Modbus�����豸ʧ��
#define MB_ACKN_EXCEPTION                 0x05                                  //Modbus�����豸��Ӧ��
#define MB_BUSY_EXCEPTION                 0x06                                  //Modbus�����豸æ
#define MB_PARI_EXCEPTION                 0x08                                  //Modbus�豸У�����
#define MB_REQ_FAILURE                    0x80                                  //Modbus�������

#define CALIB_CAPMIN_FLAG                 0x01                                  //�궨��������־
#define CALIB_CAPMAX_FLAG                 0x10                                  //�궨�������ȱ�־
#define CALIB_CAPEOC_FLAG                 0x11                                  //�����ݽ�����־

#define CALIB_CAPADMIN_FLAG               0x01                                  //�궨����AD����־
#define CALIB_CAPADLOW_FLAG               0x02                                  //�궨����AD�¿̶ȱ�־
#define CALIB_CAPADHIH_FLAG               0x10                                  //�궨����AD�Ͽ̶ȱ�־
#define CALIB_CAPADMAX_FLAG               0x20                                  //�궨����AD���ȱ�־
#define CALIB_CAPADEOC_FLAG               0x33                                  //�궨����AD������־

#define CALIB_CAPDAMIN_FLAG               0x01                                  //�궨����DA����־
#define CALIB_CAPDALOW_FLAG               0x02                                  //�궨����DA�¿̶ȱ�־
#define CALIB_CAPDAHIH_FLAG               0x10                                  //�궨����DA�Ͽ̶ȱ�־
#define CALIB_CAPDAMAX_FLAG               0x20                                  //�궨����DA���ȱ�־
#define CALIB_CAPDAEOC_FLAG               0x33                                  //�궨����DA������־

#define CALIB_TEMPDAMIN_FLAG              0x01                                  //�궨�¶�DA����־
#define CALIB_TEMPDAMAX_FLAG              0x10                                  //�궨�¶�DA���ȱ�־
#define CALIB_TEMPDAEOC_FLAG              0x11   

//�����豸
#define FREEZE_ENABLE                                0x0F
//�ⶳ�豸
#define FREEZE_DISABLE                               0x00

#define ADCLIB_ENABLE          0x0F
#define ADCLIB_DISABLE         0x00

#define NO_CHECK_ADDRESS                0
#define CHECK_ADDRESS                   1
    
    
/* ModBus����/���յĻ���ָ������ݳ��Ƚṹ */
typedef struct {
    uint8_t *Send_Buf;
    uint16_t Send_Len;
    uint8_t *Receive_Buf;
}ModBus_TX_RX_TypeDef;

/* ModBus����Ļ��������ṹ */
typedef struct _ModBusBaseParam_TypeDef {
    uint8_t Device_Addr;
    uint8_t BaudRate;
    uint8_t Parity;
    uint8_t AutoUpload;
    uint8_t Output_Mode;
    uint8_t Factory_Reset;
    uint8_t Freeze;
    uint8_t InRomWrEn;
    ModBus_TX_RX_TypeDef ModBus_TX_RX;
#ifdef USING_RT_THREAD_OS
    rt_sem_t TX_Lock;
#endif
    int     (*ModBus_CallBack) (struct _ModBusBaseParam_TypeDef *arg);
}ModBusBaseParam_TypeDef;


#ifdef __IN_FLASH_APP_H
/**
* ����       : ModBus_Init()
* ��������   : 2020-05-07
* ����       : ���
* ����       : ModBus��ʼ��
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ModBus_Init(ModBusBaseParam_TypeDef *ModBusBaseParam);
#else
/**
* ����       : ModBus_Init()
* ��������   : 2020-05-07
* ����       : ���
* ����       : ModBus��ʼ��
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
*              Param����������(���ֽ�˳������): 0,�豸��ַ; 
*              1,�����ʴ���; 2��żУ�����; 3�Զ��ϴ�����;
*              4,���ģʽ; 5,�豸�����־;
* �������   : ��
* ���ؽ��   : OP_SUCCESS(�ɹ�)��OP_FAILED(ʧ��)
* ע���˵�� : 
* �޸�����   :
*/
uint8_t ModBus_Init(ModBusBaseParam_TypeDef *ModBusBaseParam,
                uint8_t *Param, uint16_t Param_Size);
#endif

/**
* ����       : MDB_Get_CRC16()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���������Ϣ֡����CRC16У��
* �������   : Msg:��Ϣ�׵�ַ; MsgLen:��Ϣ֡����;
* �������   : ��
* ���ؽ��   : CRC16У����
* ע���˵�� : ��Ϣ���Ȳ���Ϊ0
* �޸�����   :
*/
uint16_t MDB_Get_CRC16(uint8_t *Msg, uint16_t MsgLen);

/**
* ����       : MDB_Snd_Msg_RTU()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���� Modbus RTU��Ϣ֡
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
*              Msg:��Ϣ�׵�ַ; 
*              MsgLen:��Ϣ֡����;
*              Check_Addr:�Ƿ����豸��ַ��Ч
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : ��Ϣ���Ȳ���Ϊ0������ʱ�Ƚⶳ�豸���豸��ַ����Ϊ�㲥��ַ
* �޸�����   :
*/
void MDB_Snd_Msg_RTU(ModBusBaseParam_TypeDef *ModBusBaseParam, uint8_t *pMsg, uint16_t len, uint8_t Check_Addr);

/**
* ����       : Send_Data()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���� Modbus ����
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
*              Msg:��Ϣ�׵�ַ; MsgLen:��Ϣ֡����;
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void Send_Data(ModBusBaseParam_TypeDef *ModBusBaseParam, uint8_t *pMsg, uint16_t len);

/**
* ����       : ModbusHandle()
* ��������   : 2020-04-29
* ����       : ���
* ����       : Modbus RTU��Ϣ֡������
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
*              arg:�û��Զ���Ĳ���,�����豸����
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ModbusHandle(ModBusBaseParam_TypeDef *ModBusBaseParam, void *arg);

/**
* ����       : ModbusFunc03()
* ��������   : 2020-04-29
* ����       : ���
* ����       : Modbus 03��������Ϣ֡����
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
*              arg:�û��Զ���Ĳ���,�����豸����
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ModbusFunc03(ModBusBaseParam_TypeDef *ModBusBaseParam, void *arg);

/**
* ����       : ModbusFunc04()
* ��������   : 2020-04-29
* ����       : ���
* ����       : Modbus 04��������Ϣ֡����
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
*              arg:�û��Զ���Ĳ���,�����豸����
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ModbusFunc04(ModBusBaseParam_TypeDef *ModBusBaseParam, void *arg);

/**
* ����       : ModbusFunc05()
* ��������   : 2020-04-29
* ����       : ���
* ����       : Modbus 05��������Ϣ֡����
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
*              arg:�û��Զ���Ĳ���,�����豸����
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ModbusFunc05(ModBusBaseParam_TypeDef *ModBusBaseParam, void *arg);

/**
* ����       : ModbusFunc10()
* ��������   : 2020-04-29
* ����       : ���
* ����       : Modbus 10��������Ϣ֡����
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
*              arg:�û��Զ���Ĳ���,�����豸����
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ModbusFunc10(ModBusBaseParam_TypeDef *ModBusBaseParam, void *arg);

/**
* ����       : ModbusFunc25()
* ��������   : 2020-04-29
* ����       : ���
* ����       : Modbus 25��������Ϣ֡����
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
*              arg:�û��Զ���Ĳ���,�����豸����
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ModbusFunc25(ModBusBaseParam_TypeDef *ModBusBaseParam, void *arg);

/**
* ����       : ModbusFunc26()
* ��������   : 2020-04-29
* ����       : ���
* ����       : Modbus 26��������Ϣ֡����
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
*              arg:�û��Զ���Ĳ���,�����豸����
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ModbusFunc26(ModBusBaseParam_TypeDef *ModBusBaseParam, void *arg);

/**
* ����       : ModbusFunc27()
* ��������   : 2020-04-29
* ����       : ���
* ����       : Modbus 27��������Ϣ֡����
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
*              arg:�û��Զ���Ĳ���,�����豸����
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ModbusFunc27(ModBusBaseParam_TypeDef *ModBusBaseParam, void *arg);

/**
* ����       : ModbusFunc2A()
* ��������   : 2020-04-29
* ����       : ���
* ����       : Modbus 2A��������Ϣ֡����
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ModbusFunc2A(ModBusBaseParam_TypeDef *ModBusBaseParam);

/**
* ����       : ModbusFunc2B()
* ��������   : 2020-04-29
* ����       : ���
* ����       : Modbus 2B��������Ϣ֡����
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ModbusFunc2B(ModBusBaseParam_TypeDef *ModBusBaseParam);

/**
* ����       : ModbusFunc41()
* ��������   : 2020-04-29
* ����       : ���
* ����       : Modbus 41��������Ϣ֡����
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ModbusFunc41(ModBusBaseParam_TypeDef *ModBusBaseParam);

/**
* ����       : ModbusAutoUpload()
* ��������   : 2020-04-29
* ����       : ���
* ����       : Modbus ��Ϣ֡�Զ��ϴ�����
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
*              arg:�û��Զ���Ĳ���,�����豸����
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void ModbusAutoUpload(ModBusBaseParam_TypeDef *ModBusBaseParam, void *arg);

/**
* ����       : SensorEvent()
* ��������   : 2020-04-29
* ����       : ���
* ����       : �������¼�����
* �������   : ModBusBaseParam: ModBus����Ļ��������ṹ��;
*              arg:�û��Զ���Ĳ���,�����豸����
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void SensorEvent(ModBusBaseParam_TypeDef *ModBusBaseParam, void *arg);


#ifdef __cplusplus
}
#endif
#endif
