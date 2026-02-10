/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *logo;
    QFrame *line;
    QPushButton *pushButton;
    QPushButton *pushButton_7;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QPushButton *pushButton_9;
    QPushButton *pushButton_8;
    QLabel *employe_icon;
    QLabel *poubelle_icon;
    QLabel *zone_icon;
    QLabel *vehicule_icon;
    QLabel *missions_icon;
    QWidget *pageVehiculeList;
    QLabel *bgVehiculeList;
    QTableWidget *tableWidget;
    QPushButton *pushButton_2;
    QPushButton *btnSearch;
    QPushButton *btnSort;
    QPushButton *btnStats;
    QPushButton *btnExportPDF;
    QPushButton *btnChatbot;
    QWidget *pageSearch;
    QLabel *bgSearch;
    QTableWidget *tableSearchWidget;
    QLineEdit *lineEditSearch;
    QPushButton *btnApplySearch;
    QPushButton *btnBackFromSearch;
    QLabel *lblSearchPageTitle;
    QWidget *pageSort;
    QLabel *bgSort;
    QTableWidget *tableSortWidget;
    QComboBox *comboSortCriteria;
    QPushButton *btnApplySort;
    QPushButton *btnBackFromSort;
    QLabel *lblSortPageTitle;
    QWidget *pageAddVehicule;
    QLabel *bgAddVehicule;
    QWidget *formContainer;
    QLabel *lblFormTitle;
    QLabel *lblType;
    QLabel *lblCapacite;
    QLabel *lblEtat;
    QLabel *lblCarburant;
    QComboBox *comboType;
    QDoubleSpinBox *spinCapacite;
    QComboBox *comboEtat;
    QComboBox *comboCarburant;
    QPushButton *btnSaveVehicule;
    QPushButton *btnCancelForm;
    QWidget *pageStats;
    QLabel *bgStats;
    QWidget *statsContainer;
    QLabel *lblStatsTitle;
    QLabel *lblStatsChart;
    QPushButton *btnBackFromStats;
    QWidget *pageChatbot;
    QLabel *bgChatbot;
    QWidget *chatbotContainer;
    QLabel *lblChatbotTitle;
    QLabel *lblChatbotQuestion;
    QTextEdit *textChatDisplay;
    QLineEdit *lineEditChatInput;
    QPushButton *btnSendChat;
    QPushButton *btnBackFromChatbot;
    QWidget *pageMissions;
    QLabel *bgMissions;
    QLabel *lblMissionsTitle;
    QLabel *missionsIconBig;
    QPushButton *btnAddMission;
    QLabel *lblSearchMission;
    QLineEdit *lineSearchMission;
    QPushButton *btnSearchMission;
    QCheckBox *checkSortByZone;
    QComboBox *comboGroupStatus;
    QPushButton *btnApplySortGroup;
    QWidget *statsContainer1;
    QLabel *lblStatsTitle1;
    QLabel *lblTotalMissions;
    QLabel *lblTodayMissions;
    QLabel *lblMissionsChart;
    QTableWidget *tableMissions;
    QWidget *pageAddMission;
    QLabel *bgAddMission;
    QWidget *formCard;
    QLabel *lblMissionFormTitle;
    QPushButton *btnCloseForm;
    QLabel *lblDate;
    QCalendarWidget *calendarMission;
    QLabel *lblHeureDebut;
    QTimeEdit *timeEditDebut;
    QLabel *lblHeureFin;
    QTimeEdit *timeEditFin;
    QPushButton *btnEstimerFin;
    QLabel *lblZone;
    QLineEdit *lineEditZone;
    QLabel *lblListeEmployes;
    QLineEdit *lineEditEmployes;
    QPushButton *btnEstimerFin1;
    QPushButton *btnSaveMission;
    QPushButton *btnCancelMission;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1400, 850);
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
        line->setGeometry(QRect(220, -130, 4, 1100));
        line->setStyleSheet(QString::fromUtf8("background-color: #8f954f;\n"
"    min-width: 2px;\n"
"    max-width: 2px;"));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(70, 720, 84, 61));
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
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"    color: white;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #6d7339;\n"
"}"));
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
"QPushButton:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
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
"QPushButton:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #6d7389;\n"
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
"QPushButton:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #6d7389;\n"
"}"));
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
"QPushButton:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
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
"QPushButton:hover {\n"
"    background-color: green;\n"
"    color: white;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #6d7389;\n"
"}"));
        employe_icon = new QLabel(centralwidget);
        employe_icon->setObjectName("employe_icon");
        employe_icon->setGeometry(QRect(30, 240, 41, 41));
        employe_icon->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        employe_icon->setScaledContents(true);
        poubelle_icon = new QLabel(centralwidget);
        poubelle_icon->setObjectName("poubelle_icon");
        poubelle_icon->setGeometry(QRect(30, 310, 41, 41));
        poubelle_icon->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        poubelle_icon->setScaledContents(true);
        zone_icon = new QLabel(centralwidget);
        zone_icon->setObjectName("zone_icon");
        zone_icon->setGeometry(QRect(30, 400, 41, 41));
        zone_icon->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        zone_icon->setScaledContents(true);
        vehicule_icon = new QLabel(centralwidget);
        vehicule_icon->setObjectName("vehicule_icon");
        vehicule_icon->setGeometry(QRect(30, 480, 41, 41));
        vehicule_icon->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        vehicule_icon->setScaledContents(true);
        missions_icon = new QLabel(centralwidget);
        missions_icon->setObjectName("missions_icon");
        missions_icon->setGeometry(QRect(30, 560, 41, 41));
        missions_icon->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        missions_icon->setScaledContents(true);
        pageVehiculeList = new QWidget(centralwidget);
        pageVehiculeList->setObjectName("pageVehiculeList");
        pageVehiculeList->setGeometry(QRect(230, 0, 1170, 850));
        pageVehiculeList->setVisible(false);
        bgVehiculeList = new QLabel(pageVehiculeList);
        bgVehiculeList->setObjectName("bgVehiculeList");
        bgVehiculeList->setGeometry(QRect(40, 110, 1090, 420));
        bgVehiculeList->setStyleSheet(QString::fromUtf8("background-color: #8e944e; border-radius: 10px;"));
        tableWidget = new QTableWidget(pageVehiculeList);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(50, 120, 1070, 400));
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    border: 3px solid #8e944e;\n"
"    border-radius: 8px;\n"
"    gridline-color: #8e944e;\n"
"    color: #8e944e;\n"
"    font-size: 11pt;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: white;\n"
"    color: #8e944e;\n"
"    font-size: 11pt;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"    border-bottom: 2px solid #8e944e;\n"
"    border-right: 1px solid #8e944e;\n"
"    padding: 10px;\n"
"}"));
        pushButton_2 = new QPushButton(pageVehiculeList);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(50, 30, 200, 55));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        btnSearch = new QPushButton(pageVehiculeList);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setGeometry(QRect(270, 30, 160, 55));
        btnSearch->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        btnSort = new QPushButton(pageVehiculeList);
        btnSort->setObjectName("btnSort");
        btnSort->setGeometry(QRect(450, 30, 160, 55));
        btnSort->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        btnStats = new QPushButton(pageVehiculeList);
        btnStats->setObjectName("btnStats");
        btnStats->setGeometry(QRect(630, 30, 160, 55));
        btnStats->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        btnExportPDF = new QPushButton(pageVehiculeList);
        btnExportPDF->setObjectName("btnExportPDF");
        btnExportPDF->setGeometry(QRect(450, 570, 250, 55));
        btnExportPDF->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 14pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        btnChatbot = new QPushButton(pageVehiculeList);
        btnChatbot->setObjectName("btnChatbot");
        btnChatbot->setGeometry(QRect(1040, 570, 80, 80));
        btnChatbot->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 3px solid #6d7339;\n"
