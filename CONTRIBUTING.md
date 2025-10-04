# Contribution Guidelines

Merci de votre intérêt pour contribuer au ESP32 IoT Sensor Firmware ! 🎉

## 🤝 Types de contributions

Nous accueillons tous types de contributions :
- 🐛 Correction de bugs
- ✨ Nouvelles fonctionnalités
- 📖 Amélioration de la documentation
- 🧪 Tests et validation
- 🎨 Améliorations d'interface/UX
- 🔧 Optimisations de performance

## 📋 Avant de commencer

### Vérifier l'existant
1. Consultez les [Issues existantes](https://github.com/your-username/esp32-sensor-firmware/issues)
2. Regardez les [Pull Requests ouvertes](https://github.com/your-username/esp32-sensor-firmware/pulls)
3. Lisez la [documentation](README.md) et [l'architecture](README_ARCHITECTURE.md)

### Créer une Issue (optionnel mais recommandé)
Pour les changements importants, créez une issue pour discuter :
- Description du problème ou fonctionnalité
- Contexte et motivation
- Solution proposée
- Alternatives considérées

## 🛠️ Processus de développement

### 1. Fork et clone
```bash
git clone https://github.com/your-username/esp32-sensor-firmware.git
cd esp32-sensor-firmware
git remote add upstream https://github.com/original-username/esp32-sensor-firmware.git
```

### 2. Créer une branche
```bash
git checkout -b feature/description-courte
# ou
git checkout -b bugfix/issue-123
```

### 3. Configuration de développement
```bash
# Copier la configuration d'exemple
cp include/config_local.example.h include/config_local.h

# Éditer avec vos valeurs de test
nano include/config_local.h
```

### 4. Développement

#### Standards de code
- **Style** : Suivre le style Arduino/C++ existant
- **Nommage** : camelCase pour variables, PascalCase pour classes
- **Commentaires** : En français ou anglais, cohérent avec l'existant
- **Modularité** : Respecter l'architecture modulaire

#### Structure des commits
```
type(scope): description courte

Description plus détaillée si nécessaire.

Fixes #123
```

Types :
- `feat`: nouvelle fonctionnalité
- `fix`: correction de bug
- `docs`: documentation
- `style`: formatage, pas de changement de logique
- `refactor`: refactoring sans changement de comportement
- `test`: ajout/modification de tests
- `chore`: maintenance, dépendances

Exemples :
```
feat(mqtt): add TLS support for secure connections

Add WiFiClientSecure implementation with certificate validation
for production environments.

Fixes #45

fix(sensor): handle DHT read timeout gracefully

Prevent infinite blocking when DHT sensor is disconnected.
Add retry mechanism with exponential backoff.

Fixes #67
```

### 5. Tests

#### Tests locaux
```bash
# Compilation
pio run

# Tests sur hardware (si disponible)
pio run --target upload
pio device monitor

# Vérification statique
pio check
```

#### Tests à effectuer
- [ ] Compilation sans erreurs ni warnings
- [ ] Fonctionnement avec vraie carte ESP32
- [ ] Pas de fuite mémoire (monitoring heap)
- [ ] Gestion des erreurs réseau
- [ ] Respect des standards de sécurité

### 6. Documentation

#### Mettre à jour si nécessaire :
- [ ] README.md (nouvelles fonctionnalités)
- [ ] README_ARCHITECTURE.md (changements d'architecture)  
- [ ] QUICK_START.md (nouvelles étapes)
- [ ] Commentaires dans le code
- [ ] Exemples de configuration

### 7. Pull Request

#### Avant de soumettre
- [ ] Rebase sur la branche main la plus récente
- [ ] Commits atomiques et messages clairs
- [ ] Tests passés
- [ ] Documentation mise à jour
- [ ] Aucune donnée sensible dans les commits

#### Template de PR
```markdown
## Description
Brève description des changements.

## Type de changement
- [ ] Bug fix (non-breaking change)
- [ ] Nouvelle fonctionnalité (non-breaking change)
- [ ] Breaking change (fonctionnalité existante modifiée)
- [ ] Documentation

## Tests effectués
- [ ] Compilation réussie
- [ ] Tests sur ESP32 réel
- [ ] Tests de régression

## Checklist
- [ ] Code suit les standards du projet
- [ ] Documentation mise à jour
- [ ] Pas de données sensibles
- [ ] Tests ajoutés/mis à jour
```

## 🐛 Signalement de bugs

### Template d'issue
```markdown
## Description du bug
Description claire et concise du problème.

## Reproduction
Étapes pour reproduire :
1. Configuration matérielle
2. Configuration logicielle  
3. Actions effectuées
4. Erreur observée

## Comportement attendu
Description du comportement attendu.

## Environnement
- Version firmware : [ex: v1.0.0]
- Modèle ESP32 : [ex: ESP32-DevKitC]
- Capteur : [ex: DHT22]
- Broker MQTT : [ex: Mosquitto 2.0]
- Logs série : [coller les logs pertinents]

## Informations supplémentaires
Contexte, captures d'écran, etc.
```

## ✨ Demande de fonctionnalité

### Template d'issue
```markdown
## Fonctionnalité demandée
Description claire de la fonctionnalité souhaitée.

## Motivation
Pourquoi cette fonctionnalité serait utile ?

## Solution proposée
Description détaillée de ce que vous aimeriez voir implémenté.

## Alternatives
Alternatives que vous avez considérées.

## Contexte supplémentaire
Informations additionnelles, exemples d'usage.
```

## 📖 Contribution à la documentation

### Types de documentation
- **README** : Vue d'ensemble, installation
- **Architecture** : Design technique, modules
- **Quick Start** : Guide rapide
- **Security** : Bonnes pratiques sécurité
- **API** : Documentation des interfaces

### Standards documentation
- **Clarté** : Simple et accessible
- **Exemples** : Code et configuration concrets
- **Structure** : Titre, description, exemple, notes
- **Langue** : Français ou anglais cohérent

## 🎯 Domaines d'aide

Nous cherchons particulièrement de l'aide sur :

### Haute priorité
- 🔐 **Sécurité** : TLS/SSL, authentification robuste
- 🧪 **Tests** : Tests automatisés, CI/CD
- 📊 **Monitoring** : Métriques avancées, alertes
- 🌍 **Internationalisation** : Support multi-langues

### Moyenne priorité  
- 📱 **Capteurs** : Support BME280, DS18B20, etc.
- 🔄 **Protocoles** : CoAP, LoRaWAN
- 🎨 **Interface** : Web dashboard embarqué
- ⚡ **Performance** : Optimisations batterie

### Projets annexes
- 📊 **Dashboard** : Interface de monitoring
- 🗄️ **Backend** : API de collecte des données
- 📱 **Mobile** : App de configuration
- 🏠 **Intégrations** : Home Assistant, Node-RED

## 🏆 Reconnaissance

Les contributeurs sont listés dans :
- [Contributors](https://github.com/your-username/esp32-sensor-firmware/graphs/contributors)
- Changelog du projet
- README principal

## ❓ Questions

Des questions ? Plusieurs options :
- 💬 [Discussions GitHub](https://github.com/your-username/esp32-sensor-firmware/discussions)
- 📧 Email : contribute@yourproject.com
- 🐛 [Issues](https://github.com/your-username/esp32-sensor-firmware/issues) pour bugs/features

Merci de contribuer au projet ! 🚀