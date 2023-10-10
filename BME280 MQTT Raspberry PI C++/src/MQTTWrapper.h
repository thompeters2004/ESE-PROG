#ifndef MQTTWRAPPER_H
#define MQTTWRAPPER_H

#include <mosquitto.h>
#include <iostream>
#include <cstring>

class MQTTWrapper {
public:
    MQTTWrapper(const char* id, const char* host, int port, const char* username, const char* password);
    ~MQTTWrapper();

    bool connect();
    void publish(const char* topic, const char* payload);
    void disconnect();

private:
    struct mosquitto *mosq;
    const char* host;
    int port;
    const char* username;
    const char* password;
};

#endif
