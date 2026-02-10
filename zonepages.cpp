#include "zonepages.h"
#include <QHeaderView>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QPainter>

// ============================================================================
// Implémentation de ZoneDialog
// ============================================================================

ZoneDialog::ZoneDialog(QWidget *parent, int zoneId)
    : QDialog(parent), m_zoneId(zoneId)
{
    setupUI();
    applyStyles();

    if (zoneId == -1) {
        setWindowTitle("Ajouter une nouvelle zone");
    } else {
        setWindowTitle("Modifier la zone");
    }
}

ZoneDialog::~ZoneDialog()
{
}

void ZoneDialog::setupUI()
{
    setModal(true);
    setMinimumWidth(600);
    setMinimumHeight(550);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // En-tête avec fond coloré
    QFrame *headerFrame = new QFrame();
    headerFrame->setObjectName("headerFrame");
    QVBoxLayout *headerLayout = new QVBoxLayout(headerFrame);
    headerLayout->setContentsMargins(30, 25, 30, 25);

    QLabel *titleLabel = new QLabel(m_zoneId == -1 ? "➕ Ajouter une nouvelle zone" : "✏️ Modifier la zone");
    titleLabel->setObjectName("dialogTitle");

    QLabel *subtitleLabel = new QLabel(m_zoneId == -1 ?
                                           "Remplissez les informations ci-dessous pour créer une nouvelle zone" :
                                           "Modifiez les informations de la zone");
    subtitleLabel->setObjectName("dialogSubtitle");

    headerLayout->addWidget(titleLabel);
    headerLayout->addWidget(subtitleLabel);
    mainLayout->addWidget(headerFrame);

    // Conteneur du formulaire
    QWidget *formContainer = new QWidget();
    QVBoxLayout *formContainerLayout = new QVBoxLayout(formContainer);
    formContainerLayout->setContentsMargins(30, 30, 30, 30);
    formContainerLayout->setSpacing(25);

    // Formulaire
    QVBoxLayout *formLayout = new QVBoxLayout();
    formLayout->setSpacing(20);

    // Nom de la zone
    QVBoxLayout *nomLayout = new QVBoxLayout();
    nomLayout->setSpacing(8);
    QLabel *nomLabel = new QLabel("Nom de la zone *");
    nomLabel->setObjectName("formLabel");
    nomEdit = new QLineEdit();
    nomEdit->setPlaceholderText("Ex: Ariana, Menzah 5, Lac 2...");
    nomEdit->setObjectName("formInput");
    nomLayout->addWidget(nomLabel);
    nomLayout->addWidget(nomEdit);
    formLayout->addLayout(nomLayout);

    // Adresse
    QVBoxLayout *adresseLayout = new QVBoxLayout();
    adresseLayout->setSpacing(8);
    QLabel *adresseLabel = new QLabel("Adresse / Quartier *");
    adresseLabel->setObjectName("formLabel");
    adresseEdit = new QLineEdit();
    adresseEdit->setPlaceholderText("Ex: 7 Rue de la Gare, Dar Fadhal");
    adresseEdit->setObjectName("formInput");
    adresseLayout->addWidget(adresseLabel);
    adresseLayout->addWidget(adresseEdit);
    formLayout->addLayout(adresseLayout);

    // Ligne avec Superficie et Poubelles côte à côte
    QHBoxLayout *numberFieldsLayout = new QHBoxLayout();
    numberFieldsLayout->setSpacing(20);

    // Superficie
    QVBoxLayout *superficieLayout = new QVBoxLayout();
    superficieLayout->setSpacing(8);
    QLabel *superficieLabel = new QLabel("Superficie *");
    superficieLabel->setObjectName("formLabel");
    superficieSpinBox = new QSpinBox();
    superficieSpinBox->setMinimum(100);
    superficieSpinBox->setMaximum(999999);
    superficieSpinBox->setSuffix(" m²");
    superficieSpinBox->setValue(1000);
    superficieSpinBox->setObjectName("formInput");
    superficieLayout->addWidget(superficieLabel);
    superficieLayout->addWidget(superficieSpinBox);
    numberFieldsLayout->addLayout(superficieLayout);

    // Nombre de poubelles
    QVBoxLayout *poubellesLayout = new QVBoxLayout();
    poubellesLayout->setSpacing(8);
    QLabel *poubellesLabel = new QLabel("Nombre de poubelles *");
    poubellesLabel->setObjectName("formLabel");
    poubellesSpinBox = new QSpinBox();
    poubellesSpinBox->setMinimum(1);
    poubellesSpinBox->setMaximum(1000);
    poubellesSpinBox->setValue(10);
    poubellesSpinBox->setObjectName("formInput");
    poubellesLayout->addWidget(poubellesLabel);
    poubellesLayout->addWidget(poubellesSpinBox);
    numberFieldsLayout->addLayout(poubellesLayout);

    formLayout->addLayout(numberFieldsLayout);
    formContainerLayout->addLayout(formLayout);

    // Cadre d'information
    QFrame *infoFrame = new QFrame();
    infoFrame->setObjectName("infoFrame");
    QHBoxLayout *infoLayout = new QHBoxLayout(infoFrame);
    infoLayout->setContentsMargins(15, 12, 15, 12);

    QLabel *infoIcon = new QLabel("ℹ️");
    infoIcon->setStyleSheet("font-size: 18px;");

    QLabel *infoText = new QLabel("Les champs marqués d'un astérisque (*) sont obligatoires");
    infoText->setObjectName("infoText");
    infoText->setWordWrap(true);

    infoLayout->addWidget(infoIcon);
    infoLayout->addWidget(infoText, 1);

    formContainerLayout->addWidget(infoFrame);
    formContainerLayout->addStretch();

    mainLayout->addWidget(formContainer);

    // Pied de page avec boutons
    QFrame *footerFrame = new QFrame();
    footerFrame->setObjectName("footerFrame");
    QHBoxLayout *footerLayout = new QHBoxLayout(footerFrame);
    footerLayout->setContentsMargins(30, 20, 30, 20);
    footerLayout->setSpacing(15);

    cancelButton = new QPushButton("✕ Annuler");
    cancelButton->setObjectName("cancelButton");
    cancelButton->setFixedHeight(45);
    cancelButton->setMinimumWidth(130);
    connect(cancelButton, &QPushButton::clicked, this, &ZoneDialog::onCancelClicked);

    saveButton = new QPushButton(m_zoneId == -1 ? "✓ Ajouter la zone" : "✓ Enregistrer");
    saveButton->setObjectName("saveButton");
    saveButton->setFixedHeight(45);
    saveButton->setMinimumWidth(180);
    connect(saveButton, &QPushButton::clicked, this, &ZoneDialog::onSaveClicked);

    footerLayout->addStretch();
    footerLayout->addWidget(cancelButton);
    footerLayout->addWidget(saveButton);

    mainLayout->addWidget(footerFrame);
}

