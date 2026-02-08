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
#include <QFrame>
#include <QDialog>
#include <QSpinBox>
#include <QMessageBox>

namespace Ui {
class ZonePages;
}

// Classe ZoneDialog intégrée
class ZoneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZoneDialog(QWidget *parent = nullptr, int zoneId = -1);
    ~ZoneDialog();

    QString getNom() const { return nomEdit->text(); }
    QString getAdresse() const { return adresseEdit->text(); }
    int getSuperficie() const { return superficieSpinBox->value(); }
    int getNombrePoubelles() const { return poubellesSpinBox->value(); }

    void setNom(const QString &nom) { nomEdit->setText(nom); }
    void setAdresse(const QString &adresse) { adresseEdit->setText(adresse); }
    void setSuperficie(int superficie) { superficieSpinBox->setValue(superficie); }
    void setNombrePoubelles(int nombre) { poubellesSpinBox->setValue(nombre); }

private slots:
    void onSaveClicked();
    void onCancelClicked();

private:
    void setupUI();
    void applyStyles();

    int m_zoneId;
    QLineEdit *nomEdit;
    QLineEdit *adresseEdit;
    QSpinBox *superficieSpinBox;
    QSpinBox *poubellesSpinBox;
    QPushButton *saveButton;
    QPushButton *cancelButton;
};

class ZonePages : public QWidget
{
    Q_OBJECT

public:
    explicit ZonePages(QWidget *parent = nullptr);
    ~ZonePages();

private slots:
    // Slots pour les actions de zone
    void onAddZoneClicked();
    void onExportPDFClicked();
    void onExportExcelClicked();
    void onSearchTextChanged(const QString &text);
    void onEditZoneClicked(int row);
    void onDeleteZoneClicked(int row);
    void onViewZoneDetails(int row);
    void onOpenMapsClicked(int row);

private:
    // Widgets
    QTableWidget *zoneTable;
    QLineEdit *searchBox;
    QPushButton *addZoneBtn;
    QPushButton *exportPDFBtn;
    QPushButton *exportExcelBtn;
    QLabel *totalZonesLabel;
    QLabel *totalSurfaceLabel;
    QLabel *totalPoubelleslabel;

    // Fonctions d'initialisation
    void setupUI();
    void setupTable();
    void loadZoneData();
    void applyStyles();
    void updateStatistics();

    // Fonctions utilitaires
    void showZoneDialog(int zoneId = -1);
    void addNewZone(const QString &nom, const QString &adresse, int superficie, int poubelles);
    void updateZone(int zoneId, const QString &nom, const QString &adresse, int superficie, int poubelles);
};

#endif // ZONEPAGES_H
