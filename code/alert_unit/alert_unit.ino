// Arduino Uno:

#include <RH_ASK.h>
#include <SPI.h>
#include <string.h>

// 433 MHz transmitter DATA -> Uno D12
// MQ-2 analog output (AO) -> Uno A0

RH_ASK rfDriver(2000, 11, 12, 10);

const int smokeSensorPin = A0;
const int smokeThreshold = 120;

const unsigned long sendInterval = 300;
unsigned long lastSendTime = 0;

void setup() {
  Serial.begin(9600);

  if (!rfDriver.init()) {
    Serial.println("RF transmitter initialization failed!");

    while (true) {
      delay(1000);
    }
  }

  Serial.println("Uno: Smoke detection started");
  Serial.println("Allow MQ-2 sensor to warm up.");
}

void loop() {
  int smokeValue = analogRead(smokeSensorPin);

  Serial.print("MQ-2 value: ");
  Serial.print(smokeValue);

  if (millis() - lastSendTime >= sendInterval) {
    lastSendTime = millis();

    const char *message;

    if (smokeValue >= smokeThreshold) {
      message = "SMOKE";
    } else {
      message = "CLEAR";
    }

    rfDriver.send(
      (uint8_t *)message,
      strlen(message)
    );

    rfDriver.waitPacketSent();

    Serial.print(" | Transmitted: ");
    Serial.println(message);
  }

  delay(700);
}
