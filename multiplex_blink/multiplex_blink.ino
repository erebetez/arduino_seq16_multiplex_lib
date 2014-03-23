/*
  Driver for two Multiplexer driving leds.
 */

int m_led_inhibit = 2;
int m_led_a = 3;
int m_led_b = 4;
int m_led_c = 5;




void setup() {
  // initialize the digital pin as an output.
  pinMode(m_led_inhibit, OUTPUT); 
  pinMode(m_led_a, OUTPUT);
  pinMode(m_led_b, OUTPUT);
  pinMode(m_led_c, OUTPUT);

}


void loop() {
  // Test 1
  ledOn(1);
  delay(800);
  for(int j = 0; j < 20; ++j){
    for(int i = 1; i <= 16; ++i) {
        ledOn(i);
        delay(10);
    }
  }
  ledOn(1);
  delay(200);

  // Test 2
  ledOn(2);
  delay(800);
  for(int i = 1; i <= 16; ++i) {
      keepLedOn(i, i + 1 ,200);
  }
  ledOn(2);
  delay(200);

  // Test 3
  ledOn(3);
  delay(800);
  for(int i = 1; i <= 16; ++i) {
      keepLedOn(i, 16 - i ,200);
  }
  ledOn(3);
  delay(200);
 
  // Test 4
  ledOn(4);
  delay(800);
  for(int i = 16; i > 1; --i) {
      ledOn(i);
      delay(150);
      keepLedOn(3 , 11, 100);
  }
  ledOn(4);
  delay(200);

}

void keepLedOn(int num, int num2, int time){
   for(int i = 0; i < (time / 2); ++i){
     ledOn(num);
     delay(1);
     ledOn(num2);
     delay(1);
   }
}


void ledOn(int num){

  if(num <= 8){
    digitalWrite(m_led_inhibit, LOW);
  } else {
    num = num - 8;
    digitalWrite(m_led_inhibit, HIGH);
  }

  switch (num) {
    case 1:
      writeMultiplex(LOW, LOW, LOW);
      break;
    case 2:
      writeMultiplex(HIGH, LOW, LOW);
      break;
    case 3:
      writeMultiplex(LOW, HIGH, LOW);
      break;
    case 4:
      writeMultiplex(HIGH, HIGH, LOW);
      break;
    case 5:
      writeMultiplex(LOW, LOW, HIGH);
      break;
    case 6:
      writeMultiplex(HIGH, LOW, HIGH);
      break;
    case 7:
      writeMultiplex(LOW, HIGH, HIGH);
      break;
    case 8:
      writeMultiplex(HIGH, HIGH, HIGH);
      break;
  }
}

void writeMultiplex(int a, int b, int c) {
  digitalWrite(m_led_a, a);
  digitalWrite(m_led_b, b);
  digitalWrite(m_led_c, c);
}
