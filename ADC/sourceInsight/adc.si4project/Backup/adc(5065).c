#include "stdio.h"
#include "stm8l15x_syscfg.h"
#include "stm8l15x_adc.h"
#include "stm8l15x_dma.h"
#include "adc.h"
#include "uart.h"



int Buffer[BUFFER_SIZE]  = {0};
uint8_t ADCCount=0;    //��ǰ�ɼ���ADC��ѹ����
u8 ADCEndFlag=0;

//u8 ADCStart=0;
//u16 ADCValueBuffer[];

void Delay(int nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {   
    nCount--;
  }
}

/*
void Init_ADC(void)
{   

    //GPIO_Init(GPIO_TypeDef * GPIOx, uint8_t GPIO_Pin, GPIO_Mode_TypeDef GPIO_Mode)

    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1,ENABLE);//����ADC1ʱ��
    ADC_VrefintCmd(ENABLE); //ʹ���ڲ��ο���ѹ
    ADC_DeInit(ADC1);
    ADC_Init(ADC1,ADC_ConversionMode_Continuous,ADC_Resolution_12Bit,ADC_Prescaler_1);//����ת����12λ��ת��ʱ��1��Ƶ

    ADC_ChannelCmd(ADC1,ADC_Channel_Vrefint,ENABLE);//ʹ���ڲ��ο���ѹͨ��
    ADC_Cmd(ADC1,ENABLE);//ADCʹ��


}


void GetValue_ADC(void)
{
    u16 adc1_value=0;
    float value=0;    
    char showBuf[50]={0};
    unsigned int temp=0;
    
    while(1)
    {
        ADC_SoftwareStartConv(ADC1); //�������ת��
        while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//�ȴ�ת������
        ADC_ClearFlag(ADC1,ADC_FLAG_EOC);//�����Ӧ��־
        adc1_value=ADC_GetConversionValue(ADC1); //��ȡת��ֵ
        value=(float)adc1_value*(3.2/4096); //���VDD��ѹ����λV
        if(value<2.8)
        {
          
          temp = value *100;
          sprintf(showBuf, "votalge %d.%d V\n", temp/100,temp%100 );
          printf("%s",showBuf);

          Delay(5000);

            
            
        }
    }

}*/

//����ת��
void Init_ADC(void)
{   

    GPIO_Init(GPIOE,GPIO_Pin_5, GPIO_Mode_In_PU_No_IT);

    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1,ENABLE);//����ADC1ʱ��
    ADC_VrefintCmd(ENABLE); //ʹ���ڲ��ο���ѹ
    ADC_DeInit(ADC1);
    ADC_Init(ADC1,ADC_ConversionMode_Single,ADC_Resolution_12Bit,ADC_Prescaler_1);//����ת����12λ��ת��ʱ��1��Ƶ

    ADC_ChannelCmd(ADC1,Spiro_Meter_Channel,ENABLE);//ʹ���ڲ��ο���ѹͨ��
    ADC_Cmd(ADC1,ENABLE);//ADCʹ��

}


//�������ܣ���ȡtimes ��ADC��ֵ�ۼӣ�ȥ�����ֵ����Сֵ֮�󷵻�ƽ��ֵ
//������times:��ȡADC�Ĵ��� ����   >=2
u16 GetValue_ADC(u8 times)
{
    int i=0;
    u32 adcx=0;
    u16 temp=0;
    u16 maxValue=0;
    u16 minValue=0;


    for(i=0;i<times;i++)
    {
        ADC_SoftwareStartConv(ADC1); //�������ת��
        while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//�ȴ�ת������
        ADC_ClearFlag(ADC1,ADC_FLAG_EOC);//�����Ӧ��־
        //adc1_value=ADC_GetConversionValue(ADC1); //��ȡת��ֵ
        temp = ADC_GetConversionValue(ADC1); //��ȡת��ֵ 
        if(temp > maxValue) maxValue = temp;
        if(temp < minValue) minValue = temp;
        adcx+=temp;
    }
    adcx = adcx - maxValue -minValue;
    adcx/=times-2;
    return adcx;
}


