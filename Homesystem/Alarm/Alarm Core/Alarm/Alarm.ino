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

#include <Wire.h> 

//using https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library.git
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

//using https://github.com/Chris--A/Keypad
//note: debounce is built into this function and works well.
#include <Keypad.h>




///////////////////////Timer Alarm Timer Class///////////////////////////////
class AlarmTimer{
    public:
      const static unsigned long tAMaxTime = 4294967295;
      
      static unsigned long tACurrent;
      static unsigned long tAUserInteraction;
      static unsigned long tASystemInteraction;
      unsigned long tATimer;      
    
    
    public:
      void tAGetCurrent(){
        tACurrent = millis();
      }

      void tASetUserInteraction(){
         tAUserInteraction = millis();
      }

      void tASetSystemInteraction(){
         tASystemInteraction = millis();
      }
      //find the amount of time that has passed since RTstart to current time. maximuim amount of time is 4294967295 milliseconds, ~50 days
      unsigned long tAGetTimeDifference(unsigned long tAStart, unsigned long tAEnd){
          if(tAStart <= tAEnd)
              return tAEnd - tAStart;
          return (tAMaxTime - tAStart) + tAEnd;
      }
      
      unsigned long tALastUserInteraction(){
          return tAGetTimeDifference(tAUserInteraction, tACurrent);
      }

      unsigned long tALastSystemInteraction(){
          return tAGetTimeDifference(tASystemInteraction, tACurrent);
      }

      unsigned long tALastInteraction(){
          unsigned long tASys = tALastSystemInteraction();
          unsigned long tAUsr = tALastUserInteraction();
          if(tASys > tAUsr)
            return tAUsr;
          return tASys;
      }

  
};

//Define the Static Variables
unsigned long AlarmTimer::tACurrent;
unsigned long AlarmTimer::tAUserInteraction;
unsigned long AlarmTimer::tASystemInteraction;


///////////////////////Alarm User Class/////////////////////////////

struct AlarmUser{

  bool uAMenuPressed = false;
  bool uAInteraction = false;
  AlarmTimer userTimer;
  
  

  void uASetInteraction(){
       userTimer.tASetUserInteraction();
       uAInteraction = true;
  }

  void uASetMenuPressed(){
      uAMenuPressed = true;
  }
  
  void uAClear(){
       uAMenuPressed = false;
       uAInteraction = false;
       
       
  }
  
};


///////////////////////keypad alarm keypad class/////////////////////////////


class AlarmKeypad: public Keypad{
    private:
      static const byte m_KEYROWS = 4; 
      static const byte m_KEYCOLS = 4;
      static const byte m_maxStream = 16;
      unsigned char m_keys[m_KEYROWS][m_KEYCOLS] = 
      {
        {'1','2','3','A'}, //1,2,3,A = Cancel
        {'4','5','6','B'}, //4,5,6,B = Clear
        {'7','8','9','C'}, //7,8,9,C = Menu
        {'*','0','#','D'}  //*,0,#,D = Enter
      };
      byte m_keyRowPins[m_KEYROWS] = {6, 5, 3, 2}; 
      byte m_keyColPins[m_KEYCOLS] = {12, 11, 10, 9};
      char m_keyData;
      AlarmUser* user;

    public:

      enum kaKey: unsigned char{kaOne = '1',kaTwo = '2',kaThree = '3',kaCancel = 'A',
                                kaFour = '4',kaFive = '5',kaSix = '6',kaClear = 'B',
                                kaSeven = '7',kaEight = '8',kaNine = '9',kaMenu = 'C',
                                kaAstrick = '*',kaZero = '0',kaPound = '#',kaEnter = 'D'};
      unsigned char kaStringStream[m_maxStream];
      byte StringStreamPosition;
      unsigned long int kaIntStream;
      unsigned char kaCommand;
      enum kaKeyStates: byte {kaNoUStream, kaIntUStream, kaStringUStream};
      byte kaKeyState;

    private:
      void m_kaStream(){
        switch(kaKeyState){
          case kaNoUStream:
            return;
          case kaIntUStream:
            kaIntStream = (kaIntStream * 10) + (m_keyData - '0');
            return;
          case kaStringUStream:
            if(StringStreamPosition > 14)
              return;
            kaStringStream[StringStreamPosition] = m_keyData;         
            StringStreamPosition++;
            return;
        }
      }

      void m_kaCommand(){
        switch(kaKeyState){
          case kaNoUStream:
            if(m_keyData == kaMenu){
              Serial.print('c');
              user->uASetMenuPressed();
              return;
            }
            return;            
          case kaIntUStream:
            if(m_keyData == kaClear){
              kaIntStream = 0;
              return;
            }        
          case kaStringUStream:
            if(m_keyData == kaClear){
              kaClearStream();
              return;
            }
            if(m_keyData == kaEnter){
              if(StringStreamPosition == 0)
                return;
              for(StringStreamPosition; StringStreamPosition >= 0; StringStreamPosition--){
                  kaStringStream[StringStreamPosition] = '\0';
              }
              return;
            }
        }
      }
    
    public:
      AlarmKeypad(AlarmUser* _user)
        :Keypad( makeKeymap(m_keys), m_keyRowPins, m_keyColPins, m_KEYROWS, m_KEYCOLS),StringStreamPosition(0),kaCommand('\0'),kaKeyState(kaNoUStream), user(_user)
      {
        for(byte i = 0; i < m_maxStream; i++)
          kaStringStream[i] = '\0';

      }

