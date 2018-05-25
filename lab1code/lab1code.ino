#include <phys253.h>

const int  buttonPin = 0;   
int  buttonState = 0;
int lastButtonState = 0; 
int buttonPushCounter = 0;


void setup() {
  #include <phys253setup.txt>
  Serial.begin(9600);
}

void loop() {
  
unsigned long startTime = micros();

while (buttonPushCounter < 200){
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
      buttonPushCounter++;
  }
  lastButtonState = buttonState;
}
double endTime = micros();

double elapsedTime = endTime - startTime;
Serial.println(startTime);
Serial.println(endTime);
Serial.println(100000000.0/elapsedTime);
Serial.println("");

}
