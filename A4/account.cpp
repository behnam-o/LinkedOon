#include "account.h"
#include "transaction.h"
void Account::transact(Transaction& t)
{
	if (t.get_state()==accepted && t.get_src_account()->id==id)
	{
		balance-=t.get_amount();
		t.get_des_account()->balance+=t.get_amount();
	}
}
vector<int> Account::get_owner_ids()
{
	vector<int> result;
	for (int i = 0; i < owners.size(); i++)
	{
		result.push_back(owners[i]->get_id());
	}
	return result;
}
void Account::show_info()
{
	cout<<"Balance : "<<balance<<endl;
	cout<<"Owners : ";
	for (int i = 0; i < owners.size(); i++)
	{
		owners[i]->print();
		if (i==owners.size()-1)
			cout<<endl;
		else
			cout<<" , ";
	}
	if (!transactions.empty())
	{
		cout<<"Transactions:"<<endl;
		for (int i = 0; i < transactions.size(); i++)
		{
			Transaction* t=transactions[i];
			int src_id=t->get_src_account()->id;
			int des_id=t->get_des_account()->id;
			cout<<"["<<i+1<<"] "<< t->get_amount();
			
			if (src_id==id)
			{	
				cout<<" to "<<des_id;
			}
			else if (des_id==id)
			{	
				cout<<" from "<<src_id;
			}
			cout<<" -> ";
			Status s=t->get_state();
			if (s==pending)
				cout<<"pending"<<endl;
			else if (s==rejected)
				cout<<"rejected"<<endl;
			else if (s==accepted)
				cout<<"accepted"<<endl;

		}
	}
	
}