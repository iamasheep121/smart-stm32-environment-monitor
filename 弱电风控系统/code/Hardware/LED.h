#ifndef __LED_H
#define __LED_H
#include "common_types.h"

#define SAFE_LED_PIN GPIO_Pin_13			//安全，报警关，平时开
#define EMERG_LED_PIN GPIO_Pin_14			//紧急，报警开，平时关
#define SYSLED_LED_PIN GPIO_Pin_15			//系统，远程控制开关
#define SYS_CLK GPIOC						//系统时钟灯

#define EMERG_LED_ON    GPIO_SetBits(GPIOC, GPIO_Pin_14)
#define EMERG_LED_OFF   GPIO_ResetBits(GPIOC, GPIO_Pin_14)

#define SAFE_LED_ON    GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define SAFE_LED_OFF   GPIO_ResetBits(GPIOC, GPIO_Pin_13)

#define SYS_LED_ON    GPIO_SetBits(GPIOC, GPIO_Pin_15)	
#define SYS_LED_OFF   GPIO_ResetBits(GPIOC, GPIO_Pin_15)

void LED_Init(void);
bool LED_GetStatus(void);
#endif

