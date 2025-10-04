# Configuration MQTT pour ESP32 Sensor Firmware

## Exemple de configuration MQTT

```ini
# Mosquitto MQTT Broker
# /etc/mosquitto/mosquitto.conf

# Port d'écoute
port 1883

# Autoriser les connexions anonymes (pour les tests)
# allow_anonymous true

# Ou avec authentification (recommandé)
allow_anonymous false
password_file /etc/mosquitto/passwd

# Logs
log_dest file /var/log/mosquitto/mosquitto.log
log_type error
log_type warning  
log_type notice
log_type information

# Persistance des données
persistence true
persistence_location /var/lib/mosquitto/

# Will delay (pour Last Will Testament)
max_queued_messages 1000
```

## Création d'utilisateurs MQTT

```bash
# Créer un utilisateur pour les capteurs ESP32
mosquitto_passwd -c /etc/mosquitto/passwd sensor_user

# Ajouter d'autres utilisateurs
mosquitto_passwd /etc/mosquitto/passwd dashboard_user
mosquitto_passwd /etc/mosquitto/passwd admin_user
```

## Topics utilisés par le firmware

```
# Données des capteurs (QoS 0)
datayoti/sensor/{device_mac}/data

# Heartbeat/status des devices (QoS 0)  
datayoti/sensor/{device_mac}/heartbeat

# Last Will Testament - offline status (QoS 1, retained)
datayoti/sensor/{device_mac}/status
```

## Exemple de subscription

```bash
# Écouter tous les capteurs
mosquitto_sub -h localhost -u sensor_user -P your_password -t "datayoti/sensor/+/data"

# Écouter un capteur spécifique
mosquitto_sub -h localhost -u sensor_user -P your_password -t "datayoti/sensor/AA:BB:CC:DD:EE:FF/+"

# Écouter les heartbeats
mosquitto_sub -h localhost -u sensor_user -P your_password -t "datayoti/sensor/+/heartbeat"
```

## Configuration recommandée pour la production

```ini
# /etc/mosquitto/mosquitto.conf - Production

# Sécurité
allow_anonymous false
password_file /etc/mosquitto/passwd

# TLS/SSL (optionnel mais recommandé)
# listener 8883
# cafile /etc/mosquitto/ca.crt
# certfile /etc/mosquitto/server.crt  
# keyfile /etc/mosquitto/server.key

# Limites de connexion
max_connections 100
max_queued_messages 1000
message_size_limit 1024

# Logging
log_dest file /var/log/mosquitto/mosquitto.log
log_type warning
log_type error

# Persistance
persistence true
persistence_location /var/lib/mosquitto/
autosave_interval 300

# Will delay pour les déconnexions ESP32
will_delay_interval 30
```

## Test de la configuration

```bash
# Démarrer Mosquitto
sudo systemctl start mosquitto
sudo systemctl enable mosquitto

# Tester la connexion
mosquitto_pub -h localhost -u sensor_user -P your_password -t "test/topic" -m "Hello MQTT"

# Vérifier les logs
tail -f /var/log/mosquitto/mosquitto.log
```