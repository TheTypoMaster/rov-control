// 
// 
// 

#include "Controller.h"

void ControllerClass::init()
{
	surge_Kp = 10;
	surge_Kd = 10;
	surge_Ki = 10;
	
	hive_Kp = 10;
	hive_Kd = 10;
	hive_Ki = 10;
	
	yaw_Kp = 10;
	yaw_Kd = 10;
	yaw_Ki = 10;

}
long ControllerClass::calculate_tau_u(long e_u)
{
	long ei = surge_Ki*euler(e_u,surge_ep1);
	long eii = euler(ei,surge_ep1);
	//long tau_u = surge_Kp*e_u + ei + eii;
	long tau_u = surge_Kp*e_u;
	surge_ep1 = ei;
	surge_ep2 = eii;
	return tau_u;
}
long ControllerClass::calculate_tau_yaw(long e_r)
{
	/*long ei = surge_Ki*euler(e_r,surge_ep1);
	long eii = euler(ei,surge_ep1);*/
	//long tau_u = surge_Kp*e_u + ei + eii;
	long tau_r = yaw_Kp*e_r;
	/*surge_ep1 = ei;
	surge_ep2 = eii;*/
	return tau_r;
}

long ControllerClass::euler(long e,long e_p)
{
	long h = 0.1;
	long xdot = e_p + h*e;
}


ControllerClass Controller;

