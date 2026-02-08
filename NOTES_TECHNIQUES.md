# Notes Techniques - Système de Gestion des Poubelles

## 🏗️ Architecture du Projet

### Structure MVC
L'application suit le pattern Model-View-Controller:

- **Model**: Structure `Poubelle` + QMap pour stockage
- **View**: Fichier `.ui` créé avec Qt Designer
- **Controller**: Classe `GestionPoubellePage`

### Composants Principaux

```
GestionPoubellePage
├── QStackedWidget (pages)
│   ├── pageList (Liste)
│   ├── pageForm (Formulaire)
│   ├── pageStats (Statistiques)
│   └── pageHistorique (Historique)
├── QTableWidget (affichage données)
├── QChart (graphiques)
└── Diverses widgets de saisie
```

## 📦 Dépendances Qt

### Modules Requis
- **Qt6::Core** - Fonctionnalités de base
- **Qt6::Widgets** - Composants d'interface
- **Qt6::Charts** - Graphiques (camembert, barres)
- **Qt6::PrintSupport** - Export PDF

### Classes Principales Utilisées
```cpp
// Widgets de base
QWidget, QPushButton, QLineEdit, QComboBox, QSpinBox
QTableWidget, QTableWidgetItem, QStackedWidget

// Graphiques
QChart, QChartView
QPieSeries, QPieSlice
QBarSeries, QBarSet, QBarCategoryAxis, QValueAxis

// Export
QPrinter, QPainter (PDF)
QFile, QTextStream (CSV)

// Layouts
QVBoxLayout, QHBoxLayout, QGridLayout

// Dialogues
QMessageBox, QFileDialog, QInputDialog
```

## 🗂️ Structure des Données

### Classe Poubelle
```cpp
struct Poubelle {
    int id;                      // Clé primaire auto-incrémentée
    QString type_dechet;         // 6 types possibles
    QString etat;                // Bon/Moyen/Mauvais
    int taux_remplissage;        // 0-100
    QString localisation;        // Obligatoire
    QString date_installation;   // Format: yyyy-MM-dd
    QString derniere_collecte;   // Format: yyyy-MM-dd
    bool endommagee;            // true/false
    QString notes;              // Texte libre
};
```

### Stockage en Mémoire
```cpp
QMap<int, Poubelle> poubelles;  // Clé = ID
int nextId;                      // Compteur auto-incrémenté
```

**Avantages**:
- Accès O(log n)
- Clés uniques garanties
- Itération facile

**Limitations**:
- Données perdues à la fermeture
- Pas de persistance

### Évolution vers Base de Données

Pour une version production, remplacer par:
```cpp
// SQLite
QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("poubelles.db");

// Table SQL
CREATE TABLE poubelles (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    type_dechet TEXT NOT NULL,
    etat TEXT NOT NULL,
    taux_remplissage INTEGER CHECK(taux_remplissage >= 0 AND taux_remplissage <= 100),
    localisation TEXT NOT NULL,
    date_installation DATE,
    derniere_collecte DATE,
    endommagee BOOLEAN DEFAULT 0,
    notes TEXT
);
```

## 🎨 Gestion du Style

### Palette de Couleurs
```cpp
// Couleurs principales
#8e944e  // Vert olive (boutons actifs, headers)
#6d7339  // Vert foncé (hover)
#05668D  // Bleu (accents)
#F0F3F5  // Gris clair (background)
#2C3E50  // Gris foncé (texte)
#E0E0E0  // Gris moyen (bordures)

// Couleurs de statut
#2ECC71  // Vert (bon état, < 50%)
#FFC300  // Jaune (moyen, 50-89%)
#E74C3C  // Rouge (mauvais, ≥ 90%, endommagée)
```

### StyleSheet Global
Appliqué dans le constructeur avec `setStyleSheet()`:
- Widgets individuels
- Headers de tableau
- Boutons (états normal, hover)
- Champs de saisie

## 📊 Système de Graphiques

### Graphique Camembert (Distribution)
```cpp
QPieSeries *pieSeries = new QPieSeries();
// Calcul des données
QMap<QString, int> compteurTypes;
for (poubelle : poubelles) {
    compteurTypes[poubelle.type_dechet]++;
}
// Ajout au graphique
for (type : compteurTypes) {
    pieSeries->append(type, count);
}
```

**Fonctionnalités**:
- Explosion des parts > 20%
- Labels avec pourcentages
- Légende en bas
- Animation au chargement

### Graphique à Barres (Comparatif)
```cpp
QBarSet *countSet = new QBarSet("Nombre");
QBarSet *fillSet = new QBarSet("Taux moyen");
// Barres groupées par type
QBarSeries *series = new QBarSeries();
series->append(countSet);
series->append(fillSet);
```

**Axes**:
- Axe X: Types de déchets (QBarCategoryAxis)
- Axe Y: Valeurs 0-100 (QValueAxis)

## 🔔 Système de Notifications

### Vérification Automatique
```cpp
void verifierEtatPoubelle(const Poubelle &p) {
    // Poubelle endommagée
    if (p.endommagee) {
        QMessageBox::warning(...);
    }
    // Taux critique
    if (p.taux_remplissage >= 90) {
        QMessageBox::information(...);
    }
}
```

**Déclenchement**:
- Après ajout d'une poubelle
- Après modification

### Codes Couleur dans le Tableau
```cpp
if (etat == "Bon") {
    item->setBackground(QColor(46, 204, 113, 50)); // Vert transparent
}
```

