#include <phys253.h>          
#include <LiquidCrystal.h>    
#define SERVO 0

int angle = 0;
int ON = 0;

void setup(){
  #include <phys253setup.txt>
  Serial.begin(9600) ;   
  RCServo0.write(0);
  delay(1000);
}

void loop()
{
  //angle = map(knob(6),0,1023,0,180);
  //ON = knob(7) / 4;
  for(int i = 0; i < 180; i++){
  LCD.setCursor(0,0);  LCD.print(i) ; LCD.print(" "); LCD.print(120);
  RCServo0.write(i);
  delay(120);
  //delay(ON);
  //delay(255-ON);
  LCD.clear();
  }
  for(int i = 180; i >0; i--){
  LCD.setCursor(0,0);  LCD.print(i) ; LCD.print(" "); LCD.print(120);
  RCServo0.write(i);
  delay(120);
  //delay(ON);
  //delay(255-ON);
  LCD.clear();
  }
}
  
