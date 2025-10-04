#include "mqtt_manager.h"
#include "wifi_manager.h"
#include "time_manager.h"

MQTTManager mqttManager;

MQTTManager::MQTTManager() : mqttClient(espClient) {
    lastMqttAttempt = 0;
    lastConnectionCheck = 0;
    mqttAttemptCount = 0;
}

void MQTTManager::begin(const String& deviceID) {
    deviceId = deviceID;
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setKeepAlive(90);
    mqttClient.setSocketTimeout(45);
}

String MQTTManager::getMqttErrorMessage(int errorCode) {
    switch (errorCode) {
        case -4: return "MQTT_CONNECTION_TIMEOUT - Timeout de connexion";
        case -3: return "MQTT_CONNECTION_LOST - Connexion perdue";
        case -2: return "MQTT_CONNECT_FAILED - Échec de connexion réseau";
        case -1: return "MQTT_DISCONNECTED - Client déconnecté";
        case 0:  return "MQTT_CONNECTED - Connecté avec succès";
        case 1:  return "MQTT_CONNECT_BAD_PROTOCOL - Version de protocole incorrecte";
        case 2:  return "MQTT_CONNECT_BAD_CLIENT_ID - ID client rejeté";
        case 3:  return "MQTT_CONNECT_UNAVAILABLE - Serveur indisponible";
        case 4:  return "MQTT_CONNECT_BAD_CREDENTIALS - Identifiants incorrects";
        case 5:  return "MQTT_CONNECT_UNAUTHORIZED - Non autorisé";
        default: return "Code d'erreur inconnu: " + String(errorCode);
    }
}

bool MQTTManager::connect() {
    // Vérifier d'abord la qualité du signal
    if (!wifiManager.isSignalStable()) {
        Serial.printf("❌ Signal WiFi trop faible (%d dBm) - Connexion MQTT reportée\n", WiFi.RSSI());
        return false;
    }
    
    // Limite le nombre de tentatives consécutives
    if (mqttAttemptCount >= MAX_MQTT_ATTEMPTS) {
        unsigned long currentTime = millis();
        unsigned long retryInterval = MQTT_RETRY_INTERVAL;
        
        // Doubler l'intervalle si le signal est faible
        if (WiFi.RSSI() < -75) {
            retryInterval *= 2;
            Serial.println("Signal faible - Intervalle de reconnexion doublé");
        }
        
        if (currentTime - lastMqttAttempt < retryInterval) {
            return false; // Attendre avant de réessayer
        }
        mqttAttemptCount = 0; // Reset du compteur après l'intervalle
    }
    
    if (!mqttClient.connected()) {
        Serial.printf("Tentative de connexion MQTT (Signal: %d dBm)...\n", WiFi.RSSI());
        mqttAttemptCount++;
        lastMqttAttempt = millis();
        
        String clientId = "ESP32Client-" + deviceId + "-" + String(millis() % 10000);
        
        // Connexion avec Last Will Testament pour détecter les déconnexions
        String lwt_topic = "datayoti/sensor/" + deviceId + "/status";
        String lwt_message = "{\"device_id\":\"" + deviceId + "\",\"timestamp\":\"" + timeManager.getFormattedDateTime() + "\"}";
        
        if (mqttClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD, 
                              lwt_topic.c_str(), 1, true, lwt_message.c_str())) {
            Serial.println("✅ MQTT connecté avec succès");
            
            // Publier le statut "online" immédiatement
            String online_message = "{\"device_id\":\"" + deviceId + "\",\"timestamp\":\"" + timeManager.getFormattedDateTime() + "\"}";
            mqttClient.publish(lwt_topic.c_str(), online_message.c_str(), true);
            
            mqttAttemptCount = 0;
            return true;
        } else {
            int errorCode = mqttClient.state();
            Serial.print("❌ Échec de connexion MQTT: ");
            Serial.println(getMqttErrorMessage(errorCode));
            Serial.printf("(Tentative %d/%d, Signal: %d dBm)\n", mqttAttemptCount, MAX_MQTT_ATTEMPTS, WiFi.RSSI());
            return false;
        }
    }
    return true; // Déjà connecté
}

bool MQTTManager::isConnected() {
    return mqttClient.connected();
}

bool MQTTManager::publish(const String& topic, const String& payload, bool retained) {
    if (!mqttClient.connected()) {
        return false;
    }
    return mqttClient.publish(topic.c_str(), payload.c_str(), retained);
}

void MQTTManager::loop() {
    if (mqttClient.connected()) {
        mqttClient.loop();
    }
}

void MQTTManager::maintainConnection() {
    unsigned long currentTime = millis();
    
    // Vérification périodique de l'état de la connexion
    if (currentTime - lastConnectionCheck >= CONNECTION_CHECK_INTERVAL) {
        lastConnectionCheck = currentTime;
        
        if (mqttClient.connected()) {
            // Connexion MQTT active - le heartbeat dans readAndSendSensorData() maintient la connexion
        } else {
            // Ne pas spammer les tentatives si le signal est mauvais
            if (wifiManager.isSignalStable()) {
                Serial.println("Connexion MQTT perdue détectée - Signal suffisant pour reconnexion");
                connect();
            } else {
                // Attendre que le signal s'améliore
                if (currentTime - lastMqttAttempt > 60000) { // Log toutes les minutes seulement
                    Serial.printf("En attente d'amélioration du signal WiFi (%d dBm) pour reconnecter MQTT\n", WiFi.RSSI());
                    lastMqttAttempt = currentTime;
                }
            }
        }
    }
}

void MQTTManager::printMqttStatus() {
    Serial.printf("MQTT État: %s (code: %d)\n", 
                  mqttClient.connected() ? "Connecté" : "Déconnecté", 
                  mqttClient.state());
}