"    border-radius: 40px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        pageSearch = new QWidget(centralwidget);
        pageSearch->setObjectName("pageSearch");
        pageSearch->setGeometry(QRect(230, 0, 1170, 850));
        pageSearch->setVisible(false);
        bgSearch = new QLabel(pageSearch);
        bgSearch->setObjectName("bgSearch");
        bgSearch->setGeometry(QRect(40, 110, 1090, 550));
        bgSearch->setStyleSheet(QString::fromUtf8("background-color: #8e944e; border-radius: 10px;"));
        tableSearchWidget = new QTableWidget(pageSearch);
        tableSearchWidget->setObjectName("tableSearchWidget");
        tableSearchWidget->setGeometry(QRect(50, 180, 1070, 470));
        tableSearchWidget->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    border: 3px solid #8e944e;\n"
"    border-radius: 8px;\n"
"    gridline-color: #8e944e;\n"
"    color: #8e944e;\n"
"    font-size: 11pt;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: white;\n"
"    color: #8e944e;\n"
"    font-size: 11pt;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"    border-bottom: 2px solid #8e944e;\n"
"    border-right: 1px solid #8e944e;\n"
"    padding: 10px;\n"
"}"));
        lineEditSearch = new QLineEdit(pageSearch);
        lineEditSearch->setObjectName("lineEditSearch");
        lineEditSearch->setGeometry(QRect(50, 30, 700, 50));
        lineEditSearch->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;\n"
"    border: 3px solid #8e944e;\n"
"    border-radius: 12px;\n"
"    padding: 10px;\n"
"    font-size: 13pt;\n"
"    color: #333;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 3px solid #6d7339;\n"
"}"));
        btnApplySearch = new QPushButton(pageSearch);
        btnApplySearch->setObjectName("btnApplySearch");
        btnApplySearch->setGeometry(QRect(770, 30, 180, 50));
        btnApplySearch->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        btnBackFromSearch = new QPushButton(pageSearch);
        btnBackFromSearch->setObjectName("btnBackFromSearch");
        btnBackFromSearch->setGeometry(QRect(970, 30, 150, 50));
        btnBackFromSearch->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #666;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #444;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #333;\n"
"}"));
        lblSearchPageTitle = new QLabel(pageSearch);
        lblSearchPageTitle->setObjectName("lblSearchPageTitle");
        lblSearchPageTitle->setGeometry(QRect(50, 120, 400, 40));
        lblSearchPageTitle->setStyleSheet(QString::fromUtf8("color: white; font-size: 16pt; font-weight: bold; background-color: transparent;"));
        pageSort = new QWidget(centralwidget);
        pageSort->setObjectName("pageSort");
        pageSort->setGeometry(QRect(230, 0, 1170, 850));
        pageSort->setVisible(false);
        bgSort = new QLabel(pageSort);
        bgSort->setObjectName("bgSort");
        bgSort->setGeometry(QRect(40, 110, 1090, 550));
        bgSort->setStyleSheet(QString::fromUtf8("background-color: #8e944e; border-radius: 10px;"));
        tableSortWidget = new QTableWidget(pageSort);
        tableSortWidget->setObjectName("tableSortWidget");
        tableSortWidget->setGeometry(QRect(50, 180, 1070, 470));
        tableSortWidget->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    border: 3px solid #8e944e;\n"
