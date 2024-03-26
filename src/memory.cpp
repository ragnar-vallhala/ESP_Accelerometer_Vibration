#include "memory.h"

void Memory::writeFloat(float value, unsigned int address)
{
    unsigned char* data = float2byte(value);
    EEPROM.write(address,data[0]);
    EEPROM.write(address + 1,data[1]);
    EEPROM.write(address + 2,data[2]);
    EEPROM.write(address + 3,data[3]);
    delete[] data;
}

float Memory::readFloat(unsigned int address)
{
    unsigned char* data = new unsigned char[4];
    for (int i=0 ;i<4;i++)
    {
        data[i] = EEPROM.read(address+i);
    }
    float result = byte2float(data);
    delete[] data;
    return result;
}

unsigned char *Memory::float2byte(float &a)
{
    unsigned int b = *((unsigned int*)&a);
    unsigned char *c = new unsigned char[4];
    c[0] = (b>>24)&0xff;
    c[1] = (b>>16)&0xff;
    c[2] = (b>>8)&0xff;
    c[3] = (b)&0xff;
    return c;
}

float Memory::byte2float(unsigned char *c)
{
    unsigned int d {};
    d = d|(((unsigned int)c[0])<<24);
    d = d|(((unsigned int)c[1])<<16);
    d = d|(((unsigned int)c[2])<<8);
    d = d|(((unsigned int)c[3]));
    float m = *((float*)&d);
    return m;
}

Memory::Memory()
{
    EEPROM.begin(4096);
}

Memory::~Memory()
{
    EEPROM.end();
}
