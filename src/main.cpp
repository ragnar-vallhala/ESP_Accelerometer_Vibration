#include <Arduino.h>
#include <Wire.h>
#include "memory.h"

#define MPU6050_ADDRESS (0x68)         // MPU6050 default I2C address
#define DATA_LENGTH 256
#define REGISTER_ACCEL_XOUT_H (0x3B)  // X-axis acceleration data high byte
#define REGISTER_ACCEL_XOUT_L (0x3C)  // X-axis acceleration data low byte
#define REGISTER_ACCEL_YOUT_H (0x3D)  // Y-axis acceleration data high byte
#define REGISTER_ACCEL_YOUT_L (0x3E)  // Y-axis acceleration data low byte
#define REGISTER_ACCEL_ZOUT_H (0x3F)  // Z-axis acceleration data high byte
#define REGISTER_ACCEL_ZOUT_L (0x40)  // Z-axis acceleration data low byte

void writeToRegister(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

float readAcceleration(uint8_t regH, uint8_t regL);

void storeData()
{
  Memory memory{}; 
  for(int i{};i<DATA_LENGTH;i++)
  {
    float x_acceleration = readAcceleration(REGISTER_ACCEL_XOUT_H, REGISTER_ACCEL_XOUT_L);
    memory.writeFloat(x_acceleration,i*4);
  }
}

void loadData()
{
  Memory memory{}; 
  for(int i{};i<DATA_LENGTH;i++)
  {
    float val = memory.readFloat(i*4);
    Serial.println(val);
  }
}


void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Initialize MPU6050
  writeToRegister(0x6B, 0x00); // Set power management register to 0 for normal operation
  writeToRegister(0x1C, 0x00); // Set accelerometer scale to ±2g
}




float readAcceleration(uint8_t regH, uint8_t regL) {
  uint8_t data[2];
  int16_t result;

  // Read the two bytes for acceleration data
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(regH);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDRESS, 2);
  
  // Combine the two bytes to form the 16-bit acceleration value
  data[0] = Wire.read();
  data[1] = Wire.read();
  result = ((int16_t)data[0] << 8) | data[1];
  
  // Convert raw value to m/s^2
  // 1 g = 9.81 m/s^2
  float acceleration_m_s2 = result / 16384.0 * 9.81;

  return acceleration_m_s2;
}




void loop() {
  Serial.println("Start");
  Serial.println(micros());
  storeData();
  Serial.println(micros());
  loadData();
  Serial.println("End");
  delay(100);
}