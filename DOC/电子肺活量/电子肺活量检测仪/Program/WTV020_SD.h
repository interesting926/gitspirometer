#include<stdio.h>
#include<intrins.h>
#define uchar unsigned char
#define uint  unsigned int
sbit clk1= P0^1;
sbit sda1= P0^0;

uchar addr;

void WTV020_SPI(uchar addr,uchar adde)	  //2线发地址和数据的程序
{
	uchar i;
	clk1 = 0;
	delay2ms();
	for (i = 0; i < 8; i ++)
	{
		clk1 = 0;
		sda1 = addr & 0x80;
		delay100us();
		clk1 = 1;
		delay100us();
		addr <<= 1;
	}
	clk1 = 0;
	for (i = 0; i < 8; i ++)
	{
		clk1 = 0;
		sda1 = adde & 0x80;
		delay100us();
		clk1 = 1;
		delay100us();
		adde <<= 1;
	}
	clk1 = 1;
	sda1 = 1;
}