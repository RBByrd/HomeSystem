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
  #include<Keypad.h>

  //Global Variables. Variables that will be used for the initial setup and during operation
  
  //IO State Variables
  byte zoneStates[5];

  //EEProm Variables: Information that we want stored in the case of lost power the system can return to original state on startup
  int EEAddIntialized = 0;
  byte EEIntialized;
  int EEAddPassword = 4;
  int EEPassword;
  byte EEAddMonitoredZones = 8;
  byte EEMonitoredZones[5];
  //This may not get used as a way to save the alarm from wear by activating and deactivating
  //int EEAddArmedAddress = 28;
  //byte  EEArmedAddress;
  int EEAddArmed = 32;
  int EEArmed;


  /*State:
   * 0000 0000 New User 
   * 0000 0001 New User setting PW
   * 0000 0010 New User confirming PW
   * 0000 0011 New User PW did not match
   * 0000 0100 New User PW Set
   * 0000 0101 New User setting Zones 1
   * 
   * 
   * 
   * 
   */
  byte currentState = 0;

  //password function
  unsigned long int firstPassword;
  unsigned long int secPassword;
  bool passwordSet;

  //Initialize lcd variable
  LiquidCrystal_I2C lcd(0x27, 16, 2);


  const byte KEYROWS = 4; 
  const byte KEYCOLS = 4;
  
  // I converted the type char to type byte, but kept the same ASCII decimal equivalent.
  //I believe this will allow for a bit more fluid like interaction between the user and the system
  byte keys[KEYROWS][KEYCOLS] = 
  {
    {49,50,51,65}, //1,2,3,A
    {52,53,54,66}, //4,5,6,B
    {55,56,57,67}, //7,8,9,C
    {42,48,35,68}  //*,0,#,D
  };
  byte keyRowPins[KEYROWS] = {6, 5, 3, 2}; 
  byte keyColPins[KEYCOLS] = {12, 11, 10, 9};
  
  Keypad keypad = Keypad( makeKeymap(keys), keyRowPins, keyColPins, KEYROWS, KEYCOLS );
  byte keypadData;


  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //LCD boot
  LCDInitialize();
  
  //tests if the system has been setup before. Does not progress if the system has not been setup, or the memory has become corrupt. The system will stay in this function until the system is setup.
  setupCheck();

  //set the zones to the correct HW state
  setZones();

  zoneRead(zoneStates);
}


//loop variables

//RT (Real Time) variables need to be unsigned long to interact with the millis() function

//RTinteration is the latest time that the system has seen interaction.
unsigned long RTinteraction = millis();

/* The interaction variable will denote current interaction 
 * to keep this to one variable a bit will be assigened to the following
 * serial    1
 * Zones     8
 * settings 12
 * keypad   16
 */
unsigned int interaction;

int serialData;


/*The loop function should be thought of as a while(1) loop. 
*
*Keeping this in mind each function used in the loop should be executed in a timely manner that does not hold up the system 
*
*/
void loop() {
  //Serial.println(LCDbldelay);
  
  //initialize loop
  interaction = 0;

  //loop inputs
  //zoneRead(zoneStates);
  //keyPad();
  serialInput();


  //system functions
  getInteractionTime(interaction);

  //loop outputs
  //printZones();
  LCDbacklight(RTinteraction);
  //serialOutput();


}





void getInteractionTime(bool interaction){
  if(interaction > 0){
    RTinteraction = millis();
    return;
  }
  return;
}

void keypadInput(){

  keypadData = keypad.getKey();

  if(keypadData){
    interaction = interaction | 16;
    
    return;
  }

  return;
}


//Turns on backlight after an interaction, and the backlight stays on for a set amount of time after the last interaction.
void LCDbacklight(unsigned long RTinteraction){
    //how low in millisec the backlight should remain lit
    unsigned long RTblOnDelay = 15000;

    if((RTdifference(RTinteraction) < RTblOnDelay) && !lcd.getBacklight()){
      lcd.backlight();
      return;
    }
    if((RTdifference(RTinteraction) > RTblOnDelay) && lcd.getBacklight()){
       lcd.noBacklight();
       return;
    }

}


