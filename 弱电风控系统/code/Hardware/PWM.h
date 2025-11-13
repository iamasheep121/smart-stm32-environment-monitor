#ifndef __PWM_H
#define __PWM_H

// ==================================================
//              TIM2 引脚映射 (默认)
// ==================================================
#define TIM2_CH1_PIN        GPIO_PIN_0      // PA0
#define TIM2_CH2_PIN        GPIO_PIN_1      // PA1  
#define TIM2_CH3_PIN        GPIO_PIN_2      // PA2
#define TIM2_CH4_PIN        GPIO_PIN_3      // PA3

// ==================================================
//              TIM3 引脚映射 (默认)  
// ==================================================
#define TIM3_CH1_PIN        GPIO_PIN_6      // PA6
#define TIM3_CH2_PIN        GPIO_PIN_7      // PA7
#define TIM3_CH3_PIN        GPIO_PIN_0      // PB0  
#define TIM3_CH4_PIN        GPIO_PIN_1      // PB1

// ==================================================
//              TIM4 引脚映射 (默认)
// ==================================================
#define TIM4_CH1_PIN        GPIO_PIN_6      // PB6
#define TIM4_CH2_PIN        GPIO_PIN_7      // PB7
#define TIM4_CH3_PIN        GPIO_PIN_8      // PB8
#define TIM4_CH4_PIN        GPIO_PIN_9      // PB9


#define PWM_GPIO_PORT 	GPIOA
#define PWM_GPIO_PIN	GPIO_Pin_0//选择的PWM输出引脚PA0

/*电机驱动电路逻辑高地电平*/
#define MOTOR_GPIO_IN1 GPIO_Pin_4
#define MOTOR_GPIO_IN2 GPIO_Pin_5

#define PWM_GPIO_CLK	RCC_APB2Periph_GPIOA	
#define PWM_TIM_CLK		RCC_APB1Periph_TIM2

#define PWM_TIMER		TIM2//选择的定时器


void PWM_Init(void);
void PWM_SetCompare1(uint16_t Compare);//设置定时器1的CCR
void PWM_SetPrescaler(uint16_t Prescaler);
void PWM_SetCompare2(uint16_t Compare);//设置定时器2的CCR

#endif
