/**
  ********************************************************************************
  * @file    stm8s_USART1.c
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   This file contains all the functions for the USART1 peripheral.
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_usart.h"

/** @addtogroup STM8S_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/** @}
  * @addtogroup USART1_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the UART peripheral.
  * @param  None
  * @retval None
	*/
void USART1_DeInit(void)
{
  /* Clear the Idle Line Detected bit in the status register by a read
  to the USART1_SR register followed by a Read to the USART1_DR register */
  (void)USART1->SR;
  (void)USART1->DR;
  
  USART1->BRR2 = USART1_BRR2_RESET_VALUE;  /* Set USART1_BRR2 to reset value 0x00 */
  USART1->BRR1 = USART1_BRR1_RESET_VALUE;  /* Set USART1_BRR1 to reset value 0x00 */
  
  USART1->CR1 = USART1_CR1_RESET_VALUE;  /* Set USART1_CR1 to reset value 0x00 */
  USART1->CR2 = USART1_CR2_RESET_VALUE;  /* Set USART1_CR2 to reset value 0x00 */
  USART1->CR3 = USART1_CR3_RESET_VALUE;  /* Set USART1_CR3 to reset value 0x00 */
  USART1->CR4 = USART1_CR4_RESET_VALUE;  /* Set USART1_CR4 to reset value 0x00 */
  USART1->CR5 = USART1_CR5_RESET_VALUE;  /* Set USART1_CR5 to reset value 0x00 */
  
  USART1->GTR = USART1_GTR_RESET_VALUE;
  USART1->PSCR = USART1_PSCR_RESET_VALUE;
}

/**
  * @brief  Initializes the USART1 according to the specified parameters.
  * @note   Configure in Push Pull or Open Drain mode the Tx pin by setting the
  *         correct I/O Port register according the product package and line
  *         configuration
  * @param  BaudRate: The baudrate.
  * @param  WordLength : This parameter can be any of the 
  *         @ref USART1_WordLength_TypeDef enumeration.
  * @param  StopBits: This parameter can be any of the 
  *         @ref USART1_StopBits_TypeDef enumeration.
  * @param  Parity: This parameter can be any of the 
  *         @ref USART1_Parity_TypeDef enumeration.
  * @param  SyncMode: This parameter can be any of the 
  *         @ref USART1_SyncMode_TypeDef values.
  * @param  Mode: This parameter can be any of the @ref USART1_Mode_TypeDef values
  * @retval None
  */
