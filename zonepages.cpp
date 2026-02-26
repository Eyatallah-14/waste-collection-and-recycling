#include "zonepages.h"

#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QPrinter>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QDateTime>
#include <QDebug>
#include <QList>

#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>

// =============================================================================
// STYLES — identiques à GestionPoubellePage
// =============================================================================
static const QString NAV_ACTIVE =
    "QPushButton {"
    "  background-color: #8e944e; color: white; border: none;"
    "  border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
    "QPushButton:hover { background-color: #6d7339; }";

static const QString NAV_INACTIVE =
    "QPushButton {"
    "  background-color: white; color: #8e944e; border: 2px solid #E0E0E0;"
    "  border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
    "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }";

// =============================================================================
// CONSTRUCTEUR
// =============================================================================
ZonePages::ZonePages(QWidget *parent)
    : QWidget(parent)
    , currentEditId(-1)
    , sortColumn(0)
    , sortAscending(true)
{
    setObjectName("ZonePages");

    setStyleSheet(
        "QWidget#ZonePages { background-color: #F0F3F5; }"
        "QWidget#topButtonBar, QWidget#searchBar { background-color: transparent; }"

        "QPushButton#btnSearch, QPushButton#btnTriNom, QPushButton#btnTriType,"
        "QPushButton#btnExportPdf, QPushButton#btnExportCsv {"
        "  background-color: #8e944e; color: white; border: none;"
        "  border-radius: 8px; padding: 10px 20px; font-size: 10pt; font-weight: bold; }"
        "QPushButton#btnSearch:hover, QPushButton#btnTriNom:hover,"
        "QPushButton#btnTriType:hover, QPushButton#btnExportPdf:hover,"
        "QPushButton#btnExportCsv:hover { background-color: #6d7339; }"

        "QPushButton#btnConfirmAdd, QPushButton#btnConfirmUpdate {"
        "  background-color: #8e944e; color: white; border: none;"
        "  border-radius: 10px; padding: 12px 30px; font-size: 11pt; font-weight: bold; }"
        "QPushButton#btnConfirmAdd:hover, QPushButton#btnConfirmUpdate:hover { background-color: #6d7339; }"

        "QLineEdit, QComboBox, QDoubleSpinBox {"
        "  border: 2px solid #E0E0E0; border-radius: 8px;"
        "  padding: 8px 12px; background-color: white; color: #2C3E50; }"
        "QComboBox QAbstractItemView {"
        "  background-color: white; color: #2C3E50;"
        "  selection-background-color: rgba(142,148,78,0.25); selection-color: #2C3E50; outline: none; }"

        "QLabel { color: #2C3E50; font-size: 9.5pt; font-weight: 600; }"
        "QLabel#formTitle { color: #8e944e; font-size: 18pt; font-weight: 800; }"
        "QWidget#pageForm QLabel { margin-top: 6px; margin-bottom: 4px; }"

        "QTableWidget {"
        "  background-color: white; alternate-background-color: #F7F8FA;"
        "  border: 2px solid #E0E0E0; border-radius: 10px;"
        "  gridline-color: #E0E0E0; font-size: 10pt; color: #2C3E50; }"
        "QTableWidget::viewport { background-color: white; }"
        "QTableWidget::item { padding: 10px; border-bottom: 1px solid #F0F0F0; }"
        "QTableWidget::item:selected { background-color: rgba(142,148,78,0.22); color: #2C3E50; }"
        "QHeaderView::section {"
        "  background-color: #8e944e; color: white; padding: 12px;"
        "  border: none; font-weight: bold; font-size: 10pt; cursor: pointer; }"
        "QHeaderView::section:hover { background-color: #6d7339; }"

        "QWidget#formFieldsContainer { background-color: white; border: 2px solid #8e944e; border-radius: 15px; }"
        "QWidget#statsLeftContainer, QWidget#statsRightContainer {"
        "  background-color: white; border: 2px solid #E0E0E0; border-radius: 15px; }"
        );

    // =========================================================================
    // LAYOUT
    // =========================================================================
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 10, 15, 10);

    // ── Navigation ────────────────────────────────────────────────────────────
    QWidget *topButtonBar = new QWidget(); topButtonBar->setObjectName("topButtonBar");
    QHBoxLayout *navLayout = new QHBoxLayout(topButtonBar);
    navLayout->setSpacing(10); navLayout->setContentsMargins(0,0,0,0);

    btnListZones  = new QPushButton("Liste des Zones");
    btnAddZone    = new QPushButton("Ajouter une Zone");
    btnStatistics = new QPushButton("Statistiques");
    btnMap        = new QPushButton("Carte");

    for (QPushButton *b : {btnListZones, btnAddZone, btnStatistics, btnMap}) {
        b->setMinimumHeight(45); b->setCursor(Qt::PointingHandCursor);
    }
    navLayout->addWidget(btnListZones); navLayout->addWidget(btnAddZone);
    navLayout->addWidget(btnStatistics); navLayout->addWidget(btnMap);
    navLayout->addStretch();
    mainLayout->addWidget(topButtonBar);

    pagesStack = new QStackedWidget();

    // =========================================================================
    // PAGE 1 : LISTE
    // =========================================================================
    pageList = new QWidget();
    QVBoxLayout *listLayout = new QVBoxLayout(pageList);
    listLayout->setSpacing(10);

    // ── Barre recherche + filtres ─────────────────────────────────────────────
    QWidget *searchBar = new QWidget(); searchBar->setObjectName("searchBar");
    QHBoxLayout *searchLayout = new QHBoxLayout(searchBar);
    searchLayout->setSpacing(8); searchLayout->setContentsMargins(0,0,0,0);

    searchBox = new QLineEdit();
    searchBox->setObjectName("searchBox");
    searchBox->setPlaceholderText("Rechercher par type, ID, localisation...");
    searchBox->setMinimumHeight(42); searchBox->setMinimumWidth(300);
    searchBox->setClearButtonEnabled(true);
    // Recherche en direct à chaque frappe
    connect(searchBox, &QLineEdit::textChanged, this, &ZonePages::rechercherZone);
    connect(searchBox, &QLineEdit::returnPressed, this, &ZonePages::rechercherZone);

    btnSearch = new QPushButton("Rechercher"); btnSearch->setObjectName("btnSearch");
    btnSearch->setMinimumHeight(42); btnSearch->setCursor(Qt::PointingHandCursor);

    sortCombo = new QComboBox(); sortCombo->setObjectName("sortCombo");
    sortCombo->setMinimumHeight(42); sortCombo->setMinimumWidth(145);
    sortCombo->addItem("Tous les types", "");
    sortCombo->addItem("Résidentielle",  "Résidentielle");
    sortCombo->addItem("Commerciale",    "Commerciale");
    sortCombo->addItem("Industrielle",   "Industrielle");
    sortCombo->addItem("Mixte",          "Mixte");
    sortCombo->addItem("Zone Verte",     "Zone Verte");
    sortCombo->addItem("Administrative", "Administrative");
    connect(sortCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ZonePages::filtrerParType);

    btnTriNom  = new QPushButton("Tri État");  btnTriNom->setObjectName("btnTriNom");
    btnTriNom->setMinimumHeight(42); btnTriNom->setCursor(Qt::PointingHandCursor);
    btnTriNom->setToolTip("Trier par nom (A→Z / Z→A)");

    btnTriType = new QPushButton("Tri Type");  btnTriType->setObjectName("btnTriType");
    btnTriType->setMinimumHeight(42); btnTriType->setCursor(Qt::PointingHandCursor);
    btnTriType->setToolTip("Trier par type de zone (A→Z / Z→A)");

    btnExportPdf = new QPushButton("PDF");     btnExportPdf->setObjectName("btnExportPdf");
    btnExportPdf->setMinimumHeight(42); btnExportPdf->setCursor(Qt::PointingHandCursor);
    btnExportPdf->setToolTip("Exporter en PDF mis en page");

    btnExportCsv = new QPushButton("CSV");     btnExportCsv->setObjectName("btnExportCsv");
    btnExportCsv->setMinimumHeight(42); btnExportCsv->setCursor(Qt::PointingHandCursor);
    btnExportCsv->setToolTip("Exporter en CSV");

    searchLayout->addWidget(searchBox);
    searchLayout->addWidget(btnSearch);
    searchLayout->addWidget(sortCombo);
    searchLayout->addWidget(btnTriNom);
    searchLayout->addWidget(btnTriType);
    searchLayout->addStretch();
    searchLayout->addWidget(btnExportPdf);
    searchLayout->addWidget(btnExportCsv);

    // Label compteur de résultats
    lblResultCount = new QLabel("");
    lblResultCount->setStyleSheet(
        "color:#8e944e; font-size:9pt; font-weight:600; background:transparent;");

    zoneTable = new QTableWidget(); zoneTable->setObjectName("zoneTable");

    listLayout->addWidget(searchBar);
    listLayout->addWidget(lblResultCount);
    listLayout->addWidget(zoneTable);

    // =========================================================================
    // PAGE 2 : FORMULAIRE
    // =========================================================================
    pageForm = new QWidget(); pageForm->setObjectName("pageForm");
    QVBoxLayout *formMainLayout = new QVBoxLayout(pageForm);
    formMainLayout->setAlignment(Qt::AlignHCenter);
    formMainLayout->setSpacing(18); formMainLayout->setContentsMargins(0,10,0,0);

    formTitle = new QLabel("Ajouter une Zone");
    formTitle->setObjectName("formTitle"); formTitle->setAlignment(Qt::AlignCenter);
    formMainLayout->addWidget(formTitle);

    QWidget *formFieldsContainer = new QWidget();
    formFieldsContainer->setObjectName("formFieldsContainer");
    formFieldsContainer->setMaximumWidth(900);

    QGridLayout *formGrid = new QGridLayout(formFieldsContainer);
    formGrid->setVerticalSpacing(18); formGrid->setHorizontalSpacing(20);
    formGrid->setContentsMargins(30,25,30,25);

    const QString lblS =
        "color:#2C3E50; font-size:9.5pt; font-weight:600;"
        "background:transparent; border:none; margin-top:6px; margin-bottom:4px;";

    QLabel *lblNom     = new QLabel("Nom de la Zone *");     lblNom->setStyleSheet(lblS);
    QLabel *lblAdresse = new QLabel("Adresse *");            lblAdresse->setStyleSheet(lblS);
    QLabel *lblSup     = new QLabel("Superficie (m²) *");   lblSup->setStyleSheet(lblS);
    QLabel *lblType    = new QLabel("Type de Zone *");       lblType->setStyleSheet(lblS);

    inputNom = new QLineEdit();
    inputNom->setPlaceholderText("Ex: Ariana Centre, Menzah 5...");
    inputNom->setMaxLength(100); inputNom->setMinimumHeight(42);

    inputAdresse = new QLineEdit();
    inputAdresse->setPlaceholderText("Ex: Avenue Habib Bourguiba, Centre Ville...");
    inputAdresse->setMaxLength(255); inputAdresse->setMinimumHeight(42);

    inputSuperficie = new QDoubleSpinBox();
    inputSuperficie->setMinimum(0.01); inputSuperficie->setMaximum(99999999.99);
    inputSuperficie->setDecimals(2); inputSuperficie->setValue(1000.0);
    inputSuperficie->setSuffix(" m²"); inputSuperficie->setMinimumHeight(42);
    inputSuperficie->setGroupSeparatorShown(true);

    inputTypeZone = new QComboBox(); inputTypeZone->setMinimumHeight(42);
    // Pas d'option vide — TYPEZONE NOT NULL dans Oracle
    inputTypeZone->addItem("Résidentielle",  "Résidentielle");
    inputTypeZone->addItem("Commerciale",    "Commerciale");
    inputTypeZone->addItem("Industrielle",   "Industrielle");
    inputTypeZone->addItem("Mixte",          "Mixte");
    inputTypeZone->addItem("Zone Verte",     "Zone Verte");
    inputTypeZone->addItem("Administrative", "Administrative");

    formGrid->addWidget(lblNom,          0, 0); formGrid->addWidget(inputNom,        1, 0);
    formGrid->addWidget(lblAdresse,      0, 1); formGrid->addWidget(inputAdresse,    1, 1);
    formGrid->addWidget(lblSup,          2, 0); formGrid->addWidget(inputSuperficie, 3, 0);
    formGrid->addWidget(lblType,         2, 1); formGrid->addWidget(inputTypeZone,   3, 1);

    formMainLayout->addWidget(formFieldsContainer, 0, Qt::AlignHCenter);

    QLabel *noteNonNull = new QLabel(
        "  Tous les champs sont obligatoires (NOT NULL dans la table EYA.ZONE)");
    noteNonNull->setStyleSheet(
        "background-color:rgba(142,148,78,0.1); border:1px solid #8e944e;"
        "border-radius:8px; padding:8px 14px; color:#2C3E50; font-size:9pt;");
    noteNonNull->setMaximumWidth(880);
    formMainLayout->addWidget(noteNonNull, 0, Qt::AlignHCenter);

    QHBoxLayout *btnFormLayout = new QHBoxLayout();
    btnFormLayout->setSpacing(15); btnFormLayout->addStretch();

    btnConfirmAdd = new QPushButton("Enregistrer la Zone");
    btnConfirmAdd->setObjectName("btnConfirmAdd");
    btnConfirmAdd->setMinimumWidth(200); btnConfirmAdd->setMinimumHeight(44);
    btnConfirmAdd->setCursor(Qt::PointingHandCursor);

    btnConfirmUpdate = new QPushButton("Mettre à Jour");
    btnConfirmUpdate->setObjectName("btnConfirmUpdate");
    btnConfirmUpdate->setMinimumWidth(200); btnConfirmUpdate->setMinimumHeight(44);
    btnConfirmUpdate->setVisible(false); btnConfirmUpdate->setCursor(Qt::PointingHandCursor);

    btnFormLayout->addWidget(btnConfirmAdd); btnFormLayout->addWidget(btnConfirmUpdate);
    btnFormLayout->addStretch();
    formMainLayout->addLayout(btnFormLayout);
    formMainLayout->addStretch();

    // =========================================================================
    // PAGE 3 : STATISTIQUES
    // =========================================================================
    pageStats = new QWidget();
    QHBoxLayout *statsLayout = new QHBoxLayout(pageStats); statsLayout->setSpacing(20);
    statsLeftContainer  = new QWidget(); statsLeftContainer->setObjectName("statsLeftContainer");
    statsRightContainer = new QWidget(); statsRightContainer->setObjectName("statsRightContainer");
    statsLayout->addWidget(statsLeftContainer); statsLayout->addWidget(statsRightContainer);

    // =========================================================================
    // PAGE 4 : CARTE
    // =========================================================================
    pageMap = new QWidget();
    QVBoxLayout *mapLayout = new QVBoxLayout(pageMap);
    QLabel *mapTitle = new QLabel("Carte Interactive des Zones");
    mapTitle->setStyleSheet("font-size:18pt; font-weight:bold; color:#8e944e;");
    mapTitle->setAlignment(Qt::AlignCenter);
    mapPlaceholder = new QLabel(
        "\n\nCarte Interactive des Zones\n\n"
        "Sélectionnez une zone pour afficher sa position\n"
        "Intégration OpenStreetMap à venir");
    mapPlaceholder->setStyleSheet(
        "background-color:#E8F4F8; border:3px solid #8e944e; border-radius:15px;"
        "padding:40px; font-size:14pt; color:#7B8794;");
    mapPlaceholder->setAlignment(Qt::AlignCenter);
    mapPlaceholder->setMinimumHeight(480);
    mapLayout->addWidget(mapTitle); mapLayout->addWidget(mapPlaceholder);

    pagesStack->addWidget(pageList); pagesStack->addWidget(pageForm);
    pagesStack->addWidget(pageStats); pagesStack->addWidget(pageMap);
    mainLayout->addWidget(pagesStack);

    // =========================================================================
    // SETUP + SIGNAUX
    // =========================================================================
    setupZoneTable();
    setupCharts();
    rafraichirTable();

    connect(btnListZones,  &QPushButton::clicked, this, &ZonePages::showListPage);
    connect(btnAddZone,    &QPushButton::clicked, this, &ZonePages::showFormPage);
    connect(btnStatistics, &QPushButton::clicked, this, &ZonePages::showStatsPage);
    connect(btnMap,        &QPushButton::clicked, this, &ZonePages::showMapPage);
    connect(btnConfirmAdd,    &QPushButton::clicked, this, &ZonePages::ajouterZone);
    connect(btnConfirmUpdate, &QPushButton::clicked, this, &ZonePages::modifierZone);
    connect(btnSearch,        &QPushButton::clicked, this, &ZonePages::rechercherZone);
    connect(btnTriNom,        &QPushButton::clicked, this, &ZonePages::trierParNom);
    connect(btnTriType,       &QPushButton::clicked, this, &ZonePages::trierParType);
    connect(btnExportPdf,     &QPushButton::clicked, this, &ZonePages::exporterPDF);
    connect(btnExportCsv,     &QPushButton::clicked, this, &ZonePages::exporterCSV);

    // Clic sur en-tête du tableau → tri de la colonne
    connect(zoneTable->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &ZonePages::trierColonne);

    showListPage();
}

