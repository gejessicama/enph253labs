//#include <FreqCount.h>

#include <phys253.h> 

int num = 30000;

int pin = 0;
unsigned long dur = 0;

double avg;

double freq;

void setup() {

  #include <phys253setup.txt>
  //Serial.begin(9600);
  pinMode(pin,INPUT);
}

void loop() {

  for(int i = 0; i < num; i++){
    dur += pulseIn(pin,HIGH);
  }

  avg = dur/(double)num;
  freq =(1000000.0/(2.0 * avg) - 2000);

  
  LCD.print(freq);
  delay(500);
  LCD.clear();
  dur = 0;
  

}
