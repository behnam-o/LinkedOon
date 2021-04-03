#include "recipe.h"

RecipeItem RecipeItem::translate_recipe_item(string s)
{
	vector<string> comps=split_string(s,',');
	if (comps.size()!=2)
		throw RecipeItemStringException();
	return RecipeItem(comps[0],atoi(comps[1].c_str()));
}

vector<RecipeItem> Recipe::translate_recipe(string s)
{
	vector<RecipeItem> v;
	vector<string> comps=split_string(s,'[');
	for (int i = 1; i < comps.size(); i++)
	{
		string item_str=comps[i].substr(0,comps[i].find(']')+1);
		RecipeItem item=RecipeItem::translate_recipe_item(item_str);
		v.push_back(item);
	}
	
	return v;
}
void Recipe::show_ingredients()
{
	for (int i = 0; i < items.size()-1; i++)
	{
		cout<<items[i].get_name()<<": "<<items[i].get_quantity()<<", ";
	}
	cout<<items[items.size()-1].get_name()<<": "<<items[items.size()-1].get_quantity()<<endl;
}
int Recipe::price(Warehouse w)
{
	int result=0;
	try{
		for (int i = 0; i < items.size(); i++)
		result+=w.price_of(items[i].get_quantity(),items[i].get_name());
		return result;
	}catch(ShipItemNotFoundException e){
		cout<<"Some items were not found in the warehouse"<<endl;
		return 0;
	}
	
}

void Recipe::estimate(int n,Warehouse w)
{
	sort_items();
	int tp=0;
	cout<<left<<setw(20)<<"ingredient"<<left<<setw(20)<<"required"<<left<<setw(20)<<"available"<<left<<setw(20)<<"purchase price"<<endl;
	for (int i = 0; i < items.size(); i++)
	{
		string s=items[i].get_name();
		int req=items[i].get_quantity()*n;
		int av;
		int p;
		try{
			av=w.get_total_quantity(items[i].get_name());
			p=(av>=req)?0:(req-av)*w.get_last_unit_price(items[i].get_name());

		}catch(ShipItemNotFoundException e){
			p=-1;
			av=0;
		}
		cout<<left<<setw(20)<<s<<left<<setw(20)<<req<<left<<setw(20)<<av;
		if(p>=0)
		{
			cout<<left<<setw(20)<<p<<endl;
			tp+=p;
		}
		else
			cout<<"NA"<<endl;
	}
	cout<<left<<setw(60)<<"";
	cout<<tp<<endl;

}
void Recipe::sort_items()
{
	for (int i = 0; i < items.size(); i++)
	{
		for (int j = i+1; j < items.size(); j++)
		{
			if (items[j].get_name()<items[i].get_name())
			{
				RecipeItem temp=items[i];
				items[i]=items[j];
				items[j]=temp;
			}
		}
	}
}