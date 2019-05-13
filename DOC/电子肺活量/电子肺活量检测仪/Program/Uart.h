#ifndef __UART_H__
#define __UART_H__

#define FOSC 11059200L                            
#define BAUD 9600

#define uchar unsigned char 
#define uint unsigned int

void Uart_Init(void)
{
	EA = 1;
	TMOD &= 0x0F;		//初始化定时器T1
	TMOD |= 0x20;		//定时器T1工作在方式2（即自动重装初值），定时状态由TR1控制 
	TH1 = TL1 = -(FOSC/12/32/BAUD);                    //Set Uart baudrate 
	ET1 = 0;		//T1用作波特率发生器，禁止T1中断 
	TR1 = 1;		//启动定时器T1 
	SCON = 0xc0;		//方式3
	PCON &= 0x7F;		//波特率不倍增 
	ES = 1;
	REN = 1;
}
/*
void Uart_Init_9600_12M(void)
{
	EA = 1;
	TMOD &= 0x0F;		//初始化定时器T1
	TMOD |= 0x20;		//定时器T1工作在方式2（即自动重装初值），定时状态由TR1控制 
	TL1 = TH1 = 0xfe;	//波特率为：9600@ 12
	ET1 = 0;		//T1用作波特率发生器，禁止T1中断 
	TR1 = 1;		//启动定时器T1 
	SCON = 0xc0;		//方式3
	PCON &= 0x7F;		//波特率不倍增 
	ES = 1;
	REN = 1;
}

*/


uchar Uart_Receive(void)
{
	ES = 0;

	while(!RI);
	RI = 0;
	ACC = SBUF;
	ES = 1;
	return(ACC);
}



void Uart_Send(uchar Serial_data)
{
	ES = 0; 		  

	TI = 0;
	SBUF = Serial_data;
	while(!TI);
	TI = 0;
	
	ES = 1;
}

void UART_Interrupt(void) interrupt 4   //串口中断
{
	
	Uart_Send( Uart_Receive() );
}

#endif