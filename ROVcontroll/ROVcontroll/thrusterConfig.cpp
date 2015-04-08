// 
// 
// 

#include "thrusterConfig.h"

void ThrusterConfigClass::init()
{


}

void ThrusterConfigClass::thrustAllocation(long F_surge, long F_yaw ){
	bool extraThrust = false;
	F1 = angel*(F_surge + F_yaw);
	F2 = angel*(F_surge - F_yaw);
	if F1 >= thrustmax
	{
		F1 = 20;//Newton mulighens endres pga desimal operasjoner
		extraThrust = true;
	}
	if F2 >= thrustmax
	{
		F2 = 22;//Newton
		extraThrust = true;
	}
	if (extraThrust)
	{
		F3 = (F_surge - F1)/(2 + 2*angel);
		F4 = F3;
		F5 = F3;
		F6 = F3;
	}
}
long ThrusterConfigClass::getF1(){
	return F1;
}
long ThrusterConfigClass::getF2(){
	return F2;
}
long ThrusterConfigClass::getF3(){
	return F3;
}
long ThrusterConfigClass::getF4(){
	return F4;
}
long ThrusterConfigClass::getF5(){
	return F5;
}
long ThrusterConfigClass::getF6(){
	return F6;
}

ThrusterConfigClass ThrusterConfig;

