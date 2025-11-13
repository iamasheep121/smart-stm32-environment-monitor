#ifndef __OLED_HANDLER_H
#define __OLED_HANDLER_H
#include "common_types.h"

void OLED_Display_Manual(SystemState_t *state);

void OLED_Display_Auto(SystemState_t *state);

void OLED_Display_Platform(SystemState_t *state);

void OLED_Display_Setting(SystemState_t *state);

void OLED_Display_Default(SystemState_t *state);

void OLED_Switch(SystemState_t *state );
#endif
