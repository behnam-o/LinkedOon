#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "headers/system.h"
#include "headers/user.h"
#include "headers/education.h"
#include "headers/skill.h"
#include "headers/experience.h"
#include "headers/company.h"
#include "headers/job.h"

SearchWindow::SearchWindow(QString search ,System* sys , QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    system = sys;
   users= system->search_user(search.toStdString());
   companies = system->search_company(search.toStdString());
    set_results();
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::set_results()
{

    if(users.size() == 0 && companies.size()==0){
        QLabel* no_result = new QLabel(this);
        no_result->setGeometry(50,200,200,50);
        no_result->setText("No Results Found .");
    }
    else{
        int y = 200;
        QLabel* userlabel = new QLabel(this);
        userlabel->setText("Users");
        userlabel->setGeometry(50,y,80,40);
        userlabel->setStyleSheet("font-size : 15px;");
        for(int i = 0 ; i<users.size() ; i++){
            user_results.push_back(new QLabel(this));
            user_results[i]->setGeometry(200,y,400,40);
            user_results[i]->setText(QString::fromStdString(users[i]->get_username()+":   "+users[i]->get_f_name()+"  "+users[i]->get_l_name()));
            y+=50;
        }
        if(users.size()==0) y+=50;
        QLabel* companylabel = new QLabel(this);
        companylabel->setText("Companies");
        companylabel->setGeometry(50,y,80,40);
        companylabel->setStyleSheet("font-size : 15px;");
        for(int i = 0 ; i<companies.size() ; i++){
            company_results.push_back(new QLabel(this));
            company_results[i]->setGeometry(200,y,400,40);
            company_results[i]->setText(QString::fromStdString(companies[i]->get_username()+":  "+companies[i]->get_name()+"    "+companies[i]->get_ceo()));
            y+=50;
        }
    }

}
