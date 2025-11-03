# DataYoti ESP32 Firmware# ESP32 IoT Sensor Firmware



![ESP32](https://img.shields.io/badge/ESP32-IoT-blue)![ESP32](https://img.shields.io/badge/ESP32-IoT-blue)

![MQTT](https://img.shields.io/badge/MQTT-Communication-green)![MQTT](https://img.shields.io/badge/MQTT-Communication-green)

![DHT](https://img.shields.io/badge/DHT11%2F22-Sensor-orange)![DHT](https://img.shields.io/badge/DHT11%2F22-Sensor-orange)

![License](https://img.shields.io/badge/License-MIT-yellow)![License](https://img.shields.io/badge/License-MIT-yellow)



Firmware modulaire pour capteurs IoT ESP32 avec communication MQTT, synchronisation NTP et monitoring système avancé. Ce projet fait partie de l'écosystème **DataYoti**, une solution complète de collecte et d'analyse de données environnementales.Firmware modulaire pour capteurs IoT ESP32 avec communication MQTT, synchronisation NTP et monitoring système avancé.



## 📋 Table des matières## 🌟 Fonctionnalités



- [Vue d'ensemble](#-vue-densemble)- 📡 **Communication MQTT** robuste avec reconnexion automatique

- [Fonctionnalités](#-fonctionnalités)- 🌡️ **Capteurs DHT11/DHT22** pour température et humidité

- [Architecture](#-architecture)- ⏰ **Synchronisation NTP** avec timestamps UTC RFC3339

- [Prérequis matériel](#-prérequis-matériel)- 📶 **Gestion WiFi intelligente** avec monitoring de signal

- [Installation](#-installation)- 🔍 **Monitoring système** complet (mémoire, uptime, alertes)

- [Configuration](#-configuration)- 🏠 **Multi-sites** avec identification automatique par MAC

- [Utilisation](#-utilisation)- 🔄 **Architecture modulaire** pour faciliter la maintenance

- [Format des données](#-format-des-données)

- [Développement](#-développement)## 🚀 Installation rapide

- [Dépannage](#-dépannage)

- [Contribution](#-contribution)### 1. Cloner le projet

- [Licence](#-licence)```bash

git clone https://github.com/your-username/esp32-sensor-firmware.git

## 🎯 Vue d'ensemblecd esp32-sensor-firmware

```

**DataYoti ESP32 Firmware** est un firmware embarqué pour microcontrôleurs ESP32 conçu pour collecter des données de capteurs environnementaux (température, humidité) et les transmettre via MQTT à un serveur central. Le projet met l'accent sur la **fiabilité**, la **modularité** et la **facilité de maintenance**.

### 2. Configuration

### Cas d'usage```bash

# Copier le fichier de configuration d'exemple

- 🏠 **Domotique** : Monitoring de température et humidité dans différentes piècescp include/config.example.h include/config.h

- 🌡️ **Agriculture** : Surveillance des conditions environnementales en serre

- 🏭 **Industrie** : Monitoring des conditions de stockage et de production# Éditer avec vos vraies valeurs

- 🔬 **Laboratoire** : Collecte de données précises pour analyses scientifiquesnano include/config.h

```

## ✨ Fonctionnalités

### 3. Compilation et upload

### Core Features```bash

# Avec PlatformIO CLI

- 📡 **Communication MQTT robuste** avec reconnexion automatique et gestion intelligente des erreurspio run --target upload

- 🌡️ **Support DHT11/DHT22** pour mesures précises de température et humidité

- ⏰ **Synchronisation NTP** automatique avec timestamps UTC RFC3339# Ou utiliser PlatformIO IDE dans VSCode

- 📶 **Gestion WiFi intelligente** avec monitoring de la qualité du signal et reconnexion automatique```

- 🔍 **Monitoring système complet** (mémoire, uptime, alertes automatiques)

- 🏠 **Multi-sites** avec identification automatique des devices par adresse MAC## ⚙️ Configuration

- 🔄 **Architecture modulaire** pour faciliter la maintenance et l'évolution

### Fichiers de configuration

### Fonctionnalités avancées

- **`include/config.example.h`** : Template de configuration (versionnée)

- ✅ **Validation des données** avant envoi (plages de valeurs réalistes)- **`include/config.h`** : Vos vraies valeurs (ignoré par git)

- 🎯 **Heartbeat automatique** pour monitoring de l'état des capteurs

- 📊 **Métriques système** (heap, RSSI, uptime, synchronisation NTP)### Variables importantes

- ⚡ **Gestion intelligente de la bande passante** (mesures conditionnelles selon qualité signal)

- 🛡️ **Last Will Testament** MQTT pour détection de déconnexions```cpp

- 📝 **Logs détaillés** pour debugging et monitoring// WiFi

#define WIFI_SSID "your_wifi_name"

## 🏗️ Architecture#define WIFI_PASSWORD "your_wifi_password"



Le firmware suit une **architecture modulaire** avec séparation claire des responsabilités :// MQTT Broker

#define MQTT_SERVER "192.168.1.100"

```#define MQTT_USER "your_mqtt_user"

┌─────────────────────────────────────────────────────────────┐#define MQTT_PASSWORD "your_mqtt_password"

│                         main.cpp                            │

│                    (Orchestration)                          │// Sites (mapping MAC → Site)

└─────────────────────────────────────────────────────────────┘const SiteConfig SITE_CONFIGS[] = {

           │         │         │         │         │    {"AA:BB:CC:DD:EE:FF", "SITE_001", "Salon"},

           ▼         ▼         ▼         ▼         ▼    {"AA:BB:CC:DD:EE:00", "SITE_002", "Chambre"}

    ┌──────────┐ ┌──────────┐ ┌──────────┐ ┌──────────┐};

    │  Device  │ │   WiFi   │ │   MQTT   │ │  Sensor  │```

    │ Manager  │ │ Manager  │ │ Manager  │ │ Manager  │

    └──────────┘ └──────────┘ └──────────┘ └──────────┘## 📊 Données envoyées

                      │             │

                      ▼             ▼### Topic principal : `datayoti/sensor/{device_id}/data`

                 ┌──────────┐ ┌──────────┐```json

                 │   Time   │ │  System  │{

                 │ Manager  │ │ Monitor  │  "device_id": "AA:BB:CC:DD:EE:FF",

                 └──────────┘ └──────────┘  "timestamp": "2025-10-04T14:30:25.000Z",

```  "temperature": 22.5,

  "humidity": 65.0

### Modules principaux}

```

| Module | Responsabilité | Fichiers |

|--------|---------------|----------|### Topic heartbeat : `datayoti/sensor/{device_id}/heartbeat`

| **DeviceManager** | Identification du device et mapping MAC → Site | `device_manager.h/cpp` |```json

| **WiFiManager** | Connexion WiFi, monitoring signal, stabilité | `wifi_manager.h/cpp` |{

| **MQTTManager** | Communication MQTT, retry logic, LWT | `mqtt_manager.h/cpp` |  "device_id": "AA:BB:CC:DD:EE:FF",

| **TimeManager** | Synchronisation NTP, timestamps UTC RFC3339 | `time_manager.h/cpp` |  "site_id": "SITE_001",

| **SensorManager** | Lecture capteurs DHT, création JSON, scheduling | `sensor_manager.h/cpp` |  "timestamp": "2025-10-04T14:30:25.000Z",

| **SystemMonitor** | Monitoring heap, alertes, rapports système | `system_monitor.h/cpp` |  "rssi": -45,

  "free_heap": 123456,

### Avantages de cette architecture  "uptime": 3600,

  "ntp_sync": true

- ✅ **Maintenabilité** : Code organisé par responsabilité}

- ✅ **Testabilité** : Modules indépendants et isolés```

- ✅ **Réutilisabilité** : Managers réutilisables dans d'autres projets

- ✅ **Évolutivité** : Ajout facile de nouvelles fonctionnalités## 🏗️ Architecture

- ✅ **Debugging facilité** : Isolation des problèmes par module

Le firmware utilise une **architecture modulaire** pour faciliter la maintenance :

## 🔌 Prérequis matériel

```

### Composants nécessaires📁 include/          → Headers des modules

📁 src/              → Implémentations  

| Composant | Description | Quantité |├── wifi_manager     → Gestion WiFi

|-----------|-------------|----------|├── mqtt_manager     → Communication MQTT

| **ESP32** | Microcontrôleur (DevKit, DevKitC, etc.) | 1 |├── time_manager     → Synchronisation NTP

| **DHT11 ou DHT22** | Capteur température/humidité | 1 |├── sensor_manager   → Lecture capteurs

| **Résistance 10kΩ** | Pull-up pour DHT (optionnelle si intégrée) | 1 |├── system_monitor   → Monitoring système

| **Câbles** | Jumper wires pour connexions | 3-4 |└── device_manager   → Identification sites

| **Breadboard** | Pour prototypage (optionnel) | 1 |```



### Schéma de connexionVoir [README_ARCHITECTURE.md](README_ARCHITECTURE.md) pour plus de détails.



```## 🔌 Matériel requis

ESP32                    DHT11/DHT22

┌────────┐              ┌──────────┐- **ESP32** (DevKit ou compatible)

│        │              │          │- **Capteur DHT11 ou DHT22**

│  3.3V  ├──────────────┤ VCC      │- **Résistance pull-up 10kΩ** (souvent intégrée)

│        │              │          │

│  GND   ├──────────────┤ GND      │### Connexions

│        │              │          │```

│  D17   ├──────────────┤ DATA     │ESP32 Pin 17 ──── DHT Data

│        │              │          │ESP32 3.3V   ──── DHT VCC  

└────────┘              └──────────┘ESP32 GND    ──── DHT GND

     │                       │```

     │      Résistance       │

     └────────10kΩ──────────┘## 📡 Infrastructure MQTT

        (entre VCC et DATA)

```Le firmware est conçu pour fonctionner avec un broker MQTT standard. Topics recommandés :



### Spécifications techniques- `datayoti/sensor/+/data` → Données des capteurs

- `datayoti/sensor/+/heartbeat` → Status des devices  

- **Alimentation** : 5V via USB ou 3.3V régulé- `datayoti/sensor/+/status` → Online/Offline (LWT)

- **Consommation** : ~80-240mA en fonctionnement (variable selon WiFi)

- **Température de fonctionnement** : -40°C à +85°C (ESP32)## 🔧 Développement

- **Plage de mesure DHT22** : -40°C à +80°C, 0-100% humidité

- **Plage de mesure DHT11** : 0°C à +50°C, 20-90% humidité### Prérequis

- [PlatformIO](https://platformio.org/) (recommandé)

## 🚀 Installation- Ou Arduino IDE avec les bibliothèques ESP32



### 1. Prérequis logiciels### Bibliothèques utilisées

- `ArduinoJson` : Sérialisation JSON

Installez [PlatformIO](https://platformio.org/) :- `PubSubClient` : Client MQTT

- **VS Code** : Installez l'extension PlatformIO IDE- `DHT sensor library` : Lecture capteurs DHT

- **CLI** : `pip install platformio`- `NTPClient` : Synchronisation temps



Ou utilisez **Arduino IDE** avec les bibliothèques ESP32.### Structure de développement

```bash

### 2. Cloner le projet# Tests

pio test

```bash

git clone https://github.com/medkan01/datayoti-esp32-firmware.git# Build pour différents environnements  

cd datayoti-esp32-firmwarepio run -e esp32dev

```pio run -e esp32-s3



### 3. Configuration initiale# Monitoring série

pio device monitor

```bash```

# Copier le fichier de configuration d'exemple

cp include/config.example.h include/config.h## 🐛 Debugging



# Éditer avec vos vraies valeurs### Logs série

# Windows : notepad include/config.hLe firmware produit des logs détaillés via série (115200 baud) :

# Linux/Mac : nano include/config.h

``````

=== STATUT SYSTÈME ===

### 4. Compilation et uploadUptime: 3600 secondes (1.00 heures)

Heap libre: 234567 bytes (87.2% de 268984 bytes)

#### Avec PlatformIO CLIWiFi RSSI: -45 dBm (Excellent)

```bashMQTT État: Connecté (code: 0)

# CompilationNTP Synchronisé: Oui (dernière sync: 30 sec ago)

pio run=====================

```

# Upload vers l'ESP32

pio run --target upload### Alertes automatiques

- ⚠️ Mémoire faible

# Monitoring série- ⚠️ Signal WiFi critique  

pio device monitor- ⚠️ NTP non synchronisé

```- ⚠️ Fragmentation heap élevée



#### Avec PlatformIO IDE (VS Code)## 🤝 Contribution

1. Ouvrir le dossier du projet dans VS Code

2. Cliquer sur l'icône PlatformIO dans la barre latéraleLes contributions sont bienvenues ! 

3. Cliquer sur "Build" puis "Upload"

4. Ouvrir le "Serial Monitor" pour voir les logs1. Fork le projet

2. Créer une branche (`git checkout -b feature/amazing-feature`)

#### Avec Arduino IDE3. Commit (`git commit -m 'Add amazing feature'`)

1. Installer le support ESP32 : Fichier → Préférences → URL de gestionnaire de cartes supplémentaires4. Push (`git push origin feature/amazing-feature`)

2. Ajouter : `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`5. Ouvrir une Pull Request

3. Installer les bibliothèques (voir [Dépendances](#dépendances))

4. Ouvrir `src/main.cpp`## 📄 License

5. Sélectionner la carte ESP32 Dev Module

6. Compiler et téléverserCe projet est sous licence MIT. Voir [LICENSE](LICENSE) pour plus de détails.



### 5. Vérification## 🆘 Support



Après l'upload, ouvrez le moniteur série (115200 baud) et vous devriez voir :- 📖 [Documentation complète](README_ARCHITECTURE.md)

- 🐛 [Issues GitHub](https://github.com/your-username/esp32-sensor-firmware/issues)

```- 💬 [Discussions](https://github.com/your-username/esp32-sensor-firmware/discussions)

=== Démarrage du système de capteurs ESP32 ===

WiFi connecté## 🏷️ Changelog

Adresse IP: 192.168.1.xxx

MAC Address: AA:BB:CC:DD:EE:FF### v1.0.0 (2025-10-04)

Site identifié: SITE_001 (Salon)- ✅ Architecture modulaire complète

MQTT connecté- ✅ Support DHT11/DHT22

NTP synchronisé: 2025-11-03T14:30:25.000Z- ✅ Communication MQTT robuste

=== Système initialisé avec succès (Horodatage UTC) ===- ✅ Synchronisation NTP UTC

```- ✅ Monitoring système avancé

- ✅ Gestion multi-sites

## ⚙️ Configuration

---

### Fichiers de configuration

**Fait avec ❤️ pour l'IoT**
- **`include/config.example.h`** : Template de configuration (versionné sur Git)
- **`include/config.h`** : Vos vraies valeurs (ignoré par Git, à créer localement)

### Paramètres WiFi

```cpp
#define WIFI_SSID "votre_nom_wifi"
#define WIFI_PASSWORD "votre_mot_de_passe_wifi"
```

### Paramètres MQTT

```cpp
#define MQTT_SERVER "192.168.1.100"        // IP ou hostname du broker MQTT
#define MQTT_PORT 1883                     // Port MQTT (1883 standard, 8883 TLS)
#define MQTT_USER "votre_utilisateur_mqtt"
#define MQTT_PASSWORD "votre_mot_de_passe_mqtt"
```

### Configuration du capteur

```cpp
#define DHT_PIN 17              // Pin GPIO connectée au DHT
#define DHT_TYPE DHT11          // DHT11 ou DHT22
```

### Configuration temporelle

```cpp
#define MEASUREMENT_INTERVAL 1 * 60 * 1000  // Intervalle en ms (1 min par défaut)
#define NTP_SERVER "pool.ntp.org"           // Serveur NTP
#define GMT_OFFSET_SEC 0                    // UTC (0 = pas de décalage)
#define DAYLIGHT_OFFSET_SEC 0               // UTC (0 = pas d'heure d'été)
```

### Configuration multi-sites

Le firmware identifie automatiquement le site à partir de l'adresse MAC de l'ESP32 :

```cpp
const SiteConfig SITE_CONFIGS[] = {
    {"AA:BB:CC:DD:EE:F1", "SITE_001", "Salon"},
    {"AA:BB:CC:DD:EE:F2", "SITE_002", "Chambre"},
    {"AA:BB:CC:DD:EE:F3", "SITE_003", "Bureau"},
    {"AA:BB:CC:DD:EE:F4", "SITE_004", "Cave"}
};

#define NUM_SITES 4
```

**Comment obtenir l'adresse MAC de votre ESP32 ?**

Flashez le firmware et regardez les logs série au démarrage :
```
MAC Address: 1C:69:20:E9:18:24
```

## 🎮 Utilisation

### Démarrage

1. Alimentez l'ESP32 (USB ou alimentation externe)
2. Le device se connecte automatiquement au WiFi
3. Synchronisation NTP automatique
4. Connexion au broker MQTT
5. Début des mesures selon l'intervalle configuré

### Topics MQTT

Le firmware publie sur deux topics principaux :

#### 1. Topic données : `datayoti/sensor/{device_id}/data`

Publié à chaque mesure (intervalle configurable) :

```json
{
  "device_id": "1C:69:20:E9:18:24",
  "timestamp": "2025-11-03T14:30:25.000Z",
  "temperature": 22.5,
  "humidity": 65.0
}
```

#### 2. Topic heartbeat : `datayoti/sensor/{device_id}/heartbeat`

Publié à chaque mesure pour monitoring du device :

```json
{
  "device_id": "1C:69:20:E9:18:24",
  "site_id": "SITE_001",
  "timestamp": "2025-11-03T14:30:25.000Z",
  "rssi": -45,
  "free_heap": 234567,
  "uptime": 3600,
  "min_heap": 220000,
  "ntp_sync": true
}
```

#### 3. Topic status (LWT) : `datayoti/sensor/{device_id}/status`

Message de Last Will Testament automatique :
- `online` : Device connecté
- `offline` : Device déconnecté (LWT)

### Monitoring

Le firmware affiche des informations détaillées dans les logs série :

```
=== STATUT SYSTÈME ===
Uptime: 3600 secondes (1.00 heures)
Heap libre: 234567 bytes (87.2% de 268984 bytes)
Heap minimal atteint: 220000 bytes
Fragmentation: 15%
WiFi RSSI: -45 dBm (Excellent)
MQTT État: Connecté (code: 0)
NTP Synchronisé: Oui (dernière sync: 30 sec ago)
=====================
```

### Alertes automatiques

Le système génère des alertes dans les cas suivants :

- ⚠️ **Mémoire faible** : Heap < 50 KB
- ⚠️ **Signal WiFi critique** : RSSI < -85 dBm
- ⚠️ **NTP non synchronisé** : Pas de sync depuis > 1 heure
- ⚠️ **Fragmentation élevée** : > 30%

## 📊 Format des données

### Timestamps

Tous les timestamps sont au format **RFC3339** en **UTC** :

```
2025-11-03T14:30:25.000Z
```

Format : `YYYY-MM-DDTHH:MM:SS.sssZ`

### Validation des données

Les données sont validées avant envoi :

| Paramètre | Plage valide (DHT22) | Plage valide (DHT11) |
|-----------|---------------------|---------------------|
| Température | -40°C à +80°C | 0°C à +50°C |
| Humidité | 0% à 100% | 20% à 90% |

### Codes RSSI (qualité signal WiFi)

| RSSI | Qualité |
|------|---------|
| > -50 dBm | Excellent |
| -50 à -60 dBm | Très bon |
| -60 à -70 dBm | Bon |
| -70 à -80 dBm | Moyen |
| -80 à -85 dBm | Faible |
| < -85 dBm | Très faible |

## 🛠️ Développement

### Dépendances

Le projet utilise les bibliothèques suivantes (gérées par PlatformIO) :

```ini
lib_deps = 
    adafruit/DHT sensor library@^1.4.4
    knolleary/PubSubClient@^2.8
    bblanchon/ArduinoJson@^6.21.3
    arduino-libraries/NTPClient@^3.2.1
```

### Structure du code

```
datayoti-esp32-firmware/
├── include/                    # Headers des modules
│   ├── config.example.h        # Template de configuration
│   ├── config.h                # Configuration locale (ignoré par git)
│   ├── device_manager.h        # Gestion identification devices
│   ├── wifi_manager.h          # Gestion WiFi
│   ├── mqtt_manager.h          # Gestion MQTT
│   ├── time_manager.h          # Gestion temps/NTP
│   ├── sensor_manager.h        # Gestion capteurs
│   └── system_monitor.h        # Monitoring système
├── src/                        # Implémentations
│   ├── main.cpp                # Point d'entrée principal
│   ├── device_manager.cpp
│   ├── wifi_manager.cpp
│   ├── mqtt_manager.cpp
│   ├── time_manager.cpp
│   ├── sensor_manager.cpp
│   └── system_monitor.cpp
├── lib/                        # Bibliothèques tierces (vide)
├── platformio.ini              # Configuration PlatformIO
├── LICENSE                     # Licence MIT
└── README.md                   # Cette documentation
```

### Ajouter un nouveau capteur

Pour ajouter un nouveau type de capteur (ex: BME280, DS18B20) :

1. **Modifier `sensor_manager.h`** : Ajouter les prototypes
2. **Modifier `sensor_manager.cpp`** : Implémenter la lecture
3. **Modifier `config.h`** : Ajouter les paramètres de configuration
4. **Modifier `main.cpp`** : Intégrer dans la boucle principale
5. **Modifier le JSON** : Adapter `createDataJson()` pour inclure les nouvelles données

### Tests

```bash
# Compilation sans upload
pio run

# Tests sur hardware
pio run --target upload
pio device monitor --baud 115200

# Vérification statique du code
pio check

# Nettoyage
pio run --target clean
```

### Convention de code

- **Nommage** :
  - Variables : `camelCase`
  - Fonctions : `camelCase()`
  - Classes : `PascalCase`
  - Constantes : `UPPER_SNAKE_CASE`
- **Indentation** : 4 espaces
- **Accolades** : Style K&R
- **Commentaires** : En français ou anglais, cohérents

## 🐛 Dépannage

### Problème : ESP32 ne se connecte pas au WiFi

**Solutions** :
- Vérifiez le SSID et le mot de passe dans `config.h`
- Vérifiez que le réseau WiFi est en 2.4 GHz (l'ESP32 ne supporte pas le 5 GHz)
- Vérifiez la portée du signal WiFi
- Essayez de redémarrer votre routeur

### Problème : MQTT ne se connecte pas

**Solutions** :
- Vérifiez l'IP du broker MQTT
- Vérifiez que le broker est démarré : `sudo systemctl status mosquitto`
- Vérifiez les credentials MQTT
- Vérifiez les règles de pare-feu (port 1883)
- Testez avec un client MQTT : `mosquitto_sub -h 192.168.1.100 -t datayoti/# -v`

### Problème : Erreurs de lecture du capteur DHT

**Solutions** :
- Vérifiez les connexions physiques
- Vérifiez que vous utilisez le bon type de capteur (`DHT11` ou `DHT22`)
- Vérifiez que la résistance pull-up est bien connectée (10kΩ entre VCC et DATA)
- Attendez 2 secondes après le démarrage avant la première lecture
- Essayez un autre capteur DHT (défectueux ?)

### Problème : NTP ne se synchronise pas

**Solutions** :
- Vérifiez la connexion Internet
- Essayez un autre serveur NTP : `time.google.com`, `time.cloudflare.com`
- Vérifiez les règles de pare-feu (port UDP 123)
- Vérifiez que le WiFi est bien connecté

### Problème : Mémoire insuffisante (heap faible)

**Solutions** :
- Augmentez `MEASUREMENT_INTERVAL` pour réduire la fréquence
- Réduisez la taille du buffer JSON
- Désactivez les logs série détaillés en production
- Vérifiez les fuites mémoire avec `systemMonitor.printSystemStatus()`

### Problème : Reboot aléatoires

**Solutions** :
- Vérifiez l'alimentation (minimum 500mA recommandé)
- Ajoutez un condensateur de découplage (100µF) près de l'ESP32
- Vérifiez la qualité du câble USB
- Désactivez le WiFi power save : `WiFi.setSleep(false)`

### Logs de debug

Pour activer les logs détaillés, modifiez `platformio.ini` :

```ini
build_flags = 
    -DCORE_DEBUG_LEVEL=5
```

Niveaux :
- 0 = Aucun log
- 1 = Erreurs
- 2 = Warnings
- 3 = Info
- 4 = Debug
- 5 = Verbose

## 🤝 Contribution

Les contributions sont les bienvenues ! Pour contribuer :

1. **Fork** le projet
2. Créez une **branche** pour votre fonctionnalité (`git checkout -b feature/AmazingFeature`)
3. **Committez** vos changements (`git commit -m 'Add some AmazingFeature'`)
4. **Pushez** vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrez une **Pull Request**

### Guidelines

- Respectez l'architecture modulaire existante
- Ajoutez des commentaires pour le code complexe
- Testez sur hardware réel avant de soumettre
- Mettez à jour la documentation si nécessaire

### Reporting bugs

Ouvrez une [Issue](https://github.com/medkan01/datayoti-esp32-firmware/issues) avec :
- Description du problème
- Étapes pour reproduire
- Comportement attendu vs observé
- Environnement (modèle ESP32, version firmware, etc.)
- Logs série

## 📄 Licence

Ce projet est sous licence **MIT**. Voir le fichier [LICENSE](LICENSE) pour plus de détails.

```
MIT License

Copyright (c) 2025 DataYoti Project

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## 🙏 Remerciements

- **Espressif** pour le fantastique ESP32
- **Adafruit** pour la bibliothèque DHT
- **Nick O'Leary** pour PubSubClient
- **Benoît Blanchon** pour ArduinoJson
- La communauté **Arduino** et **PlatformIO**

## 📞 Contact & Support

- 🐛 **Issues** : [GitHub Issues](https://github.com/medkan01/datayoti-esp32-firmware/issues)
- 💬 **Discussions** : [GitHub Discussions](https://github.com/medkan01/datayoti-esp32-firmware/discussions)
- 📧 **Email** : contact@datayoti.com
- 🌐 **Website** : [datayoti.com](https://datayoti.com)

## 🗺️ Roadmap

### Version 1.1 (Q1 2026)
- [ ] Support TLS/SSL pour MQTT
- [ ] Over-The-Air (OTA) updates
- [ ] Interface web de configuration
- [ ] Support multi-capteurs (BME280, DS18B20)

### Version 1.2 (Q2 2026)
- [ ] Mode deep sleep pour économie d'énergie
- [ ] Support batterie avec monitoring
- [ ] Stockage local des données (fallback SD)
- [ ] API REST locale

### Version 2.0 (Q3 2026)
- [ ] Support LoRaWAN
- [ ] Dashboard embarqué
- [ ] Machine Learning on-device
- [ ] Support ESP32-S3 et ESP32-C3

---

**Développé avec ❤️ pour la communauté IoT**

*DataYoti ESP32 Firmware - Rendons l'IoT accessible à tous*