**Appliqué à**:
- Colonne État
- Colonne Taux de Remplissage
- Colonne Endommagée

## 📤 Export de Données

### Export PDF

**Technologie**: QPrinter + QPainter

**Processus**:
1. Créer QPrinter configuré pour PDF
2. Initialiser QPainter
3. Dessiner le contenu:
   - En-tête (titre, date)
   - Statistiques globales
   - Tableau de données
4. Gérer la pagination

**Mise en page**:
- Format: A4
- Résolution: HighResolution
- Coordonnées: absolues en points

### Export CSV

**Format**: RFC 4180 (CSV standard)

**Gestion des guillemets**:
```cpp
QString escapedNotes = notes.replace("\"", "\"\"");
out << "\"" << escapedNotes << "\"";
```

**Séparateur**: Virgule `,`

**Encodage**: UTF-8

## 🕐 Gestion de l'Historique

### Structure
```cpp
struct HistoriqueEntry {
    QDateTime dateTime;
    QString action;      // Ajout/Modification/Suppression
    int poubelleId;
    QString details;
};
```

### Sauvegarde
```cpp
void sauvegarderHistorique(const QString &action, const Poubelle &p) {
    QString log = QString("%1 - %2 - Poubelle #%3")
        .arg(QDateTime::currentDateTime().toString())
        .arg(action)
        .arg(p.id);
    // Sauvegarder dans fichier ou DB
}
```

**Évolution**:
- Actuellement: qDebug() pour développement
- Production: Fichier texte ou table SQL

## 🔍 Système de Recherche

### Recherche Simple
```cpp
void rechercherPoubelle() {
    QString recherche = searchBox->text().toLower();
    // Filtre sur tous les champs
    if (id.contains(recherche) || 
        type.contains(recherche) ||
        localisation.contains(recherche)) {
        // Afficher
    }
}
```

**Champs recherchés**:
- ID (converti en QString)
- Type de déchet
- Localisation
- État

### Tri
```cpp
void trierParEtat() {
    QList<Poubelle> liste = poubelles.values();
    std::sort(liste.begin(), liste.end(), 
        [](const Poubelle &a, const Poubelle &b) {
            return a.etat < b.etat;
        });
}
```

**Algorithme**: std::sort avec lambda

## 🎯 Gestion des Événements

### Connexions Signal/Slot
```cpp
// Navigation
connect(btnListPoubelles, &QPushButton::clicked, 
        this, &GestionPoubellePage::showListPage);

// CRUD
connect(btnConfirmAdd, &QPushButton::clicked,
        this, &GestionPoubellePage::ajouterPoubelle);

// Boutons dynamiques dans tableau
connect(btnUpdate, &QPushButton::clicked, [this, p]() {
    remplirFormulaire(p);
    showFormPage();
});
```

### Validation des Données
```cpp
void ajouterPoubelle() {
    if (localisation.isEmpty()) {
        QMessageBox::warning(this, "Erreur", 
            "La localisation est obligatoire !");
        return;
    }
    // Continuer...
}
```

## 🖼️ Gestion des Ressources

### Fichier resources.qrc
```xml
<RCC>
    <qresource prefix="/">
        <file>images/update.png</file>
        <file>images/delete.png</file>
    </qresource>
</RCC>
```

### Utilisation
```cpp
QPixmap updatePixmap(":/images/update.png");
btnUpdate->setIcon(QIcon(updatePixmap));
```

**Avantage**: Ressources embarquées dans l'exécutable

## ⚡ Optimisations

### Performance
- **QMap** pour recherche rapide O(log n)
- **setEditTriggers(NoEditTriggers)** sur tableaux
- **setFocusPolicy(Qt::NoFocus)** pour performance
- Mise à jour graphiques uniquement quand nécessaire

### Mémoire
- Destructeur libère `ui`
- Smart pointers pour nouveaux widgets
- Réutilisation des layouts existants

## 🔧 Compilation et Déploiement

### Options CMake
```cmake
set(CMAKE_AUTOUIC ON)  # Génération automatique des headers UI
set(CMAKE_AUTOMOC ON)  # Métaobjets Qt automatiques
set(CMAKE_AUTORCC ON)  # Ressources Qt automatiques
```

### Déploiement Windows
```bash
windeployqt GestionPoubelle.exe
```

### Déploiement Linux
```bash
linuxdeployqt GestionPoubelle -appimage
```

## 🐛 Débogage

### Messages de Débogage
```cpp
qDebug() << "HISTORIQUE:" << log;
```

### Tests Recommandés
1. Ajout avec champs vides
2. Modification sans sélection
3. Suppression avec confirmation
4. Recherche avec caractères spéciaux
5. Export dans dossiers protégés
6. Graphiques avec 0 données
7. Taux de remplissage > 100

## 📚 Documentation Qt Utile

- [QTableWidget](https://doc.qt.io/qt-6/qtablewidget.html)
- [Qt Charts](https://doc.qt.io/qt-6/qtcharts-index.html)
- [QPrinter](https://doc.qt.io/qt-6/qprinter.html)
- [QFileDialog](https://doc.qt.io/qt-6/qfiledialog.html)

## 🚀 Prochaines Étapes

### Version 2.0 Planifiée
- [ ] Base de données SQLite
- [ ] Authentification utilisateurs
- [ ] Graphiques supplémentaires
- [ ] Mode sombre
- [ ] Impression directe
- [ ] Import CSV
- [ ] API REST
- [ ] Notifications système

---

**Dernière mise à jour**: Février 2026  
**Mainteneur**: Équipe de développement
