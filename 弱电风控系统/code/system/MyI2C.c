#include "stm32f10x.h"
#include "delay.h"
#include "MyI2C.h"

	/*写SCL*/
void MyI2C_W_SCL( uint8_t BitValue)
{
	GPIO_WriteBit(I2C_GPIO_PORT,I2C_SCL_PIN,(BitAction)BitValue);
	Delay_us(10);
}
	/*写SDA*/
void MyI2C_W_SDA( uint8_t BitValue)
{
	GPIO_WriteBit(I2C_GPIO_PORT,I2C_SDA_PIN,(BitAction)BitValue);
	Delay_us(10);
}
	/*读SDA*/
uint8_t MyI2C_R_SDA( void )
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(I2C_GPIO_PORT,I2C_SDA_PIN);
	Delay_us(10);
	return BitValue;
}

void MyI2C_Init( void )
{
	RCC_APB2PeriphClockCmd(I2C_CLK,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN | I2C_SCL_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(I2C_GPIO_PORT ,&GPIO_InitStructure);
	GPIO_SetBits(I2C_GPIO_PORT, I2C_SDA_PIN | I2C_SCL_PIN );
	
}

void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
	
}

void MyI2C_Stop(void)
{
	
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for(i = 0; i < 8; i++)
	{
		MyI2C_W_SDA(Byte & (0x80 >> i));//在SCL低电平时设置数据
		MyI2C_W_SCL(1);					// 从机在SCL上升沿采样
		MyI2C_W_SCL(0);					// 准备下一位
	}
}


uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t i, Byte = 0x00;					//定义接收的数据，并赋初值0x00，此处必须赋初值0x00，后面会用到
	MyI2C_W_SDA(1);							//接收前，主机先确保释放SDA，避免干扰从机的数据发送
	for (i = 0; i < 8; i ++)				//循环8次，主机依次接收数据的每一位
	{
		MyI2C_W_SCL(1);						//释放SCL，主机机在SCL高电平期间读取SDA
		if (MyI2C_R_SDA() == 1){Byte |= (0x80 >> i);}	//读取SDA数据，并存储到Byte变量
														//当SDA为1时，置变量指定位为1，当SDA为0时，不做处理，指定位为默认的初值0
		MyI2C_W_SCL(0);						//拉低SCL，从机在SCL低电平期间写入SDA
	}
	return Byte;							//返回接收到的一个字节数据
}


	/*接收应答，0表示应答成功，1表示应答失败*/
uint8_t MyI2C_ReceiveAck( void )
{
		uint8_t AckBit;
		MyI2C_W_SDA(1);					// 主机释放SDA线（让它被上拉电阻拉高）
		MyI2C_W_SCL(1);					// 主机在SCL高电平时读取
		AckBit = MyI2C_R_SDA();			// 读取SDA电平，这就是从机的应答
		MyI2C_W_SCL(0);					// 拉低SCL，结束ACK周期
		return 	AckBit;

}

void MyI2C_SendAck(uint8_t AckBit )
{

		MyI2C_W_SDA( AckBit );
		MyI2C_W_SCL(1);					// 从机在SCL上升沿采样
		MyI2C_W_SCL(0);					// 准备下一位
	
}


