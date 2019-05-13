/*
                文档说明
    本文档内容为一些通用的C语言函数，不涉及到底层

*/
#include "com.h"


static void delay1ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}



void delayms(int ms)
{
    int  i;
    for(i=0;i<ms;i++)
    {
        delay1ms();
    }
}



