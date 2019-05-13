/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    18-November-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "string.h"
#include "stm8l15x.h"
#include "main.h"
#include "Uart.h"
#include "IIC.h"
#include "adc.h"
#include "tim2.h"
#include "math.h"



/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#define LED_GPIO_PORT  (GPIOB)
#define LED_GPIO_PINS  (GPIO_PIN_5)



/* ��ʼ��ϵͳʱ�� */
void sys_clock_init(void)
{
  /* High speed internal clock prescaler: 1 */
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
  /* Select HSE as system clock source */
  CLK_SYSCLKSourceSwitchCmd(ENABLE);
  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
  while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI)
  {}
}

/*
    ����λ���
    ��ѹ����ѹ��ʽ:       p=90.48V-19.3
    �λ����ļ��㹫ʽ��Q =  K ��(2P-��) *F*T
    v:��ѹֵ
    P����ǰ��ѹ��Ӧ����ѹ
    K: PITOT Ƥ�й�ϵ��
    V2����ѹֵ
    ��: airDensity �����ܶ�
    F��PIPESIZE Բ�����
    T������ʱ�� ADC�ɼ���Ƶ���� 200HZ ��1S�ɼ�200������

*/
int Calculate_Lung_Capacity(void)
{
    int i;
    int ADCBuf[BUFFER_SIZE]={0};
    //
    spirometer  Capacity={0,AIRDENSITY, PIPESIZE,PITOT,0};


    //�Ȱ�ADC�����ݱ�������
    memcpy(ADCBuf,Buffer,BUFFER_SIZE);
    for(i=0;i<BUFFER_SIZE;i++)
    { 
        //������ѹ
        Capacity.airPressure =  ((u32)9048*ADCBuf[i]);
        //������ѹ
        Capacity.airPressure =  (9048U*ADCBuf[i]-1930U)/(PRECISION) ;
        //���㵥λʱ������������
        Capacity.unitGasFlow = (PITOT * (u32)sqrt((2U*Capacity.airPressure - AIRDENSITY))*PIPESIZE)/(PRECISION *PRECISION);        
        //�����������ֵ����ʱ��
        Capacity.unitGasFlow =  (Capacity.unitGasFlow*5U)/1000U;
        //�ۼ���������
        Capacity.lungCapacity += Capacity.unitGasFlow;
    }    
    return Capacity.lungCapacity;
 
}



void test()
{
    volatile u32 testA=9048U*20;
    u32 buf32[]={1,2,3};
    u16 buf16[]={1,2,3};
    u8 buf8[]={1,2,3};
    long buflong[]={1,2,3};
    int bufint[]={1,2,3};
    short bufshort[]={1,2,3};


}



void main(void)
{
  uint8_t i=0;   
  sys_clock_init();
  Init_USART1();

//  Init_ADC();
//  GetVotage_ADC();
  
  Init_ADC();
  Timer2_Init(5);
  //GetVotage_ADC();
  //ShowVotage_ADC();
  //DMA_Config();

  //test();

  while(1)
  {

    if(UartRlen)
    {
        for(i=0;i<UartRlen;i++)
        {
            Uart1_Send(UartRbuf[i]);
        }
        UartRlen =0;
    }
    if(IICOverFlag)
    {
        IICOverFlag=0;        
    }

    if(ADCOverFlag)
    {
        Calculate_Lung_Capacity();
        ADCOverFlag=0;    
    }

    
  } 
}


