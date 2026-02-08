#ifndef GESTIONPOUBELLEPAGES_H
#define GESTIONPOUBELLEPAGES_H

#include <QWidget>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui {
class GestionPoubellePage;
}
QT_END_NAMESPACE

struct Poubelle {
    int id;
    QString type_dechet;
    QString etat;
    int taux_remplissage;
    QString localisation;
    QString date_installation;
    QString derniere_collecte;
    bool endommagee;
    QString notes;
};

class GestionPoubellePage : public QWidget
{
    Q_OBJECT

public:
    explicit GestionPoubellePage(QWidget *parent = nullptr);
    ~GestionPoubellePage();

    void showListPage();
    void showFormPage();
    void showStatsPage();
    void showHistoriquePage();

private slots:
    void ajouterPoubelle();
    void modifierPoubelle();
    void supprimerPoubelle();
    void rechercherPoubelle();
    void trierParEtat();
    void trierParType();
    void exporterPDF();
    void exporterCSV();
    void afficherNotification();
    void chargerHistorique();
    void uploadImage();

private:
    Ui::GestionPoubellePage *ui;
    QMap<int, Poubelle> poubelles;
    int nextId;

    void setupPoubelleTable();
    void setupCharts();
    void rafraichirTable();
    void ajouterLigneTable(const Poubelle &p, int row);
    void viderFormulaire();
    void remplirFormulaire(const Poubelle &p);
    void verifierEtatPoubelle(const Poubelle &p);
    void sauvegarderHistorique(const QString &action, const Poubelle &p);
};

#endif // GESTIONPOUBELLEPAGES_H
