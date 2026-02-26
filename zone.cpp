#include "zone.h"
#include <QSqlError>
#include <QDebug>
#include <QObject>

Zone::Zone()
{
    id_zone = 0;
    nom = "";
    adresse = "";
    superficie = 0.0;
    typeZone = "";
}

Zone::Zone(int id, QString nom, QString adresse, double superficie, QString typeZone)
{
    this->id_zone = id;
    this->nom = nom;
    this->adresse = adresse;
    this->superficie = superficie;
    this->typeZone = typeZone;
}

// ============================================================
// CREATE — Ajouter une zone
// Utilise des requêtes préparées (anti-injection SQL)
// ============================================================
bool Zone::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO ZONE (ID_ZONE, NOM, ADRESSE, SUPERFICIE, TYPEZONE) "
                  "VALUES (:id, :nom, :adresse, :superficie, :typezone)");
    query.bindValue(":id",         id_zone);
    query.bindValue(":nom",        nom);
    query.bindValue(":adresse",    adresse);
    query.bindValue(":superficie", superficie);
    // Si typeZone est vide, on insère NULL
    query.bindValue(":typezone",   typeZone.isEmpty() ? QVariant(QMetaType::fromType<QString>()) : QVariant(typeZone));

    bool result = query.exec();
    if (!result) {
        qDebug() << "Erreur ajouter zone:" << query.lastError().text();
    }
    return result;
}

// ============================================================
// DELETE — Supprimer une zone par ID
// ============================================================
bool Zone::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ZONE WHERE ID_ZONE = :id");
    query.bindValue(":id", id);

    bool result = query.exec();
    if (!result) {
        qDebug() << "Erreur supprimer zone:" << query.lastError().text();
    }
    return result;
}

// ============================================================
// UPDATE — Modifier une zone existante
// ============================================================
bool Zone::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE ZONE SET NOM = :nom, ADRESSE = :adresse, "
                  "SUPERFICIE = :superficie, TYPEZONE = :typezone "
                  "WHERE ID_ZONE = :id");
    query.bindValue(":nom",        nom);
    query.bindValue(":adresse",    adresse);
    query.bindValue(":superficie", superficie);
    query.bindValue(":typezone",   typeZone.isEmpty() ? QVariant(QMetaType::fromType<QString>()) : QVariant(typeZone));
    query.bindValue(":id",         id_zone);

    bool result = query.exec();
    if (!result) {
        qDebug() << "Erreur modifier zone:" << query.lastError().text();
    }
    return result;
}

// ============================================================
// READ — Afficher toutes les zones
// Retourne un QSqlQueryModel pour alimenter directement la vue
// ============================================================
QSqlQueryModel* Zone::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_ZONE, NOM, ADRESSE, SUPERFICIE, TYPEZONE FROM ZONE ORDER BY ID_ZONE");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Superficie (m²)"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));

    return model;
}

// ============================================================
// SEARCH — Rechercher des zones par mot-clé (NOM ou ADRESSE)
// Utilise LIKE avec paramètre lié pour éviter l'injection SQL
// ============================================================
QSqlQueryModel* Zone::chercher(QString motCle)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare(
        "SELECT ID_ZONE, NOM, ADRESSE, SUPERFICIE, TYPEZONE FROM ZONE "
        "WHERE UPPER(NOM) LIKE UPPER(:mc) OR UPPER(ADRESSE) LIKE UPPER(:mc2) "
        "ORDER BY NOM"
        );
    QString pattern = "%" + motCle + "%";
    query.bindValue(":mc",  pattern);
    query.bindValue(":mc2", pattern);
    query.exec();
    model->setQuery(std::move(query));

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Superficie (m²)"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));

    return model;
}

// ============================================================
// SORT — Afficher les zones triées par colonne
// La colonne est vérifiée côté C++ (pas injectée directement)
// ============================================================
QSqlQueryModel* Zone::afficherTriee(QString colonne)
{
    // Validation de la colonne — évite toute injection SQL
    QStringList colonnesAutorisees = {"NOM", "SUPERFICIE", "TYPEZONE", "ID_ZONE"};
    if (!colonnesAutorisees.contains(colonne.toUpper()))
        colonne = "ID_ZONE";  // valeur sûre par défaut

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(
        "SELECT ID_ZONE, NOM, ADRESSE, SUPERFICIE, TYPEZONE FROM ZONE ORDER BY " + colonne
        );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Superficie (m²)"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));

    return model;
}
