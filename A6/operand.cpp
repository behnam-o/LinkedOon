#include "operand.h"
#include "utils.h"
void Operand::add_child_id(int _id)
{
	throw OperandChildException();
}
void Operand::change_mode(char _mode)
{
	throw OperandModeException();
}
bool Operand::check()
{
	if (child_ids.size()!=0)
	{
		return false;
	}
	return true;
}
void Operand::change_base(char b)
{
	switch(b)
	{
		case 'b':
			for (int i = (value[0]!='-')?0:1; i < value.length(); i++)
			{
				if (value[i]<'0'||value[i]>'7')
				{
					throw BaseException();
				}
			}
			new OpB(id,*tree,value);
			return;
		case 'o':
			for (int i = (value[0]!='-')?0:1; i < value.length(); i++)
			{
				if (value[i]<'0'||value[i]>'7')
				{
					throw BaseException();
					return;
				}
			}
			new OpO(id,*tree,value);
			return;
		case 'd':
			for (int i = (value[0]!='-')?0:1; i < value.length(); i++)
			{
				if (value[i]<'0'||value[i]>'9')
				{
					throw BaseException();
					return;
				}
			}
			new OpD(id,*tree,value);
			return;
		case 'h':
			for (int i =(value[0]!='-')?0:1; i < value.length(); i++)
			{
				if (!((value[i]>='0'&&value[i]<='9')||(value[i]>='a'&&value[i]<='f')))
				{
					throw ValueException();
					return;
				}
			}
			new OpH(id,*tree,value);
			return;
		default:
			throw UnknownBaseException();
			return;
	}
	delete this;
}
void OpB::change_value(string _value)
{
	for (int i = (_value[0]!='-')?0:1; i < _value.length(); i++)
	{
		if (_value[i]<'0'||_value[i]>'1')
		{
			throw ValueException();
			return;
		}
	}
	value=_value;
}
void OpO::change_value(string _value)
{
	for (int i = (_value[0]!='-')?0:1; i < _value.length(); i++)
	{
		if (_value[i]<'0'||_value[i]>'7')
		{
			throw ValueException();
			return;
		}
	}
	value=_value;
}
void OpD::change_value(string _value)
{
	for (int i =(_value[0]!='-')?0:1; i < _value.length(); i++)
	{
		if (_value[i]<'0'||_value[i]>'9')
		{
			throw ValueException();
			return;
		}
	}
	value=_value;
}
void OpH::change_value(string _value)
{
	for (int i =(_value[0]!='-')?0:1; i < _value.length(); i++)
	{
		if (!((_value[i]>='0'&&_value[i]<='9')||(_value[i]>='a'&&_value[i]<='f')))
		{
			throw ValueException();
			return;
		}
	}
	value=_value;
}
int OpB::eval()
{
	int result=0;
	for (int i = (value[0]!='-')?0:1; i < value.length(); i++)
	{
		result+=(value[i]-48)*pow(2,value.length()-i-1);
	}
	return (value[0]!='-')?result:(-1*result);
}
int OpO::eval()
{
	int result=0;
	for (int i = (value[0]!='-')?0:1; i < value.length(); i++)
	{
		result+=(value[i]-48)*pow(8,value.length()-i-1);
	}
	return (value[0]!='-')?result:(-1*result);
}
int OpD::eval()
{
	int result=0;
	for (int i = (value[0]!='-')?0:1; i < value.length(); i++)
	{
		result+=(value[i]-48)*pow(10,value.length()-i-1);
	}
	return (value[0]!='-')?result:(-1*result);
}
int OpH::eval()
{
	int result=0;
	for (int i = (value[0]!='-')?0:1; i < value.length(); i++)
	{
		if (value[i]>='0'&&value[i]<='9')
		{
			result+=(value[i]-48)*pow(16,value.length()-i-1);
		}
		else if (value[i]>='a'&&value[i]<='f')
		{
			result+=(value[i]-87)*pow(16,value.length()-i-1);
		}
	}
	return (value[0]!='-')?result:(-1*result);
}