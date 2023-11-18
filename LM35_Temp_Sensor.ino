#include <Arduino.h>
#include <elapsedMillis.h>

const int analogPin = A0;         // LM35 temperature sensor connected to A0
const int ledPin = 13;            // Onboard LED connected to pin 13
const int temperatureThreshold = 30;

int temperature = 0;
bool isBelowThreshold = false;

elapsedMillis ledBlinkTimer;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read temperature from LM35 sensor
  int sensorValue = analogRead(analogPin);
  temperature = (sensorValue * 500) / 1024; // Convert analog reading to temperature in Celsius

  // Check temperature conditions
  if (temperature < temperatureThreshold) {
    isBelowThreshold = true;
    controlLED(250); // Blink every 250 milliseconds
  } else {
    isBelowThreshold = false;
    controlLED(500); // Blink every 500 milliseconds
  }
}

void controlLED(int interval) {
  if (ledBlinkTimer >= interval) {
    ledBlinkTimer = 0; // Reset the timer

    // Toggle the LED state
    if (digitalRead(ledPin) == LOW) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  }
}
