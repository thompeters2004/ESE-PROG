#ifndef BME280_H
#define BME280_H

#include <cstdint>

class BME280 {
public:
    BME280(uint8_t i2cAddress);
    ~BME280();

    bool initialize();
    bool readTemperature(float &temperature);
    bool readHumidity(float &humidity);

private:
    uint8_t _i2cAddress;
    int _fd; // File descriptor for I2C bus

    bool read8(uint8_t reg, uint8_t &value);
    bool read16(uint8_t reg, uint16_t &value);
    bool write8(uint8_t reg, uint8_t value);
};

#endif // BME280_H
