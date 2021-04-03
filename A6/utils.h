#ifndef __UTILS_H__
#define __UTILS_H__ 

#include <string>
#include <vector>
#include "node.h"
#include "operand.h"
#include "operator.h"

int pow(int x,int y);
vector<string> split_string(string str);
char int_to_char(int n);
void show_in_base(int num,char base);
string lower(string str);
Tree make_tree();
void deal(Tree& t,string line,int line_number);
bool check_tree(Tree& t);
#endif