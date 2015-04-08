#include "thrusterConfig.h"
#include "Controller.h"
#include "FSM.h"
/*
 * ROVcontroll.ino
 *
 * Created: 3/25/2015 2:00:47 PM
 * Author: Kjetil
 */ 

#include "MyClass.h"
//byte servoPin;

void setup()
{
	Serial.begin(9600);
	FSM.init();
}

void loop()
{
	FSM.operate();
}
