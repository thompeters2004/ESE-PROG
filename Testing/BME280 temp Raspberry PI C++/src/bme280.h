#ifndef BME280_H
#define BME280_H

#include <cstdint>
#include <unistd.h>

class BME280 {
public:
    BME280(int i2cAddress = 0x76);
    ~BME280();

    bool initialize();
    float readTemperature();

private:
    int fd;
    int i2cAddress;
    int32_t t_fine;

    // Compensation parameters
    uint16_t dig_T1;
    int16_t dig_T2, dig_T3;

    int32_t read24(uint8_t reg);
    uint16_t read16LE(uint8_t reg);
    int16_t readS16LE(uint8_t reg);
};

#endif
