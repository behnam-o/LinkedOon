#include "transaction.h"

Transaction::Transaction(Account* _src,Account* _des,double _amount,int _id)
{
	src=_src;
	des=_des;
	amount=_amount;
	id=_id;
	state=pending;
	must_approve_ids=src->get_owner_ids();
	decisions=vector<Status>(must_approve_ids.size(),pending);
	src->add_transaction(this);
	des->add_transaction(this);
}
void Transaction::change_decisions(int cus_id,Status decision)
{
	int pos=-1;
	for (int i = 0; i < must_approve_ids.size(); i++)
	{
		if(must_approve_ids[i]==cus_id)
		{
			pos=i;
			break;
		}
	}
	if (pos!=-1)
	{
		{
			decisions[pos]=decision;
		}
		if (decision==rejected)
		{
			state=rejected;
			return;
		}
		for (int i = 0; i < decisions.size(); i++)
		{
			if (decisions[i]!=accepted)
			{
				return;
			}
		}
		if(src->get_balance()>=amount)
		{
			state=accepted;
			src->transact(*this);
		}
		else
			state=rejected;
	}
}