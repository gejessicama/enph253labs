#include <phys253.h>          
#include <LiquidCrystal.h>    
#define MOTOR 3

int motorSpeed = 0;
int ON = 0;

void setup(){
  #include <phys253setup.txt>
  Serial.begin(9600) ;    
}

void loop()
{
  motorSpeed = map(knob(6),0,1023,-255,255);
  ON = knob(7) / 4;
  LCD.setCursor(0,0);  LCD.print(motorSpeed) ; LCD.print(" "); LCD.print(ON);
  motor.speed(MOTOR,motorSpeed);
  delay(ON);
  motor.stop(MOTOR);
  delay(255-ON);
  LCD.clear();
	
}
