#include "BME280.h"
#include <iostream>

int main()
{
    BMP280 bmp;
    if (!bmp.initialize())
    {
        std::cerr << "Failed to initialize BMP280" << std::endl;
        return 1;
    }

    float temperature = bmp.readTemperature();
    std::cout << "Temperature: " << temperature << " °C" << std::endl;

    return 0;
}