void USART1_Init(uint32_t BaudRate, USART1_WordLength_TypeDef WordLength, 
                USART1_StopBits_TypeDef StopBits, USART1_Parity_TypeDef Parity, 
                USART1_SyncMode_TypeDef SyncMode, USART1_Mode_TypeDef Mode)
{
  uint32_t BaudRate_Mantissa = 0, BaudRate_Mantissa100 = 0;
  
  /* Check the parameters */
  assert_param(IS_USART1_BAUDRATE_OK(BaudRate));
  assert_param(IS_USART1_WORDLENGTH_OK(WordLength));
  assert_param(IS_USART1_STOPBITS_OK(StopBits));
  assert_param(IS_USART1_PARITY_OK(Parity));
  assert_param(IS_USART1_MODE_OK((uint8_t)Mode));
  assert_param(IS_USART1_SYNCMODE_OK((uint8_t)SyncMode));
  
  /* Clear the word length bit */
  USART1->CR1 &= (uint8_t)(~USART1_CR1_M);  
  
  /* Set the word length bit according to USART1_WordLength value */
  USART1->CR1 |= (uint8_t)WordLength;
  
  /* Clear the STOP bits */
  USART1->CR3 &= (uint8_t)(~USART1_CR3_STOP);  
  /* Set the STOP bits number according to USART1_StopBits value  */
  USART1->CR3 |= (uint8_t)StopBits;  
  
  /* Clear the Parity Control bit */
  USART1->CR1 &= (uint8_t)(~(USART1_CR1_PCEN | USART1_CR1_PS  ));  
  /* Set the Parity Control bit to USART1_Parity value */
  USART1->CR1 |= (uint8_t)Parity;  
  
  /* Clear the LSB mantissa of USART1DIV  */
  USART1->BRR1 &= (uint8_t)(~USART1_BRR1_DIVM);  
  /* Clear the MSB mantissa of USART1DIV  */
  USART1->BRR2 &= (uint8_t)(~USART1_BRR2_DIVM);  
  /* Clear the Fraction bits of USART1DIV */
  USART1->BRR2 &= (uint8_t)(~USART1_BRR2_DIVF);  
  
  /* Set the USART1 BaudRates in BRR1 and BRR2 registers according to USART1_BaudRate value */
  BaudRate_Mantissa    = ((uint32_t)CLK_GetClockFreq() / (BaudRate << 4));
  BaudRate_Mantissa100 = (((uint32_t)CLK_GetClockFreq() * 100) / (BaudRate << 4));
  /* Set the fraction of USART1DIV  */
  USART1->BRR2 |= (uint8_t)((uint8_t)(((BaudRate_Mantissa100 - (BaudRate_Mantissa * 100)) << 4) / 100) & (uint8_t)0x0F); 
  /* Set the MSB mantissa of USART1DIV  */
  USART1->BRR2 |= (uint8_t)((BaudRate_Mantissa >> 4) & (uint8_t)0xF0); 
  /* Set the LSB mantissa of USART1DIV  */
  USART1->BRR1 |= (uint8_t)BaudRate_Mantissa;           
  
  /* Disable the Transmitter and Receiver before setting the LBCL, CPOL and CPHA bits */
  USART1->CR2 &= (uint8_t)~(USART1_CR2_TEN | USART1_CR2_REN); 
  /* Clear the Clock Polarity, lock Phase, Last Bit Clock pulse */
  USART1->CR3 &= (uint8_t)~(USART1_CR3_CPOL | USART1_CR3_CPHA | USART1_CR3_LBCL); 
  /* Set the Clock Polarity, lock Phase, Last Bit Clock pulse */
  USART1->CR3 |= (uint8_t)((uint8_t)SyncMode & (uint8_t)(USART1_CR3_CPOL | 
                                                        USART1_CR3_CPHA | USART1_CR3_LBCL));  
  
  if ((uint8_t)(Mode & USART1_MODE_TX_ENABLE))
  {
    /* Set the Transmitter Enable bit */
    USART1->CR2 |= (uint8_t)USART1_CR2_TEN;  
  }
  else
  {
    /* Clear the Transmitter Disable bit */
    USART1->CR2 &= (uint8_t)(~USART1_CR2_TEN);  
  }
  if ((uint8_t)(Mode & USART1_MODE_RX_ENABLE))
  {
    /* Set the Receiver Enable bit */
    USART1->CR2 |= (uint8_t)USART1_CR2_REN;  
  }
  else
  {
    /* Clear the Receiver Disable bit */
    USART1->CR2 &= (uint8_t)(~USART1_CR2_REN);  
  }
  /* Set the Clock Enable bit, lock Polarity, lock Phase and Last Bit Clock 
  pulse bits according to USART1_Mode value */
  if ((uint8_t)(SyncMode & USART1_SYNCMODE_CLOCK_DISABLE))
  {
    /* Clear the Clock Enable bit */
    USART1->CR3 &= (uint8_t)(~USART1_CR3_CKEN); 
  }
  else
  {
    USART1->CR3 |= (uint8_t)((uint8_t)SyncMode & USART1_CR3_CKEN);
  }
}

/**
  * @brief  Enable the USART1 peripheral.
  * @param  NewState : The new state of the UART Communication.
  *         This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void USART1_Cmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* USART1 Enable */
    USART1->CR1 &= (uint8_t)(~USART1_CR1_UARTD); 
  }
  else
  {
    /* UART Disable */
    USART1->CR1 |= USART1_CR1_UARTD;  
  }
}

