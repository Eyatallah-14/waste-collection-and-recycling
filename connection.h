#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

/*
 * Classe Connection - Patron Singleton (Meyers Singleton)
 *
 * Objectif :
 *   - Garantir qu'une seule et unique instance de connexion existe
 *   - Fournir un point d'accès global à cette instance
 *
 * Conforme à l'atelier "Connexion QT/Oracle" - Esprit Tunis 2025-2026
 */

class Connection
{
public:
    // ─── Point d'accès global à l'instance unique ───────────────────────────
    // Retourne toujours la même instance (Meyers Singleton)
    static Connection& createInstance()
    {
        static Connection instance;   // Créé une seule fois, détruit automatiquement
        return instance;
    }

    // ─── Méthode de connexion ────────────────────────────────────────────────
    bool createconnect();

    // ─── Empêcher la copie et l'affectation ─────────────────────────────────
    Connection(const Connection&)            = delete;  // Pas de copie
    Connection& operator=(const Connection&) = delete;  // Pas d'affectation

private:
    // Constructeur privé → instanciation directe impossible depuis l'extérieur
    Connection();
};

#endif // CONNECTION_H