"    border-radius: 8px;\n"
"    gridline-color: #8e944e;\n"
"    color: #8e944e;\n"
"    font-size: 11pt;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: white;\n"
"    color: #8e944e;\n"
"    font-size: 11pt;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"    border-bottom: 2px solid #8e944e;\n"
"    border-right: 1px solid #8e944e;\n"
"    padding: 10px;\n"
"}"));
        comboSortCriteria = new QComboBox(pageSort);
        comboSortCriteria->setObjectName("comboSortCriteria");
        comboSortCriteria->setGeometry(QRect(50, 30, 700, 50));
        comboSortCriteria->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: white;\n"
"    border: 3px solid #8e944e;\n"
"    border-radius: 12px;\n"
"    padding: 10px;\n"
"    font-size: 13pt;\n"
"    color: #333;\n"
"}\n"
"QComboBox:hover {\n"
"    border: 3px solid #6d7339;\n"
"}"));
        btnApplySort = new QPushButton(pageSort);
        btnApplySort->setObjectName("btnApplySort");
        btnApplySort->setGeometry(QRect(770, 30, 180, 50));
        btnApplySort->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        btnBackFromSort = new QPushButton(pageSort);
        btnBackFromSort->setObjectName("btnBackFromSort");
        btnBackFromSort->setGeometry(QRect(970, 30, 150, 50));
        btnBackFromSort->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #666;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #444;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #333;\n"
"}"));
        lblSortPageTitle = new QLabel(pageSort);
        lblSortPageTitle->setObjectName("lblSortPageTitle");
        lblSortPageTitle->setGeometry(QRect(50, 120, 400, 40));
        lblSortPageTitle->setStyleSheet(QString::fromUtf8("color: white; font-size: 16pt; font-weight: bold; background-color: transparent;"));
        pageAddVehicule = new QWidget(centralwidget);
        pageAddVehicule->setObjectName("pageAddVehicule");
        pageAddVehicule->setGeometry(QRect(230, 0, 1170, 850));
        pageAddVehicule->setVisible(false);
        bgAddVehicule = new QLabel(pageAddVehicule);
        bgAddVehicule->setObjectName("bgAddVehicule");
        bgAddVehicule->setGeometry(QRect(200, 100, 750, 550));
        bgAddVehicule->setStyleSheet(QString::fromUtf8("background-color: #8e944e; border-radius: 15px;"));
        formContainer = new QWidget(pageAddVehicule);
        formContainer->setObjectName("formContainer");
        formContainer->setGeometry(QRect(220, 120, 710, 510));
        formContainer->setStyleSheet(QString::fromUtf8("background-color: white; border-radius: 10px;"));
        lblFormTitle = new QLabel(formContainer);
        lblFormTitle->setObjectName("lblFormTitle");
        lblFormTitle->setGeometry(QRect(0, 20, 710, 50));
        lblFormTitle->setStyleSheet(QString::fromUtf8("color: #8e944e; font-size: 20pt; font-weight: bold; background-color: transparent;"));
        lblFormTitle->setAlignment(Qt::AlignCenter);
        lblType = new QLabel(formContainer);
        lblType->setObjectName("lblType");
        lblType->setGeometry(QRect(80, 100, 150, 30));
        lblType->setStyleSheet(QString::fromUtf8("color: #8e944e; font-size: 12pt; font-weight: bold; background-color: transparent;"));
        lblCapacite = new QLabel(formContainer);
        lblCapacite->setObjectName("lblCapacite");
        lblCapacite->setGeometry(QRect(80, 170, 150, 30));
        lblCapacite->setStyleSheet(QString::fromUtf8("color: #8e944e; font-size: 12pt; font-weight: bold; background-color: transparent;"));
        lblEtat = new QLabel(formContainer);
        lblEtat->setObjectName("lblEtat");
        lblEtat->setGeometry(QRect(80, 240, 150, 30));
        lblEtat->setStyleSheet(QString::fromUtf8("color: #8e944e; font-size: 12pt; font-weight: bold; background-color: transparent;"));
        lblCarburant = new QLabel(formContainer);
        lblCarburant->setObjectName("lblCarburant");
        lblCarburant->setGeometry(QRect(80, 310, 150, 30));
        lblCarburant->setStyleSheet(QString::fromUtf8("color: #8e944e; font-size: 12pt; font-weight: bold; background-color: transparent;"));
        comboType = new QComboBox(formContainer);
        comboType->setObjectName("comboType");
        comboType->setGeometry(QRect(280, 100, 350, 40));
        comboType->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: white;\n"
"    border: 2px solid #8e944e;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-size: 11pt;\n"
"    color: #333;\n"
"}\n"
"QComboBox:hover {\n"
"    border: 2px solid #6d7339;\n"
"}\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"}"));
        spinCapacite = new QDoubleSpinBox(formContainer);
        spinCapacite->setObjectName("spinCapacite");
        spinCapacite->setGeometry(QRect(280, 170, 350, 40));
        spinCapacite->setStyleSheet(QString::fromUtf8("QDoubleSpinBox {\n"
"    background-color: white;\n"
"    border: 2px solid #8e944e;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-size: 11pt;\n"
"    color: #333;\n"
"}\n"
"QDoubleSpinBox:hover {\n"
"    border: 2px solid #6d7339;\n"
"}"));
        spinCapacite->setMaximum(999.990000000000009);
        spinCapacite->setSingleStep(0.500000000000000);
        comboEtat = new QComboBox(formContainer);
        comboEtat->setObjectName("comboEtat");
        comboEtat->setGeometry(QRect(280, 240, 350, 40));
        comboEtat->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: white;\n"
