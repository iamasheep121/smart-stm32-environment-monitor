#include "common_types.h"
#include "usart.h"
#include "LED.h"
#include "Motor.h"
#include "Buzzer.h"
#include "OLED.h"
#include "SHT30.h"
#include "Key.h"
#include "ADC2.h"

void Hardware_Init(void)
{
	/*初始化各种外设*/
	LED_Init();
	OLED_Init();
	AD2_Init();
	SHT30_Init();
	Key_Init();
	Motor_Init();
	BUZZER_Init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Usart2_Init(115200);
	Usart1_Init(115200);
	
	UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
	
	OLED_ShowString(0,20,"硬件初始化完成",OLED_8X16);
	OLED_Update();
	Delay_ms(500);
	OLED_Clear();
	OLED_ShowString(20,20,"云端互联启动",OLED_8X16);
	OLED_Update();
	
}

// 获取模式字符串
const char* GetModeString(SystemMode_t mode)
{
    switch(mode)
    {
        case SYS_MANUAL_MODE:   return "手动模式";
        case SYS_AUTO_MODE:     return "自动模式";
        case SYS_PLATFORM_MODE: return "平台模式";
        case SYS_SETTING_MODE:  return "设置模式";
        default:                return "未知模式";
    }
}

// 获取设置项目字符串
const char* GetSettingString(SettingItem_t item)
{
    switch(item)
    {
        case SET_TEMP_THRESHOLD:    return "温度阈值";
        case SET_HUMIDITY_THRESHOLD:return "湿度阈值";
        case SET_MQ2_THRESHOLD:     return "MQ2阈值";
        case SET_MQ7_THRESHOLD:     return "MQ7阈值";
        default:                    return "未知项目";
    }
}

// 打印系统状态
void PrintSystemStatus(SystemState_t *state)
{
    UsartPrintf(USART1, "\r\n============== 系统状态 ==============\r\n");
    UsartPrintf(USART1, "工作模式: %s\r\n", GetModeString(state->current_mode));
    UsartPrintf(USART1, "电机速度: %d%%\r\n", state->motor_speed);
    UsartPrintf(USART1, "当前温度: %.1f℃  阈值: %d℃\r\n", state->current_temp, state->temp_threshold);
    UsartPrintf(USART1, "当前湿度: %.1f%%  阈值: %d%%\r\n", state->current_humidity, state->humidity_threshold);
    UsartPrintf(USART1, "当前有害气体浓度: %d%%  阈值: %d%%\r\n", state->current_mq2, state->mq2_threshold);
    UsartPrintf(USART1, "当前一氧化碳浓度: %d%%  阈值: %d%%\r\n", state->current_mq7, state->mq7_threshold);
    UsartPrintf(USART1, "=====================================\r\n\r\n");
}

// 打印设置状态
void PrintSettingStatus(SystemState_t *state)
{
    UsartPrintf(USART1, "\r\n============== 设置模式 ==============\r\n");
    UsartPrintf(USART1, "设置项目: %s\r\n", GetSettingString(state->current_setting));
    
    switch(state->current_setting)
    {
        case SET_TEMP_THRESHOLD:
            UsartPrintf(USART1, "当前值: %d℃\r\n", state->temp_threshold);
            break;
        case SET_HUMIDITY_THRESHOLD:
            UsartPrintf(USART1, "当前值: %d%%\r\n", state->humidity_threshold);
            break;
        case SET_MQ2_THRESHOLD:
            UsartPrintf(USART1, "当前值: %d%%\r\n", state->mq2_threshold);
            break;
        case SET_MQ7_THRESHOLD:
            UsartPrintf(USART1, "当前值: %d%%\r\n", state->mq7_threshold);
            break;
    }
    UsartPrintf(USART1, "操作: UP/DOWN调整 | CONFIRM切换项目\r\n");
    UsartPrintf(USART1, "=====================================\r\n\r\n");
}


//自动控制函数,用于控制状态下的处理情况
void AutoControl_Handler(SystemState_t *state, AutoControl_t *auto_ctrl)
{
    // 温度报警检测(利用标志位防止重复报警)
    if(state->current_temp > state->temp_threshold) {
        if(!auto_ctrl->temp_alarm) {
            UsartPrintf(USART1, "温度报警! 当前:%.1fC, 阈值:%dC\r\n", 
                       state->current_temp, state->temp_threshold);
            auto_ctrl->temp_alarm = 1;
        }
    } else {
        auto_ctrl->temp_alarm = 0;
    }
	
	// 湿度报警检测
    if(state->current_humidity > state->humidity_threshold) {
        if(!auto_ctrl->humi_alarm) {
            UsartPrintf(USART1, "湿度报警! 当前:%.1f%%, 阈值:%d%%\r\n", 
                       state->current_humidity, state->humidity_threshold);
            auto_ctrl->humi_alarm = 1;
        }
    } else {
        auto_ctrl->humi_alarm = 0;
    }
    
    // MQ2报警检测
    if(state->current_mq2 > state->mq2_threshold) {
        if(!auto_ctrl->mq2_alarm) {
            UsartPrintf(USART1, "MQ2报警! 当前:%d, 阈值:%d\r\n", 
                       state->current_mq2, state->mq2_threshold);
            auto_ctrl->mq2_alarm = 1;
        }
    } else {
        auto_ctrl->mq2_alarm = 0;
    }
    
    // MQ7报警检测  
    if(state->current_mq7 > state->mq7_threshold) {
        if(!auto_ctrl->mq7_alarm) {
            UsartPrintf(USART1, "MQ7报警! 当前:%d, 阈值:%d\r\n", 
                       state->current_mq7, state->mq7_threshold);
            auto_ctrl->mq7_alarm = 1;
        }
    } else {
        auto_ctrl->mq7_alarm = 0;
    }

    // 自动模式下控制风扇
    if(state->current_mode == SYS_AUTO_MODE) {
        StateMachine_Control(state, auto_ctrl);
    } else {
        // 非自动模式下重置自动控制状态
        auto_ctrl->fan_auto_status = 0;
    }
    
    // 报警指示（报警灯和蜂鸣器）
	   if(state->current_mode == SYS_AUTO_MODE) {

		if(auto_ctrl->temp_alarm || auto_ctrl->mq2_alarm || auto_ctrl->mq7_alarm || auto_ctrl->humi_alarm) {
      
			Buzzer_ON();
			EMERG_LED_ON;
			SAFE_LED_OFF;
			} else {
			Buzzer_OFF();
			EMERG_LED_OFF;
			SAFE_LED_ON;
		}
	}
}	

