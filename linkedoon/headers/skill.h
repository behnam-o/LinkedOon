#ifndef __SKILL_H__
#define __SKILL_H__

#include <vector>
#include <string>
using namespace std;

class User;
class Skill
{
public:
	Skill(string n): name(n) {}
	string get_name() { return name; }
	void add_endorser(User* usr);
	vector<User*> get_endorsers();
private:
	string name;
	vector<User*> endorsers;
};
#endif