/**
  * @brief  Enables or disables the specified USART interrupts.
  * @param  USART1_IT specifies the USART interrupt sources to be enabled or disabled.
  *         This parameter can be one of the following values:
  *         - USART1_IT_TXE:  Transmit Data Register empty interrupt
  *         - USART1_IT_TC:   Transmission complete interrupt
  *         - USART1_IT_RXNE_OR: Receive Data register not empty and Overrun interrupt
  *         - USART1_IT_IDLE: Idle line detection interrupt
  *         - USRT1_IT_ERR:  Error interrupt
  * @param  NewState new state of the specified USART interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART1_ITConfig(USART1_IT_TypeDef USART1_IT, FunctionalState NewState)
{
  uint8_t uartreg = 0, itpos = 0x00;
  
  /* Check the parameters */
  assert_param(IS_USART1_CONFIG_IT_OK(USART1_IT));
  assert_param(IS_FUNCTIONALSTATE_OK(NewState));
  
  /* Get the USART1 register index */
  uartreg = (uint8_t)((uint16_t)USART1_IT >> 0x08);
  /* Get the USART1 IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)USART1_IT & (uint8_t)0x0F));
  
  if (NewState != DISABLE)
  {
    /**< Enable the Interrupt bits according to USART1_IT mask */
    if (uartreg == 0x01)
    {
      USART1->CR1 |= itpos;
    }
    else if (uartreg == 0x02)
    {
      USART1->CR2 |= itpos;
    }
    else
    {
      USART1->CR4 |= itpos;
    }
  }
  else
  {
    /**< Disable the interrupt bits according to USART1_IT mask */
    if (uartreg == 0x01)
    {
      USART1->CR1 &= (uint8_t)(~itpos);
    }
    else if (uartreg == 0x02)
    {
      USART1->CR2 &= (uint8_t)(~itpos);
    }
    else
    {
      USART1->CR4 &= (uint8_t)(~itpos);
    }
  }
  
}

/**
  * @brief  Enables or disables the UART’s Half Duplex communication.
  * @param  NewState new state of the UART Communication.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART1_HalfDuplexCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONALSTATE_OK(NewState));
  
  if (NewState != DISABLE)
  {
    USART1->CR5 |= USART1_CR5_HDSEL;  /**< USART1 Half Duplex Enable  */
  }
  else
  {
    USART1->CR5 &= (uint8_t)~USART1_CR5_HDSEL; /**< USART1 Half Duplex Disable */
  }
}

/**
  * @brief  Configures the UART’s IrDA interface.
  * @param  USART1_IrDAMode specifies the IrDA mode.
  *         This parameter can be any of the @ref USART1_IrDAMode_TypeDef values.
  * @retval None
  */
void USART1_IrDAConfig(USART1_IrDAMode_TypeDef USART1_IrDAMode)
{
  assert_param(IS_USART1_IRDAMODE_OK(USART1_IrDAMode));
  
  if (USART1_IrDAMode != USART1_IRDAMODE_NORMAL)
  {
    USART1->CR5 |= USART1_CR5_IRLP;
  }
  else
  {
    USART1->CR5 &= ((uint8_t)~USART1_CR5_IRLP);
  }
}

/**
  * @brief  Enables or disables the UART’s IrDA interface.
  * @param  NewState new state of the IrDA mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART1_IrDACmd(FunctionalState NewState)
{
  /* Check parameters */
  assert_param(IS_FUNCTIONALSTATE_OK(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the IrDA mode by setting the IREN bit in the CR3 register */
    USART1->CR5 |= USART1_CR5_IREN;
  }
  else
  {
    /* Disable the IrDA mode by clearing the IREN bit in the CR3 register */
    USART1->CR5 &= ((uint8_t)~USART1_CR5_IREN);
  }
}

/**
  * @brief  Sets the USART1 LIN Break detection length.
  * @param  USART1_LINBreakDetectionLength specifies the LIN break detection length.
  *         This parameter can be any of the
  *         @ref USART1_LINBreakDetectionLength_TypeDef values.
  * @retval None
  */