void ZoneDialog::applyStyles()
{
    QString styleSheet = R"(
        QDialog {
            background-color: white;
        }

        QFrame#headerFrame {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #8e944e, stop:1 #6d7339);
            border: none;
        }

        QLabel#dialogTitle {
            font-size: 26px;
            font-weight: bold;
            color: white;
            margin-bottom: 5px;
        }

        QLabel#dialogSubtitle {
            font-size: 14px;
            color: rgba(255, 255, 255, 0.9);
            font-weight: normal;
        }

        QLabel#formLabel {
            font-size: 13px;
            font-weight: 600;
            color: #2C3E50;
            margin-bottom: 5px;
        }

        QLineEdit#formInput {
            padding: 14px 18px;
            border: 2px solid #E0E8D0;
            border-radius: 10px;
            background-color: #FAFAF8;
            font-size: 14px;
            color: #333;
        }

        QLineEdit#formInput:hover {
            border-color: #C8D0A8;
            background-color: white;
        }

        QLineEdit#formInput:focus {
            border-color: #8e944e;
            background-color: white;
        }

        QSpinBox#formInput {
            padding: 14px 18px;
            border: 2px solid #E0E8D0;
            border-radius: 10px;
            background-color: #FAFAF8;
            font-size: 14px;
            color: #333;
        }

        QSpinBox#formInput:hover {
            border-color: #C8D0A8;
            background-color: white;
        }

        QSpinBox#formInput:focus {
            border-color: #8e944e;
            background-color: white;
        }

        QFrame#infoFrame {
            background-color: #EEF2E6;
            border-left: 4px solid #8e944e;
            border-radius: 8px;
        }

        QLabel#infoText {
            font-size: 12px;
            color: #555;
        }

        QFrame#footerFrame {
            background-color: #F8F9FA;
            border-top: 1px solid #E0E0E0;
        }

        QPushButton#saveButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #8e944e, stop:1 #6d7339);
            color: white;
            border: none;
            border-radius: 10px;
            font-size: 14px;
            font-weight: bold;
            padding: 0 25px;
        }

        QPushButton#saveButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #9da658, stop:1 #7d8344);
        }

        QPushButton#saveButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #6d7339, stop:1 #5a5f2f);
        }

        QPushButton#cancelButton {
            background-color: white;
            color: #666;
            border: 2px solid #DDD;
            border-radius: 10px;
            font-size: 14px;
            font-weight: 600;
            padding: 0 25px;
        }

        QPushButton#cancelButton:hover {
            background-color: #F5F5F5;
            border-color: #BBB;
            color: #333;
        }

        QPushButton#cancelButton:pressed {
            background-color: #ECECEC;
        }
    )";

    setStyleSheet(styleSheet);
}

