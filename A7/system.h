#ifndef __SYSTEM_H
#define __SYSTEM_H 

#include <string>
#include <vector>
#include <fstream>
#include "helpers.h"
#include "user.h"
#include "warehouse.h"
#include "recipe.h"
#include "menu.h"
#include "reserve.h"

using namespace std;

class System
{
	public:
		System():menu_confirmed(false),next_reserve_id(0){}
		void load_users(string user_file_name);
		void load_warehouse(string warehouse_file_name);
		void load_recipes(string recipes_file_name);
		vector<User> users;
		Warehouse warehouse;
		vector<Recipe> recipes;
		Menu last_menu;
		Menu menu;
		vector<Reservation> reservations;
		int next_reserve_id;
		bool menu_confirmed;
};
#endif