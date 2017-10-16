// include servo library
#include <Servo.h>

// declare two servo objects
Servo servoX;
Servo servoY;

// declare failsafe boolean
boolean OVERRIDE = false;

// step for moving servos
// increase this value to move servos more
int deg = 5;

// declare initial servo positions in degrees
int posX = 90;
int posY = 90;

// declare pins used to control the servos
int servoPinX = A0;
int servoPinY = A1;
// declare pins used to control the motors
int IN3 = 7;
int IN4 = 6;

void setup() {
  // put your setup code here, to run once:

  // serial used for ethernet or WiFi
  Serial1.begin(115200);
  // serial used for debugging
  Serial.begin(9600);

  // configure the pin modes
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // attach the servos to the servo objects
  servoX.attach(servoPinX);
  servoY.attach(servoPinY);
  // move servos to the initial position
  servoX.write(posX);
  servoY.write(posY);

  // clear the serial buffer
  while(Serial1.available()) {
    Serial1.read();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // check if OVERRIDE is true
  // loop does NOT EXECUTE when OVERRIDE is true (failsafe)
  if(!OVERRIDE) {
    // read input from the serial
    if(Serial1.available() > 0) {
      char key = Serial1.read();
      // for a list of commands, please consult code guide
      switch(key) {
        case 'w':
          rotateServo('Y', deg);
          break;
        case 's':
          rotateServo('Y', -deg);
          break;
        case 'a':
          rotateServo('X', deg);
          break;
        case 'd':
          rotateServo('X', -deg);
          break;
        case 'q':
          rotateServo('Z', 90);
          break;
        // MOTOR; needs more working, add methods
        case 'o':
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          delay(200);
          stopMotors();
          break;
        case 'p':
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          delay(200);
          stopMotors();
          break;
      }
    }
  }
}

// function used for rotating servoX / servoY
void rotateServo(char X, int value) {
  // rotate servoX
  if(X == 'X' && 5 <= value + posX && value + posX <= 180) {
    posX += value;
    servoX.write(posX);
  }

  // rotate servoY
  if(X == 'Y' && 5 <= value + posY && value + posY <= 180) {
    posY += value;
    servoY.write(posY);
  }

  // reset both servos to 90 deg
  if(X == 'Z' && value == 90) {
    posX = posY = 90;
    servoX.write(posX);
    servoY.write(posY);
  }

  // log the new position to the console
  logPosition(X);
}

// function used for printing the position of the servos to the console
void logPosition(char X) {
  if(X == 'X') {
    Serial.print("posX: ");
    Serial.println(posX);
  }

  if(X == 'Y') {
    Serial.print("posY: ");
    Serial.println(posY);
  }
}

// function used for stopping the motors
void stopMotors() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