"    border: 2px solid #8e944e;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-size: 11pt;\n"
"    color: #333;\n"
"}\n"
"QComboBox:hover {\n"
"    border: 2px solid #6d7339;\n"
"}"));
        comboCarburant = new QComboBox(formContainer);
        comboCarburant->setObjectName("comboCarburant");
        comboCarburant->setGeometry(QRect(280, 310, 350, 40));
        comboCarburant->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: white;\n"
"    border: 2px solid #8e944e;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-size: 11pt;\n"
"    color: #333;\n"
"}\n"
"QComboBox:hover {\n"
"    border: 2px solid #6d7339;\n"
"}"));
        btnSaveVehicule = new QPushButton(formContainer);
        btnSaveVehicule->setObjectName("btnSaveVehicule");
        btnSaveVehicule->setGeometry(QRect(180, 410, 150, 50));
        btnSaveVehicule->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        btnCancelForm = new QPushButton(formContainer);
        btnCancelForm->setObjectName("btnCancelForm");
        btnCancelForm->setGeometry(QRect(380, 410, 150, 50));
        btnCancelForm->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #999;\n"
"    border: 2px solid #666;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #777;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #555;\n"
"}"));
        pageStats = new QWidget(centralwidget);
        pageStats->setObjectName("pageStats");
        pageStats->setGeometry(QRect(230, 0, 1170, 850));
        pageStats->setVisible(false);
        bgStats = new QLabel(pageStats);
        bgStats->setObjectName("bgStats");
        bgStats->setGeometry(QRect(100, 80, 950, 650));
        bgStats->setStyleSheet(QString::fromUtf8("background-color: #8e944e; border-radius: 15px;"));
        statsContainer = new QWidget(pageStats);
        statsContainer->setObjectName("statsContainer");
        statsContainer->setGeometry(QRect(120, 100, 910, 610));
        statsContainer->setStyleSheet(QString::fromUtf8("background-color: white; border-radius: 10px;"));
        lblStatsTitle = new QLabel(statsContainer);
        lblStatsTitle->setObjectName("lblStatsTitle");
        lblStatsTitle->setGeometry(QRect(0, 20, 910, 50));
        lblStatsTitle->setStyleSheet(QString::fromUtf8("color: #8e944e; font-size: 20pt; font-weight: bold; background-color: transparent;"));
        lblStatsTitle->setAlignment(Qt::AlignCenter);
        lblStatsChart = new QLabel(statsContainer);
        lblStatsChart->setObjectName("lblStatsChart");
        lblStatsChart->setGeometry(QRect(155, 100, 600, 400));
        lblStatsChart->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        lblStatsChart->setAlignment(Qt::AlignCenter);
        btnBackFromStats = new QPushButton(statsContainer);
        btnBackFromStats->setObjectName("btnBackFromStats");
        btnBackFromStats->setGeometry(QRect(330, 520, 250, 55));
        btnBackFromStats->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        pageChatbot = new QWidget(centralwidget);
        pageChatbot->setObjectName("pageChatbot");
        pageChatbot->setGeometry(QRect(230, 0, 1170, 850));
        pageChatbot->setVisible(false);
        bgChatbot = new QLabel(pageChatbot);
        bgChatbot->setObjectName("bgChatbot");
        bgChatbot->setGeometry(QRect(100, 80, 950, 650));
        bgChatbot->setStyleSheet(QString::fromUtf8("background-color: #8e944e; border-radius: 15px;"));
        chatbotContainer = new QWidget(pageChatbot);
        chatbotContainer->setObjectName("chatbotContainer");
        chatbotContainer->setGeometry(QRect(120, 100, 910, 610));
        chatbotContainer->setStyleSheet(QString::fromUtf8("background-color: white; border-radius: 10px;"));
        lblChatbotTitle = new QLabel(chatbotContainer);
        lblChatbotTitle->setObjectName("lblChatbotTitle");
        lblChatbotTitle->setGeometry(QRect(0, 20, 910, 50));
        lblChatbotTitle->setStyleSheet(QString::fromUtf8("color: #8e944e; font-size: 20pt; font-weight: bold; background-color: transparent;"));
        lblChatbotTitle->setAlignment(Qt::AlignCenter);
        lblChatbotQuestion = new QLabel(chatbotContainer);
        lblChatbotQuestion->setObjectName("lblChatbotQuestion");
        lblChatbotQuestion->setGeometry(QRect(50, 120, 810, 60));
        lblChatbotQuestion->setStyleSheet(QString::fromUtf8("color: #8e944e; font-size: 16pt; background-color: transparent;"));
        lblChatbotQuestion->setAlignment(Qt::AlignCenter);
        textChatDisplay = new QTextEdit(chatbotContainer);
        textChatDisplay->setObjectName("textChatDisplay");
        textChatDisplay->setGeometry(QRect(50, 200, 810, 250));
        textChatDisplay->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background-color: #f5f5f5;\n"
