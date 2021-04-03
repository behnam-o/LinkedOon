#include <iostream>
#include <cstdlib>
#include "utils.h"

int pow(int x,int y)
{
	int result=1;
	for (int i = 0; i < y; i++)
	{
		result*=x;
	}
	return result;
}

vector<string> split_string(string str)
{
	vector<string> result;
	int space_pos=0;
	while(space_pos!=-1)
	{
		space_pos=str.find(' ');
		result.push_back(str.substr(0,space_pos));
		str=str.substr(space_pos+1);
	}
	return result;
}

char int_to_char(int n)
{
	if (n>=10)
	{	
		return n+55;
	}
	else
		return n+48;
}

void show_in_base(int num,char base)
{
	vector<char> str;
	if (num==0)
	{
		cout<<0;
		return;
	}
	if (num<0)
	{
		cout<<"-";
		num*=-1;
	}



	if (base=='d')
	{
		cout<<num<<endl;
		return;
	}
	else if (base=='b')
	{
		while(num>=2)
		{
			str.push_back(int_to_char(num%2));
			num/=2;
		}
		str.push_back(int_to_char(num));
		while(!str.empty())
		{
				cout<<str.back();
				str.pop_back();
		}
		cout<<endl;
		return;
	}
	else if (base=='o')
	{
		while(num>=8)
		{
			str.push_back(int_to_char(num%8));
			num/=8;
		}
		str.push_back(int_to_char(num));
		while(!str.empty())
		{
				cout<<str.back();
				str.pop_back();
		}
		cout<<endl;
		return;
	}
	else if (base=='h')
	{
		while(num>=16)
		{
			str.push_back(int_to_char(num%16));
			num/=16;
		}
		str.push_back(int_to_char(num));
		while(!str.empty())
		{
				cout<<str.back();
				str.pop_back();
		}
		cout<<endl;
		return;
	}
	else
		throw UnknownBaseException();
}

string lower(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i]>='A'&&str[i]<='Z')
		{
			str[i]+=32;
		}
	}
	return str;
}






Tree make_tree()
{
	int num_of_nodes;
	string line;
	vector<string> args;
	getline(cin,line);
	num_of_nodes=atoi(line.c_str());
	Tree t(num_of_nodes);
	for (int i = 0; i < num_of_nodes; i++)
	{
		getline(cin,line);
		args=split_string(line);
		int child_id =atoi(args[0].c_str());
		int parent_id=atoi(args[1].c_str());
		string node=args[2];
		string val=args[3];
		string val_l=lower(val);
		if (node=="operator")
		{
			if (val=="AND")
			{
				new AndA(child_id,t);
			}
			else if (val=="OR")
			{
				new OrA(child_id,t);
			}
			else if (val=="NOT")
			{
				new NotA(child_id,t);
			}
			else if (val=="XOR")
			{
				new XorA(child_id,t);
			}

		}
		else if (node=="input")
		{
			new OpD(child_id,t,val_l);
		}

		if (parent_id!=-1)
		{
			if (t[parent_id]!=NULL)
			{
				t[parent_id]->add_child_id(child_id);
			}
			else
			{
				throw InaccessibleNodeException();
			}
		}
		// for (int i = 0; i < t.size(); i++)
		// {
		// 	cout<<t[i]<<endl;
		// }
		// cout<<"............."<<endl;


	}
	return t;
}
void deal(Tree& t,string line,int line_number)
{
	try{
		vector<string> args=split_string(line);
		string f=args[0];
		if (f=="evaluate")
		{
			string b=args[1];
			show_in_base(t[0]->eval(),b[1]);
		}
		else if (f=="remode")
		{
			string m=args[1];
			int id=atoi(args[2].c_str());
			t[id]->change_mode(m[1]);
		}
		else if (f=="rebase")
		{
			string b=args[1];
			int id=atoi(args[2].c_str());
			t[id]->change_base(b[1]);
		}
		else if (f=="reset")
		{
			string val=args[2];
			int id=atoi(args[1].c_str());
			t[id]->change_value(val);
		}
	}
	catch(ValueException e){
		cerr<<"Error:line:"<<line_number<<" Cannot Change Value"<<endl;	
	}
	catch(OperandModeException e){
		cerr<<"Error:line:"<<line_number<<" Cannot Change Mode of Operand"<<endl;
	}
	catch(BaseException e){
		cerr<<"Error:line:"<<line_number<<" Cannot Change to This Base"<<endl;
	}
	catch(UnknownBaseException e){
		cerr<<"Error:line:"<<line_number<<" Unknown Base"<<endl;
	}
	catch(ChildFullException e){
		cerr<<"Error:line:"<<line_number<<" Cannot Add anymore children"<<endl;
	}
	catch(OperatorBaseException e){
		cerr<<"Error:line:"<<line_number<<" Cannot Change Base of Operator"<<endl;
	}
	catch(OperatorValueException e){
		cerr<<"Error:line:"<<line_number<<" Cannot Change Value of Operator"<<endl;
	}
}
bool check_tree(Tree& t)
{
	for (int i = 0; i < t.size(); i++)
	{
		if (!(t[i]->check()))
		{
			return false;
		}
	}
	return true;
}