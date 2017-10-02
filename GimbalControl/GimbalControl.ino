// this program demonstrates the communication from the control laptop
// to the arduino and the control of the two servos in the supplied gimbal
// 
// you need an USB cable to program the arduino

// pin number of on-board LED
int ledPin = 13;

#include <Servo.h>  // standard servo library

Servo servoX; // declare servo objects
Servo servoY;

int posY = 90; // initial servo posititions in degree
int posX = 90;

int servoPinX = A0; // arduino pins used to connect servo control signals
int servoPinY = A1;

// setup() is only run once
void setup() {
  Serial1.begin(115200); // ethernet cable or WiFi
  Serial.begin(9600);
      
  servoX.attach(servoPinX);
  servoY.attach(servoPinY);
  
  servoX.write(posX); // move to middle position
  servoY.write(posY);
  
   
  // read the input buffer until it is empty
  // any character in the buffer is ignored
  while (Serial1.available())
     Serial1.read();
}

// the commands in loop() are repeated forever
void loop() {
  if(Serial1.available() > 0)
  {
    char Command = Serial1.read();
    // if a w,z,a or d is pressed servos move with a step of
    // 5 degrees.
    // s moves to mid position
    switch(Command)
    {
      case 'w':
        if(posY + 5 <= 180) {
          posY = posY + 5;
          servoY.write(posY);
          logPosY();
        }
      break;
      case 'z':
        if(posY - 5 >= 5) {
          posY = posY - 5;
          servoY.write(posY);
          logPosY();
        }
      break;
      case 'a':
        if(posX + 5 <= 180) {
          posX = posX + 5;
          servoX.write(posX);
          logPosX();
        }
      break;
      case 'd':
        if(posX - 5 >= 5) {
          posX = posX - 5;
          servoX.write(posX);
          logPosX();
        }
      break;
      case 's':
        posX = 90;
        servoX.write(posX);
        posY = 90;
        servoY.write(posY);
      break;
    }
  }
}

void logPosX() {
  // logs the X position of the servo to the console
  Serial.print("posX: ");
  Serial.println(posX);
  Serial.println();
}


void logPosY() {
  // logs the Y position of the servo to the console
  Serial.print("posY: ");
  Serial.println(posY);
  Serial.println();
}

