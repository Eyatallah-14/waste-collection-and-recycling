#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "employepages.h"
#include "zonepages.h"
#include "gestionpoubellepages.h"
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
#include <QPainterPath>
#include <algorithm>
#include <cmath>

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
    ui->comboGroupStatus->addItem("Tous les statuts");       // default = show all
    ui->comboGroupStatus->addItem("Planifiée");
    ui->comboGroupStatus->addItem("En cours");
    ui->comboGroupStatus->addItem("Terminée");
    ui->comboGroupStatus->addItem("Annulée");

    // Configuration des tableaux
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

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
    connect(ui->btnEstimerFin, &QPushButton::clicked, this, &MainWindow::on_btnEstimerFin_clicked);
    
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

    // Populate combo box for sort (dans l'interface principale)
    ui->comboSortCriteria->addItems({"ID", "Type", "Capacité", "État", "Carburant"});

    // Connect form buttons
    connect(ui->btnSaveVehicule, &QPushButton::clicked, this, &MainWindow::onSaveVehiculeForm);
    connect(ui->btnCancelForm, &QPushButton::clicked, this, &MainWindow::onCancelForm);

    // Connect stats button
    connect(ui->btnBackFromStats, &QPushButton::clicked, this, &MainWindow::showVehiculePage);

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
    connect(ui->btnBackFromChatbot, &QPushButton::clicked, this, &MainWindow::showVehiculePage);

    // ─── Missions connections ───────────────────────────────────────────────
    connect(ui->btnAddMission, &QPushButton::clicked, this, &MainWindow::onAddMissionClicked);
    connect(ui->btnSaveMission, &QPushButton::clicked, this, &MainWindow::onSaveMissionForm);
    connect(ui->btnCancelMission, &QPushButton::clicked, this, &MainWindow::onCancelMissionForm);
    connect(ui->btnCloseForm, &QPushButton::clicked, this, &MainWindow::onCloseMissionForm);

    // Charger les données
    loadVehicules();
    loadMissions();

    // Initialize employee pages widget
    employePages = new EmployePages(this);
    employePages->setGeometry(230, 0, 1170, 850);
    employePages->setVisible(false);

    // Initialize zone pages widget
    zonePages = new ZonePages(this);
    zonePages->setGeometry(230, 0, 1170, 850);
    zonePages->setVisible(false);

    // Initialize poubelle pages widget
    poubellePages = new GestionPoubellePage(this);
    poubellePages->setGeometry(230, 0, 1170, 850);
    poubellePages->setVisible(false);
    zonePages->hide();
    ui->checkSortByZone->setStyleSheet(
    "QCheckBox { color: black; }"
    "QCheckBox::indicator { width: 20px; height: 20px; }"
    "QCheckBox::indicator:unchecked { background: white; border: 2px solid green; }"
    "QCheckBox::indicator:checked { background: green; border: 2px solid green; }"
);

    // Afficher page par défaut
    showMissionsPage();
}

//==============================================================================
// DESTRUCTOR
//==============================================================================
MainWindow::~MainWindow()
{
    delete employePages;
    delete zonePages;
    delete poubellePages;
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

    allVehicules = vehicules; // Sauvegarder une copie

    qDebug() << "Loaded" << vehicules.size() << "vehicules";
}

//==============================================================================
// LOAD MISSIONS (TEST DATA)
//==============================================================================
void MainWindow::loadMissions()
{
    missions.clear();

    missions.append(Mission(nextMissionId++, "2025-02-10", "07:30", "13:00", "Rue France", "1,4,6"));
    missions.append(Mission(nextMissionId++, "2025-02-11", "08:00", "16:30", "Avenue Habib Bourguiba", "2,5"));
    missions.append(Mission(nextMissionId++, "2025-02-12", "06:45", "14:15", "Lac 1", "3"));

    qDebug() << "Loaded" << missions.size() << "missions";
}

//==============================================================================
// PAGE MANAGEMENT
//==============================================================================

