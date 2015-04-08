// Controller.h

#ifndef _CONTROLLER_h
#define _CONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ControllerClass
{
private:
 long surge_Kp;
 long surge_Kd;
 long surge_Ki;
 long surge_ep1;
 long surge_ep2;

 long hive_Kp;
 long hive_Kd;
 long hive_Ki;

 long yaw_Kp;
 long yaw_Kd;
 long yaw_Ki;
 long euler(long e,long e_p);
 protected:


 public:
	void init();
	long calculate_tau_u(long e_u);
	long calculate_tau_yaw(long e_r);
	long calculate_tau_hive(long e_h);
};

extern ControllerClass Controller;

#endif

