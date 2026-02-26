#include "connection.h"
#include <QSqlError>
#include <QDebug>

Connection::Connection()
{
}

bool Connection::createconnect()
{
    bool test=false;

    qDebug()<<"Drivers disponibles:"<<QSqlDatabase::drivers();

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("eya");
    db.setPassword("missaoui");

    if(db.open())
    {
        qDebug()<<"Connexion OK";
        test=true;
    }
    else
    {
        qDebug()<<"Erreur connexion:"<<db.lastError().text();
    }

    return test;
}
