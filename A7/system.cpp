#include "system.h"

void System::load_users(string user_file_name)
{
	ifstream user_file(user_file_name.c_str());
	string line;
	while(getline(user_file,line))
	{
		vector<string> args=split_string(line,' ');
		users.push_back(User(args[0],args[1]));
	}
	user_file.close();
}



void System::load_warehouse(string warehouse_file_name)
{
	ifstream warehouse_file(warehouse_file_name.c_str());
	string line;
	while(getline(warehouse_file,line))
	{
		string next_line;
		getline(warehouse_file,next_line);
		warehouse.add_shipment(Shipment(line.substr(2),Shipment::translate_shipment(next_line)));
	}
	warehouse_file.close();
}



void System::load_recipes(string recipes_file_name)
{
	ifstream recipes_file(recipes_file_name.c_str());
	string line;
	while(getline(recipes_file,line))
	{
		string next_line;
		getline(recipes_file,next_line);
		recipes.push_back(Recipe(line.substr(2),Recipe::translate_recipe(next_line)));
	}
	recipes_file.close();
}