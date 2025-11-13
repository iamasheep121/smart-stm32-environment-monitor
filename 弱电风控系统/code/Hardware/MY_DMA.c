#include "stm32f10x.h"
uint16_t myDMA_Size;
void MyDMA_Init(uint32_t src, uint32_t dest,uint16_t Size)
{
	myDMA_Size = Size;
	//	DMA Config three steps that the first to enable DMA_Clock,
	//	the second to config DMA_REF and the end 
	//	of DMA_Cmd to ENABLE;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	DMA_InitTypeDef  DMA_InitStruct;
	//
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable ;
	DMA_InitStruct.DMA_MemoryBaseAddr = dest ;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitStruct.DMA_PeripheralBaseAddr = src;
	DMA_InitStruct.DMA_PeripheralDataSize =DMA_PeripheralDataSize_Byte;
	
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_BufferSize = Size;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	DMA_Cmd(DMA1_Channel1,DISABLE);
}

void MyDMA_Transfer ( void )
{
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1 , myDMA_Size);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);
}

//    
//    
//	const uint8_t src[] = {0x01,0x02,0x03,0x04};
//	uint8_t dest[] = {0,0,0,0};
//	
//    /*模块初始化*/
//    OLED_Init();  
//	
//	OLED_ShowString(1,1,"SRC");
//	OLED_ShowString(3,1,"det");
//	
//	OLED_ShowHexNum(1,8,(uint32_t)src,8);
//	OLED_ShowHexNum(3,8,(uint32_t)dest,8);
//	
//	MyDMA_Init((uint32_t)src,(uint32_t)dest,4);

//	while (1)
//	{
////		src[0] ++;
////		src[1] ++;
////		src[2] ++;
////		src[3] ++;
////		
//		OLED_ShowHexNum(2,1,src[0],2);
//		OLED_ShowHexNum(2,4,src[1],2);
//		OLED_ShowHexNum(2,7,src[2],2);
//		OLED_ShowHexNum(2,10,src[3],2);
//		
//		OLED_ShowHexNum(4,1,dest[0],2);
//		OLED_ShowHexNum(4,4,dest[1],2);
//		OLED_ShowHexNum(4,7,dest[2],2);
//		OLED_ShowHexNum(4,10,dest[3],2);
//			
//		Delay_ms(1000);
//		MyDMA_Transfer();
//		
//		OLED_ShowHexNum(2,1,src[0],2);
//		OLED_ShowHexNum(2,4,src[1],2);
//		OLED_ShowHexNum(2,7,src[2],2);
//		OLED_ShowHexNum(2,10,src[3],2);
//		
//		OLED_ShowHexNum(4,1,dest[0],2);
//		OLED_ShowHexNum(4,4,dest[1],2);
//		OLED_ShowHexNum(4,7,dest[2],2);
//		OLED_ShowHexNum(4,10,dest[3],2);
//		
//		Delay_ms(1000);
//		
//	}


/*模块初始化*/
//	OLED_Init();				//OLED初始化
//	AD_Init();					//AD初始化
//	
//	/*显示静态字符串*/
//	OLED_ShowString(1, 1, "AD0:");
//	OLED_ShowString(2, 1, "AD1:");
//	OLED_ShowString(3, 1, "AD2:");
//	OLED_ShowString(4, 1, "AD3:");
//	
//	while (1)
//	{
//		OLED_ShowNum(1, 5, AD_Value[0], 4);		//显示转换结果第0个数据
//		OLED_ShowNum(2, 5, AD_Value[1], 4);		//显示转换结果第1个数据
//		OLED_ShowNum(3, 5, AD_Value[2], 4);		//显示转换结果第2个数据
//		OLED_ShowNum(4, 5, AD_Value[3], 4);		//显示转换结果第3个数据
//		
//		Delay_ms(100);		
