#ifndef USERPROFILEWINDOW_H
#define USERPROFILEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <vector>
#include "./headers/system.h"
//#include "./headers/user.h"

namespace Ui {
class UserProfileWindow;
}

class UserProfileWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UserProfileWindow(System* sys, QWidget *parent = 0);
    ~UserProfileWindow();
    void set_fields_user();
public slots:
    void logout();
    void edit();
    void search();

private:
    Ui::UserProfileWindow *ui;
    System* system;
    std::vector<QLabel*> skills;
    std::vector<QLabel*> educations;
    std::vector<QLabel*> experiences;
    QLabel* skillslabel;
    QLabel* educationslabel;
    QLabel* experienceslabel;

};

#endif // USERPROFILEWINDOW_H
