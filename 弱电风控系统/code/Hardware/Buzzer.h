#ifndef __BUZZER_H
#define __BUZZER_H
#include "stdbool.h"

#define BUZZER_CLK_PORT RCC_APB2Periph_GPIOA
#define BUZZER_PORT GPIOA
#define BUZZER_PIN GPIO_Pin_12

void BUZZER_Init(void);
void Buzzer_ON(void);
void Buzzer_OFF(void);
void Buzzer_Turn(void);
bool Buzzer_GetStatus(void);

#endif
