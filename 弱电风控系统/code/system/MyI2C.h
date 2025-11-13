#ifndef __MyI2C_H
#define __MyI2C_H 

#define I2C_SCL_PIN GPIO_Pin_8
#define I2C_SDA_PIN GPIO_Pin_9
#define I2C_GPIO_PORT GPIOB
#define I2C_CLK RCC_APB2Periph_GPIOB 

void MyI2C_W_SCL( uint8_t BitValue);

void MyI2C_W_SDA( uint8_t BitValue);

uint8_t MyI2C_R_SDA( void );

void MyI2C_Init( void );

void MyI2C_Start(void);

void MyI2C_Stop(void);

void MyI2C_SendByte(uint8_t Byte);

uint8_t MyI2C_ReceiveByte(void);

uint8_t MyI2C_ReceiveAck( void );

void MyI2C_SendAck(uint8_t AckBit );


#endif


