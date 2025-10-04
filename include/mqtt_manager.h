#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <PubSubClient.h>
#include <WiFi.h>
#include "config.h"

class MQTTManager {
private:
    WiFiClient espClient;
    PubSubClient mqttClient;
    String deviceId;
    unsigned long lastMqttAttempt;
    unsigned long lastConnectionCheck;
    int mqttAttemptCount;
    
    static const unsigned long MQTT_RETRY_INTERVAL = 30000;
    static const int MAX_MQTT_ATTEMPTS = 3;
    static const unsigned long CONNECTION_CHECK_INTERVAL = 15000;

    String getMqttErrorMessage(int errorCode);

public:
    MQTTManager();
    void begin(const String& deviceID);
    bool connect();
    bool isConnected();
    bool publish(const String& topic, const String& payload, bool retained = false);
    void loop();
    void maintainConnection();
    void printMqttStatus();
};

extern MQTTManager mqttManager;

#endif