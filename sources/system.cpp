#include "../headers/system.h"
#include "../headers/user.h"
#include "../headers/company.h"
#include "../headers/job.h"
#include "../headers/education.h"
#include "../headers/experience.h"
#include "../headers/skill.h"
#include "../headers/utils.h"


System::~System()
{
	for (int i = 0; i < users.size(); i++)
		delete users[i];
	for (int i = 0; i < companies.size(); i++)
		delete companies[i];
}
void System::login(string username,string password)
{
	for (int i = 0; i < users.size(); i++)
		if (users[i]->get_username()==username && users[i]->is_password(password))
		{
			current_user=users[i];
			return;
		}
	for (int i = 0; i < companies.size(); i++)
		if (companies[i]->get_username()==username && companies[i]->is_password(password))
		{
			current_company=companies[i];
			return;
		}
	throw LoginException();
}
void System::signupu(string username,string password)
{
	if (this->has_username(username))
		throw SignupException();
	users.push_back(new User(username,password));
}
void System::signupc(string username,string password)
{
	if (has_username(username))
		throw SignupException();
	companies.push_back(new Company(username,password));
}
vector<User*> System::search_user(string c)
{
	vector<bool> checked(users.size(),false);
	vector<User*> result;
	for (int i = 0; i < users.size(); i++)
	{
		if(		-1!=(int)(users[i]->get_username().find(c))
			|| 	-1!=(int)(users[i]->get_f_name().find(c))
			||	-1!=(int)(users[i]->get_l_name().find(c)))
		{
			result.push_back(users[i]);
			checked[i]=true;
		}
	}
	vector<string> cargs=split_string(c,' ');
	for (int i = 0; i < cargs.size(); i++)
	{
		for (int j = 0; j < users.size(); j++)
		{
			if (!checked[j])
			{
				if(		-1!=(int)(users[j]->get_username().find(cargs[i]))
					|| 	-1!=(int)(users[j]->get_f_name().find(cargs[i]))
					||	-1!=(int)(users[j]->get_l_name().find(cargs[i])))
				{
					result.push_back(users[j]);
					checked[j]=true;
				}			
			}
		}
	}
	return result;
}
vector<Company*> System::search_company(string c)
{
	vector<bool> checked(companies.size(),false);
	vector<Company*> result;
	for (int i = 0; i < companies.size(); i++)
	{
		if(		-1!=(int)(companies[i]->get_username().find(c))
			|| 	-1!=(int)(companies[i]->get_description().find(c))
			|| 	-1!=(int)(companies[i]->get_name().find(c))
			||	-1!=(int)(companies[i]->get_ceo().find(c)))
		{
			result.push_back(companies[i]);
			checked[i]=true;
		}
	}
	vector<string> cargs=split_string(c,' ');
	for (int i = 0; i < cargs.size(); i++)
	{
		for (int j = 0; j < companies.size(); j++)
		{
			if (!checked[j])
			{
				if(		-1!=(int)(companies[j]->get_username().find(cargs[i]))
					|| 	-1!=(int)(companies[i]->get_description().find(cargs[i]))
					|| 	-1!=(int)(companies[j]->get_name().find(cargs[i]))
					||	-1!=(int)(companies[j]->get_ceo().find(cargs[i])))
				{
					result.push_back(companies[j]);
					checked[j]=true;
				}			
			}
		}
	}
	return result;
}
void System::logout()
{
	current_user=NULL;
	current_company=NULL;
}
bool System::has_username(string un)
{
	for (int i = 0; i < users.size(); i++)
		if (users[i]->get_username()==un)
			return true;
	for (int i = 0; i < companies.size(); i++)
		if (companies[i]->get_username()==un)
			return true;
	return false;
}