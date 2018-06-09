#include <phys253.h> 

#define PIN 0
int signal;


void setup() {

  #include <phys253setup.txt>
  pinMode(PIN,INPUT);
}

void loop(){


	signal = analogRead(PIN);
	LCD.print(signal*(5.77 + 5.17)/2);
	LCD.print(" mV");
	delay(100);
	LCD.clear();


}