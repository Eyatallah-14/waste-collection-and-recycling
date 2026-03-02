#include "poubelle.h"

bool Poubelle::ajouter()
{
    QSqlQuery q;
    q.prepare(
        "INSERT INTO POUBELLE "
        "(ID_POUBELLE, TYPEDECHET, CAPACITEMAX, ETAT, TAUXREMPLISSAGE, DATEINSTALLATION, ID_ZONE) "
        "VALUES (:id, :type, :cap, :etat, :taux, TO_DATE(:date,'YYYY-MM-DD'), :zone)"
    );
    q.bindValue(":id",   id_poubelle);
    q.bindValue(":type", typeDechet);
    q.bindValue(":cap",  capaciteMax);
    q.bindValue(":etat", etat);
    q.bindValue(":taux", tauxRemplissage);
    q.bindValue(":date", dateInstallation.toString("yyyy-MM-dd"));
    q.bindValue(":zone", id_zone);
    return q.exec();
}

bool Poubelle::modifier()
{
    QSqlQuery q;
    q.prepare(
        "UPDATE POUBELLE SET "
        "  TYPEDECHET=:type, CAPACITEMAX=:cap, ETAT=:etat, "
        "  TAUXREMPLISSAGE=:taux, DATEINSTALLATION=TO_DATE(:date,'YYYY-MM-DD'), ID_ZONE=:zone "
        "WHERE ID_POUBELLE=:id"
    );
    q.bindValue(":type", typeDechet);
    q.bindValue(":cap",  capaciteMax);
    q.bindValue(":etat", etat);
    q.bindValue(":taux", tauxRemplissage);
    q.bindValue(":date", dateInstallation.toString("yyyy-MM-dd"));
    q.bindValue(":zone", id_zone);
    q.bindValue(":id",   id_poubelle);
    return q.exec();
}

bool Poubelle::supprimer(int id)
{
    QSqlQuery q;
    q.prepare("DELETE FROM POUBELLE WHERE ID_POUBELLE=:id");
    q.bindValue(":id", id);
    return q.exec();
}

QSqlQueryModel* Poubelle::afficher()
{
    QSqlQueryModel *m = new QSqlQueryModel();
    m->setQuery(
        "SELECT P.ID_POUBELLE, P.TYPEDECHET, P.CAPACITEMAX, P.ETAT, P.TAUXREMPLISSAGE, "
        "TO_CHAR(P.DATEINSTALLATION,'DD/MM/YYYY') AS DATE_INSTALL, Z.NOM AS ZONE "
        "FROM POUBELLE P LEFT JOIN ZONE Z ON P.ID_ZONE=Z.ID_ZONE "
        "ORDER BY P.ID_POUBELLE"
    );
    m->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m->setHeaderData(1, Qt::Horizontal, QObject::tr("Type Déchet"));
    m->setHeaderData(2, Qt::Horizontal, QObject::tr("Capacité Max"));
    m->setHeaderData(3, Qt::Horizontal, QObject::tr("État"));
    m->setHeaderData(4, Qt::Horizontal, QObject::tr("Taux (%)"));
    m->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Install."));
    m->setHeaderData(6, Qt::Horizontal, QObject::tr("Zone"));
    return m;
}

QSqlQueryModel* Poubelle::rechercher(const QString &motCle)
{
    QSqlQueryModel *m = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare(
        "SELECT P.ID_POUBELLE, P.TYPEDECHET, P.CAPACITEMAX, P.ETAT, P.TAUXREMPLISSAGE, "
        "TO_CHAR(P.DATEINSTALLATION,'DD/MM/YYYY') AS DATE_INSTALL, Z.NOM AS ZONE "
        "FROM POUBELLE P LEFT JOIN ZONE Z ON P.ID_ZONE=Z.ID_ZONE "
        "WHERE UPPER(P.TYPEDECHET) LIKE UPPER(:mot) "
        "   OR UPPER(P.ETAT) LIKE UPPER(:mot) "
        "   OR UPPER(Z.NOM) LIKE UPPER(:mot) "
        "   OR TO_CHAR(P.ID_POUBELLE) LIKE :mot "
        "ORDER BY P.ID_POUBELLE"
    );
    q.bindValue(":mot", "%" + motCle + "%");
    q.exec();
    m->setQuery(std::move(q));
    m->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m->setHeaderData(1, Qt::Horizontal, QObject::tr("Type Déchet"));
    m->setHeaderData(2, Qt::Horizontal, QObject::tr("Capacité Max"));
    m->setHeaderData(3, Qt::Horizontal, QObject::tr("État"));
    m->setHeaderData(4, Qt::Horizontal, QObject::tr("Taux (%)"));
    m->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Install."));
    m->setHeaderData(6, Qt::Horizontal, QObject::tr("Zone"));
    return m;
}

