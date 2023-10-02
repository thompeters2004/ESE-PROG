#ifndef BME280_H
#define BME280_H

#include <cstdint>

class BMP280
{
public:
    BMP280(uint8_t i2cAddress = 0x76);
    ~BMP280();

    bool initialize();
    float readTemperature();

private:
    int fd;
    uint8_t address;
    int32_t t_fine;

    uint16_t readU16(uint8_t reg);
    int32_t readS32(uint8_t reg);
    bool readCalibrationData();
    int32_t compensateTemperature(int32_t adc_T);
};

#endif // BME280_H