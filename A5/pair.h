#ifndef __PAIR_H__
#define __PAIR_H__

using namespace std;

class Function;
class Pair
{
public:
	Pair(){};
	Pair(double _p1,double _p2){p1=_p1;p2=_p2;};
	double get_p1() const {return p1;};
	double get_p2() const {return p2;};
private:
	double p1;
	double p2;
	friend Function;
};


#endif