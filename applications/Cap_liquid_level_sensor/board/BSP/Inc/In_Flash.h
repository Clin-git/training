#ifndef __IN_FLASH_H
#define __IN_FLASH_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "VariaType.h"

#define FLASH_BASE_ADDRESS              0x0801E800                          //����Flash����ַ

#define FLASH_START                     0x0000                              //Flash��ʼ��ַ
#define FLASH_END                       0x17FF                              //Flash������ַ

#define FLASH_WR_ENABLE                 0x0F                                //Flashд����ʹ��
#define FLASH_WR_DISABLE                0x00                                //Flashд������ֹ

#define WRITE_FLASH_ERR_MAX             0x03                                //дFlash����������

/**
* ����       : InFlash_Write_OneByte()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���ڲ�Flashָ��λ��д��һ�ֽ�����
* �������   : RWAddr��д���ַ����WrData��д�����ݣ�
* �������   : ��
* ���ؽ��   : OP_SUCCESS���ɹ�����OP_FAILED��ʧ�ܣ�
* ע���˵�� : ��ַ����Խ��
* �޸�����   :
*/
uint8_t InFlash_Write_OneByte(uint16_t RWAddr, uint8_t WrData);

/**
* ����       : InFlash_Read_OneByte()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���ڲ�Flashָ��λ�ö�ȡһ�ֽ�����
* �������   : RWAddr����ȡ��ַ��
* �������   : ��
* ���ؽ��   : 1���ֽ�����
* ע���˵�� : ��ַ����Խ��
* �޸�����   :
*/
uint8_t InFlash_Read_OneByte(uint16_t RWAddr);

/**
* ����       : InFlash_Write_MultiBytes()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���ڲ�Flashָ��λ��д����ֽ�
* �������   : RWAddr(д��ʼ��ַ)��pWrbuf(�̶������ڴ�),Wrlen(д���ݳ���)
* �������   : ��
* ���ؽ��   : OP_SUCCESS���ɹ�����OP_FAILED��ʧ�ܣ�
* ע���˵�� : ��ַ����Խ��
* �޸�����   :
*/
uint8_t InFlash_Write_MultiBytes(uint16_t RWAddr, uint8_t const *pWrbuf, uint16_t Wrlen);

/**
* ����       : InFlash_Read_MultiBytes()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���ڲ�Flashָ��λ�ö�����ֽ�
* �������   : RWAddr(����ʼ��ַ)��Rdlen(�����ݳ���)
* �������   : pRdbuf(���ݶ��ڴ�)
* ���ؽ��   : ��
* ע���˵�� : ��ַ����Խ��
* �޸�����   :
*/
void InFlash_Read_MultiBytes(uint16_t RWAddr, uint8_t *pRdbuf, uint16_t Rdlen);

/**
* ����       : InFlash_Erase_Page()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���ڲ�Flashָ��λ�ò���ҳ
* �������   : RWAddr(������ʼ��ַ)��PageNb(����ҳ��Ŀ)
* �������   : ��
* ���ؽ��   : OP_SUCCESS���ɹ�����OP_FAILED��ʧ�ܣ�
* ע���˵�� : ��ַ����Խ��
* �޸�����   :
*/
uint8_t InFlash_Erase_Page(uint16_t RWAddr, uint8_t PageNb);
  
#ifdef __cplusplus
}
#endif
#endif

