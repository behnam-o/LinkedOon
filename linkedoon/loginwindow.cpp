#include "loginwindow.h"
#include "ui_loginwindow.h"

#include "headers/user.h"
#include "headers/education.h"
#include "headers/skill.h"
#include "headers/experience.h"
#include "companyprofilewindow.h"

LoginWindow::LoginWindow(System* sys , QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect(ui->signupbutton,SIGNAL(clicked(bool)),this,SLOT(signup()));
    connect(ui->loginbutton,SIGNAL(clicked(bool)),this,SLOT(login()));
    system=sys;
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::signup()
{
    SignupWindow* signupwin = new SignupWindow(system);
    signupwin->showMaximized();
    this->close();
}

void LoginWindow::login()
{
    if(ui->usernametxt->text()!="" && ui->passwordtxt->text()!="" && ui->usernametxt->text().toStdString().find(' ')==-1 && ui->passwordtxt->text().toStdString().find(' ')==-1 ){
        try{
            system->login(ui->usernametxt->text().toStdString(), ui->passwordtxt->text().toStdString());
            this->close();
        }
        catch(LoginException E){ui->loginlabel->setText(" User doesn't exist");}

        if(system->current_user!=0){
            UserProfileWindow* profilewindow = new UserProfileWindow(system);
            profilewindow->showMaximized();
        }
        else if(system->current_company!=0){
            CompanyProfileWindow* profilewindow = new CompanyProfileWindow(system);
            profilewindow->showMaximized();
        }

    }
    else
    {
        ui->loginlabel->setText("Invalid Username and/or Password ");
    }
}
