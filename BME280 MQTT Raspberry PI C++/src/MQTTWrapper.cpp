#include "MQTTWrapper.h"

MQTTWrapper::MQTTWrapper(const char* id, const char* host, int port, const char* username, const char* password)
    : host(host), port(port), username(username), password(password) {
    mosquitto_lib_init();
    mosq = mosquitto_new(id, true, NULL);
    if (!mosq) {
        std::cerr << "Failed to create Mosquitto instance" << std::endl;
        exit(1);
    }
    mosquitto_username_pw_set(mosq, username, password);
}

MQTTWrapper::~MQTTWrapper() {
    disconnect();
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}

bool MQTTWrapper::connect() {
    if (mosquitto_connect(mosq, host, port, 60) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to connect to MQTT broker" << std::endl;
        return false;
    }
    return true;
}

void MQTTWrapper::publish(const char* topic, const char* payload) {
    mosquitto_publish(mosq, NULL, topic, strlen(payload), payload, 0, false);
}

void MQTTWrapper::disconnect() {
    mosquitto_disconnect(mosq);
}
