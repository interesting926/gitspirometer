

#include "STC12C5A60S2.H"
#include "global.h"
#include "LCD1602.h"
#include "WTV020_SD.h"
#include "ADC.H"
#include "Transform.H"
#include "KeyScan.H"



void  Main(void) 
{		
//	uchar temp_a, temp_b, temp_c, temp_d;
	uchar i;
	P0M0 = 0x03;
	P0M1 = 0x03;
	LCD1602Init();
	
	Transform_Init();	 
	 	
	led = 1;
	DisplayListChar(0, 0, " Welcome to Use ");
	DisplayListChar(0, 1, "   VC  Tester   ");
	for (i = 0; i < 102; i ++)
	{
		Save[i] = 0;
	}
	delay2s();
	WTV020_SPI(0, 0x20);
	

	while (1)
	{
		Key_Scan();
	}
}

