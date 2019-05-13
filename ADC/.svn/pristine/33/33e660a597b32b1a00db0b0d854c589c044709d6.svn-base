#include "IIC.h"
#include "stm8l15x_syscfg.h"
#include "stm8l15x_i2c.h"



__IO uint8_t Slave_Buffer_Rx[255];
__IO uint8_t Tx_Idx=0 , Rx_Idx=0 ;
__IO uint16_t Event=0x00 ;
__IO uint8_t IICOverFlag=0;



//IIC从机地址的最后一个bit是读写控制位，只有高7位是地址
#define IIC_SLAVE_ADDRESS 0x74
#define IIC_SLAVE_SPEED 100000UL

void Init_IIC(void)
{

  GPIO_Init(GPIOC, GPIO_Pin_0,GPIO_Mode_In_FL_No_IT  );

  GPIO_Init(GPIOC, GPIO_Pin_1,GPIO_Mode_In_FL_No_IT  );
  
  CLK_PeripheralClockConfig(CLK_Peripheral_I2C1, ENABLE);  
  
  I2C_DeInit(I2C1);
  
  I2C_Init(I2C1, IIC_SLAVE_SPEED, IIC_SLAVE_ADDRESS,
           I2C_Mode_SMBusDevice , I2C_DutyCycle_2,
           I2C_Ack_Enable , I2C_AcknowledgedAddress_7bit);
  
  
  I2C_AcknowledgeConfig(I2C1, ENABLE);


  /* Enable Error Interrupt*/
  I2C_ITConfig(I2C1, (I2C_IT_TypeDef)(I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF |I2C_IT_RXNE ), ENABLE);
  
  I2C_Cmd(I2C1, ENABLE);

  /* Enable general interrupts */
  enableInterrupts();

}




