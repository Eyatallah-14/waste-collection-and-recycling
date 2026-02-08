#include "mainwindow.h"
#include "Loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
