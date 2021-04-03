#ifndef __ACTIONS_H
#define __ACTIONS_H 


#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "system.h"
#include "user.h"
#include "helpers.h"

using namespace std;

string get_command();
void 	   act(System& system,string& user,string command);
void act_login(System& system,string& user,string command);
void act_admin(System& system,string& user,string command);
void  act_user(System& system,string& user,string command);

#endif