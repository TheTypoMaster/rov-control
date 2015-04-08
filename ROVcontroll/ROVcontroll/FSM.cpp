// 
// 
// 

#include "FSM.h"
#include "Controller.h"
#include "thrusterConfig.h"

void FSMClass::init()
{
	state = INITIALIZE;
	Controller.init();
	
	//Sett inn initialisering av recive socket og send socket
	
	state = OPERATION; //if sucessfull

}
STATES FSMClass::operate(){
	//send alive
	//recive command
	long e_u;
	long e_r;
	long e_hive;
	//calculate tau
	long F_surge = Controller.calculate_tau_u(e_u);
	long F_yaw = Controller.calculate_tau_yaw(e_r)
	/*long e2 = calculate_tau_jaw(e_psi);
	long e3 = calculate_tau_hive(e_hive);*/
	//distrubute tau to thrusters
	ThrusterConfig.thrustAllocation(F_surge,F_yaw);
	//thrust(e1,e2,e3);
	
	return readState();
	
}
STATES FSMClass::readState(){
	return state;
}

FSMClass FSM;

