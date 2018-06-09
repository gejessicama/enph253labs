#include <phys253.h> 

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 3
//from the view of the robot pin 7 is right sensor and pin 0 is left sensor
#define PIN0 0
#define PIN7 7

#define Kp .025 // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd .1 // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp << Kd) 
#define Ki 0.0025

#define MAXSPEED 255 //the max speed of the motor
#define motorSpeed 200 //the speed to go at when on the line
#define PWM 70

// when it is on the tape it will be HIGH
// when it is off it will be LOW
int left = HIGH; //the left sensor
int right= HIGH; // the right sensor

int lastLeft = 0;
int lastRight = 0;
int sumError = 0;

void setup() {
  #include <phys253setup.txt>
  //Serial.begin(9600);
  pinMode(PIN0,INPUT);
  pinMode(PIN7,INPUT);
  
  lastLeft = digitalRead(PIN0); //hexadeciaml
  lastRight = digitalRead(PIN7); //hexadeciaml
}

//int motorSpeed = 0;
int lastError = 0;
int error;

int response = 0;
int rightSpeed = 0;
int leftSpeed = 0;

void loop() {

  left = digitalRead(PIN0); //hexadeciaml
  right = digitalRead(PIN7); //hexadeciaml
  
  if(left == 0 && right ==0){error = 0;} else{error = (left*-1000 + right*1000)/(left + right);}
  //if(lastLeft == 1 && left == 0){right = 1;} else if(lastRight == 1 && right == 0){left = 1;}

  response = Kp * error + Kd * (error - lastError) + Ki*sumError;
//  motorSpeed = (knob(6)/4); 
  leftSpeed = motorSpeed + response;
  rightSpeed = motorSpeed - response;
  if(leftSpeed > MAXSPEED){leftSpeed =  MAXSPEED;} if(leftSpeed < -255){leftSpeed = -255;}
  if(rightSpeed > MAXSPEED){rightSpeed =  MAXSPEED;} if(rightSpeed < -255){rightSpeed = -255;}
  
  LCD.setCursor(0,0);  LCD.print(rightSpeed); LCD.print(" "); LCD.print(leftSpeed);
  LCD.setCursor(0,1);  LCD.print(right); LCD.print(" "); LCD.print(left);

/*
  if(left == HIGH && right == HIGH){
      motor.speed(LEFT_MOTOR,motorSpeed);
      motor.speed(RIGHT_MOTOR,motorSpeed);
      
  } else if (left == LOW && right == HIGH){
      motor.speed(LEFT_MOTOR,motorSpeed); 
      motor.speed(RIGHT_MOTOR,0);
      
  } else if (left == HIGH && right == LOW){
      motor.speed(LEFT_MOTOR,0);
      motor.speed(RIGHT_MOTOR,motorSpeed);
      
  } else {
      motor.speed(LEFT_MOTOR,motorSpeed);
      motor.speed(RIGHT_MOTOR,0);
  }
  */

  motor.speed(LEFT_MOTOR,leftSpeed);
  motor.speed(RIGHT_MOTOR,rightSpeed);

  delay(PWM);
  LCD.clear();
  motor.stop_all();
  lastLeft = left; lastRight=right;
  lastError = error;
  sumError += error;
}
