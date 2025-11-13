/*

This is example for SHT3X-DIS Digital Humidity & Temperature Sensors Arduino Library
ClosedCube SHT30D-EASY or ClosedCube SHT31D-PRO breakout modules

Initial Date: 06-Oct-2015

Hardware connections for Arduino Uno:
	VDD to 3.3V DC
	SDA to A4
	SCL to A5
	GND to common groud

MIT License

*/

#include <Wire.h>
#include <ClosedCube_SHT3XD.h>

ClosedCube_SHT3XD sht3xd;

void setup()
{
	Serial.begin(9600);
	Serial.println("ClosedCube SHT3XD Library - Who I Am Example");
	
	sht3xd.begin(0x44);
}

void loop()
{
	Serial.print("SHT3XD Serial #");
	Serial.println(sht3xd.readSerialNumber());
	delay(250);	
}

