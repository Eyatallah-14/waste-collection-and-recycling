#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestionpoubellepages.h"

#include <QEvent>
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , poubelleWidget(nullptr)
    , currentPage(PAGE_POUBELLE)
{
    ui->setupUi(this);

    // Configuration du logo
    originalLogoPixmap = QPixmap(":/images/logo.png");
    ui->logo->setPixmap(originalLogoPixmap);
    ui->logo->setScaledContents(true);

    // Configuration de toutes les icônes
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

    // Installer les event filters pour toutes les icônes
    ui->missions_icon->installEventFilter(this);
    ui->zone_icon->installEventFilter(this);
    ui->poubelle_icon->installEventFilter(this);
    ui->employe_icon->installEventFilter(this);
    ui->vehicule_icon->installEventFilter(this);

    // Configurer les curseurs
    ui->missions_icon->setCursor(Qt::PointingHandCursor);
    ui->zone_icon->setCursor(Qt::PointingHandCursor);
    ui->poubelle_icon->setCursor(Qt::PointingHandCursor);
    ui->employe_icon->setCursor(Qt::PointingHandCursor);
    ui->vehicule_icon->setCursor(Qt::PointingHandCursor);

    // Configurer les tooltips
    ui->missions_icon->setToolTip("Missions");
    ui->zone_icon->setToolTip("Zones");
    ui->poubelle_icon->setToolTip("Gestion des Poubelles");
    ui->employe_icon->setToolTip("Employés");
    ui->vehicule_icon->setToolTip("Véhicules");

    // Créer le widget de gestion des poubelles
    poubelleWidget = new GestionPoubellePage(ui->centralwidget);
    poubelleWidget->setGeometry(240, 20, 1340, 860);
    poubelleWidget->setVisible(false);

    // Créer les labels pour les pages vides
    ui->missionsLabel->setVisible(false);
    ui->zonesLabel->setVisible(false);
    ui->employeLabel->setVisible(false);
    ui->vehiculeLabel->setVisible(false);

    // Afficher la page poubelles par défaut
    showPoubellePage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

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

    // Gestion des événements Enter (survol)
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
    } 
    // Gestion des événements Leave (fin de survol)
    else if (event->type() == QEvent::Leave) {
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

    // Gestion des clics
    if (event->type() == QEvent::MouseButtonPress) {
        if (obj == ui->missions_icon) {
            showMissionsPage();
            return true;
        } else if (obj == ui->zone_icon) {
            showZonesPage();
            return true;
        } else if (obj == ui->poubelle_icon) {
            showPoubellePage();
            return true;
        } else if (obj == ui->employe_icon) {
            showEmployePage();
            return true;
        } else if (obj == ui->vehicule_icon) {
            showVehiculePage();
            return true;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::clearPage()
{
    if (poubelleWidget) {
        poubelleWidget->setVisible(false);
    }
    ui->missionsLabel->setVisible(false);
    ui->zonesLabel->setVisible(false);
    ui->employeLabel->setVisible(false);
    ui->vehiculeLabel->setVisible(false);
}

void MainWindow::showMissionsPage()
{
    clearPage();
    currentPage = PAGE_MISSIONS;
    ui->missionsLabel->setVisible(true);
    qDebug() << "Missions page displayed";
}

void MainWindow::showZonesPage()
{
    clearPage();
    currentPage = PAGE_ZONES;
    ui->zonesLabel->setVisible(true);
    qDebug() << "Zones page displayed";
}

void MainWindow::showPoubellePage()
{
    clearPage();
    currentPage = PAGE_POUBELLE;
    
    if (poubelleWidget) {
        poubelleWidget->setVisible(true);
    }
    
    qDebug() << "Poubelle page displayed";
}

void MainWindow::showEmployePage()
{
    clearPage();
    currentPage = PAGE_EMPLOYE;
    ui->employeLabel->setVisible(true);
    qDebug() << "Employe page displayed";
}

void MainWindow::showVehiculePage()
{
    clearPage();
    currentPage = PAGE_VEHICULE;
    ui->vehiculeLabel->setVisible(true);
    qDebug() << "Vehicule page displayed";
}