void USART1_LINBreakDetectionConfig(USART1_LINBreakDetectionLength_TypeDef USART1_LINBreakDetectionLength)
{
  assert_param(IS_USART1_LINBREAKDETECTIONLENGTH_OK(USART1_LINBreakDetectionLength));
  
  if (USART1_LINBreakDetectionLength != USART1_LINBREAKDETECTIONLENGTH_10BITS)
  {
    USART1->CR4 |= USART1_CR4_LBDL;
  }
  else
  {
    USART1->CR4 &= ((uint8_t)~USART1_CR4_LBDL);
  }
}

/**
  * @brief  Enables or disables the USART1’s LIN mode.
  * @param  NewState is new state of the USART1 LIN mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART1_LINCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONALSTATE_OK(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the LIN mode by setting the LINE bit in the CR2 register */
    USART1->CR3 |= USART1_CR3_LINEN;
  }
  else
  {
    /* Disable the LIN mode by clearing the LINE bit in the CR2 register */
    USART1->CR3 &= ((uint8_t)~USART1_CR3_LINEN);
  }
}

/**
  * @brief  Enables or disables the USART1 Smart Card mode.
  * @param  NewState: new state of the Smart Card mode.
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART1_SmartCardCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONALSTATE_OK(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the SC mode by setting the SCEN bit in the CR5 register */
    USART1->CR5 |= USART1_CR5_SCEN;
  }
  else
  {
    /* Disable the SC mode by clearing the SCEN bit in the CR5 register */
    USART1->CR5 &= ((uint8_t)(~USART1_CR5_SCEN));
  }
}

/**
  * @brief  Enables or disables NACK transmission.
  * @note   This function is valid only for USART1 because is related to SmartCard mode.
  * @param  NewState: new state of the Smart Card mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART1_SmartCardNACKCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONALSTATE_OK(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the NACK transmission by setting the NACK bit in the CR5 register */
    USART1->CR5 |= USART1_CR5_NACK;
  }
  else
  {
    /* Disable the NACK transmission by clearing the NACK bit in the CR5 register */
    USART1->CR5 &= ((uint8_t)~(USART1_CR5_NACK));
  }
}

/**
  * @brief  Selects the USART1 WakeUp method.
  * @param  USART1_WakeUp: specifies the USART1 wakeup method.
  *         This parameter can be any of the @ref USART1_WakeUp_TypeDef values.
  * @retval None
  */
void USART1_WakeUpConfig(USART1_WakeUp_TypeDef USART1_WakeUp)
{
  assert_param(IS_USART1_WAKEUP_OK(USART1_WakeUp));
  
  USART1->CR1 &= ((uint8_t)~USART1_CR1_WAKE);
  USART1->CR1 |= (uint8_t)USART1_WakeUp;
}

/**
  * @brief  Determines if the USART1 is in mute mode or not.
  * @param  NewState: new state of the USART1 mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART1_ReceiverWakeUpCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONALSTATE_OK(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the mute mode USART1 by setting the RWU bit in the CR2 register */
    USART1->CR2 |= USART1_CR2_RWU;
  }
  else
  {
    /* Disable the mute mode USART1 by clearing the RWU bit in the CR1 register */
    USART1->CR2 &= ((uint8_t)~USART1_CR2_RWU);
  }
}

/**
  * @brief  Returns the most recent received data by the USART1 peripheral.
  * @param  None
  * @retval The received data.
  */
uint8_t USART1_ReceiveData8(void)
{
  return ((uint8_t)USART1->DR);
}

/**
  * @brief  Returns the most recent received data by the USART1 peripheral.
  * @param  None
  * @retval The received data.
  */
uint16_t USART1_ReceiveData9(void)
{
  uint16_t temp = 0;
  
  temp = (uint16_t)(((uint16_t)( (uint16_t)USART1->CR1 & (uint16_t)USART1_CR1_R8)) << 1);
  return (uint16_t)( (((uint16_t) USART1->DR) | temp ) & ((uint16_t)0x01FF));
}

