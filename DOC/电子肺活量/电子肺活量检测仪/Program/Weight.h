#ifndef __ANGLE_H__
#define __ANGLE_H__

#include "ADC.H"

unsigned int adc_init_num = 0, adc_cita = 0;

void Weight_Init()
{
	// ------以下为AD初始化-----
	Adc_Init();
	IE |= 0xa0;         //开启AD中断
	ADC_CONTR = ADC_POWER | ADC_SPEEDHH | ADC_START | ch;
	Delay_10ms(10);
	adc_init_num = vin_channle[ch];
	// ------以上为AD初始化----
}

void Weight()
{
	uchar i, j;
	unsigned long int vin_tmp;
	for (j = 0; j < 100; j ++)
	{
		for ( i = 0; i < 100; i ++ )
		{
			GetADCResult();
			vin_channle[ ch ] = vin_channle[ ch ] + vin_temp; 
		}
		vin_channle[ ch ] = vin_channle[ ch ] / 100;
		vin_tmp = vin_tmp +	vin_channle[ ch ];
	} 
	vin_tmp = vin_tmp / 100;	
	adc_cita = vin_tmp * 5;			  
}


void Change()
{
	if (adc_cita < 250)
	{}
	else if (adc_cita < 300)
	{
		adc_cita = adc_cita - 40;
	}
	else if (adc_cita < 600)
	{
		adc_cita = adc_cita - 100;
	}
	else if (adc_cita < 700)
	{
		adc_cita = adc_cita - 150;
	}
	else
	{
		adc_cita = adc_cita - 200;
	}
}	
	
#endif
