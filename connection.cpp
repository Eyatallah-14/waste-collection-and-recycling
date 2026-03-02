#include "connection.h"
#include <QMessageBox>

/*
 * connection.cpp - Implémentation du patron Singleton
 *
 * Conforme à l'atelier "Connexion QT/Oracle" - Esprit Tunis 2025-2026
 *
 * ⚠  IMPORTANT : Remplacez les valeurs ci-dessous par vos propres paramètres :
 *    - Nom de la source de données ODBC créée dans le panneau de config Windows
 *    - Nom d'utilisateur Oracle créé avec SQL Developer (ex: soumaya)
 *    - Mot de passe correspondant (ex: esprit18)
 */

// Constructeur privé (le Singleton s'initialise ici)
Connection::Connection()
{
    // Le constructeur est privé pour empêcher l'instanciation depuis l'extérieur.
    // createInstance() est le seul point d'entrée.
}

// ─── Méthode de connexion à la base de données Oracle via ODBC ───────────────
bool Connection::createconnect()
{
    bool test = false;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    // ─────────────────────────────────────────────────────────────────────────
    // ⚠  À MODIFIER avec vos propres paramètres (voir atelier slide 9 et 14) :
    // ─────────────────────────────────────────────────────────────────────────
    db.setDatabaseName("source_projectfatma"); // Nom de votre source de données ODBC
    db.setUserName("SYSTEM");             // Nom d'utilisateur Oracle
    db.setPassword("12345");            // Mot de passe Oracle
    // ─────────────────────────────────────────────────────────────────────────

    if (db.open()) {
        test = true;
        QMessageBox::information(nullptr,
                                 "Base de données",
                                 "Connexion à Oracle réussie !");
    } else {
        QMessageBox::critical(nullptr,
                              "Erreur de connexion",
                              "Connexion échouée !\n\n"
                              "Détails : " + db.lastError().text() + "\n\n"
                              "Vérifiez :\n"
                              "  1. Oracle 64 bit est lancé\n"
                              "  2. Le nom de la source ODBC est correct\n"
                              "  3. Le compilateur est en 64 bit");
    }

    return test;
}
