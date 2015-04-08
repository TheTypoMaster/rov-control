// FSM.h

#ifndef _FSM_h
#define _FSM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
typedef enum {
	INITIALIZE,
	OPERATION,
	ERROR_STATE
}STATES;
class FSMClass
{
private:
	STATES state;
protected:


public:
	void init();
	STATES operate();
	STATES readState();
};

extern FSMClass FSM;

#endif

