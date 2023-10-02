#include "HCSR04.h"
#include <pigpio.h>
#include <chrono>
#include <thread>

HCSR04::HCSR04(int triggerPin, int echoPin) : triggerPin(triggerPin), echoPin(echoPin) {
    if (gpioInitialise() < 0) {
        // Initialization failed
        throw "GPIO Initialization failed";
    }

    gpioSetMode(triggerPin, PI_OUTPUT);
    gpioSetMode(echoPin, PI_INPUT);
    gpioWrite(triggerPin, PI_LOW);
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
}

HCSR04::~HCSR04() {
    gpioTerminate();
}

float HCSR04::getDistance() {
    gpioWrite(triggerPin, PI_HIGH);
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    gpioWrite(triggerPin, PI_LOW);

    uint32_t start, end;
    while (gpioRead(echoPin) == 0)
        start = gpioTick();

    while (gpioRead(echoPin) == 1)
        end = gpioTick();

    uint32_t diff = end - start;
    return diff / 58.0;
}