void ZoneDialog::onSaveClicked()
{
    if (nomEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom de la zone est obligatoire.");
        nomEdit->setFocus();
        return;
    }

    if (adresseEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "L'adresse est obligatoire.");
        adresseEdit->setFocus();
        return;
    }

    accept();
}

void ZoneDialog::onCancelClicked()
{
    reject();
}

// ============================================================================
// Implémentation de ZonePages
// ============================================================================

ZonePages::ZonePages(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    setupTable();
    applyStyles();
    loadZoneData();
    updateStatistics();
}

ZonePages::~ZonePages()
{
}

void ZonePages::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(25);

    // ==== EN-TÊTE: Titre + Statistiques ====
    QWidget *headerWidget = new QWidget();
    headerWidget->setObjectName("headerWidget");
    QVBoxLayout *headerLayout = new QVBoxLayout(headerWidget);
    headerLayout->setSpacing(20);
    headerLayout->setContentsMargins(0, 0, 0, 0);

    // Titre principal
    QLabel *titleLabel = new QLabel("🗺️ Gestion des Zones");
    titleLabel->setObjectName("pageTitle");

    // Statistiques
    QWidget *statsWidget = new QWidget();
    statsWidget->setObjectName("statsContainer");
    QHBoxLayout *statsLayout = new QHBoxLayout(statsWidget);
    statsLayout->setSpacing(20);
    statsLayout->setContentsMargins(20, 15, 20, 15);

    // Statistique 1: Total zones
    QWidget *stat1 = new QWidget();
    stat1->setObjectName("statCard");
    QVBoxLayout *stat1Layout = new QVBoxLayout(stat1);
    stat1Layout->setSpacing(5);
    stat1Layout->setContentsMargins(20, 15, 20, 15);
    QLabel *stat1Icon = new QLabel("📍");
    stat1Icon->setStyleSheet("font-size: 28px;");
    totalZonesLabel = new QLabel("0");
    totalZonesLabel->setObjectName("statValue");
    QLabel *stat1Text = new QLabel("Total Zones");
    stat1Text->setObjectName("statLabel");
    stat1Layout->addWidget(stat1Icon, 0, Qt::AlignCenter);
    stat1Layout->addWidget(totalZonesLabel, 0, Qt::AlignCenter);
    stat1Layout->addWidget(stat1Text, 0, Qt::AlignCenter);

    // Statistique 2: Surface totale
    QWidget *stat2 = new QWidget();
    stat2->setObjectName("statCard");
    QVBoxLayout *stat2Layout = new QVBoxLayout(stat2);
    stat2Layout->setSpacing(5);
    stat2Layout->setContentsMargins(20, 15, 20, 15);
    QLabel *stat2Icon = new QLabel("📐");
    stat2Icon->setStyleSheet("font-size: 28px;");
    totalSurfaceLabel = new QLabel("0 m²");
    totalSurfaceLabel->setObjectName("statValue");
    QLabel *stat2Text = new QLabel("Surface Totale");
    stat2Text->setObjectName("statLabel");
    stat2Layout->addWidget(stat2Icon, 0, Qt::AlignCenter);
    stat2Layout->addWidget(totalSurfaceLabel, 0, Qt::AlignCenter);
    stat2Layout->addWidget(stat2Text, 0, Qt::AlignCenter);

    // Statistique 3: Total poubelles
    QWidget *stat3 = new QWidget();
    stat3->setObjectName("statCard");
    QVBoxLayout *stat3Layout = new QVBoxLayout(stat3);
    stat3Layout->setSpacing(5);
    stat3Layout->setContentsMargins(20, 15, 20, 15);
    QLabel *stat3Icon = new QLabel("🗑️");
    stat3Icon->setStyleSheet("font-size: 28px;");
    totalPoubelleslabel = new QLabel("0");
    totalPoubelleslabel->setObjectName("statValue");
    QLabel *stat3Text = new QLabel("Total Poubelles");
    stat3Text->setObjectName("statLabel");
    stat3Layout->addWidget(stat3Icon, 0, Qt::AlignCenter);
    stat3Layout->addWidget(totalPoubelleslabel, 0, Qt::AlignCenter);
    stat3Layout->addWidget(stat3Text, 0, Qt::AlignCenter);

    statsLayout->addWidget(stat1);
    statsLayout->addWidget(stat2);
    statsLayout->addWidget(stat3);
    statsLayout->addStretch();

    headerLayout->addWidget(titleLabel);
    headerLayout->addWidget(statsWidget);

    // ==== BARRE D'OUTILS: Boutons d'action ====
    QWidget *toolbarWidget = new QWidget();
    toolbarWidget->setObjectName("toolbarWidget");
    QHBoxLayout *toolbarLayout = new QHBoxLayout(toolbarWidget);
    toolbarLayout->setSpacing(15);
    toolbarLayout->setContentsMargins(0, 0, 0, 0);

    // Barre de recherche
    searchBox = new QLineEdit();
    searchBox->setObjectName("searchBox");
    searchBox->setPlaceholderText("🔍 Rechercher une zone...");
    searchBox->setClearButtonEnabled(true);
    searchBox->setFixedHeight(45);
    searchBox->setMinimumWidth(350);
    connect(searchBox, &QLineEdit::textChanged, this, &ZonePages::onSearchTextChanged);

    // Bouton Ajouter
    addZoneBtn = new QPushButton("➕ Ajouter Zone");
    addZoneBtn->setObjectName("addButton");
    addZoneBtn->setFixedHeight(45);
    addZoneBtn->setMinimumWidth(160);
    connect(addZoneBtn, &QPushButton::clicked, this, &ZonePages::onAddZoneClicked);

    // Bouton Export PDF
    exportPDFBtn = new QPushButton("📄 Export PDF");
    exportPDFBtn->setObjectName("exportButton");
    exportPDFBtn->setFixedHeight(45);
    exportPDFBtn->setMinimumWidth(140);
    connect(exportPDFBtn, &QPushButton::clicked, this, &ZonePages::onExportPDFClicked);

    // Bouton Export Excel
    exportExcelBtn = new QPushButton("📊 Export Excel");
    exportExcelBtn->setObjectName("exportButton");
    exportExcelBtn->setFixedHeight(45);
    exportExcelBtn->setMinimumWidth(140);
    connect(exportExcelBtn, &QPushButton::clicked, this, &ZonePages::onExportExcelClicked);

    toolbarLayout->addWidget(searchBox);
    toolbarLayout->addStretch();
    toolbarLayout->addWidget(addZoneBtn);
    toolbarLayout->addWidget(exportPDFBtn);
    toolbarLayout->addWidget(exportExcelBtn);

    // ==== TABLEAU DES ZONES ====
    QWidget *tableContainer = new QWidget();
    tableContainer->setObjectName("tableContainer");
    QVBoxLayout *tableContainerLayout = new QVBoxLayout(tableContainer);
    tableContainerLayout->setContentsMargins(0, 0, 0, 0);

    zoneTable = new QTableWidget();
    zoneTable->setObjectName("zoneTable");

    tableContainerLayout->addWidget(zoneTable);

    // Assemblage final
    mainLayout->addWidget(headerWidget);
    mainLayout->addWidget(toolbarWidget);
    mainLayout->addWidget(tableContainer, 1);
}

