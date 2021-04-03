#ifndef __MENU_H
#define __MENU_H 

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "helpers.h"

using namespace std;

class MenuItemStringException{};
class MenuItem
{
	public:
		MenuItem(string d,string n,int p):day(d),name(n),price(p){}
		string get_day() { return day; }
		string get_name() { return name; }
		int get_price() { return price; }
		static MenuItem translate_menu_item(string s);
	private:
		string day;
		string name;
		int price;
};

class Menu
{
public:
	vector<MenuItem> items;
	void add_menu_item(MenuItem i) { items.push_back(i); }
	static Menu translate_menu (string s);
	void show();
};

#endif	