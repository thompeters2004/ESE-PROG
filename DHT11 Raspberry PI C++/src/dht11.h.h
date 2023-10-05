#ifndef __DHT11_H__
#define __DHT11_H__

#include <wiringPi.h>
#include <stdint.h>

class DHT11 {
public:
    explicit DHT11(int pin);
    bool read();

    float getTemperature() const;
    float getHumidity() const;

private:
    int dataPin;
    float temperature;
    float humidity;

    bool waitForState(int state, int maxMicros);
};

#endif
