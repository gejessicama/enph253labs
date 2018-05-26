#include <phys253.h> 

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 3
#define PIN0 0
#define PIN7 7
//from the view of the robot pin 7 is right sensor and pin 0 is left sensor

// when it is on the tape it will be HIGH
// when it is off it will be LOW
int left = HIGH; //the left sensor
int right= HIGH; // the right sensor

void setup() {
  #include <phys253setup.txt>
  //Serial.begin(9600);
  pinMode(PIN0,INPUT);
  pinMode(PIN7,INPUT);
}

int motorSpeed = 0;
int PWM = 0;

void loop() {

  left = digitalRead(PIN0);
  right = digitalRead(PIN7);
  
  PWM = knob(7);
  motorSpeed = (knob(6)/4);
  
  LCD.setCursor(0,0); LCD.print("DC:");  LCD.print(motorSpeed) ; LCD.print(left);
  LCD.setCursor(0,1); LCD.print("PWM:");  LCD.print(PWM) ; LCD.print(right);

  if(left == HIGH && right == HIGH){
      motor.speed(LEFT_MOTOR,motorSpeed);
      motor.speed(RIGHT_MOTOR,motorSpeed);
      delay(PWM);
  } else if (left == LOW && right == HIGH){
      motor.speed(LEFT_MOTOR,motorSpeed);
      motor.speed(RIGHT_MOTOR,0);
      delay(PWM);
  } else if (left == HIGH && right == LOW){
      motor.speed(LEFT_MOTOR,0);
      motor.speed(RIGHT_MOTOR,motorSpeed);
      delay(PWM);
  } else {
      motor.speed(LEFT_MOTOR,motorSpeed);
      motor.speed(RIGHT_MOTOR,0);
      delay(PWM);
  }
  motor.stop_all();
}