void MainWindow::clearAllPages()
{
    ui->pageVehiculeList->setVisible(false);
    ui->pageAddVehicule->setVisible(false);
    ui->pageStats->setVisible(false);
    ui->pageChatbot->setVisible(false);
    ui->pageMissions->setVisible(false);
    ui->pageAddMission->setVisible(false);
    employePages->setVisible(false);

    ui->tableWidget->setRowCount(0);
}

void MainWindow::on_btnApplySortGroup_clicked()
{
    QList<Mission> filtered = missions;

    // Filter by status (combo)
    QString selectedStatus = ui->comboGroupStatus->currentText();
    if (selectedStatus != "Tous les statuts") {
        filtered.clear();
        for (const auto& m : missions) {
            // Temporary fake status - replace with real m.statut() when you add the field
            QString fakeStatut = "Planifiée";
            if (fakeStatut == selectedStatus) {
                filtered.append(m);
            }
        }
    }

    // Sort by ID if checkbox is checked
    if (ui->checkSortByZone->isChecked()) {
        std::sort(filtered.begin(), filtered.end(),
                  [](const Mission& a, const Mission& b) {
                      return a.id() < b.id(); // ascending ID
                  });
    }

    // Refresh table
    ui->tableMissions->setRowCount(0);
    int row = 0;
    for (const auto& m : filtered) {
        addMissionRowWithButtons(row++, m);
    }
}

void MainWindow::showMissionsPage()
{
    clearAllPages();
    currentPage = PAGE_MISSIONS;
    ui->pageMissions->setVisible(true);

    setupMissionsTableHeaders();
    refreshMissionsTable();

    // === NEW COOL STATS + CHART + TRANSITION ===
    ui->statsContainer->setVisible(false);   // start hidden

    // Fade + scale animation
    QPropertyAnimation *anim = new QPropertyAnimation(ui->statsContainer, "geometry");
    anim->setDuration(700);
    anim->setEasingCurve(QEasingCurve::OutCubic);

    QRect startRect = ui->statsContainer->geometry();
    startRect.setWidth(startRect.width() * 0.95);
    startRect.setHeight(startRect.height() * 0.95);

    anim->setStartValue(startRect);
    anim->setEndValue(ui->statsContainer->geometry());

    QPropertyAnimation *fade = new QPropertyAnimation(ui->statsContainer, "windowOpacity");
    fade->setDuration(700);
    fade->setStartValue(0.0);
    fade->setEndValue(1.0);

    anim->start(QAbstractAnimation::DeleteWhenStopped);
    fade->start(QAbstractAnimation::DeleteWhenStopped);

    ui->statsContainer->setVisible(true);

    // Draw the chart
    drawMissionsChart();
}

void MainWindow::drawMissionsChart()
{
    // Example data - replace with your real stats
    int total = missions.size();
    int today = 0;
    int planned = 0;
    int ongoing = 0;
    int completed = 0;

    QDate todayDate = QDate::currentDate();
    for (const auto& m : missions) {
        QDate d = QDate::fromString(m.date(), "yyyy-MM-dd");
        if (d == todayDate) today++;
        // Add your real status logic here
        if (m.statutZone().contains("Planifiée")) planned++;
        else if (m.statutZone().contains("En cours")) ongoing++;
        else completed++;
    }

    QPixmap pix(1010, 220);
    pix.fill(Qt::transparent);
    QPainter painter(&pix);
    painter.setRenderHint(QPainter::Antialiasing);

    // Background gradient
    QLinearGradient bgGrad(0, 0, 0, 220);
    bgGrad.setColorAt(0, QColor(40, 40, 70));
    bgGrad.setColorAt(1, QColor(20, 20, 40));
    painter.fillRect(pix.rect(), bgGrad);

    // Draw simple bar chart
    int barWidth = 180;
    int spacing = 40;
    int maxHeight = 160;
    int baseY = 180;

    struct Bar { QString label; int value; QColor color; };
    QVector<Bar> bars = {
        {"Total", total, QColor(100, 180, 255)},
        {"Today", today, QColor(100, 255, 200)},
        {"Planned", planned, QColor(255, 180, 100)},
        {"Ongoing", ongoing, QColor(255, 120, 120)},
        {"Completed", completed, QColor(120, 255, 120)}
    };

    int x = 50;
    for (const auto& bar : bars) {
        int h = (bar.value * maxHeight) / qMax(1, total); // scale
        QLinearGradient grad(x, baseY - h, x, baseY);
        grad.setColorAt(0, bar.color.lighter(120));
        grad.setColorAt(1, bar.color);
        painter.setBrush(grad);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(x, baseY - h, barWidth, h, 12, 12);

        // Label value
        painter.setPen(QColor(220, 220, 255));
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        painter.drawText(QRect(x, baseY - h - 30, barWidth, 30), Qt::AlignCenter, QString::number(bar.value));

        // Bottom label
        painter.drawText(QRect(x, baseY + 10, barWidth, 30), Qt::AlignCenter, bar.label);

        x += barWidth + spacing;
    }

    ui->lblMissionsChart->setPixmap(pix);
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
    poubellePages->setVisible(true);
}