/**
  * @brief  Transmits 8 bit data through the USART1 peripheral.
  * @param  Data: The data to transmit.
  * @retval None
  */
void USART1_SendData8(uint8_t Data)
{
  /* Transmit Data */
  USART1->DR = Data;
}

/**
  * @brief  Transmits 9 bit data through the UART peripheral.
  * @param  Data : The data to transmit.
  *         This parameter should be lower than 0x1FF.
  * @retval None
  */
void USART1_SendData9(uint16_t Data)
{
  /**< Clear the transmit data bit 8 [8]  */
  USART1->CR1 &= ((uint8_t)~USART1_CR1_T8);
  /**< Write the transmit data bit [8]  */
  USART1->CR1 |= (uint8_t)(((uint8_t)(Data >> 2)) & USART1_CR1_T8);
  /**< Write the transmit data bit [0:7] */
  USART1->DR   = (uint8_t)(Data);
}

/**
  * @brief  Transmits break characters.
  * @param  None
  * @retval None
  */
void USART1_SendBreak(void)
{
  USART1->CR2 |= USART1_CR2_SBK;
}

/**
  * @brief  Sets the address of the USART1 node.
  * @param  USART1_Address: Indicates the address of the USART1 node.
  * @retval None
  */
void USART1_SetAddress(uint8_t USART1_Address)
{
  /*assert_param for USART1_Address*/
  assert_param(IS_USART1_ADDRESS_OK(USART1_Address));
  
  /* Clear the USART1 address */
  USART1->CR4 &= ((uint8_t)~USART1_CR4_ADD);
  /* Set the USART1 address node */
  USART1->CR4 |= USART1_Address;
}

/**
  * @brief  Sets the specified UART guard time.
  * @note   SmartCard Mode should be Enabled
  * @param  USART1_GuardTime: specifies the guard time.
  * @retval None
  */
void USART1_SetGuardTime(uint8_t USART1_GuardTime)
{
  /* Set the USART1 guard time */
  USART1->GTR = USART1_GuardTime;
}

/**
  * @brief  Sets the system clock prescaler.
  * @note   IrDA Low Power mode or smartcard mode should be enabled
  * @note   This function is related to SmartCard and IrDa mode.
  * @param  USART1_Prescaler: specifies the prescaler clock.
  *         This parameter can be one of the following values:
  *         @par IrDA Low Power Mode
  *         The clock source is divided by the value given in the register (8 bits)
  *         - 0000 0000 Reserved
  *         - 0000 0001 divides the clock source by 1
  *         - 0000 0010 divides the clock source by 2
  *         - ...
  *        @par Smart Card Mode
  *        The clock source is divided by the value given in the register
  *        (5 significant bits) multiplied by 2
  *         - 0 0000 Reserved
  *         - 0 0001 divides the clock source by 2
  *         - 0 0010 divides the clock source by 4
  *         - 0 0011 divides the clock source by 6
  *         - ...
  * @retval None
  */
void USART1_SetPrescaler(uint8_t USART1_Prescaler)
{
  /* Load the USART1 prescaler value*/
  USART1->PSCR = USART1_Prescaler;
}

/**
  * @brief  Checks whether the specified USART1 flag is set or not.
  * @param  USART1_FLAG specifies the flag to check.
  *         This parameter can be any of the @ref USART1_Flag_TypeDef enumeration.
  * @retval FlagStatus (SET or RESET)
  */
