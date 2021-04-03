#ifndef __WAREHOUSE_H
#define __WAREHOUSE_H 

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "helpers.h"

using namespace std;


class ShipItemStringException{};
class OutOfShipItemException{};
class ShipItem
{
	public:
		ShipItem(string n,int q,int up=0):name(n),quantity(q),unit_price(up){}
		string get_name() { return name; }
		int get_quantity() { return quantity; }
		int get_unit_price() { return unit_price; }
		static ShipItem translate_ship_item(string ship_item_str);
		ShipItem& operator--(int);
	private:
		string name;
		int quantity;
		int unit_price;
};

class Shipment
{
	public:
		Shipment(string d,vector<ShipItem> i): date(d),items(i) {}
		vector<ShipItem> items;
		void add_item(ShipItem item) { items.push_back(item); }
		static vector<ShipItem> translate_shipment(string ship_str);
	private:
		string date;
};
class ShipItemNotFoundException{};
class Warehouse
{
	public:
		vector<Shipment> shipments;
		void add_shipment(Shipment ship) { shipments.push_back(ship); }
		int get_total_quantity(string ship_item_str);
		int get_total_value(string ship_item_str);
		int value();
		int	get_last_unit_price(string ship_item_str);
		int price_of(int n,string ship_item);
		void take(int n, string ship_item);
		void show();
};

#endif