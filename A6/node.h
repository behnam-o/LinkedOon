#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <vector>

using namespace std;

class Node;
typedef vector<Node*> Tree;

class InaccessibleNodeException{};

class Node
{
public:
	Node(int _id,Tree& _tree):id(_id),tree(&_tree)
	{ 
		if(id>=tree->size()) 
			throw InaccessibleNodeException();
		(*tree)[id]=this;
	}
	virtual int eval()=0;
	virtual void add_child_id(int _id)=0;
	virtual void change_value(string _value)=0;
	virtual void change_base(char _base)=0;
	virtual void change_mode(char _mode)=0;
	virtual bool check()=0;
protected:
	int id;
	Tree* tree;
	vector<int> child_ids;
};



#endif