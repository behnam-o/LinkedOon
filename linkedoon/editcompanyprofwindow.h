#ifndef EDITCOMPANYPROFWINDOW_H
#define EDITCOMPANYPROFWINDOW_H

#include <QWidget>
#include <vector>
#include <QLabel>

using namespace std;
class System;

namespace Ui {
class EditCompanyprofWindow;
}

class EditCompanyprofWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditCompanyprofWindow(System* sys , QWidget *parent = 0);
    ~EditCompanyprofWindow();
    void set_fields_company();

public slots:
    void save();
    void add_description();
    void add_job();

private:
    Ui::EditCompanyprofWindow *ui;
    System* system;
    vector<QLabel*> jobs;
};

#endif // EDITCOMPANYPROFWINDOW_H
