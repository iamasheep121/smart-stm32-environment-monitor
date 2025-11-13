#include "KEY.h"
#define KEY_PORT GPIOB
#define KEY_PIN  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15
void Key_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//开启PB11作为按键中断源
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = KEY_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB ,&GPIO_InitStructure);
	
}
	
//	/*开启13中断线*/
//	EXTI_InitTypeDef EXTI_InitStruct;
//	EXTI_InitStruct.EXTI_Line = EXTI_Line13;
//	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
//	EXTI_Init(&EXTI_InitStruct);
//	
//	/*开启15中断线*/
//	EXTI_InitStruct.EXTI_Line = EXTI_Line15;
//	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
//	EXTI_Init(&EXTI_InitStruct);
//	
//	/*配置两个按键的nvic分组*/
//	NVIC_InitTypeDef  NVIC_InitStruct;
//	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
//	NVIC_Init(&NVIC_InitStruct);
//	
//}

//volatile uint8_t Key_Mode_Pressed = 0;    // PB13
//volatile uint8_t Key_Motor_Pressed = 0;   // PB15

//void EXTI15_10_IRQHandler(void)
//{
//    if (EXTI_GetITStatus(EXTI_Line15) == SET)
//    {
//       
//        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 0)
//        {
//			
//        }
//        EXTI_ClearITPendingBit(EXTI_Line15); // 清除中断挂起位
//    }
//	
//	if (EXTI_GetITStatus(EXTI_Line13) == SET)
//    {

//        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0)
//        {
//			
//        }
//        EXTI_ClearITPendingBit(EXTI_Line13); // 清除中断挂起位
//    }
//}

/**
  * 函    数：获取键码值
  * 参    数：无
  * 返 回 值：1为按下模式切换，2为按下电机速度切换
  */
//uint8_t Key_GetNumber(void)
//{
//	uint8_t KeyNum = 0;
//	if(GPIO_ReadInputDataBit(KEY_MODESWITCH_PORT,KEY_MODESWITCH_PIN)==0)
//	{
//		Delay_ms(20);
//		while (GPIO_ReadInputDataBit(KEY_MODESWITCH_PORT,KEY_MODESWITCH_PIN)==0);
//		Delay_ms(20);
//		KeyNum = 1;
//		
//	}
//	
//	if(GPIO_ReadInputDataBit(KEY_MOTOR_PORT,KEY_MOTOR_PIN)==0)
//	{
//		Delay_ms(20);
//		while (GPIO_ReadInputDataBit(KEY_MOTOR_PORT,KEY_MOTOR_PIN)==0);
//		Delay_ms(20);
//		KeyNum = 2;
//		
//	}
//	
//	
//	return KeyNum;
//}

/** 
  * 函    数：按键读取函数
  * 参    数：无
  * 返 回 值：键码
  */
KeyType_t KEY_Scan(void)
{
    static uint8_t key_up = 1;  // 按键松开标志
    
    if(key_up && (KEY_MODE_PRES || KEY_UP_PRES || KEY_DOWN_PRES || KEY_CONFIRM_PRES))
    {
        Delay_ms(10);  // 消抖延时
        key_up = 0;
        
        if(KEY_MODE_PRES)       return KEY_MODE;
        else if(KEY_UP_PRES)    return KEY_UP;
        else if(KEY_DOWN_PRES)  return KEY_DOWN;
        else if(KEY_CONFIRM_PRES) return KEY_CONFIRM;
    }
    // 所有按键都为0（低电平）时才认为松开
    else if(KEY_MODE_PRES==0 && KEY_UP_PRES==0 && KEY_DOWN_PRES==0 && KEY_CONFIRM_PRES==0)
    {
        key_up = 1;  // 所有按键都松开
    }
    
    return KEY_NONE;  // 无按键按下
}
