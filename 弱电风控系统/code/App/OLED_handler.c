#include "OLED_Handler.h"

void OLED_Display_Manual(SystemState_t *state)
{
    OLED_Clear();
    
    // 标题 - 手动模式 (汉字，居中显示)
    OLED_ShowString(32, 2, "手动模式", OLED_8X16);  
    OLED_DrawLine(0, 18, 127, 18);                
    
    // 第一行：温度 (左侧区域)
    OLED_ShowString(0, 22, "温度", OLED_8X16);      
    OLED_ShowString(32, 26, ":", OLED_6X8);       
    OLED_ShowFloatNum(38, 26, state->current_temp, 2, 1, OLED_6X8);
    OLED_ShowString(68, 26, "C", OLED_6X8);        
    
    // 第二行：湿度 (左侧区域)
    OLED_ShowString(0, 38, "湿度", OLED_8X16);
    OLED_ShowString(32, 42, ":", OLED_6X8);
    OLED_ShowFloatNum(38, 42, state->current_humidity, 2, 1, OLED_6X8);
    OLED_ShowString(68, 42, "%", OLED_6X8);        
    
    // 风机状态 (右侧区域)
    OLED_ShowString(80, 26, "fan", OLED_6X8);     
    OLED_ShowString(100, 26, ":", OLED_6X8);        
    OLED_ShowNum(108, 26, state->motor_speed, 2, OLED_6X8);
    OLED_ShowString(120, 26, "%", OLED_6X8);        
    
    // 操作提示 (底部居中)
    OLED_ShowString(5, 54, "UP/DOWN:SpeedControl", OLED_6X8);  // Speed control
    
    OLED_Update();
}

void OLED_Display_Auto(SystemState_t *state)
{
    OLED_Clear();
    
    // 标题 - 自动模式
    OLED_ShowString(32, 0, "自动模式", OLED_8X16);
    OLED_DrawLine(0, 16, 127, 16);
    
    // 第一行：温度和风机
    OLED_ShowString(0, 18, "温度:", OLED_8X16);
    OLED_ShowFloatNum(38, 26, state->current_temp, 2, 1, OLED_6X8);
    OLED_ShowString(70, 26, "C", OLED_6X8);
    
    //OLED_ShowString(75, 18, "风机:", OLED_8X16);
    OLED_ShowNum(99, 26, state->motor_speed, 2, OLED_6X8);
    OLED_ShowString(111, 26, "%", OLED_6X8);
    
    // 第二行：湿度和MQ2
    OLED_ShowString(0, 34, "湿度:", OLED_8X16);
    OLED_ShowFloatNum(38, 41, state->current_humidity, 2, 1, OLED_6X8);
    OLED_ShowString(68, 41, "%", OLED_6X8);
    
    OLED_ShowString(80, 41, "MQ2:", OLED_6X8);
    OLED_ShowNum(103, 41, state->current_mq2, 2, OLED_6X8);
	OLED_ShowString(115, 41, "%", OLED_6X8);
    
    // 第三行：MQ7
    OLED_ShowString(8, 56, "MQ7:", OLED_6X8);
    OLED_ShowNum(40, 56, state->current_mq7, 3, OLED_6X8);
	OLED_ShowString(60, 56, "%", OLED_6X8);
    
    // 最右边报警状态 
    uint8_t alarm_y = 50;
    if(state->current_temp > state->temp_threshold) {
        OLED_ShowString(75, 50, "高温", OLED_8X16);
        alarm_y += 16;
    }
    if(state->current_humidity > state->humidity_threshold) {
        OLED_ShowString(75, alarm_y, "高湿", OLED_8X16);
        alarm_y += 16;
    }
    if(state->current_mq2 > state->mq2_threshold) {
        OLED_ShowString(75, alarm_y, "气体", OLED_8X16);
    }
    if(state->current_mq7 > state->mq7_threshold) {
        OLED_ShowString(107, alarm_y, "CO", OLED_8X16);
    }
    
    OLED_Update();
}

void OLED_Display_Platform(SystemState_t *state)
{
    OLED_Clear();
    
    // ========== 第一行：标题栏 ==========
    // 左侧：模式名称
    OLED_ShowString(0, 0, "平台模式", OLED_8X16);        
    
    // 右侧：网络状态
	if(state->net_state == NETWORK_CONNECTED )
	{
		OLED_ShowString(90, 0, "在线", OLED_8X16);           // 右侧对齐
	}
    else{
		OLED_ShowString(90, 0, "离线", OLED_8X16);
	}
    // 标题下方横线
    OLED_DrawLine(0, 16, 127, 16);                      
    
    // ========== 第二行：温度数据 ==========
    OLED_ShowString(0, 18, "温度", OLED_8X16);          
    OLED_ShowString(32, 22, ":", OLED_6X8);              // 冒号
    OLED_ShowFloatNum(38, 22, state->current_temp, 2, 1, OLED_6X8);  // 数值
    OLED_ShowString(62, 22, "C", OLED_6X8);              // 单位
    
    // ========== 第三行：湿度数据 ==========
    OLED_ShowString(0, 34, "湿度", OLED_8X16);           // Y:34-49
    OLED_ShowString(32, 38, ":", OLED_6X8);
    OLED_ShowFloatNum(38, 38, state->current_humidity, 2, 1, OLED_6X8);
    OLED_ShowString(62, 38, "%", OLED_6X8);
    
    // ========== 右侧区域：其他信息 ==========
    // 风速显示
    OLED_ShowString(72, 18, "风速", OLED_8X16);          // 右侧区域
    OLED_ShowString(104, 22, ":", OLED_6X8);
    OLED_ShowNum(110, 22, state->motor_speed, 2, OLED_6X8);
    OLED_ShowString(122, 22, "%", OLED_6X8);
    
    // MQ2气体
    OLED_ShowString(72, 34, "气体", OLED_8X16);
    OLED_ShowString(104, 38, ":", OLED_6X8);
    OLED_ShowNum(110, 38, state->current_mq2, 3, OLED_6X8);
    
    // ========== 底部状态栏 ==========
    OLED_DrawLine(0, 50, 127, 50);                      // 底部横线
    OLED_ShowString(0, 54, "Cloud Control Systems...", OLED_6X8); // 底部提示
    
    OLED_Update();
}

