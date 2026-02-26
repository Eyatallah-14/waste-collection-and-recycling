#ifndef ZONE_H
#define ZONE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Zone
{
private:
    int id_zone;
    QString nom;
    QString adresse;
    double superficie;
    QString typeZone;

public:
    // Constructeurs
    Zone();
    Zone(int id, QString nom, QString adresse, double superficie, QString typeZone);

    // Getters
    int getId() const { return id_zone; }
    QString getNom() const { return nom; }
    QString getAdresse() const { return adresse; }
    double getSuperficie() const { return superficie; }
    QString getTypeZone() const { return typeZone; }

    // Setters
    void setId(int id) { this->id_zone = id; }
    void setNom(QString n) { this->nom = n; }
    void setAdresse(QString a) { this->adresse = a; }
    void setSuperficie(double s) { this->superficie = s; }
    void setTypeZone(QString t) { this->typeZone = t; }

    // Méthodes CRUD (requêtes dans la classe modèle — règle de l'atelier)
    bool ajouter();
    bool supprimer(int id);
    bool modifier();
    QSqlQueryModel* afficher();

    // Recherche et tri
    QSqlQueryModel* chercher(QString motCle);
    QSqlQueryModel* afficherTriee(QString colonne);  // "NOM", "SUPERFICIE", "TYPEZONE"
};

#endif // ZONE_H
