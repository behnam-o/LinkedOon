#include "actions.h"

int main()
{
	string command;
	string user="";
	System system;
	system.load_users("users.txt");
	system.load_warehouse("warehouse.txt");
	system.load_recipes("recipes.txt");
	clear_log();
	log("program started");
	while(1)
	{	
		command=get_command();log(command);if (command=="exit") break;
		act(system,user,command);
	}
	return 0;
}