QSqlQueryModel* Poubelle::trierParEtat()
{
    QSqlQueryModel *m = new QSqlQueryModel();
    m->setQuery(
        "SELECT P.ID_POUBELLE, P.TYPEDECHET, P.CAPACITEMAX, P.ETAT, P.TAUXREMPLISSAGE, "
        "TO_CHAR(P.DATEINSTALLATION,'DD/MM/YYYY') AS DATE_INSTALL, Z.NOM AS ZONE "
        "FROM POUBELLE P LEFT JOIN ZONE Z ON P.ID_ZONE=Z.ID_ZONE "
        "ORDER BY P.ETAT ASC, P.ID_POUBELLE"
    );
    m->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m->setHeaderData(1, Qt::Horizontal, QObject::tr("Type Déchet"));
    m->setHeaderData(2, Qt::Horizontal, QObject::tr("Capacité Max"));
    m->setHeaderData(3, Qt::Horizontal, QObject::tr("État"));
    m->setHeaderData(4, Qt::Horizontal, QObject::tr("Taux (%)"));
    m->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Install."));
    m->setHeaderData(6, Qt::Horizontal, QObject::tr("Zone"));
    return m;
}

QSqlQueryModel* Poubelle::trierParType()
{
    QSqlQueryModel *m = new QSqlQueryModel();
    m->setQuery(
        "SELECT P.ID_POUBELLE, P.TYPEDECHET, P.CAPACITEMAX, P.ETAT, P.TAUXREMPLISSAGE, "
        "TO_CHAR(P.DATEINSTALLATION,'DD/MM/YYYY') AS DATE_INSTALL, Z.NOM AS ZONE "
        "FROM POUBELLE P LEFT JOIN ZONE Z ON P.ID_ZONE=Z.ID_ZONE "
        "ORDER BY P.TYPEDECHET ASC, P.ID_POUBELLE"
    );
    m->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m->setHeaderData(1, Qt::Horizontal, QObject::tr("Type Déchet"));
    m->setHeaderData(2, Qt::Horizontal, QObject::tr("Capacité Max"));
    m->setHeaderData(3, Qt::Horizontal, QObject::tr("État"));
    m->setHeaderData(4, Qt::Horizontal, QObject::tr("Taux (%)"));
    m->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Install."));
    m->setHeaderData(6, Qt::Horizontal, QObject::tr("Zone"));
    return m;
}

QSqlQueryModel* Poubelle::afficherPleinement()
{
    QSqlQueryModel *m = new QSqlQueryModel();
    m->setQuery(
        "SELECT P.ID_POUBELLE, P.TYPEDECHET, P.CAPACITEMAX, P.ETAT, P.TAUXREMPLISSAGE, "
        "TO_CHAR(P.DATEINSTALLATION,'DD/MM/YYYY') AS DATE_INSTALL, Z.NOM AS ZONE "
        "FROM POUBELLE P LEFT JOIN ZONE Z ON P.ID_ZONE=Z.ID_ZONE "
        "WHERE P.TAUXREMPLISSAGE >= 80 "
        "ORDER BY P.TAUXREMPLISSAGE DESC"
    );
    m->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m->setHeaderData(1, Qt::Horizontal, QObject::tr("Type Déchet"));
    m->setHeaderData(2, Qt::Horizontal, QObject::tr("Capacité Max"));
    m->setHeaderData(3, Qt::Horizontal, QObject::tr("État"));
    m->setHeaderData(4, Qt::Horizontal, QObject::tr("Taux (%)"));
    m->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Install."));
    m->setHeaderData(6, Qt::Horizontal, QObject::tr("Zone"));
    return m;
}

QSqlQueryModel* Poubelle::statistiquesParType()
{
    QSqlQueryModel *m = new QSqlQueryModel();
    m->setQuery(
        "SELECT TYPEDECHET, COUNT(*) AS NB, "
        "ROUND(AVG(TAUXREMPLISSAGE),1) AS TAUX_MOYEN, MAX(TAUXREMPLISSAGE) AS TAUX_MAX "
        "FROM POUBELLE GROUP BY TYPEDECHET ORDER BY NB DESC"
    );
    m->setHeaderData(0, Qt::Horizontal, QObject::tr("Type Déchet"));
    m->setHeaderData(1, Qt::Horizontal, QObject::tr("Nb Poubelles"));
    m->setHeaderData(2, Qt::Horizontal, QObject::tr("Taux Moyen (%)"));
    m->setHeaderData(3, Qt::Horizontal, QObject::tr("Taux Max (%)"));
    return m;
}

QSqlQueryModel* Poubelle::statistiquesParEtat()
{
    QSqlQueryModel *m = new QSqlQueryModel();
    m->setQuery(
        "SELECT ETAT, COUNT(*) AS NB FROM POUBELLE "
        "GROUP BY ETAT ORDER BY NB DESC"
    );
    m->setHeaderData(0, Qt::Horizontal, QObject::tr("État"));
    m->setHeaderData(1, Qt::Horizontal, QObject::tr("Nb Poubelles"));
    return m;
}
