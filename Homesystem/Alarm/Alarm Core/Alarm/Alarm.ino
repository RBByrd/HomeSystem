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
  
  
  #include <EEPROM.h>

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //tests if the system has been setup before. Does not progress if the system has not been setup, or the memory has become corrupt.
  setupCheck();

  //set the zones to the correct HW state
  setZones();


  zoneRead(zoneStates);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  zoneRead(zoneStates);

  printZones();
  Serial.println(zoneStates[0]);
  delay(1000);


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
      return;
    }

    //run user setup with 1 indicating that this is a new setup
    userSetup(1);

    return;
}

void userSetup(byte newSetup){
  byte input;

  if(newSetup == 1){
    Serial.println("Please Enter a Four Digit Passcode");
    
  }
  
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

void printZones(){
  for (int i = 0; i < 5; i ++){
    Serial.print("Zone ");
    Serial.println(i+1);
    Serial.println(zoneStates[i]);    
  }
}


void zoneRead(byte *zoneStates){
  
  zoneStates[0] = digitalRead(4);
  zoneStates[1] = digitalRead(7);
  zoneStates[2] = digitalRead(8);
  zoneStates[3] = digitalRead(12);
  zoneStates[4] = digitalRead(13);
  
}

void touchPad(){
  //takes input from an external touchpad
  
}


void siren(){
  
}
