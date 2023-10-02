#include "BME280.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <cerrno>
#include <cstdio>
#include <cmath>

BMP280::BMP280(uint8_t i2cAddress) : address(i2cAddress), t_fine(0)
{
    fd = open("/dev/i2c-1", O_RDWR);
    if (fd < 0)
    {
        perror("Failed to open the i2c bus");
    }
}

BMP280::~BMP280()
{
    if (fd >= 0)
        close(fd);
}

bool BMP280::initialize()
{
    if (ioctl(fd, I2C_SLAVE, address) < 0)
    {
        perror("Failed to acquire bus access and/or talk to slave");
        return false;
    }

    // Check if BMP280 is connected properly
    if (readU16(0xD0) != 0x76)
    {
        perror("BMP280 not found");
        return false;
    }

    return readCalibrationData();
}

float BMP280::readTemperature()
{
    int32_t adc_T = readS32(0xFA);
    int32_t compensated_T = compensateTemperature(adc_T);
    return compensated_T / 5120.0f;
}

uint16_t BMP280::readU16(uint8_t reg)
{
    uint8_t buffer[2];
    if (read(fd, buffer, 2) != 2)
    {
        perror("Failed to read from the i2c bus");
        return 0;
    }
    return (buffer[0] << 8) | buffer[1];
}

int32_t BMP280::readS32(uint8_t reg)
{
    uint8_t buffer[3];
    if (read(fd, buffer, 3) != 3)
    {
        perror("Failed to read from the i2c bus");
        return 0;
    }
    return (buffer[0] << 12) | (buffer[1] << 4) | (buffer[2] >> 4);
}

bool BMP280::readCalibrationData()
{
    // Read and store all calibration values.
    // Implementation depends on the sensor's datasheet.
    // Please refer to the BMP280 datasheet for the details.
    // Here, we are assuming that you will implement the required functionality
    // to read the calibration data from the sensor and use it to compensate
    // the temperature and pressure readings.
    return true;
}

int32_t BMP280::compensateTemperature(int32_t adc_T)
{
    // Use the calibration data to compensate the temperature value.
    // Implementation depends on the sensor's datasheet.
    // Please refer to the BMP280 datasheet for the details.
    // Here, we are assuming that you will implement the required functionality
    // to use the calibration data to compensate the temperature reading.
    return adc_T; // This is a placeholder. Replace with actual implementation.
}
