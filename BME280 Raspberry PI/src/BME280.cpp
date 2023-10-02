#include "BME280.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <cerrno>
#include <cstdio>

BME280::BME280(uint8_t i2cAddress) : _i2cAddress(i2cAddress), _fd(-1) {}

BME280::~BME280() {
    if (_fd != -1) close(_fd);
}

bool BME280::initialize() {
    const char *device = "/dev/i2c-1"; // I2C bus 1
    _fd = open(device, O_RDWR);
    if (_fd < 0) {
        perror("Failed to open the i2c bus");
        return false;
    }

    if (ioctl(_fd, I2C_SLAVE, _i2cAddress) < 0) {
        perror("Failed to acquire bus access and/or talk to slave");
        return false;
    }

    // Initialization code specific to BME280
    // ...

    return true;
}

bool BME280::readTemperature(float &temperature) {
    // Implement temperature reading
    // ...

    return true;
}

bool BME280::readHumidity(float &humidity) {
    // Implement humidity reading
    // ...

    return true;
}

bool BME280::read8(uint8_t reg, uint8_t &value) {
    if (write(_fd, &reg, 1) != 1) {
        perror("Failed to write to the i2c bus");
        return false;
    }

    if (read(_fd, &value, 1) != 1) {
        perror("Failed to read from the i2c bus");
        return false;
    }

    return true;
}

bool BME280::read16(uint8_t reg, uint16_t &value) {
    uint8_t buffer[2];
    if (write(_fd, &reg, 1) != 1) {
        perror("Failed to write to the i2c bus");
        return false;
    }

    if (read(_fd, buffer, 2) != 2) {
        perror("Failed to read from the i2c bus");
        return false;
    }

    value = (buffer[0] << 8) | buffer[1];
    return true;
}

bool BME280::write8(uint8_t reg, uint8_t value) {
    uint8_t buffer[2] = {reg, value};
    if (write(_fd, buffer, 2) != 2) {
        perror("Failed to write to the i2c bus");
        return false;
    }

    return true;
}
