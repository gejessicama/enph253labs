#include <phys253.h> 
#include <math.h>

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 3
#define LTHRESHOLD 200
#define STHRESHOLD 100

#define ON_TAPE 600
#define OFF_TAPE 300

#define RPIN 2
#define LPIN 4

//from the view of the robot pin 7 is right sensor and pin 0 is left 

#define Kp .25 // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd 1 // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp << Kd) 
#define Ki 0.025

#define MAXSPEED 255 //the max speed of the motor
//#define motorSpeed 240 //the speed to go at when on the line
#define PWM 70
#define CONST_ERR 100

// when it is on the tape it will be HIGH
// when it is off it will be LOW
int left = 0; //the left sensor
int right= 0; // the right sensor

int lastLeft = 0;
int lastRight = 0;
int sumError = 0;

int sign(int left, int right){
  if(left == right)
    return 0;
  if(left > right)
    return 1;
  return -1;
}

void setup() {
  #include <phys253setup.txt>
  //Serial.begin(9600);
  
  lastLeft = analogRead(LPIN); //hexadeciaml
  lastRight = analogRead(RPIN); //hexadeciaml
}

//int motorSpeed = 0;
int lastError = 0;
int error;

int response = 0;
int rightSpeed = 0;
int leftSpeed = 0;
double difference;

void loop() {

  for(int i = 0; i<3; i++){
  left += analogRead(LPIN); //hexadeciaml
  right += analogRead(RPIN); //hexadeciaml
  }
  left /= 3;
  right /= 3;
  difference = fabs((double)(left - right));

  
  //here is the condition for on the tape
  if(left >= ON_TAPE || right >= ON_TAPE){ 
  if(difference <= STHRESHOLD){error = 0;}
  else if(difference <= LTHRESHOLD){error = sign(left,right) * 5;}
  else{error = left - right;}
  }else{
    if(left >= OFF_TAPE || right >= OFF_TAPE && left != right){
      error = (left - right) * 1 + sign(left,right)*CONST_ERR;
    }else if (left == right){
      error = lastleft - lastright
    }
  }
  //if(lastLeft == 1 && left == 0){right = 1;} else if(lastRight == 1 && right == 0){left = 1;}

  response = Kp * error + Kd * (error - lastError) + Ki*sumError;
//  motorSpeed = (knob(6)/4); 
  leftSpeed = 50 + response;
  rightSpeed = 50 - response;
  if(leftSpeed > MAXSPEED){leftSpeed =  MAXSPEED;} if(leftSpeed < -255){leftSpeed = -255;}
  if(rightSpeed > MAXSPEED){rightSpeed =  MAXSPEED;} if(rightSpeed < -255){rightSpeed = -255;}
  
  LCD.setCursor(0,0);  LCD.print(rightSpeed); LCD.print(" "); LCD.print(leftSpeed);
  LCD.setCursor(0,1);  LCD.print(RPIN); LCD.print(": "); LCD.print(right); LCD.print(" "); LCD.print(LPIN); LCD.print(": "); LCD.print(left);

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
  left =0;
  right = 0;
}
