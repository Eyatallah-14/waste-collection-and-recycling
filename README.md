# Système de Gestion des Poubelles

Application Qt6 complète pour la gestion intelligente des poubelles avec suivi, statistiques et notifications.

## 🎯 Fonctionnalités

### Fonctionnalités CRUD (de base)
- ✅ **Ajouter** une nouvelle poubelle
- ✅ **Modifier** les informations d'une poubelle existante
- ✅ **Supprimer** une poubelle
- ✅ **Afficher/Consulter** la liste complète des poubelles

### Fonctionnalités Normales (5)
1. ✅ **Tri par état** - Trier les poubelles par leur état (Bon/Moyen/Mauvais)
2. ✅ **Tri par type de déchet** - Organiser par type (Plastique, Verre, Papier, etc.)
3. ✅ **Recherche avancée** - Rechercher par type, ID ou localisation
4. ✅ **Statistiques détaillées** 
   - Nombre total de poubelles
   - Taux moyen de remplissage
   - Distribution par type de déchet (graphique camembert)
   - Statistiques comparatives (graphique à barres)
5. ✅ **Export des données**
   - Export PDF avec rapport complet
   - Export CSV pour analyse externe

### Fonctionnalités Avancées (2)
6. ✅ **Historique des modifications** - Traçabilité complète de toutes les actions
7. ✅ **Vérification automatique de l'état** 
   - Notification pour poubelles endommagées
   - Alerte pour taux de remplissage élevé (≥90%)

## 🎨 Design

L'interface utilise la même palette de couleurs professionnelle que le module employé:
- **Couleur primaire**: #8e944e (vert olive)
- **Couleur secondaire**: #05668D (bleu)
- **Arrière-plan**: #F0F3F5 (gris clair)
- **Texte principal**: #2C3E50 (gris foncé)

### Pages de l'application

1. **Page Liste** - Tableau avec toutes les poubelles et barre de recherche/filtres
2. **Page Formulaire** - Ajout/modification de poubelles
3. **Page Statistiques** - Graphiques interactifs (camembert + barres)
4. **Page Historique** - Journal de toutes les modifications

## 📋 Prérequis

- Qt 6.10.1 ou supérieur
- CMake 3.16 ou supérieur
- Compilateur C++17
- Qt Charts module

## 🚀 Installation et Compilation

### Avec Qt Creator

1. Ouvrir Qt Creator
2. Fichier → Ouvrir un fichier ou projet
3. Sélectionner `CMakeLists.txt`
4. Configurer le projet avec votre kit Qt
5. Compiler et exécuter

### En ligne de commande

```bash
mkdir build
cd build
cmake ..
cmake --build .
./GestionPoubelle
```

## 📊 Structure du Projet

```
gestion_poubelle/
├── CMakeLists.txt                 # Configuration CMake
├── main.cpp                       # Point d'entrée
├── gestionpoubellepages.h         # Header
├── gestionpoubellepages.cpp       # Implémentation
├── gestionpoubellepages.ui        # Interface Qt Designer
└── README.md                      # Ce fichier
```

## 💾 Structure des Données

Chaque poubelle contient:
- **ID**: Identifiant unique
- **Type de déchet**: Plastique, Verre, Papier, Organique, Métal, Mixte
- **État**: Bon, Moyen, Mauvais
- **Taux de remplissage**: 0-100%
- **Localisation**: Adresse/zone
- **Date d'installation**: Date de mise en place
- **Dernière collecte**: Date de la dernière collecte
- **Endommagée**: Oui/Non
- **Notes**: Informations supplémentaires

## 🔔 Système de Notifications

Le système vérifie automatiquement:
- **Poubelle endommagée** → Alerte critique
- **Remplissage ≥ 90%** → Notification de collecte urgente
- **Remplissage 50-89%** → Indicateur visuel jaune
- **Remplissage < 50%** → Indicateur visuel vert

## 📈 Statistiques Disponibles

1. **Graphique Camembert** - Distribution des poubelles par type de déchet
2. **Graphique à Barres** - Comparaison nombre/taux moyen par type
3. **Indicateurs clés**:
   - Nombre total de poubelles
   - Taux moyen de remplissage global
   - Nombre de poubelles endommagées

## 🔍 Fonctions de Tri et Recherche

- **Recherche dynamique** par mots-clés (type, ID, localisation)
- **Tri par état** - Organiser par qualité
- **Tri par type** - Grouper par catégorie de déchet
- **Filtrage visuel** avec codes couleur dans le tableau

## 📄 Export de Données

### Export PDF
- En-tête avec date et statistiques globales
- Tableau complet de toutes les poubelles
- Mise en page professionnelle

### Export CSV
- Format standard pour Excel/LibreOffice
- Toutes les données exportées
- Compatible avec outils d'analyse

## 🎯 Fonctionnalités Métier

- **Gestion visuelle** avec codes couleur par état
- **Indicateurs de remplissage** avec alertes automatiques
- **Historique complet** pour audit et traçabilité
- **Interface intuitive** avec navigation par onglets
- **Données de démonstration** incluses

## 📝 Notes de Développement

- Architecture MVC (Model-View-Controller)
- Utilisation de Qt Widgets pour l'interface
- Qt Charts pour les graphiques
- Gestion des données en mémoire avec QMap
- Système d'historique avec horodatage

## 🐛 Améliorations Futures

- Connexion à une base de données (SQLite/PostgreSQL)
- API REST pour synchronisation
- Application mobile compagnon
- Notifications push
- Génération de rapports planifiés
- Cartographie GPS des poubelles

## 👥 Auteur

Projet développé pour la gestion écologique des déchets

## 📜 Licence

Ce projet est fourni à des fins éducatives.

---

**Version**: 1.0.0  
**Date**: Février 2026  
**Technologie**: Qt 6.10.1, C++17, CMake
