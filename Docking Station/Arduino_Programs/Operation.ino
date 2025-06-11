// Daniel Gonzalez
// AME 504: Mechatronic Systems
// danielg2@usc.edu

// LED Pin
int ledPin = 8;

// Ultrasonic Sensor Pins
const int trigPin = 11;
const int echoPin = 12;

// Motor A pins
const int motorA1 = 3;   // IN1
const int motorA2 = 4;   // IN2
const int enableA = 9;   // ENA (PWM capable)

// Motor B pins
const int motorB1 = 5;   // IN3
const int motorB2 = 6;   // IN4
const int enableB = 10;  // ENB (PWM capable)

// Constants
const int minDistance = 2;        // cm - lower bound
const int maxDistance = 14;       // cm - upper bound
const int motorSpeed = 220;       
const int motorRunTime = 2000;    // ms

bool objectDetected = false;

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set control pins as outputs
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(enableA, OUTPUT);
  analogWrite(enableA, 0);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  

  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(enableB, OUTPUT);
  analogWrite(enableB, 0);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  

  stopMotor();

  //  Blink LED once at startup
  digitalWrite(ledPin, HIGH);
  delay(300);
  digitalWrite(ledPin, LOW);
}

void loop() {
  long distance = getDistance();

  if (distance >= minDistance && distance <= maxDistance) {
    if (!objectDetected) {
      Serial.println("Object detected!");
      objectDetected = true;
      ledSequence();

      activateMotor();
      delay(motorRunTime);
      stopMotor();
    }
  } else {
    if (objectDetected) {
      objectDetected = false;  // Reset when object leaves the detection range
    }
    Serial.println("Nothing is there");
  }

  delay(200);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout: 30ms
  if (duration == 0) return -1;

  return duration * 0.034 / 2; // Convert to cm
}

void activateMotor() {
 // Move Motor A forward
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  analogWrite(enableA, 255); // Full speed
  delay(4200);

  // Stop Motor A
  analogWrite(enableA, 0);

  // Move Motor B forward
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(enableB, 225); // 225 PWM speed
  delay(1000);

  // Stop Motor B
  analogWrite(enableB, 0);

  //Pause between cycles
  delay(3000);

    // Move Motor A forward
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  analogWrite(enableA, 255); // Full speed
  delay(3000);

  // Stop Motor A
  analogWrite(enableA, 0);

  // Move Motor B forward
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(enableB, 225); // 225 PWM speed
  delay(1000);

  // Stop Motor B
  analogWrite(enableB, 0);

  // Pause between cycles
  delay(3000);
}

void stopMotor() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  analogWrite(enableA, 0);

  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  analogWrite(enableB, 0);
}

void ledSequence() {
  digitalWrite(ledPin, HIGH);
  delay(100);  // short blink
  digitalWrite(ledPin, LOW);
  delay(100);

  digitalWrite(ledPin, HIGH);
  delay(300);  // longer blink
  digitalWrite(ledPin, LOW);
  delay(100);

  digitalWrite(ledPin, HIGH);
  delay(100);  // short blink
  digitalWrite(ledPin, LOW);
  delay(500);  // pause before repeating
}