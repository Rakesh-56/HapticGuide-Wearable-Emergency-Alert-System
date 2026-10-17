//Arduino Nano:
#include <RH_ASK.h>
#include <SPI.h>
#include <string.h>

// 433 MHz RF receiver DATA -> Nano D12
RH_ASK driver(2000, 12, 11, 10);

// IR obstacle sensors
const int LEFT_IR  = 2;
const int RIGHT_IR = 3;

// Vibration motor control pins
const int LEFT_MOTOR   = 5;
const int CENTER_MOTOR = 6;
const int RIGHT_MOTOR  = 9;

// Most IR modules output LOW when an obstacle is detected
const int OBSTACLE_ACTIVE = LOW;

// RF communication timeout
const unsigned long RF_TIMEOUT = 2000;

bool smokeDetected = false;
bool packetReceived = false;
unsigned long lastPacketTime = 0;

void stopMotors() {
  digitalWrite(LEFT_MOTOR, LOW);
  digitalWrite(CENTER_MOTOR, LOW);
  digitalWrite(RIGHT_MOTOR, LOW);
}

void setup() {
  Serial.begin(9600);

  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);

  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(CENTER_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);

  stopMotors();

  if (!driver.init()) {
    Serial.println("RF receiver initialization failed!");
    while (true) {
      stopMotors();
      delay(1000);
    }
  }

  Serial.println("Wireless guidance receiver ready.");
  Serial.println("Waiting for Uno smoke status...");
}

void loop() {
  // Receive the message from Arduino Uno
  uint8_t buffer[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t length = sizeof(buffer);

  if (driver.recv(buffer, &length)) {

    // Uno sends the word SMOKE
    if (length == 5 && memcmp(buffer, "SMOKE", 5) == 0) {
      smokeDetected = true;
      packetReceived = true;
      lastPacketTime = millis();

      Serial.println("Smoke status received: SMOKE DETECTED");
    }

    // Uno sends the word CLEAR
    else if (length == 5 && memcmp(buffer, "CLEAR", 5) == 0) {
      smokeDetected = false;
      packetReceived = true;
      lastPacketTime = millis();

      Serial.println("Smoke status received: CLEAR");
    }
  }

  // Stop if no valid message has been received recently
  if (!packetReceived ||
      millis() - lastPacketTime > RF_TIMEOUT) {
    smokeDetected = false;
    stopMotors();
    return;
  }

  // Run obstacle guidance only when smoke is detected
  if (!smokeDetected) {
    stopMotors();
    return;
  }

  // Read the IR sensor outputs
  bool leftObstacle =
      (digitalRead(LEFT_IR) == OBSTACLE_ACTIVE);

  bool rightObstacle =
      (digitalRead(RIGHT_IR) == OBSTACLE_ACTIVE);

  // Select vibration pattern
  if (leftObstacle && rightObstacle) {
    // Both sides blocked
    digitalWrite(LEFT_MOTOR, HIGH);
    digitalWrite(CENTER_MOTOR, HIGH);
    digitalWrite(RIGHT_MOTOR, HIGH);
  }
  else if (leftObstacle) {
    // Left obstacle
    digitalWrite(LEFT_MOTOR, HIGH);
    digitalWrite(CENTER_MOTOR, LOW);
    digitalWrite(RIGHT_MOTOR, LOW);
  }
  else if (rightObstacle) {
    // Right obstacle
    digitalWrite(LEFT_MOTOR, LOW);
    digitalWrite(CENTER_MOTOR, LOW);
    digitalWrite(RIGHT_MOTOR, HIGH);
  }
  else {
    // Neither sensor detects an obstacle
    digitalWrite(LEFT_MOTOR, LOW);
    digitalWrite(CENTER_MOTOR, HIGH);
    digitalWrite(RIGHT_MOTOR, LOW);
  }

  delay(50);
}
