#ifndef __PLATFORM_HANDLER_H
#define __PLATFORM_HANDLER_H
#include "common_types.h"
#include "Sensors.h"
#include "onenet.h"
#include "esp8266.h"
#include "LED.h"
#include "Buzzer.h"

extern const char devPubTopic[];				//发布，传数据
extern const char *devSubTopic[];				//订阅，收数据

#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"mqtts.heclouds.com\",1883\r\n"			//OneNet平台网址

void Network_Init(SystemState_t *current_net);

void Network_UploadData(SystemState_t *state);

void PlatformMode_Handler(SystemState_t *state);

#endif
