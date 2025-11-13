#ifndef __KEY_H
#define __KEY_H
#include "common_types.h"

/* 按键功能定义 */
typedef enum {
	KEY_NONE = 0,
    KEY_MODE,        // 模式切换键
    KEY_UP,          // 上调键
    KEY_DOWN,        // 下调键  
    KEY_CONFIRM      // 确认键
} KeyType_t;

// 按键引脚定义
#define KEY_MODE_PIN      GPIO_Pin_12
#define KEY_UP_PIN        GPIO_Pin_13  
#define KEY_DOWN_PIN      GPIO_Pin_14
#define KEY_CONFIRM_PIN   GPIO_Pin_15
#define KEY_PORT          GPIOB

// 检测高电平（因为按键接正极，按下时为1）(面包板右边负极太远，只能接正极，抗干扰能力较差，以后优化)
#define KEY_MODE_PRES    (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0)
#define KEY_UP_PRES      (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0)
#define KEY_DOWN_PRES    (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
#define KEY_CONFIRM_PRES (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 0)

void Key_Init(void);
uint8_t Key_GetNumber(void);
void Key_Turn(void);

KeyType_t KEY_Scan(void);
uint8_t KEY_Scan_Fast(void);

#endif
