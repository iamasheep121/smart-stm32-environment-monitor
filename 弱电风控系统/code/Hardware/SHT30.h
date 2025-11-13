#ifndef __SHT30_H
#define __SHT30_H

#include "stm32f10x.h"
	//temp:温度，-400~1250,分辨率0.1℃,精度±0.3℃
	//humi:湿度，0~1000,分辨率0.1%rh,精度±3

	// 根据模块ADDR引脚接线选择（0x44）
#define SHT30_ADDR_WRITE    0x88  // (0x44 << 1) 写地址
#define SHT30_ADDR_READ     0x89  // (0x44 << 1 | 0x01) 读地址

#define SHT30_HOT_LSB_EN 0x6D			//加热器启用
#define SHT30_HOT_LSB 0x66			//加热器禁用
#define SHT30_HOT_HSB 0x30			//加热器高八位，用于测试传感器好坏，不可长时间开启，容易影响性能，期间测量数据不算

#define SHT30_SOFTRST_CMD 0x30A2		//软复位

#define SHT30_RDSR_CMD 	0xF32D			//读取状态寄存器

#define SHT30_CLSR_CMD	0x3041			//清除状态寄存器	

// 单次测量命令 - 高重复性，时钟拉伸禁用（最常用）
#define SHT30_MEAS_HIGHREP  0x2C06

uint8_t SHT30_ReadData(float *temp, float *hum);
uint8_t SHT30_Init(void);
void CheckSHT30(void);

uint16_t SHT30_ReadStatus(void);
void Parse_Status(uint16_t status);
void SHT30_SoftReset(void);

#endif
