#ifndef AlarmSiren_H_
#define AlarmSiren_H_

#include "AlarmTimer.h"
#include <Arduino.h>

class AlarmSiren {
    private:
      	AlarmTimer timer_;
      	enum Siren_States_ {kOff, kOn, kChirp};
      	Siren_States_ siren_state_ = kOff;
    public:
    	AlarmSiren();
      	void Chirp();
      
    	void On();
    	bool IsOn();
      
      	void Off();
      
      	void output(); 
};


#endif