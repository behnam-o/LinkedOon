#ifndef __EDUCATION_H__
#define __EDUCATION_H__ 

#include <string>

using namespace std;

class Education
{
	public:
		Education(string d,string s,unsigned int y):
			degree(d),
			school(s),
			year(y)
		{}
		string get_degree() { return degree; }
		string get_school() { return school; }
		unsigned int get_year() { return year; }
		string to_string() { return degree+" from " + school; }
	private:
		string degree;
		string school;
		unsigned int year;
};

#endif