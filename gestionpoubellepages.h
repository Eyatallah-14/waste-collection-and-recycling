#ifndef GESTIONPOUBELLEPAGES_H
#define GESTIONPOUBELLEPAGES_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QList>
#include <QStringList>
#include "poubelle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GestionPoubellePage; }
QT_END_NAMESPACE

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
    void trierPoubelles();
    void exporterPDF();
    void afficherNotification();
    void chargerHistorique();

private:
    Ui::GestionPoubellePage *ui;
    Poubelle Ptmp;
    int currentEditId = -1;
    QList<QStringList> historique;

    void setupPoubelleTable();
    void setupCharts();
    void rafraichirTable();
    void remplirTableDepuisModel(QSqlQueryModel *model);
    void viderFormulaire();
    void sauvegarderHistorique(const QString &action, int id,
                                const QString &type, const QString &zone);
};

#endif // GESTIONPOUBELLEPAGES_H
