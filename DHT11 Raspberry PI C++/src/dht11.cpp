#include "dht11.h"
#include <chrono>
#include <thread>

DHT11::DHT11(int pin) : dataPin(pin), temperature(0.0f), humidity(0.0f) {
    wiringPiSetup();
    pinMode(dataPin, OUTPUT);
    digitalWrite(dataPin, HIGH);
}

bool DHT11::waitForState(int state, int maxMicros) {
    int count = 0;
    while (digitalRead(dataPin) == state) {
        if (count++ > maxMicros)
            return false;
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
    return true;
}

bool DHT11::read() {
    uint8_t data[5] = {0, 0, 0, 0, 0};

    // Send request signal
    pinMode(dataPin, OUTPUT);
    digitalWrite(dataPin, LOW);
    delay(18);
    digitalWrite(dataPin, HIGH);
    delayMicroseconds(40);
    pinMode(dataPin, INPUT);

    // Wait for DHT11 to send its response
    if (!waitForState(LOW, 100) || !waitForState(HIGH, 100))
        return false;

    // Read data
    for (int i = 0; i < 40; i++) {
        if (!waitForState(LOW, 100) || !waitForState(HIGH, 100))
            return false;

        auto start = std::chrono::high_resolution_clock::now();
        while (digitalRead(dataPin) == HIGH) {
            if (!waitForState(LOW, 100))
                return false;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        int bitIndex = 7 - (i % 8);
        data[i / 8] |= (duration > 40 ? 1 : 0) << bitIndex;
    }

    // Check checksum
    if (data[4] != ((data[0] + data[1] + data[2] + data[3]) & 0xFF))
        return false;

    humidity = data[0] + data[1] * 0.1;
    temperature = data[2] + data[3] * 0.1;

    return true;
}

float DHT11::getTemperature() const {
    return temperature;
}

float DHT11::getHumidity() const {
    return humidity;
}
