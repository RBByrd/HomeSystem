#include "AlarmSiren.h"


AlarmSiren::AlarmSiren(): siren_state_(kOff) {

}
void AlarmSiren::Chirp(){
  siren_state_ = kChirp;
}

void AlarmSiren::On(){
  siren_state_ = kOn;
  return;
}

bool AlarmSiren::IsOn(){
  if(siren_state_ == kOn) {
    return true;
  }
  return false;
}

void AlarmSiren::Off(){
  siren_state_ = kOff;
  return;
}


void AlarmSiren::output(){
   
}    

