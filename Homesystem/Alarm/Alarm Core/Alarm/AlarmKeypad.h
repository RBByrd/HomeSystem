#ifndef AlarmKeypad_H_
#define AlarmKeypad_H_

#include <Arduino.h>
#include <Keypad.h>
//#include "AlarmUser.h"

class AlarmKeypad:public Keypad {
    private: 
      static const byte kKeyRows = 4; 
      static const byte kKeyCols = 4;
      static const byte kMaxStream = 16;
      enum AlarmKeys: unsigned char{one_key = '1', two_key = '2', three_key = '3', cancel_key = 'A',
                                    four_key = '4', five_key = '5', six_key = '6', clear_key = 'B',
                                    seven_key = '7', eight_key = '8', nine_key = '9', menu_key = 'C',
                                    astrick_key = '*', zero_key = '0', pound_key = '#', enter_key = 'D'};
      const unsigned char m_keys[kKeyRows][kKeyCols] = {
        {one_key, two_key, three_key, cancel_key}, 
        {four_key, five_key, six_key, clear_key}, 
        {seven_key, eight_key, nine_key, menu_key}, 
        {astrick_key, zero_key, pound_key, enter_key}  
      };
      byte kKeyRowPins[kKeyRows] = {6, 5, 3, 2}; 
      byte kKeyColPins[kKeyCols] = {12, 11, 10, 9};
      char key_data_;
      bool cancel_key_pressed, clear_key_pressed, menu_key_pressed, enter_key_pressed;
      //AlarmUser* user_;
      


      static unsigned long alarm_current_time_;
      static unsigned long latest_user_interaction_time_;
      static unsigned long latest_zone_interaction_time_;
      unsigned long alarm_timer_;
      
    public:
      unsigned char string_stream_[kMaxStream];
      byte string_stream_position_;
      unsigned long int int_stream_;
      unsigned char keypad_command_;
      enum KeypadStates_: byte {kNoUserStream, kIntUserStream, kStringUserStream};
      KeypadStates_ keypad_state_;
    private:
      void AppendStream();
      void GetCommand();
      void ClearCommands();

    public:
      AlarmKeypad();
      void KeypadGetKey();
      void ClearStream();
};

#endif
