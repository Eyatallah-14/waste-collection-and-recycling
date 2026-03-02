#include "mainwindow.h"
#include "Loginwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ─── Étape 1 : Connexion à la base de données via le Singleton ────────────
    // createInstance() garantit qu'une seule instance de Connection est créée
    // tout au long de l'exécution du projet (patron Singleton)
    Connection& conn = Connection::createInstance();
    bool connected = conn.createconnect();

    if (!connected) {
        // La connexion a échoué → message déjà affiché dans createconnect()
        // L'application continue pour permettre l'utilisation sans BD
        QMessageBox::warning(nullptr,
                             "Démarrage",
                             "L'application démarre sans base de données.\n"
                             "Certaines fonctionnalités seront indisponibles.");
    }

    // ─── Étape 2 : Afficher la fenêtre de login ───────────────────────────────
    LoginWindow *loginWindow = new LoginWindow();
    MainWindow  *mainWindow  = new MainWindow();

    // Connect login success signal to show main window
    QObject::connect(loginWindow, &LoginWindow::loginSuccessful, [mainWindow]() {
        mainWindow->resize(1100, 700);
        mainWindow->show();
    });

    // Show login window first
    loginWindow->show();

    return a.exec();
}
