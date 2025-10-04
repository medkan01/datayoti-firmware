#include "device_manager.h"
#include <WiFi.h>

DeviceManager deviceManager;

DeviceManager::DeviceManager() {
    deviceId = "";
    currentSiteId = "";
    currentSiteName = "";
}

void DeviceManager::identifySite() {
    String macAddr = WiFi.macAddress();
    deviceId = macAddr;
    
    // Recherche du site correspondant à cette MAC
    for (int i = 0; i < NUM_SITES; i++) {
        if (SITE_CONFIGS[i].macAddress == "" || SITE_CONFIGS[i].macAddress == macAddr) {
            currentSiteId = SITE_CONFIGS[i].siteId;
            currentSiteName = SITE_CONFIGS[i].siteName;
            Serial.println("Site identifié: " + currentSiteName + " (ID: " + currentSiteId + ")");
            return;
        }
    }
    
    // Si aucun site configuré, utiliser un site par défaut
    currentSiteId = "SITE_UNKNOWN";
    currentSiteName = "Site Inconnu";
    Serial.println("Aucun site configuré pour cette MAC, utilisation du site par défaut");
}

String DeviceManager::getDeviceId() {
    return deviceId;
}

String DeviceManager::getSiteId() {
    return currentSiteId;
}

String DeviceManager::getSiteName() {
    return currentSiteName;
}