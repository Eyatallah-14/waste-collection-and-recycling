/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *logo;
    QFrame *line;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_8;
    QTableWidget *tableWidget;
    QLabel *label;
    QPushButton *pushButton_2;
    QLabel *missions_icon;
    QLabel *zone_icon;
    QLabel *poubelle_icon;
    QPushButton *pushButton_9;
    QLabel *vehicule_icon;
    QLabel *employe_icon;
    QPushButton *pushButton_7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1303, 765);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #fcf7f3;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        logo = new QLabel(centralwidget);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(0, 10, 241, 221));
        logo->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        logo->setScaledContents(true);
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(220, -130, 4, 951));
        line->setStyleSheet(QString::fromUtf8("background-color: #8f954f;\n"
"    min-width: 2px;\n"
"    max-width: 2px;"));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(70, 640, 84, 61));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 30px;\n"
"    color: white;\n"
"    font-size: 24pt;\n"
"    font-weight: bold;\n"
"    min-width: 80px;\n"
"    min-height: 50px;\n"
"    text-align: center;\n"
"    padding: 0px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #6d7339;\n"
"}"));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 380, 211, 74));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 2px solid transparent;\n"
"    border-radius: 20px;\n"
"    color: #8e944e;\n"
"    font-size: 12pt;\n"
"    text-align: center;\n"
"    padding: 15px 20px;\n"
"    min-height: 40px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #6d7389;\n"
"}"));
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(10, 300, 211, 74));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 2px solid transparent;\n"
"    border-radius: 20px;\n"
"    color: #8e944e;\n"
"    font-size: 12pt;\n"
"    text-align: center;\n"
"    padding: 15px 20px;\n"
"    min-height: 40px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #6d7389;\n"
"}"));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(10, 540, 211, 74));
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 2px solid transparent;\n"
"    border-radius: 20px;\n"
"    color: #8e944e;\n"
"    font-size: 12pt;\n"
"    text-align: center;\n"
"    padding: 15px 20px;\n"
"    min-height: 40px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #6d7389;\n"
"}"));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(290, 190, 861, 451));
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    border: 3px solid #8e944e;\n"
"    gridline-color: #8e944e;\n"
"    color: #8e944e;\n"
"    font-size: 12pt;\n"
"}\n"
"\n"
"/* Style the viewport (the actual scrollable area) */\n"
"QTableWidget::viewport {\n"
"    background-color: white;\n"
"    border: none;\n"
"}\n"
"\n"
"/* Ensure the corner widget doesn't interfere */\n"
"QTableWidget QTableCornerButton::section {\n"
"    background-color: white;\n"
"    border: none;\n"
"    border-bottom: 2px solid #8e944e;\n"
"    border-right: 1px solid #8e944e;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 10px;\n"
"    color: #8e944e;\n"
"    border-right: 1px solid #8e944e;\n"
"    border-bottom: 1px solid #8e944e;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: white;\n"
"    color: #8e944e;\n"
"    font-size: 12pt;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"    border-bottom: 2px solid #8e944e;\n"
"    border-right: 1px solid #8e944e;\n"
"    padding: 15px;\n"
"}\n"
"\n"
"/*"
                        " Remove border from last header section */\n"
