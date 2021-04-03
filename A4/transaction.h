#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

#include "account.h"
enum Status { accepted,rejected,pending };

class Transaction
{
public:
	Transaction(Account* _src,Account* _des,double _amount,int _id);
	// ~Transaction(){cout<<"Transaction "<<id<<" deleted"<<endl;};
	void change_decisions(int cus_id,Status decision);
	double get_amount(){return amount;};
	Status get_state(){return state;};
	Account* get_des_account(){return des;};
	Account* get_src_account(){return src;};
private:
	int id;
	Account* src;
	Account* des;
	double amount;
	vector<int> must_approve_ids;
	vector<Status> decisions;
	Status state;
};
#endif