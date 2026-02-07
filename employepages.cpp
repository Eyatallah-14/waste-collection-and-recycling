#include "employepages.h"
#include "ui_employepages.h"

#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>
#include <QTableWidgetItem>
#include <QScrollArea>
#include <QFrame>

#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>

EmployePages::EmployePages(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EmployePages)
{
    ui->setupUi(this);

    setStyleSheet(
        "QWidget#EmployePages { background-color: #F5F9FA; }"
        "QWidget#topButtonBar, QWidget#searchBar { background-color: transparent; }"
        "QPushButton#btnListEmployees, QPushButton#btnAddEmployee, QPushButton#btnStatistics { min-height: 50px; border-radius: 12px; font-size: 11pt; font-weight: 600; padding: 12px 24px; }"
        "QPushButton#btnEmail, QPushButton#btnFilter, QPushButton#btnGeneratePdf { background-color: #8e944e; color: white; border: none; border-radius: 12px; padding: 12px 24px; font-size: 10pt; font-weight: bold; }"
        "QPushButton#btnConfirmAdd, QPushButton#btnConfirmUpdate { background-color: #8e944e; color: white; border: none; border-radius: 14px; padding: 14px 36px; font-size: 12pt; font-weight: bold; min-height: 50px; }"
        "QPushButton#btnUploadImage { background-color: white; color: #05668D; border: 3px dashed #05668D; border-radius: 14px; padding: 20px; font-size: 11pt; font-weight: 600; }"
        "QPushButton#btnUploadImage:hover { background-color: #E6F2F5; }"
        "QLineEdit, QComboBox { border: 2px solid #E0E0E0; border-radius: 12px; padding: 12px 16px; background-color: white; color: #2C3E50; font-size: 11pt; min-height: 40px; }"
        "QLineEdit:focus, QComboBox:focus { border-color: #8e944e; }"
        "QLineEdit::placeholder { color: #A0AEC0; }"
        "QComboBox::drop-down { border: none; width: 35px; }"
        "QComboBox::down-arrow { image: none; border-left: 5px solid transparent; border-right: 5px solid transparent; border-top: 6px solid #8e944e; width: 0; height: 0; margin-right: 10px; }"
        "QComboBox QAbstractItemView { background-color: white; color: #2C3E50; border: 2px solid #E0E0E0; border-radius: 10px; selection-background-color: rgba(142, 148, 78, 0.2); selection-color: #2C3E50; outline: none; padding: 5px; }"
        "QTextEdit#inputProgress { border: 2px solid #E0E0E0; border-radius: 12px; padding: 12px; background-color: white; font-size: 10pt; color: #2C3E50; }"
        "QTextEdit#inputProgress:focus { border-color: #8e944e; }"
        "QLabel { color: #4A5568; font-size: 10.5pt; font-weight: 600; }"
        "QLabel#formTitle { color: #8e944e; font-size: 22pt; font-weight: 800; margin-bottom: 20px; }"
        "QWidget#pageForm QLabel { margin-top: 10px; margin-bottom: 6px; color: #2D3748; font-size: 10.5pt; font-weight: 600; }"
        
        "QScrollArea { border: none; background-color: transparent; }"
        "QScrollBar:vertical { border: none; background: #F0F3F5; width: 12px; border-radius: 6px; }"
        "QScrollBar::handle:vertical { background: #8e944e; border-radius: 6px; min-height: 30px; }"
        "QScrollBar::handle:vertical:hover { background: #6d7339; }"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0px; }"
        
        "QTableWidget { background-color: white; alternate-background-color: #F7F8FA; border: 2px solid #E0E0E0; border-radius: 12px; gridline-color: #E2E8F0; font-size: 10pt; color: #2D3748; }"
        "QTableWidget::viewport { background-color: white; }"
        "QTableWidget::item { padding: 12px; border-bottom: 1px solid #E2E8F0; }"
        "QTableWidget::item:selected { background-color: rgba(142, 148, 78, 0.2); color: #2D3748; }"
        "QHeaderView::section { background-color: #8e944e; color: white; padding: 14px; border: none; font-weight: bold; font-size: 10.5pt; }"
        "QWidget#formFieldsContainer { background-color: white; border: 3px solid #8e944e; border-radius: 22px; padding: 35px; }"
        "QWidget#statsLeftContainer, QWidget#statsRightContainer { background-color: white; border: 2px solid #E2E8F0; border-radius: 16px; padding: 20px; }"
        );

    QWidget *formFieldsContainer = this->findChild<QWidget*>("formFieldsContainer");
    if (formFieldsContainer) {
        formFieldsContainer->setMaximumWidth(1100);
    }
    if (ui->formLayout) {
        ui->formLayout->setAlignment(Qt::AlignHCenter);
        ui->formLayout->setSpacing(20);
        ui->formLayout->setContentsMargins(30, 20, 30, 20);
    }

    if (ui->formGrid) {
        ui->formGrid->setVerticalSpacing(18);
        ui->formGrid->setHorizontalSpacing(30);
        ui->formGrid->setContentsMargins(30, 25, 30, 25);
    }

    if (ui->searchBox) {
        ui->searchBox->setClearButtonEnabled(true);
        ui->searchBox->setToolTip("Search employees by name, CIN, email...");
    }

    if (ui->btnGeneratePdf) {
        ui->btnGeneratePdf->setToolTip("Export the employee list to PDF");
    }
    if (ui->btnFilter) {
        ui->btnFilter->setToolTip("Open advanced filters");
    }
    if (ui->btnUploadImage) {
        ui->btnUploadImage->setToolTip("Upload an employee photo");
        ui->btnUploadImage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->btnUploadImage->setFixedHeight(100);
    }
    if (ui->inputProgress) {
        ui->inputProgress->setToolTip("Add a short progress note");
        ui->inputProgress->setMinimumHeight(120);
        ui->inputProgress->setMaximumHeight(120);
    }

    ui->sortCombo->addItems({"Nom", "Prénom", "ID", "Position"});
    ui->inputType->addItems({"Employé", "Admin"});
    ui->inputGender->addItems({"Male", "Female", "Other"});

    // Add scroll area to form page
    QWidget *pageForm = ui->pageForm;
    if (pageForm && ui->formLayout) {
        QScrollArea *scrollArea = new QScrollArea(pageForm);
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setFrameShape(QFrame::NoFrame);
        
        QWidget *scrollWidget = new QWidget();
        QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
        scrollLayout->setContentsMargins(0, 0, 0, 0);
        
        while (ui->formLayout->count() > 0) {
            QLayoutItem *item = ui->formLayout->takeAt(0);
            if (item->layout()) {
                scrollLayout->addLayout(item->layout());
            } else if (item->widget()) {
                scrollLayout->addWidget(item->widget());
            }
        }
        
        scrollWidget->setLayout(scrollLayout);
        scrollArea->setWidget(scrollWidget);
        ui->formLayout->addWidget(scrollArea);
    }

    setupEmployeeTable();
    setupCharts();

    connect(ui->btnListEmployees, &QPushButton::clicked, this, &EmployePages::showListPage);
    connect(ui->btnAddEmployee, &QPushButton::clicked, this, &EmployePages::showFormPage);
    connect(ui->btnStatistics, &QPushButton::clicked, this, &EmployePages::showStatsPage);

    showListPage();
}

