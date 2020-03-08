#include "../headers/butler.h"
#include "../headers/system.h"
#include "../headers/user.h"
#include "../headers/company.h"
#include "../headers/job.h"
#include "../headers/education.h"
#include "../headers/experience.h"
#include "../headers/skill.h"
#include "../headers/utils.h"

#include <vector>
#include <cstdlib>
#include <iostream>
void Butler::act(string command)
{
	vector<string> args=split_string(command,' ');
	if (system->current_user==NULL && system->current_company==NULL) // No one Logged in
	{
		if (args[0]=="signupu")
			signupu(args);
		else if (args[0]=="signupc")
			signupc(args);
		else if(args[0]=="login")
			login(args);
		else
			cout<<"Unknown command!"<<endl;
	}
	else if (system->current_user!=NULL) // User Logged in
	{
		if (args[0]=="logout")
			logout();
		else if (args[0]=="show_company")
			show_company(args);
		else if (args[0]=="search")
		{
				search_company(args,command);
				search_user(args,command);
		}
		else if (args[0]=="search_company")
			search_company(args,command);
		else if (args[0]=="search_user")
			search_user(args,command);
		else if (args[0]=="show_user")
			show_user(args);
		else if (args[0]=="show_usernames")
			show_usernames();
		else if (args[0]=="change_f_name")
			change_f_name(args,command);
		else if (args[0]=="change_l_name")
			change_l_name(args,command);
		else if (args[0]=="add_education")
			add_education(args,command);
		else if (args[0]=="add_experience")
			add_experience(args,command);
		else if (args[0]=="add_skill")
			add_skill(args,command);
		else if (args[0]=="show_profile")
			show_profileu();
		else if (args[0]=="apply")
			apply(args,command);
		else
			cout<<"Unknown command!"<<endl;
	}
	else if (system->current_company!=NULL) // Company logged in
	{
		if (args[0]=="logout")
			logout();
		else if (args[0]=="change_name")
			change_name(args,command);
		else if (args[0]=="show_company")
			show_company(args);
		else if (args[0]=="search")
		{
				search_user(args,command);
				search_company(args,command);
		}
		else if (args[0]=="search_company")
			search_company(args,command);
		else if (args[0]=="search_user")
			search_user(args,command);
		else if (args[0]=="show_user")
			show_user(args);
		else if (args[0]=="show_usernames")
			show_usernames();
		else if (args[0]=="change_ceo")
			change_ceo(args,command);
		else if (args[0]=="change_description")
			change_description(args,command);
		else if (args[0]=="show_profile")
			show_profilec();
		else if (args[0]=="add_job")
			add_job(args,command);
		else if (args[0]=="confirm")
			confirm(args,command);
		else
			cout<<"Unknown command!"<<endl;
	}	
}
void Butler::show_usernames()
{
	for (int i = 0; i < system->get_users().size(); i++)
	{
		cout<<"\tUser: "<<system->get_users()[i]->get_username()<<endl;
	}

	for (int i = 0; i < system->get_companies().size(); i++)
	{
		cout<<"\tCompany: "<<system->get_companies()[i]->get_username()<<endl;
	}	
}
void Butler::show_user(vector<string> args)
{
	if (args.size()!=2)
	{
		cout<<"Invalid Arguments!"<<endl;
		return;
	}
	for (int i = 0; i < system->get_users().size(); i++)
	{
		if (args[1]==system->get_users()[i]->get_username())
		{
			User* usr=system->get_users()[i];	
			cout<<"-username: "<<usr->get_username()<<endl;
			cout<<"-First Name:\n\t"<<usr->get_f_name()<<endl;
			cout<<"-Last Name:\n\t"<<usr->get_l_name()<<endl;
			cout<<"-Education:"<<endl;
			vector<Education> edu=usr->get_educations();
			for (int i = 0; i <edu.size(); i++)
				cout<<"\t-"<<edu[i].to_string()<<" in "<<edu[i].get_year()<<endl;
			cout<<"-Experience:"<<endl;
			vector<Experience> exp=usr->get_experiences();
			for (int i = 0; i <exp.size(); i++)
				cout<<"\t-"<<exp[i].to_string()<<" from "<<exp[i].get_start_year()<<" to "<<exp[i].get_end_year()<<endl;
			cout<<"-Skills:"<<endl;
			vector<Skill> skl=usr->get_skills();
			for (int i = 0; i <skl.size(); i++)
				cout<<"\t-"<<skl[i].get_name()<<" , Endorsed by: "<<skl[i].get_endorsers().size()<<endl;
			return;
		}
	}
	cout<<"User Not Found!"<<endl;
	return;
}
void Butler::show_company(vector<string> args)
{
	if (args.size()!=2)
	{
		cout<<"Invalid Arguments!"<<endl;
		return;
	}
	for (int i = 0; i < system->get_companies().size(); i++)
	{
		if (args[1]==system->get_companies()[i]->get_username())
		{
			Company* cmp=system->get_companies()[i];
			cout<<"-username: "<<cmp->get_username()<<endl;
			cout<<"-Name:\n\t"<<cmp->get_name()<<endl;
			cout<<"-CEO:\n\t"<<cmp->get_ceo()<<endl;
			cout<<"-Description:\n\t"<<cmp->get_description()<<endl;
			cout<<"-Jobs:\n";
			vector<Job*> jvec=cmp->get_jobs();
			for (int i = 0; i < jvec.size(); i++)
			{
				cout<<"\t"<<jvec[i]->get_id()<<": "<<jvec[i]->get_title()<<endl;
			}
			return;
		}
	}
	cout<<"Company Not Found!"<<endl;
	return;
}
void Butler::signupu(vector<string> args)
{
	if (args.size()!=3)
	{
		cout<<"Invalid Sign Up Arguments"<<endl;
		return;
	}
	try{
		system->signupu(args[1],args[2]);
		cout<<"User "<<args[1]<<" Signed Up!"<<endl;
	}catch(SignupException e){
		cout<<"This username is already registered!"<<endl;
	}
}
void Butler::signupc(vector<string> args)
{
	if (args.size()!=3)
	{
		cout<<"Invalid Sign Up Arguments"<<endl;
		return;
	}
	try{
		system->signupc(args[1],args[2]);
		cout<<"Company "<<args[1]<<" Signed Up!"<<endl;
	}catch(SignupException e){
		cout<<"This username is already registered!"<<endl;
	}
}
void Butler::login(vector<string> args)
{
	if (args.size()!=3)
	{
		cout<<"Invalid Arguments"<<endl;
		return;
	}
	try{
		system->login(args[1],args[2]);
		string u=(system->current_user!=NULL)?(system->current_user->get_username()):(system->current_company->get_username());
		cout<<"Welcome, "<<u<<endl;
	}catch(LoginException e){
		cout<<"Wrong username and/or password!"<<endl;
	}
}
void Butler::logout()
{
	cout<<"Bye, "<<(system->current_company?system->current_company->get_username():system->current_user->get_username())<<endl;
	system->logout();
}
void Butler::change_name(vector<string> args,string command)
{
	if (args.size()<2)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	system->current_company->set_name(command.substr(command.find(' ')+1));
}
void Butler::change_ceo(vector<string> args,string command)
{
	if (args.size()<2)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	system->current_company->set_ceo(command.substr(command.find(' ')+1));
}
void Butler::change_description(vector<string> args,string command)
{
	if (args.size()<2)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	system->current_company->set_description(command.substr(command.find(' ')+1));
}
void Butler::change_f_name(vector<string> args,string command)
{
	if (args.size()<2)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	system->current_user->set_f_name(command.substr(command.find(' ')+1));
}
void Butler::change_l_name(vector<string> args,string command)
{
	if (args.size()<2)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	system->current_user->set_l_name(command.substr(command.find(' ')+1));
}
void Butler::add_education(vector<string> args,string command)
{
	if (args.size()<2)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	string str=command.substr(command.find(' ')+1);
	vector<string> edu_args=split_string(str,',');
	if (edu_args.size()!=3)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	system->current_user->add_education(Education(edu_args[0],edu_args[1],atoi(edu_args[2].c_str())));	
}
void Butler::add_experience(vector<string> args,string command)
{
	if (args.size()<2)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	string str=command.substr(command.find(' ')+1);
	vector<string> exp_args=split_string(str,',');
	if (exp_args.size()!=4)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	system->current_user->add_experience(Experience(exp_args[0],exp_args[1],atoi(exp_args[2].c_str()),atoi(exp_args[3].c_str())));
}
void Butler::add_skill(vector<string> args,string command)
{
	if (args.size()<2)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	system->current_user->add_skill(Skill(command.substr(command.find(' ')+1)));
}
void Butler::show_profileu()
{
	cout<<"-username: "<<system->current_user->get_username()<<endl;
	cout<<"-First Name:\n\t"<<system->current_user->get_f_name()<<endl;
	cout<<"-Last Name:\n\t"<<system->current_user->get_l_name()<<endl;
	cout<<"-Education:"<<endl;
	vector<Education> edu=system->current_user->get_educations();
	for (int i = 0; i <edu.size(); i++)
		cout<<"\t-"<<edu[i].to_string()<<" in "<<edu[i].get_year()<<endl;
	cout<<"-Experience:"<<endl;
	vector<Experience> exp=system->current_user->get_experiences();
	for (int i = 0; i <exp.size(); i++)
		cout<<"\t-"<<exp[i].to_string()<<" from "<<exp[i].get_start_year()<<" to "<<exp[i].get_end_year()<<endl;
	cout<<"-Skills:"<<endl;
	vector<Skill> skl=system->current_user->get_skills();
	for (int i = 0; i <skl.size(); i++)
		cout<<"\t-"<<skl[i].get_name()<<" , Endorsed by: "<<skl[i].get_endorsers().size()<<endl;
	cout<<"-Job Requests:"<<endl;
	vector<JobRequest*> reqs=system->current_user->get_requests();
	for (int i = 0; i < reqs.size(); i++)
	{
		cout<<"\t-"<<
			reqs[i]->get_job()->get_title()<<" at "<<
			reqs[i]->get_job()->get_owner()->get_name()<<
			"( "<<reqs[i]->get_job()->get_owner()->get_username()<<" )"<<
			(reqs[i]->get_status()?": confirmed":": not confirmed")<<endl;
	}
}
void Butler::apply(vector<string> args,string command)
{
	if (args.size()<3)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	vector<Company*> comps=system->get_companies();
	Company* comp=NULL;
	for (int i = 0; i < comps.size(); i++)
	{
		if (comps[i]->get_username()==args[1])
		{
			comp=comps[i];
		}
	}
	if (comp==NULL)
	{
		cout<<"No Such Company"<<endl;
		return;
	}
	vector<Job*> jobs=comp->get_jobs();
	string id_str= command.substr(command.find(' ')+1);
	id_str= id_str.substr(id_str.find(' ')+1);
	int id=atoi(id_str.c_str());
	if (id<jobs.size())
	{
		system->current_user->apply(jobs[id]);
		return;
	}
	cout<<"No Such Job!"<<endl;
	return;
}
void Butler::show_profilec()
{
		cout<<"-username: "<<system->current_company->get_username()<<endl;
		cout<<"-Name:\n\t"<<system->current_company->get_name()<<endl;
		cout<<"-CEO:\n\t"<<system->current_company->get_ceo()<<endl;
		cout<<"-Description:\n\t"<<system->current_company->get_description()<<endl;
		cout<<"-Jobs:\n";
		vector<Job*> jvec=system->current_company->get_jobs();
		for (int i = 0; i < jvec.size(); i++)
		{
			cout<<"\t"<<jvec[i]->get_id()<<": "<<jvec[i]->get_title()<<endl;
			for (int j = 0; j < jvec[i]->get_requests().size(); j++)
			{
				cout<<"\t\t"<<jvec[i]->get_requests()[j]->to_string()<<endl;
			}
		}
}
void Butler::add_job(vector<string> args,string command)
{
	if (args.size()<2)
	{
		cout<<"Invalid arguments!"<<endl;
		return;
	}
	string jstr=command.substr(command.find(' ')+1);
	vector<string> jargs=split_string(jstr,',');
	if (jargs.size()!=5)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	vector<string> jskl=split_string(jargs[1],'/');
	vector<string> jkey=split_string(jargs[4],'/');
	system->current_company->add_job(new Job(system->current_company->get_last_job_id(),system->current_company,jargs[0],jskl,atoi(jargs[2].c_str()),jargs[3],jkey));
}
void Butler::confirm(vector<string> args,string command)
{
	if (args.size()!=3)
	{
		cout<<"Invalid arguments"<<endl;
		return;
	}
	int id=atoi(args[2].c_str());
	Job* jb;
	try{
		jb=system->current_company->find_job_by_id(id);
	}catch(JobNotFound e){
		cout<<"Job not found!"<<endl;
		return;
	}
	bool f=false;
	for (int i = 0; i < jb->get_requests().size(); i++)
	{
		if (jb->get_requests()[i]->get_user()->get_username()==args[1])
		{
			f=true;
			jb->get_requests()[i]->status=true;
		}
	}

	if(!f) cout<<"The User Hasn't requested for this job!"<<endl;
	return;
}
void Butler::search_company(vector<string> args,string command)
{
	if (args.size()<2)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	vector<Company*> comps=system->search_company(command.substr(command.find(' ')+1));
	for (int i = 0; i < comps.size(); i++)
		cout<<"\tCompany "<<i+1<<" : "<<comps[i]->get_username()<<endl;
}
void Butler::search_user(vector<string> args,string command)
{
	if (args.size()<2)
	{
		cout<<"Invalid arguemnts!"<<endl;
		return;
	}
	vector<User*> usrs=system->search_user(command.substr(command.find(' ')+1));
	for (int i = 0; i < usrs.size(); i++)
		cout<<"\tUser "<<i+1<<" : "<<usrs[i]->get_username()<<endl;
}