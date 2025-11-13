#include "LED.h"

//==========================================================
//	函数名称：	LED_Init
//
//	函数功能：	LED灯初始化
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		初始化系统指示、报警和安全三颗灯
//==========================================================
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = EMERG_LED_PIN | SYSLED_LED_PIN | SAFE_LED_PIN; //PC13、14、15
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SYS_CLK ,&GPIO_InitStructure);
	GPIO_SetBits(SYS_CLK, SAFE_LED_PIN);
	
	GPIO_ResetBits(SYS_CLK ,EMERG_LED_PIN | SAFE_LED_PIN | SYSLED_LED_PIN);
}

//==========================================================
//	函数名称：	LED_GetStatus
//
//	函数功能：	获取系统指示灯状态
//
//	入口参数：	无
//
//	返回参数：	TRUE, FALSE
//	说明：		返回指示灯状态上传云平台
//==========================================================
bool LED_GetStatus(void)
{
     return (GPIO_ReadInputDataBit(SYS_CLK, SYSLED_LED_PIN) == Bit_SET);
}

// 正弦波呼吸灯
//void Sine_Breathing_LED(void) {
//    float angle = 0.0f;
//        // 使用正弦函数计算PWM值，范围0-1000
//        uint16_t pwm_val = (sin(angle) + 1) * 500;  // sin范围[-1,1] → [0,1000]
//        
//        TIM_SetCompare2(TIM2, pwm_val);
//        
//        angle += 0.05f;  // 增加角度
//        if(angle > 2 * 3.14159f) {  // 超过2π则归零
//            angle = 0;
//        }
//        Delay_ms(10);
//}

//void heartbeat(void) {
//    // 像心跳一样：快闪两次 + 停顿
//    GPIO_ResetBits(LED_PORT, LED_PIN); Delay_ms(100);
//    GPIO_SetBits(LED_PORT, LED_PIN);   Delay_ms(100);
//    GPIO_ResetBits(LED_PORT, LED_PIN); Delay_ms(100);
//    GPIO_SetBits(LED_PORT, LED_PIN);   Delay_ms(300);
//}
	
