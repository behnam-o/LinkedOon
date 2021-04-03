#include "../headers/utils.h"
#include <iostream>
using namespace std;

string get_command()
{
	string line;
	cout<<"> ";
	getline(cin,line);
	return line;
}

vector<string> split_string(string str,char c)
{
	vector<string> result;
	int char_pos=0;
	while(char_pos!=-1)
	{
		char_pos=str.find(c);
		result.push_back(str.substr(0,char_pos));
		str=str.substr(char_pos+1);
	}
	return result;
}