/*
    ��ΪSTM8�Ը�������֧�ֲ���
    ���ص�ѹֵ*100
*/
int GetVotage_ADC(void)
{
    u16 adc1_value=0;
    float Fvalue=0;  
    int Ivalue=0;

    adc1_value = GetValue_ADC(20);
    //��ADC�ɼ����ĵ�ѹװ����ʵ�ʵ�ѹ
    Fvalue=(float)adc1_value*(3.2/4096);
    Ivalue = (int)(Fvalue * 100.00);
    return Ivalue;   
}


//��ʾ��ǰ��ѹֵ
void ShowVotage_ADC(void)
{
    u16 adc1_value=0;
    float value=0;    
    char showBuf[50]={0};
    int temp=0;
    float airPress=0;
    
    while(1)
    {
        adc1_value = GetValue_ADC(20);
        //��ADC�ɼ����ĵ�ѹװ����ʵ�ʵ�ѹ
        value=(float)adc1_value*(3.2/4096);
        temp = (int)(value *100.00);
        sprintf(showBuf, "votalge %d.%d V ", temp/100, temp%100);
        printf("%s",showBuf);

        temp=0;
        airPress = 90.4 *value-19.3;
        temp = (int)(airPress *100.00);
        sprintf(showBuf, "airPress %d.%d Pa\n", temp/100, temp%100);
        printf("%s",showBuf);
        Delay(5000);          
    }
}


//ADC����DMA����ת��
void ADC_Config(void)
{
  GPIO_Init(GPIOE,GPIO_Pin_5, GPIO_Mode_In_FL_No_IT);
    
  /* Enable ADC1 clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
  /* Initialize and configure ADC1 */
  ADC_DeInit(ADC1);

  ADC_Init(ADC1, ADC_ConversionMode_Single  , ADC_Resolution_12Bit, ADC_Prescaler_1);
  //ADC_Init(ADC1, ADC_ConversionMode_Continuous, ADC_Resolution_12Bit, ADC_Prescaler_1);
  ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_24Cycles);
  ADC_SamplingTimeConfig(ADC1, ADC_Group_FastChannels, ADC_SamplingTime_24Cycles);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
  ADC_VrefintCmd(ENABLE);

  /* Enable ADC1 Channels 24 */
  ADC_ChannelCmd(ADC1, Spiro_Meter_Channel, ENABLE); /* connected to ADC_Channel_Vrefint */
  ADC_SoftwareStartConv(ADC1); //�������ת��
}

void DMA_Config(void)
{
  DMA_GlobalDeInit();
   /* Enable DMA1 clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_DMA1, ENABLE);
  /* Connect ADC to DMA channel 0 */
  SYSCFG_REMAPDMAChannelConfig(REMAP_DMA1Channel_ADC1ToChannel0);//ADCͨ��Ҫremap
  //BUFFER_SIZE
  DMA_Init(DMA1_Channel0, BUFFER_ADDRESS,
             ADC1_DR_ADDRESS,
             //ADC1->DRL,
             BUFFER_SIZE,
             DMA_DIR_PeripheralToMemory,
             DMA_Mode_Circular,
             DMA_MemoryIncMode_Inc,
             DMA_Priority_High,
             DMA_MemoryDataSize_HalfWord);
  /* DMA Channel0 enable */
  DMA_Cmd(DMA1_Channel0, ENABLE);
  /* Enable DMA1 channel0 Transfer complete interrupt */
  DMA_ITConfig(DMA1_Channel0, DMA_ITx_TC, ENABLE);   
  /* DMA enable */
  DMA_GlobalCmd(ENABLE);
  ADC_DMACmd(ADC1, ENABLE); 
}



void ADC_DMA_Start(void)
{
    ADC_Cmd(ADC1,ENABLE);//ADCʹ��
    ADC_SoftwareStartConv(ADC1); //�������ת��

}

void ADC_DMA_Stop(void)
{
    ADC_Cmd(ADC1,DISABLE);//�ر�ADC
}