// 简易电机自动控制函数，根据报警数量自动控制电机速度
void StateMachine_Control(SystemState_t *state, AutoControl_t *auto_ctrl) {
    static Fan_State_t last_state = FAN_OFF;
    static uint8_t last_alarm_count = 0;
    
    Fan_State_t new_state = FAN_OFF; // 默认关闭
    
    // 计算当前报警数量
    uint8_t alarm_count = 0;
    if(auto_ctrl->temp_alarm) alarm_count++;
    if(auto_ctrl->humi_alarm) alarm_count++;
    if(auto_ctrl->mq2_alarm) alarm_count++;
    if(auto_ctrl->mq7_alarm) alarm_count++;
    
    // 状态判断
    if (alarm_count >= 2) {
        // 2个或以上报警 → 高速档
        new_state = FAN_HIGH;
    }
    else if (alarm_count == 1) {
        // 1个报警 → 中速档
        new_state = FAN_MEDIUM;
    }
    else {
        // 无报警：检查是否接近阈值
        if (state->current_temp > (state->temp_threshold - TEMP_PRE_ACTIVATION) ||
            state->current_humidity > (state->humidity_threshold - HUMIDITY_PRE_ACTIVATION)) {
            // 温度或湿度接近阈值 → 低速档
            new_state = FAN_LOW;
        } else {
            // 所有参数都正常 → 关闭
            new_state = FAN_OFF;
        }
    }
    
    // 只在状态变化时打印
    if (new_state != last_state || alarm_count != last_alarm_count) {
        switch(new_state) {
            case FAN_OFF:
                UsartPrintf(USART1, "环境良好：风机停止\r\n");
                break;
            case FAN_LOW:
                UsartPrintf(USART1, "接近阈值：低速通风\r\n");
                break;
            case FAN_MEDIUM:
                UsartPrintf(USART1, "单个报警：中速通风\r\n");
                break;
            case FAN_HIGH:
                UsartPrintf(USART1, "多个报警：高速通风\r\n");
                break;
        }
        UsartPrintf(USART1, "报警数量:%d, 风机速度:%d%%\r\n", alarm_count, state->motor_speed);
        
        // 更新上一次状态
        last_state = new_state;
        last_alarm_count = alarm_count;
    }
    
    // 根据状态设置电机速度
    switch(new_state) {
        case FAN_OFF:
            state->motor_speed = AUTO_MOTOR_MIN_SPEED;    // 0%
            break;
        case FAN_LOW:
            state->motor_speed = AUTO_MOTOR_LOW_SPEED;    // 30%
            break;
        case FAN_MEDIUM:
            state->motor_speed = AUTO_MOTOR_MEDIUM_SPEED; // 50%
            break;
        case FAN_HIGH:
            state->motor_speed = AUTO_MOTOR_MAX_SPEED;    // 80%
            break;
    }
    
    // 执行控制
    Motor_Speed(state->motor_speed);
    
    // 更新自动控制状态
    auto_ctrl->fan_auto_status = (new_state != FAN_OFF);
}

// 获取状态字符串，用于显示
const char* GetFanStateString(Fan_State_t state) {
    switch(state) {
        case FAN_OFF:    return "停止";
        case FAN_LOW:    return "低速";
        case FAN_MEDIUM: return "中速";
        case FAN_HIGH:   return "高速";
        default:         return "未知";
    }
}

// OLED显示各个数据,像素点为长128，宽64
void OLED_Display_Simple( const SystemState_t *state) {
    OLED_Clear();
    
    OLED_ShowString(0, 10, "Temp:", OLED_6X8);
    OLED_ShowFloatNum(30, 10, state->current_temp, 2, 1, OLED_6X8);
    
    OLED_ShowString(65, 10, "Humi:", OLED_6X8);
    OLED_ShowFloatNum(94, 10, state->current_humidity, 2, 1, OLED_6X8);
    
    OLED_ShowString(0, 20, "MQ2:", OLED_6X8);
    OLED_ShowNum(24, 20, state->current_mq2, 3, OLED_6X8);
    
    OLED_ShowString(70, 20, "MQ7:", OLED_6X8);
    OLED_ShowNum(94, 20, state->current_mq2, 3, OLED_6X8);
    
    OLED_ShowString(0, 30, "MODE:", OLED_6X8);
    OLED_ShowString(30, 30, state->current_mode == SYS_AUTO_MODE ? "AUTO" : "MAN", OLED_6X8);
    
    OLED_ShowString(70, 30, "FAN:", OLED_6X8);
    OLED_ShowNum(94, 30, state->motor_speed, 3, OLED_6X8);
    
    OLED_Update();
}

//==========================================================
//	函数名称：	PB7_PowerPath
//
//	函数功能：	单片机IO口保护
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		PCB板子画错了，3.3V飞线到PB7，PB6为GND，千万别动这两个口
//==========================================================
void PB7_PowerPath(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  // 模拟输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
}
