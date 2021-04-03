#ifndef __USER_H__
#define __USER_H__ 

#include <vector>
#include <string>
using namespace std;

class Education;
class Experience;
class Skill;
class Job;
class JobRequest;
class User
{
	public:
		User(string u,string p):
			username(u),
			password(p)
		{}
		~User();
		string get_username() { return username; }
		void set_f_name(string fn) { f_name=fn; }
		void set_l_name(string ln) { l_name=ln; }
		string get_f_name() { return f_name; }
		string get_l_name() { return l_name; }
		vector<JobRequest*> get_requests() {return requests;}
		bool is_password(string pass) { return pass==password; }
		vector<Education> get_educations();
		vector<Experience> get_experiences();
		vector<Skill> get_skills();
		void add_education(const Education& edu); 
		void add_experience(const Experience& exp);
		void add_skill(const Skill& skl);
		void apply(Job* job);
	private:
		string username;
		string password;
		string f_name;
		string l_name;
		vector<Education> educations;
		vector<Experience> experiences;
		vector<Skill> skills;
		vector<JobRequest*> requests;
};

#endif