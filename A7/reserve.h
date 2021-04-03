#ifndef __RESERVE_H__
#define __RESERVE_H__ 

#include <string>
using namespace std;
class Reservation
{
public:
	Reservation(int i,string u,string d,string m,int c,int p):id(i),username(u),day(d),meal(m),cost(c),price(p){}
	int get_id() {return id;}
	int get_cost() {return cost;}
	int get_price() {return price;}
	string get_username() { return username;}
	string get_day() { return day; }
	string get_meal() { return meal; }
private:
	int id;
	int cost;
	int price;
	string username;
	string day;
	string meal;
};

#endif