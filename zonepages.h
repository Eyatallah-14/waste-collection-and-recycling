#ifndef ZONEPAGES_H
#define ZONEPAGES_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

// ── Miroir exact de la table EYA.ZONE ────────────────────────────────────────
struct Zone {
    int     id_zone;       // ID_ZONE    NUMBER        PK NOT NULL
    QString nom;           // NOM        VARCHAR2(100)    NOT NULL
    QString adresse;       // ADRESSE    VARCHAR2(255)    NOT NULL
    double  superficie;    // SUPERFICIE NUMBER(10,2)     NOT NULL
    QString typeZone;      // TYPEZONE   VARCHAR2(100)    NOT NULL
};

class ZonePages : public QWidget
{
    Q_OBJECT

public:
    explicit ZonePages(QWidget *parent = nullptr);
    ~ZonePages();

private slots:
    // Navigation
    void showListPage();
    void showFormPage();
    void showStatsPage();
    void showMapPage();

    // CRUD Oracle
    void ajouterZone();
    void modifierZone();
    void supprimerZone();

    // Métiers avancés
    void rechercherZone();          // Recherche Oracle LIKE multi-champs
    void filtrerParType();          // Filtre combo → SELECT WHERE TYPEZONE=
    void trierColonne(int col);     // Tri ASC/DESC sur n'importe quelle colonne
    void trierParNom();             // Tri rapide par NOM
    void trierParType();            // Tri rapide par TYPEZONE
    void exporterPDF();             // PDF mis en page avec tableau complet
    void exporterCSV();             // CSV avec toutes les colonnes

private:
    // ── Navigation ──────────────────────────────────────────────────────────
    QPushButton  *btnListZones;
    QPushButton  *btnAddZone;
    QPushButton  *btnStatistics;
    QPushButton  *btnMap;

    // ── Pages ───────────────────────────────────────────────────────────────
    QStackedWidget *pagesStack;
    QWidget        *pageList;
    QWidget        *pageForm;
    QWidget        *pageStats;
    QWidget        *pageMap;

    // ── Liste ───────────────────────────────────────────────────────────────
    QLineEdit    *searchBox;
    QPushButton  *btnSearch;
    QComboBox    *sortCombo;         // filtre par type
    QPushButton  *btnTriNom;
    QPushButton  *btnTriType;
    QPushButton  *btnExportPdf;
    QPushButton  *btnExportCsv;
    QTableWidget *zoneTable;
    QLabel       *lblResultCount;   // "X zone(s) trouvée(s)"

    // ── Formulaire ──────────────────────────────────────────────────────────
    QLabel         *formTitle;
    QLineEdit      *inputNom;
    QLineEdit      *inputAdresse;
    QDoubleSpinBox *inputSuperficie;
    QComboBox      *inputTypeZone;
    QPushButton    *btnConfirmAdd;
    QPushButton    *btnConfirmUpdate;

    // ── Stats ───────────────────────────────────────────────────────────────
    QWidget *statsLeftContainer;
    QWidget *statsRightContainer;

    // ── Map ─────────────────────────────────────────────────────────────────
    QLabel *mapPlaceholder;

    // ── État interne ────────────────────────────────────────────────────────
    int  currentEditId;
    int  sortColumn;        // colonne de tri courante
    bool sortAscending;     // direction du tri courante

    // ── Méthodes privées ────────────────────────────────────────────────────
    void setupZoneTable();
    void setupCharts();
    void chargerTable(const QList<Zone> &liste);
    void rafraichirTable();
    void ajouterLigneTable(const Zone &z, int row);
    void viderFormulaire();
    void remplirFormulaire(const Zone &z);
    bool validerFormulaire();
    int  prochainIdZone();

    // Helpers PDF
    void dessinerEntetePDF(QPainter &p, int &y, double scaleX, double scaleY);
    void dessinerLignePDF(QPainter &p, int &y, const Zone &z, double scaleX, double scaleY, bool grise);
};

#endif // ZONEPAGES_H
