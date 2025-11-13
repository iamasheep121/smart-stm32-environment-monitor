 /*  文件说明：用于处理不同按键按下操作 */
#include "Key_handler.h"

void KEY_ProcessMode(SystemState_t *state) {
    UsartPrintf(USART1, "模式键按下\r\n");
    state->current_mode = (state->current_mode + 1) % SYS_MODE_COUNT;
    UsartPrintf(USART1, "切换到: %s\r\n", GetModeString(state->current_mode));
    if(state->current_mode == SYS_SETTING_MODE) {
        PrintSettingStatus(state);
    }
}

/* 增加按键处理函数子函数*/
void HandleSettingIncrement(SystemState_t *state) {
    switch(state->current_setting) {
        case SET_TEMP_THRESHOLD:
            if(state->temp_threshold < TEMP_THRESHOLD_MAX) 
                state->temp_threshold += TEMP_THRESHOLD_STEP;
            break;
        case SET_HUMIDITY_THRESHOLD:
            if(state->humidity_threshold < HUMIDITY_THRESHOLD_MAX) 
                state->humidity_threshold += HUMIDITY_THRESHOLD_STEP;
            break;
        case SET_MQ2_THRESHOLD:
            if(state->mq2_threshold < MQ2_THRESHOLD_MAX)
                state->mq2_threshold += MQ2_THRESHOLD_STEP;
            break;
        case SET_MQ7_THRESHOLD:
            if(state->mq7_threshold < MQ7_THRESHOLD_MAX)
                state->mq7_threshold += MQ7_THRESHOLD_STEP;
            break;
    }
    PrintSettingStatus(state);
}

/* 增加按键处理函数*/
void KEY_ProcessUp(SystemState_t *state) {
    UsartPrintf(USART1, "上调键按下\r\n");
    
    if(state->current_mode == SYS_MANUAL_MODE) {
        // 手动模式逻辑
        if(state->motor_speed < MANUAL_MOTOR_SPEED_MAX) {
            state->motor_speed += MOTOR_SPEED_STEP;
            UsartPrintf(USART1, "电机速度: %d%%\r\n", state->motor_speed);
            Motor_Speed(state->motor_speed);
        }
    } else if(state->current_mode == SYS_SETTING_MODE) {
        // 设置模式逻辑
        HandleSettingIncrement(state); 
    }
}

/* 减少按键处理函数*/
void KEY_ProcessDown(SystemState_t *state)
{
    UsartPrintf(USART1, "下调键按下\r\n");
    
    if(state->current_mode == SYS_MANUAL_MODE)
    {
        // 手动模式：调节电机速度
        if(state->motor_speed > MANUAL_MOTOR_SPEED_MIN  )
        {
            state->motor_speed -= MOTOR_SPEED_STEP;
            UsartPrintf(USART1, "电机速度: %d%%\r\n", state->motor_speed);
            Motor_Speed(state->motor_speed);
        }
    }
    else if(state->current_mode == SYS_SETTING_MODE) 
    {
        // 设置模式逻辑
        HandleSettingReduce(state);  
    }
}

/* 减少按键处理子函数*/
void HandleSettingReduce(SystemState_t *state)
{
    // 设置模式：减少当前设置项目的值
    switch(state->current_setting)
    {
        case SET_TEMP_THRESHOLD:
            if(state->temp_threshold > TEMP_THRESHOLD_MIN)
                state->temp_threshold -= TEMP_THRESHOLD_STEP;
            break;
        case SET_HUMIDITY_THRESHOLD:
            if(state->humidity_threshold > HUMIDITY_THRESHOLD_MIN)
                state->humidity_threshold -= HUMIDITY_THRESHOLD_STEP;
            break;
        case SET_MQ2_THRESHOLD:
            if(state->mq2_threshold > MQ2_THRESHOLD_MIN)
                state->mq2_threshold -= MQ2_THRESHOLD_STEP;
            break;
        case SET_MQ7_THRESHOLD:
            if(state->mq7_threshold > MQ7_THRESHOLD_MIN)
                state->mq7_threshold -= MQ7_THRESHOLD_STEP;
            break;
    }
    PrintSettingStatus(state);
}

 /* 确认按键处理函数*/
void KEY_ProcessConfirm(SystemState_t *state)
{
    UsartPrintf(USART1, "确认键按下\r\n");
    if(state->current_mode == SYS_SETTING_MODE)
    {
        // 设置模式下：切换设置项目
        state->current_setting = (state->current_setting + 1) % SET_ITEM_COUNT;
        UsartPrintf(USART1, "切换到设置项目: %s\r\n", GetSettingString(state->current_setting));
        PrintSettingStatus(state);
    }
    else
    {
        // 其他模式下：显示系统状态
        PrintSystemStatus(state);
    }
}

//==========================================================
//	函数名称：	KEY_HandleKeyEvent
//
//	函数功能：	不同按键事件处理
//
//	入口参数：	key：键码	state：系统结构体
//
//	返回参数：	无
//
//	说明：		处理四个按钮按下后不同事件
//==========================================================
void KEY_HandleKeyEvent(uint8_t key, SystemState_t *state) {
    switch(key) {
        case KEY_MODE:    KEY_ProcessMode(state); break;
        case KEY_UP:      KEY_ProcessUp(state); break;
        case KEY_DOWN:    KEY_ProcessDown(state); break;
        case KEY_CONFIRM: KEY_ProcessConfirm(state); break;
    }
}