EmployePages::~EmployePages()
{
    delete ui;
}

void EmployePages::showListPage()
{
    ui->pagesStack->setCurrentWidget(ui->pageList);

    ui->btnListEmployees->setStyleSheet(
        "QPushButton { background-color: #8e944e; color: white; border: none; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #6d7339; }"
        );

    ui->btnAddEmployee->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    ui->btnStatistics->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );
}

void EmployePages::showFormPage()
{
    ui->pagesStack->setCurrentWidget(ui->pageForm);

    ui->btnListEmployees->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    ui->btnAddEmployee->setStyleSheet(
        "QPushButton { background-color: #8e944e; color: white; border: none; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #6d7339; }"
        );

    ui->btnStatistics->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );
}

void EmployePages::showStatsPage()
{
    ui->pagesStack->setCurrentWidget(ui->pageStats);

    ui->btnListEmployees->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    ui->btnAddEmployee->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    ui->btnStatistics->setStyleSheet(
        "QPushButton { background-color: #8e944e; color: white; border: none; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #6d7339; }"
        );
}

void EmployePages::setupEmployeeTable()
{
    ui->employeeTable->setColumnCount(7);
    ui->employeeTable->setHorizontalHeaderLabels({
        "ID", "CIN", "Nom", "Prénom", "Position",
        "Email", "Operations"
    });

    ui->employeeTable->horizontalHeader()->setStretchLastSection(false);
    ui->employeeTable->verticalHeader()->setVisible(false);
    ui->employeeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->employeeTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->employeeTable->setAlternatingRowColors(true);
    ui->employeeTable->setShowGrid(true);
    ui->employeeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->employeeTable->setFocusPolicy(Qt::NoFocus);

    ui->employeeTable->setColumnWidth(0, 80);
    ui->employeeTable->setColumnWidth(1, 120);
    ui->employeeTable->setColumnWidth(2, 150);
    ui->employeeTable->setColumnWidth(3, 150);
    ui->employeeTable->setColumnWidth(4, 150);
    ui->employeeTable->setColumnWidth(5, 200);
    ui->employeeTable->setColumnWidth(6, 150);

    ui->employeeTable->setRowCount(0);

    ui->employeeTable->insertRow(0);
    ui->employeeTable->setRowHeight(0, 60);
    ui->employeeTable->setItem(0, 0, new QTableWidgetItem("1"));
    ui->employeeTable->setItem(0, 1, new QTableWidgetItem("12345678"));
    ui->employeeTable->setItem(0, 2, new QTableWidgetItem("Dupont"));
    ui->employeeTable->setItem(0, 3, new QTableWidgetItem("Jean"));
    ui->employeeTable->setItem(0, 4, new QTableWidgetItem("Manager"));
    ui->employeeTable->setItem(0, 5, new QTableWidgetItem("jean.dupont@eco.com"));

    QWidget *buttonWidget = new QWidget();
    buttonWidget->setStyleSheet("background-color: transparent;");
    QHBoxLayout *btnLayout = new QHBoxLayout(buttonWidget);
    btnLayout->setContentsMargins(0, 0, 0, 0);
    btnLayout->setSpacing(10);
    btnLayout->setAlignment(Qt::AlignCenter);

    QSize buttonSize(35, 35);

    QPushButton *btnUpdate = new QPushButton();
    QPixmap updatePixmap(":/images/update.png");
    updatePixmap = updatePixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    btnUpdate->setIcon(QIcon(updatePixmap));
    btnUpdate->setIconSize(buttonSize);
    btnUpdate->setFixedSize(buttonSize);
    btnUpdate->setFlat(true);
    btnUpdate->setStyleSheet("QPushButton { background: transparent; border: none; }");
    btnUpdate->setCursor(Qt::PointingHandCursor);

    QPushButton *btnDelete = new QPushButton();
    QPixmap deletePixmap(":/images/delete.png");
    deletePixmap = deletePixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    btnDelete->setIcon(QIcon(deletePixmap));
    btnDelete->setIconSize(buttonSize);
    btnDelete->setFixedSize(buttonSize);
    btnDelete->setFlat(true);
    btnDelete->setStyleSheet("QPushButton { background: transparent; border: none; }");
    btnDelete->setCursor(Qt::PointingHandCursor);

    btnLayout->addWidget(btnUpdate);
    btnLayout->addWidget(btnDelete);

    ui->employeeTable->setCellWidget(0, 6, buttonWidget);
}