void MainWindow::showEmployePage()
{
    clearAllPages();
    currentPage = PAGE_EMPLOYE;
    employePages->setVisible(true);
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
    disconnect(ui->lineEditSearch, nullptr, nullptr, nullptr);
    disconnect(ui->btnApplySearch, nullptr, nullptr, nullptr);
    disconnect(ui->comboSortCriteria, nullptr, nullptr, nullptr);
    disconnect(ui->btnApplySort, nullptr, nullptr, nullptr);
    disconnect(ui->btnStats, nullptr, nullptr, nullptr);
    disconnect(ui->btnExportPDF, nullptr, nullptr, nullptr);
    disconnect(ui->btnChatbot, nullptr, nullptr, nullptr);

    // Connect buttons - TRI UNIQUEMENT SUR CLIC DU BOUTON
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onAddVehiculeClicked);
    connect(ui->lineEditSearch, &QLineEdit::returnPressed, this, &MainWindow::onApplySearch);
    connect(ui->btnApplySearch, &QPushButton::clicked, this, &MainWindow::onApplySearch);
    // PAS DE CONNEXION sur comboSortCriteria::currentIndexChanged - tri uniquement sur clic bouton
    connect(ui->btnApplySort, &QPushButton::clicked, this, &MainWindow::onApplySort);
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
        for (const auto& v : std::as_const(allVehicules)) {
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

void MainWindow::showAddMissionPage()
{
    clearAllPages();
    currentPage = PAGE_ADD_MISSION;
    ui->pageAddMission->setVisible(true);

    // Reset form
    ui->calendarMission->setSelectedDate(QDate::currentDate());
    ui->timeEditDebut->setTime(QTime(8, 0));
    ui->timeEditFin->setTime(QTime(16, 0));
    ui->lineEditZone->clear();
    ui->lineEditEmployes->clear();

    if (editingMissionId >= 0) {
        ui->lblMissionFormTitle->setText("Modifier la mission");

        for (const auto& m : std::as_const(missions)) {
            if (m.id() == editingMissionId) {
                ui->calendarMission->setSelectedDate(QDate::fromString(m.date(), "yyyy-MM-dd"));
                ui->timeEditDebut->setTime(QTime::fromString(m.heureDebut(), "HH:mm"));
                ui->timeEditFin->setTime(QTime::fromString(m.heureFin(), "HH:mm"));
                ui->lineEditZone->setText(m.statutZone());
                ui->lineEditEmployes->setText(m.listeEmployes());
                break;
            }
        }
    } else {
        ui->lblMissionFormTitle->setText("Ajouter une nouvelle mission");
    }
}


//==============================================================================
// MISSIONS TABLE SETUP
//==============================================================================
void MainWindow::setupMissionsTableHeaders()
{
    ui->tableMissions->setColumnCount(7);
    ui->tableMissions->setHorizontalHeaderLabels({"ID", "Date", "Heure Début", "Heure Fin", "Zone", "Statut", "Employés", "Actions"});

    ui->tableMissions->setColumnWidth(0, 100);
    ui->tableMissions->setColumnWidth(1, 150);
    ui->tableMissions->setColumnWidth(2, 120);
    ui->tableMissions->setColumnWidth(3, 120);
    ui->tableMissions->setColumnWidth(4, 200);
    ui->tableMissions->setColumnWidth(5, 180);
    ui->tableMissions->setColumnWidth(6, 180);

    ui->tableMissions->setShowGrid(true);
    ui->tableMissions->verticalHeader()->setVisible(false);
    ui->tableMissions->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableMissions->setFocusPolicy(Qt::NoFocus);
    ui->tableMissions->setSelectionMode(QAbstractItemView::NoSelection);
}

void MainWindow::refreshMissionsTable()
{
    ui->tableMissions->setRowCount(0);
    for (const auto& m : missions) {
        addMissionRowWithButtons(ui->tableMissions->rowCount(), m);
    }
}

void MainWindow::on_btnSearchMission_clicked()
{
    QString text = ui->lineSearchMission->text().trimmed().toLower();
    ui->tableMissions->setRowCount(0);
    int row = 0;

    for (const auto& m : missions) {
        if (text.isEmpty() ||
            m.date().toLower().contains(text) ||
            m.statutZone().toLower().contains(text) ||
            m.listeEmployes().toLower().contains(text)) {
            addMissionRowWithButtons(row++, m);
        }
    }
}

void MainWindow::addMissionRowWithButtons(int row, const Mission& mission)
{
    ui->tableMissions->insertRow(row);
    ui->tableMissions->setRowHeight(row, 60);

    ui->tableMissions->setItem(row, 0, new QTableWidgetItem(QString::number(mission.id())));
    ui->tableMissions->setItem(row, 1, new QTableWidgetItem(mission.date()));
    ui->tableMissions->setItem(row, 2, new QTableWidgetItem(mission.heureDebut()));
    ui->tableMissions->setItem(row, 3, new QTableWidgetItem(mission.heureFin()));
    ui->tableMissions->setItem(row, 4, new QTableWidgetItem(mission.statutZone()));
    ui->tableMissions->setItem(row, 5, new QTableWidgetItem("Planifiée"));
    ui->tableMissions->setItem(row, 6, new QTableWidgetItem(mission.listeEmployes()));

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
    btnUpdate->setProperty("missionId", mission.id());
    connect(btnUpdate, &QPushButton::clicked, this, &MainWindow::onUpdateMissionClicked);

    QPushButton *btnDelete = new QPushButton();
    btnDelete->setIcon(QIcon(QPixmap(":/images/delete.png").scaled(
        buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    btnDelete->setIconSize(buttonSize);
    btnDelete->setFixedSize(buttonSize);
    btnDelete->setFlat(true);
    btnDelete->setProperty("missionId", mission.id());
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onDeleteMissionClicked);

    layout->addWidget(btnUpdate);
    layout->addWidget(btnDelete);

    ui->tableMissions->setCellWidget(row, 6, buttonWidget);
}

//==============================================================================
// MISSIONS ACTIONS
//==============================================================================

void MainWindow::onAddMissionClicked()
{
    editingMissionId = -1;

    // Reset form for new mission
    ui->calendarMission->setSelectedDate(QDate::currentDate());
    ui->timeEditDebut->setTime(QTime(8, 0));
    ui->timeEditFin->setTime(QTime(9, 0));
    ui->lineEditZone->clear();
    ui->lineEditEmployes->clear();

    // Update title
    ui->lblMissionFormTitle->setText("Ajouter une Mission");

    // Show form, hide list
    ui->pageMissions->setVisible(false);
    ui->pageAddMission->setVisible(true);
}

void MainWindow::onUpdateMissionClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    editingMissionId = btn->property("missionId").toInt();

    // Fill form with existing mission data
    for (const auto& m : missions) {
        if (m.id() == editingMissionId) {
            ui->calendarMission->setSelectedDate(QDate::fromString(m.date(), "yyyy-MM-dd"));
            ui->timeEditDebut->setTime(QTime::fromString(m.heureDebut(), "HH:mm"));
            ui->timeEditFin->setTime(QTime::fromString(m.heureFin(), "HH:mm"));
            ui->lineEditZone->setText(m.statutZone());
            ui->lineEditEmployes->setText(m.listeEmployes());
            break;
        }
    }

    // Update title with ID
    ui->lblMissionFormTitle->setText("Modifier la Mission #" + QString::number(editingMissionId));

    // Show form, hide list
    ui->pageMissions->setVisible(false);
    ui->pageAddMission->setVisible(true);
}

void MainWindow::onDeleteMissionClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int id = btn->property("missionId").toInt();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmation",
        QString("Voulez-vous vraiment supprimer la mission ID %1 ?").arg(id),
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes) {
        for (int i = 0; i < missions.size(); ++i) {
            if (missions[i].id() == id) {
                missions.removeAt(i);
                break;
            }
        }
        refreshMissionsTable();
        QMessageBox::information(this, "Succès", "Mission supprimée.");
    }
}

