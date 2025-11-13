#include "sht30.h"
#include "delay.h"
#include "usart.h"

extern void MyI2C_Init(void);
extern void MyI2C_Start(void);
extern void MyI2C_Stop(void);
extern void MyI2C_SendByte(uint8_t Byte);
extern uint8_t MyI2C_ReceiveByte(void);
extern uint8_t MyI2C_ReceiveAck(void);
extern void MyI2C_SendAck(uint8_t AckBit);

/**
 * @brief  初始化SHT30
 * @retval 0:成功 1:失败
 */
uint8_t SHT30_Init(void)
{
    MyI2C_Init(); 
    
    MyI2C_Start();
    MyI2C_SendByte(SHT30_ADDR_WRITE);
    if(MyI2C_ReceiveAck()) return 1;
    MyI2C_SendByte(0x30); // 软复位命令高字节
    if(MyI2C_ReceiveAck()) return 1;
    MyI2C_SendByte(0xA2); // 软复位命令低字节
    if(MyI2C_ReceiveAck()) return 1;
    MyI2C_Stop();
    
    Delay_ms(2); // 等待软复位完成
    return 0;
}


// I2C设备检测
//void CheckSHT30(void)
//{
//    printf("开始检测SHT30...\r\n");
//    
//    MyI2C_Start();
//    MyI2C_SendByte(0x44<<1);  // SHT30写地址
//	
//    
//    if(MyI2C_ReceiveAck() == 0) {
//        printf(" SHT30响应正常！\r\n");
//    } else {
//        printf(" SHT30无响应，检查接线！\r\n");
//    }
//    
//    MyI2C_Stop();
//}

/**
 * @brief  读取状态寄存器
 * @retval 状态寄存器的值
 */

uint16_t SHT30_ReadStatus(void)
{
    uint8_t data[3];
    
    // 1. 发送读状态寄存器命令
    MyI2C_Start();
    MyI2C_SendByte(SHT30_ADDR_WRITE);
    MyI2C_SendByte(0xF3);  // 命令高字节
    MyI2C_SendByte(0x2D);  // 命令低字节
    MyI2C_Stop();
    
    // 2. 等待命令处理
    Delay_ms(1);
    
    // 3. 读取3字节状态数据
    MyI2C_Start();
    MyI2C_SendByte(SHT30_ADDR_READ);
    
    data[0] = MyI2C_ReceiveByte();  // 状态高字节
    MyI2C_SendAck(0);               // ACK
    
    data[1] = MyI2C_ReceiveByte();  // 状态低字节
    MyI2C_SendAck(0);               // ACK
    
    data[2] = MyI2C_ReceiveByte();  // CRC字节
    MyI2C_SendAck(1);               // NACK（最后一个字节）
    
    MyI2C_Stop();
    
    // 4. 组合成16位状态值（跳过CRC校验）
    return (data[0] << 8) | data[1];
}


/**
 * @brief  处理各种状态寄存器的情况，已弃用
 * @retval 串口打印显示
 */
//void Parse_Status(uint16_t status)
//{
//    // 检查报警状态
//    if (status & (1 << 15)) {
//        printf("有未处理的报警\n");
//    }
//    
//    // 检查加热器状态
//    if (status & (1 << 13)) {
//        printf("加热器正在运行\n");
//    }
//    
//    // 检查系统复位状态
//    if (status & (1 << 4)) {
//        printf("检测到系统复位\n");
//    }
//    
//    // 检查命令执行状态
//    if (status & (1 << 1)) {
//        printf("上一个命令执行失败\n");
//    }
//}

/**
 * @brief  软复位SHT30
 * @retval 0:成功, 1:失败
 */