ZonePages::~ZonePages() {}

// =============================================================================
// NAVIGATION
// =============================================================================
void ZonePages::showListPage() {
    rafraichirTable();
    pagesStack->setCurrentWidget(pageList);
    btnListZones->setStyleSheet(NAV_ACTIVE);   btnAddZone->setStyleSheet(NAV_INACTIVE);
    btnStatistics->setStyleSheet(NAV_INACTIVE); btnMap->setStyleSheet(NAV_INACTIVE);
}
void ZonePages::showFormPage() {
    viderFormulaire();
    formTitle->setText("Ajouter une Zone");
    btnConfirmAdd->setVisible(true); btnConfirmUpdate->setVisible(false);
    currentEditId = -1;
    pagesStack->setCurrentWidget(pageForm);
    btnListZones->setStyleSheet(NAV_INACTIVE); btnAddZone->setStyleSheet(NAV_ACTIVE);
    btnStatistics->setStyleSheet(NAV_INACTIVE); btnMap->setStyleSheet(NAV_INACTIVE);
}
void ZonePages::showStatsPage() {
    setupCharts();
    pagesStack->setCurrentWidget(pageStats);
    btnListZones->setStyleSheet(NAV_INACTIVE); btnAddZone->setStyleSheet(NAV_INACTIVE);
    btnStatistics->setStyleSheet(NAV_ACTIVE);  btnMap->setStyleSheet(NAV_INACTIVE);
}
void ZonePages::showMapPage() {
    pagesStack->setCurrentWidget(pageMap);
    btnListZones->setStyleSheet(NAV_INACTIVE); btnAddZone->setStyleSheet(NAV_INACTIVE);
    btnStatistics->setStyleSheet(NAV_INACTIVE); btnMap->setStyleSheet(NAV_ACTIVE);
}

