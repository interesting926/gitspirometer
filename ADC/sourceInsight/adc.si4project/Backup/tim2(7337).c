#include "stm8l15x_tim2.h"
#include "tim2.h"


//name:             GUA_Timer2_Init        
//introduce:        ��ʱ��2��ʼ��  
//ʹ�õ��� HSE          12000000
//��ʱ 1M =1US 
//******************************************************************************  
void Timer2_Init(int ARR)
{
  //ʱ������
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,ENABLE);  
 
  //1��Ƶ�����ϼ�����ÿ13us��ʱ�ж�һ�� 
  TIM2_DeInit();
  //1MS�ж�һ��
  TIM2_TimeBaseInit(TIM2_Prescaler_128, TIM2_CounterMode_Up, 8*1000);     
  TIM2_ARRPreloadConfig(ENABLE);
  TIM2_ITConfig(TIM2_IT_Update , ENABLE);
  TIM2_Cmd(ENABLE);
}






