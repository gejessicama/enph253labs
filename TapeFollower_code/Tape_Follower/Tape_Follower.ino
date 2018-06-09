#include <phys253.h> 

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 3
#define PIN0 0
#define PIN7 7
//from the view of the robot pin 7 is right sensor and pin 0 is left sensor

#define Kp 0.01 // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd 0.1 // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 

#define MAXSPEED 255 //the max speed of the motor
#define NORMALSPEED 240 //the speed to go at when on the line


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

int lastError = 0;
int error;

int lastLeft = 0;
int lastRight = 0;
int response = 0;
int rightSpeed = 0;
int leftSpeed = 0;

void loop() {

  left = digitalRead(PIN0); //hexadeciaml
  right = digitalRead(PIN7); //hexadeciaml

  //if(lastLeft == 1 && left == 0){right = 1;} else if(lastRight == 1 && right == 0){left = 1;}
  if(left == 0 && right ==0){error = 0;} else{error = (left*-1 + right*1)/(left + right);}

  response = Kp * error + Kd * (error - lastError);
  motorSpeed = (knob(6)/4); 
  leftSpeed = motorSpeed + response;
  leftSpeed = motorSpeed - response;
  if(leftSpeed > MAXSPEED){leftSpeed =  MAXSPEED;} if(leftSpeed < 0){leftSpeed = 0;}
  if(rightSpeed > MAXSPEED){rightSpeed =  MAXSPEED;} if(rightSpeed < 0){rightSpeed = 0;}

  PWM = 125;
  
  LCD.setCursor(0,0);  LCD.print(motorSpeed) ; LCD.print(" "); LCD.print(PWM);
  LCD.setCursor(0,1);  LCD.print(right); LCD.print(" "); LCD.print(left);

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

  delay(PWM);
  LCD.clear();
  motor.stop_all();
  lastLeft = left; lastRight=right;
  lastError = error;
}
