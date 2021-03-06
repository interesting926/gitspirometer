#include "stdio.h"
#include "stm8l15x.h"
#include "Uart.h"
#include "stm8l15x_syscfg.h"
#include "stm8l15x.h"






uint8_t UartRbuf[255];
uint8_t UartRlen;



void Init_USART1(void)
{ 
  //重新映射
  SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortC,ENABLE);
    /* Enable USART clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
    
  /* Configure USART Tx as alternate function push-pull  (software pull up)*/
  GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_2,ENABLE);

  /* Configure USART Rx as alternate function push-pull  (software pull up)*/
  GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_3,ENABLE);
  /* USART configuration */
  USART_Init(USART1, (u32)9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,(USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));

   //以下2个函数是配置接收中断
  /* Enable the USART Receive interrupt: this interrupt is generated when the
    USART receive data register is not empty */
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

  /* Select the USART WakeUp Method */
  //USART_WakeUpConfig(USART1, USART_WakeUp_AddressMark);


  USART_Cmd(USART1, ENABLE);

  enableInterrupts();
}


void Uart1_Send(uint8_t dat)
{
  
  /* Write a character to the USART */
  USART_SendData8(USART1, dat);
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
	
}



//////////////////////////printf//////////////////////////////

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE //发送一个字符协议
{
/* 将Printf内容发往串口 */
  //UART1_SendData8((unsigned char) ch);
  USART_SendData8(USART1,(unsigned char) ch);
  while (!(USART1->SR & USART_FLAG_TXE));//如果发送未完成， //标志位未置位，则循环等待
  return (ch);

}










