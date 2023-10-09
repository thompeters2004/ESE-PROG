#include "HC-SR04.h"
#include <Arduino.h>

// Define the pins for the HC-SR04 sensor
const int trigPin = 9;  // Example pin number for the trigger
const int echoPin = 10; // Example pin number for the echo

// Create an instance of the HC_SR04_sensor class
HC_SR04_sensor hcSR04(trigPin, echoPin);

void setup() {
  Serial.begin(9600);  // Start serial communication for debugging
}

void loop() {
  int distance = hcSR04.readDistance();  // Read the distance using the HC-05 sensor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(1000);  // Wait for a second before taking the next reading
}
