#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include <vector>
#include "customer.h"

class Transaction;

class Account
{
public:
	Account(vector<Customer*> _owners,double _balance,int _id)
		{owners=_owners;balance=_balance;id=_id;};
	// ~Account(){cout<<"Account "<<id<<" deleted"<<endl;};
	void add_owner(Customer* customer)
		{owners.push_back(customer);};
	void add_transaction(Transaction* transaction)
		{transactions.push_back(transaction);};
	vector<int> get_owner_ids();
	void transact(Transaction& t);
	double get_balance(){return balance;};
	void show_info();
private:
	int id;
	double balance;
	vector<Customer*> owners;
	vector<Transaction*> transactions;
};
#endif