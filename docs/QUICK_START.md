# Guide de démarrage rapide

## ⚡ Configuration en 5 minutes

### 1. Préparer l'environnement

```bash
# Installer PlatformIO
pip install platformio

# Cloner le projet
git clone https://github.com/your-username/esp32-sensor-firmware.git
cd esp32-sensor-firmware
```

### 2. Configuration rapide

```bash
# Copier le fichier de configuration
cp include/config.example.h include/config.h
```

Éditer `include/config.h` avec vos vraies valeurs :

```cpp
#define WIFI_SSID "VotreWiFi"
#define WIFI_PASSWORD "VotreMotDePasse"
#define MQTT_SERVER "192.168.1.100"  // IP de votre broker MQTT
#define MQTT_USER "sensor_user"
#define MQTT_PASSWORD "sensor_password"
```

### 3. Flasher l'ESP32

```bash
# Compiler et flasher
pio run --target upload

# Monitoring série (optionnel)
pio device monitor
```

### 4. Récupérer l'adresse MAC

Dans le moniteur série, notez l'adresse MAC affichée :
```
Site identifié: Site Example 1 (ID: SITE_001)
Adresse MAC: AA:BB:CC:DD:EE:FF
```

### 5. Configurer le site (optionnel)

Modifiez `config.h` pour mapper votre MAC :

```cpp
#undef SITE_CONFIGS
const SiteConfig SITE_CONFIGS[] = {
    {"AA:BB:CC:DD:EE:FF", "SALON", "Salon principal"}
};
#undef NUM_SITES
#define NUM_SITES 1
```

## 📊 Vérification

### MQTT Topics à surveiller :
- `datayoti/sensor/AA:BB:CC:DD:EE:FF/data` → Données capteur
- `datayoti/sensor/AA:BB:CC:DD:EE:FF/heartbeat` → Status device

### Commandes de test MQTT :
```bash
# Écouter les données
mosquitto_sub -h 192.168.1.100 -u sensor_user -P sensor_password -t "datayoti/sensor/+/data"

# Écouter tous les topics
mosquitto_sub -h 192.168.1.100 -u sensor_user -P sensor_password -t "datayoti/sensor/+/+"
```

## 🔧 Dépannage express

### Problème WiFi
- Vérifiez SSID/password dans `config.h`
- Assurez-vous que l'ESP32 est à portée

### Problème MQTT  
- Vérifiez l'IP du broker
- Testez les identifiants MQTT
- Vérifiez que le port 1883 est ouvert

### Problème capteur
- Vérifiez le câblage sur pin 17
- DHT22 nécessite une résistance pull-up 10kΩ

### Logs utiles
```
=== STATUT SYSTÈME ===
WiFi RSSI: -45 dBm (Excellent)
MQTT État: Connecté (code: 0)  
NTP Synchronisé: Oui
=====================
```

## 🎯 Étapes suivantes

1. **Multi-capteurs** : Flashez d'autres ESP32 et ajoutez leurs MACs
2. **Dashboard** : Configurez Node-RED, Grafana ou Home Assistant  
3. **Base de données** : Stockez les données (InfluxDB, PostgreSQL)
4. **Alertes** : Configurez des notifications sur seuils

Voir [README.md](../README.md) pour la documentation complète.