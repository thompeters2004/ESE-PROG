#include "bme280.h"
#include <iostream>

int main() {
    BME280 sensor;
    if (!sensor.initialize()) {
        std::cerr << "Failed to initialize BME280" << std::endl;
        return 1;
    }
    
    while(1)
    {

    float temperature = sensor.readTemperature();
    float humidity = sensor.readHumidity();
    std::cout << "Temperature: " << temperature << " °C" << std::endl;
    std::cout << "Humidity: " << humidity << " %" << std::endl;
}

    return 0;
}
