#ifndef EDITUSERPROFWINDOW_H
#define EDITUSERPROFWINDOW_H

#include <QWidget>
#include <QLabel>

class System;

namespace Ui {
class EditUserprofWindow;
}

class EditUserprofWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditUserprofWindow(System* sys , QWidget *parent = 0);
    ~EditUserprofWindow();
    void set_fields_user();

public slots:
    void save();
    void add_education();
    void add_experience();
    void add_skill();

private:
    Ui::EditUserprofWindow *ui;
    System* system;
    std::vector<QLabel*> skills;
    std::vector<QLabel*> educations;
    std::vector<QLabel*> experiences;
    QLabel* skillslabel;
    QLabel* educationslabel;
    QLabel* experienceslabel;
};

#endif // EDITUSERPROFWINDOW_H