"QHeaderView::section:last {\n"
"    border-right: none;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: rgba(142, 148, 78, 0.2);\n"
"}\n"
"\n"
"/* Show gridlines properly */\n"
"QTableWidget {\n"
"    showGrid: true;\n"
"}"));
        tableWidget->setDragEnabled(false);
        tableWidget->setAlternatingRowColors(false);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(280, 180, 881, 471));
        label->setStyleSheet(QString::fromUtf8(" background-color: #8e944e;\n"
"\n"
""));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(280, 100, 301, 61));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 30px;\n"
"    color: white;\n"
"    font-size: 15pt;\n"
"    font-weight: bold;\n"
"    min-width: 80px;\n"
"    min-height: 50px;\n"
"    text-align: center;\n"
"    padding: 0px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #6d7339;\n"
"}"));
        missions_icon = new QLabel(centralwidget);
        missions_icon->setObjectName("missions_icon");
        missions_icon->setGeometry(QRect(30, 560, 41, 41));
        missions_icon->setStyleSheet(QString::fromUtf8("QLabel{background-color: transparent;}\n"
"QLabel:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"\n"
"QLabel:pressed {\n"
"    background-color: #6d7389;\n"
"}\n"
""));
        missions_icon->setPixmap(QPixmap(QString::fromUtf8("images/mission_logo.png")));
        missions_icon->setScaledContents(true);
        zone_icon = new QLabel(centralwidget);
        zone_icon->setObjectName("zone_icon");
        zone_icon->setGeometry(QRect(30, 400, 41, 41));
        zone_icon->setStyleSheet(QString::fromUtf8("QLabel{background-color: transparent;}\n"
"QLabel:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"\n"
"QLabel:pressed {\n"
"    background-color: #6d7389;\n"
"}\n"
""));
        zone_icon->setPixmap(QPixmap(QString::fromUtf8("images/zone.png")));
        zone_icon->setScaledContents(true);
        poubelle_icon = new QLabel(centralwidget);
        poubelle_icon->setObjectName("poubelle_icon");
        poubelle_icon->setGeometry(QRect(30, 310, 41, 41));
        poubelle_icon->setStyleSheet(QString::fromUtf8("QLabel{background-color: transparent;}\n"
"QLabel:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"\n"
"QLabel:pressed {\n"
"    background-color: #6d7389;\n"
"}\n"
""));
        poubelle_icon->setPixmap(QPixmap(QString::fromUtf8("images/poubelle.png")));
        poubelle_icon->setScaledContents(true);
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(10, 460, 211, 74));
        pushButton_9->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 2px solid transparent;\n"
"    border-radius: 20px;\n"
"    color: #8e944e;\n"
"    font-size: 12pt;\n"
"    text-align: center;\n"
"    padding: 15px 20px;\n"
"    min-height: 40px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #6d7389;\n"
"}"));
        vehicule_icon = new QLabel(centralwidget);
        vehicule_icon->setObjectName("vehicule_icon");
        vehicule_icon->setGeometry(QRect(30, 480, 41, 41));
        vehicule_icon->setStyleSheet(QString::fromUtf8("QLabel{background-color: transparent;}\n"
"QLabel:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"\n"
"QLabel:pressed {\n"
"    background-color: #6d7389;\n"
"}\n"
""));
        vehicule_icon->setPixmap(QPixmap(QString::fromUtf8("images/truck.png")));
        vehicule_icon->setScaledContents(true);
        employe_icon = new QLabel(centralwidget);
        employe_icon->setObjectName("employe_icon");
        employe_icon->setGeometry(QRect(30, 240, 41, 41));
        employe_icon->setStyleSheet(QString::fromUtf8("QLabel{background-color: transparent;}\n"
"QLabel:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"\n"
"QLabel:pressed {\n"
"    background-color: #6d7389;\n"
"}\n"
""));
        employe_icon->setPixmap(QPixmap(QString::fromUtf8("images/employe.png")));
        employe_icon->setScaledContents(true);
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(10, 220, 211, 74));
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 2px solid transparent;\n"
"    border-radius: 20px;\n"
"    color: #8e944e;\n"
"    font-size: 12pt;\n"
"    text-align: center;\n"
"    padding: 15px 20px;\n"
"    min-height: 40px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #6d7389;\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);
        pushButton_7->raise();
        label->raise();
        logo->raise();
        line->raise();
        pushButton->raise();
        pushButton_5->raise();
        pushButton_6->raise();
        pushButton_8->raise();
        tableWidget->raise();
        pushButton_2->raise();
        missions_icon->raise();
        zone_icon->raise();
        poubelle_icon->raise();
        pushButton_9->raise();
        vehicule_icon->raise();
        employe_icon->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1303, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        logo->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Zone", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Poubelle", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Missions", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Mission number", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "zone", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "workers invoved", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Starting time", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Ending time", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Operations", nullptr));
        label->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Launch a new mission", nullptr));
        missions_icon->setText(QString());
        zone_icon->setText(QString());
        poubelle_icon->setText(QString());
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "V\303\251hicule", nullptr));
        vehicule_icon->setText(QString());
        employe_icon->setText(QString());
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Employ\303\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
