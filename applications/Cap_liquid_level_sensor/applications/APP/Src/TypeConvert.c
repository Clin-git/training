#include "TypeConvert.h"

/**
* ����     : HexToFloat()
* ����     : ��32λ���ͱ���(���ģʽ)ת���ɸ�����ֵ(С��ģʽ)
* ������� : pData,�޷����ַ���ָ��
* ������� : ��
* ���ؽ�� : ת����ĸ�������ֵ
*/
float HexToFloat(uint8_t *pData)
{
    uint32_t Data;
    Data = pData[0];
    Data <<= 8;
    Data += pData[1];
    Data <<= 8;
    Data += pData[2];
    Data <<= 8;
    Data += pData[3];
    return *(float*)&Data;
}

/**
* ����     : HexToUlong()
* ����     : ��32λ���ͱ���(���ģʽ)ת�����޷���32λ����ֵ(С��ģʽ)
* ������� : pData,�޷����ַ���ָ��
* ������� : ��
* ���ؽ�� : ת������޷���32λ����ֵ
*/
uint32_t HexToUlong(uint8_t *pData)
{
    uint32_t Data;
    Data = pData[0];
    Data <<= 8;
    Data += pData[1];
    Data <<= 8;
    Data += pData[2];
    Data <<= 8;
    Data += pData[3];
    return Data;
}

/**
* ����     : floatToHexArray()
* ����     : �������ͱ���(С��ģʽ)ת�����޷���8λ����ֵ������(���ģʽ)
* ������� : fSource:�����ͱ���; num:������ֽڸ���
* ������� : pu8Temp:ת����Ľ��
* ���ؽ�� : ��
*/
void floatToHexArray(float fSource, uint8_t *pu8Temp, uint16_t num)
{
    uint16_t i;
    uint32_t u32Source = *(uint32_t *)&fSource;

    for(i = 0; i < num; i++)
    {
        pu8Temp[num - i - 1] = (u32Source >> (8 * i)) & 0xFF;
    }
}

/**
* ����     : SortArrayExtreme()
* ����     : ��Array[]���鰴ָ��ͷ����SortHeadSize��β����SortTailSize����˳������
* ������� : Array[]:Ҫ���е�����; ArraySize:���鳤��;
*            SortHeadSize:����ͷ�����г���; SortTailSize:����β�����г���;
* ������� : ��
* ���ؽ�� : ��
*/
void SortArrayExtreme(uint32_t Array[], uint32_t ArraySize, uint32_t SortHeadSize, uint32_t SortTailSize)
{
    uint32_t i, j;
    uint32_t temp;

    for (i = 0; i < SortTailSize; i++)
    {
        for (j = 0; j < ArraySize - i - 1; j++)
        {
            if (Array[j] > Array[j+1])
            {
                temp = Array[j];
                Array[j] = Array[j+1];
                Array[j+1] = temp;
            }
        }
    }

    for (i = 0; i < SortHeadSize; i++)
    {
        for (j = ArraySize - SortTailSize - 1 ; j > i; j--)
        {
            if (Array[j - 1] > Array[j])
            {
                temp = Array[j - 1];
                Array[j - 1] = Array[j];
                Array[j] = temp;
            }
        }
    }
}

/**
* ����     : GetAverage()
* ����     : ����Array[]�����Array[DelHeadSize]��Array[ArraySize - DelTailSize - 1]��ƽ��ֵ
* ������� : Array[]:Ҫ����ƽ��ֵ������; ArraySize:���鳤��;
*            DelHeadSize:����ͷ���޳��ĳ���; DelTailSize:����β���޳��ĳ���;
* ������� : Array[DelHeadSize]��Array[ArraySize - DelTailSize - 1]��ƽ��ֵ
* ���ؽ�� : ��
*/
uint32_t GetAverage(uint32_t Array[], uint32_t ArraySize, uint32_t DelHeadSize, uint32_t DelTailSize)
{
    uint64_t sum = 0;

    if ((DelHeadSize + DelTailSize) >= ArraySize)
    {
        return 0;
    }

    for (long i = DelHeadSize; i < ArraySize - DelTailSize; i++)
    {
        sum += Array[i];
    }

    return(sum / (ArraySize - DelHeadSize - DelTailSize));
}

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
uint32_t GetDelExtremeAndAverage(uint32_t Array[], uint32_t ArraySize, uint32_t SortHeadSize, uint32_t SortTailSize)
{
    SortArrayExtreme(Array, ArraySize, SortHeadSize, SortTailSize);
    return(GetAverage(Array, ArraySize, SortHeadSize, SortTailSize));
}

