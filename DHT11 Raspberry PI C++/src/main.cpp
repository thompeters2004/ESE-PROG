#include "dht11.h"
#include <iostream>

int main() {
    DHT11 sensor(0);  // Assuming you've connected the DHT11 to GPIO 0

    if (sensor.read()) {
        std::cout << "Temperature: " << sensor.getTemperature() << "°C" << std::endl;
        std::cout << "Humidity: " << sensor.getHumidity() << "%" << std::endl;
    } else {
        std::cout << "Failed to read from DHT11 sensor!" << std::endl;
    }

    return 0;
}