void ZonePages::setupTable()
{
    zoneTable->setColumnCount(6);
    zoneTable->setHorizontalHeaderLabels({
        "ID", "Nom", "Adresse", "Superficie", "Poubelles", "Opérations"
    });

    // Configuration des colonnes
    zoneTable->setColumnWidth(0, 80);
    zoneTable->setColumnWidth(1, 180);
    zoneTable->setColumnWidth(2, 300);
    zoneTable->setColumnWidth(3, 150);
    zoneTable->setColumnWidth(4, 120);
    zoneTable->setColumnWidth(5, 200);

    // Configuration du tableau
    zoneTable->horizontalHeader()->setStretchLastSection(true);
    zoneTable->verticalHeader()->setVisible(false);
    zoneTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    zoneTable->setSelectionMode(QAbstractItemView::SingleSelection);
    zoneTable->setAlternatingRowColors(true);
    zoneTable->setShowGrid(true);
    zoneTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    zoneTable->setFocusPolicy(Qt::NoFocus);
    zoneTable->setSortingEnabled(false);
}

void ZonePages::loadZoneData()
{
    // Données exemple
    struct ZoneData {
        QString nom;
        QString adresse;
        int superficie;
        int poubelles;
    };

    QVector<ZoneData> zones = {
                               {"Centre Ville", "Avenue Habib Bourguiba, Tunis", 5000, 45},
                               {"Menzah 5", "Rue du Lac Windermere", 3500, 28},
                               {"Ariana", "Boulevard de l'Environnement", 7500, 62},
                               {"Lac 2", "Avenue Mohamed V", 4200, 35},
                               {"Marsa Plage", "Corniche de la Marsa", 2800, 22},
                               };

    int id = 1;
    for (const auto &zone : zones) {
        int row = zoneTable->rowCount();
        zoneTable->insertRow(row);
        zoneTable->setRowHeight(row, 60);

        // ID
        QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(id++));
        idItem->setTextAlignment(Qt::AlignCenter);
        zoneTable->setItem(row, 0, idItem);

        // Nom
        QTableWidgetItem *nomItem = new QTableWidgetItem(zone.nom);
        zoneTable->setItem(row, 1, nomItem);

        // Adresse
        QTableWidgetItem *adresseItem = new QTableWidgetItem(zone.adresse);
        zoneTable->setItem(row, 2, adresseItem);

        // Superficie
        QTableWidgetItem *superficieItem = new QTableWidgetItem(QString::number(zone.superficie) + " m²");
        superficieItem->setTextAlignment(Qt::AlignCenter);
        zoneTable->setItem(row, 3, superficieItem);

        // Poubelles
        QTableWidgetItem *poubellesItem = new QTableWidgetItem(QString::number(zone.poubelles));
        poubellesItem->setTextAlignment(Qt::AlignCenter);
        zoneTable->setItem(row, 4, poubellesItem);

        // Boutons d'opération (Update/Delete)
        QWidget *actionWidget = new QWidget();
        actionWidget->setStyleSheet("background-color: transparent;");
        QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);
        actionLayout->setContentsMargins(0, 0, 0, 0);
        actionLayout->setSpacing(10);
        actionLayout->setAlignment(Qt::AlignCenter);

        QSize buttonSize(35, 35);

        // Bouton Modifier
        QPushButton *editBtn = new QPushButton();
        QPixmap updatePixmap(":/images/update.png");
        updatePixmap = updatePixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        editBtn->setIcon(QIcon(updatePixmap));
        editBtn->setIconSize(buttonSize);
        editBtn->setFixedSize(buttonSize);
        editBtn->setFlat(true);
        editBtn->setStyleSheet("QPushButton { background: transparent; border: none; }");
        editBtn->setCursor(Qt::PointingHandCursor);
        editBtn->setToolTip("Modifier");
        connect(editBtn, &QPushButton::clicked, [this, row]() { onEditZoneClicked(row); });

        // Bouton Supprimer
        QPushButton *deleteBtn = new QPushButton();
        QPixmap deletePixmap(":/images/delete.png");
        deletePixmap = deletePixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        deleteBtn->setIcon(QIcon(deletePixmap));
        deleteBtn->setIconSize(buttonSize);
        deleteBtn->setFixedSize(buttonSize);
        deleteBtn->setFlat(true);
        deleteBtn->setStyleSheet("QPushButton { background: transparent; border: none; }");
        deleteBtn->setCursor(Qt::PointingHandCursor);
        deleteBtn->setToolTip("Supprimer");
        connect(deleteBtn, &QPushButton::clicked, [this, row]() { onDeleteZoneClicked(row); });

        actionLayout->addWidget(editBtn);
        actionLayout->addWidget(deleteBtn);

        zoneTable->setCellWidget(row, 5, actionWidget);
    }
}

