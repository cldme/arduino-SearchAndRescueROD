int motorMinus = 3;
int motorPlus = 4;

int motorEN = 5;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200); // ethernet cable or WiFi
  // open serial for debugging (in Arduino IDE)
  Serial.begin(9600);

  // configure motor pins
  pinMode(motorPlus, OUTPUT);
  pinMode(motorMinus, OUTPUT);
  pinMode(motorEN, OUTPUT);

  // read the input buffer until it is empty
  // any character in the buffer is ignored
  while (Serial1.available())
     Serial1.read();
}

void loop() {
  // put your main code here, to run repeatedly:

  // if information is available in on the serial, read it
  if(Serial1.available() > 0) {
    char key = Serial1.read();
    // press 'o' to open Cd tray and 'p' to close it
    // press 'k' to progressively open and 'l' to progressively close 
    switch(key) {
      case 'o':
        digitalWrite(motorEN, HIGH);
        digitalWrite(motorPlus, HIGH);
        digitalWrite(motorMinus, LOW);
        Serial.println("Open");
        delay(2000);
        stopMotors();
      break;
      case 'p':
        digitalWrite(motorEN, HIGH);
        digitalWrite(motorPlus, LOW);
        digitalWrite(motorMinus, HIGH);
        Serial.println("Close");
        delay(2000);
        stopMotors();
      break;
      case 'k':
      digitalWrite(motorEN, HIGH);
      digitalWrite(motorPlus, HIGH);
      digitalWrite(motorMinus, LOW);
      delay(200);
      stopMotors();
      break;
      case 'l':
      digitalWrite(motorEN, HIGH);
      digitalWrite(motorPlus, LOW);
      digitalWrite(motorMinus, HIGH);
      delay(200);
      stopMotors();
      break;
    }
  }
}

void stopMotors() {
  digitalWrite(motorPlus, LOW);
  digitalWrite(motorMinus, LOW);
  digitalWrite(motorEN, LOW);
}

