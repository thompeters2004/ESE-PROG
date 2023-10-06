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
    float readHumidity();

private:
    int fd;
    int i2cAddress;
    int32_t t_fine;

    // Compensation parameters for temperature
    uint16_t dig_T1;
    int16_t dig_T2, dig_T3;

    // Compensation parameters for humidity
    uint8_t dig_H1, dig_H3;
    int16_t dig_H2;
    int8_t dig_H4, dig_H5, dig_H6;

    int32_t read24(uint8_t reg);
    uint16_t read16LE(uint8_t reg);
    int16_t readS16LE(uint8_t reg);
    uint8_t read8(uint8_t reg);
};

#endif
