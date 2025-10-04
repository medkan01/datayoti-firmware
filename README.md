# ESP32 IoT Sensor Firmware

![ESP32](https://img.shields.io/badge/ESP32-IoT-blue)
![MQTT](https://img.shields.io/badge/MQTT-Communication-green)
![DHT](https://img.shields.io/badge/DHT11%2F22-Sensor-orange)
![License](https://img.shields.io/badge/License-MIT-yellow)

Firmware modulaire pour capteurs IoT ESP32 avec communication MQTT, synchronisation NTP et monitoring système avancé.

## 🌟 Fonctionnalités

- 📡 **Communication MQTT** robuste avec reconnexion automatique
- 🌡️ **Capteurs DHT11/DHT22** pour température et humidité
- ⏰ **Synchronisation NTP** avec timestamps UTC RFC3339
- 📶 **Gestion WiFi intelligente** avec monitoring de signal
- 🔍 **Monitoring système** complet (mémoire, uptime, alertes)
- 🏠 **Multi-sites** avec identification automatique par MAC
- 🔄 **Architecture modulaire** pour faciliter la maintenance

## 🚀 Installation rapide

### 1. Cloner le projet
```bash
git clone https://github.com/your-username/esp32-sensor-firmware.git
cd esp32-sensor-firmware
```

### 2. Configuration
```bash
# Copier le fichier de configuration d'exemple
cp include/config.example.h include/config.h

# Éditer avec vos vraies valeurs
nano include/config.h
```

### 3. Compilation et upload
```bash
# Avec PlatformIO CLI
pio run --target upload

# Ou utiliser PlatformIO IDE dans VSCode
```

## ⚙️ Configuration

### Fichiers de configuration

- **`include/config.example.h`** : Template de configuration (versionnée)
- **`include/config.h`** : Vos vraies valeurs (ignoré par git)

### Variables importantes

```cpp
// WiFi
#define WIFI_SSID "your_wifi_name"
#define WIFI_PASSWORD "your_wifi_password"

// MQTT Broker
#define MQTT_SERVER "192.168.1.100"
#define MQTT_USER "your_mqtt_user"
#define MQTT_PASSWORD "your_mqtt_password"

// Sites (mapping MAC → Site)
const SiteConfig SITE_CONFIGS[] = {
    {"AA:BB:CC:DD:EE:FF", "SITE_001", "Salon"},
    {"AA:BB:CC:DD:EE:00", "SITE_002", "Chambre"}
};
```

## 📊 Données envoyées

### Topic principal : `datayoti/sensor/{device_id}/data`
```json
{
  "device_id": "AA:BB:CC:DD:EE:FF",
  "timestamp": "2025-10-04T14:30:25.000Z",
  "temperature": 22.5,
  "humidity": 65.0
}
```

### Topic heartbeat : `datayoti/sensor/{device_id}/heartbeat`
```json
{
  "device_id": "AA:BB:CC:DD:EE:FF",
  "site_id": "SITE_001",
  "timestamp": "2025-10-04T14:30:25.000Z",
  "rssi": -45,
  "free_heap": 123456,
  "uptime": 3600,
  "ntp_sync": true
}
```

## 🏗️ Architecture

Le firmware utilise une **architecture modulaire** pour faciliter la maintenance :

```
📁 include/          → Headers des modules
📁 src/              → Implémentations  
├── wifi_manager     → Gestion WiFi
├── mqtt_manager     → Communication MQTT
├── time_manager     → Synchronisation NTP
├── sensor_manager   → Lecture capteurs
├── system_monitor   → Monitoring système
└── device_manager   → Identification sites
```

Voir [README_ARCHITECTURE.md](README_ARCHITECTURE.md) pour plus de détails.

## 🔌 Matériel requis

- **ESP32** (DevKit ou compatible)
- **Capteur DHT11 ou DHT22**
- **Résistance pull-up 10kΩ** (souvent intégrée)

### Connexions
```
ESP32 Pin 17 ──── DHT Data
ESP32 3.3V   ──── DHT VCC  
ESP32 GND    ──── DHT GND
```

## 📡 Infrastructure MQTT

Le firmware est conçu pour fonctionner avec un broker MQTT standard. Topics recommandés :

- `datayoti/sensor/+/data` → Données des capteurs
- `datayoti/sensor/+/heartbeat` → Status des devices  
- `datayoti/sensor/+/status` → Online/Offline (LWT)

## 🔧 Développement

### Prérequis
- [PlatformIO](https://platformio.org/) (recommandé)
- Ou Arduino IDE avec les bibliothèques ESP32

### Bibliothèques utilisées
- `ArduinoJson` : Sérialisation JSON
- `PubSubClient` : Client MQTT
- `DHT sensor library` : Lecture capteurs DHT
- `NTPClient` : Synchronisation temps

### Structure de développement
```bash
# Tests
pio test

# Build pour différents environnements  
pio run -e esp32dev
pio run -e esp32-s3

# Monitoring série
pio device monitor
```

## 🐛 Debugging

### Logs série
Le firmware produit des logs détaillés via série (115200 baud) :

```
=== STATUT SYSTÈME ===
Uptime: 3600 secondes (1.00 heures)
Heap libre: 234567 bytes (87.2% de 268984 bytes)
WiFi RSSI: -45 dBm (Excellent)
MQTT État: Connecté (code: 0)
NTP Synchronisé: Oui (dernière sync: 30 sec ago)
=====================
```

### Alertes automatiques
- ⚠️ Mémoire faible
- ⚠️ Signal WiFi critique  
- ⚠️ NTP non synchronisé
- ⚠️ Fragmentation heap élevée

## 🤝 Contribution

Les contributions sont bienvenues ! 

1. Fork le projet
2. Créer une branche (`git checkout -b feature/amazing-feature`)
3. Commit (`git commit -m 'Add amazing feature'`)
4. Push (`git push origin feature/amazing-feature`)
5. Ouvrir une Pull Request

## 📄 License

Ce projet est sous licence MIT. Voir [LICENSE](LICENSE) pour plus de détails.

## 🆘 Support

- 📖 [Documentation complète](README_ARCHITECTURE.md)
- 🐛 [Issues GitHub](https://github.com/your-username/esp32-sensor-firmware/issues)
- 💬 [Discussions](https://github.com/your-username/esp32-sensor-firmware/discussions)

## 🏷️ Changelog

### v1.0.0 (2025-10-04)
- ✅ Architecture modulaire complète
- ✅ Support DHT11/DHT22
- ✅ Communication MQTT robuste
- ✅ Synchronisation NTP UTC
- ✅ Monitoring système avancé
- ✅ Gestion multi-sites

---

**Fait avec ❤️ pour l'IoT**