FlagStatus USART1_GetFlagStatus(USART1_Flag_TypeDef USART1_FLAG)
{
  FlagStatus status = RESET;
  
  /* Check parameters */
  assert_param(IS_USART1_FLAG_OK(USART1_FLAG));
  
  
  /* Check the status of the specified USART1 flag*/
  if (USART1_FLAG == USART1_FLAG_LBDF)
  {
    if ((USART1->CR4 & (uint8_t)USART1_FLAG) != (uint8_t)0x00)
    {
      /* USART1_FLAG is set*/
      status = SET;
    }
    else
    {
      /* USART1_FLAG is reset*/
      status = RESET;
    }
  }
  else if (USART1_FLAG == USART1_FLAG_SBK)
  {
    if ((USART1->CR2 & (uint8_t)USART1_FLAG) != (uint8_t)0x00)
    {
      /* USART1_FLAG is set*/
      status = SET;
    }
    else
    {
      /* USART1_FLAG is reset*/
      status = RESET;
    }
  }
  else
  {
    if ((USART1->SR & (uint8_t)USART1_FLAG) != (uint8_t)0x00)
    {
      /* USART1_FLAG is set*/
      status = SET;
    }
    else
    {
      /* USART1_FLAG is reset*/
      status = RESET;
    }
  }
  /* Return the USART1_FLAG status*/
  return status;
}

/**
  * @brief  Clears the USART1 flags.
  * @param  USART1_FLAG specifies the flag to clear
  *         This parameter can be any combination of the following values:
  *         - USART1_FLAG_LBDF: LIN Break detection flag.
  *         - USART1_FLAG_RXNE: Receive data register not empty flag.
  * @note
  *         - PE (Parity error), FE (Framing error), NE (Noise error), 
  *         OR (OverRun error) and IDLE (Idle line detected) flags are 
  *         cleared by software sequence: a read operation to USART1_SR register
  *         (USART1_GetFlagStatus())followed by a read operation to USART1_DR 
  *         register(USART1_ReceiveData8() or USART1_ReceiveData9()).
  *           
  *         - RXNE flag can be also cleared by a read to the USART1_DR register
  *         (USART1_ReceiveData8()or USART1_ReceiveData9()).
  *           
  *         - TC flag can be also cleared by software sequence: a read operation
  *         to USART1_SR register (USART1_GetFlagStatus()) followed by a write 
  *         operation to USART1_DR register (USART1_SendData8() or USART1_SendData9()).
  *           
  *         - TXE flag is cleared only by a write to the USART1_DR register 
  *         (USART1_SendData8() or USART1_SendData9()).
  *           
  *         - SBK flag is cleared during the stop bit of break.
  * @retval None
  */
void USART1_ClearFlag(USART1_Flag_TypeDef USART1_FLAG)
{
  assert_param(IS_USART1_CLEAR_FLAG_OK(USART1_FLAG));
  
  /* Clear the Receive Register Not Empty flag */
  if (USART1_FLAG == USART1_FLAG_RXNE)
  {
    USART1->SR = (uint8_t)~(USART1_SR_RXNE);
  }
  /* Clear the LIN Break Detection flag */
  else
  {
    USART1->CR4 &= (uint8_t)~(USART1_CR4_LBDF);
  }
}

/**
  * @brief  Checks whether the specified USART1 interrupt has occurred or not.
  * @param  USART1_IT: Specifies the USART1 interrupt pending bit to check.
  *         This parameter can be one of the following values:
  *         - USART1_IT_LBDF:  LIN Break detection interrupt
  *         - USART1_IT_TXE:  Transmit Data Register empty interrupt
  *         - USART1_IT_TC:   Transmission complete interrupt
  *         - USART1_IT_RXNE: Receive Data register not empty interrupt
  *         - USART1_IT_IDLE: Idle line detection interrupt
  *         - USART1_IT_OR:  OverRun Error interrupt
  *         - USART1_IT_PE:   Parity Error interrupt
  * @retval The new state of USART1_IT (SET or RESET).
  */