"    border: 2px solid #8e944e;\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"    font-size: 11pt;\n"
"    color: #333;\n"
"}\n"
"QTextEdit:focus {\n"
"    border: 3px solid #6d7339;\n"
"}"));
        textChatDisplay->setReadOnly(true);
        lineEditChatInput = new QLineEdit(chatbotContainer);
        lineEditChatInput->setObjectName("lineEditChatInput");
        lineEditChatInput->setGeometry(QRect(50, 470, 660, 50));
        lineEditChatInput->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;\n"
"    border: 2px solid #8e944e;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-size: 12pt;\n"
"    color: #333;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 3px solid #6d7339;\n"
"}"));
        btnSendChat = new QPushButton(chatbotContainer);
        btnSendChat->setObjectName("btnSendChat");
        btnSendChat->setGeometry(QRect(730, 470, 130, 50));
        btnSendChat->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 12pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        btnBackFromChatbot = new QPushButton(chatbotContainer);
        btnBackFromChatbot->setObjectName("btnBackFromChatbot");
        btnBackFromChatbot->setGeometry(QRect(330, 540, 250, 50));
        btnBackFromChatbot->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        pageMissions = new QWidget(centralwidget);
        pageMissions->setObjectName("pageMissions");
        pageMissions->setGeometry(QRect(230, 0, 1170, 850));
        pageMissions->setVisible(false);
        bgMissions = new QLabel(pageMissions);
        bgMissions->setObjectName("bgMissions");
        bgMissions->setGeometry(QRect(40, 230, 1090, 300));
        bgMissions->setStyleSheet(QString::fromUtf8("background-color: #d3d3d3; border-radius: 10px;"));
        lblMissionsTitle = new QLabel(pageMissions);
        lblMissionsTitle->setObjectName("lblMissionsTitle");
        lblMissionsTitle->setGeometry(QRect(100, 20, 500, 60));
        lblMissionsTitle->setStyleSheet(QString::fromUtf8("font-size: 28pt; font-weight: bold; color: #8e944e; background: transparent;"));
        missionsIconBig = new QLabel(pageMissions);
        missionsIconBig->setObjectName("missionsIconBig");
        missionsIconBig->setGeometry(QRect(20, 10, 80, 80));
        missionsIconBig->setPixmap(QPixmap(QString::fromUtf8(":/images/mission_logo.png")));
        missionsIconBig->setScaledContents(true);
        btnAddMission = new QPushButton(pageMissions);
        btnAddMission->setObjectName("btnAddMission");
        btnAddMission->setGeometry(QRect(50, 165, 220, 55));
        btnAddMission->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        lblSearchMission = new QLabel(pageMissions);
        lblSearchMission->setObjectName("lblSearchMission");
        lblSearchMission->setGeometry(QRect(50, 80, 120, 30));
        lineSearchMission = new QLineEdit(pageMissions);
        lineSearchMission->setObjectName("lineSearchMission");
        lineSearchMission->setGeometry(QRect(550, 30, 400, 40));
        lineSearchMission->setStyleSheet(QString::fromUtf8("color:black;background: white; border: 2px solid #8e944e; border-radius: 8px; padding: 5px; font-size: 12pt;"));
        btnSearchMission = new QPushButton(pageMissions);
        btnSearchMission->setObjectName("btnSearchMission");
        btnSearchMission->setGeometry(QRect(1000, 30, 120, 40));
        btnSearchMission->setStyleSheet(QString::fromUtf8("QPushButton { color: #000000; background-color: #8e944e;  border-radius: 8px; } QPushButton:hover { background-color: #6d7339; }"));
        checkSortByZone = new QCheckBox(pageMissions);
        checkSortByZone->setObjectName("checkSortByZone");
        checkSortByZone->setGeometry(QRect(50, 130, 200, 30));
        checkSortByZone->setStyleSheet(QString::fromUtf8("font-size: 13pt; color: #000000;"));
        comboGroupStatus = new QComboBox(pageMissions);
        comboGroupStatus->setObjectName("comboGroupStatus");
        comboGroupStatus->setGeometry(QRect(550, 130, 250, 40));
        comboGroupStatus->setStyleSheet(QString::fromUtf8("font-size: 12pt; ; color: #000000;border: 2px solid #8e944e; border-radius: 8px;"));
        btnApplySortGroup = new QPushButton(pageMissions);
        btnApplySortGroup->setObjectName("btnApplySortGroup");
        btnApplySortGroup->setGeometry(QRect(1000, 130, 140, 40));
        btnApplySortGroup->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #8e944e; color: #000000; border-radius: 8px; font-size: 13pt; } QPushButton:hover { background-color: #6d7339; }"));
        statsContainer1 = new QWidget(pageMissions);
        statsContainer1->setObjectName("statsContainer1");
        statsContainer1->setGeometry(QRect(70, 560, 840, 250));
        statsContainer1->setStyleSheet(QString::fromUtf8("\n"
"   background: rgba(30, 79, 44, 0.82);\n"
"   border-radius: 16px;\n"
"   border: 1px solid rgba(100, 180, 255, 0.4);\n"
"   box-shadow: 0 8px 28px rgba(0, 0, 0, 0.5);\n"
"  "));
        lblStatsTitle1 = new QLabel(statsContainer1);
        lblStatsTitle1->setObjectName("lblStatsTitle1");
        lblStatsTitle1->setGeometry(QRect(30, 15, 450, 35));
        lblStatsTitle1->setStyleSheet(QString::fromUtf8("color: #c0e0ff; font-size: 18pt; font-weight: bold; background: transparent;"));
        lblTotalMissions = new QLabel(statsContainer1);
        lblTotalMissions->setObjectName("lblTotalMissions");
        lblTotalMissions->setGeometry(QRect(35, 65, 290, 42));
        lblTotalMissions->setStyleSheet(QString::fromUtf8("\n"
"    color: #ffffff; \n"
"    font-size: 14pt; \n"
"    font-weight: bold; \n"
"    background: rgba(60, 60, 100, 0.6);\n"
"    border-radius: 10px;\n"
"    padding: 0 14px;\n"
"    border: none;\n"
"   "));
        lblTotalMissions->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        lblTodayMissions = new QLabel(statsContainer1);
        lblTodayMissions->setObjectName("lblTodayMissions");
        lblTodayMissions->setGeometry(QRect(35, 115, 290, 42));
        lblTodayMissions->setStyleSheet(QString::fromUtf8("\n"
"    color: #b0ffd0; \n"
"    font-size: 14pt; \n"
"    font-weight: bold; \n"
"    background: rgba(50, 100, 80, 0.6);\n"
"    border-radius: 10px;\n"
"    padding: 0 14px;\n"
"    border: none;\n"
"   "));
        lblTodayMissions->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        lblMissionsChart = new QLabel(statsContainer1);
        lblMissionsChart->setObjectName("lblMissionsChart");
        lblMissionsChart->setGeometry(QRect(350, 60, 460, 160));
        lblMissionsChart->setStyleSheet(QString::fromUtf8("\n"
"    background: rgba(35, 35, 70, 0.75);\n"
"    border-radius: 12px;\n"
"    border: 1px solid rgba(110, 180, 255, 0.35);\n"
"   "));
        lblMissionsChart->setAlignment(Qt::AlignCenter);
        tableMissions = new QTableWidget(pageMissions);
        tableMissions->setObjectName("tableMissions");
        tableMissions->setGeometry(QRect(50, 240, 1070, 280));
        tableMissions->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    border: 3px solid #8e944e;\n"