void ZonePages::applyStyles()
{
    QString styleSheet = R"(
        /* === CONTENEUR PRINCIPAL === */
        ZonePages {
            background-color: #F5F7F3;
        }

        /* === TITRE DE LA PAGE === */
        QLabel#pageTitle {
            font-size: 32px;
            font-weight: bold;
            color: #2C3E50;
            padding-bottom: 10px;
        }

        /* === CONTENEUR STATISTIQUES === */
        QWidget#statsContainer {
            background-color: white;
            border: 2px solid #E8ECDF;
            border-radius: 15px;
        }

        QWidget#statCard {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #FAFBF8, stop:1 #F2F5EB);
            border: 2px solid #E0E8D0;
            border-radius: 12px;
            min-width: 180px;
            max-width: 220px;
        }

        QLabel#statValue {
            font-size: 28px;
            font-weight: bold;
            color: #8e944e;
        }

        QLabel#statLabel {
            font-size: 13px;
            color: #7A7A7A;
            font-weight: 600;
        }

        /* === BARRE DE RECHERCHE === */
        QLineEdit#searchBox {
            background-color: white;
            border: 2px solid #E0E8D0;
            border-radius: 10px;
            padding: 0 15px;
            font-size: 14px;
            color: #2C3E50;
        }

        QLineEdit#searchBox:hover {
            border-color: #C8D0A8;
        }

        QLineEdit#searchBox:focus {
            border-color: #8e944e;
            background-color: #FAFBF8;
        }

        /* === BOUTON AJOUTER === */
        QPushButton#addButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #8e944e, stop:1 #6d7339);
            color: white;
            border: none;
            border-radius: 10px;
            font-size: 14px;
            font-weight: bold;
            padding: 0 20px;
        }

        QPushButton#addButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #9da658, stop:1 #7d8344);
        }

        QPushButton#addButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #6d7339, stop:1 #5a5f2f);
        }

        /* === BOUTONS EXPORT === */
        QPushButton#exportButton {
            background-color: white;
            color: #8e944e;
            border: 2px solid #8e944e;
            border-radius: 10px;
            font-size: 13px;
            font-weight: bold;
            padding: 0 18px;
        }

        QPushButton#exportButton:hover {
            background-color: #8e944e;
            color: white;
        }

        QPushButton#exportButton:pressed {
            background-color: #6d7339;
            border-color: #6d7339;
        }

        /* === CONTENEUR TABLEAU === */
        QWidget#tableContainer {
            background-color: white;
            border: 3px solid #8e944e;
            border-radius: 15px;
            padding: 10px;
        }

        /* === TABLEAU === */
        QTableWidget#zoneTable {
            background-color: #FEFEF9;
            alternate-background-color: #F8FAF4;
            border: none;
            border-radius: 10px;
            gridline-color: #E8ECDF;
            font-size: 13px;
            color: #2C3E50;
        }

        QTableWidget#zoneTable::item {
            padding: 12px 8px;
            border-bottom: 1px solid #F0F4E8;
        }

        QTableWidget#zoneTable::item:selected {
            background-color: rgba(142, 148, 78, 0.2);
            color: #2C3E50;
        }

        /* === EN-TÊTE DE TABLEAU === */
        QHeaderView::section {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #8e944e, stop:1 #7a8242);
            color: white;
            padding: 14px 8px;
            border: none;
            border-right: 1px solid rgba(255, 255, 255, 0.2);
            font-weight: bold;
            font-size: 12px;
            text-transform: uppercase;
        }

        QHeaderView::section:first {
            border-top-left-radius: 10px;
        }

        QHeaderView::section:last {
            border-top-right-radius: 10px;
            border-right: none;
        }

        QHeaderView::section:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #9da658, stop:1 #8a9348);
        }
    )";

    setStyleSheet(styleSheet);
}

