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

// define keyboard inputs

#define MOVE_FORWARD 'w'
#define MOVE_BACK 's'
#define MOVE_LEFT 'a'
#define MOVE_RIGHT 'd'

#define FULL_STOP 'e'

#define ARM_LEFT 'o'
#define ARM_RIGHT 'p'


// the 'setup' section of the code runs once when you power on the arduino
void setup() {
  
  // Open a serial channel to talk to the board
  Serial.begin(9600); 
  
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

  //  wait for the Serial monitor to be opened
  while(!Serial){}
}

// the 'loop' section of the code runs over and over again until the board is reset/turned off.
void loop(){
  char byte = 0;
  // press q to cancel and exit
  while (byte != 'q') {
    // read serial input
    Serial.readBytes(&byte, 1);
    
    // press w to move forward
    if (byte == MOVE_FORWARD) {
      back_left_speed -= 5;  // Increase speed by 5
      back_right_speed += 5;  // Increase speed by 5
      front_left_speed -= 5;  // Increase speed by 5
      front_right_speed += 5;  // Increase speed by 5
      Serial.print("moving forward \n");
      byte = 0;
    }
    // press s to move backward
    if (byte == MOVE_BACK) {
      back_left_speed += 5;  // Increase speed by 5
      back_right_speed -= 5;  // Increase speed by 5
      front_left_speed += 5;  // Increase speed by 5
      front_right_speed -= 5;  // Increase speed by 5
      Serial.print("moving back \n");
      byte = 0;
    }
    // press a to turn left
    if (byte == MOVE_LEFT) {
      back_left_speed += 5;  // Increase speed by 5
      back_right_speed += 5;  // Increase speed by 5
      front_left_speed += 5;  // Increase speed by 5
      front_right_speed += 5;  // Increase speed by 5
      Serial.print("moving left \n");
      byte = 0;
    }
    // press d to turn right
    if (byte == MOVE_RIGHT) {
      back_left_speed -= 5;  // Increase speed by 5
      back_right_speed -= 5;  // Increase speed by 5
      front_left_speed -= 5;  // Increase speed by 5
      front_right_speed -= 5;  // Increase speed by 5
      Serial.print("moving left \n");
      byte = 0;
    }
    // press o to move arm to the left
    if (byte == ARM_LEFT) {
      arm_position -= 5;
      Serial.print("moving right \n");
      byte = 0;
    }
    // press p to move arm to the right
    if (byte == ARM_RIGHT) {
      arm_position += 5;
      Serial.print("moving right \n");
      byte = 0;
    }
    // press e to default stop
    if (byte == FULL_STOP) {
      back_left.write(BACKLEFT_STOP);
      back_right.write(BACKRIGHT_STOP);
      front_left.write(FRONTLEFT_STOP);
      front_right.write(FRONTRIGHT_STOP);
      arm.write(90);
      Serial.print("full stop \n");
      byte = 0;
    }
    updateServos();
  }
  Serial.print("Done \n");
  Serial.end();
}


void updateServos(){
    // Set servos to mid-range, ie, default stop
  back_left.write(back_left_speed);
  back_right.write(back_right_speed);
  front_left.write(front_left_speed);
  front_right.write(front_right_speed);
  arm.write(arm_position);
}


