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

int irPin = 4; //Sensor pin 1 wired to Arduino's pin 2
int statLED = 13; //Toggle the status LED every time Power is pressed
int start_bit = 2200; //Start bit threshold (Microseconds)
int bin_1 = 1000; //Binary 1 threshold (Microseconds)
int bin_0 = 400; //Binary 0 threshold (Microseconds)

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
  
  pinMode(statLED, OUTPUT);
  digitalWrite(statLED, LOW);
  pinMode(irPin, INPUT);
  
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
  constrain(back_left_speed,0,180);
  constrain(back_right_speed,0,180);
  constrain(front_left_speed,0,180);
  constrain(front_right_speed,0,180);
  constrain(arm_position,0,180);
  updateServos();
  int key = getIRKey();        //Fetch the key
  
  if(key != 0) //Ignore keys that are zero
  {
//    Serial.print("Key Recieved: ");
    switch(key)
    {
    
    // press "CH Up" to move forward
    case 144:   // "CH Up" 
      back_left_speed -= 5;  // Increase speed by 5
      back_right_speed += 5;  // Increase speed by 5
      front_left_speed -= 5;  // Increase speed by 5
      front_right_speed += 5;  // Increase speed by 5
      break;
      
    // press "CH Down" to move backward
    case 145:
      back_left_speed += 5;  // Increase speed by 5
      back_right_speed -= 5;  // Increase speed by 5
      front_left_speed += 5;  // Increase speed by 5
      front_right_speed -= 5;  // Increase speed by 5
      break;

    // press "VOL Left" to turn left
      case 147:
      back_left_speed += 5;  // Increase speed by 5
      back_right_speed += 5;  // Increase speed by 5
      front_left_speed += 5;  // Increase speed by 5
      front_right_speed += 5;  // Increase speed by 5
      break;

    // press "VOL Right" to turn right
      case 146:
      back_left_speed -= 5;  // Increase speed by 5
      back_right_speed -= 5;  // Increase speed by 5
      front_left_speed -= 5;  // Increase speed by 5
      front_right_speed -= 5;  // Increase speed by 5
      break;

    // press "Mute" to move arm one way
      case 148:           
      arm_position -= 5;
      break;

    // press "AVTV" to move arm the other way
      case 165:
      arm_position += 5;
      break;

    // press power to stop, will also flash the led so you can check the connection  
      case 149: 
      back_left_speed   = BACKLEFT_STOP; 
      back_right_speed  = BACKRIGHT_STOP; 
      front_left_speed  = FRONTLEFT_STOP; 
      front_right_speed = FRONTRIGHT_STOP; 
      arm_position      = 0;
      if(digitalRead(statLED) != 1) //This toggles the statLED every time power button is hit
        digitalWrite(statLED, HIGH);
      else
        digitalWrite(statLED, LOW);
      break;
    }
  }
}


void updateServos(){
    // Set servos to mid-range, ie, default stop
  back_left.write(back_left_speed);
  back_right.write(back_right_speed);
  front_left.write(front_left_speed);
  front_right.write(front_right_speed);
  arm.write(arm_position);
}

int getIRKey() {
  int data[12];
  int i;

  while(pulseIn(irPin, LOW) < start_bit); //Wait for a start bit
  
  for(i = 0 ; i < 11 ; i++)
    data[i] = pulseIn(irPin, LOW); //Start measuring bits, I only want low pulses
  
  for(i = 0 ; i < 11 ; i++) //Parse them
  {     
    if(data[i] > bin_1) //is it a 1?
      data[i] = 1;
    else if(data[i] > bin_0) //is it a 0?
      data[i] = 0;
    else
      return -1; //Flag the data as invalid; I don't know what it is! Return -1 on invalid data
  }

  int result = 0;
  for(i = 0 ; i < 11 ; i++) //Convert data bits to integer
    if(data[i] == 1) result |= (1<<i);

  return result; //Return key number
} 
