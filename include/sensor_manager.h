#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <DHT.h>
#include <ArduinoJson.h>
#include "config.h"

struct SensorData {
    float temperature;
    float humidity;
    bool valid;
};

class SensorManager {
private:
    DHT dht;
    unsigned long lastMeasurement;

public:
    SensorManager();
    void begin();
    SensorData readSensor();
    bool shouldTakeMeasurement();
    void updateLastMeasurement();
    String createDataJson(const String& deviceId, const String& timestamp, const SensorData& data);
    String createHeartbeatJson(const String& deviceId, const String& siteId, const String& timestamp, bool ntpSync, uint32_t minHeap);
};

extern SensorManager sensorManager;

#endif