void EmployePages::setupCharts()
{
    if (!ui->statsLeftContainer || !ui->statsRightContainer) {
        return;
    }

    QVBoxLayout *leftLayout = new QVBoxLayout(ui->statsLeftContainer);
    leftLayout->setContentsMargins(20, 20, 20, 20);

    QLabel *pieTitle = new QLabel("Employee Distribution by Department");
    pieTitle->setStyleSheet("font-size: 13pt; font-weight: bold; color: #2C3E50; background-color: transparent;");
    pieTitle->setAlignment(Qt::AlignCenter);
    leftLayout->addWidget(pieTitle);

    QPieSeries *pieSeries = new QPieSeries();
    pieSeries->append("Administration", 15);
    pieSeries->append("Medical", 25);
    pieSeries->append("Therapy", 30);
    pieSeries->append("Research", 20);
    pieSeries->append("IT", 10);

    QList<QColor> colors = {QColor("#8e944e"), QColor("#6d7339"), QColor("#05668D"), QColor("#02C39A"), QColor("#8e944e")};

    for (int i = 0; i < pieSeries->slices().count(); i++) {
        QPieSlice *slice = pieSeries->slices().at(i);
        slice->setColor(colors[i % colors.size()]);
        slice->setLabelVisible(true);
        if (slice->percentage() > 0.25) {
            slice->setExploded(true);
            slice->setExplodeDistanceFactor(0.1);
        }
    }

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->legend()->setAlignment(Qt::AlignBottom);
    pieChart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *pieChartView = new QChartView(pieChart);
    pieChartView->setRenderHint(QPainter::Antialiasing);
    pieChartView->setMinimumHeight(400);

    leftLayout->addWidget(pieChartView);

    QVBoxLayout *rightLayout = new QVBoxLayout(ui->statsRightContainer);
    rightLayout->setContentsMargins(20, 20, 20, 20);

    QLabel *barTitle = new QLabel("Employee Count and Average Salary");
    barTitle->setStyleSheet("font-size: 13pt; font-weight: bold; color: #2C3E50; background-color: transparent;");
    barTitle->setAlignment(Qt::AlignCenter);
    rightLayout->addWidget(barTitle);

    QBarSet *countSet = new QBarSet("Quantity");
    QBarSet *salarySet = new QBarSet("Price");

    *countSet << 12 << 32 << 18 << 24 << 14;
    *salarySet << 20 << 10 << 25 << 15 << 18;

    countSet->setColor(QColor("#05668D"));
    salarySet->setColor(QColor("#8e944e"));

    QBarSeries *barSeries = new QBarSeries();
    barSeries->append(countSet);
    barSeries->append(salarySet);

    QChart *barChart = new QChart();
    barChart->addSeries(barSeries);
    barChart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Admin" << "Medical" << "Therapy" << "Research" << "IT";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    barChart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 35);
    barChart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    barChart->legend()->setAlignment(Qt::AlignTop);

    QChartView *barChartView = new QChartView(barChart);
    barChartView->setRenderHint(QPainter::Antialiasing);
    barChartView->setMinimumHeight(400);

    rightLayout->addWidget(barChartView);
}
