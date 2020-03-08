#include "../headers/job.h"
#include "../headers/user.h"
#include "../headers/education.h"
#include "../headers/experience.h"
#include "../headers/skill.h"
#include "../headers/company.h"

void Job::add_request(JobRequest* jobreq)
{
	requests.push_back(jobreq);
}
string JobRequest::to_string()
{
	return user->get_username() + (status?": confirmed":": not confirmed");
}