#ifndef __EXPERIENCE_H__
#define __EXPERIENCE_H__ 

#include <string>

using namespace std;

class Experience
{
	public:
		Experience(string p, string o, unsigned int sy,unsigned int ey):
			position(p),
			organization(o),
			start_year(sy),
			end_year(ey)
		{}
		string get_position() { return position; }
		string get_organization() { return organization; }
		unsigned int get_start_year() { return start_year; }
		unsigned int get_end_year() { return end_year; }
		string to_string() { return position+" at "+organization; }
	private:
		string position;
		string organization;
		unsigned int start_year;
		unsigned int end_year;
};	
#endif