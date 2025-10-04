#include <Arduino.h>
#include "config.h"
#include "wifi_manager.h"
#include "mqtt_manager.h"
#include "time_manager.h"
#include "sensor_manager.h"
#include "system_monitor.h"
#include "device_manager.h"

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("=== Démarrage du système de capteurs ESP32 ===");
    
    // Initialisation des modules
    systemMonitor.begin();
    deviceManager.identifySite();
    sensorManager.begin();
    wifiManager.begin();
    
    // Connexion WiFi
    if (wifiManager.connect()) {
        // Configuration MQTT
        mqttManager.begin(deviceManager.getDeviceId());
        mqttManager.connect();
        
        // Initialisation du temps
        timeManager.begin();
        
        Serial.println("=== Système initialisé avec succès (Horodatage UTC) ===");
        Serial.printf("Prochaine mesure dans %d minutes\n", MEASUREMENT_INTERVAL / 60000);
        
        // Affichage initial de l'état système
        systemMonitor.printSystemStatus();
    } else {
        Serial.println("=== Erreur d'initialisation - Pas de connexion WiFi ===");
        systemMonitor.printSystemStatus();
    }
}

void loop() {
    // Vérification et maintenance des connexions
    wifiManager.checkConnection();
    
    if (wifiManager.isWifiConnected()) {
        timeManager.maintainSync();
        mqttManager.maintainConnection();
        mqttManager.loop();
    }
    
    // Monitoring système
    systemMonitor.checkSystem();
    
    // Lecture et envoi des données du capteur
    if (wifiManager.isWifiConnected() && mqttManager.isConnected() && 
        wifiManager.isSignalStable() && sensorManager.shouldTakeMeasurement()) {
        
        Serial.println("=== DÉBUT LECTURE CAPTEUR ===");
        
        SensorData data = sensorManager.readSensor();
        if (data.valid) {
            String timestamp = timeManager.getFormattedDateTime();
            
            // Création et envoi des données JSON
            String dataJson = sensorManager.createDataJson(
                deviceManager.getDeviceId(),
                timestamp,
                data
            );
            
            Serial.println("Données JSON: " + dataJson);
            
            String dataTopic = "datayoti/sensor/" + deviceManager.getDeviceId() + "/data";
            
            if (mqttManager.publish(dataTopic, dataJson)) {
                Serial.println("✅ Données envoyées avec succès via MQTT sur: " + dataTopic);
                
                // Envoi du heartbeat
                String heartbeatJson = sensorManager.createHeartbeatJson(
                    deviceManager.getDeviceId(),
                    deviceManager.getSiteId(),
                    timestamp,
                    timeManager.isSynchronized(),
                    systemMonitor.getMinFreeHeap()
                );
                
                String heartbeatTopic = "datayoti/sensor/" + deviceManager.getDeviceId() + "/heartbeat";
                mqttManager.publish(heartbeatTopic, heartbeatJson);
                
            } else {
                Serial.println("❌ Échec de l'envoi MQTT - Vérification de la connexion...");
                if (!mqttManager.isConnected()) {
                    Serial.println("Connexion MQTT perdue pendant l'envoi");
                }
            }
        }
        
        sensorManager.updateLastMeasurement();
        Serial.printf("Prochaine mesure dans %d minutes\n", MEASUREMENT_INTERVAL / 60000);
        Serial.println("=== FIN LECTURE CAPTEUR ===");
        
    } else if (wifiManager.isWifiConnected() && !wifiManager.isSignalStable() && 
               sensorManager.shouldTakeMeasurement()) {
        // Signal trop faible - reporter la mesure
        Serial.printf("📡 Mesure reportée - Signal WiFi trop faible (%d dBm)\n", WiFi.RSSI());
        // Réessayer dans 30 secondes au lieu d'attendre le cycle complet
        delay(30000);
    }
    
    // Petite pause pour éviter la surcharge du processeur
    delay(1000);
}

