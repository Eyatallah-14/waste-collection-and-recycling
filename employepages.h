#ifndef EMPLOYEPAGES_H
#define EMPLOYEPAGES_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class EmployePages;
}
QT_END_NAMESPACE

class EmployePages : public QWidget
{
    Q_OBJECT

public:
    explicit EmployePages(QWidget *parent = nullptr);
    ~EmployePages();

    void showListPage();
    void showFormPage();
    void showStatsPage();

private:
    Ui::EmployePages *ui;

    void setupEmployeeTable();
    void setupCharts();
};

#endif // EMPLOYEPAGES_H