void OLED_Display_Setting(SystemState_t *state)
{
    OLED_Clear();
    
    // 标题
    OLED_ShowString(32, 0, "设置模式", OLED_8X16);
    OLED_DrawLine(0, 16, 127, 16);
    
    // 项目区域
    switch(state->current_setting) {
        case SET_TEMP_THRESHOLD:
            OLED_ShowString(16, 20, "温度", OLED_8X16);
            OLED_ShowNum(80, 26, state->temp_threshold, 2, OLED_6X8);
            OLED_ShowString(92, 26, "C", OLED_6X8);
            break;
        case SET_HUMIDITY_THRESHOLD:
            OLED_ShowString(16, 20, "湿度", OLED_8X16);
            OLED_ShowNum(80, 26, state->humidity_threshold, 2, OLED_6X8);
            OLED_ShowString(92, 26, "%", OLED_6X8);
            break;
        case SET_MQ2_THRESHOLD:
            OLED_ShowString(16, 20, "气体", OLED_8X16);
            OLED_ShowNum(80, 26, state->mq2_threshold, 3, OLED_6X8);
            break;
        case SET_MQ7_THRESHOLD:
            OLED_ShowString(16, 20, "CO", OLED_8X16);
            OLED_ShowNum(80, 26, state->mq7_threshold, 3, OLED_6X8);
            break;
    }
    
    // 操作提示
    OLED_ShowString(20, 46, "UP/DOWN:", OLED_6X8);
    OLED_ShowString(78, 46, "OK:", OLED_6X8);
    OLED_ShowString(40, 56, "<-- -->", OLED_6X8);        // 箭头指示
    
    OLED_Update();
}

void OLED_Display_Default(SystemState_t *state)
{
    OLED_Clear();
    
    // 标题 - 系统概览
    OLED_ShowString(32, 2, "系统概览", OLED_8X16);
    OLED_DrawLine(0, 18, 127, 18);
    
    // 第一行：温度和湿度
    OLED_ShowString(8, 22, "温度:", OLED_6X8);
    OLED_ShowFloatNum(32, 22, state->current_temp, 2, 1, OLED_6X8);
    OLED_ShowString(57, 22, "C", OLED_6X8);
    
    OLED_ShowString(75, 22, "湿度:", OLED_6X8);     
    OLED_ShowFloatNum(99, 22, state->current_humidity, 2, 1, OLED_6X8);  
    OLED_ShowString(124, 22, "%", OLED_6X8);        
    
    // 第二行：气体传感器
    OLED_ShowString(8, 32, "MQ2:", OLED_6X8);
    OLED_ShowNum(32, 32, state->current_mq2, 3, OLED_6X8);
    
    OLED_ShowString(75, 32, "MQ7:", OLED_6X8);
    OLED_ShowNum(99, 32, state->current_mq7, 3, OLED_6X8);
    
    // 第三行：工作模式
    OLED_ShowString(8, 42, "模式:", OLED_6X8);
    switch(state->current_mode) {
        case SYS_MANUAL_MODE: OLED_ShowString(32, 42, "手动", OLED_6X8); break;
        case SYS_AUTO_MODE: OLED_ShowString(32, 42, "自动", OLED_6X8); break;
        case SYS_PLATFORM_MODE: OLED_ShowString(32, 42, "平台", OLED_6X8); break;
        case SYS_SETTING_MODE: OLED_ShowString(32, 42, "设置", OLED_6X8); break;
        default: OLED_ShowString(32, 42, "未知", OLED_6X8); break;
    }
    
    // 第四行：风机状态
    OLED_ShowString(8, 52, "风机:", OLED_6X8);
    OLED_ShowNum(32, 52, state->motor_speed, 2, OLED_6X8);
    OLED_ShowString(44, 52, "%", OLED_6X8);        
    
    // 系统状态指示
    if(state->current_temp > state->temp_threshold || 
       state->current_mq2 > state->mq2_threshold ||
       state->current_mq7 > state->mq7_threshold) {
        OLED_ShowString(75, 52, "报警", OLED_6X8);
    } else {
        OLED_ShowString(75, 52, "正常", OLED_6X8);
    }
    
    OLED_Update();
}


void OLED_Switch(SystemState_t *state )
{
    switch(state->current_mode) {
        case SYS_MANUAL_MODE:
            OLED_Display_Manual(state);
            break;
        case SYS_AUTO_MODE:
            OLED_Display_Auto(state);
            break;
        case SYS_PLATFORM_MODE:
            OLED_Display_Platform(state);
            break;
        case SYS_SETTING_MODE:
            OLED_Display_Setting(state);
            break;
        default:
            OLED_Display_Default(state);
            break;
    }
}
