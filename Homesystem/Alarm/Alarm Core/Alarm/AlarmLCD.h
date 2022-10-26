#ifndef AlarmLCD_H_
#define AlarmLCD_H_

#include "AlarmTimer.h"
#include "AlarmKeypad.h"
#include "AlarmSystem.h"
#include <Arduino.h>
//using https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library.git
#include <LiquidCrystal_I2C.h>

class AlarmLCD: public LiquidCrystal_I2C{
    private:
      byte m_lcdPin = 0x27;
      uint8_t m_lcdLen = 16;
      uint8_t m_lcdHeight = 2;
      AlarmTimer lcdTimer; 
      bool m_menuChange, m_inputBufferChange;
    public:
      //how low in millisec the backlight should remain lit
      unsigned long lcdBlOnDelay;
      AlarmSystem* alarm_;
      AlarmKeypad* keypad_;
      enum LcdStates: byte {LCDWrite, LCDIdle, LCDUserInput, LCDOff};
        
    public:
      AlarmLCD(AlarmSystem* _alarm, AlarmKeypad* _keypad);
      //Turns on backlight after an interaction, and the backlight stays on for a set amount of time after the last interaction.
      void AlarmBacklight();      
      void AlarmInit();
      void SetMenuChange();
      void SetInputBufferChange();
      void AlarmDisplay();
      void AlarmOut();
};
#endif