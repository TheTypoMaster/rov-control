#include "MS5803_14BA.h"
#include "Timer.h"
#include "MS5803.h"
#include "IMU.h"
#include <Wire.h>
//#include <Wire.h>

//IMU sensor;
MS5803_14BA depthSensor;

void setup()
{
	Serial.begin(9600);
	Wire.begin();
	//Serial.print("setup done \n");
	//sensor.CompasSetup();
	depthSensor.initialize(true);
	
	

}


void loop()
{	
	depthSensor.read();
	Serial.println(depthSensor.getPreassure());
	
	/*
	Serial.println(sensor.readAll());
	//Serial.print('/n');
	delay(100);
	//Serial.println(depthSensor.getDepth());
	//Serial.println(depthSensor.readAdcPreassure());
	//Serial.println(depthSensor.readAdcTemperature());
	depthSensor.readSensor();
	Serial.println(depthSensor.pressure());
	Serial.println(depthSensor.temperature());
	
	*/
	
	 //this is working but reading only one thing at a time. 
	/*
	double dT = ( (double) sensor.read(MPU9150_TEMP_OUT_L,MPU9150_TEMP_OUT_H) + 12412.0) / 340.0;
	Serial.print(dT);
	Serial.print("  ");
	Serial.print(sensor.read(MPU9150_CMPS_XOUT_L,MPU9150_CMPS_XOUT_H));
	Serial.print("  ");
	Serial.print(sensor.read(MPU9150_CMPS_YOUT_L,MPU9150_CMPS_YOUT_H));
	Serial.print("  ");
	Serial.print(sensor.read(MPU9150_CMPS_ZOUT_L,MPU9150_CMPS_ZOUT_H));
	Serial.print("  ");
	Serial.print(sensor.read(MPU9150_GYRO_XOUT_L,MPU9150_GYRO_XOUT_H));
	Serial.print("  ");
	Serial.print(sensor.read(MPU9150_GYRO_YOUT_L,MPU9150_GYRO_YOUT_H));
	Serial.print("  ");
	Serial.print(sensor.read(MPU9150_GYRO_ZOUT_L,MPU9150_GYRO_ZOUT_H));
	Serial.print("  ");
	Serial.print(sensor.read(MPU9150_ACCEL_XOUT_L,MPU9150_ACCEL_XOUT_H));
	Serial.print("  ");
	Serial.print(sensor.read(MPU9150_ACCEL_YOUT_L,MPU9150_ACCEL_YOUT_H));
	Serial.print("  ");
	Serial.print(sensor.read(MPU9150_ACCEL_ZOUT_L,MPU9150_ACCEL_ZOUT_H));
	Serial.println();
	
	*/
	/* add main program code here */
	delay(100);
}
