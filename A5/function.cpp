#include "function.h"
#include <iostream>

Function operator+(const Pair& pair,const Function& f)
{
	return f+pair;
}
Function operator+(const double x,const Function& f)
{
	return f+x;
}
Function operator*(const double x,const Function& f)
{
	return f*x;
}
Function operator-(const double x,const Function& f)
{
	return (-1*f)+x;
}
ostream& operator<<(ostream& out,const Function& f)
{
	vector<Pair> p=f.get_pairs();
	for (int i = 0; i < p.size(); i++)
	{
		out<<"("<<p[i].get_p1()<<","<<p[i].get_p2()<<")";
		if (i!=p.size()-1)
			out<<", ";
	}
	return out;
}

Function::Function(const Function& g)
{
	*this=g;
}
void Function::add_pair(const Pair& pair)
{
	for (int i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].p1==pair.p1)
		{
			throw Already_Defined_Exception();
		}
	}
	pairs.push_back(pair);
}
void Function::remove_pair(const Pair& pair)
{
	for (int i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].p1==pair.p1 && pairs[i].p2==pair.p2)
		{
			pairs.erase(pairs.begin()+i);
			return;
		}
	}
	throw No_Such_Pair_Exception();
}
Function Function::operator+(const Pair& pair) const
{

	Function f2=*this;
	try{
		f2.add_pair(pair);
	}catch(Already_Defined_Exception e){
		cout<<"This pair is already defined."<<endl;
	}
	return f2;
}
Function Function::operator-(const Pair& pair) const
{
	Function f2=*this;
	try{
		f2.remove_pair(pair);
	}catch(No_Such_Pair_Exception e){
		cout<<"Function does not containg such pair."<<endl;
	}
	return f2;
}
Function& Function::operator+=(const Pair& pair)
{
	*this=(*this)+pair;
	return *this;
}
Function& Function::operator-=(const Pair& pair)
{

	*this=(*this)-pair;
	return *this;
}


double& Function::operator()(double x)
{
	for (int i = 0; i < pairs.size(); i++)
	{
		if (x==pairs[i].p1)
		{
			return pairs[i].p2;
		}
	}
	throw No_Such_Pair_Exception();
}

Function Function::operator+(const double x) const
{
	Function f2=*this;
	for (int i = 0; i < f2.pairs.size(); i++)
	{
		f2.pairs[i].p2+=x;
	}
	return f2;
}
Function Function::operator*(const double x) const
{
	Function f2=*this;
	for (int i = 0; i < f2.pairs.size(); i++)
	{
		f2.pairs[i].p2*=x;
	}
	return f2;
}
Function Function::operator-(const double x) const
{
	Function f2=*this;
	for (int i = 0; i < f2.pairs.size(); i++)
	{
		f2.pairs[i].p2-=x;
	}
	return f2;
}
Function Function::operator/(const double x) const
{	
	Function f2=*this;
	if (x==0)
	{
		cout<<"Cannot divide by 0."<<endl;
		return f2; 
	}
	for (int i = 0; i < f2.pairs.size(); i++)
	{
		f2.pairs[i].p2/=x;
	}
	return f2;
}
Function& Function::operator+=(const double x)
{
	*this=(*this)+x;
	return *this;
}
Function& Function::operator*=(const double x)
{
	*this=(*this)*x;
	return *this;
}
Function& Function::operator-=(const double x)
{
	*this=(*this)-x;
	return *this;
}
Function& Function::operator/=(const double x)
{
	*this=(*this)/x;
	return *this;
}
Function& Function::operator++()
{
	*this=(*this)+1;
	return *this;
}
Function Function::operator++(int)
{
	Function temp=*this;
	*this=(*this)+1;
	return temp;
}
Function& Function::operator--()
{
	*this=(*this)-1;
	return *this;
}
Function Function::operator--(int)
{
	Function temp=*this;
	*this=(*this)-1;
	return temp;
}




Function Function::operator+(const Function& f2) const
{
	Function f1;
	for (int i = 0; i < pairs.size(); i++)
	{
		for (int j = 0; j < f2.pairs.size(); j++)
		{
			if (pairs[i].p1==f2.pairs[j].p1)
			{
				f1+=Pair(pairs[i].p1,pairs[i].p2+f2.pairs[j].p2);
				break;
			}
		}
	}
	return f1;
}
Function Function::operator-(const Function& f2) const
{
	Function f1;
	for (int i = 0; i < pairs.size(); i++)
	{
		for (int j = 0; j < f2.pairs.size(); j++)
		{
			if (pairs[i].p1==f2.pairs[j].p1)
			{
				f1+=Pair(pairs[i].p1,pairs[i].p2-f2.pairs[j].p2);
				break;
			}
		}
	}
	return f1;
}
Function& Function::operator+=(const Function& f2)
{
	*this=*this+f2;
	return *this;
}
Function& Function::operator-=(const Function& f2)
{
	*this=*this-f2;
	return *this;
}
bool Function::operator==(const Function& f2) const
{
	bool found;
	int s1=pairs.size();
	int s2=f2.pairs.size();
	if(s1!=s2)
		return false;
	for (int i = 0; i < s1; i++)
	{
		found=false;
		for (int j = 0; j < s2; j++)
		{
			if (pairs[i].p1==f2.pairs[j].p1 && pairs[i].p2==f2.pairs[j].p2)
			{
				found=true;
				break;
			}
		}
		if (!found)
			return false;
	}
	return true;
}
Function Function::operator|(const Function& f2) const
{
	Function f1=*this;
	for (int i = 0; i < f2.pairs.size(); i++)
	{
		try{
			f1+=f2.pairs[i];
		}catch(Already_Defined_Exception e){
			f1(f2.pairs[i].p1)+=f2.pairs[i].p2;
		}
	}
	return f1;
}
Function& Function::operator|=(const Function& f2)
{
	*this=*this|f2;
	return *this;
}
Function Function::operator()(const Function& g) const
{
	Function fog;
	for (int i = 0; i < pairs.size(); i++)
	{
		for (int j = 0; j < g.pairs.size(); j++)
		{
			if(pairs[i].p1==g.pairs[j].p2)
				fog+=Pair(g.pairs[j].p1,pairs[i].p2);
		}
	}
	return fog;
} 