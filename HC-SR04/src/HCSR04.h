// HCSR04.h
#ifndef HCSR04_H
#define HCSR04_H

#include <wiringPi.h>
#include <chrono>

class HCSR04 {
public:
    HCSR04(int triggerPin, int echoPin);
    float getDistance();

private:
    int triggerPin;
    int echoPin;
};

#endif // HCSR04_H