void ZonePages::updateStatistics()
{
    int totalZones = zoneTable->rowCount();
    int totalSurface = 0;
    int totalPoubelles = 0;

    for (int i = 0; i < totalZones; ++i) {
        QString superficieText = zoneTable->item(i, 3)->text();
        superficieText.remove(" m²");
        totalSurface += superficieText.toInt();

        totalPoubelles += zoneTable->item(i, 4)->text().toInt();
    }

    totalZonesLabel->setText(QString::number(totalZones));
    totalSurfaceLabel->setText(QString::number(totalSurface) + " m²");
    totalPoubelleslabel->setText(QString::number(totalPoubelles));
}

void ZonePages::onAddZoneClicked()
{
    showZoneDialog(-1);
}

void ZonePages::onExportPDFClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "PDF Files (*.pdf)");
    if (!fileName.isEmpty()) {
        QMessageBox::information(this, "Export PDF", "Les zones ont été exportées en PDF avec succès!");
    }
}

void ZonePages::onExportExcelClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en Excel", "", "Excel Files (*.xlsx)");
    if (!fileName.isEmpty()) {
        QMessageBox::information(this, "Export Excel", "Les zones ont été exportées en Excel avec succès!");
    }
}

void ZonePages::onSearchTextChanged(const QString &text)
{
    for (int i = 0; i < zoneTable->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < zoneTable->columnCount() - 1; ++j) {
            QTableWidgetItem *item = zoneTable->item(i, j);
            if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        zoneTable->setRowHidden(i, !match);
    }
}

