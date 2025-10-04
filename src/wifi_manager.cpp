#include "wifi_manager.h"

WiFiManager wifiManager;

WiFiManager::WiFiManager() {
    isConnected = false;
    lastWifiSignalCheck = 0;
    consecutiveWeakSignal = 0;
}

void WiFiManager::begin() {
    WiFi.mode(WIFI_STA);
}

bool WiFiManager::connect() {
    Serial.println("Connexion au WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30) {
        delay(1000);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println();
        Serial.println("WiFi connecté!");
        Serial.print("Adresse IP: ");
        Serial.println(WiFi.localIP());
        Serial.print("Adresse MAC: ");
        Serial.println(WiFi.macAddress());
        isConnected = true;
        return true;
    } else {
        Serial.println();
        Serial.println("Échec de la connexion WiFi");
        isConnected = false;
        return false;
    }
}

bool WiFiManager::isWifiConnected() {
    return WiFi.status() == WL_CONNECTED && isConnected;
}

bool WiFiManager::isSignalStable() {
    int rssi = WiFi.RSSI();
    
    // Signal trop faible pour MQTT stable
    if (rssi < -85) {
        consecutiveWeakSignal++;
        if (consecutiveWeakSignal >= MAX_WEAK_SIGNAL_COUNT) {
            Serial.printf("🚨 Signal WiFi critique (%d dBm) - Arrêt temporaire des tentatives MQTT\n", rssi);
            return false;
        }
    } else if (rssi > -75) {
        // Signal redevenu acceptable, reset du compteur
        if (consecutiveWeakSignal > 0) {
            Serial.printf("✅ Signal WiFi amélioré (%d dBm) - Reprise des tentatives MQTT\n", rssi);
            consecutiveWeakSignal = 0;
        }
    }
    
    return rssi > -85; // Seuil minimum pour tentatives MQTT
}

void WiFiManager::checkConnection() {
    unsigned long currentTime = millis();
    
    // Vérification périodique du signal WiFi
    if (currentTime - lastWifiSignalCheck >= WIFI_SIGNAL_CHECK_INTERVAL) {
        lastWifiSignalCheck = currentTime;
        isSignalStable(); // Met à jour le compteur de signal faible
    }
    
    // Reconnexion si nécessaire
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Connexion WiFi perdue, tentative de reconnexion...");
        connect();
    }
}

void WiFiManager::printWifiStatus() {
    Serial.printf("WiFi RSSI: %d dBm (", WiFi.RSSI());
    if (WiFi.RSSI() > -50) Serial.print("Excellent");
    else if (WiFi.RSSI() > -60) Serial.print("Bon");
    else if (WiFi.RSSI() > -70) Serial.print("Moyen");
    else Serial.print("Faible");
    Serial.println(")");
}