void LCDInitialize(){
  
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  LCDmessageDisplay("      BYRD      ","   PROTECTION   ");
  delay(1000);
}



//displays a message to the LCD. when not using top or bottom pass "NULL" string.
void LCDmessageDisplay(String topMessage, String botMessage){
    if(topMessage != "NULL"){
        lcd.setCursor(0,0);
        lcd.print(topMessage);
    }
    if(botMessage != "NULL"){
        lcd.setCursor(0,1);
        lcd.print(botMessage);
    }
    return;
}


//user function to create a new password. 
/* global variables
 * firstPassword
 * secPassword
 * currentState
 * 
 */
void newPassword(){
  


  //if the passwords did not match we want the user to see the message for an amount of time
  //and be able to break the message and start entering the passwords again.
  if(currentState == B00000011 || 0){
      if(keypadData > 0 || RTdifference(RTinteraction) > 10000){
        currentState = currentState & B11111100;
      }
  }

  //Before the user enters the passcode
  if(currentState == 0 || 0){
    LCDmessageDisplay(" Please Enter a ","4 Digit Passcode");
    currentState = currentState | B00000001;
  }
  
  if(currentState == B00000001 || 0){
    if(keypadData > 47 && keypadData < 58){
      firstPassword = (firstPassword * 100) + keypadData;
      if(firstPassword < 100){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("4 Digit Passcode");
        lcd.setCursor(0,1);
        lcd.print("*");
      }else{
        lcd.print("*");
      }
    }
  }
  
  //User verifies the entered passcode
  if(currentState == B00000010 || 0){
    if(keypadData > 47 && keypadData < 58){
      secPassword = ((secPassword * 100) + keypadData);
      if(secPassword < 100){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("  The Passcode  ");
        lcd.setCursor(0,1);
        lcd.print("*");
      }else{
        lcd.print("*");
      }
      if(secPassword > 48484847){
        //verify that the passwords match
        if(firstPassword == secPassword){
          currentState = currentState & B11111101;
          currentState = currentState | B00000100;
          //store password in EEPROM
        }
        if(firstPassword != secPassword){
          LCDmessageDisplay(" The Passwords  "," Did Not Match  ");
          RTinteraction = millis();
          currentState = currentState | B00000011;
          firstPassword = 0;
          secPassword = 0;
        }
  
      }
    }
  
  }
  
  //outputs

  //After the passcode has been entered once
  if((currentState == B00000001 || 0) && (firstPassword > 48484847)){
        currentState = currentState & B11111110;
        currentState = currentState | B00000010;
        LCDmessageDisplay("Please Re-Enter ","  The Passcode  ");
  } 

 }
    
  


void printZones(){
  for (int i = 0; i < 5; i ++){
    Serial.print("Zone ");
    Serial.println(i+1);
    Serial.println(zoneStates[i]);    
  }
}


//find the amount of time that has passed since RTstart to current time. maximuim amount of time is 4294967295 milliseconds, ~50 days
unsigned long RTdifference(unsigned long RTstart){
    unsigned long RTcurrent = millis();
    
    if(RTstart <= RTcurrent){
        return RTcurrent - RTstart;  
    }

    return (4294967295 - RTstart) + RTcurrent;
  
}


void serialInput(){
   if (Serial.available() > 0){
      serialData = Serial.read();
      //Serial.println(serialData);
      interaction = interaction | 1;
      return;
    }
    interaction = interaction & 65,534;
    serialData = 0;
    return;
  
}