// =============================================================================
// CONFIGURATION DU TABLEAU
// =============================================================================
void ZonePages::setupZoneTable()
{
    zoneTable->setColumnCount(6);
    zoneTable->setHorizontalHeaderLabels({
        "ID ↕", "Nom ↕", "Adresse ↕", "Superficie (m²) ↕", "Type ↕", "Opérations"
    });
    zoneTable->horizontalHeader()->setStretchLastSection(false);
    zoneTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    zoneTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    zoneTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    zoneTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    zoneTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    zoneTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    zoneTable->setColumnWidth(5, 110);

    zoneTable->verticalHeader()->setVisible(false);
    zoneTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    zoneTable->setSelectionMode(QAbstractItemView::SingleSelection);
    zoneTable->setAlternatingRowColors(true);
    zoneTable->setShowGrid(true);
    zoneTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    zoneTable->setFocusPolicy(Qt::NoFocus);
    zoneTable->setSortingEnabled(false); // on gère le tri manuellement via Oracle
}

// =============================================================================
// HELPERS — charger depuis Oracle
// =============================================================================
QList<Zone> requeteZones(const QString &sql, const QMap<QString,QVariant> &params = {})
{
    QList<Zone> liste;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return liste;

    QSqlQuery q(db);
    q.prepare(sql);
    for (auto it = params.begin(); it != params.end(); ++it)
        q.bindValue(it.key(), it.value());

    if (!q.exec()) {
        qWarning() << "SQL error:" << q.lastError().text();
        return liste;
    }
    while (q.next()) {
        Zone z;
        z.id_zone    = q.value("ID_ZONE").toInt();
        z.nom        = q.value("NOM").toString();
        z.adresse    = q.value("ADRESSE").toString();
        z.superficie = q.value("SUPERFICIE").toDouble();
        z.typeZone   = q.value("TYPEZONE").toString();
        liste << z;
    }
    return liste;
}

