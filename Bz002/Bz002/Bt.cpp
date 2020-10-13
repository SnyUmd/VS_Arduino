// 
// 
// 

#include "Bt.h"
#include <exception>

BluetoothSerial btSerial;

//*******************************************************************************************
bool InitBt(String strBtName)
{
	if (!btSerial.begin(strBtName))
		return false;
	else
		return true;
}

////*******************************************************************************************
//bool ESP32_BLSerial_Set(BluetoothSerial& BS_Serial, String strBT_Name)
//{
//	if (!BS_Serial.begin(strBT_Name))
//		return false;
//	else
//		return true;
//}

//*******************************************************************************************
int ESP32_BLSerial_Read()
{
	if (0 < btSerial.available())
		return btSerial.read();
	else
		return -1;
}

//*******************************************************************************************
bool ESP32_BLSerial_Write(String strSendValue, bool blNewLine)
{
	try
	{
		if (blNewLine)
			//BT_Serial.println(strSendValue);
			btSerial.println(strSendValue);
		else
			//BT_Serial.print(strSendValue);
			btSerial.print(strSendValue);
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}

}