void setupCheck(){

    //Test value to check if the system has been setup before. If the system does no
    byte setupVarification = 170;

    EEIntialized = EEPROM.read(EEAddIntialized);
    
    //if the value stored in memory matches the verification then retrieve the other values then return to setup
    if(EEIntialized == setupVarification){
      EEArmed = EEPROM.read(EEAddArmed);
      EEPassword = EEPROM.read(EEAddPassword);
      EEPROM.get(EEAddMonitoredZones,EEMonitoredZones);
      //currentState = ;
      return;
    }

    //run user setup with 1 indicating that this is a new setup
    currentState = 0;
    userSetup();

    return;
}


void setZones(){
  //Zones 1-5 of the alarm system
  //These pins Digital IO only where as the others have other functions (PWM, Serial Comms, Ect.)
  pinMode(4, INPUT_PULLUP); 
  pinMode(7, INPUT_PULLUP); 
  pinMode(8, INPUT_PULLUP); 
  pinMode(12, INPUT_PULLUP); 
  pinMode(13, INPUT_PULLUP); 

  
}


void siren(){
  
}


//uses global variables currentState
void userSetup(){
 
  
  if(currentState == 0){
    firstPassword = 0;
    secPassword = 0;

    while(currentState < B00000100){
      keypadInput();
      newPassword();
      Serial.println(currentState);
    }

    while(currentState < B00001000){
      if(currentState == B00000100){
         LCDmessageDisplay("Please Enter 1-5","For Watched Zone");
         currentState = B00000101;
      }
    }
      
//    while(!passwordSet){
//      unsigned long int firstPassword = 0;
//      unsigned long int secPassword = 0;
//
//      //User enters passcode the first time
//      bool firstPasswordSet = 0;
//      LCDmessageDisplay(" Please Enter a ","4 Digit Passcode");
//      while(!firstPasswordSet){
//        //keyPad();
//        serialInput();
//        //Serial.println(firstPassword);
//        if(serialData > 47 && serialData < 58){
//          Serial.println(firstPassword);
//          Serial.println(serialData);
//          firstPassword = firstPassword * 100;
//          Serial.println(firstPassword);
//          firstPassword = firstPassword + serialData;
//          Serial.println("equals");
//          Serial.println(firstPassword);
//          //Serial.print(firstPassword);
//          if(firstPassword < 100){
//            lcd.clear();
//            lcd.setCursor(0,0);
//            lcd.print("4 Digit Passcode");
//            lcd.setCursor(0,1);
//            lcd.print("*");
//          }else{
//            lcd.print("*");
//          }
//          if(firstPassword > 48484847){
//            firstPasswordSet = 1;
//          }
//        }
//      
//      }
//
//      //User verifies the entered passcode
//      bool secPasswordSet = 0;
//      LCDmessageDisplay("Please Re-Enter ","  The Passcode  ");
//      while(!secPasswordSet){
//        //keyPad();
//        serialInput();
//        if(serialData > 47 && serialData < 58){
//          secPassword = ((secPassword * 100) + serialData);
//          if(secPassword < 100){
//            lcd.clear();
//            lcd.setCursor(0,0);
//            lcd.print("  The Passcode  ");
//            lcd.setCursor(0,1);
//            lcd.print("*");
//          }else{
//            lcd.print("*");
//          }
//          if(secPassword > 48484847){
//            secPasswordSet = 1;
//          }
//        }
//      
//      }
//
//      //verify that the passwords match
//      if(firstPassword == secPassword){
//         passwordSet = 1;
//         //hash password
//
//         //store password in EEPROM
//      }
//      if(firstPassword != secPassword){
//         LCDmessageDisplay(" The Passwords  "," Did Not Match  ");
//      }
//
//      //this among other things should be changed for changing the password on a live setup.
//      delay(5000);
//      
//  }
    
  }
  
}


void zoneRead(byte *zoneStates){
  
  zoneStates[0] = digitalRead(4);
  zoneStates[1] = digitalRead(7);
  zoneStates[2] = digitalRead(8);
  zoneStates[3] = digitalRead(12);
  zoneStates[4] = digitalRead(13);
  
}
