#ifndef _GLOBAL_h_
#define _GLOBAL_h_

//#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char 
#define uint unsigned int

#define TRUE  1
#define FALSE 0

#define ON  1
#define OFF 0

#ifndef BIT
#define BIT(x)	(1 << (x))
#endif


void delay2s(void)   //Îó²î 0us
{
    unsigned char a,b,c,n;
    for(c=165;c>0;c--)
        for(b=218;b>0;b--)
            for(a=207;a>0;a--);
    for(n=8;n>0;n--);
    _nop_();  //if Keil,require use intrins.h
}


void delay850ms(void)   //Îó²î -0.000000000047us
{
    unsigned char a,b,c,n;
    for(c=205;c>0;c--)
        for(b=199;b>0;b--)
            for(a=61;a>0;a--);
    for(n=3;n>0;n--);
    _nop_();  //if Keil,require use intrins.h
}

void delay650ms(void)   //Îó²î -0.000000000036us
{
    unsigned char a,b,c;
    for(c=79;c>0;c--)
        for(b=172;b>0;b--)
            for(a=142;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
    _nop_();  //if Keil,require use intrins.h
}


void delay450ms(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=254;c>0;c--)
        for(b=96;b>0;b--)
            for(a=60;a>0;a--);
}


void delay100us(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=66;b>0;b--)
        for(a=3;a>0;a--);
}


void delay2ms(void)   //Îó²î 0.000000000000us
{
    unsigned char a,b,c;
    for(c=3;c>0;c--)
        for(b=235;b>0;b--)
            for(a=7;a>0;a--);
}


void Delay_10ms(unsigned int i)   //Îó²î -0.000000000001us
{
    unsigned char a,b;
	for (;i>0;i--)
		for(b=194;b>0;b--)
			for(a=141;a>0;a--);
}

void Delay_1ms(unsigned int i)    //Îó²î -0.018084490741us
{
    unsigned char a,b;
	for (;i>0;i--){
		for(b=21;b>0;b--)
			for(a=130;a>0;a--);
		_nop_();  //if Keil,require use intrins.h
	}
}
/*
void Delay_100us(unsigned int i)    //Îó²î -0.083188657407us
{
    unsigned char a,b;
	for (;i>0;i--){
		for(b=78;b>0;b--)
			for(a=2;a>0;a--);
		_nop_();  //if Keil,require use intrins.h
	}
		
}

void Delay_10us(unsigned int i)    //Îó²î -0.053530092593us
{
    unsigned char a,b;
	for (;i>0;i--)
		for(b=7;b>0;b--)
			for(a=2;a>0;a--);
}
*/

#endif