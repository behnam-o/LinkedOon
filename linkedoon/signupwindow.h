#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>
#include "loginwindow.h"
#include "./headers/system.h"

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SignupWindow(System* sys , QWidget *parent = 0);
    ~SignupWindow();

public slots:
    void signup();
    void login();

private:
    Ui::SignupWindow *ui;
    System* system;

};

#endif // SIGNUPWINDOW_H