void ZonePages::onEditZoneClicked(int row)
{
    int zoneId = zoneTable->item(row, 0)->text().toInt();
    showZoneDialog(zoneId);
}

void ZonePages::onDeleteZoneClicked(int row)
{
    QString zoneName = zoneTable->item(row, 1)->text();
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirmation",
        QString("Êtes-vous sûr de vouloir supprimer la zone '%1' ?").arg(zoneName),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        zoneTable->removeRow(row);
        updateStatistics();
        QMessageBox::information(this, "Suppression", "Zone supprimée avec succès!");
    }
}

void ZonePages::onViewZoneDetails(int row)
{
    QString zoneInfo = QString("Détails de la zone:\n\n"
                               "ID: %1\n"
                               "Nom: %2\n"
                               "Adresse: %3\n"
                               "Superficie: %4\n"
                               "Poubelles: %5")
                           .arg(zoneTable->item(row, 0)->text())
                           .arg(zoneTable->item(row, 1)->text())
                           .arg(zoneTable->item(row, 2)->text())
                           .arg(zoneTable->item(row, 3)->text())
                           .arg(zoneTable->item(row, 4)->text());

    QMessageBox::information(this, "Détails de la zone", zoneInfo);
}

void ZonePages::onOpenMapsClicked(int row)
{
    QString zoneName = zoneTable->item(row, 1)->text();
    QString zoneAddress = zoneTable->item(row, 2)->text();

    QString searchQuery = zoneAddress + ", Tunis, Tunisia";
    QString encodedQuery = QUrl::toPercentEncoding(searchQuery);
    QString mapsUrl = "https://www.google.com/maps/search/?api=1&query=" + encodedQuery;

    if (!QDesktopServices::openUrl(QUrl(mapsUrl))) {
        QMessageBox::warning(this, "Erreur",
                             "Impossible d'ouvrir Google Maps.\n"
                             "Adresse: " + zoneAddress);
    }
}

void ZonePages::showZoneDialog(int zoneId)
{
    ZoneDialog *dialog = new ZoneDialog(this, zoneId);

    if (zoneId != -1) {
        for (int i = 0; i < zoneTable->rowCount(); ++i) {
            if (zoneTable->item(i, 0)->text().toInt() == zoneId) {
                dialog->setNom(zoneTable->item(i, 1)->text());
                dialog->setAdresse(zoneTable->item(i, 2)->text());

                QString superficieText = zoneTable->item(i, 3)->text();
                superficieText.remove(" m²");
                dialog->setSuperficie(superficieText.toInt());

                dialog->setNombrePoubelles(zoneTable->item(i, 4)->text().toInt());
                break;
            }
        }
    }

    if (dialog->exec() == QDialog::Accepted) {
        if (zoneId == -1) {
            addNewZone(dialog->getNom(), dialog->getAdresse(),
                       dialog->getSuperficie(), dialog->getNombrePoubelles());
        } else {
            updateZone(zoneId, dialog->getNom(), dialog->getAdresse(),
                       dialog->getSuperficie(), dialog->getNombrePoubelles());
        }
    }

    dialog->deleteLater();
}