"    border-radius: 8px;\n"
"    gridline-color: #8e944e;\n"
"    color: #8e944e;\n"
"    font-size: 11pt;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: white;\n"
"    color: #8e944e;\n"
"    font-size: 11pt;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"    border-bottom: 2px solid #8e944e;\n"
"    border-right: 1px solid #8e944e;\n"
"    padding: 10px;\n"
"}"));
        tableMissions->setShowGrid(true);
        tableMissions->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableMissions->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableMissions->setFocusPolicy(Qt::NoFocus);
        tableMissions->setSelectionMode(QAbstractItemView::NoSelection);
        pageAddMission = new QWidget(centralwidget);
        pageAddMission->setObjectName("pageAddMission");
        pageAddMission->setGeometry(QRect(230, 0, 1170, 850));
        pageAddMission->setVisible(false);
        bgAddMission = new QLabel(pageAddMission);
        bgAddMission->setObjectName("bgAddMission");
        bgAddMission->setGeometry(QRect(0, 0, 1170, 850));
        bgAddMission->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f8f7f4, stop:1 #e8e6e0);"));
        formCard = new QWidget(pageAddMission);
        formCard->setObjectName("formCard");
        formCard->setGeometry(QRect(200, 80, 770, 680));
        formCard->setStyleSheet(QString::fromUtf8("background-color: white; border-radius: 16px; border: 1px solid #d0d0d0; box-shadow: 0px 8px 24px rgba(0,0,0,0.1);"));
        lblMissionFormTitle = new QLabel(formCard);
        lblMissionFormTitle->setObjectName("lblMissionFormTitle");
        lblMissionFormTitle->setGeometry(QRect(30, 30, 710, 50));
        lblMissionFormTitle->setStyleSheet(QString::fromUtf8("font-size: 24pt; font-weight: bold; color: #8e944e; background: transparent;"));
        lblMissionFormTitle->setAlignment(Qt::AlignCenter);
        btnCloseForm = new QPushButton(formCard);
        btnCloseForm->setObjectName("btnCloseForm");
        btnCloseForm->setGeometry(QRect(700, 30, 50, 50));
        btnCloseForm->setStyleSheet(QString::fromUtf8("QPushButton { background: transparent; color: #8e944e; font-size: 24pt; border: none; } QPushButton:hover { color: #6d7339; }"));
        btnCloseForm->setFlat(true);
        lblDate = new QLabel(formCard);
        lblDate->setObjectName("lblDate");
        lblDate->setGeometry(QRect(60, 100, 180, 35));
        lblDate->setStyleSheet(QString::fromUtf8("color: #555; font-size: 14pt; font-weight: bold;"));
        calendarMission = new QCalendarWidget(formCard);
        calendarMission->setObjectName("calendarMission");
        calendarMission->setGeometry(QRect(60, 150, 600, 210));
        calendarMission->setStyleSheet(QString::fromUtf8("\n"
"   QCalendarWidget {\n"
"    background-color: #ffffff;\n"
"    color: #000000 !important;\n"
"    font-size: 14pt;\n"
"    border: 2px solid #ffffff;\n"
"    border-radius: 10px;\n"
"   }\n"
"   QCalendarWidget QAbstractItemView {\n"
"    background-color: #ffffff;\n"
"    color: #000000 !important;\n"
"    selection-background-color: #fcfcfc;\n"
"    selection-color: white;\n"
"    alternate-background-color: #f8f8f8;\n"
"   }\n"
"   QCalendarWidget QWidget#qt_calendar_navigationbar {\n"
"    background-color: #ffffff;\n"
"    color: white !important;\n"
"   }\n"
"   QCalendarWidget QToolButton {\n"
"    color: black !important;\n"
"   }\n"
"   QCalendarWidget QMenu {\n"
"    background-color: #ffffff !important;\n"
"    color: #000000 !important;\n"
"   }\n"
"   QCalendarWidget QMenu::item {\n"
"    color: #000000 !important;\n"
"   }\n"
"   QCalendarWidget QMenu::item:selected {\n"
"    background-color: #ffffff !important;\n"
"    color: black !important;\n"
"   }\n"
"  "));
        calendarMission->setGridVisible(true);
        calendarMission->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
        calendarMission->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        calendarMission->setMinimumDate(QDate(2020, 1, 1));
        calendarMission->setMaximumDate(QDate(2030, 12, 31));
        lblHeureDebut = new QLabel(formCard);
        lblHeureDebut->setObjectName("lblHeureDebut");
        lblHeureDebut->setGeometry(QRect(10, 520, 180, 35));
        lblHeureDebut->setStyleSheet(QString::fromUtf8("color: #555; font-size: 14pt; font-weight: bold;"));
        timeEditDebut = new QTimeEdit(formCard);
        timeEditDebut->setObjectName("timeEditDebut");
        timeEditDebut->setGeometry(QRect(170, 520, 180, 40));
        timeEditDebut->setStyleSheet(QString::fromUtf8("background: white; border: 1px solid #d0d0d0; border-radius: 8px; padding: 6px; font-size: 14pt; color: #333;"));
        lblHeureFin = new QLabel(formCard);
        lblHeureFin->setObjectName("lblHeureFin");
        lblHeureFin->setGeometry(QRect(390, 520, 180, 35));
        lblHeureFin->setStyleSheet(QString::fromUtf8("color: #555; font-size: 14pt; font-weight: bold;"));
        timeEditFin = new QTimeEdit(formCard);
        timeEditFin->setObjectName("timeEditFin");
        timeEditFin->setGeometry(QRect(550, 520, 180, 40));
        timeEditFin->setStyleSheet(QString::fromUtf8("background: #f0f0f0; border: 1px solid #ccc; border-radius: 8px; padding: 6px; font-size: 14pt; color: #666;"));
        timeEditFin->setReadOnly(true);
        btnEstimerFin = new QPushButton(formCard);
        btnEstimerFin->setObjectName("btnEstimerFin");
        btnEstimerFin->setGeometry(QRect(850, 10, 100000, 40));
        btnEstimerFin->setStyleSheet(QString::fromUtf8("QPushButton { background: #8e944e; color: white; border-radius: 8px; font-size: 12pt; } QPushButton:hover { background: #6d7339; }"));
        lblZone = new QLabel(formCard);
        lblZone->setObjectName("lblZone");
        lblZone->setGeometry(QRect(80, 370, 150, 30));
        lblZone->setStyleSheet(QString::fromUtf8("color: #8e944e; font-size: 12pt; font-weight: bold; background-color: transparent;"));
        lineEditZone = new QLineEdit(formCard);
        lineEditZone->setObjectName("lineEditZone");
        lineEditZone->setGeometry(QRect(280, 370, 350, 40));
        lineEditZone->setStyleSheet(QString::fromUtf8("background-color: white; border: 2px solid #8e944e; border-radius: 8px; padding: 5px; font-size: 11pt; color: #333;"));
        lblListeEmployes = new QLabel(formCard);
        lblListeEmployes->setObjectName("lblListeEmployes");
        lblListeEmployes->setGeometry(QRect(80, 420, 150, 30));
        lblListeEmployes->setStyleSheet(QString::fromUtf8("color: #8e944e; font-size: 12pt; font-weight: bold; background-color: transparent;"));
        lineEditEmployes = new QLineEdit(formCard);
        lineEditEmployes->setObjectName("lineEditEmployes");
        lineEditEmployes->setGeometry(QRect(280, 420, 350, 40));
        lineEditEmployes->setStyleSheet(QString::fromUtf8("background-color: white; border: 2px solid #8e944e; border-radius: 8px; padding: 5px; font-size: 11pt; color: #333;"));
        btnEstimerFin1 = new QPushButton(formCard);
        btnEstimerFin1->setObjectName("btnEstimerFin1");
        btnEstimerFin1->setGeometry(QRect(570, 600, 150, 40));
        btnEstimerFin1->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #8e944e; color: white; border-radius: 8px; font-size: 12pt; } QPushButton:hover { background-color: #6d7339; }"));
        btnSaveMission = new QPushButton(formCard);
        btnSaveMission->setObjectName("btnSaveMission");
        btnSaveMission->setGeometry(QRect(180, 600, 150, 50));
        btnSaveMission->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8e944e;\n"
