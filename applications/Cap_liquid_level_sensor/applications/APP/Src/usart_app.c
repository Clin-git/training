/****************************************************************************************************************************************************************
** ��Ȩ:          2020-2030,��������Ϊ�Ƽ���չ���޹�˾
** �ļ���:        usart_app.c
** ����:          ���
** �汾:          V1.0.0
** ����:          2020-04-29
** ����:          ����ͨ��
** ����:          ���ڳ�ʼ�������������շ����жϴ���
*****************************************************************************************************************************************************************
** �޸���:        No
** �汾:          No
** �޸�����:      No
** ����:          No
****************************************************************************************************************************************************************/

#include "usart_app.h"


static uint16_t RX_Len = 0;
static uint16_t Used_RX_Len = 0;
static uint8_t RX_OverRun_Flag = 0;
static uint8_t TX_Cplt_Flag = 1;
static uint8_t RX_Updata_Flag = 0;
static uint8_t USART_Receive_Buf[RECEIVE_SIZE];     //���ڽ��ջ���


#ifdef  USART_USING_485

/**
* ����       : _485_RE_DE_GPIO_Init()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ��ʼ��485оƬ������������ƹܽ�
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : ��ͨ���궨��USART_USING_485������ر��������
* �޸�����   :
*/
static void _485_RE_DE_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  _485_RE_DE_PIN_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = _485_RE_DE_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(_485_RE_DE_GPIO_PORT, &GPIO_InitStruct);
  
  RX_ON;
}
#endif

/**
* ����       : Sensor_USART_Init()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���ݲ����ʺ���żУ�������ʼ������������
* �������   : baudrate_code,�����ʴ���; parity_code,��żУ�����ʹ���;
*              Receive_Data,���ջ���ָ��; Receive_Data_Size,���ջ����С;
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void Sensor_USART_Init(uint8_t baudrate_code, uint8_t parity_code)
{
    uint32_t baudrate;
    uint32_t parity;
    uint32_t timeout;
    
    switch(baudrate_code)
    {
        case USART_BAUDRATE_4800_CODE : baudrate = 4800;
        break;
        
        case USART_BAUDRATE_9600_CODE : baudrate = 9600;
        break;
        
        case USART_BAUDRATE_19200_CODE : baudrate = 19200;
        break;
        
        case USART_BAUDRATE_38400_CODE : baudrate = 38400;
        break;
        
        case USART_BAUDRATE_57600_CODE : baudrate = 57600;
        break;
        
        case USART_BAUDRATE_115200_CODE : baudrate = 115200;
        break;
        
        default : baudrate = DEFAULT_UART_BAUD;
        break;
    }
    switch(parity_code)
    {
        case USART_PARITY_NONE_CODE : parity = UART_PARITY_NONE;
        break;
        
        case USART_PARITY_ODD_CODE : parity = UART_PARITY_ODD;
        break;
        
        case USART_PARITY_EVEN_CODE : parity = UART_PARITY_EVEN;
        break;
        
        default : parity = UART_PARITY_NONE;
        break;
    }
    
    BSP_USART_UART_Init(baudrate, parity);
#ifdef  USART_USING_485
    _485_RE_DE_GPIO_Init();
#endif
    if(parity_code == USART_PARITY_NONE_CODE)
    {
        timeout = DEFAULT_UART_TIMEOUT * 10;
    }
    else
    {
        timeout = DEFAULT_UART_TIMEOUT * 11;
    }
    timeout = (timeout % 10) ? ((timeout / 10) + 1) : timeout / 10;
    BSP_UART_ReceiverTimeout_Config(timeout);
    BSP_UART_Receive_DMA(USART_Receive_Buf, RECEIVE_SIZE);
}

/**
* ����       : Sensor_USART_GetReceData()
* ��������   : 2020-05-15
* ����       : ���
* ����       : ��ȡʵ�ʽ��յ�����(����ʹ����DMAѭ��ģʽ,���뾭�����������ܱ�֤�������ݵ�����)
* �������   : ��
* �������   : ReceData:����ʵ�ʽ������ݵĻ���ָ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void Sensor_USART_GetReceData(uint8_t *ReceData)
{
    if(Used_RX_Len > RECEIVE_SIZE || RX_Len > RECEIVE_SIZE)
        return;
    
    if(Used_RX_Len > RX_Len)
    {
        memcpy( ReceData, USART_Receive_Buf 
                + Used_RX_Len
                - RX_Len, 
                RX_Len);
    }
    else
    {
        memcpy( ReceData, USART_Receive_Buf 
                + (RECEIVE_SIZE - RX_Len 
                + Used_RX_Len), 
                RX_Len - Used_RX_Len);
        memcpy( ReceData + RX_Len - Used_RX_Len, 
                USART_Receive_Buf, 
                Used_RX_Len);
    }
}

/**
* ����       : Sensor_USART_Get_RX_Len()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ��ȡ����������һ�ν��յ������ݳ���
* �������   : ��
* �������   : ��
* ���ؽ��   : һ�ν��յ������ݳ���
* ע���˵�� : 
* �޸�����   :
*/
uint16_t Sensor_USART_Get_RX_Len(void)
{
    return RX_Len;
}

