#include "AlarmKeypad.h"


void AlarmKeypad::AppendStream(){
  switch(keypad_state_){
    case kNoUserStream:
      return;
    case kIntUserStream:
      int_stream_ = (int_stream_ * 10) + (key_data_ - '0');
      return;
    case kStringUserStream:
      if(string_stream_position_ > 14)
        return;
      string_stream_[string_stream_position_] = key_data_;         
      string_stream_position_++;
      return;
  }
}

void AlarmKeypad::GetCommand(){
  switch(keypad_state_){
    case kNoUserStream:
      if(key_data_ == menu_key){
        menu_key_pressed = true;
        return;
      }
      return;            
    case kIntUserStream:
      if(key_data_ == clear_key){
        clear_key_pressed = true;
        int_stream_ = 0;
        return;
      }        
    case kStringUserStream:
      if(key_data_ == clear_key){
        clear_key_pressed = true;
        ClearStream();
        return;
      }
      if(key_data_ == enter_key){
        if(string_stream_position_ == 0){
          enter_key_pressed = true;
          return;
        }
        for(string_stream_position_; string_stream_position_ >= 0; string_stream_position_--){
            string_stream_[string_stream_position_] = '\0';
        }
        return;
      }
  }
}
  

AlarmKeypad::AlarmKeypad()
  :Keypad( makeKeymap(m_keys), kKeyRowPins, kKeyColPins, kKeyRows, kKeyCols),
           string_stream_position_(0), keypad_command_('\0'), 
           keypad_state_(kNoUserStream),
           cancel_key_pressed(false), clear_key_pressed(false), 
           menu_key_pressed(false), enter_key_pressed(false)
{
  for(byte i = 0; i < kMaxStream; i++)
    string_stream_[i] = '\0';

}

void AlarmKeypad::KeypadGetKey(){
    ClearCommands();
    key_data_ = getKey();
    
    if(key_data_ == '\0')
      return;

    //user_->setInteraction();
    if(key_data_ >= zero_key and key_data_ <= nine_key){
       AppendStream();
       return;
    }
    if(key_data_ >= cancel_key and key_data_ <= enter_key){
       GetCommand();
       return;
    } 
}
      
void AlarmKeypad::ClearStream(){
  int_stream_ = 0;
  
  if(string_stream_position_ == 0){
    return;
  }
  for(string_stream_position_; string_stream_position_ >= 0; string_stream_position_--)
      string_stream_[string_stream_position_] = '\0';
  return;
}


void AlarmKeypad::ClearCommands(){
  cancel_key_pressed = false;
  clear_key_pressed = false; 
  menu_key_pressed = false;
  enter_key_pressed = false;
}
