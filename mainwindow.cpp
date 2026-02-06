#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QIcon>
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QEvent>

#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>


//==============================================================================
// CONSTRUCTOR - Initialize the main window and setup UI components
//==============================================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentPage(PAGE_MISSIONS)
{
    ui->setupUi(this);

    //--------------------------------------------------------------------------
    // TABLE WIDGET CONFIGURATION
    //--------------------------------------------------------------------------
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    ui->tableWidget->setColumnWidth(0, 180);
    ui->tableWidget->setColumnWidth(1, 180);
    ui->tableWidget->setColumnWidth(2, 180);
    ui->tableWidget->setColumnWidth(3, 180);
    ui->tableWidget->setColumnWidth(4, 180);
    ui->tableWidget->setColumnWidth(5, 240);

    ui->tableWidget->setRowCount(0);

    //--------------------------------------------------------------------------
    // LOGO AND ICON CONFIGURATION
    //--------------------------------------------------------------------------
    originalLogoPixmap = QPixmap(":/images/logo.png");
    ui->logo->setPixmap(originalLogoPixmap);
    ui->logo->setScaledContents(true);

    ui->missions_icon->setPixmap(
        QPixmap(":/images/mission_logo.png").scaled(
            ui->missions_icon->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            )
        );
    ui->missions_icon->setScaledContents(true);

    ui->zone_icon->setPixmap(
        QPixmap(":/images/zone_icon.png").scaled(
            ui->zone_icon->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            )
        );
    ui->zone_icon->setScaledContents(true);

    ui->poubelle_icon->setPixmap(
        QPixmap(":/images/poubelle_icon.png").scaled(
            ui->poubelle_icon->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            )
        );
    ui->poubelle_icon->setScaledContents(true);

    ui->employe_icon->setPixmap(
        QPixmap(":/images/employe_icon.png").scaled(
            ui->employe_icon->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            )
        );
    ui->employe_icon->setScaledContents(true);

    ui->vehicule_icon->setPixmap(
        QPixmap(":/images/truck_icon.png").scaled(
            ui->vehicule_icon->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            )
        );
    ui->vehicule_icon->setScaledContents(true);

    //--------------------------------------------------------------------------
    // CONNECT ICON CLICK EVENTS
    //--------------------------------------------------------------------------
    ui->missions_icon->installEventFilter(this);
    ui->zone_icon->installEventFilter(this);
    ui->poubelle_icon->installEventFilter(this);
    ui->employe_icon->installEventFilter(this);
    ui->vehicule_icon->installEventFilter(this);

    ui->missions_icon->setCursor(Qt::PointingHandCursor);
    ui->zone_icon->setCursor(Qt::PointingHandCursor);
    ui->poubelle_icon->setCursor(Qt::PointingHandCursor);
    ui->employe_icon->setCursor(Qt::PointingHandCursor);
    ui->vehicule_icon->setCursor(Qt::PointingHandCursor);

    ui->missions_icon->setToolTip("Missions");
    ui->zone_icon->setToolTip("Zones");
    ui->poubelle_icon->setToolTip("Poubelles");
    ui->employe_icon->setToolTip("Employes");
    ui->vehicule_icon->setToolTip("Vehicules");

    //--------------------------------------------------------------------------
    // SHOW DEFAULT PAGE (MISSIONS)
    //--------------------------------------------------------------------------
    employeePages = new EmployePages(ui->centralwidget);
    employeePages->setGeometry(ui->tableWidget->geometry());
    employeePages->setVisible(false);

    showMissionsPage();
}

