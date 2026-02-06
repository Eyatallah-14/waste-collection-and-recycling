#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QEvent>
#include <QPushButton>
#include <QIcon>
#include <QPixmap>

#include "employepages.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

//==============================================================================
// IMAGE BUTTON HOVER FILTER CLASS
// Handles hover, press, and normal states for icon buttons
//==============================================================================
class ImageButtonHoverFilter : public QObject
{
    Q_OBJECT
public:
    ImageButtonHoverFilter(QPushButton *button, const QString &normalIcon,
                           const QString &hoverIcon, const QString &clickedIcon,
                           QSize iconSize)
        : QObject(button), btn(button), normalIconPath(normalIcon),
        hoverIconPath(hoverIcon), clickedIconPath(clickedIcon), size(iconSize)
    {
        btn->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (obj == btn) {
            if (event->type() == QEvent::MouseButtonPress) {
                QPixmap clickedPixmap(clickedIconPath);
                clickedPixmap = clickedPixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                btn->setIcon(QIcon(clickedPixmap));
                btn->setIconSize(size);
                return false;
            } else if (event->type() == QEvent::MouseButtonRelease) {
                QPixmap hoverPixmap(hoverIconPath);
                hoverPixmap = hoverPixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                btn->setIcon(QIcon(hoverPixmap));
                btn->setIconSize(size);
                return false;
            } else if (event->type() == QEvent::Enter) {
                QPixmap hoverPixmap(hoverIconPath);
                hoverPixmap = hoverPixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                btn->setIcon(QIcon(hoverPixmap));
                btn->setIconSize(size);
                return true;
            } else if (event->type() == QEvent::Leave) {
                QPixmap normalPixmap(normalIconPath);
                normalPixmap = normalPixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                btn->setIcon(QIcon(normalPixmap));
                btn->setIconSize(size);
                return true;
            }
        }
        return QObject::eventFilter(obj, event);
    }

private:
    QPushButton *btn;
    QString normalIconPath;
    QString hoverIconPath;
    QString clickedIconPath;
    QSize size;
};

//==============================================================================
// MAIN WINDOW CLASS
//==============================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_pushButton_clicked();      // Sidebar toggle animation
    void on_pushButton_5_clicked();    // Zone navigation
    void on_pushButton_6_clicked();    // Poubelle navigation
    void on_pushButton_7_clicked();    // Employe navigation
    void on_pushButton_8_clicked();    // Missions navigation
    void on_pushButton_9_clicked();    // Vehicule navigation

    // NEW BrainWave Employee Functions
    void showEmployeeForm();           // Show employee form page
    void showEmployeeStatistics();     // Show employee statistics page

private:
    Ui::MainWindow *ui;
    EmployePages *employeePages = nullptr;
    void addRowWithButtons(int row, QString missionNum, QString zone,
                           QString workers, QString startTime, QString endTime);
    void addEmployeRowWithButtons(int row, QString id_employe, QString nom,
                                  QString prenom, QString mot_de_passe,
                                  QString telephone, QString salaire, QString etat);
    QPixmap originalLogoPixmap;

    // Page management
    enum PageType {
        PAGE_MISSIONS,
        PAGE_ZONES,
        PAGE_POUBELLE,
        PAGE_EMPLOYE,
        PAGE_VEHICULE
    };

    PageType currentPage;

    // Page management functions
    void clearPage();
    void showMissionsPage();
    void showZonesPage();
    void showPoubellePage();
    void showEmployePage();      // Now shows BrainWave-style employee list
    void showVehiculePage();
};

#endif // MAINWINDOW_H