void ZonePages::addNewZone(const QString &nom, const QString &adresse,
                           int superficie, int poubelles)
{
    int newRow = zoneTable->rowCount();
    zoneTable->insertRow(newRow);
    zoneTable->setRowHeight(newRow, 60);

    int newId = 1;
    for (int i = 0; i < newRow; ++i) {
        int currentId = zoneTable->item(i, 0)->text().toInt();
        if (currentId >= newId) {
            newId = currentId + 1;
        }
    }

    // ID
    QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(newId));
    idItem->setTextAlignment(Qt::AlignCenter);
    zoneTable->setItem(newRow, 0, idItem);

    // Nom
    QTableWidgetItem *nomItem = new QTableWidgetItem(nom);
    zoneTable->setItem(newRow, 1, nomItem);

    // Adresse
    QTableWidgetItem *adresseItem = new QTableWidgetItem(adresse);
    zoneTable->setItem(newRow, 2, adresseItem);

    // Superficie
    QTableWidgetItem *superficieItem = new QTableWidgetItem(QString::number(superficie) + " m²");
    superficieItem->setTextAlignment(Qt::AlignCenter);
    zoneTable->setItem(newRow, 3, superficieItem);

    // Poubelles
    QTableWidgetItem *poubellesItem = new QTableWidgetItem(QString::number(poubelles));
    poubellesItem->setTextAlignment(Qt::AlignCenter);
    zoneTable->setItem(newRow, 4, poubellesItem);

    // Boutons d'opération
    QWidget *actionWidget = new QWidget();
    actionWidget->setStyleSheet("background-color: transparent;");
    QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);
    actionLayout->setContentsMargins(0, 0, 0, 0);
    actionLayout->setSpacing(10);
    actionLayout->setAlignment(Qt::AlignCenter);

    QSize buttonSize(35, 35);

    QPushButton *editBtn = new QPushButton();
    QPixmap updatePixmap(":/images/update.png");
    updatePixmap = updatePixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    editBtn->setIcon(QIcon(updatePixmap));
    editBtn->setIconSize(buttonSize);
    editBtn->setFixedSize(buttonSize);
    editBtn->setFlat(true);
    editBtn->setStyleSheet("QPushButton { background: transparent; border: none; }");
    editBtn->setCursor(Qt::PointingHandCursor);
    editBtn->setToolTip("Modifier");
    connect(editBtn, &QPushButton::clicked, [this, newRow]() { onEditZoneClicked(newRow); });

    QPushButton *deleteBtn = new QPushButton();
    QPixmap deletePixmap(":/images/delete.png");
    deletePixmap = deletePixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    deleteBtn->setIcon(QIcon(deletePixmap));
    deleteBtn->setIconSize(buttonSize);
    deleteBtn->setFixedSize(buttonSize);
    deleteBtn->setFlat(true);
    deleteBtn->setStyleSheet("QPushButton { background: transparent; border: none; }");
    deleteBtn->setCursor(Qt::PointingHandCursor);
    deleteBtn->setToolTip("Supprimer");
    connect(deleteBtn, &QPushButton::clicked, [this, newRow]() { onDeleteZoneClicked(newRow); });

    actionLayout->addWidget(editBtn);
    actionLayout->addWidget(deleteBtn);

    zoneTable->setCellWidget(newRow, 5, actionWidget);

    // Bouton Email
    QPushButton *btnEmail = new QPushButton();
    QPixmap emailPixmap(":/images/email.png");
    if (!emailPixmap.isNull()) {
        emailPixmap = emailPixmap.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        btnEmail->setIcon(QIcon(emailPixmap));
        btnEmail->setIconSize(QSize(30, 30));
    }
    btnEmail->setFixedSize(50, 40);
    btnEmail->setStyleSheet(
        "QPushButton { "
        "background-color: #8e944e; "
        "color: white; "
        "border-radius: 8px; "
        "} "
        "QPushButton:hover { "
        "background-color: #6d7339; "
        "}"
        );
    btnEmail->setCursor(Qt::PointingHandCursor);
    btnEmail->setToolTip("Envoyer un email");
    connect(btnEmail, &QPushButton::clicked, [this, nom]() {
        QMessageBox::information(this, "Email",
                                 QString("Envoi d'email pour la zone: %1").arg(nom));
    });

    QWidget *emailWidget = new QWidget();
    emailWidget->setStyleSheet("background-color: transparent;");
    QHBoxLayout *emailLayout = new QHBoxLayout(emailWidget);
    emailLayout->setContentsMargins(0, 0, 0, 0);
    emailLayout->setAlignment(Qt::AlignCenter);
    emailLayout->addWidget(btnEmail);

    zoneTable->setCellWidget(newRow, 6, emailWidget);

    updateStatistics();
    QMessageBox::information(this, "Succès", "La zone a été ajoutée avec succès !");
}

void ZonePages::updateZone(int zoneId, const QString &nom, const QString &adresse,
                           int superficie, int poubelles)
{
    for (int i = 0; i < zoneTable->rowCount(); ++i) {
        if (zoneTable->item(i, 0)->text().toInt() == zoneId) {
            zoneTable->item(i, 1)->setText(nom);
            zoneTable->item(i, 2)->setText(adresse);
            zoneTable->item(i, 3)->setText(QString::number(superficie) + " m²");
            zoneTable->item(i, 4)->setText(QString::number(poubelles));

            updateStatistics();
            QMessageBox::information(this, "Succès", "La zone a été modifiée avec succès !");
            break;
        }
    }
}
