/*
    Copyright 2017 Chiehting Huang <j.huang.1985@gmail.com>
*/
#include "Arduino.h"
#include "MI78M6610PSU.h"
//#include <Wire.h>


#define I2C_ADDR 0x03

MI78M6610PSU::MI78M6610PSU(uint8_t i2cAddress) {
  _exist = false;
  _address = i2cAddress;
}

MI78M6610PSU::MI78M6610PSU() {
  _exist = false;
  _address = I2C_ADDR;
}

#if defined(ARDUINO_ARCH_ESP8266)
bool MI78M6610PSU::begin(int SDA_pin, int SCL_pin) {
    Wire.begin(SDA_pin,SCL_pin);
#else
bool MI78M6610PSU::begin() {
    Wire.begin();
#endif
    Wire.beginTransmission(_address);
    if (Wire.endTransmission() == 0) {
        _exist = true;
    }
    return _exist;
}

bool MI78M6610PSU::exist() 
{
    return _exist;
}

int32_t MI78M6610PSU::read24(uint8_t reg)
{
    int32_t x1, x2, x3;

    Wire.beginTransmission(_address);
#if ARDUINO >= 100
    Wire.write(reg);
#else
    Wire.send(reg);
#endif
    Wire.endTransmission();

    Wire.requestFrom(_address, (uint8_t) 3);
#if ARDUINO >= 100
    x1 = Wire.read();
    x2 = Wire.read();
    x3 = Wire.read();
#else
    x1 = Wire.receive();
    x2 = Wire.receive();
    x3 = Wire.receive();
#endif
    x1 <<= 16;
    x2 <<= 8;
    x3 |= x1;
    x3 |= x2;
    return x3;
}


void MI78M6610PSU::write24(uint8_t reg, uint32_t data) {
    Wire.beginTransmission(_address); // start transmission to device 

    uint8_t x1, x2, x3;
   // data = 0xFFFFFFFF;
    
    x1 = (data >> 16 ) & 0xFF;
    x2 = (data >>  8 ) & 0xFF;
    x3 = (data >>  0 ) & 0xFF;
    

#if (ARDUINO >= 100)
    Wire.write(reg); // sends register address to read from
    Wire.write(x1);  // write data
    Wire.write(x2);  // write data
    Wire.write(x3);  // write data
#else
    Wire.send(reg); // sends register address to read from
    Wire.send(x1);  // write data
    Wire.send(x2);  // write data
    Wire.send(x3);  // write data
#endif

    Wire.endTransmission();
}

