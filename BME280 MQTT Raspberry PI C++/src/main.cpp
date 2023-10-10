#include "bme280.h"
#include "MQTTWrapper.h"

int main() {
    BME280 sensor;

    if (!sensor.initialize()) {
        std::cerr << "Failed to initialize BME280" << std::endl;
        return 1;
    }

    MQTTWrapper mqtt("test", "192.168.178.25", 1883, "thompeters2004", "thompeters2004");
    if (!mqtt.connect()) {
        return 1;
    }

    while (1) {
        float temperature = sensor.readTemperature();
        float humidity = sensor.readHumidity();
        std::cout << "Temperature: " << temperature << " °C" << std::endl;
        std::cout << "Humidity: " << humidity << " %" << std::endl;

        char temp_payload[50];
        char hum_payload[50];
        snprintf(temp_payload, sizeof(temp_payload), "Temperature: %.2f °C", temperature);
        snprintf(hum_payload, sizeof(hum_payload), "Humidity: %.2f %%", humidity);

        mqtt.publish("test", temp_payload);
        mqtt.publish("test", hum_payload);

        delay(1000);
    }

    return 0;
}
