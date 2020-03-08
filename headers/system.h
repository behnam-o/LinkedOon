#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <vector>
#include <string>
using namespace std;

class User;
class Company;
class LoginException{};
class SignupException{};
class System
{
	public:
		System(): current_user(NULL), current_company(NULL) {}
		~System();
		void login(string un,string pw);
		void signupu(string un,string pw);
		void signupc(string un,string pw);
		void logout();
		vector<Company*> get_companies() { return companies; }
		vector<User*> get_users() { return users; }
		User* current_user;
		Company* current_company;
		vector<User*> search_user(string u);
		vector<Company*> search_company(string c);

	private:
		vector<User*> users;
		vector<Company*> companies;
		bool has_username(string un);
};
#endif