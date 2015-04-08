// thrusterConfig.h

#ifndef _THRUSTERCONFIG_h
#define _THRUSTERCONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ThrusterConfigClass
{
 protected:
private:
	long F1;
	long F2;
	long F3;
	long F4;
	long F5;
	long F6;
	long angel;
	long thrustmax;
				
 public:
	void init();
	void thrustAllocation(long F_surge,long F_yaw);
	long getF1();
	long getF2();
	long getF3();
	long getF4();
	long getF5();
	long getF6();
	
};

extern ThrusterConfigClass ThrusterConfig;

#endif