ITStatus USART1_GetITStatus(USART1_IT_TypeDef USART1_IT)
{
  ITStatus pendingbitstatus = RESET;
  uint8_t itpos = 0;
  uint8_t itmask1 = 0;
  uint8_t itmask2 = 0;
  uint8_t enablestatus = 0;
  
  /* Check parameters */
  assert_param(IS_USART1_GET_IT_OK(USART1_IT));
  
  /* Get the USART1 IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)USART1_IT & (uint8_t)0x0F));
  /* Get the USART1 IT index */
  itmask1 = (uint8_t)((uint8_t)USART1_IT >> (uint8_t)4);
  /* Set the IT mask*/
  itmask2 = (uint8_t)((uint8_t)1 << itmask1);
  
  
  /* Check the status of the specified USART1 pending bit*/
  if (USART1_IT == USART1_IT_PE)
  {
    /* Get the USART1_IT enable bit status*/
    enablestatus = (uint8_t)((uint8_t)USART1->CR1 & itmask2);
    /* Check the status of the specified USART1 interrupt*/
    
    if (((USART1->SR & itpos) != (uint8_t)0x00) && enablestatus)
    {
      /* Interrupt occurred*/
      pendingbitstatus = SET;
    }
    else
    {
      /* Interrupt not occurred*/
      pendingbitstatus = RESET;
    }
  }
  
  else if (USART1_IT == USART1_IT_LBDF)
  {
    /* Get the USART1_IT enable bit status*/
    enablestatus = (uint8_t)((uint8_t)USART1->CR4 & itmask2);
    /* Check the status of the specified USART1 interrupt*/
    if (((USART1->CR4 & itpos) != (uint8_t)0x00) && enablestatus)
    {
      /* Interrupt occurred*/
      pendingbitstatus = SET;
    }
    else
    {
      /* Interrupt not occurred*/
      pendingbitstatus = RESET;
    }
  }
  else
  {
    /* Get the USART1_IT enable bit status*/
    enablestatus = (uint8_t)((uint8_t)USART1->CR2 & itmask2);
    /* Check the status of the specified USART1 interrupt*/
    if (((USART1->SR & itpos) != (uint8_t)0x00) && enablestatus)
    {
      /* Interrupt occurred*/
      pendingbitstatus = SET;
    }
    else
    {
      /* Interrupt not occurred*/
      pendingbitstatus = RESET;
    }
  }
  
  /* Return the USART1_IT status*/
  return  pendingbitstatus;
}

/**
  * @brief  Clears the USART1 pending flags.
  * @param  USART1_IT specifies the pending bit to clear
  *         This parameter can be one of the following values:
  *         - USART1_IT_LBDF:  LIN Break detection interrupt
  *         - USART1_IT_RXNE: Receive Data register not empty interrupt.
  * @note
  *         - PE (Parity error), FE (Framing error), NE (Noise error), 
  *           OR (OverRun error) and IDLE (Idle line detected) pending bits are 
  *           cleared by software sequence: a read operation to USART1_SR register
  *           (USART1_GetITStatus()) followed by a read operation to USART1_DR register
  *           (USART1_ReceiveData8() or USART1_ReceiveData9()).
  *   
  *         - RXNE pending bit can be also cleared by a read to the USART1_DR register
  *           (USART1_ReceiveData8() or USART1_ReceiveData9()).
  * 
  *         - TC (Transmit complete) pending bit can be cleared by software 
  *           sequence: a read operation to USART1_SR register (USART1_GetITStatus())
  *           followed by a write operation to USART1_DR register (USART1_SendData8()
  *           or USART1_SendData9()).
  *             
  *         - TXE pending bit is cleared only by a write to the USART1_DR register
  *           (USART1_SendData8() or USART1_SendData9()).
  * @retval None
  */
void USART1_ClearITPendingBit(USART1_IT_TypeDef USART1_IT)
{
  assert_param(IS_USART1_CLEAR_IT_OK(USART1_IT));
  
  /* Clear the Receive Register Not Empty pending bit */
  if (USART1_IT == USART1_IT_RXNE)
  {
    USART1->SR = (uint8_t)~(USART1_SR_RXNE);
  }
  /* Clear the LIN Break Detection pending bit */
  else
  {
    USART1->CR4 &= (uint8_t)~(USART1_CR4_LBDF);
  }
}

/**
  * @}
  */
  
/**
  * @}
  */
  

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
