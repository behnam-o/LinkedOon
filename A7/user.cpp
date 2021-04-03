#include "user.h"
#define MAX_ATTEMPTS 3
#define BLOCK_TIME 120


string User::login(string p)
{
	if (time(NULL)-last_attempt>BLOCK_TIME)
	{
		attempts=0;
	}

	if (attempts>=MAX_ATTEMPTS)
	{
		if (time(NULL)-last_attempt<BLOCK_TIME)
		{
			cout<<"blocked for another "<<BLOCK_TIME-time(NULL)+last_attempt<<" seconds"<<endl;
			return "";
		}
		else
			attempts=0;	
	}

	if (p==password)
	{
		cout<<"Hello, "<<name<<" !"<<endl;
		attempts=0;
		return name;
	}
	last_attempt=time(NULL);
	attempts++;
	cout<<"Wrong Password ! "<< "Remaining attempts: "<<MAX_ATTEMPTS-attempts<<endl;
	if (attempts>=MAX_ATTEMPTS)
	{
		cout<<"blocked for "<<BLOCK_TIME<<" seconds"<<endl;
	}
	
	return "";
}