      void kaGet(){
          m_keyData = getKey();
          
          if(m_keyData == '\0')
            return;

          user->uASetInteraction();
          if(m_keyData >= kaZero and m_keyData <= kaNine){
             m_kaStream();
             return;
          }
          if(m_keyData >= kaCancel and m_keyData <= kaEnter){
             m_kaCommand();
             return;
          }

          
            
      }
      
      void kaClearStream(){
        kaIntStream = 0;
        
        if(StringStreamPosition == 0)
          return;
        
        for(StringStreamPosition; StringStreamPosition >= 0; StringStreamPosition--)
            kaStringStream[StringStreamPosition] = '\0';
        
        return;
      }
};








///////////////////////Menu Alarm Class/////////////////////////////

class AlarmMenu {
    protected:

    public:
        const char* title;
        AlarmMenu* childMenu;
        bool mAHasChild;
        AlarmMenu* nextMenu;
        bool mAHasNext;
        
    AlarmMenu(const char* _title)
      :title(_title){

    }
      
    AlarmMenu(const char* _title,AlarmMenu& prev)
      :title(_title){        
        AlarmMenu* next = this;
        prev.nextMenu = next;
        prev.mAHasNext = true;
    }
    
    AlarmMenu(const char* _title,AlarmMenu& parent, byte generation)
      :title(_title){        
        AlarmMenu* child = this;
        parent.childMenu = child;
        parent.mAHasChild = true;
    }



};

//duplicate Menu titles to save memory
const char  *newPwTitle = "New Password";
const char *reEnterPWTitle = "Reenter Password";


//MenuItems
AlarmMenu mainMenu("Main Menu");

AlarmMenu enterPasswordMenu("Enter Password"); 

AlarmMenu displayMenu("Display Settings",mainMenu);
AlarmMenu lcdBacklightMenu("LCD BL Timer (S)",displayMenu, 1);

AlarmMenu passwordMenu("Password",displayMenu);
AlarmMenu newPasswordMenu(newPwTitle,passwordMenu, 1);
AlarmMenu reEnterPassword(reEnterPWTitle,newPasswordMenu, 2);

AlarmMenu tempPasswordMenu("Temp Password",newPasswordMenu);
AlarmMenu newTempPasswordMenu(newPwTitle,tempPasswordMenu, 1);
AlarmMenu reEnterTempPassword(reEnterPWTitle,newTempPasswordMenu, 2);






class Alarm {
    protected:

    public:
      AlarmUser* user;
      AlarmMenu* mainMenu;
      AlarmMenu* currentMenu;


      Alarm(AlarmUser* _user, AlarmMenu* _mainMenu)
        : user(_user), mainMenu(_mainMenu), currentMenu(_mainMenu)
      {
        
      }

      void sys(){
        if(user->uAMenuPressed){
          Serial.print(currentMenu->mAHasNext);
          if(currentMenu->mAHasNext){
            currentMenu = currentMenu->nextMenu;
          }
          else{
            currentMenu = mainMenu;
          }
        }
        
      }


};


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


///////////////////////LCD Alarm Class/////////////////////////////

class AlarmLCD: public LiquidCrystal_I2C{

    private:
      byte m_lcdPin = 0x27;
      uint8_t m_lcdLen = 16;
      uint8_t m_lcdHeight = 2;
      AlarmTimer lcdTimer;
      
    public:
      //how low in millisec the backlight should remain lit
      unsigned long lcdBlOnDelay = 15000;

      Alarm* alarm;
      AlarmUser* user;
      
      enum LcdStates: byte {LCDWrite, LCDIdle, LCDUserInput, LCDOff};
        

    public:
      AlarmLCD(Alarm* _alarm, AlarmUser* _user)
        :LiquidCrystal_I2C(0x27, 16, m_lcdHeight), alarm(_alarm), user(_user)
      {

      }

      //Turns on backlight after an interaction, and the backlight stays on for a set amount of time after the last interaction.
    void LaBacklight(){
      unsigned long RTdifference = lcdTimer.tALastInteraction();
      if((RTdifference < lcdBlOnDelay) && !getBacklight()){
        backlight();
        return;
      }
      if((RTdifference > lcdBlOnDelay) && getBacklight()){
         noBacklight();
         return;
      }
    }


    void LaInit(){
          begin();
          backlight();
          clear();
          //LCDmessageDisplay("      BYRD      ","   PROTECTION   ");
          delay(5000);
    }
    void LaDisplay(){
      
      if(user->uAInteraction){
        clear();
        setCursor(0,0);
        print(alarm->currentMenu->title);
      }
      //blink();
    }

    void LaOut(){
      LaBacklight();
      LaDisplay();
    }

      
};












  AlarmTimer sysTimer;
  AlarmUser user;
  AlarmKeypad keypad(&user);
  Alarm alarm(&user, &mainMenu);
  AlarmLCD lcd(&alarm, &user);


void setup() {
  Serial.begin(9600);
  lcd.LaInit();

}
void loop() {

  user.uAClear();
  //inputs
  sysTimer.tAGetCurrent();

  keypad.kaGet();

  //functionality
  alarm.sys();
  
 
  //outputs
  lcd.LaOut();
}
