# DME_MECH
Starter code for the basic chassis components.
Refer to the notes for how to wire up your components. These codes will allow you to move the wheels/arm with your remote. 

**SimpleSpinMotors** will just make the motors spin for 5 seconds, and does not use the remote (you will need to reupload the code to change wheel speeds). This is to test if your motors are all working, and to trim the zero-speed point.

**IR_Remote_Tester** does not move the motors, it will just turn the board LED on or off in response to the buttons. This is to test if your remote is working.

**IR_MotorController** moves the motors in response to remote commands.

This is just a minimal example to get you started. Using the IR remote for control is slow and clunky, i.e. not a good idea for the final design.

Download the example code (in the folder) and open it in the Arduino IDE, then upload to your Adafruit board.
