#include "edituserprofwindow.h"
#include "ui_edituserprofwindow.h"
#include "userprofilewindow.h"
#include "headers/system.h"
#include "headers/user.h"
#include "headers/education.h"
#include "headers/skill.h"
#include "headers/experience.h"

EditUserprofWindow::EditUserprofWindow(System* sys , QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditUserprofWindow)
{
    ui->setupUi(this);
    system = sys;
    set_fields_user();
    connect(ui->savebutton , SIGNAL(clicked(bool)) , this , SLOT(save()));
    connect(ui->addedubutton , SIGNAL(clicked(bool)) , this ,SLOT(add_education()));
    connect(ui->addexpbutton , SIGNAL(clicked(bool)) , this , SLOT(add_experience()));
    connect(ui->addskillbutton , SIGNAL(clicked(bool)) , this , SLOT(add_skill()));
}

EditUserprofWindow::~EditUserprofWindow()
{
    delete ui;
}

void EditUserprofWindow::add_education()
{
    if(ui->degreetxt->text()!="" && ui->schooltxt->text()!="" && ui->yeartxt->text()!=""){
        system->current_user->add_education(Education(ui->degreetxt->text().toStdString(),
                                                         ui->schooltxt->text().toStdString(),
                                                         ui->yeartxt->text().toUInt()));
        EditUserprofWindow* win = new EditUserprofWindow(system);
        win->showMaximized();
        this->close();
    }
}

void EditUserprofWindow::add_experience()
{
    if(ui->postxt->text()!="" && ui->orgtxt->text()!="" && ui->syeartxt->text()!=0 && ui->eyeartxt->text()!=""){
        system->current_user->add_experience(Experience(ui->postxt->text().toStdString(),
                                                        ui->orgtxt->text().toStdString(),
                                                        ui->syeartxt->text().toUInt(),
                                                        ui->eyeartxt->text().toUInt()));
        EditUserprofWindow* win = new EditUserprofWindow(system);
        win->showMaximized();
        this->close();
    }
}

void EditUserprofWindow::add_skill()
{
    if(ui->skilltxt->text()!=""){
        system->current_user->add_skill(Skill(ui->skilltxt->text().toStdString()));
        EditUserprofWindow* win = new EditUserprofWindow(system);
        win->showMaximized();
        this->close();
    }
}

void EditUserprofWindow::save()
{
    system->current_user->set_f_name(ui->fnametxt->text().toStdString());
    system->current_user->set_l_name(ui->lnametxt->text().toStdString());

    UserProfileWindow* userwin = new UserProfileWindow(system);
    userwin->showMaximized();
    this->close();

}

void EditUserprofWindow::set_fields_user()
{
    ui->usernamelabel->setText(QString::fromStdString(system->current_user->get_username()));
    ui->fnametxt->setText(QString::fromStdString(system->current_user->get_f_name()));
    ui->lnametxt->setText(QString::fromStdString(system->current_user->get_l_name()));

    int y =250;
    educationslabel = new QLabel(this);
    educationslabel->setGeometry(800,y,80,40);
    educationslabel->setText("Educations");
    for (int i=0 ; i<system->current_user->get_educations().size() ; i++){
        educations.push_back(new QLabel(this));
        educations[i]->setGeometry(900,y,200,40);
        educations[i]->setText(QString::fromStdString(
                                   system->current_user->get_educations()[i].to_string())+
                                   " in "+QString::number(system->current_user->get_educations()[i].get_year()));
        educations[i]->setStyleSheet("background-color : white;");
        y+=50;
    }

    y+=20;
    experienceslabel = new QLabel(this);
    experienceslabel->setGeometry(800,y,80,40);
    experienceslabel->setText("Experiences");
    for (int i=0 ; i<system->current_user->get_experiences().size() ; i++){
        experiences.push_back(new QLabel(this));
        experiences[i]->setGeometry(900,y,200,40);
        experiences[i]->setText(QString::fromStdString(
                                    system->current_user->get_experiences()[i].to_string())+" : "+
                                    QString::number(system->current_user->get_experiences()[i].get_start_year())+" - " + QString::number(system->current_user->get_experiences()[i].get_end_year()));
        experiences[i]->setStyleSheet("background-color : white;");
        y+=50;
    }

    y+=20;
    skillslabel = new QLabel(this);
    skillslabel->setGeometry(800,y,80,40);
    skillslabel->setText("Skills");

    for(int i = 0 ; i<system->current_user->get_skills().size() ; i++ ){
        skills.push_back(new QLabel(this));
        skills[i]->setGeometry(900,y,80,40);
        skills[i]->setText(QString::fromStdString(system->current_user->get_skills()[i].get_name()));
        skills[i]->setStyleSheet("background-color :white; ");
        y+=50;
    }
}
