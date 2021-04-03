#ifndef __OPERATOR_H__
#define __OPERATOR_H__ 


#include "node.h"
class OperatorValueException{};
class OperatorBaseException{};
class ChildFullException{};

class Operator:public Node
{
public:
	Operator(int _id,Tree& _tree):Node(_id,_tree){}
	virtual int eval()=0;
	virtual void add_child_id(int _id)=0;
	virtual void change_value(string _value); // Just throw some exception
	virtual void change_base(char _base);  // ~
	virtual void change_mode(char _mode)=0;
	virtual bool check()=0;
};
class And:public Operator
{
public:
	And(int _id,Tree& _tree):Operator(_id,_tree){}
	virtual int eval()=0;
	virtual void add_child_id(int _id);
	virtual void change_mode(char _mode);
	virtual bool check();
};
class AndA:public And
{
public:
	AndA(int _id,Tree& _tree):And(_id,_tree){}
	virtual int eval();
};
class AndB:public And
{
public:
	AndB(int _id,Tree& _tree):And(_id,_tree){}
	virtual int eval();
};
class Or:public Operator
{
public:
	Or(int _id,Tree& _tree):Operator(_id,_tree){}
	virtual int eval()=0;
	virtual void add_child_id(int _id);
	virtual void change_mode(char _mode);
	virtual bool check();
};
class OrA:public Or
{
public:
	OrA(int _id,Tree& _tree):Or(_id,_tree){}
	virtual int eval();
};
class OrB:public Or
{
public:
	OrB(int _id,Tree& _tree):Or(_id,_tree){}
	virtual int eval();
};
class Not:public Operator
{
public:
	Not(int _id,Tree& _tree):Operator(_id,_tree){}
	virtual int eval()=0;
	virtual void add_child_id(int _id);
	virtual void change_mode(char _mode);
	virtual bool check();
};
class NotA:public Not
{
public:
	NotA(int _id,Tree& _tree):Not(_id,_tree){}
	virtual int eval();
};
class NotB:public Not
{
public:
	NotB(int _id,Tree& _tree):Not(_id,_tree){}
	virtual int eval();
};
class Xor:public Operator
{
public:
	Xor(int _id,Tree& _tree):Operator(_id,_tree){}
	virtual int eval()=0;
	virtual void add_child_id(int _id);
	virtual void change_mode(char _mode);
	virtual bool check();
};
class XorA:public Xor
{
public:
	XorA(int _id,Tree& _tree):Xor(_id,_tree){}
	virtual int eval();
};
class XorB:public Xor
{
public:
	XorB(int _id,Tree& _tree):Xor(_id,_tree){}
	virtual int eval();
};

#endif