#include "warehouse.h"


ShipItem ShipItem::translate_ship_item(string ship_item_str)
{
	vector<string> comps=split_string(ship_item_str,',');
	if (comps.size()!=3)
		throw ShipItemStringException();
	return ShipItem(comps[0],atoi(comps[1].c_str()),atoi(comps[2].c_str()));
}
ShipItem& ShipItem::operator--(int)
{
	if (quantity<=0)
		throw OutOfShipItemException();
	quantity--;
	return *this;
}

vector<ShipItem> Shipment::translate_shipment(string ship_str)
{
	vector<ShipItem> shipment;
	vector<string> comps=split_string(ship_str,'[');
	for (int i = 1; i < comps.size(); i++)
	{
		string item_str=comps[i].substr(0,comps[i].find(']')+1);
		ShipItem item=ShipItem::translate_ship_item(item_str);
		shipment.push_back(item);
	}
	
	return shipment;
}
int Warehouse::get_total_quantity(string ship_item_str)
{
	int result=0;
	bool found=false;
	for (int i = 0; i < shipments.size(); i++)
	{
		for (int j = 0; j < shipments[i].items.size(); j++)
		{
			if (shipments[i].items[j].get_name()==ship_item_str)	
			{
				found=true;
				result+=shipments[i].items[j].get_quantity();
			}
		}
	}
	if (!found)
		throw ShipItemNotFoundException();
	return result;
}
int Warehouse::get_total_value(string ship_item_str)
{
	int result=0;
	for (int i = 0; i < shipments.size(); i++)
	{
		for (int j = 0; j < shipments[i].items.size(); j++)
		{
			if (shipments[i].items[j].get_name()==ship_item_str)	
			{
				result+=shipments[i].items[j].get_quantity()*shipments[i].items[j].get_unit_price();
			}
		}
	}
	return result;
}
int Warehouse::value()
{
	vector<string> names;
	int result=0;
	for (int i = 0; i < shipments.size() ; i++)
	{
		for (int j = 0; j < shipments[i].items.size(); j++)
		{
			bool found=false;
			for (int k = 0; k < names.size(); k++)
			{
				if (names[k]==shipments[i].items[j].get_name())
				{
					found=true;
					break;
				}
			}
			if (!found)
				names.push_back(shipments[i].items[j].get_name());
		}
	}
	for (int i = 0; i < names.size(); i++)
		result+=get_total_value(names[i]);
	return result;
}
int	Warehouse::get_last_unit_price(string ship_item_str)
{
	for (int i = shipments.size()-1; i>=0; i--)
	{
		for (int j = 0; j < shipments[i].items.size(); j++)
		{
			if (shipments[i].items[j].get_name()==ship_item_str)	
			{
				return shipments[i].items[j].get_unit_price();
			}
		}
	}
	throw
		ShipItemNotFoundException();
}



void Warehouse::take(int n, string ship_item)
{
	bool found=false;
	for (int i = 0; i < shipments.size(); i++)
	{
		for (int j = 0; j < shipments[i].items.size(); j++)
		{
			if (shipments[i].items[j].get_name()==ship_item)
			{	
				found=true;
				while(shipments[i].items[j].get_quantity()!=0 && n!=0)
				{
					shipments[i].items[j]--;
					n--;
				}
			}
		}
	}
	if (n!=0)
		throw OutOfShipItemException();
}
void Warehouse::show()
{
	vector<string> names;
	for (int i = 0; i < shipments.size() ; i++)
	{
		for (int j = 0; j < shipments[i].items.size(); j++)
		{
			bool found=false;
			for (int k = 0; k < names.size(); k++)
			{
				if (names[k]==shipments[i].items[j].get_name())
				{
					found=true;
					break;
				}
			}
			if (!found)
				names.push_back(shipments[i].items[j].get_name());
		}
	}
	sort(names);
	for (int i = 0; i < names.size(); i++)
		cout<<left<<setw(5)<<i+1<<left<<setw(20)<<names[i]<<left<<setw(10)<<get_total_quantity(names[i])<<left<<setw(10)<<get_total_value(names[i])<<endl;
}
int Warehouse::price_of(int n,string ship_item)
{

	int result=0;
	bool found=false;
	for (int i = 0; i < shipments.size(); i++)
	{
		for (int j = 0; j < shipments[i].items.size(); j++)
		{
			if (shipments[i].items[j].get_name()==ship_item)
			{
				found=true;
				int num=shipments[i].items[j].get_quantity();
				while(num!=0 && n!=0)
				{
					num--;
					n--;
					result+=shipments[i].items[j].get_unit_price();
				}
			}
		}
	}
	if(!found)
		throw ShipItemNotFoundException();
	if (n!=0)
		throw OutOfShipItemException();
	return result;
}