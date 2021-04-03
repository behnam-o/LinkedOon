#ifndef COMPANYPROFILEWINDOW_H
#define COMPANYPROFILEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <vector>

class System;

using namespace std;
namespace Ui {
class CompanyProfileWindow;
}

class CompanyProfileWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CompanyProfileWindow(System* sys , QWidget *parent = 0);
    ~CompanyProfileWindow();
    void set_fields_company();

public slots:
    void logout();
    void edit();
    void search();

private:
    Ui::CompanyProfileWindow *ui;
    System* system;
    vector<QLabel*> jobs;
};

#endif // COMPANYPROFILEWINDOW_H
