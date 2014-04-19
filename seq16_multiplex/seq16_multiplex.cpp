    #include "seq16_multiplex.h"

    const byte m_led_inhibit = 2;
    const byte m_led_a = 3;
    const byte m_led_b = 4;
    const byte m_led_c = 5;

    const byte m_btn_a = 6;
    const byte m_btn_b = 7;
    const byte m_btn_c = 8;
    const byte m_btn_1 = 10;
    const byte m_btn_2 = 11;

    const byte m_btn_f = 12;     

    SEQ16_MULTIPEX::SEQ16_MULTIPEX(){
      pinMode(m_led_inhibit, OUTPUT); 
      pinMode(m_led_a, OUTPUT);
      pinMode(m_led_b, OUTPUT);
      pinMode(m_led_c, OUTPUT);

      pinMode(m_btn_a, OUTPUT);
      pinMode(m_btn_b, OUTPUT);
      pinMode(m_btn_c, OUTPUT);  

      pinMode(m_btn_1, INPUT);
      pinMode(m_btn_2, INPUT);

      pinMode(m_btn_f, INPUT);
    }

    SEQ16_MULTIPEX::~SEQ16_MULTIPEX(){/*nothing to destruct*/}

    void SEQ16_MULTIPEX::ledOn(byte num){
	if(num < 8){
	  digitalWrite(m_led_inhibit, LOW);
	} else {
	  num = num-8;
	  digitalWrite(m_led_inhibit, HIGH);
	}

	writeMultiplexLed(num);
    }


    void SEQ16_MULTIPEX::readButtons(){
      byte buttonState = LOW;

      m_is_function = digitalRead(m_btn_f);

      for(byte i = 0; i < 8; ++i){
	writeMultiplexBtn(i);

	buttonState = digitalRead(m_btn_1);

	if(buttonState == HIGH){
	    m_last_button = i;
	    return; 
	  }

	buttonState = digitalRead(m_btn_2); 

	if(buttonState == HIGH){
	    m_last_button = i+8;
	    return;
	  }
      }

    }


    bool SEQ16_MULTIPEX::isFunctionActive(){
	return m_is_function;
    }

    byte SEQ16_MULTIPEX::getCurrentButton(){
	return m_last_button;
    }

    bool SEQ16_MULTIPEX::isButtonActive(byte num){
	if(num > 15){
	  return false;
	}
	return m_currently_pressed[num];
    }

    void SEQ16_MULTIPEX::writeMultiplexLed(const byte num) {
      byte a;
      byte b;
      byte c;
      intToBinMuliplex(num, a, b, c);
      digitalWrite(m_led_a, a);
      digitalWrite(m_led_b, b);
      digitalWrite(m_led_c, c);
    }

    void SEQ16_MULTIPEX::writeMultiplexBtn(const byte num) {
      byte a;
      byte b;
      byte c;
      intToBinMuliplex(num, a, b, c);
      digitalWrite(m_btn_a, a);
      digitalWrite(m_btn_b, b);
      digitalWrite(m_btn_c, c);
    }

    void SEQ16_MULTIPEX::intToBinMuliplex(const byte i, byte &a, byte &b, byte &c){
      switch (i) {
	case 0:
	  a = LOW;
	  b = LOW;
	  c = LOW;
	  break;
	case 1:
	  a = HIGH;
	  b = LOW;
	  c = LOW;
	  break;
	case 2:
	  a = LOW;
	  b = 1;
	  c = LOW;
	  break;
	case 3:
	  a = HIGH;
	  b = HIGH;
	  c = LOW;
	  break;
	case 4:
	  a = LOW;
	  b = LOW;
	  c = HIGH;
	  break;
	case 5:
	  a = HIGH;
	  b = LOW;
	  c = HIGH;
	  break;
	case 6:
	  a = LOW;
	  b = HIGH;
	  c = HIGH;
	  break;
	case 7:
	  a = HIGH;
	  b = HIGH;
	  c = HIGH;
	  break;
      } 
    }