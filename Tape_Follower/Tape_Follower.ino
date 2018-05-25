#include <phys253.h> 
int pin0 = 0;
int pin7 = 7;

void setup() {

  #include <phys253setup.txt>
  //Serial.begin(9600);
  pinMode(pin0,INPUT);
  pinMode(pin1,INPUT);
}

void loop() {
  while ( !(stopbutton()) ) {
      for (int i = 0; i < 4; i++) {
         motorSpeed = knob(6)/4 ;
         LCD.clear();  LCD.home() ;
       // 16 positions on LCD screen:   1234567890123456
         LCD.setCursor(0,0); LCD.print("DC Motor: ");  LCD.print(motorSpeed) ;
         LCD.setCursor(0,1); LCD.print("<stop>");

        motor.speed(i, motorSpeed) ;
        if (stopbutton()) {break;} ;
        delay(knob(7)) ;
        motor.speed(i, -motorSpeed);
        if (stopbutton()) {break;} ;
        delay(knob(7)) ;    
        motor.stop(i) ;
      }
  }
   motor.stop_all() ;

}
