
#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>

//Ctrl2******************

void I2C_Init(HardwareSerial& hs_serial);
int I2C_Write_RX8035(int i2c_Address, int register_Address, byte* data, int dataSize);
int I2C_Read_RX8035(int i2c_Address, int register_Address, int* data, int dataSize, int stop);
//void I2C_Read_RX8035_0(int i2c_Address, int register_Address, int* data, int readDataSize, int stop);
