// 
// 
// 

#include "WheelData.h"



WheelData::WheelData()
{
	
}

bool WheelData::get_data_from_string(String data)
{
	Serial.println(data);
	Serial.println(" ");
	if (data.substring(1, 6) = "\"J1:\":")
	{
		for (int i = 0; i < 7; i++)
		{
			data.remove(0, data.indexOf(":") + 1);
			data.trim();
			JointArray[i] = data.substring(0, data.indexOf(",")).toFloat();
			data.remove(0, data.indexOf(",") + 1);
			data.trim();
			Serial.println(JointArray[i]);
		}

		data.remove(0, data.indexOf(":") + 1);
		data.trim();
		if (data.substring(0, data.indexOf("}")) == "true")
		{
			LaserON = true;
			Serial.println("true");
		}
		else
		{
			LaserON = false;
			Serial.println("false");
		}
		Serial.println(" ");
		return true;
	}
	
	return false;

	//Serial.println(sizeof(JointArray));
	//Serial.println(sizeof(LaserON));
	
}

void WheelData::pack(unsigned char* buff)
{
	memcpy(buff, &JointArray, sizeof(JointArray));
	memcpy(buff + 28, &LaserON, sizeof(LaserON));
}
