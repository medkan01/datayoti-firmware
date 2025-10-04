#include "system_monitor.h"
#include "wifi_manager.h"
#include "mqtt_manager.h"
#include "time_manager.h"

SystemMonitor systemMonitor;

SystemMonitor::SystemMonitor() {
    lastMemoryReport = 0;
    minFreeHeap = UINT32_MAX;
}

void SystemMonitor::begin() {
    minFreeHeap = ESP.getFreeHeap();
}

void SystemMonitor::checkSystem() {
    unsigned long currentTime = millis();
    
    // Rapport système périodique
    if (currentTime - lastMemoryReport >= MEMORY_REPORT_INTERVAL) {
        lastMemoryReport = currentTime;
        printSystemStatus();
    }
    
    updateMinHeap();
}

void SystemMonitor::updateMinHeap() {
    uint32_t currentHeap = ESP.getFreeHeap();
    if (currentHeap < minFreeHeap) {
        minFreeHeap = currentHeap;
    }
}

uint32_t SystemMonitor::getMinFreeHeap() {
    return minFreeHeap;
}

void SystemMonitor::printSystemStatus() {
    uint32_t freeHeap = ESP.getFreeHeap();
    uint32_t heapSize = ESP.getHeapSize();
    uint32_t maxAllocHeap = ESP.getMaxAllocHeap();
    uint32_t usedHeap = heapSize - freeHeap;
    float heapFragmentation = 100.0 - (maxAllocHeap * 100.0 / freeHeap);
    
    Serial.println("=== STATUT SYSTÈME ===");
    Serial.printf("Uptime: %lu secondes (%.2f heures)\n", millis() / 1000, millis() / 3600000.0);
    Serial.printf("Heap libre: %u bytes (%.1f%% de %u bytes)\n", freeHeap, (freeHeap * 100.0 / heapSize), heapSize);
    Serial.printf("Heap utilisée: %u bytes\n", usedHeap);
    Serial.printf("Plus gros bloc libre: %u bytes\n", maxAllocHeap);
    Serial.printf("Fragmentation: %.1f%%\n", heapFragmentation);
    Serial.printf("Heap libre minimum observé: %u bytes\n", minFreeHeap);
    
    // État des modules
    wifiManager.printWifiStatus();
    mqttManager.printMqttStatus();
    timeManager.printTimeStatus();
    
    // Alertes
    if (heapFragmentation > 50) {
        Serial.println("⚠️  ALERTE: Fragmentation élevée de la heap!");
    }
    if (freeHeap < 20000) {
        Serial.println("⚠️  ALERTE: Mémoire libre faible!");
    }
    if (WiFi.RSSI() < -80) {
        Serial.println("⚠️  ALERTE: Signal WiFi très faible!");
    }
    if (!timeManager.isSynchronized()) {
        Serial.println("⚠️  ALERTE: NTP non synchronisé - Horodatage peut être incorrect!");
    }
    
    Serial.println("=====================");
}