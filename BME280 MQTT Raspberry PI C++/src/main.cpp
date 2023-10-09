#include "bme280.h"

int main() {
    BME280 sensor;

    if (!sensor.initialize()) {
        std::cerr << "Failed to initialize BME280" << std::endl;
        return 1;
    }

    // Mosquitto initialization
    mosquitto_lib_init();
    struct mosquitto *mosq = mosquitto_new("hello", true, NULL);
    if (!mosq) {
        std::cerr << "Failed to create Mosquitto instance" << std::endl;
        return 1;
    }

    const char *mqtt_host = "192.168.178.25"; // Change this to your MQTT broker IP/hostname
    int mqtt_port = 1883; // Default MQTT port, change if needed
    const char *mqtt_username = "thompeters2004";
    const char *mqtt_password = "Daatje1.Spetter2";

    mosquitto_username_pw_set(mosq, mqtt_username, mqtt_password);

    if (mosquitto_connect(mosq, mqtt_host, mqtt_port, 60) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to connect to MQTT broker" << std::endl;
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
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

        mosquitto_publish(mosq, NULL, "hello", strlen(temp_payload), temp_payload, 0, false);
        mosquitto_publish(mosq, NULL, "hello", strlen(hum_payload), hum_payload, 0, false);

        delay(1000);
    }

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}
