#include <phys253.h> 
#include <math.h>

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 3

#define right_on 650
#define left_on 120

//from the robot's perspective
#define RPIN 2
#define LPIN 4

//PID constants
double Kp;
double Kd;
#define Ki 0

#define MAXSPEED 255 //the maximum speed of the motor
#define NORMAL_SPEED 240
#define PWM 70
#define CONST_ERR 100
int Gain =  1; // the gain very assertive

// when it is on the tape it will be high
// when it is off it will be low
int left = 0; //the left sensor
int right= 0; // the right sensor

int lastLeft = 0;
int lastRight = 0;

int sumError = 0;
int lastError = 0;
int error;
int response = 0;

int rightSpeed = 0;
int leftSpeed = 0;
double avg;
int lError = 0;

int sign(int left, int right){
  if(left == right) return 0;
  if(left > right) return -1;
  return 1;
}

int calculatePID(int error,int ErrorSum, int lError)
{
  int P = error;
  int I = ErrorSum + error;
  int D = error - lError;
  return ((Kp*P) + (Ki*I) + (Kd*D)) * Gain;
}


void setup() {
  #include <phys253setup.txt>
  
  lastLeft = analogRead(LPIN); //hexadeciaml
  lastRight = analogRead(RPIN); //hexadeciaml
}


void loop() {


    //read sensors
    left = analogRead(LPIN); //0 to -1023
    right = analogRead(RPIN); //0 to 1023

    Kp = map(knob(6),0,1023,0,100);
    Kd = map(knob(7),0,1023,0,15);

    //calc difference and position
    //avg = (left + right) / 2.0;

    if(left >= left_on && right >= right_on){
      error = 0;
    }else if(left < left_on && right < right_on){
      error = 5 * sign(lastLeft,lastRight);
    }else{
      error = 1 * sign(left,right);
    }

   // we are not lost so we should ontinue forward
    response = calculatePID(error,sumError,lError);
    leftSpeed = NORMAL_SPEED - response;
    rightSpeed = NORMAL_SPEED + response;
    lastLeft = left; lastRight=right;

    if(leftSpeed > MAXSPEED){leftSpeed =  MAXSPEED;} if(leftSpeed < -255){leftSpeed = -255;}
    if(rightSpeed > MAXSPEED){rightSpeed =  MAXSPEED;} if(rightSpeed < -255){rightSpeed = -255;}
    
    //LCD.setCursor(0,0);  LCD.print(rightSpeed); LCD.print(" "); LCD.print(leftSpeed);
    //LCD.setCursor(0,1);  LCD.print(RPIN); LCD.print(": "); LCD.print(right); LCD.print(" "); LCD.print(LPIN); LCD.print(": "); LCD.print(left);
    LCD.setCursor(0,0);  LCD.print(Kp); LCD.print("   "); LCD.print(Kd);
    
    motor.speed(LEFT_MOTOR,leftSpeed);
    motor.speed(RIGHT_MOTOR,rightSpeed);
    delay(10);
    LCD.clear();
    
    motor.stop_all();
    lastError = error; sumError += error;

    //sumError > 10 ? sumError = 10 : sumError=sumError;
    if(lastError != error){
      lError = lastErrorr;
    }
}
