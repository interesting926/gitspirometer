#include "stm8l15x.h"
#include "Uart.h"
#include "stm8l15x_syscfg.h"


uint8_t rbuf[255];
uint8_t rlen;



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



#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/


