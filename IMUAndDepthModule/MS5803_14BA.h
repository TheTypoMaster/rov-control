// MS5803_14BA.h

#ifndef _MS5803_14BA_h
#define _MS5803_14BA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MS5803_14BA
{
	public:
		MS5803_14BA();// default constructor with Resolution 512
		MS5803_14BA(uint16_t resolution);
		boolean initialize(boolean Verbose);
		void reset();
		void read();
		
		float getTemperature();
		float getPreassure();
		
		uint32_t getD1();
		uint32_t getD2();
		
		
	private:
		float mbar_;
		float tempC_;
		
		uint32_t	D1_;
		uint32_t	D2_;
		
		int32_t mbarInt_;
		
		uint16_t Resolution_;
		static uint16_t sensorCoefficients_[8];
		
		unsigned char MS5803_CRC(uint16_t n_prom[]);
		uint32_t MS5803_ADC(int8_t commandAdc);
		

		
	
};


// defines:
// i2C_address might be 0x77 if R6 is added and R5 is removed from the open ROV module.
#define MS5803_I2C_ADDRESS	0x76
#define PROM_ADDRESS_START	0xA0

//comands for different opperations the PROM Read comand is not included.
#define COMMAND_RESET		0x1E
#define COMMAND_ADC_READ	0x00
#define COMMAND_D1_256		0x40
#define COMMAND_D1_512		0x42
#define COMMAND_D1_1024		0x44
#define COMMAND_D1_2048		0x46
#define COMMAND_D1_4096		0x48
#define COMMAND_D2_256		0x50
#define COMMAND_D2_512		0x52
#define COMMAND_D2_1024		0x54
#define COMMAND_D2_2048		0x56
#define COMMAND_D2_4096		0x58


#endif

