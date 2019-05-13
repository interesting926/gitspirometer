#ifndef __UART_H__
#define __UART_H__

#define FOSC 11059200L                            
#define BAUD 9600

#define uchar unsigned char 
#define uint unsigned int

void Uart_Init(void)
{
	EA = 1;
	TMOD &= 0x0F;		//��ʼ����ʱ��T1
	TMOD |= 0x20;		//��ʱ��T1�����ڷ�ʽ2�����Զ���װ��ֵ������ʱ״̬��TR1���� 
	TH1 = TL1 = -(FOSC/12/32/BAUD);                    //Set Uart baudrate 
	ET1 = 0;		//T1���������ʷ���������ֹT1�ж� 
	TR1 = 1;		//������ʱ��T1 
	SCON = 0xc0;		//��ʽ3
	PCON &= 0x7F;		//�����ʲ����� 
	ES = 1;
	REN = 1;
}
/*
void Uart_Init_9600_12M(void)
{
	EA = 1;
	TMOD &= 0x0F;		//��ʼ����ʱ��T1
	TMOD |= 0x20;		//��ʱ��T1�����ڷ�ʽ2�����Զ���װ��ֵ������ʱ״̬��TR1���� 
	TL1 = TH1 = 0xfe;	//������Ϊ��9600@ 12
	ET1 = 0;		//T1���������ʷ���������ֹT1�ж� 
	TR1 = 1;		//������ʱ��T1 
	SCON = 0xc0;		//��ʽ3
	PCON &= 0x7F;		//�����ʲ����� 
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

void UART_Interrupt(void) interrupt 4   //�����ж�
{
	
	Uart_Send( Uart_Receive() );
}

#endif