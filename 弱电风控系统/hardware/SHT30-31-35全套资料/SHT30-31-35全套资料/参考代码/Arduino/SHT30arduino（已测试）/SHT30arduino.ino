/****************************************sht3x温湿度 part****************************************/
/*
  接线：
  3.3V------VCC
  GND------GND
  SCL------SCL
  SDA------SDA
*/
#include <Arduino.h>                                                        //调用库文件                 
#include <Wire.h>                                                           //调用库文件
#include "Adafruit_SHT31.h"                                                 //调用库文件
 
Adafruit_SHT31 sht31 = Adafruit_SHT31();                                    //实例化对象
 
#define sht3xTimeInterval 1000                                              //检测一次的时间间隔                   
float sht3xTemp = 0, sht3xHumi = 0;                                         //存储温度值和湿度值。
unsigned long sht3xTimes = 0;                                               //记录设备运行时间
/****************************************set up and loop part*********************************/
void setup() {
  Serial.begin(9600);                                                       //设置串口波特率为9600
 
  if (! sht31.begin(0x44)) {                                                //传感器IIC初始化
    while (millis() - 1000) {
      Serial.println("找不到SHT31");                                         //串口打印对应的值
    }
  }
  Serial.println("设备上线！");
}
void loop() {
  getData();                                                                //获取温湿度值。
}
/****************************************sht3x温湿度 part****************************************/
/*获取温度和湿度函数*/
void getData() {
  if (millis() - sht3xTimes >= sht3xTimeInterval) {                         //一定时间执行一次
    sht3xTimes = millis();
 
    sht3xTemp = sht31.readTemperature();                                    //获取温度数据
    sht3xHumi = sht31.readHumidity();                                       //获取湿度数据
 
    Serial.print("温度：");                                                  //串口打印对应的值
    Serial.print(sht3xTemp, 1);                                             //保留一位小数
    Serial.print(" (C), ");                                                 //串口打印对应的值
    Serial.print("湿度：");                                                  //串口打印对应的值
    Serial.print(sht3xHumi, 1);                                             //保留一位小数
    Serial.println(" (%)。");                                               //串口打印对应的值
  }
}