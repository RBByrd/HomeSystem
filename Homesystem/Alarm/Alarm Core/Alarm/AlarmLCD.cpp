#include "AlarmLCD.h"
//#include <LiquidCrystal_I2C.h>

AlarmLCD::AlarmLCD(AlarmSystem* _alarm, AlarmKeypad* _keypad)
    :LiquidCrystal_I2C(0x27, 16, m_lcdHeight), alarm_(_alarm), keypad_(_keypad), lcdBlOnDelay(15000) {

  }

  //Turns on backlight after an interaction, and the backlight stays on for a set amount of time after the last interaction.
void AlarmLCD::AlarmBacklight(){
  unsigned long RTdifference = lcdTimer.LastInteraction();
  if((RTdifference < lcdBlOnDelay) && !getBacklight()){
    backlight();
    return;
  }
  if((RTdifference > lcdBlOnDelay) && getBacklight()){
     noBacklight();
     return;
  }
}


void AlarmLCD::AlarmInit(){
      begin();
      backlight();
      clear();
      //LCDmessageDisplay("      BYRD      ","   PROTECTION   ");
      delay(5000);
}


void AlarmLCD::SetMenuChange(){
  m_menuChange = true;
}

void AlarmLCD::SetInputBufferChange(){
  m_inputBufferChange = true;
}

void AlarmLCD::AlarmDisplay(){
  
  if(m_menuChange){
    m_menuChange = false;
    clear();
    setCursor(0,0);
    //print(alarm_->current_menu_->kTitle);
  }

  if(m_inputBufferChange){
    m_inputBufferChange = false;
    setCursor(0,1);
    for(int i = 0; i < 16; i++) {
      print(keypad_->string_stream_[i]);
    }
    blink();
  }
}

void AlarmLCD::AlarmOut(){
  AlarmBacklight();
  AlarmDisplay();
}  