void MainWindow::onSaveMissionForm()
{
    QString date = ui->calendarMission->selectedDate().toString("yyyy-MM-dd");
    QString heureDebut = ui->timeEditDebut->time().toString("HH:mm");
    QString heureFin = ui->timeEditFin->time().toString("HH:mm");
    QString zone = ui->lineEditZone->text().trimmed();
    QString employes = ui->lineEditEmployes->text().trimmed();

    if (zone.isEmpty() || employes.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir la zone et les employés.");
        return;
    }

    if (ui->timeEditDebut->time() >= ui->timeEditFin->time()) {
        QMessageBox::warning(this, "Erreur", "L'heure de fin doit être après l'heure de début.");
        return;
    }

    if (editingMissionId >= 0) {
        // Update existing mission
        for (auto &m : missions) {
            if (m.id() == editingMissionId) {
                m.setDate(date);
                m.setHeureDebut(heureDebut);
                m.setHeureFin(heureFin);
                m.setStatutZone(zone);
                m.setListeEmployes(employes);
                break;
            }
        }
        QMessageBox::information(this, "Succès", "Mission modifiée avec succès.");
    } else {
        // Add new mission
        missions.append(Mission(nextMissionId++, date, heureDebut, heureFin, zone, employes));
        QMessageBox::information(this, "Succès", "Mission ajoutée avec succès.");
    }

    editingMissionId = -1;
    ui->pageAddMission->setVisible(false);
    ui->pageMissions->setVisible(true);
    refreshMissionsTable();
}

