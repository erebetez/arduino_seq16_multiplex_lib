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
	  num = num - 8;
	  digitalWrite(m_led_inhibit, HIGH);
	}

	activateMuliplex(num, TYPE_LED);
    }
    
    
    void SEQ16_MULTIPEX::readButtons(){
      byte buttonState = LOW;

      m_is_function = digitalRead(m_btn_f);


      for(byte i = 0; i < 8; ++i){
	activateMuliplex(i, TYPE_BUTTON);

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
    
    void SEQ16_MULTIPEX::activateMuliplex(byte i, byte type){
      switch (i) {
	case 0:
	  writeMultiplex(LOW, LOW, LOW, type);
	  break;
	case 1:
	  writeMultiplex(HIGH, LOW, LOW, type);
	  break;
	case 2:
	  writeMultiplex(LOW, HIGH, LOW, type);
	  break;
	case 3:
	  writeMultiplex(HIGH, HIGH, LOW, type);
	  break;
	case 4:
	  writeMultiplex(LOW, LOW, HIGH, type);
	  break;
	case 5:
	  writeMultiplex(HIGH, LOW, HIGH, type);
	  break;
	case 6:
	  writeMultiplex(LOW, HIGH, HIGH, type);
	  break;
	case 7:
	  writeMultiplex(HIGH, HIGH, HIGH, type);
	  break;
      } 
    }

    void SEQ16_MULTIPEX::writeMultiplex(byte a, byte b, byte c, byte type) {
      if(type == TYPE_LED){
	writeMultiplexLed(a, b, c);
      }
      if(type == TYPE_BUTTON){
	writeMultiplexBtn(a, b, c);
      }
    }

    void SEQ16_MULTIPEX::writeMultiplexLed(byte a, byte b, byte c) {
      digitalWrite(m_led_a, a);
      digitalWrite(m_led_b, b);
      digitalWrite(m_led_c, c);
    }

    void SEQ16_MULTIPEX::writeMultiplexBtn(byte a, byte b, byte c) {
      digitalWrite(m_btn_a, a);
      digitalWrite(m_btn_b, b);
      digitalWrite(m_btn_c, c);
    }
