#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>
#include "config.h"

class TimeManager {
private:
    WiFiUDP ntpUDP;
    NTPClient timeClient;
    unsigned long lastNtpUpdate;
    bool ntpSynchronized;
    
    static const unsigned long NTP_UPDATE_INTERVAL = 300000; // 5 minutes

public:
    TimeManager();
    void begin();
    void maintainSync();
    String getFormattedDateTime();
    bool isSynchronized();
    void printTimeStatus();
};

extern TimeManager timeManager;

#endif