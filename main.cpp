#include "mainwindow.h"
#include "Loginwindow.h"
#include <QApplication>
#include <QDebug>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Création de la connexion à la base
    Connection c;

    if(!c.createconnect())
    {
        qDebug() << "Erreur : impossible de se connecter à la base de données.";
        return -1;  // arrêter l'application si la connexion échoue
    }

    // Create login window
    LoginWindow *loginWindow = new LoginWindow();
    MainWindow *mainWindow = new MainWindow();

    // Connect login success signal to show main window
    QObject::connect(loginWindow, &LoginWindow::loginSuccessful, [mainWindow]() {
        mainWindow->show();
    });

    // Show login window first
    loginWindow->show();

    return a.exec();
}
