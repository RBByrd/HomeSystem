#ifndef AlarmUser_H_
#define AlarmUser_H_

#include "AlarmTimer.h"
#include <Arduino.h>


struct AlarmUser{
  bool menu_pressed_ = false;
  bool interaction = false;
  AlarmTimer userTimer;

  AlarmUser();
 
  void setInteraction();
  void setMenuPressed();
  bool getMenuPressed();
  void clear();
};

#endif