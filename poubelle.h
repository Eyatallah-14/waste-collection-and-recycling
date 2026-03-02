#ifndef POUBELLE_H
#define POUBELLE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

// ============================================================
//  CLASSE MODÈLE : Poubelle  (Architecture Modèle-Vue)
//  Attributs = colonnes Oracle exactes :
//    ID_POUBELLE, TYPEDECHET, CAPACITEMAX, ETAT,
//    TAUXREMPLISSAGE, DATEINSTALLATION, ID_ZONE
// ============================================================
class Poubelle
{
    int     id_poubelle;
    QString typeDechet;
    int     capaciteMax;
    QString etat;
    int     tauxRemplissage;
    QDate   dateInstallation;
    int     id_zone;

public:
    Poubelle() : id_poubelle(0), capaciteMax(0), tauxRemplissage(0), id_zone(0) {}

    Poubelle(int id, const QString &type, int cap, const QString &etat,
             int taux, const QDate &date, int zone)
        : id_poubelle(id), typeDechet(type), capaciteMax(cap),
          etat(etat), tauxRemplissage(taux), dateInstallation(date), id_zone(zone) {}

    // Getters
    int     getId()               const { return id_poubelle;      }
    QString getTypeDechet()       const { return typeDechet;       }
    int     getCapaciteMax()      const { return capaciteMax;      }
    QString getEtat()             const { return etat;             }
    int     getTauxRemplissage()  const { return tauxRemplissage;  }
    QDate   getDateInstallation() const { return dateInstallation; }
    int     getIdZone()           const { return id_zone;          }

    // Setters
    void setId(int v)                        { id_poubelle      = v; }
    void setTypeDechet(const QString &v)     { typeDechet       = v; }
    void setCapaciteMax(int v)               { capaciteMax      = v; }
    void setEtat(const QString &v)           { etat             = v; }
    void setTauxRemplissage(int v)           { tauxRemplissage  = v; }
    void setDateInstallation(const QDate &v) { dateInstallation = v; }
    void setIdZone(int v)                    { id_zone          = v; }

    // CRUD
    bool            ajouter();
    bool            modifier();
    bool            supprimer(int id);
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(const QString &motCle);
    QSqlQueryModel* trierParEtat();
    QSqlQueryModel* trierParType();
    QSqlQueryModel* afficherPleinement();
    QSqlQueryModel* statistiquesParType();
    QSqlQueryModel* statistiquesParEtat();
};

#endif // POUBELLE_H