void ZonePages::chargerTable(const QList<Zone> &liste)
{
    zoneTable->setRowCount(0);
    int row = 0;
    for (const Zone &z : liste)
        ajouterLigneTable(z, row++);

    // Mise à jour du compteur
    lblResultCount->setText(QString("  %1 zone(s) trouvée(s)").arg(liste.size()));
}

// =============================================================================
// RAFRAÎCHIR — SELECT * ORDER BY ID
// =============================================================================
void ZonePages::rafraichirTable()
{
    searchBox->blockSignals(true);
    searchBox->clear();
    searchBox->blockSignals(false);
    sortCombo->blockSignals(true);
    sortCombo->setCurrentIndex(0);
    sortCombo->blockSignals(false);

    QList<Zone> liste = requeteZones(
        "SELECT ID_ZONE, NOM, ADRESSE, SUPERFICIE, TYPEZONE "
        "FROM EYA.ZONE ORDER BY ID_ZONE");

    if (liste.isEmpty() && QSqlDatabase::database().isOpen()) {
        // Vérifier si c'est une vraie erreur ou table vide
        QSqlQuery check(QSqlDatabase::database());
        check.prepare("SELECT COUNT(*) FROM EYA.ZONE");
        if (!check.exec()) {
            QMessageBox::critical(this, "Erreur BD",
                                  "Impossible de lire la table EYA.ZONE :\n" +
                                      check.lastError().text());
            return;
        }
    }

    chargerTable(liste);
    setupCharts();
}

