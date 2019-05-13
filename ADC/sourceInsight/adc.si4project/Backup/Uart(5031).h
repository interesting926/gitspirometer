#ifndef UART_H
#define UART_H


extern uint8_t UartRbuf[255];
extern uint8_t rlen;

void Init_USART1(void);
void Uart1_Send(uint8_t dat);

#endif