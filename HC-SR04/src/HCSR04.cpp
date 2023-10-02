// HCSR04.cpp
#include "HCSR04.h"

HCSR04::HCSR04(int triggerPin, int echoPin) : triggerPin(triggerPin), echoPin(echoPin) {
    wiringPiSetup();
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Ensure trigger pin is low
    digitalWrite(triggerPin, LOW);
    delay(30);
}

float HCSR04::getDistance() {
    // Send a 10us HIGH pulse to the trigger pin
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Wait for the echo pin to go HIGH
    while (digitalRead(echoPin) == LOW);

    // Measure the duration the echo pin stays HIGH
    auto start = std::chrono::high_resolution_clock::now();
    while (digitalRead(echoPin) == HIGH);
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the distance in cm
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    float distance = duration * 0.0344 / 2;

    return distance;
}