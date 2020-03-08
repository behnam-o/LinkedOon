#include "../headers/user.h"
#include "../headers/education.h"
#include "../headers/experience.h"
#include "../headers/skill.h"
#include "../headers/job.h"
#include "../headers/company.h"

User::~User()
{
	for (int i = 0; i < requests.size(); i++)
		delete requests[i];
}
void User::add_education(const Education& edu)
{
	educations.push_back(edu);
}
void User::add_experience(const Experience& exp)
{
	experiences.push_back(exp);
}
void User::add_skill(const Skill& skl)
{
	skills.push_back(skl);
}
vector<Education> User::get_educations() 
{
	return educations;
}
vector<Experience> User::get_experiences()
{
	return experiences;
}
vector<Skill> User::get_skills() 
{
	return skills;
}
void User::apply(Job* job)
{
	JobRequest* jr=new JobRequest(job,this);
	requests.push_back(jr);
	job->add_request(jr);
}