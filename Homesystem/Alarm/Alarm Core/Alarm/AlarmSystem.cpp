#include "AlarmSystem.h"

AlarmSystem::AlarmSystem(AlarmMenuController* _menu_,  AlarmSiren* _siren_)
  : menu_(_menu_), siren_(_siren_),
     alarm_state_(kUnarmedSecure), initial_check_(kUnset) {
}


void AlarmSystem::Menu(){
  
  
}

void AlarmSystem::UnarmedSecure(){
  if(initial_check_ != kUnarmedSecure){
     initial_check_ = kUnarmedSecure;
     //turn off siren
  }
  //menu function

  //check zones
}

void AlarmSystem::UnarmedUnsecure(){
  if(initial_check_ != kUnarmedUnsecure){
     initial_check_ = kUnarmedUnsecure;
     //chirp siren
  }
  //menu function

  //check zones
}

void AlarmSystem::ArmedStay(){
  if(initial_check_ != kArmedStay){
     //start timer
     //initial_check_ = kArmedStay;

  }
  //if timer < arming time
    //check keypad
    //if cancel
      //clear timer
      //set state as UnarmedSecure
    //check zones
      //if zone opened
        //siren chirp
        //should alarm go off for stay?  
    //return;
    
  //menu function

  //check zones
    //if zone open
      //set state = kAlarmEngaged
}

void AlarmSystem::ArmedAway(){
  if(initial_check_ != kArmedAway){
     initial_check_ = kArmedAway;
     //turn off siren
  }
  //menu function

  //check zones
}
          
void AlarmSystem::AlarmEngaged(){
  if(initial_check_ != kAlarmEngaged){
     initial_check_ = kAlarmEngaged;
     //turn off siren
  }
  //menu function

  //check zones
}
          
void AlarmSystem::AlarmOnAlert(){
  if(initial_check_ != kAlarmOnAlert){
     initial_check_ = kAlarmOnAlert;
     //turn off siren
  }
  //menu function

  //check zones
}

void AlarmSystem::SilentAlarm(){
  if(initial_check_ != kSilentAlarm){
     initial_check_ = kSilentAlarm;
     //turn off siren
  }
  //menu function

  //check zones
}
            
void AlarmSystem::AlarmLocked(){
  if(initial_check_ != kAlarmLocked){
     initial_check_ = kAlarmLocked;
     //turn off siren
  }
  //menu function

  //check zones
}



void AlarmSystem::Sys(){
  switch(alarm_state_){
  case kUnarmedSecure:{
    void UnarmedSecure();
  }
  case kUnarmedUnsecure:{
    void UnarmedUnsecure();
  }
  case kArmedStay:{
    void ArmedStay();
  }
  case kArmedAway:{
    void ArmedAway();
  }
  case kAlarmEngaged:{
    void AlarmEngaged();
  }
  case kAlarmOnAlert:{
    void AlarmOnAlert();
  }
  case kSilentAlarm:{
    void SilentAlarm();
  }   
  case kAlarmLocked:{
    void AlarmLocked();
  }
  return;
        }
}