#include "adc.h"
#include "stm8l15x_syscfg.h"
#include "stm8l15x_adc.h"



void ?adc_init(void)

{     GPIO_Init(GPIOD,GPIO_PIN_3,GPIO_MODE_IN_PU_NO_IT);//AIN4 IO设置为上拉输入

    ADC1_PrescalerConfig(ADC1_PRESSEL_FCPU_D2);//预分频2

    ADC1_ExternalTriggerConfig(ADC1_EXTTRIG_TIM,DISABLE);//不使用外部触发

    ADC1_SchmittTriggerConfig(ADC1_SCHMITTTRIG_CHANNEL4,DISABLE);

    //禁止AIN2 AIN4的施密特触发器，降低IO静态功耗

    //PD5,PD6上的通道如果施密特方式禁用会导致串口无法收发数据！

    ??

    ADC1_ConversionConfig(ADC1_CONVERSIONMODE_SINGLE,//单次转换

    ????????????????????????ADC1_CHANNEL_4,//只能选择一个通道！

    ????????????????????????ADC1_ALIGN_RIGHT);//右对齐

?ADC1_Cmd(ENABLE);//开启ADC

}



