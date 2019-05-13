#ifndef __ANGLE_H__
#define __ANGLE_H__

#include "ADC.H"

#define MEASURE			10	// 开始、停止测量临界值

unsigned int adc_init_num = 0, adc_cita = 0;
unsigned int zero;			// 初始值

sbit led = P3^6;


void Transform_Init()
{
	// ------以下为AD初始化-----
	Adc_Init();
//	IE |= 0xa0;         //开启AD中断 注意，如果用查询法最好不要开AD中断，否则你可能会蛋疼死的！！！
	ADC_CONTR = ADC_POWER | ADC_SPEEDHH | ADC_START | ch;
	Delay_10ms(5);
	adc_init_num = vin_channle[ch];
	// ------以上为AD初始化----
}


// 采200次AD求平均值
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















