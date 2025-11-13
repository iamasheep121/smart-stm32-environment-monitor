#ifndef __KEY_HANDLER_H
#define __KEY_HANDLER_H
#include "common_types.h"
#include "KEY.h"

void KEY_ProcessMode(SystemState_t *state);

void KEY_ProcessUp(SystemState_t *state);  
void HandleSettingIncrement(SystemState_t *state);

void KEY_ProcessDown(SystemState_t *state);
void HandleSettingReduce(SystemState_t *state);

void KEY_ProcessConfirm(SystemState_t *state);

void KEY_HandleKeyEvent(uint8_t key, SystemState_t *state);
#endif
