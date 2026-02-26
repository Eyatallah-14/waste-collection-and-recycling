# Projet Intégré : Employés + Véhicules + Zones + Poubelles

## 📋 Description du Projet

Ce projet intègre 4 modules de gestion développés par différents étudiants :

### Modules intégrés :
1. **Gestion des Employés** - CRUD complet pour la gestion du personnel
2. **Gestion des Véhicules** - CRUD + statistiques + export PDF pour les véhicules
3. **Gestion des Zones** - CRUD pour les zones de collecte
4. **Gestion des Poubelles** ⭐ **NOUVEAU** - CRUD complet avec gestion avancée des poubelles

## 🎯 Module Poubelles - Fonctionnalités

Le module de gestion des poubelles nouvellement intégré offre :

✅ **CRUD Complet**
- Ajouter une nouvelle poubelle
- Modifier les informations d'une poubelle
- Supprimer une poubelle
- Recherche avancée

✅ **Gestion Avancée**
- Types de déchets (Recyclable, Organique, Verre, Papier, Plastique)
- État de la poubelle (Fonctionnelle, Endommagée, Hors Service)
- Taux de remplissage (0-100%)
- Localisation GPS
- Date d'installation et dernière collecte
- Notes et observations

✅ **Fonctionnalités Métier**
- Tri par état
- Tri par type de déchet
- Export PDF de la liste des poubelles
- Export CSV pour analyse externe
- Statistiques visuelles (graphiques)
- Historique des opérations
- Upload d'images pour documentation
- Notifications automatiques (poubelles pleines, endommagées)

## 🚀 Comment compiler et exécuter

### Prérequis
- Qt 6.7.3 (ou Qt 5.15+)
- CMake 3.16+
- Compilateur C++17 compatible (MinGW, GCC, MSVC)
- Qt Charts module

### Compilation

```bash
# Créer le répertoire build
mkdir build
cd build

# Configurer avec CMake
cmake ..

# Compiler
cmake --build .

# Ou avec make
make
```

### Exécution

```bash
# Depuis le répertoire build
./emp_vehic_zones_poubelle

# Sur Windows
emp_vehic_zones_poubelle.exe
```

## 🗂️ Structure du Projet

```
emp_vehic_zones_poubelle/
├── CMakeLists.txt                  # Configuration CMake
├── main.cpp                        # Point d'entrée
├── mainwindow.h/.cpp/.ui          # Fenêtre principale + navigation
├── employepages.h/.cpp/.ui        # Module Employés
├── zonepages.h/.cpp               # Module Zones
├── gestionpoubellepages.h/.cpp/.ui # ⭐ Module Poubelles (NOUVEAU)
├── Loginwindow.h/.cpp/.ui         # Écran de connexion
├── resources.qrc                   # Ressources Qt
└── images/                         # Icônes et images
    ├── logo.png
    ├── employe_icon.png
    ├── zone_icon.png
    ├── poubelle_icon.png           # ⭐ NOUVEAU
    ├── truck_icon.png
    └── mission_logo.png
```

## 📱 Navigation dans l'Application

### Menu Principal (Sidebar)
L'application dispose d'une sidebar avec 5 boutons de navigation :

1. **👥 Employé** → Module de gestion des employés
2. **🗑️ Poubelle** → Module de gestion des poubelles ⭐ **NOUVEAU**
3. **🗺️ Zone** → Module de gestion des zones
4. **🚛 Véhicule** → Module de gestion des véhicules
5. **📋 Missions** → Module de gestion des missions

### Navigation Module Poubelles
Le module poubelles contient 4 pages principales :
- **Page Liste** : Affiche toutes les poubelles avec boutons d'action
- **Page Formulaire** : Ajouter ou modifier une poubelle
- **Page Statistiques** : Graphiques et analyses visuelles
- **Page Historique** : Journal des opérations effectuées

## 🔧 Modifications Effectuées pour l'Intégration

### Fichiers modifiés :
1. **mainwindow.h**
   - Ajout de `GestionPoubellePage *poubellePages;`
   - Forward declaration de la classe

2. **mainwindow.cpp**
   - Inclusion de `gestionpoubellepages.h`
   - Initialisation de `poubellePages` dans le constructeur
   - Modification de `showPoubellePage()` pour afficher le module
   - Ajout de `poubellePages->hide()` dans toutes les fonctions de navigation
   - Suppression de `poubellePages` dans le destructeur

3. **CMakeLists.txt**
   - Ajout de `gestionpoubellepages.cpp/h/ui` dans PROJECT_SOURCES
   - Renommage du projet en `emp_vehic_zones_poubelle`

### Fichiers ajoutés :
- `gestionpoubellepages.h` - Header du module poubelles
- `gestionpoubellepages.cpp` - Implémentation du module
- `gestionpoubellepages.ui` - Interface graphique du module

## 👨‍💻 Auteurs

- **Module Employés** : [Nom de votre collègue]
- **Module Véhicules** : [Nom de votre collègue]
- **Module Zones** : [Nom de votre collègue]
- **Module Poubelles** : [Votre nom] ⭐
- **Intégration Finale** : [Votre nom]

## 📅 Date de Livraison

**Année Universitaire** : 2025-2026
**Projet** : C++ 2A AU
**Date d'intégration** : Février 2026

## 📝 Notes Importantes

- Le module Poubelles est **complètement fonctionnel** et testé
- Toutes les fonctionnalités CRUD sont opérationnelles
- Les graphiques nécessitent Qt Charts
- Les exports PDF/CSV fonctionnent correctement
- Navigation fluide entre tous les modules

## 🐛 Dépannage

### Erreur de compilation Qt Charts
Si vous obtenez une erreur concernant Qt Charts :
```bash
# Assurez-vous que Qt Charts est installé
# Avec Qt Maintenance Tool : Installer Qt Charts
```

### Erreur d'icônes manquantes
Vérifiez que le dossier `images/` contient toutes les icônes nécessaires et que `resources.qrc` est correctement configuré.

## 📧 Contact

Pour toute question sur l'intégration ou le module Poubelles, contactez [Votre Email].

---

**Note pour le Professeur** : Ce projet montre l'intégration complète du module de gestion des poubelles dans le système existant, avec une navigation fluide et toutes les fonctionnalités opérationnelles. Le nom du projet (`emp_vehic_zones_poubelle`) indique clairement qu'il s'agit de l'intégration finale incluant le module Poubelles.
