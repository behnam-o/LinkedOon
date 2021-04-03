#ifndef __COMPANY_H__
#define __COMPANY_H__ 

#include <string>
#include <vector>
using namespace std;

class Job;
class JobRequest;

class JobNotFound{};

class Company
{
public:
	Company(string u,string p):
		username(u),
		password(p),
		last_job_id(0)
	{}
	~Company();
	string get_username() { return username; }
	string get_name() { return name; }
	string get_ceo() { return ceo; }
	string get_description() { return description; }
	vector<Job*> get_jobs() { return jobs; } 
	void set_name(string n) { name=n; }
	void set_ceo(string c) { ceo=c; }
	void set_description(string d) { description=d; }
	bool is_password(string pass) { return pass==password; }
	int get_last_job_id() {return last_job_id;}
	void add_job(Job* job);
	Job* find_job_by_id(int id);
private:
	int last_job_id;
	string username;
	string password;
	string name;
	string ceo;
	string description;
	vector<Job*> jobs;
};
#endif