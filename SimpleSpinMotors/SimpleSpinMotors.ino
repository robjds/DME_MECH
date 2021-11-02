// DME Mech Starter Kit: Simple 4WD Car

#include <Servo.h>
// Create some servo instances
Servo front_left;
Servo front_right;
Servo back_left;
Servo back_right;
Servo arm;
// Sending signals to servos:
// 90 is no servo movement (mid-point)
// 0 is full speed forward
// 180 is full speed backward

// not all continuous servos stop at exactly 90, so you can adjust default stop point here
#define BACKLEFT_STOP 90  
#define BACKRIGHT_STOP 90
#define FRONTLEFT_STOP 90  
#define FRONTRIGHT_STOP 90

int back_left_speed = BACKLEFT_STOP;
int back_right_speed = BACKRIGHT_STOP;
int front_left_speed = FRONTLEFT_STOP;
int front_right_speed = FRONTRIGHT_STOP;
int arm_position = 90;

// the 'setup' section of the code runs once when you power on the arduino
void setup() {
  // 'Attach' the servos on Arduino PWM pins 3, 5, 6, 10, 11
  // This line of code activates the servos so you can send commands
  back_left.attach(3);
  back_right.attach(10);
  front_left.attach(5);
  front_right.attach(11);
  arm.attach(6);
  
  // Set servos to mid-range, ie, default stop
  back_left.write(BACKLEFT_STOP);
  back_right.write(BACKRIGHT_STOP);
  front_left.write(FRONTLEFT_STOP);
  front_right.write(FRONTRIGHT_STOP);
  arm.write(90);
}

// the 'loop' section of the code runs over and over again until the board is reset/turned off.
void loop(){

int motorspeed = 30; // adjust this number to change the motor speed.

// run the motors for 5 seconds and then turn them off

if (millis()<5000){
  back_left_speed   = BACKLEFT_STOP   + motorspeed; 
  back_right_speed  = BACKRIGHT_STOP  - motorspeed; 
  front_left_speed  = FRONTLEFT_STOP  + motorspeed; 
  front_right_speed = FRONTRIGHT_STOP - motorspeed ; 
  arm_position      =90;
} else{
// if more than 5s has passed, stop the motors
  back_left_speed   = BACKLEFT_STOP; 
  back_right_speed  = BACKRIGHT_STOP; 
  front_left_speed  = FRONTLEFT_STOP; 
  front_right_speed = FRONTRIGHT_STOP; 
  arm_position      = 0;
}
  updateServos();
}

void updateServos(){
  back_left.write(back_left_speed);
  back_right.write(back_right_speed);
  front_left.write(front_left_speed);
  front_right.write(front_right_speed);
  arm.write(arm_position);
}
