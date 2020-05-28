#ifndef __TYPECONVERT_H
#define __TYPECONVERT_H

#include "stdint.h"

/**
* ����     : HexToFloat()
* ����     : ��32λ���ͱ���(���ģʽ)ת���ɸ�����ֵ(С��ģʽ)
* ������� : pData,�޷����ַ���ָ��
* ������� : ��
* ���ؽ�� : ת����ĸ�������ֵ
*/
float HexToFloat(uint8_t *pData);

/**
* ����     : HexToUlong()
* ����     : ��32λ���ͱ���(���ģʽ)ת�����޷���32λ����ֵ(С��ģʽ)
* ������� : pData,�޷����ַ���ָ��
* ������� : ��
* ���ؽ�� : ת������޷���32λ����ֵ
*/
uint32_t HexToUlong(uint8_t *pData);

/**
* ����     : floatToHexArray()
* ����     : �������ͱ���(С��ģʽ)ת�����޷���8λ����ֵ������(���ģʽ)
* ������� : fSource:�����ͱ���; num:������ֽڸ���
* ������� : pu8Temp:ת����Ľ��
* ���ؽ�� : ��
*/
void floatToHexArray(float fSource, uint8_t *pu8Temp, uint16_t num);

/**
* ����     : GetDelExtremeAndAverage()
* ����     : ����Array[]���鰴ָ��ͷ����SortHeadSize��β����SortTailSize����˳�����к�,
*            ��Array[DelHeadSize]��Array[ArraySize - DelTailSize - 1]��ƽ��ֵ
* ������� : Array[]:Ҫ�������в�����ƽ��ֵ������; ArraySize:���鳤��;
*            SortHeadSize:����ͷ�����г���,����ƽ��ֵʱ����ͷ���޳��ĳ���; 
*            SortTailSize:����β�����г���,����ƽ��ֵʱ����β���޳��ĳ���;
* ������� : ��
* ���ؽ�� : Array[]���鰴ָ��ͷ����SortHeadSize��β����SortTailSize����˳�����к�,
*            ��Array[DelHeadSize]��Array[ArraySize - DelTailSize - 1]��ƽ��ֵ
*/
uint32_t GetDelExtremeAndAverage(uint32_t Array[], uint32_t ArraySize, uint32_t SortHeadSize, uint32_t SortTailSize);

#endif
