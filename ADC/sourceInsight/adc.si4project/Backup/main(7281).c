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




//上一秒肺活量是否为零标志
int capacitySecondFlag=0;
//当前一秒肺活量
float capacitySecond=0;
//总的肺活量
float capacitySeconds=0;



/* 初始化系统时钟 */
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
    计算一秒钟肺活量
    计算肺活量
    电压和气压公式:       p=90.48V-19.3
    肺活量的计算公式：Q =  K √(2P-ρ) *F*T
    v:电压值
    P：当前电压对应的气压
    K: PITOT 皮托管系数
    V2：电压值
    ρ: airDensity 空气密度
    F：PIPESIZE 圆管面积
    T：采样时间 ADC采集的频率是 200HZ 即1S采集200个数据
*/
float Calculate_LungCapacity_Second(void)
{
    int i;
    int ADCBuf[BUFFER_SIZE]={0};
    spirometer  Capacity={0,AIRDENSITY, PIPESIZE,PITOT,0};
    disableInterrupts();
    //先把ADC的数据保存起来
    memcpy(ADCBuf,ADCBuffer,BUFFER_SIZE);
    for(i=0;i<BUFFER_SIZE;i++)
    { 

   
        //计算气压,
        Capacity.airPressure =  (((float)coefficientA*ADCBuffer[i]/PRECISION ) -(float)coefficientB);
        //计算单位时间内气体流量
        Capacity.unitGasFlow = (PITOT * (float)sqrt(2*Capacity.airPressure - (Capacity.airDensity))*PIPESIZE);        
        //将计算出来的值乘以时间
        Capacity.unitGasFlow =  (Capacity.unitGasFlow*(u32)samplingTime)/((u32)(unitTime));
        //累加气体流量
        Capacity.lungCapacity += Capacity.unitGasFlow;
    }  
    if(Capacity.lungCapacity <= lungThreshold) Capacity.lungCapacity=0;
    enableInterrupts();
    return Capacity.lungCapacity;
 
}


/*  
    计算多秒肺活量

*/
void Calculate_LungCapacity_Seconds(void)
{



    capacitySecond = Calculate_LungCapacity_Second();
    //这一秒和上一秒都是0
    if((capacitySecond == 0)&&(capacitySecondFlag == 0))
    {
        capacitySeconds=0;
        
    }
    //这一秒是0 上一秒不是0
    else if((capacitySecond == 0)&&(capacitySecondFlag != 0))
    {
        //capacitySeconds =0;
        //当前秒不等于0 ，标志为1
        capacitySecondFlag=0;

    }
    //当前秒不为0
    if(capacitySecond != 0)
    {
        capacitySeconds += capacitySecond;
        //当前秒不等于0 ，标志为1
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