//==============================================================================
// EVENT FILTER - Handle icon clicks
//==============================================================================
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    auto setIconHover = [](QLabel *label, bool isHover) {
        if (!label) {
            return;
        }

        if (isHover) {
            label->setStyleSheet(
                "background-color: rgba(142, 148, 78, 0.18);"
                "border-radius: 12px;"
                "padding: 4px;"
                );
        } else {
            label->setStyleSheet("background-color: transparent;");
        }
    };

    if (event->type() == QEvent::Enter) {
        if (obj == ui->missions_icon) {
            setIconHover(ui->missions_icon, true);
            return false;
        } else if (obj == ui->zone_icon) {
            setIconHover(ui->zone_icon, true);
            return false;
        } else if (obj == ui->poubelle_icon) {
            setIconHover(ui->poubelle_icon, true);
            return false;
        } else if (obj == ui->employe_icon) {
            setIconHover(ui->employe_icon, true);
            return false;
        } else if (obj == ui->vehicule_icon) {
            setIconHover(ui->vehicule_icon, true);
            return false;
        }
    } else if (event->type() == QEvent::Leave) {
        if (obj == ui->missions_icon) {
            setIconHover(ui->missions_icon, false);
            return false;
        } else if (obj == ui->zone_icon) {
            setIconHover(ui->zone_icon, false);
            return false;
        } else if (obj == ui->poubelle_icon) {
            setIconHover(ui->poubelle_icon, false);
            return false;
        } else if (obj == ui->employe_icon) {
            setIconHover(ui->employe_icon, false);
            return false;
        } else if (obj == ui->vehicule_icon) {
            setIconHover(ui->vehicule_icon, false);
            return false;
        }
    }

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
// PAGE MANAGEMENT FUNCTIONS
//==============================================================================

//------------------------------------------------------------------------------
// CLEAR PAGE - Hide all page content
//------------------------------------------------------------------------------
void MainWindow::clearPage()
{
    ui->tableWidget->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->label->setVisible(false);
    ui->tableWidget->setRowCount(0);
    if (employeePages) {
        employeePages->setVisible(false);
    }

    qDebug() << "Page cleared";
}

//------------------------------------------------------------------------------
// SHOW MISSIONS PAGE
//------------------------------------------------------------------------------
void MainWindow::showMissionsPage()
{
    clearPage();
    currentPage = PAGE_MISSIONS;

    ui->tableWidget->setVisible(true);
    ui->pushButton_2->setVisible(true);
    ui->label->setVisible(false);

    ui->pushButton_2->setText("Lancer une nouvelle mission");

    ui->tableWidget->setColumnCount(6);

    QStringList headers;
    headers << "Mission N°" << "Zone" << "Workers" << "Start Time"
            << "End Time" << "Operations";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    ui->tableWidget->setColumnWidth(0, 160);
    ui->tableWidget->setColumnWidth(1, 160);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 150);
    ui->tableWidget->setColumnWidth(4, 150);
    ui->tableWidget->setColumnWidth(5, 180);

    addRowWithButtons(0, "1", "ariana", "1,2,3,7", "15/08/2026 7Pm", "8Pm");

    qDebug() << "Missions page displayed";
}

//------------------------------------------------------------------------------
// SHOW ZONES PAGE
//------------------------------------------------------------------------------
void MainWindow::showZonesPage()
{
    clearPage();
    currentPage = PAGE_ZONES;

    qDebug() << "Zones page displayed (empty)";
}

//------------------------------------------------------------------------------
// SHOW POUBELLE PAGE
//------------------------------------------------------------------------------
void MainWindow::showPoubellePage()
{
    clearPage();
    currentPage = PAGE_POUBELLE;

    qDebug() << "Poubelle page displayed (empty)";
}

//------------------------------------------------------------------------------
// SHOW EMPLOYE PAGE - BRAINWAVE STYLE LIST VIEW
//------------------------------------------------------------------------------
void MainWindow::showEmployePage()
{
    clearPage();
    currentPage = PAGE_EMPLOYE;

    if (!employeePages) {
        return;
    }

    employeePages->setVisible(true);
    employeePages->raise();
    employeePages->showListPage();

    qDebug() << "Employee List page displayed";
}

//------------------------------------------------------------------------------
// SHOW EMPLOYEE FORM PAGE
//------------------------------------------------------------------------------
void MainWindow::showEmployeeForm()
{
    clearPage();
    currentPage = PAGE_EMPLOYE;

    if (!employeePages) {
        return;
    }

    employeePages->setVisible(true);
    employeePages->raise();
    employeePages->showFormPage();

    qDebug() << "Employee Form page displayed";
}

