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





	int data[5];
	int LoopNum = I2C_Read_RX8035(0x32, 0x0F, data, 1, 1);
	ESP32_BLSerial_Write("Data:" + String(LoopNum), true);
	//for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
	for (int i = 0; i < LoopNum; i++)
		ESP32_BLSerial_Write(String(data[i]), true);

	delay(2000);

}
//****************************************************************************************************************
//****************************************************************************************************************
//****************************************************************************************************************



