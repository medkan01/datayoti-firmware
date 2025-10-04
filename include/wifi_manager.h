#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include "config.h"

class WiFiManager {
private:
    bool isConnected;
    unsigned long lastWifiSignalCheck;
    int consecutiveWeakSignal;
    static const unsigned long WIFI_SIGNAL_CHECK_INTERVAL = 60000;
    static const int MAX_WEAK_SIGNAL_COUNT = 3;

public:
    WiFiManager();
    void begin();
    bool connect();
    bool isWifiConnected();
    bool isSignalStable();
    void checkConnection();
    void printWifiStatus();
};

extern WiFiManager wifiManager;

#endif