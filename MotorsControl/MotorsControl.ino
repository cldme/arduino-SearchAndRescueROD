int IN1 = 5;
int IN2 = 3;

char keyPress = ' ';
bool hasKey = false;

unsigned long myTime;
unsigned long currentTime;

void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  Serial1.begin(115200); // ethernet cable or WiFi
  // open serial for debugging (in Arduino IDE)
  Serial.begin(9600);

  // configure motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  keyPress = ' ';
  hasKey = false;

  // read the input buffer until it is empty
  // any character in the buffer is ignored
  while (Serial1.available())
     Serial1.read();

  Serial.println("Arduino Serial Started !");
}

void loop() {
  // put your main code here, to run repeatedly:
  // update current time
  currentTime = millis();
  hasKey = false;
  
  // if information is available in on the serial, read it
  if(Serial1.available() > 0) {
    char key = Serial1.read();
    hasKey = true;
    // press 'w' or 's' to move the motor in either direction
    // press 'q' to stop
    
    switch(key) {
      case 'w':
        keyPress = 'w';
        myTime = millis();
        analogWrite(IN1, 255);
        analogWrite(IN2, 0);
      break;
      case 's':
        keyPress = 's';
        myTime = millis();
        analogWrite(IN1, 0);
        analogWrite(IN2, 255);
      break;
      case 'q':
        stopMotors();
      break;
    }
  }

  if(currentTime - myTime >= 70 && !hasKey) {
    if(keyPress != ' ')
      Serial.println("Motors stopped");
    keyPress = ' ';
    stopMotors();
  }

  delay(5);
}

void stopMotors() {
  // stop the motors
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
}
