#include "adc.h"
#include "stm8l15x_syscfg.h"
#include "stm8l15x_adc.h"



void ?adc_init(void)

{   
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1,ENABLE);//开启ADC1时钟

    ADC_VrefintCmd(ENABLE); //使能内部参考电压
    ADC_DeInit(ADC1);
    ADC_Init(ADC1,ADC_ConversionMode_Continuous,ADC_Resolution_12Bit,ADC_Prescaler_1);//连续转换，12位，转换时钟1分频

    ADC_ChannelCmd(ADC1,ADC_Channel_Vrefint,ENABLE);//使能内部参考电压通道
    ADC_Cmd(ADC1,ENABLE);//ADC使能


}



