#ifndef __BUTLER_H__
#define __BUTLER_H__

#include <string>
#include <vector>
using namespace std;
class System;
class Butler
{
public:
	Butler(System* sys): system(sys) {}
	void act(string command);
private:
	System* system;
	void signupu(vector<string> args);
	void signupc(vector<string> args);
	void login(vector<string> args);
	void logout();
	void change_f_name(vector<string> args,string command);
	void change_l_name(vector<string> args,string command);
	void add_education(vector<string> args,string command);
	void add_experience(vector<string> args,string command);
	void add_skill(vector<string> args,string command);
	void search_company(vector<string> args,string command);
	void search_user(vector<string> args,string command);
	void show_user(vector<string> args);
	void show_usernames();
	void show_company(vector<string> args);
	void show_profileu();
	void show_profilec();
	void change_name(vector<string> args,string command); // Comp Name
	void change_ceo(vector<string> args,string command); // Comp CEO
	void change_description(vector<string> args,string command); // Comp discription
	void add_job(vector<string> args,string command);
	void apply(vector<string> args,string command);
	void confirm(vector<string> args,string command);

};

#endif