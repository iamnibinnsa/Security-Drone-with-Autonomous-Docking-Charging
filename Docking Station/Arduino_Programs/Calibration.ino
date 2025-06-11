// Daniel Gonzalez
// AME 504: Mechatronic Systems
// danielg2@usc.edu

// Motor A pins
const int motorA1 = 3;
const int motorA2 = 4;
const int enableA = 9;

// Motor B pins
const int motorB1 = 5;
const int motorB2 = 6;
const int enableB = 10;

// Speed (PWM)
const int motorSpeed = 200;

void setup() {
  Serial.begin(9600);

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(enableA, OUTPUT);

  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(enableB, OUTPUT);

  stopAllMotors();

  Serial.println("Ready for motor commands.");
  Serial.println("a: A forward | z: A backward | s: Stop A");
  Serial.println("k: B forward | m: B backward | l: Stop B");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case 'a':
        moveMotorA(true);
        Serial.println("Motor A Forward");
        break;
      case 'z':
        moveMotorA(false);
        Serial.println("Motor A Backward");
        break;
      case 's':
        stopMotorA();
        Serial.println("Motor A Stopped");
        break;
      case 'k':
        moveMotorB(true);
        Serial.println("Motor B Forward");
        break;
      case 'm':
        moveMotorB(false);
        Serial.println("Motor B Backward");
        break;
      case 'l':
        stopMotorB();
        Serial.println("Motor B Stopped");
        break;
      default:
        Serial.println("Unknown command");
    }
  }
}

void moveMotorA(bool forward) {
  if (forward) {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
  } else {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
  }
  analogWrite(enableA, motorSpeed);
}

void stopMotorA() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  analogWrite(enableA, 0);
}

void moveMotorB(bool forward) {
  if (forward) {
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
  } else {
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
  }
  analogWrite(enableB, motorSpeed);
}

void stopMotorB() {
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  analogWrite(enableB, 0);
}

void stopAllMotors() {
  stopMotorA();
  stopMotorB();
}
