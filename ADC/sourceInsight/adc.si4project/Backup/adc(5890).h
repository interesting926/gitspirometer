#ifndef ADC_H
#define ADC_H

#include "stm8l15x.h"


//�����Ƶ�ѹ�ɼ�ͨ��
#define Spiro_Meter_Channel ADC_Channel_23
//����������5ms
#define samplingTime  5
//��λ������1000ms
#define unitTime      1000
//������������ 1000/5 = 200
#define BUFFER_SIZE            ((uint16_t) 200)

//#include "stm8l15x_it.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADC1_DR_ADDRESS        ((uint16_t)0x5344)
#define BUFFER_ADDRESS         ((uint16_t)(&ADCBuffer))
extern int ADCBuffer[BUFFER_SIZE];
extern uint8_t ADCCount;
extern u8 ADCOverFlag;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
void ADC_Config(void);
void DMA_Config(void);
void ADC_DMA_Start(void);
void ADC_DMA_Stop(void);



void Init_ADC(void);
u16 GetValue_ADC(u8 times);
int GetVotage_ADC(void);
void ShowVotage_ADC(void);
#endif