//------------------------------------------------------------------------------
// SHOW EMPLOYEE STATISTICS PAGE
//------------------------------------------------------------------------------
void MainWindow::showEmployeeStatistics()
{
    clearPage();
    currentPage = PAGE_EMPLOYE;

    if (!employeePages) {
        return;
    }

    employeePages->setVisible(true);
    employeePages->raise();
    employeePages->showStatsPage();

    qDebug() << "Employee Statistics page displayed";
}

//------------------------------------------------------------------------------
// SHOW VEHICULE PAGE
//------------------------------------------------------------------------------
void MainWindow::showVehiculePage()
{
    clearPage();
    currentPage = PAGE_VEHICULE;

    qDebug() << "Vehicule page displayed (empty)";
}

//==============================================================================
// NAVIGATION BUTTON HANDLERS
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

//==============================================================================
// ADD ROW WITH BUTTONS (FOR MISSIONS)
//==============================================================================
void MainWindow::addRowWithButtons(int row, QString missionNum, QString zone,
                                   QString workers, QString startTime, QString endTime)
{
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setRowHeight(row, 60);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(missionNum));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(zone));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(workers));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(startTime));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(endTime));

    QWidget *buttonWidget = new QWidget();
    buttonWidget->setStyleSheet("background-color: transparent;");
    QHBoxLayout *layout = new QHBoxLayout(buttonWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(15);
    layout->setAlignment(Qt::AlignCenter);

    QSize buttonSize(40, 40);

    QPushButton *btnChange = new QPushButton();
    QPixmap updatePixmap(":/images/update.png");
    updatePixmap = updatePixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    btnChange->setIcon(QIcon(updatePixmap));
    btnChange->setIconSize(buttonSize);
    btnChange->setFixedSize(buttonSize);
    btnChange->setFlat(true);
    btnChange->setStyleSheet("QPushButton { background: transparent; border: none; }");

    ImageButtonHoverFilter *updateFilter = new ImageButtonHoverFilter(
        btnChange, ":/images/update.png", ":/images/update_hover.png",
        ":/images/update_clicked.png", buttonSize
        );

    QPushButton *btnDelete = new QPushButton();
    QPixmap deletePixmap(":/images/delete.png");
    deletePixmap = deletePixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    btnDelete->setIcon(QIcon(deletePixmap));
    btnDelete->setIconSize(buttonSize);
    btnDelete->setFixedSize(buttonSize);
    btnDelete->setFlat(true);
    btnDelete->setStyleSheet("QPushButton { background: transparent; border: none; }");

    ImageButtonHoverFilter *deleteFilter = new ImageButtonHoverFilter(
        btnDelete, ":/images/delete.png", ":/images/delete_hover.png",
        ":/images/delete_clicked.png", buttonSize
        );

    layout->addWidget(btnChange);
    layout->addWidget(btnDelete);

    ui->tableWidget->setCellWidget(row, 5, buttonWidget);
}

//==============================================================================
// ADD EMPLOYE ROW WITH BUTTONS (LEGACY - NOT USED IN NEW BRAINWAVE INTERFACE)
//==============================================================================
void MainWindow::addEmployeRowWithButtons(int row, QString id_employe, QString nom,
                                          QString prenom, QString mot_de_passe,
                                          QString telephone, QString salaire, QString etat)
{
    // This function is kept for backwards compatibility but is not used
    // in the new BrainWave employee interface
}

