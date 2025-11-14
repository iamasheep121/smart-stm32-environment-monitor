#ifndef __COMMON_TYPES_H
#define __COMMON_TYPES_H

#include "stdbool.h"
#include <string.h>
#include "stm32f10x.h"
#include "PWM.h"
#include "Delay.h"
#include "math.h"
#include "stdio.h"
#include "usart.h"
#include "Motor.h"
#include "OLED.h"

/*******************************
 *        系统配置说明
 *******************************/
/*
 * 【配置分层说明】
 * 
 * 1. 用户可调阈值范围 - 用户在设置模式下可以调整的范围
 *    - 用于限制用户在设置模式下的调整范围，防止设置不合理数值
 *    - 例如：设置温度为最小10，最大50，则温度报警阈值只能在10-50°C之间调整
 * 
 * 2. 系统报警阈值 - 系统实际的报警触发值  
 *    - 用户在上述范围内设置的具体数值，保存在state结构体中
 *    - 例如：用户设置为35°C，当温度>35°C时触发报警，如果程序设置最大为50，则用户只能设置报警阈值最高50
 * 
 * 3. 系统固定参数 - 系统运行所需的固定配置
 *    - 初始化值、默认速度等系统固有参数
 *    - 用户不可调整
 */

/**************************************************
 * 1. 用户可调阈值范围 - 设置模式下的调整限制
 *    作用：限制用户在设置界面能调整的范围
 **************************************************/

// 温度阈值可调范围
#define TEMP_THRESHOLD_MIN          10        // 温度阈值最小值(°C) - 用户能设置的最低温度报警点
#define TEMP_THRESHOLD_MAX          50        // 温度阈值最大值(°C) - 用户能设置的最高温度报警点  
#define TEMP_THRESHOLD_STEP         1         // 温度阈值调整步长(°C) - 每次按键调整的幅度

// 湿度阈值可调范围
#define HUMIDITY_THRESHOLD_MIN      30        // 湿度阈值最小值(%) - 用户能设置的最低湿度报警点
#define HUMIDITY_THRESHOLD_MAX      95        // 湿度阈值最大值(%) - 用户能设置的最高湿度报警点
#define HUMIDITY_THRESHOLD_STEP     5         // 湿度阈值调整步长(%) - 每次按键调整的幅度

// MQ-2气体传感器阈值可调范围
#define MQ2_THRESHOLD_MIN           50        // MQ-2阈值最小值 - 用户能设置的最低气体浓度报警点
#define MQ2_THRESHOLD_MAX           100       // MQ-2阈值最大值 - 用户能设置的最高气体浓度报警点
#define MQ2_THRESHOLD_STEP          10        // MQ-2阈值调整步长 - 每次按键调整的幅度

// MQ-7一氧化碳传感器阈值可调范围  
#define MQ7_THRESHOLD_MIN           50        // MQ-7阈值最小值 - 用户能设置的最低CO浓度报警点
#define MQ7_THRESHOLD_MAX           100       // MQ-7阈值最大值 - 用户能设置的最高CO浓度报警点
#define MQ7_THRESHOLD_STEP          10        // MQ-7阈值调整步长 - 每次按键调整的幅度

// 手动模式电机速度可调范围
#define MANUAL_MOTOR_SPEED_MIN      0         // 电机最小速度(%) - 手动模式下电机最低转速
#define MANUAL_MOTOR_SPEED_MAX      70       // 电机最大速度(%) - 手动模式下电机最高转速
#define MOTOR_SPEED_STEP            10         // 电机速度调整步长(%) - 每次按键调整的幅度

/**************************************************
 * 2. 系统固定参数 - 系统运行所需的固定配置
 *    作用：系统初始化、默认值等固定参数，用户不可调整
 **************************************************/

// 系统上电默认值
#define SYSTEM_DEFAULT_TEMP         25        // 温度初始值(℃) - 系统启动时的默认温度显示
#define SYSTEM_DEFAULT_HUMIDITY     60        // 湿度初始值(%) - 系统启动时的默认湿度显示  
#define SYSTEM_DEFAULT_MQ2          20        // MQ2初始值 - 系统启动时的默认气体浓度值
#define SYSTEM_DEFAULT_MQ7          15        // MQ7初始值 - 系统启动时的默认CO浓度值

// 自动模式电机控制参数
#define AUTO_MOTOR_MAX_SPEED        80        // 自动模式最大速度(%) - 自动控制时电机的最高限制
#define AUTO_MOTOR_STOP_SPEED		0		  // 自动模式停止速度(%) - 自动控制时电机的关闭速度

// 自动模式电机的速度控制
#define AUTO_MOTOR_MAX_SPEED      80    	  // 高速档 - 报警状态
#define AUTO_MOTOR_MEDIUM_SPEED   50    	  // 中速档 - 接近阈值
#define AUTO_MOTOR_LOW_SPEED      30    	  // 低速档 - 正常状态
#define AUTO_MOTOR_MIN_SPEED      0     	  // 停止

// 平台模式下发指令控制电机
#define PLATFORM_MOTOR_ENABLE_SPEED				50	//电机开启速度（%）
#define PLATFORM_MOTOR_DISABLE_SPEED			0	//关闭速度（%）

/* 设计的接近阈值程度，比如设置温度阈值设置50，接近程度设置为5，则在温度到达50-5的时候会开启风机*/
// 提前预警参数
#define PRE_ACTIVATION_RANGE             5   // 预激活范围：距离阈值5个单位时提前动作,这个暂时没用，可以粗略使用，下面更精细
#define TEMP_PRE_ACTIVATION              2
#define HUMIDITY_PRE_ACTIVATION          5


