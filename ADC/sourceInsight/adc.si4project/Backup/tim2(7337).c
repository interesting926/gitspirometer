#include "stm8l15x_tim2.h"
#include "tim2.h"


//name:             GUA_Timer2_Init        
//introduce:        定时器2初始化  
//使用的是 HSE          12000000
//定时 1M =1US 
//******************************************************************************  
void Timer2_Init(int ARR)
{
  //时钟配置
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,ENABLE);  
 
  //1分频，向上计数，每13us定时中断一次 
  TIM2_DeInit();
  //1MS中断一次
  TIM2_TimeBaseInit(TIM2_Prescaler_128, TIM2_CounterMode_Up, 8*1000);     
  TIM2_ARRPreloadConfig(ENABLE);
  TIM2_ITConfig(TIM2_IT_Update , ENABLE);
  TIM2_Cmd(ENABLE);
}






