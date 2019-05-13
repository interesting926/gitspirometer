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
    肺活量的计算公式：Q =  K √(180.96V2-ρ-38.6)*F*T
    K: PITOT 皮托管系数
    V2：电压值
    ρ: airDensity 空气密度
    F：PIPESIZE 圆管面积
    T：采样时间

*/
float Calculate_Lung_Capacity(void)
{
    int i;
    //
    spirometer  Capacity={0,AIRDENSITY, PIPESIZE,PITOT,0};

    for(i=0;i<200;i++)
    {
        
        Capacity.airPressure = PITOT * sqrt(180.96*Buffer[i]-AIRDENSITY-38.6)*PIPESIZE*0.005;        
        Capacity.lungCapacity += Capacity.airPressure;
    }

    return Capacity.lungCapacity;



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
  GetVotage_ADC();
  //DMA_Config();

  
  //ADC_Config();
  //Init_ADC();
  //DMA_Config();
  //Timer2_Init(50);
  
  //GetVotage_ADC();
  //ADC_Config();
  //GetValue_ADC();
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
  } 
}


