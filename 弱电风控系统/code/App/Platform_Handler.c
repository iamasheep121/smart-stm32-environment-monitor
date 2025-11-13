#include "Platform_Handler.h"

const char devPubTopic[] = "$sys/o5H719J5gg/Test1/thing/property/post";//上传（发布）
const char *devSubTopic[] = {"$sys/o5H719J5gg/Test1/thing/property/set"};//接收（订阅）

//==========================================================
//	函数名称：	Network_Init
//
//	函数功能：	初始化esp8266，与onenet建立连接
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void Network_Init(SystemState_t *current_net)
{
	OLED_Clear();
	current_net->net_state = NETWORK_CONNECTING;
	
	OLED_ShowString(20,24,"Networking",OLED_6X8);
	ESP8266_Init();					
	OLED_ShowString(0,24,"                ",OLED_6X8);
	OLED_ShowString(0,24," Connected to",OLED_6X8);
	OLED_ShowString(30,48,"ONENET",OLED_6X8);
	OLED_Update();
	UsartPrintf(USART_DEBUG, "Connect MQTTs Server...\r\n");
	while(ESP8266_SendCmd(ESP8266_ONENET_INFO, "CONNECT"))
		Delay_ms(500);
	UsartPrintf(USART_DEBUG, "NET_OK\r\n");
	
	while(OneNet_DevLink())			//接入OneNET
		Delay_ms(500);
	
	current_net->net_state = NETWORK_CONNECTED;
}

//==========================================================
//	函数名称：	Network_UploadData
//
//	函数功能：	上传环境数据到OneNet平台(OneJSON格式)
//
//	入口参数：	state： 系统状态结构体，包含温湿度、电机速度等数据
//
//	返回参数：	无
//
//	说明：		数据格式遵循OneJSON标准，平台可直接解析显示
//==========================================================
void Network_UploadData(SystemState_t *state)
{
	char PUBLIS_BUF[256];
    MQ_Values_t mq_values = Sensors_ReadAndPrint();
    
    memset(PUBLIS_BUF, 0, sizeof(PUBLIS_BUF));
    
    sprintf(PUBLIS_BUF,
        "{\"id\":\"123\",\"version\":\"1.0\",\"params\":{"
        "\"Temp\":{\"value\":%.1f},"
        "\"Hum\":{\"value\":%.1f},"
        "\"Mq2\":{\"value\":%d},"
        "\"Mq7\":{\"value\":%d},"
        "\"Anemo\":{\"value\":%d},"
		"\"Led\":{\"value\":%s},"
		"\"Alarm\":{\"value\":%s}"
        "}}",
        state->current_temp,
        state->current_humidity,
        mq_values.mq2_value,
        mq_values.mq7_value,
        state->motor_speed,
		LED_GetStatus() ? "true" : "false",
	    Buzzer_GetStatus() ? "true" : "false"
        
    );
	 OneNET_Publish(devPubTopic, PUBLIS_BUF);
	 
}

//==========================================================
//	函数名称：	PlatformMode_Handler
//
//	函数功能：	定时上传数据
//
//	入口参数：	state： 系统状态结构体，包含温湿度、电机速度等数据
//
//	返回参数：	无
//
//	说明：		数据格式遵循OneJSON标准，平台可直接解析显示
//==========================================================
void PlatformMode_Handler(SystemState_t *state)
{
    static uint16_t upload_counter = 0;
    
    // 每200次循环上传一次
    if(++upload_counter >= 200) 
    {
        Network_UploadData(state);
        upload_counter = 0;
        
        UsartPrintf(USART_DEBUG, "平台数据已上传\r\n");
    }
    
    
}