/**************************************************
 * 3. 系统报警阈值默认值 - 用户未设置时的默认报警点
 *    作用：系统第一次启动时的默认报警阈值
 **************************************************/
#define DEFAULT_TEMP_THRESHOLD      40        // 默认温度报警阈值(℃) - 用户未设置时的温度报警点
#define DEFAULT_HUMIDITY_THRESHOLD  80        // 默认湿度报警阈值(%) - 用户未设置时的湿度报警点  
#define DEFAULT_MQ2_THRESHOLD       60        // 默认MQ2报警阈值 - 用户未设置时的气体报警点
#define DEFAULT_MQ7_THRESHOLD       60        // 默认MQ7报警阈值 - 用户未设置时的CO报警点
#define SYSTEM_DEFAULT_MOTOR_SPEED  0        // 默认电机速度(%) - 系统启动时的电机转速

/*******************************
 *        数据类型定义
 *******************************/

// 系统工作模式枚举
typedef enum {
    SYS_MANUAL_MODE = 0,    // 手动模式 - 用户手动控制电机速度
    SYS_AUTO_MODE,          // 自动模式 - 系统根据传感器自动控制
    SYS_PLATFORM_MODE,      // 平台模式 - 通过云平台远程控制
    SYS_SETTING_MODE,       // 设置模式 - 设置各传感器报警阈值
    SYS_MODE_COUNT          // 模式总数 - 用于循环切换
} SystemMode_t;

// 设置项目枚举
typedef enum {
    SET_TEMP_THRESHOLD = 0,     // 温度阈值设置
    SET_HUMIDITY_THRESHOLD,     // 湿度阈值设置  
    SET_MQ2_THRESHOLD,          // MQ2气体阈值设置
    SET_MQ7_THRESHOLD,          // MQ7一氧化碳阈值设置
    SET_ITEM_COUNT              // 设置项目总数 - 用于循环切换
} SettingItem_t;

// 电机档位定义
typedef enum {
    FAN_OFF = 0,        // 停止
    FAN_LOW,            // 低速档
    FAN_MEDIUM,         // 中速档  
    FAN_HIGH            // 高速档
} Fan_State_t;

// 网络管理设置
typedef enum {
    NETWORK_DISCONNECTED = 0,    // 网络断开
    NETWORK_CONNECTING,          // 连接中  
    NETWORK_CONNECTED,           // 已连接
    NETWORK_ERROR,               // 网络错误
} NetworkState_t;


// 系统状态结构体 - 保存系统运行时的所有状态信息
typedef struct {
    // 系统模式状态
    SystemMode_t current_mode;      // 当前工作模式
    SettingItem_t current_setting;  // 当前设置项目（仅在设置模式下使用）
	NetworkState_t net_state;		// 网络状态
    
    // 控制参数
    uint8_t motor_speed;            // 电机速度 0-100%
    
    // 报警阈值参数 - 这些是用户实际设置的报警值
    uint8_t temp_threshold;         // 温度报警阈值 - 实际触发报警的温度值
    uint8_t humidity_threshold;     // 湿度报警阈值 - 实际触发报警的湿度值
    uint16_t mq2_threshold;         // MQ2报警阈值 - 实际触发报警的气体浓度值
    uint16_t mq7_threshold;         // MQ7报警阈值 - 实际触发报警的CO浓度值
    
    // 传感器当前值
    float current_temp;             // 当前温度值
    float current_humidity;         // 当前湿度值
    uint16_t current_mq2;           // 当前MQ2气体浓度值
    uint16_t current_mq7;           // 当前MQ7一氧化碳浓度值
	
} SystemState_t;

// 自动控制状态变量 - 用于自动模式下的控制逻辑
typedef struct {
    uint8_t temp_alarm;             // 温度报警状态
    uint8_t humi_alarm;             // 湿度报警状态
    uint8_t mq2_alarm;              // MQ2气体报警状态
    uint8_t mq7_alarm;              // MQ7一氧化碳报警状态
	uint8_t fan_alarm;				// 风机速度过快报警
    uint8_t fan_auto_status;        // 风机自动控制状态
} AutoControl_t;

// 气敏传感器采集数据结构
typedef struct {
    uint8_t mq2_value;              // MQ2传感器采集值
    uint8_t mq7_value;              // MQ7传感器采集值
} MQ_Values_t;

typedef struct{
	uint8_t MAIN_MENU;
	uint8_t AUTO_MENU_DISPLAY;
	uint8_t MANUAL_MENU_DISPALY;
	uint8_t PLATFORM_MENU_DISPLAY;
	uint8_t SETTING_MENG_DISPLAY;	
	uint8_t SET_MENU_COUNT;
}Menu_Dispaly_t;

// 系统信息获取函数
const char* GetModeString(SystemMode_t mode);        // 获取模式名称字符串
const char* GetSettingString(SettingItem_t item);    // 获取设置项目名称字符串
void PrintSystemStatus(SystemState_t *state);        // 打印系统状态信息
void PrintSettingStatus(SystemState_t *state);       // 打印设置状态信息

// 自动控制函数
void AutoControl_Handler(SystemState_t *state, AutoControl_t *auto_ctrl);  // 自动模式事件处理
void StateMachine_Control(SystemState_t *state, AutoControl_t *auto_ctrl); // 电机自动控制函数

// 显示函数
void OLED_Display_Simple(const SystemState_t *state);  // OLED简易显示，前期测试版，已弃用
void Hardware_Init(void);
void PB7_PowerPath(void);       //硬件bug，第一个初始化，勿动

void SysTick_Init(void);		//留着以后搞时间轮转用，但是这个时间老是被编辑器优化
uint32_t Get_System_Time(void);

void IWDG_Config(void);         //看门狗配置
#endif

