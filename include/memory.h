#pragma once
#include <EEPROM.h>

class Memory{
public:
    Memory();
    ~Memory();
    void writeFloat(float value, unsigned int address);
    float readFloat(unsigned int address);
    
private:
    unsigned char* float2byte(float &a);
    float byte2float(unsigned char* c);
};