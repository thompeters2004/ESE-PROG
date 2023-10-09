#include <iostream>
#include "dht20.h"

int main() {
    DHT20 sensor;

    if (!sensor.initialize()) {
        std::cout << "Failed to initialize DHT20 sensor!" << std::endl;
        return -1;
    }

    float temperature = sensor.readTemperature();
    float humidity = sensor.readHumidity();

    std::cout << "Temperature: " << temperature << "°C" << std::endl;
    std::cout << "Humidity: " << humidity << "%" << std::endl;

    return 0;
}
