#ifndef __ANGLE_H__
#define __ANGLE_H__

#include "ADC.H"

#define MEASURE			10	// ��ʼ��ֹͣ�����ٽ�ֵ

unsigned int adc_init_num = 0, adc_cita = 0;
unsigned int zero;			// ��ʼֵ

sbit led = P3^6;


void Transform_Init()
{
	// ------����ΪAD��ʼ��-----
	Adc_Init();
//	IE |= 0xa0;         //����AD�ж� ע�⣬����ò�ѯ����ò�Ҫ��AD�жϣ���������ܻᵰ�����ģ�����
	ADC_CONTR = ADC_POWER | ADC_SPEEDHH | ADC_START | ch;
	Delay_10ms(5);
	adc_init_num = vin_channle[ch];
	// ------����ΪAD��ʼ��----
}


// ��200��AD��ƽ��ֵ
void Transform()
{
	uchar i;
	for (i = 0; i < 200; i ++)
	{
		GetADCResult();
		vin_channle[ ch ] = vin_channle[ ch ] + vin_temp; 
	} 	
	adc_cita = vin_channle[ ch ] / 200;	
	vin_channle[ ch ] = 0;		  
}
	

	
#endif















