/*
  Driver for two Multiplexer driving leds.
 */

#define TYPE_LED 0

#define TYPE_BUTTON 1


const int m_led_inhibit = 2;
const int m_led_a = 3;
const int m_led_b = 4;
const int m_led_c = 5;

const int m_btn_a = 6;
const int m_btn_b = 7;
const int m_btn_c = 8;
const int m_btn_1 = 10;
const int m_btn_2 = 11;

const int m_btn_f = 12;

int m_current_button; // TODO make array;
int m_last_button;

void setup() {
  Serial.begin(9600);
    
  Serial.println("Hello!");
    
  init_pins();

//  test_init();
 
  ledOn(1);
  
  
}


void loop() {

//  m_last_button = m_current_button;
  readButtons();
  
//  if(m_last_button != m_current_button){
//    ledOn(m_current_button);
//  }

  
//   Serial.println(m_current_button);
   delay(1000);
}


void init_pins(){
  // initialize the digital pin as an output.
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

  activateMuliplex(--num, TYPE_LED);
}



void readButtons(){
  int buttonState = LOW;
  
  
  Serial.println("__ readButtons __");
  buttonState = digitalRead(m_btn_f);
  Serial.print("Function:\t");
  Serial.print(buttonState);
  Serial.println("");
     
  for(int i = 0; i < 8; ++i){
    activateMuliplex(i, TYPE_BUTTON);
    
     Serial.print("Buttons 1-8:\t");
     Serial.print(i+1);
     Serial.print("\t");
     buttonState = digitalRead(m_btn_1);
      
     Serial.print(buttonState);
     Serial.println("");
      
      if(buttonState == HIGH){
        m_current_button = (i+1);
//             Serial.println(m_current_button);
        ledOn(m_current_button);
        m_current_button = (i + 1);  
        
        return; 
      }

     Serial.print("Buttons 9-16:\t");      
     Serial.print(i+9);
     Serial.print("\t");     
     buttonState = digitalRead(m_btn_2); 
      
     Serial.print(buttonState);
     Serial.println("");
        
     if(buttonState == HIGH){
          m_current_button = (i+9);
//             Serial.println(m_current_button);
          ledOn(m_current_button);
          m_current_button = (i + 9); // seccond 8 - 16;   
           
        return;   
      }
  }
  
  
}


void activateMuliplex(int i, int type){
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

void writeMultiplex(int a, int b, int c, int type) {
  if(type == TYPE_LED){
    writeMultiplexLed(a, b, c);
  }
  if(type == TYPE_BUTTON){
    writeMultiplexBtn(a, b, c);
  }
}

void writeMultiplexLed(int a, int b, int c) {
  digitalWrite(m_led_a, a);
  digitalWrite(m_led_b, b);
  digitalWrite(m_led_c, c);
}

void writeMultiplexBtn(int a, int b, int c) {
  digitalWrite(m_btn_a, a);
  digitalWrite(m_btn_b, b);
  digitalWrite(m_btn_c, c);
}


void test_init(){
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
