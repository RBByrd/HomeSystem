#ifndef AlarmMenuController_H_
#define AlarmMenuController_H_

#include "AlarmMenuPages.h"
#include "AlarmTimer.h"
#include <Arduino.h>

class AlarmMenuController { 
 private:
    AlarmMenuPages* main_menu_;
    AlarmMenuPages* current_menu_;
    bool menu_active_;
    AlarmTimer timer_;
    
 public:
    AlarmMenuController(AlarmMenuPages* _main_menu_);
    void Sys();
    void MenuSelection();
    void MenuStringInput();
    void MenuIntInput();
    void MenuPWInput();
};
#endif