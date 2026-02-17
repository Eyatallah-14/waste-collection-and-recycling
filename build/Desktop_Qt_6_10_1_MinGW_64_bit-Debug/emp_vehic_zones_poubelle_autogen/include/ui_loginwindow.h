/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QWidget *leftPanel;
    QLabel *decorativeImage;
    QWidget *rightPanel;
    QLabel *welcomeLabel;
    QLineEdit *emailLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QFrame *dividerLine;
    QLabel *orLabel;
    QFrame *dividerLine2;
    QPushButton *faceRecognitionButton;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(1200, 700);
        LoginWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #fcf7f3;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    background-color: white;\n"
"    border: 2px solid #8e944e;\n"
"    border-radius: 8px;\n"
"    padding: 12px 15px;\n"
"    font-size: 14px;\n"
"    color: #2C3E50;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #6d7339;\n"
"    background-color: #F8FFF9;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #8e944e;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 15px 30px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #6d7339;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #2C3E50;\n"
"    font-size: 14px;\n"
"}"));
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName("centralwidget");
        leftPanel = new QWidget(centralwidget);
        leftPanel->setObjectName("leftPanel");
        leftPanel->setGeometry(QRect(0, 0, 500, 700));
        leftPanel->setStyleSheet(QString::fromUtf8("QWidget#leftPanel {\n"
"    background-color: #f5f0eb;\n"
"    border-right: 2px solid #8e944e;\n"
"}"));
        decorativeImage = new QLabel(leftPanel);
        decorativeImage->setObjectName("decorativeImage");
        decorativeImage->setGeometry(QRect(30, 30, 421, 571));
        decorativeImage->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: transparent;\n"
"}"));
        decorativeImage->setPixmap(QPixmap(QString::fromUtf8(":/images/login_background.png")));
        decorativeImage->setScaledContents(true);
        decorativeImage->setAlignment(Qt::AlignmentFlag::AlignCenter);
        rightPanel = new QWidget(centralwidget);
        rightPanel->setObjectName("rightPanel");
        rightPanel->setGeometry(QRect(500, 0, 700, 700));
        rightPanel->setStyleSheet(QString::fromUtf8("QWidget#rightPanel {\n"
"    background-color: white;\n"
"}"));
        welcomeLabel = new QLabel(rightPanel);
        welcomeLabel->setObjectName("welcomeLabel");
        welcomeLabel->setGeometry(QRect(150, 80, 400, 60));
        welcomeLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 32px;\n"
"    font-weight: bold;\n"
"    color: #8e944e;\n"
"}"));
        welcomeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        emailLineEdit = new QLineEdit(rightPanel);
        emailLineEdit->setObjectName("emailLineEdit");
        emailLineEdit->setGeometry(QRect(150, 200, 400, 50));
        passwordLineEdit = new QLineEdit(rightPanel);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(150, 280, 400, 50));
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        loginButton = new QPushButton(rightPanel);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(260, 380, 180, 55));
        loginButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #6d7339;\n"
"}"));
        dividerLine = new QFrame(rightPanel);
        dividerLine->setObjectName("dividerLine");
        dividerLine->setGeometry(QRect(150, 470, 170, 2));
        dividerLine->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: #CCCCCC;\n"
"}"));
        dividerLine->setFrameShape(QFrame::Shape::HLine);
        dividerLine->setFrameShadow(QFrame::Shadow::Sunken);
        orLabel = new QLabel(rightPanel);
        orLabel->setObjectName("orLabel");
        orLabel->setGeometry(QRect(330, 455, 40, 30));
        orLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 14px;\n"
"    color: #666666;\n"
"    background-color: white;\n"
"}"));
        orLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        dividerLine2 = new QFrame(rightPanel);
        dividerLine2->setObjectName("dividerLine2");
        dividerLine2->setGeometry(QRect(380, 470, 170, 2));
        dividerLine2->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: #CCCCCC;\n"
"}"));
        dividerLine2->setFrameShape(QFrame::Shape::HLine);
        dividerLine2->setFrameShadow(QFrame::Shadow::Sunken);
        faceRecognitionButton = new QPushButton(rightPanel);
        faceRecognitionButton->setObjectName("faceRecognitionButton");
        faceRecognitionButton->setGeometry(QRect(150, 520, 400, 70));
        faceRecognitionButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #6d7339;\n"
"    color: white;\n"
"    border-radius: 15px;\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    border: 3px solid #8e944e;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #5a5f2f;\n"
"    border: 3px solid #6d7339;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #4a4f25;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/face_scan_icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        faceRecognitionButton->setIcon(icon);
        faceRecognitionButton->setIconSize(QSize(40, 40));
        LoginWindow->setCentralWidget(centralwidget);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "EcoLoop - Login", nullptr));
        decorativeImage->setText(QString());
        welcomeLabel->setText(QCoreApplication::translate("LoginWindow", "Welcome Back", nullptr));
        emailLineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Email Address", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "\360\237\224\223 Log In", nullptr));
        orLabel->setText(QCoreApplication::translate("LoginWindow", "OR", nullptr));
        faceRecognitionButton->setText(QCoreApplication::translate("LoginWindow", "Login with Face Recognition", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
