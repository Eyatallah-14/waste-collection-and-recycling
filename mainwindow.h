#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QPushButton>
#include <QIcon>
#include <QPixmap>
#include <QList>
#include <QCalendarWidget>
#include <QTimeEdit>

class EmployePages;  // Forward declaration
class ZonePages;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

//==============================================================================
// VEHICULE CLASS - Représente un véhicule
//==============================================================================
class Vehicule
{
public:
    Vehicule(int id = 0, const QString& type = "", float capaciteMax = 0.0f,
             const QString& etat = "disponible", const QString& carburant = "")
        : m_id(id), m_type(type), m_capaciteMax(capaciteMax),
          m_etat(etat), m_carburant(carburant) {}

    // Getters
    int id() const { return m_id; }
    QString type() const { return m_type; }
    float capaciteMax() const { return m_capaciteMax; }
    QString etat() const { return m_etat; }
    QString carburant() const { return m_carburant; }

    // Setters
    void setId(int id) { m_id = id; }
    void setType(const QString& type) { m_type = type; }
    void setCapaciteMax(float capacite) { m_capaciteMax = capacite; }
    void setEtat(const QString& etat) { m_etat = etat; }
    void setCarburant(const QString& carburant) { m_carburant = carburant; }

private:
    int m_id;
    QString m_type;
    float m_capaciteMax;
    QString m_etat;
    QString m_carburant;
};

//==============================================================================
// MISSION CLASS
//==============================================================================
class Mission
{
public:
    Mission(int id = 0, const QString& date = "", const QString& heureDebut = "",
            const QString& heureFin = "", const QString& statutZone = "", const QString& listeEmployes = "")
        : m_id(id), m_date(date), m_heureDebut(heureDebut),
          m_heureFin(heureFin), m_statutZone(statutZone), m_listeEmployes(listeEmployes) {}

    int id() const { return m_id; }
    QString date() const { return m_date; }
    QString heureDebut() const { return m_heureDebut; }
    QString heureFin() const { return m_heureFin; }
    QString statutZone() const { return m_statutZone; }
    QString listeEmployes() const { return m_listeEmployes; }

    void setDate(const QString& date) { m_date = date; }
    void setHeureDebut(const QString& heureDebut) { m_heureDebut = heureDebut; }
    void setHeureFin(const QString& heureFin) { m_heureFin = heureFin; }
    void setStatutZone(const QString& statutZone) { m_statutZone = statutZone; }
    void setListeEmployes(const QString& listeEmployes) { m_listeEmployes = listeEmployes; }

private:
    int m_id;
    QString m_date;
    QString m_heureDebut;
    QString m_heureFin;
    QString m_statutZone;
    QString m_listeEmployes;
};

//==============================================================================
// IMAGE BUTTON HOVER FILTER CLASS
//==============================================================================
class ImageButtonHoverFilter : public QObject
{
    Q_OBJECT
public:
    ImageButtonHoverFilter(QPushButton *button, const QString &normalIcon,
                           const QString &hoverIcon, const QString &clickedIcon,
                           QSize iconSize)
        : QObject(button), btn(button), normalIconPath(normalIcon),
          hoverIconPath(hoverIcon), clickedIconPath(clickedIcon), size(iconSize)
    {
        btn->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (obj == btn) {
            if (event->type() == QEvent::MouseButtonPress) {
                QPixmap clickedPixmap(clickedIconPath);
                clickedPixmap = clickedPixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                btn->setIcon(QIcon(clickedPixmap));
                btn->setIconSize(size);
                return false;
            } else if (event->type() == QEvent::MouseButtonRelease) {
                QPixmap hoverPixmap(hoverIconPath);
                hoverPixmap = hoverPixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                btn->setIcon(QIcon(hoverPixmap));
                btn->setIconSize(size);
                return false;
            } else if (event->type() == QEvent::Enter) {
                QPixmap hoverPixmap(hoverIconPath);
                hoverPixmap = hoverPixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                btn->setIcon(QIcon(hoverPixmap));
                btn->setIconSize(size);
                return true;
            } else if (event->type() == QEvent::Leave) {
                QPixmap normalPixmap(normalIconPath);
                normalPixmap = normalPixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                btn->setIcon(QIcon(normalPixmap));
                btn->setIconSize(size);
                return true;
            }
        }
        return QObject::eventFilter(obj, event);
    }

private:
    QPushButton *btn;
    QString normalIconPath;
    QString hoverIconPath;
    QString clickedIconPath;
    QSize size;
};

