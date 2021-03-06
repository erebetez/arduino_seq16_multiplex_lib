#ifndef SEQ16_MULTIPEX_H
#define SEQ16_MULTIPEX_H

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h"


class SEQ16_MULTIPEX {
public:
	SEQ16_MULTIPEX();
	~SEQ16_MULTIPEX();
	void ledOn(byte num);
	void readButtons();
	bool isFunctionActive();
	byte getCurrentButton();
	bool isButtonPressed();

private:
	void writeMultiplexLed(const byte num);
	void writeMultiplexBtn(const byte num);
	void intToBinMuliplex(const byte i, byte &a, byte &b, byte &c);

	byte m_current_button;
	byte m_is_function;
	byte m_is_button_pressed;
};
  
#endif
