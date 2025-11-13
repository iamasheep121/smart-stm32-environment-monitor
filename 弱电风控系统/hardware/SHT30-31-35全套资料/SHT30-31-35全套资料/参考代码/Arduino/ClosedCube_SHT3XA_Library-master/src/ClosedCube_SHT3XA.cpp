/*

Arduino Library for Sensirion SHT3X-ARP Analog Humidity & Temperature Sensors

---

The MIT License (MIT)

Copyright (c) 2015 ClosedCube Limited

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "ClosedCube_SHT3XA.h"

ClosedCube_SHT3XA::ClosedCube_SHT3XA(float refVoltage, int pinT, int pinRH) : _refVoltage(refVoltage), _pinT(pinT), _pinRH(pinRH)
{
}

float ClosedCube_SHT3XA::readTempC() {
	int tValue = analogRead(_pinT);
	return -66.875 + 218.75*(tValue*0.0049) / _refVoltage;
}

float ClosedCube_SHT3XA::readTempF() {
	int tValue = analogRead(_pinT);
	return -88.375 + 393.75*(tValue*0.0049) / _refVoltage;
}

float ClosedCube_SHT3XA::readHumidity() {
	int rhValue = analogRead(_pinRH);
	return -12.5 + 125 * (rhValue*0.0049) / _refVoltage;
}


