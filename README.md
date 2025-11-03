# 📡 DataYoti ESP32 Firmware

> **Du signal à l'action** - Firmware IoT pour capteurs environnementaux

![ESP32](https://img.shields.io/badge/ESP32-IoT-blue)
![MQTT](https://img.shields.io/badge/MQTT-Communication-green)
![DHT](https://img.shields.io/badge/DHT11%2F22-Sensor-orange)
![License](https://img.shields.io/badge/License-MIT-yellow)

**DataYoti ESP32 Firmware** est le composant de collecte du projet DataYoti. Il transforme des microcontrôleurs ESP32 équipés de capteurs DHT11/DHT22 en dispositifs IoT intelligents pour le monitoring environnemental (température et humidité).


## 🎯 Place dans l'écosystème DataYoti

```
┌─────────────────────────────────────────┐
│  1️⃣  Capteurs ESP32 (DHT22)            │  ← VOUS ÊTES ICI
│      ↓ MQTT                             │
│  2️⃣  Infrastructure temps réel          │  → datayoti-realtime (Raspberry Pi)
│      ↓ Ingestion & monitoring           │
│  3️⃣  Data Warehouse + Analytics        │  → datayoti-warehouse
│      ↓ Dashboards & Conformité          │
│  4️⃣  Insights actionnables              │
└─────────────────────────────────────────┘
```

Ce firmware assure la **première brique** : capturer les signaux environnementaux et les transmettre de manière fiable.

---

## � Fonctionnalités clés

## 🌟 Fonctionnalités clés

- 🌡️ **Capteurs DHT11/DHT22** : Mesure température et humidité
- 📡 **Communication MQTT** : Transmission fiable avec reconnexion automatique
- ⏰ **Synchronisation NTP** : Timestamps UTC précis (RFC3339)
- 📶 **WiFi intelligent** : Monitoring signal et gestion de la connectivité
- 🏠 **Multi-sites** : Identification automatique par adresse MAC
- 🔍 **Monitoring système** : Surveillance mémoire, uptime, alertes
- ✅ **Validation des données** : Contrôle des plages de valeurs

---

## 🚀 Démarrage rapide

### Prérequis

- **ESP32** (DevKit, DevKitC ou compatible)
- **Capteur DHT11 ou DHT22**
- **PlatformIO** ou Arduino IDE
- **Infrastructure temps réel** (voir [datayoti-realtime](../datayoti-realtime)) déployée sur Raspberry Pi

### Installation

```bash
# 1. Cloner le projet
git clone https://github.com/medkan01/datayoti-firmware.git
cd datayoti-firmware

# 2. Copier et configurer
cp include/config.example.h include/config.h
# Éditer include/config.h avec vos paramètres

# 3. Compiler et uploader
pio run --target upload

# 4. Monitorer les logs
pio device monitor
```

### Configuration minimale

Éditez `include/config.h` :

```cpp
// WiFi
#define WIFI_SSID "votre_wifi"
#define WIFI_PASSWORD "votre_mot_de_passe"

// MQTT Broker (adresse IP du Raspberry Pi)
#define MQTT_SERVER "192.168.1.100"  // IP de votre Raspberry Pi
#define MQTT_USER "datayoti_monitor"
#define MQTT_PASSWORD "votre_mot_de_passe_mqtt"

// Capteur
#define DHT_PIN 17        // GPIO 17
#define DHT_TYPE DHT22    // DHT11 ou DHT22

// Sites (obtenir MAC avec les logs série au démarrage)
const SiteConfig SITE_CONFIGS[] = {
    {"AA:BB:CC:DD:EE:FF", "SITE_001", "Salon"}
};
```

### Schéma de connexion

```
ESP32 Pin 17 ──── DHT Data
ESP32 3.3V   ──── DHT VCC  
ESP32 GND    ──── DHT GND
```

**Note** : Une résistance pull-up 10kΩ entre VCC et DATA peut être nécessaire (souvent intégrée au module).

---

## 📊 Format des données

### Topic : `datayoti/sensor/{device_id}/data`

Publié à chaque mesure (intervalle configurable, défaut : 1 min) :

```json
{
  "device_id": "AA:BB:CC:DD:EE:FF",
  "timestamp": "2025-11-03T14:30:25.000Z",
  "temperature": 22.5,
  "humidity": 65.0
}
```

### Topic : `datayoti/sensor/{device_id}/heartbeat`

Publié avec chaque mesure pour monitoring :

```json
{
  "device_id": "AA:BB:CC:DD:EE:FF",
  "site_id": "SITE_001",
  "timestamp": "2025-11-03T14:30:25.000Z",
  "rssi": -45,
  "free_heap": 234567,
  "uptime": 3600,
  "ntp_sync": true
}
```

### Topic : `datayoti/sensor/{device_id}/status` (LWT)

- `online` : Device connecté
- `offline` : Device déconnecté (Last Will Testament)

---

## 🏗️ Architecture modulaire

Le firmware est organisé en modules indépendants :

| Module | Rôle |
|--------|------|
| **DeviceManager** | Identification du device et mapping MAC → Site |
| **WiFiManager** | Connexion WiFi et monitoring signal |
| **MQTTManager** | Communication MQTT avec retry logic |
| **TimeManager** | Synchronisation NTP et timestamps UTC |
| **SensorManager** | Lecture capteurs DHT et création JSON |
| **SystemMonitor** | Monitoring système et alertes |

**Avantages** : Maintenabilité, testabilité, évolutivité

---

## 🛠️ Développement

### Commandes PlatformIO

```bash
# Compiler
pio run

# Uploader vers ESP32
pio run --target upload

# Monitorer le port série
pio device monitor --baud 115200

# Nettoyer le build
pio run --target clean
```

### Logs de démarrage

```
=== Démarrage du système de capteurs ESP32 ===
WiFi connecté
Adresse IP: 192.168.1.xxx
MAC Address: AA:BB:CC:DD:EE:FF
Site identifié: SITE_001 (Salon)
MQTT connecté
NTP synchronisé: 2025-11-03T14:30:25.000Z
=== Système initialisé avec succès ===
```

### Alertes système

- ⚠️ **Mémoire faible** : Heap < 50 KB
- ⚠️ **Signal WiFi critique** : RSSI < -85 dBm
- ⚠️ **NTP non synchronisé** : Pas de sync depuis > 1 heure

---

## 🐛 Dépannage

### ESP32 ne se connecte pas au WiFi

- Vérifiez le SSID et mot de passe
- Le WiFi doit être en **2.4 GHz** (ESP32 ne supporte pas 5 GHz)
- Vérifiez la portée du signal

### MQTT ne se connecte pas

- Vérifiez l'IP du Raspberry Pi et le port (1883)
- Testez avec : `mosquitto_sub -h <IP_RASPBERRY_PI> -t datayoti/# -v`
- Vérifiez les credentials MQTT dans l'infrastructure temps réel

### Erreurs de lecture DHT

- Vérifiez les connexions physiques
- Vérifiez le bon type de capteur (DHT11 vs DHT22)
- Attendez 2 secondes après le démarrage

---

## 📚 Ressources

- 📖 [Documentation détaillée](https://github.com/medkan01/datayoti-firmware)
- 🔗 [Infrastructure temps réel](../datayoti-realtime) - Prochaine étape de l'écosystème
- 🔗 [Data Warehouse](../datayoti-warehouse) - Plateforme d'analyse

---

## 📄 Licence

Ce projet est sous licence MIT. Voir [LICENSE](LICENSE) pour plus de détails.

---

## �‍💻 Contact

- **LinkedIn** : [Mehdi Akniou](https://linkedin.com/in/mehdi-akniou)
- **Email** : contact@mehdi-akniou.com
- **GitHub** : [@medkan01](https://github.com/medkan01)

---

**DataYoti ESP32 Firmware** - Du signal à l'action 📡