// =============================================================================
// ██████████████  RECHERCHE AVANCÉE  ██████████████
// Recherche Oracle LIKE sur : NOM, ADRESSE, TYPEZONE, ID_ZONE
// Déclenchée : frappe texte en temps réel + bouton Rechercher
// =============================================================================
void ZonePages::rechercherZone()
{
    QString terme = searchBox->text().trimmed();
    QString typeFiltre = sortCombo->currentData().toString();

    QString sql =
        "SELECT ID_ZONE, NOM, ADRESSE, SUPERFICIE, TYPEZONE FROM EYA.ZONE WHERE 1=1 ";

    QMap<QString,QVariant> params;

    // Filtre texte libre
    if (!terme.isEmpty()) {
        sql +=
            "AND (UPPER(NOM)      LIKE UPPER(:t) "
            " OR  UPPER(ADRESSE)  LIKE UPPER(:t) "
            " OR  UPPER(TYPEZONE) LIKE UPPER(:t) "
            " OR  TO_CHAR(ID_ZONE) LIKE :t) ";
        params[":t"] = "%" + terme + "%";
    }

    // Filtre combo type
    if (!typeFiltre.isEmpty()) {
        sql += "AND TYPEZONE = :typ ";
        params[":typ"] = typeFiltre;
    }

    // Tri actuel maintenu pendant la recherche
    QStringList cols = {"ID_ZONE","NOM","ADRESSE","SUPERFICIE","TYPEZONE"};
    if (sortColumn >= 0 && sortColumn < 5) {
        sql += "ORDER BY " + cols[sortColumn] +
               (sortAscending ? " ASC" : " DESC");
    } else {
        sql += "ORDER BY ID_ZONE";
    }

    chargerTable(requeteZones(sql, params));
}

// =============================================================================
// ██████████████  FILTRE PAR TYPE (COMBO)  ██████████████
// SELECT WHERE TYPEZONE = 'Commerciale' (ou tous si vide)
// =============================================================================
void ZonePages::filtrerParType()
{
    rechercherZone(); // réutilise la logique combinée
}

// =============================================================================
// ██████████████  TRI AVANCÉ  ██████████████
// Clic sur l'en-tête → ORDER BY colonne ASC/DESC via Oracle
// =============================================================================
void ZonePages::trierColonne(int col)
{
    if (col == 5) return; // colonne Opérations → pas de tri

    // Inverser direction si même colonne, sinon ASC
    if (col == sortColumn)
        sortAscending = !sortAscending;
    else {
        sortColumn    = col;
        sortAscending = true;
    }

    // Mettre à jour les labels des en-têtes avec flèche
    QStringList headers = {"ID", "Nom", "Adresse", "Superficie (m²)", "Type", "Opérations"};
    for (int i = 0; i < 5; i++) {
        QString label = headers[i];
        if (i == sortColumn)
            label += (sortAscending ? " ▲" : " ▼");
        else
            label += " ↕";
        zoneTable->horizontalHeaderItem(i)->setText(label);
    }

    rechercherZone(); // recharge avec ORDER BY mis à jour
}

void ZonePages::trierParNom()
{
    if (sortColumn == 1)
        sortAscending = !sortAscending;
    else { sortColumn = 1; sortAscending = true; }

    // Mettre à jour en-têtes
    QStringList h = {"ID","Nom","Adresse","Superficie (m²)","Type","Opérations"};
    for (int i = 0; i < 5; i++) {
        QString lbl = h[i] + (i == sortColumn ? (sortAscending ? " ▲" : " ▼") : " ↕");
        zoneTable->horizontalHeaderItem(i)->setText(lbl);
    }
    rechercherZone();
}

void ZonePages::trierParType()
{
    if (sortColumn == 4)
        sortAscending = !sortAscending;
    else { sortColumn = 4; sortAscending = true; }

    QStringList h = {"ID","Nom","Adresse","Superficie (m²)","Type","Opérations"};
    for (int i = 0; i < 5; i++) {
        QString lbl = h[i] + (i == sortColumn ? (sortAscending ? " ▲" : " ▼") : " ↕");
        zoneTable->horizontalHeaderItem(i)->setText(lbl);
    }
    rechercherZone();
}

