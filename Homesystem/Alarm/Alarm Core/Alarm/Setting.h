#ifndef Setting_H_
#define Setting_H_


#include <Arduino.h>
#include <EEPROM.h>

class Setting {
	private:

	public:

		Setting(int eeprom_Address, int data);
		Setting(int eeprom_Address, byte data);

};


#endif