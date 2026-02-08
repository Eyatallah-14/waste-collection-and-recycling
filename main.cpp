#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Configuration de l'application
    a.setApplicationName("Gestion des Poubelles");
    a.setOrganizationName("EcoGestion");
    a.setApplicationVersion("1.0.0");
    
    // Créer et afficher la fenêtre principale avec sidebar
    MainWindow mainWindow;
    mainWindow.show();
    
    return a.exec();
}
