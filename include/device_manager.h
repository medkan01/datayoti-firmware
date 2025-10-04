#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <Arduino.h>
#include "config.h"

class DeviceManager {
private:
    String deviceId;
    String currentSiteId;
    String currentSiteName;

public:
    DeviceManager();
    void identifySite();
    String getDeviceId();
    String getSiteId();
    String getSiteName();
};

extern DeviceManager deviceManager;

#endif