#include "bme280.h"
#include <wiringPiI2C.h>
#include <iostream>

BME280::BME280(int i2cAddress) : i2cAddress(i2cAddress), t_fine(0) {
}

BME280::~BME280() {
    close(fd);
}

bool BME280::initialize() {
    fd = wiringPiI2CSetup(i2cAddress);
    if (fd == -1) {
        return false;
    }

    // Read temperature compensation values
    dig_T1 = read16LE(0x88);
    dig_T2 = readS16LE(0x8A);
    dig_T3 = readS16LE(0x8C);

    return true;
}

float BME280::readTemperature() {
    int32_t adc_T = read24(0xFA);
    adc_T >>= 4;

    int64_t var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    int64_t var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;

    t_fine = var1 + var2;
    float T = (t_fine * 5 + 128) >> 8;
    return T / 100.0f;
}

int32_t BME280::read24(uint8_t reg) {
    int32_t value;
    value = wiringPiI2CReadReg8(fd, reg);
    value = value << 8 | wiringPiI2CReadReg8(fd, reg + 1);
    value = value << 8 | wiringPiI2CReadReg8(fd, reg + 2);
    return value;
}

uint16_t BME280::read16LE(uint8_t reg) {
    uint16_t value = wiringPiI2CReadReg8(fd, reg) | (wiringPiI2CReadReg8(fd, reg + 1) << 8);
    return value;
}

int16_t BME280::readS16LE(uint8_t reg) {
    return (int16_t)read16LE(reg);
}
