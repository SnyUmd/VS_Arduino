#define ADDRESS_RX8035 0x32

#define CTRL1_ADDRESS 0x0E
#define CTRL2_ADDRESS 0x0F

//#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include "I2C_Ctrl.h"
#include "LedCtrl.h"

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

//RX8035********************
//Ctrl1-----------------------------------------------------------------------------------------------
int resistorE7_MoAlarm = 0 << 7;//アラーム月
int resistorE6_WkAlarm = 0 << 6;//アラーム曜

int resistorE5_DBSL = 0 << 5;//デバウンス時間切替　0：1996ms  1：35mS

int resistorE4_EventEn = 0 << 4;//イベントディテクションイネーブル

int resistorE3_Test = 0 << 3;//ICテスト用

int resistorE2_CT2 = 0 << 2;//定周期割込み選択
int resistorE1_CT1 = 0 << 1;//定周期割込み選択
int resistorE0_CT0 = 0 << 0;//定周期割込み選択
//0 0 0：OFF
//0 0 1：L固定
//0 1 0：2Hz
//0 1 1：1Hz
//1 0 0：1秒毎
//1 0 1：1分毎
//1 1 0：1時間毎
//1 1 1：1月毎

//Ctrl2-----------------------------------------------------------------------------------------------
int resistorF7_Bank = 0 << 7;
int resistorF6_Vdetect = 0 << 6;//※書込み時は0固定　
								//※秒桁を書き込んだ後は必ず0を書き込む事

int resistorF5_Xstep = 0 << 5;//発振停止を検出で0クリアするまで1を維持
int resistorF4_PowerOnFlg = 0 << 4;//初期投入で0クリアまで1を維持
int resistorF3_EdgeFlg = 0 << 3;//EVIN1,2の端子からの入力によりタイムスタンプを記録
int resistorF2_CTFG = 0 << 2;
int resistorF1_WkAlarmFlg = 0 << 1;
int resistorF0_MoAlarmFlg = 0;

HardwareSerial HwSerial = Serial;


//********************************************************************************
void I2C_Init(HardwareSerial& hs_serial)
{
	HwSerial = hs_serial;
	Wire.begin();
}


//********************************************************************************
void Init_RX8035()
{
	byte Write_Ctrl1_Data[1];
	byte Write_Ctrl2_Data[1];

	Write_Ctrl1_Data[0] = resistorE7_MoAlarm +
		resistorE6_WkAlarm +
		resistorE5_DBSL +
		resistorE4_EventEn +
		resistorE3_Test +
		resistorE2_CT2 +
		resistorE1_CT1 +
		resistorE0_CT0;

	Write_Ctrl2_Data[0] = resistorF7_Bank +
		resistorF6_Vdetect +
		resistorF5_Xstep +
		resistorF4_PowerOnFlg +
		resistorF3_EdgeFlg +
		resistorF2_CTFG +
		resistorF1_WkAlarmFlg +
		resistorF0_MoAlarmFlg;
	//Serial.println("Ctrl1 = " + String(Write_Ctrl1_Data[0]));
	//Serial.println("Ctrl2 = " + String(Write_Ctrl2_Data[0]));

	byte byBuf[1];

	byBuf[0] = { 0x00 };
	if (I2C_Write_RX8035(ADDRESS_RX8035, 0x02, byBuf, 1) != 0)
	{
		HwSerial.println("hour write Err");

		while (1)
		{
			LedFlash(50, 3, false);
		}
	}
	else
		HwSerial.println("Sec write success");

	byBuf[0] = { 0x11 };
	if (I2C_Write_RX8035(ADDRESS_RX8035, 0x01, byBuf, 1) != 0)
	{
		HwSerial.println("min write Err");

		while (1)
		{
			LedFlash(50, 3, false);
		}
	}
	else
		HwSerial.println("Sec write success");

	byBuf[0] = { 0x30 };
	if (I2C_Write_RX8035(ADDRESS_RX8035, 0x00, byBuf, 1) != 0)
	{
		HwSerial.println("min write Err");

		while (1)
		{
			LedFlash(50, 3, false);
		}
	}
	else
		HwSerial.println("Sec write success");


	//---------------------------------------------

	if (I2C_Write_RX8035(ADDRESS_RX8035, CTRL1_ADDRESS, Write_Ctrl1_Data, 1) != 0)
	{
		HwSerial.println("Ctrl1 write Err");

		while (1)
		{
			LedFlash(50, 3, false);
		}
	}
	else
		HwSerial.println("Ctrl1 write success");

	if (I2C_Write_RX8035(ADDRESS_RX8035, CTRL2_ADDRESS, Write_Ctrl2_Data, 1) != 0)
	{
		HwSerial.println("Ctrl2 write Err");

		while (1)
		{
			LedFlash(50, 3, false);
		}
	}
	else
		HwSerial.println("Ctrl2 write success");

}




