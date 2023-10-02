// main.cpp
#include <iostream>
#include "HCSR04.h"

int main() {
    HCSR04 sensor(0, 1); // Assuming trigger is connected to WiringPi pin 0 and echo to WiringPi pin 1

    while (true) {
        float distance = sensor.getDistance();
        std::cout << "Distance: " << distance << " cm" << std::endl;
        delay(1000); // Delay 1 second between readings
    }

    return 0;
}