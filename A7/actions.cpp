#include "actions.h"


string get_command()
{
	cout<<"> ";
	string line;
	getline(cin,line);
	return line;
}
void act(System& system,string& user,string command)
{
	if(command=="")
		return;
	if (user=="")
		act_login(system,user,command);
	else if (user=="admin")
		act_admin(system,user,command);
	else
		act_user(system,user,command);
}
void act_login(System& system,string& user,string command)
{
	vector<string> args=split_string(command,' ');
	if (args[0]!="login")
	{
		cout<<"Unknown Command"<<endl;
		return;
	}
	if (args.size()!=3)
	{
		cout<<"Invalid Arguments"<<endl;
		return;
	}
	if (args[1]=="admin")
	{
		if (args[2]=="password")
		{
			user="admin";
			cout<<"Admin Account!"<<endl;
			return;
		}
		cout<<"Wrong Password !"<<endl;
		return;	
	}
	for (int i = 0; i < system.users.size(); i++)
	{
		if (args[1]==system.users[i].name)
		{
			user=system.users[i].login(args[2]);
			return;
		}
	}
	cout<<"User Not Found !"<<endl;
}
void act_admin(System& system,string& user,string command)
{	
	vector<string> args=split_string(command,' ');
	if (args[0]=="logout")
	{
		cout<<"Bye, "<<user<<endl;
		user="";
	}
	else if (args[0]=="show")
	{

		if (args.size()<2)
		{
			cout<<"Invalid Arguments"<<endl;
			return;
		}
		if (args[1]=="ingredients")
		{
			system.warehouse.show();
		}
		else if (args[1]=="recipes")
		{
			for (int i = 0; i < system.recipes.size(); i++)
			{
				cout<<left<<setw(5)<<i+1;
				cout<<system.recipes[i].get_name()<<endl;
				cout<<left<<setw(5)<<"";system.recipes[i].show_ingredients();
				cout<<left<<setw(5)<<""<<system.recipes[i].price(system.warehouse)<<endl;
			}
		}
		else if (args[1]=="reservations")
		{
			cout<<left<<setw(15)<<"Customer"<<left<<setw(15)<<"Meal"<<"Day"<<endl;
			if (args.size()==2)
			{
				for (int i = 0; i < system.reservations.size(); i++)
					cout<<left<<setw(15)<<system.reservations[i].get_username()<<left<<setw(15)<<system.reservations[i].get_meal()<<system.reservations[i].get_day()<<endl;
				return;
			}
			if (args.size()!=4)
			{
				cout<<"Unknown Command"<<endl;
				return;
			}
			if (args[2]=="-d")
			{
				if (args[3]!="SAT" && args[3]!="SUN" && args[3]!="MON" && args[3]!="TUE" && args[3]!="WED" && args[3]!="THU" && args[3]!="FRI" )
				{
					cout<<"Invalid Day"<<endl;
					return;
				}
				for (int i = 0; i < system.reservations.size(); i++)
					if (args[3]==system.reservations[i].get_day())
						cout<<left<<setw(15)<<system.reservations[i].get_username()<<left<<setw(15)<<system.reservations[i].get_meal()<<system.reservations[i].get_day()<<endl;
					
				return;	
			}
			cout<<"Invalid Flag"<<endl;
			return;
		}
		else
			cout<<"Unknown Command"<<endl;
	}
	else if (args[0]=="estimate")
	{
		if (args.size()<3)
		{
			cout<<"Invalid Arguments"<<endl;
			return;
		}
		for (int i = 3; i < args.size(); i++)
			args[2]+=" "+args[i];
		for (int i = 0; i < system.recipes.size(); i++)
		{
			if (args[2]==system.recipes[i].get_name())
			{
				system.recipes[i].estimate(atoi(args[1].c_str()),system.warehouse);
				return;
			}
		}
		cout<<"Recipe Not Found"<<endl;
		return;
	}
	else if (args[0]=="shipment")
	{
		for (int i = 2; i < args.size(); i++)
			args[1]+=args[i];
		system.warehouse.add_shipment(Shipment("1-1-1",Shipment::translate_shipment(args[1])));
		cout<<"Current Warehouse Value: "<<system.warehouse.value()<<endl;
		return;
	}
	else if (command=="menu -repeat")
	{
		if (!system.last_menu.items.empty() && !system.menu_confirmed)
		{
			system.menu=system.last_menu;
			system.menu.show();
		}
		else
		{
			cout<<"Cannot repeat menu."<<endl;
			return;
		}
	}
	else if (args[0]=="menu")
	{
		if (system.menu_confirmed)
		{
			cout<<"Menu Alredy Confirmed"<<endl;
			return;
		}
		for (int i = 2; i < args.size(); i++)
			args[1]+=" "+args[i];
		try{
		system.menu=Menu::translate_menu(args[1]);
		}catch(MenuItemStringException e){
			cout<<"Problem with Menu String"<<endl;
			return;
		}
		bool found=false;
		for (int i = 0; i < system.menu.items.size(); i++)
		{
			for (int j = 0; j < system.recipes.size(); j++)
			{
				if (system.recipes[j].get_name()==system.menu.items[i].get_name())
				{
					found = true;
					break;
				}
			}
			if (found)
				break;
		}
		if (!found)
		{
			cout<<"Some Menu Items don't exist in the Recipes ..."<<endl;
			return;
		}
		system.menu.show();
		return;
	}
	else if (command=="confirm menu")
	{
		system.menu_confirmed=true;
		cout<<"Menu Confirmed !"<<endl;
		return;
	}
	else if (command=="finalize reservations")
	{
		if (!system.menu_confirmed)
		{
			cout<<"Menu not Yet Confirmed"<<endl;
			return;
		}
		int total_cost=0;
		int total_sold=0;
		vector<string> meals;
		
		for (int i = 0; i < system.reservations.size(); i++)
		{
			bool found=false;
			for (int j = 0; j < meals.size(); j++)
				if (meals[j]==system.reservations[i].get_meal())
					found=true;
			if (!found)
				meals.push_back(system.reservations[i].get_meal());
		}
		vector<int> num(meals.size(),0);
		for (int i = 0; i < system.reservations.size(); i++)
		{
			total_cost+=system.reservations[i].get_cost();
			total_sold+=system.reservations[i].get_price();
			for (int j = 0; j < meals.size(); j++)
			{
				if (meals[j]==system.reservations[i].get_meal())
				{
					num[j]+=1;
				}
			}
		}
		for (int i = 0; i < meals.size(); i++)
			cout<<meals[i]<<" "<<"( "<<num[i]<<" )"<<endl;
		cout<<"Cost: "<<total_cost<<endl;
		cout<<"Sold: "<<total_sold<<endl;
		double profit = total_sold - total_cost;
		cout<<"Profit: "<<profit<<"( "<< std::setprecision(4) << profit/total_cost*100 <<"% )"<<endl;
		system.last_menu.items=system.menu.items;
		system.menu.items.clear();
		system.menu_confirmed=false;
		system.reservations.clear();
		system.next_reserve_id=0;
	}	
	else
		cout<<"Unknown Command"<<endl;
}
void act_user(System& system,string& user,string command)
{	
	if (command=="show menu")
	{
		if (system.menu_confirmed)
		{
			system.menu.show();
			return;
		}
		cout<<"Menu Not Confirmed"<<endl;
		return;
	}
	else if (command=="show reservations")
	{
		cout<<left<<setw(10)<<"reference"<<left<<setw(6)<<"day"<<"meal"<<endl;
		for (int i = 0; i < system.reservations.size(); i++)
			if (system.reservations[i].get_username()==user)
				cout<<left<<setw(10)<<system.reservations[i].get_id()<<left<<setw(6)<<system.reservations[i].get_day()<<system.reservations[i].get_meal()<<endl;
		return;
	}
	vector<string> args=split_string(command,' ');
	if (args[0]=="reserve")
	{
		if (!system.menu_confirmed)
		{
			cout<<"Menu not Confirmed, Cannot reserve !"<<endl;
			return;
		}
		int cost;
		int price;
		if (args[1]!="SAT" && args[1]!="SUN" && args[1]!="MON" && args[1]!="TUE" && args[1]!="WED" && args[1]!="THU" && args[1]!="FRI" )
		{
			cout<<"Invalid Day"<<endl;
			return;
		}
		if (args.size()>3)
			for (int i = 3; i < args.size(); i++)
				args[2]+=" "+args[i];
		
		for (int i = 0; i < system.menu.items.size(); i++)
		{
			if (args[2]==system.menu.items[i].get_name() && args[1]==system.menu.items[i].get_day())
			{
				price=system.menu.items[i].get_price();
				for (int j = 0; j < system.recipes.size(); j++)
				{
					if (args[2]==system.recipes[j].get_name())
					{
						try{
							cost=system.recipes[j].price(system.warehouse);
						}catch(OutOfShipItemException e){
							cout<<"not enough ingredients"<<endl;
							return;
						}
						system.reservations.push_back(Reservation(system.next_reserve_id,user,args[1],args[2],cost,price));
						system.next_reserve_id++;
						for (int k = 0; k < system.recipes[j].items.size(); k++)
							system.warehouse.take(system.recipes[j].items[k].get_quantity(),system.recipes[j].items[k].get_name());
						cout<<"reference: "<<system.reservations.back().get_id()<<endl;
						return;
					}
				}
			}
		}
		cout<<"Problem with Request! Reservation could not be registered !!!"<<endl;
		return;
	}
	if (command=="logout")
	{
		cout<<"Bye, "<<user<<endl;
		user="";
		return;
	}
	cout<<"Unknown Command!"<<endl;

}



