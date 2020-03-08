#ifndef __JOB_H__
#define __JOB_H__ 

#include <vector>
#include <string>

using namespace std;

class Company;
class User;
class JobRequest;
class Job
{
public:
	Job(int i,Company* o,string t, vector<string> skl,int sal,string l,vector<string> k):
		id(i),
		owner(o),
		title(t),
		req_skills(skl),
		salary(sal),
		location(l),
		keywords(k)
	{}
	string get_title() {return title;}
    string get_location() {return location; }
    int get_salary() {return salary;}
	Company* get_owner() {return owner;}
	int get_id() {return id; }
	vector<JobRequest*> get_requests() { return requests; }
	void add_request(JobRequest* jobreq);
private:
	int id;
	Company* owner;
	string title;
	vector<string> req_skills;
	int salary;
	string location;
	vector<string> keywords;
	vector<JobRequest*> requests;
};

class JobRequest
{
public:
	JobRequest(Job* j,User* u): job(j), user(u), status(false) {}
	Job* get_job() {return job;}
	User* get_user() { return user;}
	bool get_status() { return status; }
	string to_string();
	bool status;
private:
	Job* job;
	User* user;
};

#endif
