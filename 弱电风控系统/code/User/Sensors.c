#include "Sensors.h"
void Sensors_ReadWithPPM(void);
void Sensors_Init(void)
{
	AD2_Init();
	SHT30_Init();
}

// 同时获取两个传感器的平均值
void GetBothMQ_Average(uint16_t* mq2_avg, uint16_t* mq7_avg)
{
    uint16_t sum_mq2 = 0, sum_mq7 = 0;
    
    for(uint16_t i = 0; i < 50; i++)
    {
        uint16_t* adc_values = ADC_Get_Values();
        sum_mq2 += adc_values[0];  // MQ2
        sum_mq7 += adc_values[1];  // MQ7
        
        Delay_ms(2);
    }
    
    *mq2_avg = sum_mq2 / 50;
    *mq7_avg = sum_mq7 / 50;
}

//==========================================================
//	函数名称：	Sensors_ReadAndPrint
//
//	函数功能：	获取mq2和mq7的模拟值
//
//	入口参数：	无
//
//	返回参数：	0%-100%
//
//	说明：		处理四个按钮按下后不同事件
//==========================================================
MQ_Values_t Sensors_ReadAndPrint(void) {
    Delay_ms(100);
    
    uint16_t* adc_values = ADC_Get_Values();
    
    MQ_Values_t result;
    result.mq2_value = (adc_values[0] * 100) / 4095;  // 0-100%
    result.mq7_value = (adc_values[1] * 100) / 4095;  // 0-100%
    
    return result;
}

//// 将ADC值转换为实际电压值
//float ADC_ToVoltage(uint16_t adc_value) {
//    return (adc_value * 3.3f) / 4095.0f; 
//}

//void Sensors_ReadWithVoltage(void) {
//    uint16_t* adc_values = ADC_Get_Values();
//    uint16_t mq2_raw = adc_values[0];
//    uint16_t mq7_raw = adc_values[1];
//    
//    float mq2_voltage = ADC_ToVoltage(mq2_raw);
//    float mq7_voltage = ADC_ToVoltage(mq7_raw);
//    
//    printf("=== 传感器电压值 ===\r\n");
//    printf("MQ2电压: %.2fV (原始值: %u)\r\n", mq2_voltage, mq2_raw);
//    printf("MQ7电压: %.2fV (原始值: %u)\r\n", mq7_voltage, mq7_raw);
//    
//    // 根据电压判断传感器状态
//    if(mq2_voltage < 0.1f) printf("MQ2: 未连接或故障\r\n");
//    else if(mq2_voltage > 2.5f) printf("MQ2: 高浓度检测\r\n");
//    else printf("MQ2: 正常范围\r\n");
//        
//    if(mq7_voltage < 0.1f) printf("MQ7: 未连接或故障\r\n");
//    else if(mq7_voltage > 2.0f) printf("MQ7: 高浓度检测\r\n");
//    else printf("MQ7: 正常范围\r\n");
//}
    
void Sensors_UpdateAll(SystemState_t *state)
{
		/* 传感器数据获取*/
		MQ_Values_t mq_values = Sensors_ReadAndPrint();//会阻塞100ms
		state->current_mq2 = mq_values.mq2_value;
        state->current_mq7 = mq_values.mq7_value;
	
		if(SHT30_ReadData(&state->current_temp, &state->current_humidity) == 0) 
		{
			
			
		}		
		else{ UsartPrintf(USART1, "温湿度获取错误\r\n");
		}
				
}
