#ifndef __ADC2_H
#define __ADC2_H
#include "stm32f10x.h"
#include "MY_DMA.h"

/*开启外设时钟*/
#define ADC1_CLK			RCC_APB2Periph_ADC1//ADC1
#define ADC1_DMA1_CLK		RCC_AHBPeriph_DMA1//DMA1
#define ADC1_GPIO_CLK		RCC_APB2Periph_GPIOB
#define ADC1_GPIO			GPIOB
#define ADC1_GPIO_PIN 		GPIO_Pin_0 

void AD2_Init(void);
void Get_ADValue(void);
extern uint16_t dest[4];

/*ADC1的四个通道*/
typedef struct {
    uint16_t adc0;
    uint16_t adc1; 
    uint16_t adc2;
    uint16_t adc3;
    uint32_t timestamp;
} adc_data_t;

void ADC_DMA_Init(void);
uint16_t* ADC_Get_Values(void);
uint16_t ADC_Get_Channel_Value(uint8_t channel);

#endif

