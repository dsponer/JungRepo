// WheelData.h

#ifndef _WHEELDATA_h
#define _WHEELDATA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class WheelData
{
 protected:


 public:
	 WheelData();
	 bool get_data_from_string(String data);
	 void pack(unsigned char* buff);
	 
private:
	float JointArray[7] = {0, 0, 0, 0, 0, 0, 0};
	bool LaserON = false;

};


#endif

