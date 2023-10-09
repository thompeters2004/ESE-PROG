#include "HC-SR04.h"
#include <Arduino.h>

HC_SR04_sensor::HC_SR04_sensor(int trig, int echo) {
    trigPin = trig;
    echoPin = echo;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

int HC_SR04_sensor::readDistance() {
    // Set trigpin HIGH for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    soundDuration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    soundDistance = soundDuration * 0.034 / 2; // Speed of sound wave divided by 2

    return soundDistance;
}
