#include "../headers/skill.h"
#include "../headers/user.h"
#include "../headers/education.h"
#include "../headers/experience.h"

vector<User*> Skill::get_endorsers()
{
	return endorsers;
}
void Skill::add_endorser(User* usr)
{
	endorsers.push_back(usr);
}