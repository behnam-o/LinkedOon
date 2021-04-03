#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <vector>
#include <iostream>
#include "pair.h"

using namespace std;

Function operator+(const Pair& pair,const Function& f);
Function operator+(const double x,const Function& f);
Function operator*(const double x,const Function& f);
Function operator-(const double x,const Function& f);
ostream& operator<<(ostream& out,const Function& f);

class Already_Defined_Exception{};
class No_Such_Pair_Exception{};

class Function
{
public:
	Function(){};
	Function(const Function& g);
	vector<Pair> get_pairs() const {return pairs;};

	Function operator+(const Pair& pair) const; 
	Function operator-(const Pair& pair) const;	
	Function& operator+=(const Pair& pair);
	Function& operator-=(const Pair& pair);

	double& operator()(double x);

	Function operator+(const double x) const;
	Function operator*(const double x) const;
	Function operator-(const double x) const;
	Function operator/(const double x) const;
	Function& operator+=(const double x);
	Function& operator*=(const double x);
	Function& operator-=(const double x);
	Function& operator/=(const double x);
	Function& operator++();
	Function operator++(int);
	Function& operator--();
	Function operator--(int);

	Function operator+(const Function& f2) const;
	Function operator-(const Function& f2) const;
	Function& operator+=(const Function& f2);// !!
	Function& operator-=(const Function& f2);// !!
	bool operator==(const Function& f2) const;
	Function operator|(const Function& f2) const;
	Function& operator|=(const Function& f2);

	Function operator()(const Function& g) const;

private:
	vector<Pair> pairs;
	void add_pair(const Pair& pair);
	void remove_pair(const Pair& pair);
};

#endif