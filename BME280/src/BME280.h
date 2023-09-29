#ifndef BME280_H
#define BME280_H

#include <Arduino.h>
#include <Wire.h>

class BME280
{
public:
    explicit BME280(uint8_t address = 0x76);
    bool initialize();
    float readTemperature();
    float readPressure();
    float readHumidity();

private:
    uint8_t _address;
    int32_t _tFine;
    struct CalibrationData {
        uint16_t T1;
        int16_t T2, T3;
        uint16_t P1;
        int16_t P2, P3, P4, P5, P6, P7, P8, P9;
        uint8_t H1, H3;
        int16_t H2, H4, H5;
        int8_t H6;
    } _calibration;
    bool readCalibrationData();
    int32_t readRegister(int regAddress, int length);
};

#endif
