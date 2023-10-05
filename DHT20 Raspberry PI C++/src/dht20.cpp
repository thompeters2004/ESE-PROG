#include "dht20.h"

DHT20::DHT20(int i2cAddress) : i2cAddress(i2cAddress), fd(-1), temperature(0.0), humidity(0.0) {}

bool DHT20::initialize() {
    fd = wiringPiI2CSetup(i2cAddress);
    return fd != -1;
}

bool DHT20::readSensorData() {
    // Assuming DHT20 provides two bytes for humidity and two bytes for temperature
    int humData = wiringPiI2CReadReg16(fd, 0x00);  // Read humidity register
    int tempData = wiringPiI2CReadReg16(fd, 0x02); // Read temperature register

    if (humData == -1 || tempData == -1) {
        return false;
    }

    // Convert raw data to actual values based on DHT20 datasheet
    humidity = static_cast<float>(humData) / 10.0;
    temperature = static_cast<float>(tempData) / 10.0;

    return true;
}

float DHT20::readTemperature() {
    if (readSensorData()) {
        return temperature;
    }
    return -1000.0;  // Return a clearly invalid temperature if reading fails
}

float DHT20::readHumidity() {
    if (readSensorData()) {
        return humidity;
    }
    return -1.0;  // Return a clearly invalid humidity if reading fails
}
