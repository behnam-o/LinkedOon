#ifndef __RECIPE_H
#define __RECIPE_H 

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "helpers.h"
#include "warehouse.h"

using namespace std;

class RecipeItemStringException{};
class RecipeItem
{
	public:
		RecipeItem(string n,int q):name(n),quantity(q){}
		string get_name() { return name; }
		int get_quantity() { return quantity; }
		static RecipeItem translate_recipe_item(string s);
	private:
		string name;
		int quantity;
};

class Recipe
{
public:
	Recipe(string n,vector<RecipeItem> i): name(n),items(i) {}
	static vector<RecipeItem>  translate_recipe(string s);
	string get_name() {return name;}
	void show_ingredients();
	int price(Warehouse w);
	void estimate(int n,Warehouse w);
	vector<RecipeItem> items;
private:
	
	void sort_items();
	string name;
};

#endif