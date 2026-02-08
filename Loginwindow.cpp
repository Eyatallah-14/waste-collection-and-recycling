#include "Loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // Set window properties
    setWindowTitle("EcoLoop - Login");
    setFixedSize(1200, 700);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString email = ui->emailLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    // Simple validation (you can add database authentication here)
    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login", "Please enter email and password");
        return;
    }

    // For demo purposes, accept any non-empty credentials
    emit loginSuccessful();
    this->close();
}

void LoginWindow::on_faceRecognitionButton_clicked()
{
    // Placeholder for face recognition functionality
    QMessageBox::information(this, "Face Recognition",
                             "Face recognition feature will be implemented here soon.\n");


    emit loginSuccessful();
    this->close();
}

void LoginWindow::on_signupButton_clicked()
{
    QMessageBox::information(this, "Sign Up",
                             "Sign up functionality will be implemented here soon.");
}
