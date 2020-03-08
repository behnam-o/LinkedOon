#include "editcompanyprofwindow.h"
#include "ui_editcompanyprofwindow.h"
#include "companyprofilewindow.h"
#include "headers/system.h"
#include "headers/company.h"
#include "headers/job.h"
#include "headers/utils.h"

EditCompanyprofWindow::EditCompanyprofWindow(System* sys , QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditCompanyprofWindow)
{
    ui->setupUi(this);
    system=sys;
    set_fields_company();
    connect(ui->savebutton , SIGNAL(clicked(bool)) , this , SLOT(save()));
    connect(ui->descbutton , SIGNAL(clicked(bool)) , this ,SLOT(add_description()));
    connect(ui->addjobbutton , SIGNAL(clicked(bool)) ,this ,SLOT(add_job()));
}

EditCompanyprofWindow::~EditCompanyprofWindow()
{
    delete ui;
}

void EditCompanyprofWindow::add_job()
{
//    Job(int i,Company* o,string t, vector<string> skl,int sal,string l,vector<string> k):

    system->current_company->add_job(new Job(system->current_company->get_last_job_id(),system->current_company,ui->titletxt->text().toStdString(),
                                         split_string(ui->skillstxt->text().toStdString(),','),
                                         ui->salarytxt->text().toUInt(),
                                         ui->locationtxt->text().toStdString(),
                                         split_string(ui->keywordstxt->text().toStdString(),','))
                                     );
    EditCompanyprofWindow* win = new EditCompanyprofWindow(system);
    win->showMaximized();
    this->close();
}

void EditCompanyprofWindow::add_description()
{
    system->current_company->set_description(ui->desctxt->text().toStdString());

    EditCompanyprofWindow* win = new EditCompanyprofWindow(system);
    win->showMaximized();
    this->close();
}

void EditCompanyprofWindow::save()
{
    system->current_company->set_name(ui->cnametxt->text().toStdString());
    system->current_company->set_ceo(ui->ceotxt->text().toStdString());

    CompanyProfileWindow* win = new CompanyProfileWindow(system);
    win->showMaximized();
    this->close();
}

void EditCompanyprofWindow::set_fields_company()
{
    ui->usernamelabel->setText(QString::fromStdString(system->current_company->get_username()));
    ui->cnametxt->setText(QString::fromStdString(system->current_company->get_name()));
    ui->ceotxt->setText(QString::fromStdString(system->current_company->get_ceo()));

    ui->desctxt->setText(QString::fromStdString(system->current_company->get_description()));

    int y =350;

    for(int i = 0 ; i<system->current_company->get_jobs().size() ; i++ ){
        jobs.push_back(new QLabel(this));
        jobs[i]->setGeometry(900,y,300,40);
        Job* job = system->current_company->get_jobs()[i];
        jobs[i]->setText(QString::number(job->get_id()) +"      "+ QString::fromStdString(job->get_title()+"    "+job->get_location())+"    "+QString::number(job->get_salary()) );
        jobs[i]->setStyleSheet("background-color :white; ");
        y+=50;
    }
}
