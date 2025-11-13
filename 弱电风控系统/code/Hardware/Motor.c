#include "stm32f10x.h"
#include "PWM.h"

void Motor_Init(void)
{
	PWM_Init();
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = MOTOR_GPIO_IN1 | MOTOR_GPIO_IN2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_InitStructure );
	
}

void Motor_Speed(int8_t Speed)
{
	if( Speed >= 0 )
	{
		//正转
		GPIO_SetBits( GPIOA, MOTOR_GPIO_IN1 );
		GPIO_ResetBits( GPIOA, MOTOR_GPIO_IN2 );
		PWM_SetCompare1( Speed );
		
		
	}
	else
	{
		//反转
		GPIO_ResetBits( GPIOA, MOTOR_GPIO_IN1 );
		GPIO_SetBits( GPIOA, MOTOR_GPIO_IN2);
		PWM_SetCompare1( -Speed );
		
	}
}
