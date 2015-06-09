// MS5803.h

#ifndef _MS5803_h
#define _MS5803_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class MS5803
{
 private:


 public:
	void sendCommand(byte command);
	void device_setup();
	void device_loop();
	long readAdcPreassure();
};

//extern MS5803 MS5803;


// definitions 
#define MS5803_I2C_ADDRESS 0x76 // 7-bit I2C address of the MS5803

//const int DevAddress = MS5803_I2C_ADDRESS;  

// defineing commands that can be sent to the 5803
// Page 7 of the data sheet

#define MS5803_reset 0x1E
#define MS5803_D1_256 0x40
#define MS5803_D1_512 0x42
#define MS5803_D1_1024 0x44
#define MS5803_D1_2048 0x46
#define MS5803_D1_4096 0x48
#define MS5803_D2_256 0x50
#define MS5803_D2_512 0x52
#define MS5803_D2_1024 0x54
#define MS5803_D2_2048 0x56
#define MS5803_D2_4096 0x58
#define MS5803_AdcRead 0x00
#define MS5803_PromBaseAddress 0xA0


//variables depending on fresh or salt water.
#define FreshWater (0)
#define SaltWater (1)


#endif

