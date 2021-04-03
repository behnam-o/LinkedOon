#include "helpers.h"


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
void sort(vector<string>& v)
{
	for (int i = 0; i < v.size(); i++)
		for (int j = i+1; j < v.size(); j++)
			if (v[j]<v[i])
			{
				string temp=v[i];
				v[i]=v[j];
				v[j]=temp;
			}
}
void log(string l)
{
	ofstream log_file("log.txt",fstream::app);
	log_file<<(l+"\n");
	log_file.close();
}
void clear_log()
{
	ofstream log_file("log.txt");
	log_file<<("");
	log_file.close();
}