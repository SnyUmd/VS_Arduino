#include <Arduino.h>
#include <time.h>
#include "def.h"
#include "Init.h"
#include "LedCtrl.h"
#include "Bzctrl.h"
#include "I2C_Ctrl.h"
#include "Bt.h"

//extern float flSound[][12];
//extern int beat;
//********************************************************
void setup()
{
	Initialize_Port();

	LedFlash(50, 3, false);

	//InitBz();
	BzGoUp(10, 10);
	I2C_Init();
	//Serial.begin(9600);

	InitBt("Buzzer");
}

//********************************************************
void loop()
{
	//int data[5];
	//String strBuf = "a";
	//bool blDataRead = false;
	//I2C_Read_RX8035(0x32, 0x0F, data, 1, 1);
	// strBuf = String((char*)data);
	// if(data[0] != 0x00)
	//   strBuf = "OK";
	// else
	//   strBuf = "NG";
	//Serial.println(strBuf);
	 //BzStop(200);

	//Bz_DragonQuest_Preface();

	//BzStop(200);

	// LedFlash(50,3,false);
	// BzGoDown(10,10);
	//BzTest();
	//BzTest2();

	//digitalWrite(26, !digitalRead(26));

	//delay(2000);
	//while(1);
	


	//int data[5];
	//int LoopNum;
	//DataReset(data);
	//LoopNum = I2C_Read_RX8035(0x32, 0x00, data, 1, 1);
	////ESP32_BLSerial_Write(String(LoopNum) + "sec", true);
	//ESP32_BLSerial_Write("sec", false);
	////for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
	//for (int i = 0; i < LoopNum; i++)
	//	ESP32_BLSerial_Write(String(data[i]), true);

	//DataReset(data);
	//LoopNum = I2C_Read_RX8035(0x32, 0x01, data, 1, 1);
	////ESP32_BLSerial_Write("Control2DataNum:" + String(LoopNum), true);
	//ESP32_BLSerial_Write("min:", false);
	////for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
	//for (int i = 0; i < LoopNum; i++)
	//	ESP32_BLSerial_Write(String(data[i]), true);

	String strTime = "";

	//int iMin = GetMin();
	//delay(200);
	//int iSecd = GetSec();
	//delay(200);
	//strTime = "'" + String(iMin) + "'" + String(iSecd);

	strTime = GetTime();

	ESP32_BLSerial_Write(strTime, true);
	delay(900);


	//delay(1000);
}

void DataReset(int *data)
{
	int loopNum = sizeof(data) / sizeof(*data);
	for (int i = 0; i < loopNum; i++)
		data[i] = 0;
}

//********************************************************
int GetMin()
{
	int iMin[5];
	int result = 0;
	I2C_Read_RX8035(0x32, 0x01, iMin, 1, 1);

	result = iMin[0] / 16 * 10;
	result = result + iMin[0] % 16;

	return result;
}

//********************************************************
int GetSec()
{
	int iMin[5];
	int result = 0;
	I2C_Read_RX8035(0x32, 0x00, iMin, 1, 1);

	result = iMin[0] / 16 * 10;
	result = result + iMin[0] % 16;

	return result;
}

//********************************************************
String GetTime()
{
	int iTime[5];
	int iH, im, is;
	String result = "";
	I2C_Read_RX8035(0x32, 0x00, iTime, 3, 1);

	iH = iTime[2] / 16 * 10;
	iH += iTime[2] % 16;

	im = iTime[1] / 16 * 10;
	im += iTime[1] % 16;

	is = iTime[0] / 16 * 10;
	is += iTime[0] % 16;

	return "'" + String(iH) + "'" + String(im) + "'" + String(is);
}
//****************************************************************************************************************
//****************************************************************************************************************
//****************************************************************************************************************



