/*
  Copyright 2017 Chiehting Huang <j.huang.1985@gmail.com>

*/
#ifndef MI78M6610PSU_h
#define MI78M6610PSU_h

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifdef __AVR_ATtiny85__
 #include "TinyWireM.h"
 #define Wire TinyWireM
#elif defined(ARDUINO_ARCH_ESP8266)
 #include <Wire.h>
#else
 #include <avr/pgmspace.h>
 #include <Wire.h>
#endif


// I2C commands
#define COMMAND_REG           0x00
#define FIRMWARE_REG          0x01

#define ALARMSET_REG          0x04

#define TEMERATURE_REG        0x06
#define VRMS_REG              0x09

#define ALARMSTATUS_REG       0x10

#define IRMS_REG              0x0A
#define WATT_REG              0x0B
#define POWERFACTOR_REG       0x0D
#define FREQUENCY_REG         0x0E

#define DIOSTATE_REG         0x6D 

#define IRMS_UNSCALE_REG      0x72
#define VRMS_UNSCALE_REG      0x73
#define FREQ_UNSCALE_REG      0x78

#define ISCALE_REG            0x5F
#define VSCALE_REG            0x60
#define PSCALE_REG            0x61
#define PFSCALE_REG           0x62
#define FSCALE_REG            0x63


class MI78M6610PSU
{
  public:
    MI78M6610PSU();
    MI78M6610PSU(uint8_t i2cAddress);
#if defined(ARDUINO_ARCH_ESP8266)
    bool begin(int SDA_pin, int SCL_pin);
#else
    bool begin();
#endif
    bool exist();
    uint32_t Firmware()  { return read24(FIRMWARE_REG); }
    uint32_t DioState()  { return read24(DIOSTATE_REG); }
    uint32_t AlarmState()  { return read24(ALARMSTATUS_REG); }
    uint32_t Vrms()      { return read24(VRMS_REG); }
    uint32_t Irms()      { return read24(IRMS_REG); }
    int32_t Watt()      { return ( read24(WATT_REG) << 8 ) >> 8; }
    int32_t PwrFactor() { return ( read24(POWERFACTOR_REG) << 8 ) >> 8; }
    int32_t Freq()      { return ( read24(FREQUENCY_REG) << 8 ) >> 8; }
    
    

    int32_t VrmsUnscale()      { return ( read24(VRMS_UNSCALE_REG) << 8 ) >> 8; }
    int32_t IrmsUnscale()      { return ( read24(IRMS_UNSCALE_REG) << 8 ) >> 8; }
    int32_t FreqUnscale()      { return ( read24(FREQ_UNSCALE_REG) << 8 ) >> 8; }
  
    void setIscale(uint32_t scale)  { write24(ISCALE_REG, scale); }
    void setVscale(uint32_t scale)  { write24(VSCALE_REG, scale); }
    void setPscale(uint32_t scale)  { write24(PSCALE_REG, scale); }
    void setPFscale(uint32_t scale) { write24(PFSCALE_REG, scale); }
    void setFscale(uint32_t scale)  { write24(FSCALE_REG, scale); }

    void setAlarmSet(uint32_t v)  { write24(ALARMSET_REG, v); }
    void setRelay(bool on) { write24(ALARMSET_REG, (uint32_t) on << 2); }
        
  private:
    void     write24(uint8_t reg, uint32_t data);
    int32_t  read24(uint8_t reg);
    
    bool    _exist;
    uint8_t _address;
};

#endif

