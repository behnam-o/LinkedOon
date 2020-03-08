#include "signupwindow.h"
#include "ui_signupwindow.h"

#include "headers/user.h"
#include "headers/education.h"
#include "headers/skill.h"
#include "headers/experience.h"

#include <iostream>
using namespace std;


SignupWindow::SignupWindow(System* sys, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupWindow)
{
    ui->setupUi(this);
    system = sys;

    connect(ui->loginbutton , SIGNAL(clicked(bool)) , this , SLOT(login()));
    connect(ui->sigupbutton , SIGNAL(clicked(bool)) , this , SLOT(signup()));
}

SignupWindow::~SignupWindow()
{
    delete ui;
}

void SignupWindow::signup()
{
    if(ui->passwordtxt->text()!="" && ui->usernametxt->text()!="" && ui->passconfirmtxt->text() !=""){
        if(ui->passwordtxt->text()!=ui->passconfirmtxt->text())
            ui->signuplabel->setText("Passwords don't match .");
        else{
            try{
            if(ui->userradio->isChecked()){
                system->signupu(ui->usernametxt->text().toStdString(),ui->passwordtxt->text().toStdString());
                ui->signuplabel->setText("Account Created .");
            }
            else if(ui->companyradio->isChecked()){
                system->signupc(ui->usernametxt->text().toStdString(),ui->passwordtxt->text().toStdString());
                ui->signuplabel->setText("Account Created .");
            }
            else
                ui->signuplabel->setText("Please Select Account Type");
            }
            catch(SignupException E){ui->signuplabel->setText("Useranme Already Exists.");}
        }
    }
}

void SignupWindow::login()
{
    LoginWindow* loginwin = new LoginWindow(system);
    loginwin->showMaximized();
    this->close();
}
