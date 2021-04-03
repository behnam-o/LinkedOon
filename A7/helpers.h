#ifndef __HELPERS_H
#define __HELPERS_H 

#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<string> split_string(string str,char c);
void sort(vector<string>& v);
void log(string l);
void clear_log();

#endif