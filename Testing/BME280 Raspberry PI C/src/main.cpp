#include <bme280.h>

int main() {
    BME280 sensor;
    sensor.initialize();
    sensor.readData();
    return 0;
}
