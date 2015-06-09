// Timer.h
//
// A class to check if an amount of time has elapsed since the last reset of the time object.
// 

#ifndef _TIMER_h
#define _TIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Arduino.h>

#define SEC_PER_MIN 60
#define SEC_PER_HOUR 3600

class Timer
{
 private:
	unsigned long start;
	unsigned long last;

 public:
	Timer();
	unsigned long now();
	boolean elapsed(unsigned long milliseconds);
	void reset();
	
};

//extern TimerClass Timer;

#endif