// =============================================================================
// AJOUTER UNE LIGNE AU TABLEAU
// =============================================================================
void ZonePages::ajouterLigneTable(const Zone &z, int row)
{
    zoneTable->insertRow(row);
    zoneTable->setRowHeight(row, 60);

    auto mkItem = [](const QString &t, int a = Qt::AlignVCenter | Qt::AlignLeft) {
        QTableWidgetItem *it = new QTableWidgetItem(t);
        it->setTextAlignment(a); return it;
    };

    zoneTable->setItem(row, 0, mkItem(QString::number(z.id_zone), Qt::AlignCenter));
    zoneTable->setItem(row, 1, mkItem(z.nom));
    zoneTable->setItem(row, 2, mkItem(z.adresse));
    zoneTable->setItem(row, 3, mkItem(QString::number(z.superficie,'f',2)+" m²", Qt::AlignCenter));
    zoneTable->setItem(row, 4, mkItem(z.typeZone, Qt::AlignCenter));

    // ── Boutons opérations ────────────────────────────────────────────────────
    QWidget *btnWidget = new QWidget();
    btnWidget->setStyleSheet("background-color: transparent;");
    QHBoxLayout *btnLayout = new QHBoxLayout(btnWidget);
    btnLayout->setContentsMargins(0,0,0,0); btnLayout->setSpacing(10);
    btnLayout->setAlignment(Qt::AlignCenter);

    QSize iconSize(35,35);

    QPushButton *btnUpdate = new QPushButton();
    QPixmap upPx(":/images/update.png");
    btnUpdate->setIcon(QIcon(upPx.scaled(iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    btnUpdate->setIconSize(iconSize); btnUpdate->setFixedSize(iconSize); btnUpdate->setFlat(true);
    btnUpdate->setStyleSheet("QPushButton { background:transparent; border:none; }");
    btnUpdate->setCursor(Qt::PointingHandCursor); btnUpdate->setToolTip("Modifier");

    QPushButton *btnDelete = new QPushButton();
    QPixmap delPx(":/images/delete.png");
    btnDelete->setIcon(QIcon(delPx.scaled(iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    btnDelete->setIconSize(iconSize); btnDelete->setFixedSize(iconSize); btnDelete->setFlat(true);
    btnDelete->setStyleSheet("QPushButton { background:transparent; border:none; }");
    btnDelete->setCursor(Qt::PointingHandCursor); btnDelete->setToolTip("Supprimer");

    connect(btnUpdate, &QPushButton::clicked, [this, z]() {
        remplirFormulaire(z); currentEditId = z.id_zone;
        formTitle->setText("Modifier la Zone");
        btnConfirmAdd->setVisible(false); btnConfirmUpdate->setVisible(true);
        pagesStack->setCurrentWidget(pageForm);
        btnListZones->setStyleSheet(NAV_INACTIVE); btnAddZone->setStyleSheet(NAV_ACTIVE);
        btnStatistics->setStyleSheet(NAV_INACTIVE); btnMap->setStyleSheet(NAV_INACTIVE);
    });

    connect(btnDelete, &QPushButton::clicked, [this, z]() {
        QMessageBox::StandardButton rep = QMessageBox::question(
            this, "Confirmation",
            QString("Supprimer la zone \"%1\" (ID: %2) ?").arg(z.nom).arg(z.id_zone),
            QMessageBox::Yes | QMessageBox::No);
        if (rep != QMessageBox::Yes) return;

        QSqlQuery q(QSqlDatabase::database());
        q.prepare("DELETE FROM EYA.ZONE WHERE ID_ZONE = :id");
        q.bindValue(":id", z.id_zone);
        if (q.exec())
        { QMessageBox::information(this,"Succès","Zone supprimée !"); rafraichirTable(); }
        else
            QMessageBox::critical(this,"Erreur BD","Suppression impossible :\n"+q.lastError().text());
    });

    btnLayout->addWidget(btnUpdate); btnLayout->addWidget(btnDelete);
    zoneTable->setCellWidget(row, 5, btnWidget);
}

// =============================================================================
// CRUD
// =============================================================================
int ZonePages::prochainIdZone()
{
    QSqlQuery q(QSqlDatabase::database());
    q.prepare("SELECT NVL(MAX(ID_ZONE),0)+1 FROM EYA.ZONE");
    if (q.exec() && q.next()) return q.value(0).toInt();
    return 1;
}

bool ZonePages::validerFormulaire()
{
    if (inputNom->text().trimmed().isEmpty()) {
        QMessageBox::warning(this,"Champ obligatoire","Le nom est obligatoire !");
        inputNom->setFocus(); return false;
    }
    if (inputNom->text().length() > 100) {
        QMessageBox::warning(this,"Trop long","Le nom ne peut pas dépasser 100 caractères.");
        inputNom->setFocus(); return false;
    }
    if (inputAdresse->text().trimmed().isEmpty()) {
        QMessageBox::warning(this,"Champ obligatoire","L'adresse est obligatoire !");
        inputAdresse->setFocus(); return false;
    }
    if (inputAdresse->text().length() > 255) {
        QMessageBox::warning(this,"Trop long","L'adresse ne peut pas dépasser 255 caractères.");
        inputAdresse->setFocus(); return false;
    }
    if (inputSuperficie->value() <= 0) {
        QMessageBox::warning(this,"Valeur invalide","La superficie doit être > 0.");
        inputSuperficie->setFocus(); return false;
    }
    return true;
}

void ZonePages::ajouterZone()
{
    if (!validerFormulaire()) return;
    QSqlQuery q(QSqlDatabase::database());
    q.prepare("INSERT INTO EYA.ZONE (ID_ZONE,NOM,ADRESSE,SUPERFICIE,TYPEZONE) "
              "VALUES (:id,:nom,:adresse,:superficie,:typezone)");
    q.bindValue(":id",         prochainIdZone());
    q.bindValue(":nom",        inputNom->text().trimmed());
    q.bindValue(":adresse",    inputAdresse->text().trimmed());
    q.bindValue(":superficie", inputSuperficie->value());
    q.bindValue(":typezone",   inputTypeZone->currentText());

    if (q.exec())
    { QMessageBox::information(this,"Succès","Zone ajoutée avec succès !"); showListPage(); }
    else
        QMessageBox::critical(this,"Erreur BD","Insertion impossible :\n"+q.lastError().text());
}

void ZonePages::modifierZone()
{
    if (!validerFormulaire() || currentEditId < 0) return;
    QSqlQuery q(QSqlDatabase::database());
    q.prepare("UPDATE EYA.ZONE SET NOM=:nom, ADRESSE=:adresse, "
              "SUPERFICIE=:superficie, TYPEZONE=:typezone WHERE ID_ZONE=:id");
    q.bindValue(":nom",        inputNom->text().trimmed());
    q.bindValue(":adresse",    inputAdresse->text().trimmed());
    q.bindValue(":superficie", inputSuperficie->value());
    q.bindValue(":typezone",   inputTypeZone->currentText());
    q.bindValue(":id",         currentEditId);

    if (q.exec())
    { QMessageBox::information(this,"Succès","Zone modifiée avec succès !"); showListPage(); }
    else
        QMessageBox::critical(this,"Erreur BD","Modification impossible :\n"+q.lastError().text());
}

void ZonePages::supprimerZone()
{
    int row = zoneTable->currentRow();
    if (row < 0) { QMessageBox::warning(this,"Erreur","Sélectionnez une zone."); return; }
    int id = zoneTable->item(row,0)->text().toInt();

    if (QMessageBox::question(this,"Confirmation","Supprimer cette zone ?",
                              QMessageBox::Yes|QMessageBox::No) != QMessageBox::Yes) return;

    QSqlQuery q(QSqlDatabase::database());
    q.prepare("DELETE FROM EYA.ZONE WHERE ID_ZONE=:id");
    q.bindValue(":id", id);
    if (q.exec())
    { QMessageBox::information(this,"Succès","Zone supprimée !"); rafraichirTable(); }
    else
        QMessageBox::critical(this,"Erreur BD","Suppression impossible :\n"+q.lastError().text());
}

void ZonePages::viderFormulaire()
{
    inputNom->clear(); inputAdresse->clear();
    inputSuperficie->setValue(1000.0); inputTypeZone->setCurrentIndex(0);
}

void ZonePages::remplirFormulaire(const Zone &z)
{
    inputNom->setText(z.nom); inputAdresse->setText(z.adresse);
    inputSuperficie->setValue(z.superficie); inputTypeZone->setCurrentText(z.typeZone);
}

// =============================================================================
// ██████████████  EXPORT PDF PROFESSIONNEL  ██████████████
// Mise en page : logo titre + date + tableau complet avec alternance de couleurs
// =============================================================================
void ZonePages::dessinerEntetePDF(QPainter &p, int &y, double sX, double sY)
{
    // Bande de titre olive
    p.setBrush(QBrush(QColor("#8e944e")));
    p.setPen(Qt::NoPen);
    p.drawRect(int(40*sX), int(30*sY), int(780*sX), int(45*sY));

    p.setPen(QPen(Qt::white));
    p.setFont(QFont("Arial", int(14*sY), QFont::Bold));
    p.drawText(int(50*sX), int(60*sY), "Liste des Zones — EYA.ZONE");

    // Date d'export
    p.setFont(QFont("Arial", int(7*sY)));
    p.setPen(QPen(Qt::white));
    p.drawText(int(640*sX), int(60*sY),
               "Exporté le " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm"));

    y = int(90*sY);

    // En-têtes colonnes
    QColor hdrColor(109, 115, 57);
    QList<QPair<int,QString>> cols = {
        {35,"ID"}, {120,"Nom"}, {250,"Adresse"}, {120,"Superficie (m²)"}, {120,"Type"}
    };
    int x = int(40*sX);
    for (auto &col : cols) {
        int w = int(col.first * sX);
        p.setBrush(QBrush(hdrColor));
        p.setPen(Qt::NoPen);
        p.drawRect(x, y, w, int(20*sY));
        p.setPen(QPen(Qt::white));
        p.setFont(QFont("Arial", int(7*sY), QFont::Bold));
        p.drawText(x+4, y + int(14*sY), col.second);
        x += w + int(2*sX);
    }
    y += int(24*sY);
}

void ZonePages::dessinerLignePDF(QPainter &p, int &y, const Zone &z,
                                 double sX, double sY, bool grise)
{
    QColor bg = grise ? QColor("#F7F8FA") : Qt::white;
    QList<QPair<int,QString>> cols = {
        {35, QString::number(z.id_zone)},
        {120, z.nom.left(18)},
        {250, z.adresse.left(38)},
        {120, QString::number(z.superficie,'f',2)+" m²"},
        {120, z.typeZone}
    };
    int x = int(40*sX);
    for (auto &col : cols) {
        int w = int(col.first * sX);
        p.setBrush(QBrush(bg));
        p.setPen(QPen(QColor("#E0E0E0")));
        p.drawRect(x, y, w, int(18*sY));
        p.setPen(QPen(QColor("#2C3E50")));
        p.setFont(QFont("Arial", int(6.5*sY)));
        p.drawText(x+4, y + int(13*sY), col.second);
        x += w + int(2*sX);
    }
    y += int(20*sY);
}

void ZonePages::exporterPDF()
{
    // Récupérer les données actuellement affichées (résultat recherche/filtre)
    QList<Zone> liste;
    for (int row = 0; row < zoneTable->rowCount(); row++) {
        Zone z;
        z.id_zone    = zoneTable->item(row,0)->text().toInt();
        z.nom        = zoneTable->item(row,1)->text();
        z.adresse    = zoneTable->item(row,2)->text();
        z.superficie = zoneTable->item(row,3)->text().remove(" m²").toDouble();
        z.typeZone   = zoneTable->item(row,4)->text();
        liste << z;
    }

    if (liste.isEmpty()) {
        QMessageBox::information(this,"Info","Aucune zone à exporter.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this, "Exporter en PDF", "zones_" +
            QDateTime::currentDateTime().toString("yyyyMMdd_HHmm"),
        "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setPageSize(QPageSize::A4);

    QPainter p;
    if (!p.begin(&printer)) {
        QMessageBox::warning(this,"Erreur","Impossible de créer le PDF.");
        return;
    }

    QRectF pageRect = printer.pageRect(QPrinter::DevicePixel);
    double sX = pageRect.width()  / 860.0;
    double sY = pageRect.height() / 600.0;

    int y = 0;
    dessinerEntetePDF(p, y, sX, sY);

    bool grise = false;
    for (const Zone &z : liste) {
        // Nouvelle page si nécessaire
        if (y > int(pageRect.height() - 40*sY)) {
            printer.newPage();
            y = int(10*sY);
            dessinerEntetePDF(p, y, sX, sY);
        }
        dessinerLignePDF(p, y, z, sX, sY, grise);
        grise = !grise;
    }

    // Pied de page
    y += int(8*sY);
    p.setPen(QPen(QColor("#8e944e")));
    p.setFont(QFont("Arial", int(6*sY)));
    p.drawText(int(40*sX), y,
               QString("Total : %1 zone(s)   |   Généré automatiquement par le système EYA")
                   .arg(liste.size()));

    p.end();
    QMessageBox::information(this,"Succès",
                             QString("PDF exporté avec succès !\n%1 zone(s) dans le fichier.").arg(liste.size()));
}

// =============================================================================
// ██████████████  EXPORT CSV  ██████████████
// =============================================================================
void ZonePages::exporterCSV()
{
    if (zoneTable->rowCount() == 0) {
        QMessageBox::information(this,"Info","Aucune zone à exporter."); return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this, "Exporter en CSV",
        "zones_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmm"),
        "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this,"Erreur","Impossible de créer le fichier CSV."); return;
    }

    QTextStream out(&file);
    // BOM UTF-8 pour Excel
    out << "\xEF\xBB\xBF";
    out << "ID_ZONE,NOM,ADRESSE,SUPERFICIE,TYPEZONE\n";

    for (int row = 0; row < zoneTable->rowCount(); row++) {
        // Échapper les virgules dans les champs texte
        auto esc = [](const QString &s) {
            return QString("\"%1\"").arg(QString(s).replace("\"","\"\""));
        };
        out << zoneTable->item(row,0)->text() << ","
            << esc(zoneTable->item(row,1)->text()) << ","
            << esc(zoneTable->item(row,2)->text()) << ","
            << zoneTable->item(row,3)->text().remove(" m²") << ","
            << esc(zoneTable->item(row,4)->text()) << "\n";
    }

    file.close();
    QMessageBox::information(this,"Succès",
                             QString("CSV exporté avec succès !\n%1 ligne(s) dans le fichier.")
                                 .arg(zoneTable->rowCount()));
}

// =============================================================================
// GRAPHIQUES — données Oracle en direct
// =============================================================================
void ZonePages::setupCharts()
{
    if (!statsLeftContainer || !statsRightContainer) return;

    for (QWidget *c : {statsLeftContainer, statsRightContainer}) {
        QLayout *l = c->layout();
        if (l) { QLayoutItem *item;
            while ((item=l->takeAt(0))) { delete item->widget(); delete item; }
            delete l; }
    }

    QMap<QString,int>    compteur;
    QMap<QString,double> totalSup;

    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery q(db);
        q.prepare("SELECT TYPEZONE, COUNT(*) NB, SUM(SUPERFICIE) TOTAL "
                  "FROM EYA.ZONE GROUP BY TYPEZONE ORDER BY TYPEZONE");
        if (q.exec()) {
            while (q.next()) {
                QString t = q.value("TYPEZONE").toString();
                compteur[t] = q.value("NB").toInt();
                totalSup[t] = q.value("TOTAL").toDouble();
            }
        }
    }

    // ── Camembert ────────────────────────────────────────────────────────────
    QVBoxLayout *leftL = new QVBoxLayout(statsLeftContainer);
    leftL->setContentsMargins(20,20,20,20);
    QLabel *pieTitle = new QLabel("Distribution des Zones par Type");
    pieTitle->setStyleSheet("font-size:13pt;font-weight:bold;color:#2C3E50;background:transparent;");
    pieTitle->setAlignment(Qt::AlignCenter);
    leftL->addWidget(pieTitle);

    QPieSeries *ps = new QPieSeries();
    for (auto it=compteur.begin(); it!=compteur.end(); ++it)
        ps->append(it.key(), it.value());

    QList<QColor> cols={QColor("#8e944e"),QColor("#6d7339"),QColor("#05668D"),
                          QColor("#02C39A"),QColor("#F77F00"),QColor("#06AED5")};
    for (int i=0; i<ps->slices().count(); i++) {
        QPieSlice *sl=ps->slices().at(i);
        sl->setColor(cols[i%cols.size()]); sl->setLabelVisible(true);
        sl->setLabel(sl->label()+QString(" (%1%)").arg(100*sl->percentage(),0,'f',1));
        if (sl->percentage()>0.20) { sl->setExploded(true); sl->setExplodeDistanceFactor(0.1); }
    }
    QChart *pieC=new QChart(); pieC->addSeries(ps);
    pieC->legend()->setAlignment(Qt::AlignBottom);
    pieC->setAnimationOptions(QChart::SeriesAnimations);
    QChartView *pieV=new QChartView(pieC);
    pieV->setRenderHint(QPainter::Antialiasing); pieV->setMinimumHeight(400);
    leftL->addWidget(pieV);

    // ── Barres ───────────────────────────────────────────────────────────────
    QVBoxLayout *rightL = new QVBoxLayout(statsRightContainer);
    rightL->setContentsMargins(20,20,20,20);
    QLabel *barTitle=new QLabel("Superficie totale par Type (×100 m²)");
    barTitle->setStyleSheet("font-size:13pt;font-weight:bold;color:#2C3E50;background:transparent;");
    barTitle->setAlignment(Qt::AlignCenter);
    rightL->addWidget(barTitle);

    QBarSet *supSet=new QBarSet("Superficie (×100 m²)"); supSet->setColor(QColor("#8e944e"));
    QStringList cats;
    for (auto it=totalSup.begin(); it!=totalSup.end(); ++it)
    { cats<<it.key(); *supSet<<(it.value()/100.0); }

    QBarSeries *barS=new QBarSeries(); barS->append(supSet);
    QChart *barC=new QChart(); barC->addSeries(barS);
    barC->setAnimationOptions(QChart::SeriesAnimations);
    QBarCategoryAxis *axX=new QBarCategoryAxis(); axX->append(cats);
    barC->addAxis(axX,Qt::AlignBottom); barS->attachAxis(axX);
    QValueAxis *axY=new QValueAxis(); axY->setTitleText("×100 m²");
    barC->addAxis(axY,Qt::AlignLeft); barS->attachAxis(axY);
    barC->legend()->setAlignment(Qt::AlignTop);
    QChartView *barV=new QChartView(barC);
    barV->setRenderHint(QPainter::Antialiasing); barV->setMinimumHeight(400);
    rightL->addWidget(barV);
}
