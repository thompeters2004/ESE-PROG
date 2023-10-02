#include "BME280.h"
#include <iostream>

int main() {
    BME280 sensor(0x76); // Replace with your sensor's I2C address

    if (!sensor.initialize()) {
        std::cerr << "Failed to initialize BME280 sensor" << std::endl;
        return 1;
    }

    float temperature, humidity;
    if (sensor.readTemperature(temperature) && sensor.readHumidity(humidity)) {
        std::cout << "Temperature: " << temperature << " °C" << std::endl;
        std::cout << "Humidity: " << humidity << " %" << std::endl;
    } else {
        std::cerr << "Failed to read from BME280 sensor" << std::endl;
    }

    return 0;
}
