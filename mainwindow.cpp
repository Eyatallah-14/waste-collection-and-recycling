#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QIcon>
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <algorithm>

//==============================================================================
// CONSTRUCTOR
//==============================================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentPage(PAGE_MISSIONS)
    , nextVehiculeId(1)
    , editingVehiculeId(-1)
{
    ui->setupUi(this);

    // Configuration des tableaux
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    ui->tableSearchWidget->setShowGrid(true);
    ui->tableSearchWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableSearchWidget->verticalHeader()->setVisible(false);
    ui->tableSearchWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableSearchWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableSearchWidget->setSelectionMode(QAbstractItemView::NoSelection);

    ui->tableSortWidget->setShowGrid(true);
    ui->tableSortWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableSortWidget->verticalHeader()->setVisible(false);
    ui->tableSortWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableSortWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableSortWidget->setSelectionMode(QAbstractItemView::NoSelection);

    // Chargement des icônes
    originalLogoPixmap = QPixmap(":/images/logo.png");
    ui->logo->setPixmap(originalLogoPixmap);
    ui->logo->setScaledContents(true);

    ui->missions_icon->setPixmap(QPixmap(":/images/mission_logo.png").scaled(
        ui->missions_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->zone_icon->setPixmap(QPixmap(":/images/zone_icon.png").scaled(
        ui->zone_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->poubelle_icon->setPixmap(QPixmap(":/images/poubelle_icon.png").scaled(
        ui->poubelle_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->employe_icon->setPixmap(QPixmap(":/images/employe_icon.png").scaled(
        ui->employe_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->vehicule_icon->setPixmap(QPixmap(":/images/truck_icon.png").scaled(
        ui->vehicule_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Chatbot icon
    QPixmap chatbotPixmap(":/images/chatbot.png");
    if (!chatbotPixmap.isNull()) {
        chatbotPixmap = chatbotPixmap.scaled(90, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->btnChatbot->setIcon(QIcon(chatbotPixmap));
        ui->btnChatbot->setIconSize(QSize(90, 90));
    } else {
        QFont font = ui->btnChatbot->font();
        font.setPointSize(36);
        ui->btnChatbot->setFont(font);
        ui->btnChatbot->setText("🤖");
    }

    // Event filters
    ui->missions_icon->installEventFilter(this);
    ui->zone_icon->installEventFilter(this);
    ui->poubelle_icon->installEventFilter(this);
    ui->employe_icon->installEventFilter(this);
    ui->vehicule_icon->installEventFilter(this);

    // Populate combo boxes for form
    ui->comboType->addItems({"Camion Benne", "Camion Compacteur", "Camionnette",
                             "Tracteur", "Poids Lourd"});
    ui->comboEtat->addItems({"disponible", "en panne", "en maintenance"});
    ui->comboCarburant->addItems({"diesel", "essence", "hybride", "électrique"});

    // Populate combo box for sort
    ui->comboSortCriteria->addItems({"ID", "Type", "Capacité", "État", "Carburant"});

    // Connect form buttons
    connect(ui->btnSaveVehicule, &QPushButton::clicked, this, &MainWindow::onSaveVehiculeForm);
    connect(ui->btnCancelForm, &QPushButton::clicked, this, &MainWindow::onCancelForm);

    // Connect search buttons
    connect(ui->btnApplySearch, &QPushButton::clicked, this, &MainWindow::onApplySearch);
    connect(ui->btnBackFromSearch, &QPushButton::clicked, this, &MainWindow::onBackToVehiculeList);

    // Connect sort buttons
    connect(ui->btnApplySort, &QPushButton::clicked, this, &MainWindow::onApplySort);
    connect(ui->btnBackFromSort, &QPushButton::clicked, this, &MainWindow::onBackToVehiculeList);

    // Connect stats button
    connect(ui->btnBackFromStats, &QPushButton::clicked, this, &MainWindow::onBackToVehiculeList);

    // Connect chatbot buttons
    connect(ui->btnSendChat, &QPushButton::clicked, this, [this]() {
        QString userInput = ui->lineEditChatInput->text();
        if (!userInput.isEmpty()) {
            QString currentText = ui->textChatDisplay->toPlainText();
            currentText += "\n👤 Vous: " + userInput + "\n";
            currentText += "🤖 Bot: Je suis là pour vous aider avec la gestion des véhicules!\n";
            ui->textChatDisplay->setText(currentText);
            ui->lineEditChatInput->clear();
        }
    });
    connect(ui->btnBackFromChatbot, &QPushButton::clicked, this, &MainWindow::onBackToVehiculeList);

    // Charger les données
    loadVehicules();

    // Afficher page par défaut
    showMissionsPage();
}

//==============================================================================
// DESTRUCTOR
//==============================================================================
MainWindow::~MainWindow()
{
    delete ui;
}

//==============================================================================
// EVENT FILTER
//==============================================================================
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (obj == ui->missions_icon) {
            on_pushButton_8_clicked();
            return true;
        } else if (obj == ui->zone_icon) {
            on_pushButton_5_clicked();
            return true;
        } else if (obj == ui->poubelle_icon) {
            on_pushButton_6_clicked();
            return true;
        } else if (obj == ui->employe_icon) {
            on_pushButton_7_clicked();
            return true;
        } else if (obj == ui->vehicule_icon) {
            on_pushButton_9_clicked();
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

//==============================================================================
// LOAD VEHICULES
//==============================================================================
void MainWindow::loadVehicules()
{
    vehicules.clear();

    vehicules.append(Vehicule(nextVehiculeId++, "Camion Benne", 15.5f, "disponible", "diesel"));
    vehicules.append(Vehicule(nextVehiculeId++, "Camion Compacteur", 20.0f, "en panne", "diesel"));
    vehicules.append(Vehicule(nextVehiculeId++, "Camionnette", 5.5f, "disponible", "essence"));
    vehicules.append(Vehicule(nextVehiculeId++, "Tracteur", 25.0f, "disponible", "diesel"));
    vehicules.append(Vehicule(nextVehiculeId++, "Camion Benne", 18.0f, "en panne", "hybride"));

    allVehicules = vehicules;  // Sauvegarder une copie

    qDebug() << "Loaded" << vehicules.size() << "vehicules";
}

//==============================================================================
// PAGE MANAGEMENT
//==============================================================================

void MainWindow::clearAllPages()
{
    ui->pageVehiculeList->setVisible(false);
    ui->pageAddVehicule->setVisible(false);
    ui->pageSearch->setVisible(false);
    ui->pageSort->setVisible(false);
    ui->pageStats->setVisible(false);
    ui->pageChatbot->setVisible(false);
    ui->tableWidget->setRowCount(0);
    ui->tableSearchWidget->setRowCount(0);
    ui->tableSortWidget->setRowCount(0);
}

void MainWindow::showMissionsPage()
{
    clearAllPages();
    currentPage = PAGE_MISSIONS;
}

void MainWindow::showZonesPage()
{
    clearAllPages();
    currentPage = PAGE_ZONES;
}

void MainWindow::showPoubellePage()
{
    clearAllPages();
    currentPage = PAGE_POUBELLE;
}

void MainWindow::showEmployePage()
{
    clearAllPages();
    currentPage = PAGE_EMPLOYE;
}

void MainWindow::showVehiculePage()
{
    clearAllPages();
    currentPage = PAGE_VEHICULE;

    // Restaurer les données complètes
    vehicules = allVehicules;

    ui->pageVehiculeList->setVisible(true);

    // Disconnect all previous connections
    disconnect(ui->pushButton_2, nullptr, nullptr, nullptr);
    disconnect(ui->btnSearch, nullptr, nullptr, nullptr);
    disconnect(ui->btnSort, nullptr, nullptr, nullptr);
    disconnect(ui->btnStats, nullptr, nullptr, nullptr);
    disconnect(ui->btnExportPDF, nullptr, nullptr, nullptr);
    disconnect(ui->btnChatbot, nullptr, nullptr, nullptr);

    // Connect buttons
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onAddVehiculeClicked);
    connect(ui->btnSearch, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
    connect(ui->btnSort, &QPushButton::clicked, this, &MainWindow::onSortClicked);
    connect(ui->btnStats, &QPushButton::clicked, this, &MainWindow::onStatsClicked);
    connect(ui->btnExportPDF, &QPushButton::clicked, this, &MainWindow::onExportPDFClicked);
    connect(ui->btnChatbot, &QPushButton::clicked, this, &MainWindow::onChatbotClicked);

    setupVehiculeTableHeaders();
    refreshVehiculeTable();
}

void MainWindow::showAddVehiculePage()
{
    clearAllPages();
    currentPage = PAGE_ADD_VEHICULE;

    ui->pageAddVehicule->setVisible(true);

    // Clear form
    ui->comboType->setCurrentIndex(0);
    ui->spinCapacite->setValue(0.0);
    ui->comboEtat->setCurrentIndex(0);
    ui->comboCarburant->setCurrentIndex(0);

    if (editingVehiculeId >= 0) {
        ui->lblFormTitle->setText("Modifier le véhicule");

        // Find vehicle and populate form
        for (const auto& v : qAsConst(allVehicules)) {
            if (v.id() == editingVehiculeId) {
                ui->comboType->setCurrentText(v.type());
                ui->spinCapacite->setValue(v.capaciteMax());
                ui->comboEtat->setCurrentText(v.etat());
                ui->comboCarburant->setCurrentText(v.carburant());
                break;
            }
        }
    } else {
        ui->lblFormTitle->setText("Ajouter un nouveau véhicule");
    }
}

void MainWindow::showSearchPage()
{
    clearAllPages();
    currentPage = PAGE_SEARCH;

    ui->pageSearch->setVisible(true);
    ui->lineEditSearch->clear();

    setupSearchTableHeaders();
    refreshSearchTable();
}

void MainWindow::showSortPage()
{
    clearAllPages();
    currentPage = PAGE_SORT;

    ui->pageSort->setVisible(true);
    ui->comboSortCriteria->setCurrentIndex(0);

    setupSortTableHeaders();
    refreshSortTable();
}

void MainWindow::showStatsPage()
{
    clearAllPages();
    currentPage = PAGE_STATS;

    ui->pageStats->setVisible(true);
    drawStatsChart();
}

void MainWindow::showChatbotPage()
{
    clearAllPages();
    currentPage = PAGE_CHATBOT;

    ui->pageChatbot->setVisible(true);
    ui->textChatDisplay->clear();
    ui->lineEditChatInput->clear();
    ui->textChatDisplay->setText("🤖 Assistant: Bonjour! Comment puis-je vous aider aujourd'hui?\n");
}

//==============================================================================
// VEHICULE TABLE SETUP
//==============================================================================

void MainWindow::setupVehiculeTableHeaders()
{
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels({
        "ID", "Type", "Capacité (m³)", "État", "Carburant", "Opérations", "Email"
    });

    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 150);
    ui->tableWidget->setColumnWidth(4, 120);
    ui->tableWidget->setColumnWidth(5, 180);
    ui->tableWidget->setColumnWidth(6, 120);
}

void MainWindow::setupSearchTableHeaders()
{
    ui->tableSearchWidget->setColumnCount(7);
    ui->tableSearchWidget->setHorizontalHeaderLabels({
        "ID", "Type", "Capacité (m³)", "État", "Carburant", "Opérations", "Email"
    });

    ui->tableSearchWidget->setColumnWidth(0, 80);
    ui->tableSearchWidget->setColumnWidth(1, 200);
    ui->tableSearchWidget->setColumnWidth(2, 150);
    ui->tableSearchWidget->setColumnWidth(3, 150);
    ui->tableSearchWidget->setColumnWidth(4, 120);
    ui->tableSearchWidget->setColumnWidth(5, 180);
    ui->tableSearchWidget->setColumnWidth(6, 120);
}

void MainWindow::setupSortTableHeaders()
{
    ui->tableSortWidget->setColumnCount(7);
    ui->tableSortWidget->setHorizontalHeaderLabels({
        "ID", "Type", "Capacité (m³)", "État", "Carburant", "Opérations", "Email"
    });

    ui->tableSortWidget->setColumnWidth(0, 80);
    ui->tableSortWidget->setColumnWidth(1, 200);
    ui->tableSortWidget->setColumnWidth(2, 150);
    ui->tableSortWidget->setColumnWidth(3, 150);
    ui->tableSortWidget->setColumnWidth(4, 120);
    ui->tableSortWidget->setColumnWidth(5, 180);
    ui->tableSortWidget->setColumnWidth(6, 120);
}

void MainWindow::refreshVehiculeTable()
{
    ui->tableWidget->setRowCount(0);

    for (int i = 0; i < vehicules.size(); ++i) {
        addVehiculeRowWithButtons(ui->tableWidget->rowCount(), vehicules[i]);
    }
}

void MainWindow::refreshSearchTable()
{
    ui->tableSearchWidget->setRowCount(0);

    for (int i = 0; i < allVehicules.size(); ++i) {
        addVehiculeRowToSearchTable(ui->tableSearchWidget->rowCount(), allVehicules[i]);
    }
}

void MainWindow::refreshSortTable()
{
    ui->tableSortWidget->setRowCount(0);

    for (int i = 0; i < allVehicules.size(); ++i) {
        addVehiculeRowToSortTable(ui->tableSortWidget->rowCount(), allVehicules[i]);
    }
}

void MainWindow::addVehiculeRowWithButtons(int row, const Vehicule& vehicule)
{
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setRowHeight(row, 60);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(vehicule.id())));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(vehicule.type()));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(vehicule.capaciteMax(), 'f', 1)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(vehicule.etat()));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(vehicule.carburant()));

    // Operations buttons
    QWidget *buttonWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(buttonWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);
    layout->setAlignment(Qt::AlignCenter);

    QSize buttonSize(35, 35);

    QPushButton *btnUpdate = new QPushButton();
    btnUpdate->setIcon(QIcon(QPixmap(":/images/update.png").scaled(
        buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    btnUpdate->setIconSize(buttonSize);
    btnUpdate->setFixedSize(buttonSize);
    btnUpdate->setFlat(true);
    btnUpdate->setProperty("vehiculeId", vehicule.id());
    connect(btnUpdate, &QPushButton::clicked, this, &MainWindow::onUpdateVehiculeClicked);

    QPushButton *btnDelete = new QPushButton();
    btnDelete->setIcon(QIcon(QPixmap(":/images/delete.png").scaled(
        buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    btnDelete->setIconSize(buttonSize);
    btnDelete->setFixedSize(buttonSize);
    btnDelete->setFlat(true);
    btnDelete->setProperty("vehiculeId", vehicule.id());
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onDeleteVehiculeClicked);

    layout->addWidget(btnUpdate);
    layout->addWidget(btnDelete);

    ui->tableWidget->setCellWidget(row, 5, buttonWidget);

    // Email button
    QPushButton *btnEmail = new QPushButton("📧");
    btnEmail->setFixedSize(50, 40);
    btnEmail->setStyleSheet("QPushButton { background-color: #8e944e; color: white; border-radius: 8px; font-size: 16pt; } QPushButton:hover { background-color: #6d7339; }");
    btnEmail->setProperty("vehiculeId", vehicule.id());
    connect(btnEmail, &QPushButton::clicked, this, &MainWindow::onSendEmailClicked);

    QWidget *emailWidget = new QWidget();
    QHBoxLayout *emailLayout = new QHBoxLayout(emailWidget);
    emailLayout->setContentsMargins(0, 0, 0, 0);
    emailLayout->setAlignment(Qt::AlignCenter);
    emailLayout->addWidget(btnEmail);

    ui->tableWidget->setCellWidget(row, 6, emailWidget);
}

void MainWindow::addVehiculeRowToSearchTable(int row, const Vehicule& vehicule)
{
    ui->tableSearchWidget->insertRow(row);
    ui->tableSearchWidget->setRowHeight(row, 60);

    ui->tableSearchWidget->setItem(row, 0, new QTableWidgetItem(QString::number(vehicule.id())));
    ui->tableSearchWidget->setItem(row, 1, new QTableWidgetItem(vehicule.type()));
    ui->tableSearchWidget->setItem(row, 2, new QTableWidgetItem(QString::number(vehicule.capaciteMax(), 'f', 1)));
    ui->tableSearchWidget->setItem(row, 3, new QTableWidgetItem(vehicule.etat()));
    ui->tableSearchWidget->setItem(row, 4, new QTableWidgetItem(vehicule.carburant()));

    // Operations buttons
    QWidget *buttonWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(buttonWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);
    layout->setAlignment(Qt::AlignCenter);

    QSize buttonSize(35, 35);

    QPushButton *btnUpdate = new QPushButton();
    btnUpdate->setIcon(QIcon(QPixmap(":/images/update.png").scaled(
        buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    btnUpdate->setIconSize(buttonSize);
    btnUpdate->setFixedSize(buttonSize);
    btnUpdate->setFlat(true);
    btnUpdate->setProperty("vehiculeId", vehicule.id());
    connect(btnUpdate, &QPushButton::clicked, this, &MainWindow::onUpdateVehiculeClicked);

    QPushButton *btnDelete = new QPushButton();
    btnDelete->setIcon(QIcon(QPixmap(":/images/delete.png").scaled(
        buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    btnDelete->setIconSize(buttonSize);
    btnDelete->setFixedSize(buttonSize);
    btnDelete->setFlat(true);
    btnDelete->setProperty("vehiculeId", vehicule.id());
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onDeleteVehiculeClicked);

    layout->addWidget(btnUpdate);
    layout->addWidget(btnDelete);

    ui->tableSearchWidget->setCellWidget(row, 5, buttonWidget);

    // Email button
    QPushButton *btnEmail = new QPushButton("📧");
    btnEmail->setFixedSize(50, 40);
    btnEmail->setStyleSheet("QPushButton { background-color: #8e944e; color: white; border-radius: 8px; font-size: 16pt; } QPushButton:hover { background-color: #6d7339; }");
    btnEmail->setProperty("vehiculeId", vehicule.id());
    connect(btnEmail, &QPushButton::clicked, this, &MainWindow::onSendEmailClicked);

    QWidget *emailWidget = new QWidget();
    QHBoxLayout *emailLayout = new QHBoxLayout(emailWidget);
    emailLayout->setContentsMargins(0, 0, 0, 0);
    emailLayout->setAlignment(Qt::AlignCenter);
    emailLayout->addWidget(btnEmail);

    ui->tableSearchWidget->setCellWidget(row, 6, emailWidget);
}

void MainWindow::addVehiculeRowToSortTable(int row, const Vehicule& vehicule)
{
    ui->tableSortWidget->insertRow(row);
    ui->tableSortWidget->setRowHeight(row, 60);

    ui->tableSortWidget->setItem(row, 0, new QTableWidgetItem(QString::number(vehicule.id())));
    ui->tableSortWidget->setItem(row, 1, new QTableWidgetItem(vehicule.type()));
    ui->tableSortWidget->setItem(row, 2, new QTableWidgetItem(QString::number(vehicule.capaciteMax(), 'f', 1)));
    ui->tableSortWidget->setItem(row, 3, new QTableWidgetItem(vehicule.etat()));
    ui->tableSortWidget->setItem(row, 4, new QTableWidgetItem(vehicule.carburant()));

    // Operations buttons
    QWidget *buttonWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(buttonWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);
    layout->setAlignment(Qt::AlignCenter);

    QSize buttonSize(35, 35);

    QPushButton *btnUpdate = new QPushButton();
    btnUpdate->setIcon(QIcon(QPixmap(":/images/update.png").scaled(
        buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    btnUpdate->setIconSize(buttonSize);
    btnUpdate->setFixedSize(buttonSize);
    btnUpdate->setFlat(true);
    btnUpdate->setProperty("vehiculeId", vehicule.id());
    connect(btnUpdate, &QPushButton::clicked, this, &MainWindow::onUpdateVehiculeClicked);

    QPushButton *btnDelete = new QPushButton();
    btnDelete->setIcon(QIcon(QPixmap(":/images/delete.png").scaled(
        buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    btnDelete->setIconSize(buttonSize);
    btnDelete->setFixedSize(buttonSize);
    btnDelete->setFlat(true);
    btnDelete->setProperty("vehiculeId", vehicule.id());
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onDeleteVehiculeClicked);

    layout->addWidget(btnUpdate);
    layout->addWidget(btnDelete);

    ui->tableSortWidget->setCellWidget(row, 5, buttonWidget);

    // Email button
    QPushButton *btnEmail = new QPushButton("📧");
    btnEmail->setFixedSize(50, 40);
    btnEmail->setStyleSheet("QPushButton { background-color: #8e944e; color: white; border-radius: 8px; font-size: 16pt; } QPushButton:hover { background-color: #6d7339; }");
    btnEmail->setProperty("vehiculeId", vehicule.id());
    connect(btnEmail, &QPushButton::clicked, this, &MainWindow::onSendEmailClicked);

    QWidget *emailWidget = new QWidget();
    QHBoxLayout *emailLayout = new QHBoxLayout(emailWidget);
    emailLayout->setContentsMargins(0, 0, 0, 0);
    emailLayout->setAlignment(Qt::AlignCenter);
    emailLayout->addWidget(btnEmail);

    ui->tableSortWidget->setCellWidget(row, 6, emailWidget);
}

//==============================================================================
// VEHICULE ACTIONS
//==============================================================================

void MainWindow::onAddVehiculeClicked()
{
    editingVehiculeId = -1;
    showAddVehiculePage();
}

void MainWindow::onUpdateVehiculeClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int vehiculeId = btn->property("vehiculeId").toInt();
    editingVehiculeId = vehiculeId;
    showAddVehiculePage();
}

void MainWindow::onDeleteVehiculeClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int vehiculeId = btn->property("vehiculeId").toInt();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmation",
        QString("Voulez-vous vraiment supprimer le véhicule ID %1?").arg(vehiculeId),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        // Delete from allVehicules
        for (int i = 0; i < allVehicules.size(); ++i) {
            if (allVehicules[i].id() == vehiculeId) {
                allVehicules.removeAt(i);
                break;
            }
        }

        // Delete from vehicules
        for (int i = 0; i < vehicules.size(); ++i) {
            if (vehicules[i].id() == vehiculeId) {
                vehicules.removeAt(i);
                break;
            }
        }

        // Refresh appropriate table based on current page
        if (currentPage == PAGE_VEHICULE) {
            refreshVehiculeTable();
        } else if (currentPage == PAGE_SEARCH) {
            refreshSearchTable();
        } else if (currentPage == PAGE_SORT) {
            refreshSortTable();
        }

        QMessageBox::information(this, "Suppression", "Véhicule supprimé avec succès!");
    }
}

void MainWindow::onSendEmailClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int vehiculeId = btn->property("vehiculeId").toInt();

    for (const auto& v : qAsConst(allVehicules)) {
        if (v.id() == vehiculeId) {
            QString message = QString("Rapport Véhicule ID %1\n\nType: %2\nCapacité: %3 m³\n"
                                      "État: %4\nCarburant: %5\n\n✅ Email envoyé avec succès!")
                                  .arg(v.id())
                                  .arg(v.type())
                                  .arg(v.capaciteMax())
                                  .arg(v.etat())
                                  .arg(v.carburant());

            QMessageBox::information(this, "Email Envoyé", message);
            break;
        }
    }
}

//==============================================================================
// BUTTON HANDLERS
//==============================================================================

void MainWindow::onSearchClicked()
{
    showSearchPage();
}

void MainWindow::onSortClicked()
{
    showSortPage();
}

void MainWindow::onStatsClicked()
{
    showStatsPage();
}

void MainWindow::onExportPDFClicked()
{
    exportVehiculesToPDF();
}

void MainWindow::onChatbotClicked()
{
    showChatbotPage();
}

//==============================================================================
// FORM ACTIONS
//==============================================================================

void MainWindow::onSaveVehiculeForm()
{
    QString type = ui->comboType->currentText();
    float capacite = ui->spinCapacite->value();
    QString etat = ui->comboEtat->currentText();
    QString carburant = ui->comboCarburant->currentText();

    if (capacite <= 0) {
        QMessageBox::warning(this, "Erreur", "La capacité doit être supérieure à 0!");
        return;
    }

    if (editingVehiculeId >= 0) {
        // Update existing vehicle
        for (int i = 0; i < allVehicules.size(); ++i) {
            if (allVehicules[i].id() == editingVehiculeId) {
                allVehicules[i].setType(type);
                allVehicules[i].setCapaciteMax(capacite);
                allVehicules[i].setEtat(etat);
                allVehicules[i].setCarburant(carburant);
                QMessageBox::information(this, "Succès", "Véhicule modifié avec succès!");
                break;
            }
        }
    } else {
        // Add new vehicle
        Vehicule newVehicule(nextVehiculeId++, type, capacite, etat, carburant);
        allVehicules.append(newVehicule);
        QMessageBox::information(this, "Succès", "Véhicule ajouté avec succès!");
    }

    editingVehiculeId = -1;
    showVehiculePage();
}

void MainWindow::onCancelForm()
{
    editingVehiculeId = -1;
    showVehiculePage();
}

void MainWindow::onApplySearch()
{
    QString searchText = ui->lineEditSearch->text();

    if (searchText.isEmpty()) {
        refreshSearchTable();
        return;
    }

    ui->tableSearchWidget->setRowCount(0);

    for (int i = 0; i < allVehicules.size(); ++i) {
        bool match = allVehicules[i].type().contains(searchText, Qt::CaseInsensitive) ||
                     allVehicules[i].etat().contains(searchText, Qt::CaseInsensitive) ||
                     allVehicules[i].carburant().contains(searchText, Qt::CaseInsensitive);

        if (match) {
            addVehiculeRowToSearchTable(ui->tableSearchWidget->rowCount(), allVehicules[i]);
        }
    }

    if (ui->tableSearchWidget->rowCount() == 0) {
        QMessageBox::information(this, "Recherche", "Aucun véhicule trouvé.");
        refreshSearchTable();
    }
}

void MainWindow::onApplySort()
{
    QString criteria = ui->comboSortCriteria->currentText();

    // Create a temporary copy for sorting
    QList<Vehicule> sortedVehicules = allVehicules;

    if (criteria == "ID") {
        std::sort(sortedVehicules.begin(), sortedVehicules.end(),
                  [](const Vehicule& a, const Vehicule& b) { return a.id() < b.id(); });
    } else if (criteria == "Type") {
        std::sort(sortedVehicules.begin(), sortedVehicules.end(),
                  [](const Vehicule& a, const Vehicule& b) { return a.type() < b.type(); });
    } else if (criteria == "Capacité") {
        std::sort(sortedVehicules.begin(), sortedVehicules.end(),
                  [](const Vehicule& a, const Vehicule& b) { return a.capaciteMax() < b.capaciteMax(); });
    } else if (criteria == "État") {
        std::sort(sortedVehicules.begin(), sortedVehicules.end(),
                  [](const Vehicule& a, const Vehicule& b) { return a.etat() < b.etat(); });
    } else if (criteria == "Carburant") {
        std::sort(sortedVehicules.begin(), sortedVehicules.end(),
                  [](const Vehicule& a, const Vehicule& b) { return a.carburant() < b.carburant(); });
    }

    // Display sorted results
    ui->tableSortWidget->setRowCount(0);
    for (int i = 0; i < sortedVehicules.size(); ++i) {
        addVehiculeRowToSortTable(ui->tableSortWidget->rowCount(), sortedVehicules[i]);
    }
}

void MainWindow::onBackToVehiculeList()
{
    showVehiculePage();
}

//==============================================================================
// UTILITY FUNCTIONS
//==============================================================================

void MainWindow::searchVehicules(const QString& searchText)
{
    QList<Vehicule> filteredVehicules;

    for (const auto& v : qAsConst(allVehicules)) {
        bool match = v.type().contains(searchText, Qt::CaseInsensitive) ||
                     v.etat().contains(searchText, Qt::CaseInsensitive) ||
                     v.carburant().contains(searchText, Qt::CaseInsensitive);

        if (match) {
            filteredVehicules.append(v);
        }
    }

    if (filteredVehicules.isEmpty()) {
        QMessageBox::information(this, "Recherche", "Aucun véhicule trouvé.");
    } else {
        vehicules = filteredVehicules;
    }
}

void MainWindow::sortVehicules(const QString& criteria)
{
    if (criteria == "ID") {
        std::sort(vehicules.begin(), vehicules.end(),
                  [](const Vehicule& a, const Vehicule& b) { return a.id() < b.id(); });
    } else if (criteria == "Type") {
        std::sort(vehicules.begin(), vehicules.end(),
                  [](const Vehicule& a, const Vehicule& b) { return a.type() < b.type(); });
    } else if (criteria == "Capacité") {
        std::sort(vehicules.begin(), vehicules.end(),
                  [](const Vehicule& a, const Vehicule& b) { return a.capaciteMax() < b.capaciteMax(); });
    } else if (criteria == "État") {
        std::sort(vehicules.begin(), vehicules.end(),
                  [](const Vehicule& a, const Vehicule& b) { return a.etat() < b.etat(); });
    } else if (criteria == "Carburant") {
        std::sort(vehicules.begin(), vehicules.end(),
                  [](const Vehicule& a, const Vehicule& b) { return a.carburant() < b.carburant(); });
    }
}

void MainWindow::showVehiculeStats()
{
    int total = allVehicules.size();
    int disponibles = 0;
    int enPanne = 0;

    for (const auto& v : qAsConst(allVehicules)) {
        if (v.etat() == "disponible") disponibles++;
        else if (v.etat() == "en panne") enPanne++;
    }

    QString stats = QString("📊 STATISTIQUES\n\nTotal: %1\nDisponibles: %2\nEn panne: %3")
                        .arg(total).arg(disponibles).arg(enPanne);

    QMessageBox::information(this, "Statistiques", stats);
}

void MainWindow::drawStatsChart()
{
    int total = allVehicules.size();
    int disponibles = 0;
    int enPanne = 0;
    int maintenance = 0;

    for (const auto& v : qAsConst(allVehicules)) {
        if (v.etat() == "disponible") disponibles++;
        else if (v.etat() == "en panne") enPanne++;
        else if (v.etat() == "en maintenance") maintenance++;
    }

    // Create pixmap for drawing
    QPixmap pixmap(600, 400);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw pie chart
    QRect rect(50, 50, 300, 300);

    if (total > 0) {
        int angle = 0;

        // Disponibles (green)
        int disponiblesAngle = (disponibles * 360 * 16) / total;
        painter.setBrush(QColor(142, 148, 78));
        painter.setPen(Qt::white);
        painter.drawPie(rect, angle, disponiblesAngle);
        angle += disponiblesAngle;

        // En panne (red)
        int enPanneAngle = (enPanne * 360 * 16) / total;
        painter.setBrush(QColor(200, 50, 50));
        painter.drawPie(rect, angle, enPanneAngle);
        angle += enPanneAngle;

        // Maintenance (orange)
        int maintenanceAngle = (maintenance * 360 * 16) / total;
        painter.setBrush(QColor(255, 165, 0));
        painter.drawPie(rect, angle, maintenanceAngle);
    }

    // Draw legend
    int legendX = 400;
    int legendY = 100;

    painter.setFont(QFont("Arial", 12, QFont::Bold));

    // Disponibles
    painter.setBrush(QColor(142, 148, 78));
    painter.drawRect(legendX, legendY, 30, 20);
    painter.setPen(QColor(142, 148, 78));
    painter.drawText(legendX + 40, legendY + 15, QString("Disponibles: %1").arg(disponibles));

    // En panne
    legendY += 40;
    painter.setBrush(QColor(200, 50, 50));
    painter.drawRect(legendX, legendY, 30, 20);
    painter.setPen(QColor(200, 50, 50));
    painter.drawText(legendX + 40, legendY + 15, QString("En panne: %1").arg(enPanne));

    // Maintenance
    legendY += 40;
    painter.setBrush(QColor(255, 165, 0));
    painter.drawRect(legendX, legendY, 30, 20);
    painter.setPen(QColor(255, 165, 0));
    painter.drawText(legendX + 40, legendY + 15, QString("Maintenance: %1").arg(maintenance));

    painter.end();

    ui->lblStatsChart->setPixmap(pixmap);
}

void MainWindow::exportVehiculesToPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter",
                                                    "vehicules.html", "HTML Files (*.html)");

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le fichier!");
        return;
    }

    QString html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><style>"
                   "body{font-family:Arial;margin:40px;}h1{color:#8e944e;text-align:center;}"
                   "table{width:100%;border-collapse:collapse;margin-top:20px;}"
                   "th,td{border:1px solid #8e944e;padding:12px;text-align:left;}"
                   "th{background-color:#8e944e;color:white;}</style></head><body>"
                   "<h1>Liste des Véhicules</h1><table>"
                   "<tr><th>ID</th><th>Type</th><th>Capacité</th><th>État</th><th>Carburant</th></tr>";

    for (const auto& v : qAsConst(allVehicules)) {
        html += QString("<tr><td>%1</td><td>%2</td><td>%3 m³</td><td>%4</td><td>%5</td></tr>")
                    .arg(v.id())
                    .arg(v.type())
                    .arg(v.capaciteMax(), 0, 'f', 1)
                    .arg(v.etat())
                    .arg(v.carburant());
    }

    html += "</table></body></html>";

    QTextStream out(&file);
    out << html;
    file.close();

    QMessageBox::information(this, "Export", "Fichier HTML créé avec succès!\nOuvrez-le dans un navigateur.");
}

//==============================================================================
// MISSIONS (EXAMPLE)
//==============================================================================

void MainWindow::addRowWithButtons(int row, QString missionNum, QString zone,
                                   QString workers, QString startTime, QString endTime)
{
    // This is just an example - missions page is not fully implemented
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setRowHeight(row, 55);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(missionNum));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(zone));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(workers));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(startTime));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(endTime));
}

//==============================================================================
// SIDEBAR ANIMATION
//==============================================================================

void MainWindow::on_pushButton_clicked()
{
    static bool isCollapsed = false;

    if (!isCollapsed) {
        ui->pushButton->setText(">");
        ui->pushButton_5->setVisible(false);
        ui->pushButton_6->setVisible(false);
        ui->pushButton_7->setVisible(false);
        ui->pushButton_8->setVisible(false);
        ui->pushButton_9->setVisible(false);
    } else {
        ui->pushButton->setText("<");
        ui->pushButton_5->setVisible(true);
        ui->pushButton_6->setVisible(true);
        ui->pushButton_7->setVisible(true);
        ui->pushButton_8->setVisible(true);
        ui->pushButton_9->setVisible(true);
    }

    isCollapsed = !isCollapsed;
}

//==============================================================================
// NAVIGATION SLOTS
//==============================================================================

void MainWindow::on_pushButton_5_clicked()
{
    showZonesPage();
}

void MainWindow::on_pushButton_6_clicked()
{
    showPoubellePage();
}

void MainWindow::on_pushButton_7_clicked()
{
    showEmployePage();
}

void MainWindow::on_pushButton_8_clicked()
{
    showMissionsPage();
}

void MainWindow::on_pushButton_9_clicked()
{
    showVehiculePage();
}
