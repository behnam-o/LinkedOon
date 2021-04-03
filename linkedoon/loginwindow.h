#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "headers/system.h"
#include "signupwindow.h"
#include "userprofilewindow.h"
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(System* sys , QWidget *parent = 0);
    ~LoginWindow();

public slots:
    void signup();
    void login();

private:
    Ui::LoginWindow *ui;
    System* system;
};

#endif // LOGINWINDOW_H
