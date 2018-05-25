#include <phys253.h>            

int var = LOW;

int pin = 0;

void setup() {

  #include <phys253setup.txt>
  Serial.begin(9600);
}

void loop() {
  //var = portRead(pin);
  var = digitalRead(pin);
  if (var == HIGH){
    LCD.print("ON");
  }else{
    LCD.print("OFF");
  }

  delay(200);

  LCD.clear();
  

}
