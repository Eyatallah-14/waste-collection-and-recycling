#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class GestionPoubellePage;

enum PageType {
    PAGE_MISSIONS,
    PAGE_ZONES,
    PAGE_POUBELLE,
    PAGE_EMPLOYE,
    PAGE_VEHICULE
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void showMissionsPage();
    void showZonesPage();
    void showPoubellePage();
    void showEmployePage();
    void showVehiculePage();

private:
    Ui::MainWindow *ui;
    GestionPoubellePage *poubelleWidget;
    QPixmap originalLogoPixmap;
    PageType currentPage;
    
    void clearPage();
};

#endif // MAINWINDOW_H