//==============================================================================
// SIDEBAR TOGGLE ANIMATION
//==============================================================================
void MainWindow::on_pushButton_clicked()
{
    static bool isCollapsed = false;
    int slideDistance = 50;
    int iconSlideDistance = -20;
    int animationDuration = 300;

    if (!isCollapsed) {
        ui->pushButton_5->setVisible(false);
        ui->pushButton_6->setVisible(false);
        ui->pushButton_7->setVisible(false);
        ui->pushButton_8->setVisible(false);
        ui->pushButton_9->setVisible(false);

        QPropertyAnimation *labelAnim = new QPropertyAnimation(ui->label, "geometry");
        labelAnim->setDuration(animationDuration);
        labelAnim->setStartValue(ui->label->geometry());
        QRect newLabelRect = ui->label->geometry();
        newLabelRect.moveLeft(newLabelRect.left() - slideDistance);
        labelAnim->setEndValue(newLabelRect);
        labelAnim->setEasingCurve(QEasingCurve::InOutQuad);
        labelAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *logoScaleAnim = new QPropertyAnimation(ui->logo, "geometry");
        logoScaleAnim->setDuration(animationDuration);
        logoScaleAnim->setStartValue(ui->logo->geometry());
        QRect newLogoRect = ui->logo->geometry();
        newLogoRect.setWidth(newLogoRect.width() / 3);
        newLogoRect.setHeight(newLogoRect.height() / 3);
        newLogoRect.moveLeft(newLogoRect.left() - slideDistance + 80);
        logoScaleAnim->setEndValue(newLogoRect);
        logoScaleAnim->setEasingCurve(QEasingCurve::InOutQuad);
        logoScaleAnim->start(QAbstractAnimation::DeleteWhenStopped);

        ui->pushButton->setText(">");

        QPropertyAnimation *btnAnim = new QPropertyAnimation(ui->pushButton, "geometry");
        btnAnim->setDuration(animationDuration);
        btnAnim->setStartValue(ui->pushButton->geometry());
        QRect newBtnRect = ui->pushButton->geometry();
        newBtnRect.moveLeft(newBtnRect.left() - slideDistance);
        btnAnim->setEndValue(newBtnRect);
        btnAnim->setEasingCurve(QEasingCurve::InOutQuad);
        btnAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *missionsIconAnim = new QPropertyAnimation(ui->missions_icon, "geometry");
        missionsIconAnim->setDuration(animationDuration);
        missionsIconAnim->setStartValue(ui->missions_icon->geometry());
        QRect newMissionsIconRect = ui->missions_icon->geometry();
        newMissionsIconRect.moveLeft(newMissionsIconRect.left() - iconSlideDistance);
        missionsIconAnim->setEndValue(newMissionsIconRect);
        missionsIconAnim->setEasingCurve(QEasingCurve::InOutQuad);
        missionsIconAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *zoneIconAnim = new QPropertyAnimation(ui->zone_icon, "geometry");
        zoneIconAnim->setDuration(animationDuration);
        zoneIconAnim->setStartValue(ui->zone_icon->geometry());
        QRect newZoneIconRect = ui->zone_icon->geometry();
        newZoneIconRect.moveLeft(newZoneIconRect.left() - iconSlideDistance);
        zoneIconAnim->setEndValue(newZoneIconRect);
        zoneIconAnim->setEasingCurve(QEasingCurve::InOutQuad);
        zoneIconAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *poubelleIconAnim = new QPropertyAnimation(ui->poubelle_icon, "geometry");
        poubelleIconAnim->setDuration(animationDuration);
        poubelleIconAnim->setStartValue(ui->poubelle_icon->geometry());
        QRect newPoubelleIconRect = ui->poubelle_icon->geometry();
        newPoubelleIconRect.moveLeft(newPoubelleIconRect.left() - iconSlideDistance);
        poubelleIconAnim->setEndValue(newPoubelleIconRect);
        poubelleIconAnim->setEasingCurve(QEasingCurve::InOutQuad);
        poubelleIconAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *employeIconAnim = new QPropertyAnimation(ui->employe_icon, "geometry");
        employeIconAnim->setDuration(animationDuration);
        employeIconAnim->setStartValue(ui->employe_icon->geometry());
        QRect newEmployeIconRect = ui->employe_icon->geometry();
        newEmployeIconRect.moveLeft(newEmployeIconRect.left() - iconSlideDistance);
        employeIconAnim->setEndValue(newEmployeIconRect);
        employeIconAnim->setEasingCurve(QEasingCurve::InOutQuad);
        employeIconAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *vehiculeIconAnim = new QPropertyAnimation(ui->vehicule_icon, "geometry");
        vehiculeIconAnim->setDuration(animationDuration);
        vehiculeIconAnim->setStartValue(ui->vehicule_icon->geometry());
        QRect newVehiculeIconRect = ui->vehicule_icon->geometry();
        newVehiculeIconRect.moveLeft(newVehiculeIconRect.left() - iconSlideDistance);
        vehiculeIconAnim->setEndValue(newVehiculeIconRect);
        vehiculeIconAnim->setEasingCurve(QEasingCurve::InOutQuad);
        vehiculeIconAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *tableAnim = new QPropertyAnimation(ui->tableWidget, "geometry");
        tableAnim->setDuration(animationDuration);
        tableAnim->setStartValue(ui->tableWidget->geometry());
        QRect newTableRect = ui->tableWidget->geometry();
        newTableRect.moveLeft(newTableRect.left() - slideDistance);
        tableAnim->setEndValue(newTableRect);
        tableAnim->setEasingCurve(QEasingCurve::InOutQuad);
        tableAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *btn2Anim = new QPropertyAnimation(ui->pushButton_2, "geometry");
        btn2Anim->setDuration(animationDuration);
        btn2Anim->setStartValue(ui->pushButton_2->geometry());
        QRect newBtn2Rect = ui->pushButton_2->geometry();
        newBtn2Rect.moveLeft(newBtn2Rect.left() - slideDistance);
        btn2Anim->setEndValue(newBtn2Rect);
        btn2Anim->setEasingCurve(QEasingCurve::InOutQuad);
        btn2Anim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *lineAnim = new QPropertyAnimation(ui->line, "geometry");
        lineAnim->setDuration(animationDuration);
        lineAnim->setStartValue(ui->line->geometry());
        QRect newLineRect = ui->line->geometry();
        newLineRect.moveLeft(newLineRect.left() - slideDistance - 40);
        lineAnim->setEndValue(newLineRect);
        lineAnim->setEasingCurve(QEasingCurve::InOutQuad);
        lineAnim->start(QAbstractAnimation::DeleteWhenStopped);

        isCollapsed = true;

    } else {
        QPropertyAnimation *labelAnim = new QPropertyAnimation(ui->label, "geometry");
        labelAnim->setDuration(animationDuration);
        labelAnim->setStartValue(ui->label->geometry());
        QRect newLabelRect = ui->label->geometry();
        newLabelRect.moveLeft(newLabelRect.left() + slideDistance);
        labelAnim->setEndValue(newLabelRect);
        labelAnim->setEasingCurve(QEasingCurve::InOutQuad);
        labelAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *logoScaleAnim = new QPropertyAnimation(ui->logo, "geometry");
        logoScaleAnim->setDuration(animationDuration);
        logoScaleAnim->setStartValue(ui->logo->geometry());
        QRect newLogoRect = ui->logo->geometry();
        newLogoRect.setWidth(newLogoRect.width() * 3);
        newLogoRect.setHeight(newLogoRect.height() * 3);
        newLogoRect.moveLeft(newLogoRect.left() + slideDistance - 80);
        logoScaleAnim->setEndValue(newLogoRect);
        logoScaleAnim->setEasingCurve(QEasingCurve::InOutQuad);
        logoScaleAnim->start(QAbstractAnimation::DeleteWhenStopped);

        ui->pushButton->setText("<");

        QPropertyAnimation *btnAnim = new QPropertyAnimation(ui->pushButton, "geometry");
        btnAnim->setDuration(animationDuration);
        btnAnim->setStartValue(ui->pushButton->geometry());
        QRect newBtnRect = ui->pushButton->geometry();
        newBtnRect.moveLeft(newBtnRect.left() + slideDistance);
        btnAnim->setEndValue(newBtnRect);
        btnAnim->setEasingCurve(QEasingCurve::InOutQuad);
        btnAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *missionsIconAnim = new QPropertyAnimation(ui->missions_icon, "geometry");
        missionsIconAnim->setDuration(animationDuration);
        missionsIconAnim->setStartValue(ui->missions_icon->geometry());
        QRect newMissionsIconRect = ui->missions_icon->geometry();
        newMissionsIconRect.moveLeft(newMissionsIconRect.left() + iconSlideDistance);
        missionsIconAnim->setEndValue(newMissionsIconRect);
        missionsIconAnim->setEasingCurve(QEasingCurve::InOutQuad);
        missionsIconAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *zoneIconAnim = new QPropertyAnimation(ui->zone_icon, "geometry");
        zoneIconAnim->setDuration(animationDuration);
        zoneIconAnim->setStartValue(ui->zone_icon->geometry());
        QRect newZoneIconRect = ui->zone_icon->geometry();
        newZoneIconRect.moveLeft(newZoneIconRect.left() + iconSlideDistance);
        zoneIconAnim->setEndValue(newZoneIconRect);
        zoneIconAnim->setEasingCurve(QEasingCurve::InOutQuad);
        zoneIconAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *poubelleIconAnim = new QPropertyAnimation(ui->poubelle_icon, "geometry");
        poubelleIconAnim->setDuration(animationDuration);
        poubelleIconAnim->setStartValue(ui->poubelle_icon->geometry());
        QRect newPoubelleIconRect = ui->poubelle_icon->geometry();
        newPoubelleIconRect.moveLeft(newPoubelleIconRect.left() + iconSlideDistance);
        poubelleIconAnim->setEndValue(newPoubelleIconRect);
        poubelleIconAnim->setEasingCurve(QEasingCurve::InOutQuad);
        poubelleIconAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *employeIconAnim = new QPropertyAnimation(ui->employe_icon, "geometry");
        employeIconAnim->setDuration(animationDuration);
        employeIconAnim->setStartValue(ui->employe_icon->geometry());
        QRect newEmployeIconRect = ui->employe_icon->geometry();
        newEmployeIconRect.moveLeft(newEmployeIconRect.left() + iconSlideDistance);
        employeIconAnim->setEndValue(newEmployeIconRect);
        employeIconAnim->setEasingCurve(QEasingCurve::InOutQuad);
        employeIconAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *vehiculeIconAnim = new QPropertyAnimation(ui->vehicule_icon, "geometry");
        vehiculeIconAnim->setDuration(animationDuration);
        vehiculeIconAnim->setStartValue(ui->vehicule_icon->geometry());
        QRect newVehiculeIconRect = ui->vehicule_icon->geometry();
        newVehiculeIconRect.moveLeft(newVehiculeIconRect.left() + iconSlideDistance);
        vehiculeIconAnim->setEndValue(newVehiculeIconRect);
        vehiculeIconAnim->setEasingCurve(QEasingCurve::InOutQuad);
        vehiculeIconAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *tableAnim = new QPropertyAnimation(ui->tableWidget, "geometry");
        tableAnim->setDuration(animationDuration);
        tableAnim->setStartValue(ui->tableWidget->geometry());
        QRect newTableRect = ui->tableWidget->geometry();
        newTableRect.moveLeft(newTableRect.left() + slideDistance);
        tableAnim->setEndValue(newTableRect);
        tableAnim->setEasingCurve(QEasingCurve::InOutQuad);
        tableAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *btn2Anim = new QPropertyAnimation(ui->pushButton_2, "geometry");
        btn2Anim->setDuration(animationDuration);
        btn2Anim->setStartValue(ui->pushButton_2->geometry());
        QRect newBtn2Rect = ui->pushButton_2->geometry();
        newBtn2Rect.moveLeft(newBtn2Rect.left() + slideDistance);
        btn2Anim->setEndValue(newBtn2Rect);
        btn2Anim->setEasingCurve(QEasingCurve::InOutQuad);
        btn2Anim->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation *lineAnim = new QPropertyAnimation(ui->line, "geometry");
        lineAnim->setDuration(animationDuration);
        lineAnim->setStartValue(ui->line->geometry());
        QRect newLineRect = ui->line->geometry();
        newLineRect.moveLeft(newLineRect.left() + slideDistance + 40);
        lineAnim->setEndValue(newLineRect);
        lineAnim->setEasingCurve(QEasingCurve::InOutQuad);
        lineAnim->start(QAbstractAnimation::DeleteWhenStopped);

        QTimer::singleShot(animationDuration + 10, this, [this]() {
            ui->pushButton_5->setVisible(true);
            ui->pushButton_6->setVisible(true);
            ui->pushButton_7->setVisible(true);
            ui->pushButton_8->setVisible(true);
            ui->pushButton_9->setVisible(true);
        });

        isCollapsed = false;
    }
}

//==============================================================================
// DESTRUCTOR
//==============================================================================
MainWindow::~MainWindow()
{
    delete ui;
}
