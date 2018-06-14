#include <phys253.h> 

#define LEFT_MOTOR 0
#define LPIN 4
#define RIGHT_MOTOR 3
#define RPIN 2

#define right_on 650
#define left_on 120

//PID constants
double Kp = 3;
double Kd = 7;
#define Ki 0

#define MAXSPEED 255 // the maximum speed of the motor
#define NORMAL_SPEED 240 
double Gain; // the gain very assertive

// On tape -> HIGH
// Off tape -> LOW 

int left = 0
int right= 0;
int lastLeft = 0;
int lastRight = 0;

int sumError = 0;
int lError = 0;
int lastError = 0;
int error;
int response = 0;

int rightSpeed = 0;
int leftSpeed = 0;

int sign(int left, int right){
  if(left == right) return 0;
  if(left > right) return -1;
  return 1;
}

int calculatePID(int error,int ErrorSum, int lError){
  int P = error;
  int I = ErrorSum + error;
  int D = lError;
  return ((Kp*P) + (Ki*I) + (Kd*D)) * Gain;
}

void setup() {
  
  #include <phys253setup.txt>
  lastLeft = analogRead(LPIN); // 0 to 1023
  lastRight = analogRead(RPIN); // 0 to 1023
}

void loop() {
  
    left = analogRead(LPIN); 
    right = analogRead(RPIN);
    Gain = map(knob(6),0,1023,0.0,50.0);

    if(left >= left_on && right >= right_on) error = 0;
    else if(left < left_on && right < right_on){
      if(lastError == 5 || lastError == -5) error = lastError 
      else error = 5 * sign(lastLeft,lastRight);
      }
    else error = 1 * sign(left,right);

    error == 0 ? lError = 0 : lError = lastError-error;

   // we are not lost so we should ontinue forward
    response = calculatePID(error, sumError, lError);
    leftSpeed = NORMAL_SPEED - response;
    rightSpeed = NORMAL_SPEED + response;

    lastLeft = left; lastRight = right;

    if(leftSpeed > MAXSPEED){leftSpeed =  MAXSPEED;} if(leftSpeed < -255){leftSpeed = -255;}
    if(rightSpeed > MAXSPEED){rightSpeed =  MAXSPEED;} if(rightSpeed < -255){rightSpeed = -255;}
    motor.speed(LEFT_MOTOR,leftSpeed);
    motor.speed(RIGHT_MOTOR,rightSpeed);
   
    LCD.setCursor(0,0);  LCD.print(Gain);
    delay(10);
    LCD.clear();
    
    motor.stop_all();
}
