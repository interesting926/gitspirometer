#include "stdio.h"
#include "stm8l15x_syscfg.h"
#include "stm8l15x_adc.h"
#include "adc.h"
#include "uart.h"




void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {   
    nCount--;
  }
}


void Init_ADC(void)

{   
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1,ENABLE);//开启ADC1时钟

    ADC_VrefintCmd(ENABLE); //使能内部参考电压
    ADC_DeInit(ADC1);
    ADC_Init(ADC1,ADC_ConversionMode_Continuous,ADC_Resolution_12Bit,ADC_Prescaler_1);//连续转换，12位，转换时钟1分频

    ADC_ChannelCmd(ADC1,ADC_Channel_Vrefint,ENABLE);//使能内部参考电压通道
    ADC_Cmd(ADC1,ENABLE);//ADC使能


}

void GetValue_ADC(void)
{
    u16 adc1_value=0;
    float value=0;
    while(1)
    {
        ADC_SoftwareStartConv(ADC1); //开启软件转换
        while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//等待转换结束
        ADC_ClearFlag(ADC1,ADC_FLAG_EOC);//清除对应标志
        adc1_value=ADC_GetConversionValue(ADC1); //获取转换值
        value=1.225*4096/adc1_value; //获得VDD电压，单位V
        if(value<2.8)
        {
            printf("ADC内部电压值:%f \n",value);
            Delay(5000);
            //GPIO_ResetBits(GPIOD,GPIO_Pin_4);
            //GPIO_ToggleBits(GPIOD,GPIO_Pin_5);
        }
    }

}



