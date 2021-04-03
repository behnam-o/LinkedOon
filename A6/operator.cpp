#include "operator.h"

void Operator::change_value(string _value)
{
	throw OperatorValueException();	
} 
void Operator::change_base(char _base)
{
	throw OperatorBaseException();
}
void And::add_child_id(int _id)
{
	if (child_ids.size()>=2)
	{
		throw ChildFullException();
	}
	child_ids.push_back(_id);
}
void And::change_mode(char _mode)
{
	And* temp;
	if (_mode=='a')
	{
		temp=new AndA(id,*tree);
		for (int i = 0; i < child_ids.size(); i++)
		{
			temp->add_child_id(child_ids[i]);
		}
		// (*tree)[id]=temp;
	}
	else if (_mode=='b')
	{
		temp=new AndB(id,*tree);
		for (int i = 0; i < child_ids.size(); i++)
		{
			temp->add_child_id(child_ids[i]);
		}
		// (*tree)[id]=temp;
	}
	delete this;
}
bool And::check()
{
	if (child_ids.size()!=2)
	{
		return false;
	}
	return true;
}
int AndA::eval()
{
	return (*tree)[child_ids[0]]->eval()*(*tree)[child_ids[1]]->eval();
}
int AndB::eval()
{
	return (*tree)[child_ids[0]]->eval()&(*tree)[child_ids[1]]->eval();
}
void Or::add_child_id(int _id)
{
	if (child_ids.size()>=2)
	{
		throw ChildFullException();
	}
	child_ids.push_back(_id);
}
void Or::change_mode(char _mode)
{
	Or* temp;
	if (_mode=='a')
	{
		temp=new OrA(id,*tree);
		for (int i = 0; i < child_ids.size(); i++)
		{
			temp->add_child_id(child_ids[i]);
		}
		// (*tree)[id]=temp;
	}
	else if (_mode=='b')
	{
		temp=new OrB(id,*tree);
		for (int i = 0; i < child_ids.size(); i++)
		{
			temp->add_child_id(child_ids[i]);
		}
		// (*tree)[id]=temp;
	}
	delete this;
}
bool Or::check()
{
	if (child_ids.size()!=2)
	{
		return false;
	}
	return true;
}
int OrA::eval()
{
	return (*tree)[child_ids[0]]->eval()+(*tree)[child_ids[1]]->eval();
}
int OrB::eval()
{
	return (*tree)[child_ids[0]]->eval()|(*tree)[child_ids[1]]->eval();
}
void Not::add_child_id(int _id)
{
	if (child_ids.size()>=1)
	{
		throw ChildFullException();
	}
	child_ids.push_back(_id);
}
void Not::change_mode(char _mode)
{
	Not* temp;
	if (_mode=='a')
	{
		temp=new NotA(id,*tree);
		for (int i = 0; i < child_ids.size(); i++)
		{
			temp->add_child_id(child_ids[i]);
		}
		// (*tree)[id]=temp;
	}
	else if (_mode=='b')
	{
		temp=new NotB(id,*tree);
		for (int i = 0; i < child_ids.size(); i++)
		{
			temp->add_child_id(child_ids[i]);
		}
		// (*tree)[id]=temp;
	}
	delete this;
}
bool Not::check()
{
	if (child_ids.size()!=1)
	{
		return false;
	}
	return true;
}
int NotA::eval()
{
	return -(*tree)[child_ids[0]]->eval();
}
int NotB::eval()
{
	return ~(*tree)[child_ids[0]]->eval();
}
void Xor::add_child_id(int _id)
{
	child_ids.push_back(_id);
}
void Xor::change_mode(char _mode)
{
	Xor* temp;
	if (_mode=='a')
	{
		temp=new XorA(id,*tree);
		for (int i = 0; i < child_ids.size(); i++)
		{
			temp->add_child_id(child_ids[i]);
		}
		// (*tree)[id]=temp;
	}
	else if (_mode=='b')
	{
		temp=new XorB(id,*tree);
		for (int i = 0; i < child_ids.size(); i++)
		{
			temp->add_child_id(child_ids[i]);
		}
		// (*tree)[id]=temp;
	}
	delete this;
}
bool Xor::check()
{
	if (child_ids.size()==0)
	{
		return false;
	}
	return true;
}
int XorA::eval()
{
	int result=0;
	for (int i = 0; i < child_ids.size(); i++)
	{
		result+=(*tree)[child_ids[i]]->eval();
	}
	return result/child_ids.size();
}
int XorB::eval()
{
	int result=0;
	for (int i = 0; i < child_ids.size(); i++)
	{
		result^=(*tree)[child_ids[i]]->eval();
	}
	return result;
}