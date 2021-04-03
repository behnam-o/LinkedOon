#include <fstream>
#include <cstdlib>
#include "customer.h"
#include "account.h"
#include "transaction.h"

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
void deal()
{
	vector<Customer*> customers;
	vector<Account*> accounts;
	vector<Transaction*> transactions;
	string line,command,args;
	while(getline(cin,line))
	{	
		command=line.substr(0,line.find(' '));
		args=line.substr(line.find(' ')+1);

		if(command=="create_customer")
		{	
			vector<string>temp=split_string(args);
			customers.push_back(new Customer(temp.at(0),temp.at(1),customers.size()));
			cout<<customers.size()-1<<endl;
		}
		else if(command=="create_account")
		{
			vector<string> temp=split_string(args);
			double balance=atof(temp.back().c_str());
			temp.pop_back();
			vector<Customer*> customer_ptrs;
			for (int i = 0; i < temp.size(); i++)
			{
				int id=atoi(temp[i].c_str());
				customer_ptrs.push_back(customers.at(id));
			}
			accounts.push_back(new Account(customer_ptrs,balance,accounts.size()));
			cout<<accounts.size()-1<<endl;
		}
		else if(command=="add_owner")
		{
			vector<string> temp=split_string(args);
			int acc_id=atoi(temp.at(0).c_str());
			int customer_id=atoi(temp.at(1).c_str());
			accounts.at(acc_id)->add_owner(customers.at(customer_id));
		}
		else if(command=="show_account")
		{
			int acc_id=atoi(args.c_str());
			accounts.at(acc_id)->show_info();
		}
		else if(command=="book_transaction")
		{
			vector<string> temp=split_string(args);
			int src_id=atoi(temp.at(0).c_str());
			int des_id=atoi(temp.at(1).c_str());
			double amount=atof(temp.at(2).c_str());
			transactions.push_back(new Transaction(accounts.at(src_id),accounts.at(des_id),amount,transactions.size()));
		}
		else if(command=="approve_transaction")
		{
			vector<string> temp=split_string(args);
			int tr_id=atoi(temp.at(0).c_str());
			int cs_id=atoi(temp.at(1).c_str());
			transactions.at(tr_id)->change_decisions(cs_id,accepted);	
		}
		else if(command=="decline_transaction")
		{
			vector<string> temp=split_string(args);
			int tr_id=atoi(temp.at(0).c_str());
			int cs_id=atoi(temp.at(1).c_str());
			transactions.at(tr_id)->change_decisions(cs_id,rejected);		
		}
		else
			cout<<"Unknown Command!"<<endl;
	}
	for (int i = 0; i < customers.size(); i++)
	{
		delete customers[i];
	}
	for (int i = 0; i < accounts.size(); i++)
	{
		delete accounts[i];
	}
	for (int i = 0; i < transactions.size(); i++)
	{
		delete transactions[i];
	}
}
int main()
{
	try
	{
		deal();
	}
	catch(...)
	{
		cout<<"ERROR!"<<endl;
	}
	return 0;
}