#include "companyprofilewindow.h"
#include "ui_companyprofilewindow.h"

#include "headers/system.h"
#include "headers/company.h"
#include "headers/job.h"
#include "loginwindow.h"

#include "editcompanyprofwindow.h"
#include "searchwindow.h"

CompanyProfileWindow::CompanyProfileWindow(System* sys , QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompanyProfileWindow)
{
    ui->setupUi(this);
    system=sys;
    set_fields_company();
    connect(ui->logoutbutton , SIGNAL(clicked(bool)) , this ,SLOT(logout()));
    connect(ui->editbutton , SIGNAL(clicked(bool)) , this , SLOT(edit()));
    connect(ui->searchbutton ,SIGNAL(clicked(bool)) , this ,SLOT(search()));

}

CompanyProfileWindow::~CompanyProfileWindow()
{
    delete ui;
}

void CompanyProfileWindow::search()
{
    if(ui->searchtxt->text()!="" && ui->searchtxt->text()!=" "){
    SearchWindow* searchwin = new SearchWindow(ui->searchtxt->text() , system);
    searchwin->showMaximized();
    }
}

void CompanyProfileWindow::logout()
{
    system->logout();
    LoginWindow* loginwin = new LoginWindow(system);
    loginwin->showMaximized();
    this->close();
}

void CompanyProfileWindow::edit()
{
    EditCompanyprofWindow* win= new EditCompanyprofWindow(system);
    win->showMaximized();
    this->close();
}

void CompanyProfileWindow::set_fields_company()
{
    ui->usernamelabel->setText(QString::fromStdString(system->current_company->get_username()));
    ui->cnamelabel->setText(QString::fromStdString(system->current_company->get_name()));
    ui->ceolabel->setText(QString::fromStdString(system->current_company->get_ceo()));

    ui->desclabel->setText(QString::fromStdString(system->current_company->get_description()));

    int y =350;

    for(int i = 0 ; i<system->current_company->get_jobs().size() ; i++ ){
        jobs.push_back(new QLabel(this));
        jobs[i]->setGeometry(550,y,300,40);
        Job* job = system->current_company->get_jobs()[i];
        jobs[i]->setText(QString::number(job->get_id()) +"      "+ QString::fromStdString(job->get_title()+"    "+job->get_location()) +"   "+QString::number(job->get_salary()) );
        jobs[i]->setStyleSheet("background-color :white; ");
        y+=50;
    }
}
