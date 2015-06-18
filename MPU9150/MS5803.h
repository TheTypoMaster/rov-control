// MS5803.h

#ifndef _MS5803_h
#define _MS5803_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MS_5803 {
public:
	// Constructor for the class. 
	// The argument is the desired oversampling resolution, which has 
	// values of 256, 512, 1024, 2048, 4096
    MS_5803(uint16_t Resolution = 512);
    // Initialize the sensor 
    boolean initializeMS_5803(boolean Verbose = true);
    // Reset the sensor
    void resetSensor();
    // Read the sensor
    void readSensor();
    //*********************************************************************
    // Additional methods to extract temperature, pressure (mbar), and the 
    // D1,D2 values after readSensor() has been called
    
    // Return temperature in degrees Celsius.
    float temperature() const       {return tempC;}  
    // Return pressure in mbar.
    float pressure() const          {return mbar;}
//    // Return temperature in degress Fahrenheit.
//    float temperatureF() const		{return tempF;}
//    // Return pressure in psi (absolute)
//    float psia() const				{return psiAbs;}
//    // Return pressure in psi (gauge)
//    float psig() const				{return psiGauge;}
//    // Return pressure in inHg
//    float inHg() const				{return inHgPress;}
//    // Return pressure in mmHg
//    float mmHg() const				{return mmHgPress;}
    // Return the D1 and D2 values, mostly for troubleshooting
    unsigned long D1val() const 	{return D1;}
    unsigned long D2val() const		{return D2;}
    
    
private:
    
    float mbar; // Store pressure in mbar. 
    float tempC; // Store temperature in degrees Celsius
//    float tempF; // Store temperature in degrees Fahrenheit
//    float psiAbs; // Store pressure in pounds per square inch, absolute
//    float psiGauge; // Store gauge pressure in pounds per square inch (psi)
//    float inHgPress;	// Store pressure in inches of mercury
//    float mmHgPress;	// Store pressure in mm of mercury
    unsigned long D1;	// Store D1 value
    unsigned long D2;	// Store D2 value
    int32_t mbarInt; // pressure in mbar, initially as a signed long integer
    // Check data integrity with CRC4
    unsigned char MS_5803_CRC(unsigned int n_prom[]); 
    // Handles commands to the sensor.
    unsigned long MS_5803_ADC(char commandADC);
    // Oversampling resolution
    uint16_t _Resolution;
};
/*
class MS5803
{
 private:
	// old one
	//bool WaterType;

 public:
		
	// old one
	void sendCommand(byte command);
	void device_setup();
	void device_loop();
	long readAdcPreassure();
	long readAdcTemperature();
	int getDepth();
	MS5803();
		
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
*/

#endif

