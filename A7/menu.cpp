#include "menu.h"


MenuItem MenuItem::translate_menu_item(string s)
{
	vector<string> comps=split_string(s,',');
	bool validday= ( comps[0]=="SAT" || comps[0]=="SUN" || 
					 comps[0]=="MON" || comps[0]=="TUE" || 
					 comps[0]=="WED" || comps[0]=="THU" || 
					 comps[0]=="FRI");
	if (comps.size()!=3 || !validday)
		throw MenuItemStringException();
	return MenuItem(comps[0],(comps[1][0]==' ')?comps[1].substr(1):comps[1],atoi(comps[2].c_str()));
}

Menu Menu::translate_menu(string s)
{
	Menu menu;
	vector<string> comps=split_string(s,'[');
	for (int i = 1; i < comps.size(); i++)
	{
		string item_str=comps[i].substr(0,comps[i].find(']')+1);
		MenuItem item=MenuItem::translate_menu_item(item_str);
		menu.add_menu_item(item);
	}
	return menu;
}
void Menu::show()
{
	string days[7]={"SAT","SUN","MON","TUE","WED","THU","FRI"};
	for (int d = 0; d < 7; d++)
	{	
		bool empty=true;
		cout<<days[d]<<endl;
		for (int i = 0; i < items.size(); i++)
		{
			if (items[i].get_day()==days[d])
			{
				empty=false;
				cout<<"- "<<items[i].get_name()<<" ("<<items[i].get_price()<<")"<<endl;
			}
		}
		if (empty)
			cout<<"-"<<endl;
	}
	
}