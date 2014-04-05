#ifndef SEQ16_MULTIPEX_H
#define SEQ16_MULTIPEX_H

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h"
  
#define TYPE_LED 0

#define TYPE_BUTTON 1
  
class SEQ16_MULTIPEX {
public:
	SEQ16_MULTIPEX();
	~SEQ16_MULTIPEX();
	void ledOn(byte num);
	void readButtons();
	bool isFunctionActive();
	byte getCurrentButton();
//	bool isbuttonActive(byte num);
	void activateMuliplex(byte i, byte type);
	
	
	
private:
	void writeMultiplex(byte a, byte b, byte c, byte type);
	void writeMultiplexLed(byte a, byte b, byte c);
	void writeMultiplexBtn(byte a, byte b, byte c);
	
	
	byte m_last_button;
	byte m_is_function;
};
  
#endif
