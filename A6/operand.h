#ifndef __OPERAND_H__
#define __OPERAND_H__ 

#include "node.h"

class OperandChildException{};
class OperandModeException{};
class ValueException{};
class BaseException{};
class UnknownBaseException{};

class Operand:public Node
{
public:
	Operand(int _id,Tree& _tree):Node(_id,_tree){}
	virtual int eval()=0;
	virtual void add_child_id(int _id);//Just throw some Exception
	virtual void change_value(string _value)=0;
	virtual void change_base(char _base);
	virtual void change_mode(char _mode);//~
	virtual bool check();
protected:
	string value;
};
class OpB:public Operand
{
public:
	OpB(int _id,Tree& _tree,string _value):Operand(_id,_tree){change_value(_value);}
	virtual void change_value(string _value);
	// virtual void change_base(char _base);
	virtual int eval();
};
class OpO:public Operand
{
public:
	OpO(int _id,Tree& _tree,string _value):Operand(_id,_tree){change_value(_value);}
	virtual void change_value(string _value);
	// virtual void change_base(char _base);
	virtual int eval();
};
class OpD:public Operand
{
public:
	OpD(int _id,Tree& _tree,string _value):Operand(_id,_tree){change_value(_value);}
	virtual void change_value(string _value);
	// virtual void change_base(char _base);
	virtual int eval();
};
class OpH:public Operand
{
public:
	OpH(int _id,Tree& _tree,string _value):Operand(_id,_tree){change_value(_value);}
	virtual void change_value(string _value);
	// virtual void change_base(char _base);
	virtual int eval();
};

#endif