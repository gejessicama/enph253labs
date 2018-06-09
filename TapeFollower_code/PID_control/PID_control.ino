#include <phys253.h> 
#include <math.h>

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 3


#define ON_TAPE 600
#define OFF_TAPE 300

//from the robot's perspective
#define RPIN 2
#define LPIN 4

//PID constants
#define Kp 25 
#define Kd 0 
#define Ki 0

#define MAXSPEED 255 //the maximum speed of the motor
#define NORMAL_SPEED 225
#define PWM 70
#define CONST_ERR 100

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
bool lost;

int sign(int left, int right){
  if(left == right)
    return 0;
  if(left > right)
    return -1;
  return 1;
}

int calculatePID(int error,int previousError,int ErrorSum)
{
  int P = error;
  int I = ErrorSum + error;
  int D = error-previousError;
  return (Kp*P) + (Ki*I) + (Kd*D);
}

void setup() {
  #include <phys253setup.txt>
  Serial.begin(9600);
  
  lastLeft = analogRead(LPIN); //hexadeciaml
  lastRight = analogRead(RPIN); //hexadeciaml
}


void loop() {

  
    //read sensors
    left = -1*analogRead(LPIN); //0 to -1023
    right = analogRead(RPIN); //0 to 1023

    //calc difference and position
    avg = (left + right) / 2.0;


    if(left >= -1 * OFF_TAPE && right <= OFF_TAPE){ //they are not on tape
        if(fabs(avg - 0.01) > 0.1){
        // left and right not equal
            error = avg * 2;
        }else{ //the values are equal but we do not see tape
            error = 0;
            lost =true;
        }
    }else{
        error = avg;
        lost = false;
    }

    if(lost != true){ // we are not lost so we should ontinue forward
        response = calculatePID(error,lastError,sumError);
        leftSpeed = NORMAL_SPEED + response;
        rightSpeed = NORMAL_SPEED - response;

        lastLeft = left; lastRight=right;
    }else{ // we are lost so we need to go back using our previous reading
        leftSpeed = MAXSPEED*sign(lastLeft*-1,lastRight);
        rightSpeed = -MAXSPEED*sign(lastLeft*-1,lastRight);

    }

    if(leftSpeed > MAXSPEED){leftSpeed =  MAXSPEED;} if(leftSpeed < -255){leftSpeed = -255;}
    if(rightSpeed > MAXSPEED){rightSpeed =  MAXSPEED;} if(rightSpeed < -255){rightSpeed = -255;}
    
    LCD.setCursor(0,0);  LCD.print(rightSpeed); LCD.print(" "); LCD.print(leftSpeed);
    LCD.setCursor(0,1);  LCD.print(RPIN); LCD.print(": "); LCD.print(right); LCD.print(" "); LCD.print(LPIN); LCD.print(": "); LCD.print(left);
    
    motor.speed(LEFT_MOTOR,leftSpeed);
    motor.speed(RIGHT_MOTOR,rightSpeed);
    delay(10);
    LCD.clear();
    
    motor.stop_all();
    lastError = error; sumError += error;
}