//==============================================================================
// MAIN WINDOW CLASS
//==============================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    // Navigation slots
    void on_pushButton_clicked();      // Sidebar toggle animation
    void on_pushButton_5_clicked();    // Zone navigation
    void on_pushButton_6_clicked();    // Poubelle navigation
    void on_pushButton_7_clicked();    // Employe navigation
    void on_pushButton_8_clicked();    // Missions navigation
    void on_pushButton_9_clicked();    // Vehicule navigation

    // Vehicule page actions
    void onAddVehiculeClicked();
    void onUpdateVehiculeClicked();
    void onDeleteVehiculeClicked();
    void onSendEmailClicked();

    // Vehicule page buttons
    void onSearchClicked();
    void onSortClicked();
    void onStatsClicked();
    void onExportPDFClicked();
    void onChatbotClicked();

    // Form actions
    void onSaveVehiculeForm();
    void onCancelForm();
    void onApplySearch();
    void onApplySort();
    void onBackToVehiculeList();

    // Missions page actions
    void onAddMissionClicked();
    void onUpdateMissionClicked();
    void onDeleteMissionClicked();
    void onSaveMissionForm();
    void onCancelMissionForm();
    void onCloseMissionForm();

private:
    Ui::MainWindow *ui;
    EmployePages *employePages;
    ZonePages *zonePages;

    // Vehicule related
    void addVehiculeRowWithButtons(int row, const Vehicule& vehicule);
    void addVehiculeRowToSearchTable(int row, const Vehicule& vehicule);
    void addVehiculeRowToSortTable(int row, const Vehicule& vehicule);
    void loadVehicules();
    void refreshVehiculeTable();
    void refreshSearchTable();
    void refreshSortTable();
    void setupVehiculeTableHeaders();
    void setupSearchTableHeaders();
    void setupSortTableHeaders();
    void searchVehicules(const QString& searchText);
    void sortVehicules(const QString& criteria);
    void showVehiculeStats();
    void exportVehiculesToPDF();

    // Missions related
    void addMissionRowWithButtons(int row, const Mission& mission);
    void loadMissions();
    void refreshMissionsTable();
    void setupMissionsTableHeaders();

    QPixmap originalLogoPixmap;

    // Page management
    enum PageType {
        PAGE_MISSIONS,
        PAGE_ZONES,
        PAGE_POUBELLE,
        PAGE_EMPLOYE,
        PAGE_VEHICULE,
        PAGE_ADD_VEHICULE,
        PAGE_SEARCH,
        PAGE_SORT,
        PAGE_STATS,
        PAGE_CHATBOT,
        PAGE_ADD_MISSION
    };

    PageType currentPage;

    // Vehicules data
    QList<Vehicule> vehicules;
    QList<Vehicule> allVehicules;  // Copie de sauvegarde pour restauration
    int nextVehiculeId;
    int editingVehiculeId;  // Pour savoir quel véhicule on modifie

    // Missions data
    QList<Mission> missions;
    int nextMissionId;
    int editingMissionId;  // Pour savoir quelle mission on modifie

    // Page management functions
    void clearAllPages();
    void showMissionsPage();
    void showZonesPage();
    void showPoubellePage();
    void showEmployePage();
    void showVehiculePage();
    void showAddVehiculePage();
    void showSearchPage();
    void showSortPage();
    void showStatsPage();
    void showChatbotPage();
    void showAddMissionPage();

    // Chart related
    void drawStatsChart();
};

#endif // MAINWINDOW_H