"    border: 2px solid black;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6d7339;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5a5f2d;\n"
"}"));
        btnCancelMission = new QPushButton(formCard);
        btnCancelMission->setObjectName("btnCancelMission");
        btnCancelMission->setGeometry(QRect(380, 600, 150, 50));
        btnCancelMission->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #999;\n"
"    border: 2px solid #666;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"    font-size: 13pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #777;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #555;\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1400, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des V\303\251hicules", nullptr));
        logo->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Employ\303\251", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Poubelle", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Zone", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "V\303\251hicule", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Missions", nullptr));
        employe_icon->setText(QString());
        poubelle_icon->setText(QString());
        zone_icon->setText(QString());
        vehicule_icon->setText(QString());
        missions_icon->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Ajouter v\303\251hicule", nullptr));
        btnSearch->setText(QCoreApplication::translate("MainWindow", "Recherche", nullptr));
        btnSort->setText(QCoreApplication::translate("MainWindow", "Tri", nullptr));
        btnStats->setText(QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        btnExportPDF->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 Exporter PDF", nullptr));
        lineEditSearch->setPlaceholderText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Rechercher par type, \303\251tat ou carburant...", nullptr));
        btnApplySearch->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        btnBackFromSearch->setText(QCoreApplication::translate("MainWindow", "\342\206\220 Retour", nullptr));
        lblSearchPageTitle->setText(QCoreApplication::translate("MainWindow", "R\303\251sultats de la recherche:", nullptr));
        btnApplySort->setText(QCoreApplication::translate("MainWindow", "Appliquer", nullptr));
        btnBackFromSort->setText(QCoreApplication::translate("MainWindow", "\342\206\220 Retour", nullptr));
        lblSortPageTitle->setText(QCoreApplication::translate("MainWindow", "V\303\251hicules tri\303\251s:", nullptr));
        lblFormTitle->setText(QCoreApplication::translate("MainWindow", "Ajouter un nouveau v\303\251hicule", nullptr));
        lblType->setText(QCoreApplication::translate("MainWindow", "Type de v\303\251hicule:", nullptr));
        lblCapacite->setText(QCoreApplication::translate("MainWindow", "Capacit\303\251 (m\302\263):", nullptr));
        lblEtat->setText(QCoreApplication::translate("MainWindow", "\303\211tat:", nullptr));
        lblCarburant->setText(QCoreApplication::translate("MainWindow", "Carburant:", nullptr));
        btnSaveVehicule->setText(QCoreApplication::translate("MainWindow", "Enregistrer", nullptr));
        btnCancelForm->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        lblStatsTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Statistiques des V\303\251hicules", nullptr));
        lblStatsChart->setText(QString());
        btnBackFromStats->setText(QCoreApplication::translate("MainWindow", "\342\206\220 Retour \303\240 la liste", nullptr));
        lblChatbotTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\244\226 Assistant Chatbot", nullptr));
        lblChatbotQuestion->setText(QCoreApplication::translate("MainWindow", "Comment puis-je vous aider ?", nullptr));
        lineEditChatInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Posez votre question ici...", nullptr));
        btnSendChat->setText(QCoreApplication::translate("MainWindow", "Envoyer", nullptr));
        btnBackFromChatbot->setText(QCoreApplication::translate("MainWindow", "\342\206\220 Retour \303\240 la liste", nullptr));
        bgMissions->setText(QString());
        lblMissionsTitle->setText(QCoreApplication::translate("MainWindow", "Gestion des Missions", nullptr));
        btnAddMission->setText(QCoreApplication::translate("MainWindow", "Ajouter Mission", nullptr));
        lineSearchMission->setPlaceholderText(QCoreApplication::translate("MainWindow", "Zone, employ\303\251s, date...", nullptr));
        btnSearchMission->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        checkSortByZone->setText(QCoreApplication::translate("MainWindow", "Trier par nom de zone", nullptr));
        btnApplySortGroup->setText(QCoreApplication::translate("MainWindow", "Appliquer", nullptr));
        lblStatsTitle1->setText(QCoreApplication::translate("MainWindow", "Mission Statistics", nullptr));
        lblTotalMissions->setText(QCoreApplication::translate("MainWindow", "Total Missions: 12", nullptr));
        lblTodayMissions->setText(QCoreApplication::translate("MainWindow", "Missions Today: 5", nullptr));
        lblMissionsChart->setText(QCoreApplication::translate("MainWindow", "Statistics Chart\\n(Empty \342\200\223 add QChartView here)\\nExample: Total vs Today vs Planned", nullptr));
        lblMissionFormTitle->setText(QCoreApplication::translate("MainWindow", "Ajouter une Mission", nullptr));
        btnCloseForm->setText(QCoreApplication::translate("MainWindow", "\303\227", nullptr));
        lblDate->setText(QCoreApplication::translate("MainWindow", "Date de la mission :", nullptr));
        lblHeureDebut->setText(QCoreApplication::translate("MainWindow", "Heure de d\303\251but :", nullptr));
        timeEditDebut->setDisplayFormat(QCoreApplication::translate("MainWindow", "HH:mm", nullptr));
        lblHeureFin->setText(QCoreApplication::translate("MainWindow", "Heure de fin :", nullptr));
        timeEditFin->setDisplayFormat(QCoreApplication::translate("MainWindow", "HH:mm", nullptr));
        btnEstimerFin->setText(QCoreApplication::translate("MainWindow", "Estimer", nullptr));
        lblZone->setText(QCoreApplication::translate("MainWindow", "Zone :", nullptr));
        lineEditZone->setPlaceholderText(QCoreApplication::translate("MainWindow", "e.g., Rue France", nullptr));
        lblListeEmployes->setText(QCoreApplication::translate("MainWindow", "Liste Employ\303\251s:", nullptr));
        lineEditEmployes->setPlaceholderText(QCoreApplication::translate("MainWindow", "e.g., 1,4,6 (IDs s\303\251par\303\251s par virgule)", nullptr));
        btnEstimerFin1->setText(QCoreApplication::translate("MainWindow", "Estimer Heure Fin", nullptr));
        btnSaveMission->setText(QCoreApplication::translate("MainWindow", "Enregistrer", nullptr));
        btnCancelMission->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
