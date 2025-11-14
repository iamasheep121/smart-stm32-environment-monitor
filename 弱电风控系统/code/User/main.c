#include "stm32f10x.h"
#include "delay.h"
#include "LED.h"
#include "KEY.h"
#include "ADC2.h"
#include "SHT30.h"
#include "OLED.h"
#include "Motor.h"
#include "MyI2C.h"
#include "usart.h"
#include "esp8266.h"
#include "onenet.h"
#include "Buzzer.h"
#include "Sensors.h"
#include "COMMON_types.h"
#include "Key_handler.h"
#include "OLED_handler.h"
#include "Platform_Handler.h"

// 全局系统状态
SystemState_t CurrentMode = {
    .current_mode = SYS_MANUAL_MODE,
    .current_setting = SET_TEMP_THRESHOLD,
	.net_state = NETWORK_CONNECTING, 
    .motor_speed = SYSTEM_DEFAULT_MOTOR_SPEED,           
    .temp_threshold = DEFAULT_TEMP_THRESHOLD,            
    .humidity_threshold = DEFAULT_HUMIDITY_THRESHOLD,    
    .mq2_threshold = DEFAULT_MQ2_THRESHOLD,              
    .mq7_threshold = DEFAULT_MQ7_THRESHOLD,              
    .current_temp = SYSTEM_DEFAULT_TEMP,                 
    .current_humidity = SYSTEM_DEFAULT_HUMIDITY,         
    .current_mq2 = SYSTEM_DEFAULT_MQ2,                   
    .current_mq7 = SYSTEM_DEFAULT_MQ7                    
};

 /* 全局变量*/
float humidity,temperature = 10;
uint8_t key_value;

 /* 自动控制函数初始化 */
AutoControl_t AutoControl = {0, 0, 0, 0, 0};
MQ_Values_t mq_values;

int main(void) {
	
	/* 别动这个函数，务必第一个初始化*/
	PB7_PowerPath();
	Hardware_Init();
	unsigned char *dataPtr = NULL;

	UsartPrintf(USART1, "弱电风控系统启动\r\n");
	
	/* 网络初始化*/
	Network_Init(&CurrentMode);
	IWDG_Config();
	/* 打印串口log*/
    PrintSystemStatus(&CurrentMode);
	
	/* 订阅主题*/
	OneNet_Subscribe(devSubTopic,1);
	
    while(1)
    {
		/* 键码获取*/
        uint8_t key = KEY_Scan();
		
		/* 读取所有传感器值*/
		Sensors_UpdateAll(&CurrentMode);
		//IWDG_ReloadCounter();//喂狗
		
		/* 根据按键事件选择对应动作*/
        if(key){KEY_HandleKeyEvent(key,&CurrentMode);}

		//自动模式下控制函数
		AutoControl_Handler(&CurrentMode, &AutoControl);
		
		/* OLED根据模式切换页面*/
		OLED_Switch(&CurrentMode);
		
		/* 平台自动上传数据*/
		PlatformMode_Handler(&CurrentMode);
		//IWDG_ReloadCounter();//喂狗
        
        //数据解析
		dataPtr = ESP8266_GetIPD(2);
		if(dataPtr != NULL)//说明有数据
			OneNet_RevPro(dataPtr);//解析数据
		
		ESP8266_Clear();
	
		IWDG_ReloadCounter();//喂狗
		Delay_ms(10);
    }
}
