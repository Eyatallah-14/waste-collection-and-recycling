#include "mainwindow.h"
#include "Loginwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 🔎 Show available SQL drivers
    qDebug() << "Available drivers:" << QSqlDatabase::drivers();

    // -----------------------------
    // 🔌 Oracle ODBC Connection
    // -----------------------------
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    // Use full connection string to ensure username/password are respected
    db.setDatabaseName("Driver={Oracle in XE};Dbq=XE;Uid=LOUAY;Pwd=Louay123;");

    if(!db.open())
    {
        qDebug() << "❌ Database connection failed!";
        qDebug() << db.lastError().text();
        return -1; // Exit if DB connection fails
    }
    else
    {
        qDebug() << "✅ Database connected successfully!";
    }

    // -----------------------------
    // 🖥 Login & Main Windows
    // -----------------------------
    LoginWindow *loginWindow = new LoginWindow();
    MainWindow *mainWindow = new MainWindow();

    QObject::connect(loginWindow, &LoginWindow::loginSuccessful, [mainWindow]() {
        mainWindow->show();
    });

    loginWindow->show();

    return a.exec();
}