//********************************************************************************
int I2C_Write(int i2c_Address, int register_Address, byte *data, int writeDataSize)
{
	Wire.beginTransmission(i2c_Address);
	Wire.write(register_Address);
	Wire.write(data, writeDataSize);

	return Wire.endTransmission();
	// 0: 成功
	// 1: 送信バッファ溢れ
	// 2: アドレス送信時にNACKを受信
	// 3: データ送信時にNACKを受信
	// 4: その他エラー
}

//********************************************************************************
bool I2C_Read(int i2c_Address, int register_Address, int *data, int readDataSize)
{
	//これはいらないかも　何かでやってみて確認---------------------
	//読込むレジスタアドレス指定の書き込み
	Wire.beginTransmission(i2c_Address);
	Wire.write(register_Address);
	if (Wire.endTransmission() > 0)
		return false;
	//-------------------------------------------------------------

	Wire.requestFrom(i2c_Address, readDataSize);
	//int loopNum = Wire.available();//バッファにあるデータ数を取得

	int cnt = 0;
	while (Wire.available())
	{
		data[cnt] = Wire.read();
		HwSerial.print("data " + String(cnt) + " = ");
		HwSerial.println(data[cnt]);
		cnt++;
	}
	Wire.endTransmission();

	return true;//データ数を返す
}







//********************************************************************************
int I2C_Write_RX8035(int i2c_Address, int register_Address, byte *data, int dataSize)
{
	char reg_Adr = register_Address << 4;

	Wire.beginTransmission(i2c_Address);
	Wire.write(reg_Adr);
	//Wire.write(data);
	Wire.write(data, dataSize);

	return Wire.endTransmission();
	// 0: 成功
	// 1: 送信バッファ溢れ
	// 2: アドレス送信時にNACKを受信
	// 3: データ送信時にNACKを受信
	// 4: その他エラー
}

//********************************************************************************
//i2c_Address:I2Cデバイスの7bitアドレス
//dataSize:要求バイト数
//stop：true-要求後バス要求までメッセージ停止　false-通信継続して送信を継続
//int I2C_Read_RX8035(int i2c_Address, int register_Address, int *data, int dataSize, int stop)
int I2C_Read_RX8035_All(int i2c_Address,  int *data)
{
	Wire.requestFrom(i2c_Address, 16);
	int loopNum = Wire.available();//バッファにあるデータ数を取得

	int cnt = 0;
	int num = 15;
	while (Wire.available())
	{
		if (cnt == 0)
		{
			data[15] = Wire.read();
			HwSerial.print("data 15 = ");
			HwSerial.println(data[15]);
		}
		else
		{
			data[cnt - 1] = Wire.read();
			HwSerial.print("data " + String(cnt - 1) + " = ");
			HwSerial.println(data[cnt - 1]);
		}
		cnt++;
	}
	Wire.endTransmission();

	return loopNum;
}



//********************************************************************************
String GetTime(int *data)
{
	int buf;
	int result = 0;
	String strRtn = "";

	//時----------------------------------------------
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
	strRtn += "'" + String(result);

	//分----------------------------------------------
	buf = data[minutes];
	result = data[minutes] / 16 * 10;
	result = result + data[minutes] % 16;
	strRtn += "'" + String(result);

	//秒----------------------------------------------
	buf = data[seconds];
	result = data[seconds] / 16 * 10;
	result = result + data[seconds] % 16;
	strRtn += "'" + String(result);

	return strRtn;
}