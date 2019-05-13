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
int Calculate_Lung_Capacity(void)
{
    int i;
    int ADCBuf[BUFFER_SIZE]={0};
    //
    spirometer  Capacity={0,AIRDENSITY, PIPESIZE,PITOT,0};


    //先把ADC的数据保存起来
    memcpy(ADCBuf,Buffer,BUFFER_SIZE);
    for(i=0;i<BUFFER_SIZE;i++)
    { 
        //计算气压
        Capacity.airPressure =  ((u32)9048*ADCBuf[i]);
        //计算气压
        Capacity.airPressure =  (9048U*ADCBuf[i]-1930U)/(PRECISION) ;
        //计算单位时间内气体流量
        Capacity.unitGasFlow = (PITOT * (u32)sqrt((2U*Capacity.airPressure - AIRDENSITY))*PIPESIZE)/(PRECISION *PRECISION);        
        //将计算出来的值乘以时间
        Capacity.unitGasFlow =  (Capacity.unitGasFlow*5U)/1000U;
        //累加气体流量
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


