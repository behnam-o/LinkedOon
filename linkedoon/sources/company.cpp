#include "../headers/company.h"
#include "../headers/job.h"
#include "../headers/user.h"
#include "../headers/education.h"
#include "../headers/experience.h"
#include "../headers/skill.h"

void Company::add_job(Job* job)
{
	jobs.push_back(job);
	last_job_id++;
}
Company::~Company()
{
	for (int i = 0; i < jobs.size(); i++)
		delete jobs[i];
}
Job* Company::find_job_by_id(int id)
{
	for (int i = 0; i < jobs.size(); i++)
		if (jobs[i]->get_id()==id)
			return jobs[i];
	throw JobNotFound();
}