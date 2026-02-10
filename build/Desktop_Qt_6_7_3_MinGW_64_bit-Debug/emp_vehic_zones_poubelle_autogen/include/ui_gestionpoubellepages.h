/********************************************************************************
** Form generated from reading UI file 'gestionpoubellepages.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GESTIONPOUBELLEPAGES_H
#define UI_GESTIONPOUBELLEPAGES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GestionPoubellePage
{
public:
    QVBoxLayout *mainLayout;
    QWidget *topButtonBar;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnListPoubelles;
    QPushButton *btnAddPoubelle;
    QPushButton *btnStatistics;
    QPushButton *btnHistorique;
    QSpacerItem *horizontalSpacer;
    QStackedWidget *pagesStack;
    QWidget *pageList;
    QVBoxLayout *verticalLayout;
    QWidget *searchBar;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *searchBox;
    QPushButton *btnSearch;
    QComboBox *sortCombo;
    QPushButton *btnTriEtat;
    QPushButton *btnTriType;
    QPushButton *btnExportPdf;
    QPushButton *btnExportCsv;
    QTableWidget *poubelleTable;
    QWidget *pageForm;
    QVBoxLayout *formLayout;
    QLabel *formTitle;
    QWidget *formFieldsContainer;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *formGrid;
    QLabel *label;
    QComboBox *inputTypeDechet;
    QLabel *label_2;
    QComboBox *inputEtat;
    QLabel *label_3;
    QSpinBox *inputTauxRemplissage;
    QLabel *label_4;
    QLineEdit *inputLocalisation;
    QLabel *label_5;
    QDateEdit *inputDateInstallation;
    QLabel *label_6;
    QDateEdit *inputDateCollecte;
    QCheckBox *checkEndommagee;
    QLabel *label_7;
    QTextEdit *inputNotes;
    QPushButton *btnUploadImage;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnConfirmAdd;
    QPushButton *btnConfirmUpdate;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QWidget *pageStats;
    QVBoxLayout *verticalLayout_4;
    QLabel *statsTitle;
    QHBoxLayout *horizontalLayout_4;
    QWidget *statsLeftContainer;
    QWidget *statsRightContainer;
    QWidget *pageHistorique;
    QVBoxLayout *verticalLayout_5;
    QLabel *historiqueTitle;
    QTableWidget *historiqueTable;

    void setupUi(QWidget *GestionPoubellePage)
    {
        if (GestionPoubellePage->objectName().isEmpty())
            GestionPoubellePage->setObjectName("GestionPoubellePage");
        GestionPoubellePage->resize(1200, 800);
        mainLayout = new QVBoxLayout(GestionPoubellePage);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        topButtonBar = new QWidget(GestionPoubellePage);
        topButtonBar->setObjectName("topButtonBar");
        topButtonBar->setMinimumSize(QSize(0, 70));
        horizontalLayout = new QHBoxLayout(topButtonBar);
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(20, 10, 20, 10);
        btnListPoubelles = new QPushButton(topButtonBar);
        btnListPoubelles->setObjectName("btnListPoubelles");

        horizontalLayout->addWidget(btnListPoubelles);

        btnAddPoubelle = new QPushButton(topButtonBar);
        btnAddPoubelle->setObjectName("btnAddPoubelle");

        horizontalLayout->addWidget(btnAddPoubelle);

        btnStatistics = new QPushButton(topButtonBar);
        btnStatistics->setObjectName("btnStatistics");

        horizontalLayout->addWidget(btnStatistics);

        btnHistorique = new QPushButton(topButtonBar);
        btnHistorique->setObjectName("btnHistorique");

        horizontalLayout->addWidget(btnHistorique);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        mainLayout->addWidget(topButtonBar);

        pagesStack = new QStackedWidget(GestionPoubellePage);
        pagesStack->setObjectName("pagesStack");
        pageList = new QWidget();
        pageList->setObjectName("pageList");
        verticalLayout = new QVBoxLayout(pageList);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        searchBar = new QWidget(pageList);
        searchBar->setObjectName("searchBar");
        searchBar->setMinimumSize(QSize(0, 50));
        horizontalLayout_2 = new QHBoxLayout(searchBar);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        searchBox = new QLineEdit(searchBar);
        searchBox->setObjectName("searchBox");
        searchBox->setMinimumSize(QSize(0, 40));

        horizontalLayout_2->addWidget(searchBox);

        btnSearch = new QPushButton(searchBar);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setMinimumSize(QSize(120, 40));

        horizontalLayout_2->addWidget(btnSearch);

        sortCombo = new QComboBox(searchBar);
        sortCombo->setObjectName("sortCombo");
        sortCombo->setMinimumSize(QSize(150, 40));

        horizontalLayout_2->addWidget(sortCombo);

        btnTriEtat = new QPushButton(searchBar);
        btnTriEtat->setObjectName("btnTriEtat");
        btnTriEtat->setMinimumSize(QSize(100, 40));

        horizontalLayout_2->addWidget(btnTriEtat);

        btnTriType = new QPushButton(searchBar);
        btnTriType->setObjectName("btnTriType");
        btnTriType->setMinimumSize(QSize(100, 40));

        horizontalLayout_2->addWidget(btnTriType);

        btnExportPdf = new QPushButton(searchBar);
        btnExportPdf->setObjectName("btnExportPdf");
        btnExportPdf->setMinimumSize(QSize(100, 40));

        horizontalLayout_2->addWidget(btnExportPdf);

        btnExportCsv = new QPushButton(searchBar);
        btnExportCsv->setObjectName("btnExportCsv");
        btnExportCsv->setMinimumSize(QSize(100, 40));

        horizontalLayout_2->addWidget(btnExportCsv);


        verticalLayout->addWidget(searchBar);

        poubelleTable = new QTableWidget(pageList);
        poubelleTable->setObjectName("poubelleTable");
        poubelleTable->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(poubelleTable);

        pagesStack->addWidget(pageList);
        pageForm = new QWidget();
        pageForm->setObjectName("pageForm");
        formLayout = new QVBoxLayout(pageForm);
        formLayout->setSpacing(20);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(20, 20, 20, 20);
        formTitle = new QLabel(pageForm);
        formTitle->setObjectName("formTitle");
        formTitle->setAlignment(Qt::AlignCenter);

        formLayout->addWidget(formTitle);

        formFieldsContainer = new QWidget(pageForm);
        formFieldsContainer->setObjectName("formFieldsContainer");
        verticalLayout_3 = new QVBoxLayout(formFieldsContainer);
        verticalLayout_3->setSpacing(20);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(30, 30, 30, 30);
        formGrid = new QGridLayout();
        formGrid->setObjectName("formGrid");
        formGrid->setHorizontalSpacing(20);
        formGrid->setVerticalSpacing(15);
        label = new QLabel(formFieldsContainer);
        label->setObjectName("label");

        formGrid->addWidget(label, 0, 0, 1, 1);

        inputTypeDechet = new QComboBox(formFieldsContainer);
        inputTypeDechet->setObjectName("inputTypeDechet");
        inputTypeDechet->setMinimumSize(QSize(0, 35));

        formGrid->addWidget(inputTypeDechet, 0, 1, 1, 1);

        label_2 = new QLabel(formFieldsContainer);
        label_2->setObjectName("label_2");

        formGrid->addWidget(label_2, 1, 0, 1, 1);

        inputEtat = new QComboBox(formFieldsContainer);
        inputEtat->setObjectName("inputEtat");
        inputEtat->setMinimumSize(QSize(0, 35));

        formGrid->addWidget(inputEtat, 1, 1, 1, 1);

        label_3 = new QLabel(formFieldsContainer);
        label_3->setObjectName("label_3");

        formGrid->addWidget(label_3, 2, 0, 1, 1);

        inputTauxRemplissage = new QSpinBox(formFieldsContainer);
        inputTauxRemplissage->setObjectName("inputTauxRemplissage");
        inputTauxRemplissage->setMinimumSize(QSize(0, 35));

        formGrid->addWidget(inputTauxRemplissage, 2, 1, 1, 1);

        label_4 = new QLabel(formFieldsContainer);
        label_4->setObjectName("label_4");

        formGrid->addWidget(label_4, 3, 0, 1, 1);

        inputLocalisation = new QLineEdit(formFieldsContainer);
        inputLocalisation->setObjectName("inputLocalisation");
        inputLocalisation->setMinimumSize(QSize(0, 35));

        formGrid->addWidget(inputLocalisation, 3, 1, 1, 1);

        label_5 = new QLabel(formFieldsContainer);
        label_5->setObjectName("label_5");

        formGrid->addWidget(label_5, 4, 0, 1, 1);

        inputDateInstallation = new QDateEdit(formFieldsContainer);
        inputDateInstallation->setObjectName("inputDateInstallation");
        inputDateInstallation->setMinimumSize(QSize(0, 35));

        formGrid->addWidget(inputDateInstallation, 4, 1, 1, 1);

        label_6 = new QLabel(formFieldsContainer);
        label_6->setObjectName("label_6");

        formGrid->addWidget(label_6, 5, 0, 1, 1);

        inputDateCollecte = new QDateEdit(formFieldsContainer);
        inputDateCollecte->setObjectName("inputDateCollecte");
        inputDateCollecte->setMinimumSize(QSize(0, 35));

        formGrid->addWidget(inputDateCollecte, 5, 1, 1, 1);

        checkEndommagee = new QCheckBox(formFieldsContainer);
        checkEndommagee->setObjectName("checkEndommagee");

        formGrid->addWidget(checkEndommagee, 6, 0, 1, 2);

        label_7 = new QLabel(formFieldsContainer);
        label_7->setObjectName("label_7");

        formGrid->addWidget(label_7, 7, 0, 1, 1);

        inputNotes = new QTextEdit(formFieldsContainer);
        inputNotes->setObjectName("inputNotes");

        formGrid->addWidget(inputNotes, 7, 1, 1, 1);

        btnUploadImage = new QPushButton(formFieldsContainer);
        btnUploadImage->setObjectName("btnUploadImage");

        formGrid->addWidget(btnUploadImage, 8, 0, 1, 2);


        verticalLayout_3->addLayout(formGrid);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        btnConfirmAdd = new QPushButton(formFieldsContainer);
        btnConfirmAdd->setObjectName("btnConfirmAdd");
        btnConfirmAdd->setMinimumSize(QSize(150, 45));

        horizontalLayout_3->addWidget(btnConfirmAdd);

        btnConfirmUpdate = new QPushButton(formFieldsContainer);
        btnConfirmUpdate->setObjectName("btnConfirmUpdate");
        btnConfirmUpdate->setMinimumSize(QSize(150, 45));

        horizontalLayout_3->addWidget(btnConfirmUpdate);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_3);


        formLayout->addWidget(formFieldsContainer);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->addItem(verticalSpacer);

        pagesStack->addWidget(pageForm);
        pageStats = new QWidget();
        pageStats->setObjectName("pageStats");
        verticalLayout_4 = new QVBoxLayout(pageStats);
        verticalLayout_4->setSpacing(20);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(20, 20, 20, 20);
        statsTitle = new QLabel(pageStats);
        statsTitle->setObjectName("statsTitle");
        statsTitle->setAlignment(Qt::AlignCenter);
        statsTitle->setStyleSheet(QString::fromUtf8("font-size: 18pt; font-weight: bold; color: #8e944e;"));

        verticalLayout_4->addWidget(statsTitle);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(20);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        statsLeftContainer = new QWidget(pageStats);
        statsLeftContainer->setObjectName("statsLeftContainer");
        statsLeftContainer->setMinimumSize(QSize(0, 450));

        horizontalLayout_4->addWidget(statsLeftContainer);

        statsRightContainer = new QWidget(pageStats);
        statsRightContainer->setObjectName("statsRightContainer");
        statsRightContainer->setMinimumSize(QSize(0, 450));

        horizontalLayout_4->addWidget(statsRightContainer);


        verticalLayout_4->addLayout(horizontalLayout_4);

        pagesStack->addWidget(pageStats);
        pageHistorique = new QWidget();
        pageHistorique->setObjectName("pageHistorique");
        verticalLayout_5 = new QVBoxLayout(pageHistorique);
        verticalLayout_5->setSpacing(15);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(20, 20, 20, 20);
        historiqueTitle = new QLabel(pageHistorique);
        historiqueTitle->setObjectName("historiqueTitle");
        historiqueTitle->setAlignment(Qt::AlignCenter);
        historiqueTitle->setStyleSheet(QString::fromUtf8("font-size: 18pt; font-weight: bold; color: #8e944e;"));

        verticalLayout_5->addWidget(historiqueTitle);

        historiqueTable = new QTableWidget(pageHistorique);
        historiqueTable->setObjectName("historiqueTable");

        verticalLayout_5->addWidget(historiqueTable);

        pagesStack->addWidget(pageHistorique);

        mainLayout->addWidget(pagesStack);


        retranslateUi(GestionPoubellePage);

        pagesStack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GestionPoubellePage);
    } // setupUi

    void retranslateUi(QWidget *GestionPoubellePage)
    {
        GestionPoubellePage->setWindowTitle(QCoreApplication::translate("GestionPoubellePage", "Gestion des Poubelles", nullptr));
        btnListPoubelles->setText(QCoreApplication::translate("GestionPoubellePage", "Liste des Poubelles", nullptr));
        btnAddPoubelle->setText(QCoreApplication::translate("GestionPoubellePage", "Ajouter Poubelle", nullptr));
        btnStatistics->setText(QCoreApplication::translate("GestionPoubellePage", "Statistiques", nullptr));
        btnHistorique->setText(QCoreApplication::translate("GestionPoubellePage", "Historique", nullptr));
        searchBox->setPlaceholderText(QCoreApplication::translate("GestionPoubellePage", "Rechercher...", nullptr));
        btnSearch->setText(QCoreApplication::translate("GestionPoubellePage", "Rechercher", nullptr));
        btnTriEtat->setText(QCoreApplication::translate("GestionPoubellePage", "Tri \303\211tat", nullptr));
        btnTriType->setText(QCoreApplication::translate("GestionPoubellePage", "Tri Type", nullptr));
        btnExportPdf->setText(QCoreApplication::translate("GestionPoubellePage", "PDF", nullptr));
        btnExportCsv->setText(QCoreApplication::translate("GestionPoubellePage", "CSV", nullptr));
        formTitle->setText(QCoreApplication::translate("GestionPoubellePage", "Ajouter une Poubelle", nullptr));
        label->setText(QCoreApplication::translate("GestionPoubellePage", "Type de D\303\251chet:", nullptr));
        label_2->setText(QCoreApplication::translate("GestionPoubellePage", "\303\211tat:", nullptr));
        label_3->setText(QCoreApplication::translate("GestionPoubellePage", "Taux de Remplissage:", nullptr));
        label_4->setText(QCoreApplication::translate("GestionPoubellePage", "Localisation:", nullptr));
        label_5->setText(QCoreApplication::translate("GestionPoubellePage", "Date Installation:", nullptr));
        label_6->setText(QCoreApplication::translate("GestionPoubellePage", "Derni\303\250re Collecte:", nullptr));
        checkEndommagee->setText(QCoreApplication::translate("GestionPoubellePage", "Poubelle Endommag\303\251e", nullptr));
        label_7->setText(QCoreApplication::translate("GestionPoubellePage", "Notes:", nullptr));
        btnUploadImage->setText(QCoreApplication::translate("GestionPoubellePage", "Ajouter une Photo", nullptr));
        btnConfirmAdd->setText(QCoreApplication::translate("GestionPoubellePage", "Ajouter", nullptr));
        btnConfirmUpdate->setText(QCoreApplication::translate("GestionPoubellePage", "Modifier", nullptr));
        statsTitle->setText(QCoreApplication::translate("GestionPoubellePage", "Statistiques des Poubelles", nullptr));
        historiqueTitle->setText(QCoreApplication::translate("GestionPoubellePage", "Historique des Modifications", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GestionPoubellePage: public Ui_GestionPoubellePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GESTIONPOUBELLEPAGES_H
