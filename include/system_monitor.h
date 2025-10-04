#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include <Arduino.h>

class SystemMonitor {
private:
    unsigned long lastMemoryReport;
    uint32_t minFreeHeap;
    
    static const unsigned long MEMORY_REPORT_INTERVAL = 30000;

public:
    SystemMonitor();
    void begin();
    void checkSystem();
    void printSystemStatus();
    uint32_t getMinFreeHeap();
    void updateMinHeap();
};

extern SystemMonitor systemMonitor;

#endif