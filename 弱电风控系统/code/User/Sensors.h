#ifndef __SENSORS_H
#define __SENSORS_H
#include "stdbool.h"
#include "stm32f10x.h"
#include "ADC2.h"
#include "SHT30.h"
#include "delay.h"
#include "OLED.h"
#include "common_types.h"

void Sensors_Init(void);
MQ_Values_t Sensors_ReadAndPrint(void);

void Sensors_UpdateAll(SystemState_t *state);
#endif