/**
* ����       : Sensor_USART_Get_RXBuf_Used_Len()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ��ȡ���������ڽ��յ����ݺ󣬴ӽ��ջ���ͷ��������β���ĳ���
* �������   : ��
* �������   : ��
* ���ؽ��   : �ӽ��ջ���ͷ��������β���ĳ���
* ע���˵�� : 
* �޸�����   :
*/
uint16_t Sensor_USART_Get_RXBuf_Used_Len(void)
{
    return Used_RX_Len;
}

/* ʹ��RT-Thread����ϵͳ,USING_RT_THREAD_OS��main.h�ж��� */
#ifdef USING_RT_THREAD_OS
#include <rtthread.h>

#define USART_SEM_NAME      "usart"

static struct rt_semaphore usart_sem;
static struct rt_semaphore usart_tx_lock;

/**
* ����       : stm32_usart_sem_init()
* ��������   : 2020-05-18
* ����       : ���
* ����       : �����ź�����ʼ��
* �������   : ��
* �������   : ��
* ���ؽ��   : int����ֵ
* ע���˵�� : ������ʹ��RT-Thread���Զ���ʼ�����INIT_DEVICE_EXPORT
               ����ִ��,ϵͳ��λ���Զ���ʼ��
* �޸�����   :
*/
static int stm32_usart_sem_init(void)
{
    if( rt_sem_init(&usart_sem, USART_SEM_NAME, 0, RT_IPC_FLAG_FIFO) != RT_EOK
        || rt_sem_init(&usart_tx_lock, USART_TX_LOCK_NAME, 1, RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        return RT_ERROR;
    }
    
    return RT_EOK;        
}
INIT_DEVICE_EXPORT(stm32_usart_sem_init);

#endif

/**
* ����       : Sensor_USART_Get_RX_Updata_Flag()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ��ȡ���ո��±�־
* �������   : ��
* �������   : ��
* ���ؽ��   : ���ո��±�־
* ע���˵�� : 
* �޸�����   :
*/
uint8_t Sensor_USART_Get_RX_Updata_Flag(void)
{
/* ʹ��RT-Thread����ϵͳ,USING_RT_THREAD_OS��main.h�ж��� */
#ifdef USING_RT_THREAD_OS
    rt_sem_take(&usart_sem, RT_WAITING_FOREVER);    //��ȡ�ź���
#endif
    return RX_Updata_Flag;
}

/**
* ����       : Sensor_USART_Get_TX_Cplt_Flag()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ��ȡ������ɱ�־
* �������   : ��
* �������   : ��
* ���ؽ��   : ������ɱ�־
* ע���˵�� : 
* �޸�����   :
*/
uint8_t Sensor_USART_Get_TX_Cplt_Flag(void)
{  
    return TX_Cplt_Flag;
}

/**
* ����       : Sensor_USART_Clear_RX_Updata_Flag()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ������ո��±�־
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void Sensor_USART_Clear_RX_Updata_Flag(void)
{
    RX_Updata_Flag = 0;
}

/**
* ����       : Sensor_USART_Clear_TX_Cplt_Flag()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���������ɱ�־
* �������   : ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void Sensor_USART_Clear_TX_Cplt_Flag(void)
{
    TX_Cplt_Flag = 0;
}

/**
* ����       : HAL_UART_RxTimoCallback()
* ��������   : 2020-04-28
* ����       : ���
* ����       : ���ڽ��ճ�ʱ�жϻص�����
* �������   : huart,���ڴ������ָ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : �������Զ����һ����������HAL���в����ڵ�
* �޸�����   :
*/
void HAL_UART_RxTimoCallback(UART_HandleTypeDef *huart)
{
    uint16_t rx_buf_used;
    
    rx_buf_used = huart->RxXferSize - __HAL_DMA_GET_COUNTER(huart->hdmarx);
    if(RX_OverRun_Flag)
    {
        RX_Len = rx_buf_used + huart->RxXferSize - Used_RX_Len;        
        RX_OverRun_Flag = 0;
    }
    else
    {
        RX_Len = rx_buf_used - Used_RX_Len;    
    }
    Used_RX_Len = rx_buf_used;
    
/* ʹ��RT-Thread����ϵͳ,USING_RT_THREAD_OS��main.h�ж��� */    
#ifdef USING_RT_THREAD_OS
    rt_sem_release(&usart_sem);     //�ͷ��ź���
#endif
    RX_Updata_Flag = 1;
}

/**
* ����       : HAL_UART_RxCpltCallback()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���ڽ�������жϻص�����
* �������   : huart,���ڴ������ָ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    RX_OverRun_Flag = 1;
}  

/**
* ����       : HAL_UART_TxCpltCallback()
* ��������   : 2020-04-29
* ����       : ���
* ����       : ���ڷ�������жϻص�����
* �������   : huart,���ڴ������ָ��
* �������   : ��
* ���ؽ��   : ��
* ע���˵�� : 
* �޸�����   :
*/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
#ifdef  USART_USING_485
    RX_ON;
#endif
/* ʹ��RT-Thread����ϵͳ,USING_RT_THREAD_OS��main.h�ж��� */    
#ifdef USING_RT_THREAD_OS
    rt_sem_release(&usart_tx_lock);     //�ͷ��ź���
#endif
    TX_Cplt_Flag = 1;
}
