/*
*	file:这是学习了DMA之后，将DMA和ADC结合起来一起使用的2.0版本，主要功能是ADC连续扫描多通道，DMA转运
	全自动化，地址从ADC1寄存器到AD_Value数组，我们定义一个函数返回数组值，然后主函数调用
*
*/

#include "ADC2.h"

uint16_t dest[4];
static uint16_t AD_Value[2] = {0};

/**
  * 函    数：初始化ADC1
  * 参    数：无
  * 返 回 值：无
  */
void AD2_Init( void )
{
	//开启ADC1、DMA1和GPIO的时钟
	
	RCC_APB2PeriphClockCmd(ADC1_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(ADC1_GPIO_CLK,ENABLE);
	RCC_AHBPeriphClockCmd(ADC1_DMA1_CLK,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//预留io口时钟，GPIOA
	
	/*将72MHZ分频为12MHZ，ADC频率不能高于14MHZ*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN ;
	GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ADC1_GPIO, &GPIO_InitStructure);
	
	//预留io口,PA6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN ;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*开启四通道*/
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_41Cycles5);
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_9,2,ADC_SampleTime_41Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6,2,ADC_SampleTime_41Cycles5);//新io口
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_41Cycles5);
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_41Cycles5);
	
	/*ADC配置为四通道*/
	ADC_InitTypeDef  ADC_InitStruct;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//触发控制的外部触发源选择
	ADC_InitStruct.ADC_Mode =ADC_Mode_Independent;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_NbrOfChannel = 2;
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC1,&ADC_InitStruct);

//	ADC_ExternalTrigConvCmd(ADC1,ENABLE);
	
	/*配置DMA,核心三要素，使能，触发源以及结构体配置*/
	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralInc =  DMA_PeripheralInc_Disable;
	
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)AD_Value;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable ;
	DMA_InitStruct.DMA_BufferSize = 2;//传输计数器的值
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	/*注意选择触发方式*/
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;//内存到内存，软件触发
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;//传输的优先级
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	/*使能两个外设工作*/
	DMA_Cmd(DMA1_Channel1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
	
	/*校准*/
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)==SET);
		
	//添加中断
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}
	
//void Get_ADValue(void)
//{
//	DMA_Cmd(DMA1_Channel1,DISABLE);
//	DMA_SetCurrDataCounter(DMA1_Channel1 , 4);
//	DMA_Cmd(DMA1_Channel1,ENABLE);
//	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
//	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
//	DMA_ClearFlag(DMA1_FLAG_TC1);
//}

/**
  * 函    数：得到搬运的ADC转换值
  * 参    数：无
  * 返 回 值：AD_Value指针，需要用指针接收
  */
uint16_t* ADC_Get_Values(void)
{
    return AD_Value;  // 返回数组指针，主函数可以直接访问
}

