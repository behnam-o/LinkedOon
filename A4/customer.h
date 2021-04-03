#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__

#include <string>
#include <iostream>

using namespace std;

class Customer
{
public:
	Customer(string _name,string _surname,int _id){id=_id;name=_name;surname=_surname;};
	// ~Customer(){cout<<"Customer "<<id<<" deleted"<<endl;};
	int get_id(){return id;};
	string get_name(){return name;};
	string get_surname(){return surname;};
	void print(){cout<<name<<" "<<surname;};
private:
	int id;
	string name;
	string surname;
};
#endif