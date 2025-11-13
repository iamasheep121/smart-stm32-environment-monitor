#include "stm32f10x.h"
#include "Buzzer.h"

//==========================================================
//	函数名称：	BUZZER_Init
//
//	函数功能：	初始化蜂鸣器
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		低电平触发
//==========================================================
void BUZZER_Init(void)
{
	RCC_APB2PeriphClockCmd(BUZZER_CLK_PORT,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BUZZER_PORT ,&GPIO_InitStructure);
	
	GPIO_SetBits(BUZZER_PORT, BUZZER_PIN);
}

void Buzzer_ON(void)
{
	GPIO_ResetBits(BUZZER_PORT, BUZZER_PIN );
}

void Buzzer_OFF(void)
{
	GPIO_SetBits(BUZZER_PORT, BUZZER_PIN );
}

void Buzzer_Turn(void)
{
	if(GPIO_ReadOutputDataBit(BUZZER_PORT,BUZZER_PIN)==0)
	{
		GPIO_SetBits(BUZZER_PORT,BUZZER_PIN);
	}
	else
	{
		GPIO_ResetBits(BUZZER_PORT,BUZZER_PIN);
	}
	
}

//==========================================================
//	函数名称：	Buzzer_GetStatus
//
//	函数功能：	上传蜂鸣器状态给云平台
//
//	入口参数：	无
//
//	返回参数：	TRUE，FALSE
//
//	说明：		低电平触发
//==========================================================
bool Buzzer_GetStatus(void)
{
    return (GPIO_ReadOutputDataBit(BUZZER_PORT, BUZZER_PIN) == Bit_RESET);
}
