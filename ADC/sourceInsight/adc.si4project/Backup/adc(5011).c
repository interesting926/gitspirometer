#include "adc.h"
#include "stm8l15x_syscfg.h"
#include "stm8l15x_adc.h"



void ?adc_init(void)

{     GPIO_Init(GPIOD,GPIO_PIN_3,GPIO_MODE_IN_PU_NO_IT);//AIN4 IO����Ϊ��������

    ADC1_PrescalerConfig(ADC1_PRESSEL_FCPU_D2);//Ԥ��Ƶ2

    ADC1_ExternalTriggerConfig(ADC1_EXTTRIG_TIM,DISABLE);//��ʹ���ⲿ����

    ADC1_SchmittTriggerConfig(ADC1_SCHMITTTRIG_CHANNEL4,DISABLE);

    //��ֹAIN2 AIN4��ʩ���ش�����������IO��̬����

    //PD5,PD6�ϵ�ͨ�����ʩ���ط�ʽ���ûᵼ�´����޷��շ����ݣ�

    ??

    ADC1_ConversionConfig(ADC1_CONVERSIONMODE_SINGLE,//����ת��

    ????????????????????????ADC1_CHANNEL_4,//ֻ��ѡ��һ��ͨ����

    ????????????????????????ADC1_ALIGN_RIGHT);//�Ҷ���

?ADC1_Cmd(ENABLE);//����ADC

}



