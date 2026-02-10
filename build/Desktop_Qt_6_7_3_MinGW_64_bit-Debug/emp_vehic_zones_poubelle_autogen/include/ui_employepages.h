/********************************************************************************
** Form generated from reading UI file 'employepages.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYEPAGES_H
#define UI_EMPLOYEPAGES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmployePages
{
public:
    QVBoxLayout *mainLayout;
    QHBoxLayout *topBarLayout;
    QPushButton *btnListEmployees;
    QPushButton *btnAddEmployee;
    QPushButton *btnStatistics;
    QSpacerItem *horizontalSpacerTop;
    QPushButton *btnEmail;
    QStackedWidget *pagesStack;
    QWidget *pageList;
    QVBoxLayout *listLayout;
    QHBoxLayout *searchLayout;
    QLineEdit *searchBox;
    QLabel *lblSortBy;
    QComboBox *sortCombo;
    QPushButton *btnFilter;
    QSpacerItem *horizontalSpacerSearch;
    QPushButton *btnGeneratePdf;
    QTableWidget *employeeTable;
    QWidget *pageForm;
    QVBoxLayout *formLayout;
    QLabel *formTitle;
    QGridLayout *formGrid;
    QLabel *lblCin;
    QLabel *lblType;
    QLineEdit *inputCin;
    QComboBox *inputType;
    QLabel *lblFirstName;
    QLabel *lblEnrollment;
    QLineEdit *inputFirstName;
    QLineEdit *inputEnrollment;
    QLabel *lblLastName;
    QLabel *lblPhoto;
    QLineEdit *inputLastName;
    QPushButton *btnUploadImage;
    QLabel *lblGender;
    QLabel *lblAge;
    QComboBox *inputGender;
    QLineEdit *inputAge;
    QLabel *lblEmail;
    QLabel *lblPhone;
    QLineEdit *inputEmail;
    QLineEdit *inputPhone;
    QLabel *lblProgress;
    QTextEdit *inputProgress;
    QHBoxLayout *formButtonsLayout;
    QSpacerItem *horizontalSpacerFormLeft;
    QPushButton *btnConfirmUpdate;
    QPushButton *btnConfirmAdd;
    QSpacerItem *horizontalSpacerFormRight;
    QWidget *pageStats;
    QHBoxLayout *statsLayout;
    QWidget *statsLeftContainer;
    QWidget *statsRightContainer;

    void setupUi(QWidget *EmployePages)
    {
        if (EmployePages->objectName().isEmpty())
            EmployePages->setObjectName("EmployePages");
        EmployePages->resize(1150, 554);
        mainLayout = new QVBoxLayout(EmployePages);
        mainLayout->setSpacing(10);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(15, 10, 15, 10);
        topBarLayout = new QHBoxLayout();
        topBarLayout->setSpacing(10);
        topBarLayout->setObjectName("topBarLayout");
        topBarLayout->setContentsMargins(0, 0, 0, 0);
        btnListEmployees = new QPushButton(EmployePages);
        btnListEmployees->setObjectName("btnListEmployees");
        btnListEmployees->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        topBarLayout->addWidget(btnListEmployees);

        btnAddEmployee = new QPushButton(EmployePages);
        btnAddEmployee->setObjectName("btnAddEmployee");
        btnAddEmployee->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        topBarLayout->addWidget(btnAddEmployee);

        btnStatistics = new QPushButton(EmployePages);
        btnStatistics->setObjectName("btnStatistics");
        btnStatistics->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        topBarLayout->addWidget(btnStatistics);

        horizontalSpacerTop = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topBarLayout->addItem(horizontalSpacerTop);

        btnEmail = new QPushButton(EmployePages);
        btnEmail->setObjectName("btnEmail");
        btnEmail->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        topBarLayout->addWidget(btnEmail);


        mainLayout->addLayout(topBarLayout);

        pagesStack = new QStackedWidget(EmployePages);
        pagesStack->setObjectName("pagesStack");
        pageList = new QWidget();
        pageList->setObjectName("pageList");
        listLayout = new QVBoxLayout(pageList);
        listLayout->setSpacing(15);
        listLayout->setObjectName("listLayout");
        searchLayout = new QHBoxLayout();
        searchLayout->setSpacing(15);
        searchLayout->setObjectName("searchLayout");
        searchLayout->setContentsMargins(0, 0, 0, 0);
        searchBox = new QLineEdit(pageList);
        searchBox->setObjectName("searchBox");
        searchBox->setMinimumSize(QSize(300, 40));

        searchLayout->addWidget(searchBox);

        lblSortBy = new QLabel(pageList);
        lblSortBy->setObjectName("lblSortBy");

        searchLayout->addWidget(lblSortBy);

        sortCombo = new QComboBox(pageList);
        sortCombo->setObjectName("sortCombo");
        sortCombo->setMinimumSize(QSize(150, 40));

        searchLayout->addWidget(sortCombo);

        btnFilter = new QPushButton(pageList);
        btnFilter->setObjectName("btnFilter");
        btnFilter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchLayout->addWidget(btnFilter);

        horizontalSpacerSearch = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        searchLayout->addItem(horizontalSpacerSearch);

        btnGeneratePdf = new QPushButton(pageList);
        btnGeneratePdf->setObjectName("btnGeneratePdf");
        btnGeneratePdf->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchLayout->addWidget(btnGeneratePdf);


        listLayout->addLayout(searchLayout);

        employeeTable = new QTableWidget(pageList);
        employeeTable->setObjectName("employeeTable");

        listLayout->addWidget(employeeTable);

        pagesStack->addWidget(pageList);
        pageForm = new QWidget();
        pageForm->setObjectName("pageForm");
        formLayout = new QVBoxLayout(pageForm);
        formLayout->setObjectName("formLayout");
        formTitle = new QLabel(pageForm);
        formTitle->setObjectName("formTitle");
        formTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout->addWidget(formTitle);

        formGrid = new QGridLayout();
        formGrid->setObjectName("formGrid");
        formGrid->setHorizontalSpacing(15);
        formGrid->setVerticalSpacing(6);
        formGrid->setContentsMargins(10, 10, 10, 10);
        lblCin = new QLabel(pageForm);
        lblCin->setObjectName("lblCin");

        formGrid->addWidget(lblCin, 0, 0, 1, 1);

        lblType = new QLabel(pageForm);
        lblType->setObjectName("lblType");

        formGrid->addWidget(lblType, 0, 1, 1, 1);

        inputCin = new QLineEdit(pageForm);
        inputCin->setObjectName("inputCin");

        formGrid->addWidget(inputCin, 1, 0, 1, 1);

        inputType = new QComboBox(pageForm);
        inputType->setObjectName("inputType");

        formGrid->addWidget(inputType, 1, 1, 1, 1);

        lblFirstName = new QLabel(pageForm);
        lblFirstName->setObjectName("lblFirstName");

        formGrid->addWidget(lblFirstName, 2, 0, 1, 1);

        lblEnrollment = new QLabel(pageForm);
        lblEnrollment->setObjectName("lblEnrollment");

        formGrid->addWidget(lblEnrollment, 2, 1, 1, 1);

        inputFirstName = new QLineEdit(pageForm);
        inputFirstName->setObjectName("inputFirstName");

        formGrid->addWidget(inputFirstName, 3, 0, 1, 1);

        inputEnrollment = new QLineEdit(pageForm);
        inputEnrollment->setObjectName("inputEnrollment");

        formGrid->addWidget(inputEnrollment, 3, 1, 1, 1);

        lblLastName = new QLabel(pageForm);
        lblLastName->setObjectName("lblLastName");

        formGrid->addWidget(lblLastName, 4, 0, 1, 1);

        lblPhoto = new QLabel(pageForm);
        lblPhoto->setObjectName("lblPhoto");

        formGrid->addWidget(lblPhoto, 4, 1, 1, 1);

        inputLastName = new QLineEdit(pageForm);
        inputLastName->setObjectName("inputLastName");

        formGrid->addWidget(inputLastName, 5, 0, 1, 1);

        btnUploadImage = new QPushButton(pageForm);
        btnUploadImage->setObjectName("btnUploadImage");

        formGrid->addWidget(btnUploadImage, 5, 1, 1, 1);

        lblGender = new QLabel(pageForm);
        lblGender->setObjectName("lblGender");

        formGrid->addWidget(lblGender, 6, 0, 1, 1);

        lblAge = new QLabel(pageForm);
        lblAge->setObjectName("lblAge");

        formGrid->addWidget(lblAge, 6, 1, 1, 1);

        inputGender = new QComboBox(pageForm);
        inputGender->setObjectName("inputGender");

        formGrid->addWidget(inputGender, 7, 0, 1, 1);

        inputAge = new QLineEdit(pageForm);
        inputAge->setObjectName("inputAge");

        formGrid->addWidget(inputAge, 7, 1, 1, 1);

        lblEmail = new QLabel(pageForm);
        lblEmail->setObjectName("lblEmail");

        formGrid->addWidget(lblEmail, 8, 0, 1, 1);

        lblPhone = new QLabel(pageForm);
        lblPhone->setObjectName("lblPhone");

        formGrid->addWidget(lblPhone, 8, 1, 1, 1);

        inputEmail = new QLineEdit(pageForm);
        inputEmail->setObjectName("inputEmail");

        formGrid->addWidget(inputEmail, 9, 0, 1, 1);

        inputPhone = new QLineEdit(pageForm);
        inputPhone->setObjectName("inputPhone");

        formGrid->addWidget(inputPhone, 9, 1, 1, 1);

        lblProgress = new QLabel(pageForm);
        lblProgress->setObjectName("lblProgress");

        formGrid->addWidget(lblProgress, 10, 0, 1, 2);

        inputProgress = new QTextEdit(pageForm);
        inputProgress->setObjectName("inputProgress");

        formGrid->addWidget(inputProgress, 11, 0, 1, 2);


        formLayout->addLayout(formGrid);

        formButtonsLayout = new QHBoxLayout();
        formButtonsLayout->setObjectName("formButtonsLayout");
        horizontalSpacerFormLeft = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formButtonsLayout->addItem(horizontalSpacerFormLeft);

        btnConfirmUpdate = new QPushButton(pageForm);
        btnConfirmUpdate->setObjectName("btnConfirmUpdate");

        formButtonsLayout->addWidget(btnConfirmUpdate);

        btnConfirmAdd = new QPushButton(pageForm);
        btnConfirmAdd->setObjectName("btnConfirmAdd");

        formButtonsLayout->addWidget(btnConfirmAdd);

        horizontalSpacerFormRight = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formButtonsLayout->addItem(horizontalSpacerFormRight);


        formLayout->addLayout(formButtonsLayout);

        pagesStack->addWidget(pageForm);
        pageStats = new QWidget();
        pageStats->setObjectName("pageStats");
        statsLayout = new QHBoxLayout(pageStats);
        statsLayout->setSpacing(20);
        statsLayout->setObjectName("statsLayout");
        statsLeftContainer = new QWidget(pageStats);
        statsLeftContainer->setObjectName("statsLeftContainer");

        statsLayout->addWidget(statsLeftContainer);

        statsRightContainer = new QWidget(pageStats);
        statsRightContainer->setObjectName("statsRightContainer");

        statsLayout->addWidget(statsRightContainer);

        pagesStack->addWidget(pageStats);

        mainLayout->addWidget(pagesStack);


        retranslateUi(EmployePages);

        QMetaObject::connectSlotsByName(EmployePages);
    } // setupUi

    void retranslateUi(QWidget *EmployePages)
    {
        btnListEmployees->setText(QCoreApplication::translate("EmployePages", "Liste des Employes", nullptr));
        btnAddEmployee->setText(QCoreApplication::translate("EmployePages", "Ajouter un Employe", nullptr));
        btnStatistics->setText(QCoreApplication::translate("EmployePages", "Statistiques", nullptr));
        btnEmail->setText(QCoreApplication::translate("EmployePages", "Email", nullptr));
        searchBox->setPlaceholderText(QCoreApplication::translate("EmployePages", "Search employees...", nullptr));
        lblSortBy->setText(QCoreApplication::translate("EmployePages", "Sort by:", nullptr));
        btnFilter->setText(QCoreApplication::translate("EmployePages", "Filter", nullptr));
        btnGeneratePdf->setText(QCoreApplication::translate("EmployePages", "Generate PDF File", nullptr));
        formTitle->setText(QCoreApplication::translate("EmployePages", "Employee Form", nullptr));
        lblCin->setText(QCoreApplication::translate("EmployePages", "CIN", nullptr));
        lblType->setText(QCoreApplication::translate("EmployePages", "Type", nullptr));
        inputCin->setPlaceholderText(QCoreApplication::translate("EmployePages", "e.g. 12345678", nullptr));
        lblFirstName->setText(QCoreApplication::translate("EmployePages", "First Name", nullptr));
        lblEnrollment->setText(QCoreApplication::translate("EmployePages", "Enrollment Date", nullptr));
        inputFirstName->setPlaceholderText(QCoreApplication::translate("EmployePages", "e.g. Jean", nullptr));
        inputEnrollment->setPlaceholderText(QCoreApplication::translate("EmployePages", "DD/MM/YYYY", nullptr));
        lblLastName->setText(QCoreApplication::translate("EmployePages", "Last Name", nullptr));
        lblPhoto->setText(QCoreApplication::translate("EmployePages", "Photo", nullptr));
        inputLastName->setPlaceholderText(QCoreApplication::translate("EmployePages", "e.g. Dupont", nullptr));
        btnUploadImage->setText(QCoreApplication::translate("EmployePages", "Upload Image", nullptr));
        lblGender->setText(QCoreApplication::translate("EmployePages", "Gender", nullptr));
        lblAge->setText(QCoreApplication::translate("EmployePages", "Age", nullptr));
        inputAge->setPlaceholderText(QCoreApplication::translate("EmployePages", "e.g. 28", nullptr));
        lblEmail->setText(QCoreApplication::translate("EmployePages", "Email", nullptr));
        lblPhone->setText(QCoreApplication::translate("EmployePages", "Phone Number", nullptr));
        inputEmail->setPlaceholderText(QCoreApplication::translate("EmployePages", "name@example.com", nullptr));
        inputPhone->setPlaceholderText(QCoreApplication::translate("EmployePages", "e.g. +216 12 345 678", nullptr));
        lblProgress->setText(QCoreApplication::translate("EmployePages", "Progress Report", nullptr));
        inputProgress->setPlaceholderText(QCoreApplication::translate("EmployePages", "Write a short progress note...", nullptr));
        btnConfirmUpdate->setText(QCoreApplication::translate("EmployePages", "Confirm Update", nullptr));
        btnConfirmAdd->setText(QCoreApplication::translate("EmployePages", "Confirm Add", nullptr));
        (void)EmployePages;
    } // retranslateUi

};

namespace Ui {
    class EmployePages: public Ui_EmployePages {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYEPAGES_H
