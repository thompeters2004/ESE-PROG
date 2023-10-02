#include <iostream>
#include "HCSR04.h"

int main() {
    try {
        HCSR04 sensor(17, 27); // Assuming trigger is connected to GPIO 17 and echo to GPIO 27

        while (true) {
            float distance = sensor.getDistance();
            std::cout << "Distance: " << distance << " cm" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    return 0;
}
