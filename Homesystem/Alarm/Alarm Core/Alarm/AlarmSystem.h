#ifndef AlarmSystem_H_
#define AlarmSystem_H_

#include "AlarmTimer.h"
#include "AlarmSiren.h"
#include "AlarmMenuController.h"
#include <Arduino.h>


class AlarmSystem {
    private:
      AlarmMenuController* menu_;
      //AlarmMenu* current_menu_;
      AlarmSiren* siren_;
      enum AlarmStates_: byte {kUnset, kUnarmedSecure, kUnarmedUnsecure,
                               kArmedStay, kArmedAway, kAlarmEngaged, 
                               kAlarmOnAlert, kSilentAlarm, kAlarmLocked};
      AlarmStates_ alarm_state_;
      AlarmStates_ initial_check_;
      AlarmTimer timer_;
    public:
      AlarmSystem(AlarmMenuController* _menu_,  AlarmSiren* _siren_);
      void Menu();   
      void UnarmedSecure();              
      void UnarmedUnsecure();            
      void ArmedStay();          
      void ArmedAway();            
      void AlarmEngaged();           
      void AlarmOnAlert();            
      void SilentAlarm();            
      void AlarmLocked();
      void Sys();
};

#endif