void MainWindow::onCancelMissionForm()
{
    editingMissionId = -1;
    ui->pageAddMission->setVisible(false);
    ui->pageMissions->setVisible(true); 
}

void MainWindow::onCloseMissionForm()
{
    onCancelMissionForm();
}

void MainWindow::on_btnEstimerFin_clicked()
{
    QTime debut = ui->timeEditDebut->time();
    if (!debut.isValid()) {
        QMessageBox::warning(this, "Erreur", "Veuillez d'abord sélectionner une heure de début.");
        return;
    }

    QTime fin = debut.addSecs(3600); // +1 heure

    // Create non-modal popup for "Estimation en cours..."
    QMessageBox *waitMsg = new QMessageBox(this);
    waitMsg->setIcon(QMessageBox::Information);
    waitMsg->setWindowTitle("Estimation");
    waitMsg->setText("Estimation en cours...");
    waitMsg->setStandardButtons(QMessageBox::NoButton);
    waitMsg->setAttribute(Qt::WA_DeleteOnClose);
    waitMsg->setModal(false);
    waitMsg->show();

    // Timer to simulate delay and set the time
    QTimer::singleShot(1500, this, [=]() mutable {
        ui->timeEditFin->setTime(fin);
        waitMsg->close();
        QMessageBox::information(this, "Estimation terminée",
                                 "Heure de fin estimée : " + fin.toString("HH:mm"));
    });
}

