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

//****************************************************************************************************************
long cnt = 0;
void loop()
{
	String strTime = "";
	int iBuf[16];
	
	Serial.println("******** " + String(cnt) + " ********");
	I2C_Read_RX8035_All(0x32, iBuf);
	cnt++;
	delay(100);
}

void DataReset(int *data)
{
	int loopNum = sizeof(data) / sizeof(*data);
	for (int i = 0; i < loopNum; i++)
		data[i] = 0;
}

//****************************************************************************************************************
//****************************************************************************************************************
//****************************************************************************************************************
int GetHour()
{
	int data[16];
	int buf;
	int result = 0;
	I2C_Read_RX8035_All(0x32, data);
	buf = data[hours];
	if (buf < 0x80)
	{
		//12時間モード
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

//****************************************************************************************************************
int GetMin()
{
	int data[16];
	int result = 0;
	I2C_Read_RX8035_All(0x32, data);

	result = data[minutes] / 16 * 10;
	result = result + data[minutes] % 16;

	return result;
}

//****************************************************************************************************************
int GetSec()
{
	int data[16];
	int result = 0;
	I2C_Read_RX8035_All(0x32, data);

	result = data[seconds] / 16 * 10;
	result = result + data[seconds] % 16;

	return result;
}

//****************************************************************************************************************
//****************************************************************************************************************
//****************************************************************************************************************



