#include "userprofilewindow.h"
#include "ui_userprofilewindow.h"
#include "headers/user.h"
#include "headers/education.h"
#include "headers/skill.h"
#include "headers/experience.h"
#include "loginwindow.h"
#include "edituserprofwindow.h"
#include "searchwindow.h"


UserProfileWindow::UserProfileWindow(System* sys,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserProfileWindow)
{
    system=sys;
    ui->setupUi(this);
    set_fields_user();
    connect(ui->logoutbutton , SIGNAL(clicked(bool)) , this , SLOT(logout()));
    connect(ui->editbutton , SIGNAL(clicked(bool)) ,this , SLOT(edit()));
    connect(ui->searchbuton ,SIGNAL(clicked(bool)) , this ,SLOT(search()));

}
UserProfileWindow::~UserProfileWindow()
{
    delete ui;
}

void UserProfileWindow::search()
{
    if(ui->searchtxt->text()!="" && ui->searchtxt->text()!=" "){
    SearchWindow* searchwin = new SearchWindow(ui->searchtxt->text() , system);
    searchwin->showMaximized();
    }
}

void UserProfileWindow::edit()
{
    EditUserprofWindow* win = new EditUserprofWindow(system);
    win->showMaximized();
    this->close();

}

void UserProfileWindow::logout()
{
    system->logout();
    LoginWindow* loginwin = new LoginWindow(system);
    loginwin->showMaximized();
    this->close();
}

void UserProfileWindow::set_fields_user()
{
    ui->usernamelabel->setText(QString::fromStdString(system->current_user->get_username()));
    ui->fnamelabel->setText(QString::fromStdString(system->current_user->get_f_name()));
    ui->lnamelabel->setText(QString::fromStdString(system->current_user->get_l_name()));

    int y =250;
    educationslabel = new QLabel(this);
    educationslabel->setGeometry(450,y,80,40);
    educationslabel->setText("Educations");
    for (int i=0 ; i<system->current_user->get_educations().size() ; i++){
        educations.push_back(new QLabel(this));
        educations[i]->setGeometry(550,y,200,40);
        educations[i]->setText(QString::fromStdString(
                                   system->current_user->get_educations()[i].to_string())+
                                   " in "+QString::number(system->current_user->get_educations()[i].get_year()));
        educations[i]->setStyleSheet("background-color : white;");
        y+=50;
    }

    y+=20;
    experienceslabel = new QLabel(this);
    experienceslabel->setGeometry(450,y,80,40);
    experienceslabel->setText("Experiences");
    for (int i=0 ; i<system->current_user->get_experiences().size() ; i++){
        experiences.push_back(new QLabel(this));
        experiences[i]->setGeometry(550,y,200,40);
        experiences[i]->setText(QString::fromStdString(
                                    system->current_user->get_experiences()[i].to_string())+" : "+
                                    QString::number(system->current_user->get_experiences()[i].get_start_year())+" - " + QString::number(system->current_user->get_experiences()[i].get_end_year()));
        experiences[i]->setStyleSheet("background-color : white;");
        y+=50;
    }

    y+=20;
    skillslabel = new QLabel(this);
    skillslabel->setGeometry(450,y,80,40);
    skillslabel->setText("Skills");

    for(int i = 0 ; i<system->current_user->get_skills().size() ; i++ ){
        skills.push_back(new QLabel(this));
        skills[i]->setGeometry(550,y,80,40);
        skills[i]->setText(QString::fromStdString(system->current_user->get_skills()[i].get_name()));
        skills[i]->setStyleSheet("background-color :white; ");
        y+=50;
    }
}

