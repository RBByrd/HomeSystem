/*
 * Alarm Code
 * 
 * A basic alarm to function for basic home use.
 * not meant for criminal protection or to be used as such
 * 
 * This code is meant to use alarm devices from an older install. 
 * It is recommended to get an alarm service. No liability is to be taken by the author or anyone that modifies this code.
 * 
 */
//Arduino Libraries
#include <Wire.h> 
#include <EEPROM.h>
//Community Libraries
//using https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library.git
//#include <LiquidCrystal_I2C.h>
//using https://github.com/Chris--A/Keypad
//note: debounce is built into this function and works well.
#include <Keypad.h>
//Class Files
#include "AlarmTimer.h"
#include "AlarmKeypad.h"
//#include "AlarmUser.h"
#include "AlarmSiren.h"
#include "AlarmMenuPages.h"
#include "AlarmMenuController.h"
#include "AlarmLCD.h"
#include "AlarmSystem.h"
#include "Setting.h"


//duplicate Menu titles to save memory
const char  *kNewPWTitle = "New Password";
const char *KReenterPWTitle = "Reenter Password";

//MenuItems
AlarmMenuPages nullMenu;
AlarmMenuPages mainMenu("Main Menu");

AlarmMenuPages enterPasswordMenu("Enter Password"); 

AlarmMenuPages displayMenu("Display Settings",mainMenu);
AlarmMenuPages lcdBacklightMenu("LCD BL Timer (S)",displayMenu, 1);

AlarmMenuPages passwordMenu("Password",displayMenu);
AlarmMenuPages newPasswordMenu(kNewPWTitle,passwordMenu, 1);
AlarmMenuPages reEnterPassword(KReenterPWTitle,newPasswordMenu, 2);

AlarmMenuPages tempPasswordMenu("Temp Password",newPasswordMenu);
AlarmMenuPages newTempPasswordMenu(kNewPWTitle,tempPasswordMenu, 1);
AlarmMenuPages reEnterTempPassword(KReenterPWTitle,newTempPasswordMenu, 2);

//TODO(RBByrd) create a serial communication class
//class AlarmSerial: 
//
//    protected:
//
//
//    public:
//
//
//};

AlarmTimer sysTimer;
//AlarmUser user;
AlarmKeypad keypad;
AlarmMenuController menu(&mainMenu);
AlarmSiren siren;
AlarmSystem alarm(&menu, &siren);
AlarmLCD lcd(&alarm, &keypad);

//Define the Static Variables
unsigned long AlarmTimer::alarm_current_time_;
unsigned long AlarmTimer::latest_user_interaction_time_;
unsigned long AlarmTimer::latest_zone_interaction_time_;

void setup() {
  Serial.begin(9600);
  lcd.AlarmInit();

}
void loop() {

  //user.clear();
  //inputs
  AlarmTimer::SetCurrentTime();

  keypad.KeypadGetKey();

  //functionality
  alarm.Sys();
  
 
  //outputs
  lcd.AlarmOut();
}
