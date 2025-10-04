#include "time_manager.h"
#include "wifi_manager.h"

TimeManager timeManager;

TimeManager::TimeManager() : timeClient(ntpUDP, NTP_SERVER, GMT_OFFSET_SEC, 60000) {
    lastNtpUpdate = 0;
    ntpSynchronized = false;
}

void TimeManager::begin() {
    timeClient.begin();
    Serial.println("Initialisation NTP...");
    maintainSync(); // Première synchronisation
    
    // Configuration du fuseau horaire sur UTC (0 offset) - backup pour l'horloge système
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
}

void TimeManager::maintainSync() {
    unsigned long currentTime = millis();
    
    // Vérifier si une mise à jour est nécessaire
    if (currentTime - lastNtpUpdate >= NTP_UPDATE_INTERVAL || lastNtpUpdate == 0) {
        lastNtpUpdate = currentTime;
        
        if (wifiManager.isWifiConnected() && wifiManager.isSignalStable()) {
            Serial.println("Synchronisation NTP...");
            
            if (timeClient.update()) {
                ntpSynchronized = true;
                Serial.printf("✅ NTP synchronisé - Heure: %s\n", getFormattedDateTime().c_str());
                
                // Optionnel: Synchroniser aussi configTime pour la cohérence
                time_t epochTime = timeClient.getEpochTime();
                struct timeval tv = { epochTime, 0 };
                settimeofday(&tv, NULL);
                
            } else {
                Serial.println("❌ Échec de synchronisation NTP");
                if (ntpSynchronized) {
                    Serial.println("⚠️  Utilisation de l'horloge locale (peut dériver)");
                }
            }
        } else {
            Serial.println("Signal WiFi insuffisant pour synchronisation NTP");
        }
    }
}

String TimeManager::getFormattedDateTime() {
    char buffer[32];
    
    if (ntpSynchronized && timeClient.isTimeSet()) {
        // Utiliser NTP en priorité si disponible et synchronisé
        time_t epochTime = timeClient.getEpochTime();
        struct tm * timeinfo = gmtime(&epochTime);
        strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S.000Z", timeinfo);
    } else {
        // Fallback sur l'horloge système
        time_t rawtime;
        time(&rawtime);
        struct tm * timeinfo = gmtime(&rawtime);
        strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S.000Z", timeinfo);
    }
    
    return String(buffer);
}

bool TimeManager::isSynchronized() {
    return ntpSynchronized;
}

void TimeManager::printTimeStatus() {
    Serial.printf("NTP Synchronisé: %s", ntpSynchronized ? "Oui" : "Non");
    if (ntpSynchronized) {
        unsigned long timeSinceSync = (millis() - lastNtpUpdate) / 1000;
        Serial.printf(" (dernière sync: %lu sec ago)", timeSinceSync);
    }
    Serial.println();
}