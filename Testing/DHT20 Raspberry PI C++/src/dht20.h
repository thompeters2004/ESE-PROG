#ifndef __DHT20_H__
#define __DHT20_H__

#include <stdint.h>
#include <wiringPiI2C.h>

class DHT20 {
public:
    DHT20(int i2cAddress = 0x76);  // Default I2C address for DHT20 is 0x76
    bool initialize();
    float readTemperature();
    float readHumidity();

private:
    int fd;
    int i2cAddress;

    bool readSensorData();
    float temperature;
    float humidity;
};

#endif
