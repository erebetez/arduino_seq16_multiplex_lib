/*
  Driver for two Multiplexer driving leds.
 */

#include <seq16_multiplex.h>

SEQ16_MULTIPEX seq;

int m_last_button;

int runner = 0;


void setup() {
  init_test();
}


void loop() {

  seq.readButtons();
  
  if(m_last_button != seq.getCurrentButton()){
    seq.ledOn(seq.getCurrentButton());
    m_last_button = seq.getCurrentButton();
  }
  
  if(seq.isFunctionActive()){
    keepLedOn(runner, seq.getCurrentButton(), 10);
    runner++;
    
    if(runner > 15){
      runner = 0;
    }
  }
  
}


void keepLedOn(int num, int num2, int time){
   for(int i = 0; i < (time / 2); ++i){
     seq.ledOn(num);
     delay(1);
     seq.ledOn(num2);
     delay(1);
   }
}


void init_test(){
  // Test 1
  seq.ledOn(0);
  delay(100);
  for(int j = 0; j < 10; ++j){
    for(int i = 0; i < 16; ++i) {
        seq.ledOn(i);
        delay(10);
    }
  }
  seq.ledOn(0);
  delay(200);

/*
  // Test 2
  seq.ledOn(1);
  delay(800);
  for(int i = 0; i < 16; ++i) {
      keepLedOn(i, i + 1 ,200);
  }
  seq.ledOn(1);
  delay(200);

  // Test 3
  seq.ledOn(2);
  delay(800);
  for(int i = 0; i < 16; ++i) {
      keepLedOn(i, 15 - i ,200);
  }
  seq.ledOn(2);
  delay(200);
 
  // Test 4
  seq.ledOn(3);
  delay(800);
  for(int i = 15; i > 0; --i) {
      seq.ledOn(i);
      delay(150);
      keepLedOn(3 , 11, 100);
  }
  seq.ledOn(3);
  delay(200);  
  */
}
