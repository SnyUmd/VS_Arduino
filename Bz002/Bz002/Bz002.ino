#include <Arduino.h>
#include <time.h>
#include "def.h"
#include "Init.h"
#include "LedCtrl.h"
#include "Bzctrl.h"
#include "I2C_Ctrl.h"
#include "Bt.h"
#include "clsRtcList.h"

enum enmRtcData
{
	seconds = 0,
	minutes,
	hours,
	day_of_week,
	day_of_month,
	month,
	years,
	digiral_offset,
	alarm_wk_minute,
	alarm_wk_hour,
	alarm_wk_day_of_week,
	alarm_mo_minute,
	alarm_mo_hour,
	ram,
	ctrl1,
	ctrl2
};

//extern float flSound[][12];
//extern int beat;
//********************************************************
void setup()
{
	Serial.begin(115200);
	Serial.println("Serial set succes");

	Initialize_Port();

	LedFlash(50, 3, true);

	//InitBz();
	BzGoUp(10, 10);

	I2C_Init(Serial);
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
	int iBuf[16];

	/*int iHour = GetHour();
	delay(200);
	int iMin = GetMin();
	delay(200);*/
	//int iSecd = GetSec();
	//delay(200);
	//strTime = "'" + String(iHour) + "'" + String(iMin) + "'" + String(iSecd);
	//strTime = String(iSecd);

	//ESP32_BLSerial_Write(strTime, true);
	//delay(350);

	//I2C_Read_RX8035(0x32, 0x0e, iBuf, 1);
	//I2C_Read_RX8035(0x32, 0x0d, iBuf, 1);

	//I2C_Read_RX8035(0x32, 0x0f, iBuf, 1);
	//I2C_Read_RX8035(0x32, 0x00, iBuf, 1);
	//I2C_Read_RX8035(0x32, 0x01, iBuf, 1);

	I2C_Read_RX8035(0x32, 0x00, iBuf, 16);

	delay(1000);
}

void DataReset(int *data)
{
	int loopNum = sizeof(data) / sizeof(*data);
	for (int i = 0; i < loopNum; i++)
		data[i] = 0;
}

//********************************************************
int GetHour()
{
	int iHour[2] = { 0,0 };
	int buf;
	int result = 0;
	I2C_Read_RX8035(0x32, 0x02, iHour, 1);
	buf = iHour[0];
	if (buf < 0x80)
	{
		//12ŽžŠÔƒ‚[ƒh
		if (buf < 0x20)
		{
			Serial.println("mode 12 AM");
		}
		else
		{
			Serial.println("mode 12 PM");
			buf = buf - 0x20;
			result = 12;
		}

		result += buf / 16 * 10;
		result += buf % 16;
	}
	else
	{
		Serial.println("mode 24");
		buf -= 0x80;
		result = buf / 16 * 10;
		result = result + buf % 16;
	}



	return result;
}

//********************************************************
int GetMin()
{
	int iMin[2];
	int result = 0;
	I2C_Read_RX8035(0x32, 0x01, iMin, 1);

	result = iMin[0] / 16 * 10;
	result = result + iMin[0] % 16;

	return result;
}

//********************************************************
int GetSec()
{
	int iMin[1];
	int result = 0;
	I2C_Read_RX8035(0x32, 0x00, iMin, 1);

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
	I2C_Read_RX8035(0x32, 0x00, iTime, 3);

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



