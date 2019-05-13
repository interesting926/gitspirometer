#ifndef __ADC_H__
#define __ADC_H__


/*Define ADC operation const for ADC_CONTR*/ 
#define ADC_POWER                   0x80                                             //ADC power control bit 
#define ADC_FLAG                    0x10                                             //ADC complete flag 
#define ADC_START                   0x08                                             //ADC start control bit 
#define ADC_SPEEDLL                 0x00                                             //540 clocks 
#define ADC_SPEEDL                  0x20                                             //360 clocks 
#define ADC_SPEEDH                  0x40                                             //180 clocks 
#define ADC_SPEEDHH					0x60                                             //90 clocks 
//#define ADC_VCC                     4950.0                                           //VCC 电压

unsigned long int  vin_temp = 0;

uchar ch = 0;                         //ADC channel NO. 

unsigned long int vin_channle[1];                  //AD采集后存放的数据
// ---------------------------- 
// AD中断程序
// ----------------------------
void GetADCResult()
{
	ADC_CONTR = ADC_POWER | ADC_SPEEDHH | ADC_START | ch;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	while ( ! ( ADC_CONTR & ADC_FLAG ) );
	ADC_CONTR &=~ ADC_FLAG;
	vin_temp = ( ADC_RES << 2 ) | ADC_RESL; 	
}

void Adc_Init( ) 
{ 
	P1ASF = 0x01;                           //开启P1口所有AD通道 
	ADC_RES = 0;                            //清空结果
	ADC_CONTR = ADC_POWER | ADC_SPEEDHH | ADC_START | ch; 
	Delay_1ms(2);
} 

#endif