#define ADDRESS_RX8035 0x32

#define CTRL1_ADDRESS 0x0E
#define CTRL2_ADDRESS 0x0F

#include <Arduino.h>
#include <Wire.h>
#include "I2C_Ctrl.h"

//RX8035********************
////Ctrl1******************
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


//********************************************************************************
void I2C_Init()
{
    Wire.begin();
    Serial.begin(115200);
}

//********************************************************************************
int I2C_Write_RX8035(int i2c_Address, int register_Address, byte *data, int dataSize)
{
    //char w_Adr = i2c_Address << 1  + 1;
    char reg_Adr = register_Address << 4;

    Wire.beginTransmission(i2c_Address);
	Wire.write(register_Address);
	//Wire.write(data);
	Wire.write(data, dataSize);
    
    // for (int i = 0; i < dataSize; i++)
	// {
	// 	Wire.write(data[i]);
	// }
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
int I2C_Read_RX8035(int i2c_Address, int register_Address, int *data, int dataSize, int stop)
{
    String strBuf;
    int reg_Adr = register_Address << 4;
    reg_Adr += 4;//読出し短縮方法
    //i2c_Address：デバイスの7bitアドレス
	Wire.beginTransmission(i2c_Address);
	Wire.write(reg_Adr);
	Wire.endTransmission();

	Wire.requestFrom(i2c_Address, dataSize, stop);
    int loopNum = Wire.available();//バッファにあるデータ数を取得
    //data = new int[loopNum];

	for (int i = 0; i < loopNum; i++)
	{
		data[i] = Wire.read();
        //strBuf = String(data[i]);
        Serial.println(data[i]);
	}
	Wire.endTransmission();

    return loopNum;
}

//********************************************************************************
//void I2C_Read_RX8035_0(int i2c_Address, int register_Address, int *data, int readDataSize, int stop)
//{
//	int reg_Adr = register_Address << 4;
//	reg_Adr += 4;
//	//i2c_Address：デバイスの7bitアドレス
//	Wire.beginTransmission(i2c_Address);
//	Wire.write(reg_Adr);
//	Wire.endTransmission();
//	//Wire.requestFrom(id, datasize, false);
//
//	//i2c_Address:I2Cデバイスの7bitアドレス
//	//dataSize:要求バイト数
//	//stop：true-要求後バス要求までメッセージ停止　false-通信継続して送信を継続
//	Wire.requestFrom(i2c_Address, readDataSize, stop);
//	int loopNum = Wire.available();
//	for (int i = 0; i < loopNum; i++)
//		data[i] = Wire.read();
//	Wire.endTransmission();
//}