#include "loginwindow.h"
#include <QApplication>
#include <iostream>
#include <string>
#include "./headers/utils.h"
#include "./headers/user.h"
#include "./headers/education.h"
#include "./headers/experience.h"
#include "./headers/skill.h"
#include "./headers/company.h"
#include "./headers/job.h"
#include "./headers/system.h"
#include "./headers/butler.h"
using namespace std;
int main(int argc, char *argv[])
{

   if (argc>1 && argv[1]==string("-gui") ){
       cout<<"GUI requested"<<endl;
        System system;
        QApplication a(argc, argv);
        LoginWindow w(&system);
        w.showMaximized()   ;

        return a.exec();
   }
   else{
       System system;
       string command;
       Butler but(&system);
       cout<<"==========================\n== Welcome to LinkedOON ==\n==========================\n"<<endl;
       while(1)
       {
           command=get_command();
           but.act(command);
       }
       return 0;
   }
}
