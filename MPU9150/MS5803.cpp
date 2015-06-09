// 
// 
// 

#include "MS5803.h"
#include "Timer.h"
#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\Wire\Wire.h"

//io_timeout is the max wait time in ms for I2C requests to complete
const int io_timeout = 20;


unsigned int CalConstant[8];  // Matrix for holding calibration constants

long AdcTemperature, AdcPressure;  // Holds raw ADC data for temperature and pressure
float Temperature, Pressure, TempDifference, Offset, Sensitivity;
float T2, Off2, Sens2;  // Offsets for second-order temperature computation
float AtmosPressure = 1015;
float Depth;
float DepthOffset = 0;
float WaterDensity = 1.019716;
Timer DepthSensorSamples;
byte ByteHigh, ByteMiddle, ByteLow;  // Variables for I2C reads
bool WaterType = FreshWater;

void MS5803::sendCommand(byte command){
	Wire.beginTransmission(MS5803_I2C_ADDRESS);
	Wire.write(command);
	Wire.endTransmission();
}

void MS5803::device_setup(){
	Wire.begin();
	delay(10);
	
	//reset and check for presence
	
	sendCommand(MS5803_reset);
	delay(10);
	
	// get calibration constants and store in array.
	for (byte i = 0; i < 8; i++)
	{
		sendCommand(MS5803_PromBaseAddress + (2*i));
		Wire.requestFrom(MS5803_I2C_ADDRESS, 2);
		while(Wire.available()){
			ByteHigh = Wire.read();
			ByteLow = Wire.read();
		}
		CalConstant[i] = (((unsigned int)ByteHigh << 8) + ByteLow);
	}
	
	DepthSensorSamples.reset();
}

long MS5803::readAdcPreassure(){
	
}

void MS5803::device_loop(){
	 if (DepthSensorSamples.elapsed(1000)){
		 // Read the Device for the ADC Temperature and Pressure values
		 
		 sendCommand(MS5803_D1_512);
		 delay(10);
		 sendCommand(MS5803_AdcRead);
		 Wire.requestFrom(MS5803_I2C_ADDRESS , 3);
		 
		 unsigned int millis_start = millis();
		 while(Wire.available() < 3){
			if(io_timeout >0 && ((unsigned int)millis()-millis_start > io_timeout)){
				 //failed to read depth from I2C.
				 return;
			}
		 }
		 ByteHigh = Wire.read();
		 ByteMiddle = Wire.read();
		 ByteLow = Wire.read();
		 
		 AdcPressure = ((long) ByteHigh << 16) + ((long) ByteMiddle << 8) + (long) ByteLow;
		 
		 sendCommand(MS5803_D2_512);
		 delay(10);
		 sendCommand(MS5803_AdcRead);
		 Wire.requestFrom(MS5803_I2C_ADDRESS , 3);
		 
		 millis_start = millis();
		 while (Wire.available() < 3){
			 if (io_timeout >0 && ((unsigned int) millis() - millis_start) > io_timeout){
				 //faild to read Depth from I2C
				 return;
			 }
		 }
		 ByteHigh = Wire.read();
		 ByteMiddle = Wire.read();
		 ByteLow = Wire.read();
		 

		 AdcTemperature = AdcTemperature = ((long)ByteHigh << 16) + ((long)ByteMiddle << 8) + (long)ByteLow;
		 
		 
		 //Calculate the temp (first order computation)
		 
		 TempDifference = (float)(AdcTemperature - ((long)CalConstant[5] << 8));
		 Temperature = (TempDifference * (float) CalConstant[6])/pow(2,23);
		 Temperature = Temperature + 2000; // The temperature in hundreads of degree C
		 
		 //second order offset
		 if (Temperature < 2000.0){ // below or abow 20 C
			 T2 = 3 * pow(TempDifference, 2) / pow(2, 33);
			 Off2 = 1.5 * pow((Temperature - 2000.0), 2);
			 Sens2 = 0.625 * pow((Temperature - 2000.0), 2);
		 }
		 else{
			 T2 = (TempDifference * TempDifference) * 7 / pow(2, 37);
		 	 Off2 = 0.0625 * pow((Temperature - 2000.0), 2);
		 	 Sens2 = 0.0;
		 }
		 
		 Temperature = Temperature / 100 ; // convert to degree C from hundreads
		 
		 // calculate preasure parameters
		 
		 Offset = (float) CalConstant[2] * pow(2,16);
		 Offset = Offset + ((float)CalConstant[4] * TempDifference / pow(2, 7));

		 Sensitivity = (float)CalConstant[1] * pow(2, 15);
		 Sensitivity = Sensitivity + ((float)CalConstant[3] * TempDifference / pow(2, 8));
		 
		 // second order correction
		 Offset = Offset - Off2;
		 Sensitivity = Sensitivity - Sens2;
		 
		 //find absolut preasure in bar
		 Pressure = (float)AdcPressure * Sensitivity / pow(2, 21);
		 Pressure = Pressure - Offset;
		 Pressure = Pressure / pow(2, 15);
		 Pressure = Pressure / 10;  // Set output to mbars = hectopascal;
		 
		 // water type correction
		 if (WaterType == FreshWater){
			 Depth = (Pressure-AtmosPressure) * WaterDensity / 100 ; 
		 } 
		 else{
			 // see Seabird App Note #69 for details and correction for latitude.
			 Depth = (Pressure-AtmosPressure) * 0.9945 / 100 ;
		 }

	
	 }
}

//MS5803 MS5803;

