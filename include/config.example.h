#ifndef CONFIG_H
#define CONFIG_H

// FICHIER DE CONFIGURATION - TEMPLATE
// Copiez ce fichier vers "config.h" et modifiez avec vos vraies valeurs
// Le fichier config.h est ignoré par git pour protéger vos données sensibles

// Configuration WiFi - Remplacez par vos vraies valeurs
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Configuration MQTT - Remplacez par vos vraies valeurs
#define MQTT_SERVER "192.168.1.100"      // IP de votre broker MQTT
#define MQTT_PORT 1883
#define MQTT_USER "your_mqtt_user"       // Votre utilisateur MQTT
#define MQTT_PASSWORD "your_mqtt_password" // Votre mot de passe MQTT

// Topics normalisés: datayoti/{site_id}/{device_id}/{data_type}

// Configuration du capteur DHT
#define DHT_PIN 17          // Pin D17 comme demandé
#define DHT_TYPE DHT11      // Type de capteur (DHT11 ou DHT22)

// Configuration temporelle
#define MEASUREMENT_INTERVAL 1 * 60 * 1000  // Intervalle de mesure en millisecondes (1 minute)
#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET_SEC 0             // UTC (pas de décalage)
#define DAYLIGHT_OFFSET_SEC 0        // UTC (pas d'heure d'été)

// Identification des sites
struct SiteConfig {
    String macAddress;
    String siteId;
    String siteName;
};

// Configuration des sites - Remplacez par vos vraies adresses MAC et noms
// Pour obtenir l'adresse MAC de votre ESP32, flashez le firmware et regardez les logs série
const SiteConfig SITE_CONFIGS[] = {
    {"AA:BB:CC:DD:EE:F1", "SITE_001", "Salon"},           // Remplacez par votre vraie MAC
    {"AA:BB:CC:DD:EE:F2", "SITE_002", "Chambre"},         // Remplacez par votre vraie MAC
    {"AA:BB:CC:DD:EE:F3", "SITE_003", "Bureau"},          // Remplacez par votre vraie MAC
    {"AA:BB:CC:DD:EE:F4", "SITE_004", "Cave"}             // Remplacez par votre vraie MAC
};

#define NUM_SITES 4

#endif