//void SHT30_SoftReset(void)
//{
//    MyI2C_Start();
//    MyI2C_SendByte(SHT30_ADDR_WRITE);
//	
//    if(MyI2C_ReceiveAck() == 1)
//	{
//		MyI2C_Stop();
//		return;
//	}		
//	MyI2C_SendByte(SHT30_SOFTRST_CMD >> 8);
//	if(MyI2C_ReceiveAck() == 1)
//	{
//		MyI2C_Stop();
//		return;
//	}	
//	MyI2C_SendByte(SHT30_SOFTRST_CMD & 0xFF);  // 低字节 0xA2
//    if(MyI2C_ReceiveAck() == 1) 
//	{
//        MyI2C_Stop();
//        return;
//	}
//    MyI2C_Stop();
//    Delay_ms(2);
//	 
//}

void SHT30_SoftReset(void)
{
    MyI2C_Start();
    
    MyI2C_SendByte(0x88);
    if(MyI2C_ReceiveAck() == 1) goto error;
    
    MyI2C_SendByte(0x30);
    if(MyI2C_ReceiveAck() == 1) goto error;
    
    MyI2C_SendByte(0xA2);
    if(MyI2C_ReceiveAck() == 1) goto error;
    
    MyI2C_Stop();
    Delay_ms(2);
    return;
    
error:
    MyI2C_Stop();
    UsartPrintf(USART1,"软复位失败\n");
}

/**
 * @brief  读取温湿度数据
 * @param  temp: 温度值指针
 * @param  hum: 湿度值指针
 * @retval 0:成功, 1:失败
 */
uint8_t SHT30_ReadData(float *temp, float *hum)
{
    uint8_t i, data[6];
    uint16_t temp_raw, hum_raw;
    
    // 1. 发送测量命令
    MyI2C_Start();
    MyI2C_SendByte(SHT30_ADDR_WRITE);
    if(MyI2C_ReceiveAck()) goto error;
    
    MyI2C_SendByte(SHT30_MEAS_HIGHREP >> 8);   // 命令高字节 0x2C
    if(MyI2C_ReceiveAck()) goto error;
    
    MyI2C_SendByte(SHT30_MEAS_HIGHREP & 0xFF); // 命令低字节 0x06
    if(MyI2C_ReceiveAck()) goto error;
    
    MyI2C_Stop();
    
    // 2. 等待测量完成
    Delay_ms(20);
    
    // 3. 读取6字节数据
    MyI2C_Start();
    MyI2C_SendByte(SHT30_ADDR_READ);
    if(MyI2C_ReceiveAck()) goto error;
    
    // 读取前5字节，每字节后发ACK
    for(i = 0; i < 5; i++) {
        data[i] = MyI2C_ReceiveByte();
        MyI2C_SendAck(0); // ACK
    }
    // 读取第6字节，发NACK
    data[5] = MyI2C_ReceiveByte();
    MyI2C_SendAck(1); // NACK
    
    MyI2C_Stop();
    
    // 4. 组合数据（跳过CRC校验）
    temp_raw = (data[0] << 8) | data[1];
    hum_raw  = (data[3] << 8) | data[4];
    
    // 5. 转换为实际值
    *temp = -45.0f + 175.0f * ((float)temp_raw / 65535.0f);
    *hum  = 100.0f * ((float)hum_raw / 65535.0f);
    
    return 0; 

error:
    MyI2C_Stop();
    return 1; // 集中失败处理
}

//到时候项目全弄好就封装在一个模块里面
//while(1) {
//        if(SHT30_ReadData(&temperature, &humidity) == 0) {
//            // 打印数据
//            char buffer[64];
//            sprintf(buffer, "温度: %.2fC  湿度: %.2f%%\r\n", temperature, humidity);
//            Serial_SendString(buffer);
//			OLED_ShowNum(1,3,temperature,2,OLED_6X8);
//			
//			OLED_ShowNum(4,3,humidity,2,OLED_6X8);
//			OLED_Update();
//			
//        } else {
//            Serial_SendString("读取失败\r\n");
//        }
//        Delay_ms(1000); // 1秒读一次
//    }
