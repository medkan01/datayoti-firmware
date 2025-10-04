#include "sensor_manager.h"
#include "time_manager.h"
#include <WiFi.h>

SensorManager sensorManager;

SensorManager::SensorManager() : dht(DHT_PIN, DHT_TYPE) {
    lastMeasurement = 0;
}

void SensorManager::begin() {
    dht.begin();
    Serial.println("Capteur DHT initialisé");
}

SensorData SensorManager::readSensor() {
    SensorData data;
    
    // Lecture du capteur DHT
    data.temperature = dht.readTemperature();
    data.humidity = dht.readHumidity();
    
    // Vérification des erreurs de lecture
    if (isnan(data.humidity) || isnan(data.temperature)) {
        Serial.println("Erreur de lecture du capteur DHT!");
        data.valid = false;
    } else {
        Serial.printf("Température: %.2f°C, Humidité: %.2f%%\n", data.temperature, data.humidity);
        data.valid = true;
    }
    
    return data;
}

bool SensorManager::shouldTakeMeasurement() {
    unsigned long currentTime = millis();
    return (currentTime - lastMeasurement >= MEASUREMENT_INTERVAL || lastMeasurement == 0);
}

void SensorManager::updateLastMeasurement() {
    lastMeasurement = millis();
}

String SensorManager::createDataJson(const String& deviceId, const String& timestamp, const SensorData& data) {
    StaticJsonDocument<200> doc;  // Taille réduite car moins de champs
    doc["device_id"] = deviceId;
    doc["timestamp"] = timestamp;
    doc["temperature"] = data.temperature;
    doc["humidity"] = data.humidity;
    
    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

String SensorManager::createHeartbeatJson(const String& deviceId, const String& siteId, 
                                         const String& timestamp, bool ntpSync, uint32_t minHeap) {
    StaticJsonDocument<200> doc;  // Taille réduite
    doc["device_id"] = deviceId;
    doc["site_id"] = siteId;
    doc["timestamp"] = timestamp;
    doc["rssi"] = WiFi.RSSI();
    doc["free_heap"] = ESP.getFreeHeap();
    doc["uptime"] = millis() / 1000;
    doc["min_heap"] = minHeap;
    doc["ntp_sync"] = ntpSync;
    
    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}