//==============================================================================
// VEHICULE TABLE SETUP (6 colonnes)
//==============================================================================
void MainWindow::setupVehiculeTableHeaders()
{
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels({
        "ID", "Type", "Capacité (m³)", "État", "Carburant", "Opérations"
    });
    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 150);
    ui->tableWidget->setColumnWidth(4, 120);
    ui->tableWidget->setColumnWidth(5, 250);
}

void MainWindow::refreshVehiculeTable()
{
    ui->tableWidget->setRowCount(0);

    for (int i = 0; i < vehicules.size(); ++i) {
        addVehiculeRowWithButtons(ui->tableWidget->rowCount(), vehicules[i]);
    }
}

//==============================================================================
// VEHICULE ROW (Email intégré dans Opérations)
//==============================================================================
void MainWindow::addVehiculeRowWithButtons(int row, const Vehicule& vehicule)
{
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setRowHeight(row, 60);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(vehicule.id())));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(vehicule.type()));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(vehicule.capaciteMax(), 'f', 1)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(vehicule.etat()));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(vehicule.carburant()));

    // Operations buttons (3 boutons : modifier, supprimer, email)
    QWidget *buttonWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(buttonWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);
    layout->setAlignment(Qt::AlignCenter);

    QSize buttonSize(35, 35);

    // Bouton Modifier
    QPushButton *btnUpdate = new QPushButton();
    btnUpdate->setIcon(QIcon(QPixmap(":/images/update.png").scaled(
        buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    btnUpdate->setIconSize(buttonSize);
    btnUpdate->setFixedSize(buttonSize);
    btnUpdate->setFlat(true);
    btnUpdate->setProperty("vehiculeId", vehicule.id());
    connect(btnUpdate, &QPushButton::clicked, this, &MainWindow::onUpdateVehiculeClicked);

    // Bouton Supprimer
    QPushButton *btnDelete = new QPushButton();
    btnDelete->setIcon(QIcon(QPixmap(":/images/delete.png").scaled(
        buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    btnDelete->setIconSize(buttonSize);
    btnDelete->setFixedSize(buttonSize);
    btnDelete->setFlat(true);
    btnDelete->setProperty("vehiculeId", vehicule.id());
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onDeleteVehiculeClicked);

    // Bouton Email (dans la même colonne)
    QPushButton *btnEmail = new QPushButton("📧");
    btnEmail->setFixedSize(35, 35);
    btnEmail->setStyleSheet("QPushButton { background-color: #8e944e; color: white; border-radius: 8px; font-size: 14pt; } QPushButton:hover { background-color: #6d7339; }");
    btnEmail->setProperty("vehiculeId", vehicule.id());
    connect(btnEmail, &QPushButton::clicked, this, &MainWindow::onSendEmailClicked);

    layout->addWidget(btnUpdate);
    layout->addWidget(btnDelete);
    layout->addWidget(btnEmail);

    ui->tableWidget->setCellWidget(row, 5, buttonWidget);
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

        refreshVehiculeTable();
        QMessageBox::information(this, "Succès", "Véhicule supprimé avec succès!");
    }
}

void MainWindow::onSendEmailClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int vehiculeId = btn->property("vehiculeId").toInt();

    bool ok;
    QString email = QInputDialog::getText(this, "Envoyer Email",
                                          "Adresse email du destinataire:",
                                          QLineEdit::Normal,
                                          "contact@example.com", &ok);

    if (ok && !email.isEmpty()) {
        // Trouver le véhicule
        QString vehiculeInfo;
        for (const auto& v : std::as_const(allVehicules)) {
            if (v.id() == vehiculeId) {
                vehiculeInfo = QString("Type: %1\nCapacité: %2 m³\nÉtat: %3\nCarburant: %4")
                                   .arg(v.type())
                                   .arg(v.capaciteMax(), 0, 'f', 1)
                                   .arg(v.etat())
                                   .arg(v.carburant());
                break;
            }
        }

        QMessageBox::information(this, "Email Envoyé",
                                 QString("Email envoyé à: %1\n\nVéhicule ID %2:\n%3")
                                 .arg(email)
                                 .arg(vehiculeId)
                                 .arg(vehiculeInfo));
    }
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

  //==============//
 // FORM ACTIONS //
//==============//

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

//==============================================================================
// RECHERCHE ET TRI (dans la même interface)
//==============================================================================

void MainWindow::onApplySearch()
{
    QString searchText = ui->lineEditSearch->text().trimmed();

    if (searchText.isEmpty()) {
        // Restaurer tous les véhicules
        vehicules = allVehicules;
    } else {
        // Filtrer les véhicules
        vehicules.clear();
        for (int i = 0; i < allVehicules.size(); ++i) {
            bool match = allVehicules[i].type().contains(searchText, Qt::CaseInsensitive) ||
                         allVehicules[i].etat().contains(searchText, Qt::CaseInsensitive) ||
                         allVehicules[i].carburant().contains(searchText, Qt::CaseInsensitive) ||
                         QString::number(allVehicules[i].id()).contains(searchText);

            if (match) {
                vehicules.append(allVehicules[i]);
            }
        }

        if (vehicules.isEmpty()) {
            QMessageBox::information(this, "Recherche", "Aucun véhicule trouvé.");
            vehicules = allVehicules;
        }
    }

    refreshVehiculeTable();
}

void MainWindow::onApplySort()
{
    QString criteria = ui->comboSortCriteria->currentText();

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

    refreshVehiculeTable();
}

//==============================================================================
// UTILITY FUNCTIONS
//==============================================================================

void MainWindow::showVehiculeStats()
{
    int total = allVehicules.size();
    int disponibles = 0;
    int enPanne = 0;

    for (const auto& v : std::as_const(allVehicules)) {
        if (v.etat() == "disponible") disponibles++;
        else if (v.etat() == "en panne") enPanne++;
    }

    QString stats = QString("📊 STATISTIQUES\n\nTotal: %1\nDisponibles: %2\nEn panne: %3")
                        .arg(total).arg(disponibles).arg(enPanne);

    QMessageBox::information(this, "Statistiques", stats);
}

//==============================================================================
// GRAPHIQUE CIRCULAIRE (PIE CHART) - CORRIGÉ
//==============================================================================
void MainWindow::drawStatsChart()
{
    int total = allVehicules.size();
    int disponibles = 0;
    int enPanne = 0;
    int maintenance = 0;

    for (const auto& v : std::as_const(allVehicules)) {
        if (v.etat() == "disponible") disponibles++;
        else if (v.etat() == "en panne") enPanne++;
        else if (v.etat() == "en maintenance") maintenance++;
    }

    // Créer un pixmap plus grand pour afficher toute la légende
    QPixmap pixmap(750, 520);
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Title
    QFont titleFont("Arial", 16, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(QColor(50, 50, 50));
    painter.drawText(QRect(0, 20, 750, 30), Qt::AlignCenter, "Statistiques des Véhicules");

    // Dessiner le graphique circulaire (pie chart)
    int centerX = 220;
    int centerY = 270;
    int radius = 140;

    // Définir les couleurs
    QColor colorDisponible(50, 200, 50);
    QColor colorPanne(200, 50, 50);
    QColor colorMaintenance(255, 165, 0);

    // Calculer les angles (360 degrés = 5760 (16ème de degré))
    double totalCount = disponibles + enPanne + maintenance;
    if (totalCount == 0) totalCount = 1; // Éviter division par zéro

    int angleDisponible = static_cast<int>((disponibles / totalCount) * 360 * 16);
    int anglePanne = static_cast<int>((enPanne / totalCount) * 360 * 16);
    int angleMaintenance = static_cast<int>((maintenance / totalCount) * 360 * 16);

    // Point de départ
    int startAngle = 90 * 16; // Commencer en haut (90 degrés)

    QRect pieRect(centerX - radius, centerY - radius, radius * 2, radius * 2);

    // Dessiner les secteurs
    // Disponibles
    if (disponibles > 0) {
        painter.setBrush(colorDisponible);
        painter.setPen(QPen(Qt::white, 3));
        painter.drawPie(pieRect, startAngle, angleDisponible);
        startAngle += angleDisponible;
    }

    // En panne
    if (enPanne > 0) {
        painter.setBrush(colorPanne);
        painter.setPen(QPen(Qt::white, 3));
        painter.drawPie(pieRect, startAngle, anglePanne);
        startAngle += anglePanne;
    }

    // Maintenance
    if (maintenance > 0) {
        painter.setBrush(colorMaintenance);
        painter.setPen(QPen(Qt::white, 3));
        painter.drawPie(pieRect, startAngle, angleMaintenance);
    }

    // Légende - repositionnée pour être visible
    int legendX = 440;
    int legendY = 160;
    QFont legendFont("Arial", 12, QFont::Bold);
    painter.setFont(legendFont);

    // Disponibles
    painter.setBrush(colorDisponible);
    painter.setPen(Qt::NoPen);
    painter.drawRect(legendX, legendY, 35, 25);
    painter.setPen(QColor(50, 50, 50));
    QString dispText = QString("Disponibles: %1 (%2%)")
                           .arg(disponibles)
                           .arg(QString::number(disponibles * 100.0 / total, 'f', 1));
    painter.drawText(legendX + 45, legendY + 18, dispText);

    // En panne
    legendY += 50;
    painter.setBrush(colorPanne);
    painter.setPen(Qt::NoPen);
    painter.drawRect(legendX, legendY, 35, 25);
    painter.setPen(QColor(50, 50, 50));
    QString panneText = QString("En panne: %1 (%2%)")
                            .arg(enPanne)
                            .arg(QString::number(enPanne * 100.0 / total, 'f', 1));
    painter.drawText(legendX + 45, legendY + 18, panneText);

    // Maintenance
    legendY += 50;
    painter.setBrush(colorMaintenance);
    painter.setPen(Qt::NoPen);
    painter.drawRect(legendX, legendY, 35, 25);
    painter.setPen(QColor(50, 50, 50));
    QString maintText = QString("Maintenance: %1 (%2%)")
                            .arg(maintenance)
                            .arg(QString::number(maintenance * 100.0 / total, 'f', 1));
    painter.drawText(legendX + 45, legendY + 18, maintText);

    // Total au centre du cercle
    painter.setPen(QColor(50, 50, 50));
    QFont totalFont("Arial", 22, QFont::Bold);
    painter.setFont(totalFont);
    painter.drawText(QRect(centerX - 60, centerY - 25, 120, 50), Qt::AlignCenter, QString("Total\n%1").arg(total));

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

    for (const auto& v : std::as_const(allVehicules)) {
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
    // Cacher toutes les pages véhicule et missions
    clearAllPages();

    if (employePages) {
        employePages->hide();
    }
    
    if (poubellePages) {
        poubellePages->hide();
    }

    // Afficher la page Zone
    if (zonePages) {
        zonePages->show();
        zonePages->raise();
    }

    currentPage = PAGE_ZONES;
}

void MainWindow::on_pushButton_6_clicked()  // Poubelle
{
    if (zonePages) {
        zonePages->hide();
    }
    if (employePages) {
        employePages->hide();
    }
    if (poubellePages) {
        poubellePages->show();
    }
    clearAllPages();
    showPoubellePage();
}

void MainWindow::on_pushButton_7_clicked()  // Employe
{
    if (zonePages) {
        zonePages->hide();
    }
    if (poubellePages) {
        poubellePages->hide();
    }
    clearAllPages();
    if (employePages) {
        employePages->show();
        employePages->raise();
    }
    currentPage = PAGE_EMPLOYE;
}

void MainWindow::on_pushButton_8_clicked()  // Missions
{
    if (zonePages) {
        zonePages->hide();
    }
    if (employePages) {
        employePages->hide();
    }
    if (poubellePages) {
        poubellePages->hide();
    }
    clearAllPages();
    showMissionsPage();
}

void MainWindow::on_pushButton_9_clicked()  // Vehicule
{
    if (zonePages) {
        zonePages->hide();
    }
    if (employePages) {
        employePages->hide();
    }
    if (poubellePages) {
        poubellePages->hide();
    }
    clearAllPages();
    showVehiculePage();
}
