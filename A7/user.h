#ifndef __USER_H
#define __USER_H 

#include <string>
#include <iostream>
using namespace std;

class User
{
	public:
		User(string n,string p):name(n),password(p),attempts(0),last_attempt(){}
		string login(string p);
		string name;
	private:
	string password;
	int attempts;
	time_t last_attempt;
};

#endif