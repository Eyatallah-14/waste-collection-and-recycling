#include "mainwindow.h"
#include "Loginwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    if(c.createconnect())
        QMessageBox::information(nullptr, "Connection", "Database Connected Successfully!");
    else
        QMessageBox::critical(nullptr, "Connection", "Database Connection Failed!");

    LoginWindow *loginWindow = new LoginWindow();
    MainWindow *mainWindow = new MainWindow();

    QObject::connect(loginWindow, &LoginWindow::loginSuccessful, [mainWindow]() {
        mainWindow->show();
    });

    loginWindow->show();
    return a.exec();
}
