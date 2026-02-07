#ifndef EMPLOYEPAGES_H
#define EMPLOYEPAGES_H

#include <QWidget>

namespace Ui {
class EmployePages;
}

class EmployePages : public QWidget
{
    Q_OBJECT

public:
    explicit EmployePages(QWidget *parent = nullptr);
    ~EmployePages();

private slots:
    void showListPage();
    void showFormPage();
    void showStatsPage();

private:
    Ui::EmployePages *ui;
    
    void setupEmployeeTable();
    void setupCharts();
};

#endif // EMPLOYEPAGES_H
