#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QWidget>
#include <QLabel>
#include <vector>

using namespace std;

class System;
class User;
class Company;

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWindow(QString search , System* sys , QWidget *parent = 0);
    ~SearchWindow();
    void set_results();

private:
    Ui::SearchWindow *ui;
    System* system;
    vector<User*> users;
    vector<Company*> companies;
    vector<QLabel*> user_results;
    vector<QLabel*> company_results;

};

#endif // SEARCHWINDOW_H
