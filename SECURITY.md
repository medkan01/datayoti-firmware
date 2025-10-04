# Security Guidelines / Guide de sécurité

## 🔒 Configuration sécurisée pour la production

### 1. Gestion des mots de passe

#### ❌ À éviter
```cpp
// Ne JAMAIS commiter des vraies données dans le code
#define WIFI_PASSWORD "monvraimotdepasse123"
#define MQTT_PASSWORD "mqtt_secret_password"
```

#### ✅ Recommandé
```cpp
// Utiliser config_local.h (ignoré par git)
#include "config_local.h"
```

### 2. MQTT sécurisé

#### Configuration de base (développement)
```cpp
#define MQTT_SERVER "192.168.1.100"
#define MQTT_PORT 1883  // Non-chiffré
```

#### Configuration sécurisée (production)
```cpp
#define MQTT_SERVER "mqtt.example.com"
#define MQTT_PORT 8883  // TLS/SSL
#define MQTT_USE_TLS true
#define MQTT_CA_CERT "-----BEGIN CERTIFICATE-----\n..."
```

### 3. Authentification MQTT

#### Permissions minimales
```bash
# Créer un utilisateur dédié aux capteurs
mosquitto_passwd -c /etc/mosquitto/passwd sensor_readonly

# ACL restrictives (/etc/mosquitto/acl)
user sensor_readonly
topic write datayoti/sensor/+/data
topic write datayoti/sensor/+/heartbeat  
topic write datayoti/sensor/+/status
```

### 4. Chiffrement des communications

#### WiFi
- Utiliser WPA3 ou au minimum WPA2
- Éviter WEP ou réseaux ouverts
- Utiliser des mots de passe forts (>12 caractères)

#### MQTT over TLS
```cpp
// Configuration TLS pour production
WiFiClientSecure espClientSecure;
PubSubClient mqttClient(espClientSecure);

void setupTLS() {
    espClientSecure.setCACert(ca_cert);
    espClientSecure.setCertificate(client_cert);
    espClientSecure.setPrivateKey(client_key);
}
```

### 5. Validation des entrées

```cpp
// Valider les données capteurs avant envoi
bool isValidTemperature(float temp) {
    return (temp > -40.0 && temp < 80.0);  // Plage réaliste DHT22
}

bool isValidHumidity(float hum) {
    return (hum >= 0.0 && hum <= 100.0);
}
```

### 6. Gestion des erreurs sécurisée

#### ❌ Éviter les informations sensibles dans les logs
```cpp
Serial.printf("MQTT failed: user=%s, pass=%s", user, pass);  // NON!
```

#### ✅ Logs sécurisés
```cpp
Serial.println("MQTT authentication failed");  // OK
Serial.printf("MQTT error code: %d", errorCode);  // OK
```

### 7. Mise à jour sécurisée (OTA)

```cpp
// OTA avec authentification
void setupOTA() {
    ArduinoOTA.setPassword("strong_ota_password");
    ArduinoOTA.setPasswordHash("md5_hash_of_password");
    
    ArduinoOTA.onStart([]() {
        Serial.println("OTA Update starting...");
    });
    
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("OTA Error[%u]: ", error);
    });
}
```

### 8. Protection contre les attaques

#### Rate limiting
```cpp
// Limiter la fréquence des tentatives MQTT
const unsigned long MIN_RETRY_INTERVAL = 30000;  // 30 secondes min
```

#### Watchdog
```cpp
// Redémarrage automatique en cas de blocage
#include "esp_task_wdt.h"

void setup() {
    esp_task_wdt_init(30, true);  // 30 secondes timeout
    esp_task_wdt_add(NULL);
}

void loop() {
    esp_task_wdt_reset();  // Reset watchdog
    // ... rest of loop
}
```

### 9. Checklist de sécurité

#### Avant déploiement
- [ ] Mots de passe forts et uniques
- [ ] config_local.h créé et .gitignore configuré
- [ ] MQTT avec authentification activée
- [ ] Permissions MQTT minimales
- [ ] WiFi WPA2/WPA3 configuré
- [ ] Logs ne contiennent pas d'infos sensibles
- [ ] OTA sécurisé si activé
- [ ] Validation des données capteurs

#### Monitoring sécurité
- [ ] Surveiller les connexions MQTT suspectes
- [ ] Alertes sur échecs d'authentification répétés
- [ ] Monitoring de l'activité réseau anormale
- [ ] Logs d'accès MQTT centralisés

### 10. Environnements multiples

#### Structure recommandée
```
config_local.h          # Production (secret)
config_local.dev.h      # Développement (secret)  
config_local.test.h     # Test (secret)
config.example.h        # Template public
```

#### Variables d'environnement
```cpp
#ifdef PRODUCTION
    #include "config_local.prod.h"
#elif defined(DEVELOPMENT)  
    #include "config_local.dev.h"
#else
    #include "config_local.h"
#endif
```

## 🚨 Incidents de sécurité

Si vous pensez avoir découvert une vulnérabilité :

1. **NE PAS** créer d'issue publique
2. Envoyer un email à : security@yourproject.com
3. Inclure : description, impact, étapes de reproduction
4. Délai de divulgation : 90 jours après correction

## 📚 Ressources complémentaires

- [OWASP IoT Security Guidelines](https://owasp.org/www-project-iot-security-guidance/)
- [ESP32 Security Best Practices](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/security/security.html)
- [MQTT Security Fundamentals](https://www.hivemq.com/blog/mqtt-security-fundamentals/)