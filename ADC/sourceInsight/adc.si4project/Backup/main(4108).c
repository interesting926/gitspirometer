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
#include "math.h"
#include "stm8l15x.h"
#include "main.h"
#include "Uart.h"
#include "IIC.h"
#include "adc.h"
#include "tim2.h"




//��һ��λ����Ƿ�Ϊ���־
int capacitySecondFlag=0;
//��ǰһ��λ���
float capacitySecond=0;
//�ܵķλ���
float capacitySeconds=0;



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
    ����һ���ӷλ���
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
float Calculate_LungCapacity_Second(void)
{
    int i;
    int ADCBuf[BUFFER_SIZE]={0};
    spirometer  Capacity={0,AIRDENSITY, PIPESIZE,PITOT,0};
    disableInterrupts();
    //�Ȱ�ADC�����ݱ�������
    memcpy(ADCBuf,ADCBuffer,BUFFER_SIZE);
    for(i=0;i<BUFFER_SIZE;i++)
    { 

   
        //������ѹ,
        Capacity.airPressure =  (((float)coefficientA*ADCBuffer[i]/PRECISION ) -(float)coefficientB);
        //���㵥λʱ������������
        Capacity.unitGasFlow = (PITOT * (float)sqrt(2*Capacity.airPressure - (Capacity.airDensity))*PIPESIZE);        
        //�����������ֵ����ʱ��
        Capacity.unitGasFlow =  (Capacity.unitGasFlow*(u32)samplingTime)/((u32)(unitTime));
        //�ۼ���������
        Capacity.lungCapacity += Capacity.unitGasFlow;
    }  
    if(Capacity.lungCapacity <= lungThreshold) Capacity.lungCapacity=0;
    enableInterrupts();
    return Capacity.lungCapacity;
 
}


/*  
    �������λ���

*/
void Calculate_LungCapacity_Seconds(void)
{



    capacitySecond = Calculate_LungCapacity_Second();
    //��һ�����һ�붼��0
    if((capacitySecond == 0)&&(capacitySecondFlag == 0))
    {
        capacitySeconds=0;
        
    }
    //��һ����0 ��һ�벻��0
    else if((capacitySecond == 0)&&(capacitySecondFlag != 0))
    {
        //capacitySeconds =0;
        //��ǰ�벻����0 ����־Ϊ1
        capacitySecondFlag=0;

    }
    //��ǰ�벻Ϊ0
    if(capacitySecond != 0)
    {
        capacitySeconds += capacitySecond;
        //��ǰ�벻����0 ����־Ϊ1
        capacitySecondFlag=1;

    }



}


void HardWare_Init(void)
{
    sys_clock_init();
    Init_USART1();
    enableInterrupts();
    Init_ADC();
    Timer2_Init(samplingTime);
}

void main(void)
{   
  HardWare_Init();



  while(1)
  {

    if(ADCOverFlag)
    {
        Calculate_LungCapacity_Seconds();
        ADCOverFlag=0;    
    }

    
  } 
}


